#include <ServeurMQTT.h>

bool devraitSauvegarderConfiguration = false;

ServeurMQTT::ServeurMQTT() {}

void SauvegardeConfigCallback()
{
    Serial.println("Devrait sauvegarder la config");
    devraitSauvegarderConfiguration = true;
}

void ServeurMQTT::LectureParametreWifiManager()
{
    if (SPIFFS.begin(true))
    {
        Serial.println("Systeme de fichier monter");

        if (SPIFFS.exists(this->m_fichier))
        {
            Serial.println("Lecture du fichier de configuration");

            this->m_fichierConfiguration = SPIFFS.open(this->m_fichier, "r");

            if (this->m_fichierConfiguration)
            {
                Serial.println("Fichier de configuration ouvert");

                size_t taille = this->m_fichierConfiguration.size();
                std::unique_ptr<char[]> amortisseur(new char[taille]);

                this->m_fichierConfiguration.readBytes(amortisseur.get(), taille);
                DeserializationError erreur = deserializeJson(this->m_doc, amortisseur.get());
                serializeJson(this->m_doc, Serial);

                if (!erreur)
                {
                    strcpy(this->mqtt_serveur, this->m_doc["mqtt_serveur"]);
                    strcpy(this->mqtt_port, this->m_doc["mqtt_port"]);
                    strcpy(this->mqtt_utilisateur, this->m_doc["mqtt_utilisateur"]);
                    strcpy(this->mqtt_motDePasse, this->m_doc["mqtt_motDePasse"]);
                }
                else
                {
                    Serial.println("Erreur de chargement de configurations");
                }
            }
        }
    }
    else
    {
        Serial.println("Erreur de montage FS");
    }
}

void ServeurMQTT::EnregistrerParametresWifiManager()
{
    if (devraitSauvegarderConfiguration)
    {
        Serial.println("Sauvegarde de configuration");

        deserializeJson(this->m_doc, this->m_fichierConfiguration);

        this->m_doc["mqtt_serveur"] = this->mqtt_serveur;
        this->m_doc["mqtt_port"] = this->mqtt_port;
        this->m_doc["mqtt_utilisateur"] = this->mqtt_utilisateur;
        this->m_doc["mqtt_motDePasse"] = this->mqtt_motDePasse;

        this->m_fichierConfiguration = SPIFFS.open(this->m_fichier, "w");

        if (!this->m_fichierConfiguration)
        {
            Serial.println("Erreur lors de l'ouverture du fichier de configuration");
        }
        else
        {
            Serial.println("Fichier de configuration ouvert");
        }

        serializeJson(this->m_doc, this->m_fichierConfiguration);

        this->m_fichierConfiguration.close();

        devraitSauvegarderConfiguration = false;
    }
}

void ServeurMQTT::ReinitialiserWifi()
{
    this->m_wifiManager.resetSettings();
}

void ServeurMQTT::Initialiser()
{
    WiFi.mode(WIFI_STA);

    //Lire les parametres dans le fichiers config.json
    LectureParametreWifiManager();

    this->m_wifiManager.setSaveConfigCallback(SauvegardeConfigCallback);

    //Creation de 4 parametres
    WiFiManagerParameter custom_mqtt_serveur("mqtt_serveur", "mqtt serveur", this->m_serveur_mqtt, 40);
    WiFiManagerParameter custom_mqtt_port("mqtt_port", "mqtt port", this->m_port_mqtt, 5);
    WiFiManagerParameter custom_mqtt_utitilisateur("mqtt_utilisateur", "mqtt utilisateur", this->m_utilisateur, 30);
    WiFiManagerParameter custom_mqtt_motDePasse("mqtt_motDePasse", "mqtt motDePasse", this->m_motDePasseUtilisateur, 100);

    //Ajouter les 4 parametres
    this->m_wifiManager.addParameter(&custom_mqtt_serveur);
    this->m_wifiManager.addParameter(&custom_mqtt_port);
    this->m_wifiManager.addParameter(&custom_mqtt_utitilisateur);
    this->m_wifiManager.addParameter(&custom_mqtt_motDePasse);

    ConnectionAuAccessPoint();

    //Recupere les valeurs dans les parametres et  les set dans les variables
    strcpy(this->mqtt_serveur, custom_mqtt_serveur.getValue());
    strcpy(this->mqtt_port, custom_mqtt_port.getValue());
    strcpy(this->mqtt_utilisateur, custom_mqtt_utitilisateur.getValue());
    strcpy(this->mqtt_motDePasse, custom_mqtt_motDePasse.getValue());

    //Enregistre les parametres si c'est la premiere connexion au serveur
    EnregistrerParametresWifiManager();

    //Connexion au bon serveur avec le bon port dans la sauvegarde
    this->m_client.setServer(this->mqtt_serveur, atoi(this->mqtt_port));
}

void ServeurMQTT::ConnectionAuAccessPoint()
{
    if (!this->m_wifiManager.autoConnect("Super Station Meteo", "12341234"))
    {
        Serial.println("Erreur de connexion");
        delay(2000);
        ESP.restart();
    }
    else
    {
        Serial.println("Connexion etablie");
    }
}

void ServeurMQTT::ConnecterMQTT(AffichageLCD p_lcd)
{
    Serial.println("Connexion au serveur Mqtt...");
    p_lcd.AfficherMessageMQTT();

    if (this->m_client.connect("esp32", this->m_utilisateur, this->m_motDePasseUtilisateur))
    {
        Serial.println("Connecté");
    }
    else
    {
        Serial.print("Echec : ");
        Serial.print(this->m_client.state());
        Serial.println(" Nouvelle tentative de connection dans 5 secondes");
    }

    delay(5000);
}

void ServeurMQTT::Publier(Bme280 p_bme)
{
    Serial.println();

    //Publie au serveur mqtt la temperature, l'humidite et la pression a un certain sujet
    char temperatureString[15];
    dtostrf(p_bme.m_temperature, 7, 3, temperatureString);
    Serial.print("Temperature: ");
    Serial.println(temperatureString);
    this->m_client.publish("esp32/temperature", temperatureString);

    char humiditeString[15];
    dtostrf(p_bme.m_humidite, 7, 3, humiditeString);
    Serial.print("Humidite: ");
    Serial.println(humiditeString);
    this->m_client.publish("esp32/humidite", humiditeString);

    char pressionString[15];
    dtostrf(p_bme.m_pression / 1000.0f, 7, 3, pressionString);
    Serial.print("Pression: ");
    Serial.println(pressionString);
    this->m_client.publish("esp32/pression", pressionString);
}

void ServeurMQTT::Loop(Bme280 p_bme, AffichageLCD p_lcd)
{
    //Si le client n'est pas connecté au MQTT
    if (!this->m_client.connected())
    {
        //Il se connecte au serveur
        ConnecterMQTT(p_lcd);
    }
    else
    {
        //Sinon il publie les données à chaque 5 secondes
        long temps = millis();

        if (temps - this->m_tempsDernierMessage > 5000)
        {
            this->m_tempsDernierMessage = temps;
            this->m_client.loop();

            Publier(p_bme);
        }
    }
}
