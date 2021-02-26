#include <ServeurMQTT.h>

bool shouldSaveConfig = false;

ServeurMQTT::ServeurMQTT() {}

void SauvegardeConfigCallback()
{
    Serial.println("Devrait sauvegarder la config");
    shouldSaveConfig = true;
}

void ServeurMQTT::LectureCongiguration()
{
    if (shouldSaveConfig)
    {
        Serial.println("Lecture de configuration");

        this->m_fichierConfiguration = SPIFFS.open(this->m_fichier, "r");
        Serial.println("Fichier de configuration ouvert");

        deserializeJson(this->m_doc, this->m_fichierConfiguration);

        this->m_doc["serveurMQTT"] = this->mqtt_serveur;
        this->m_doc["portMQTT"] = this->mqtt_port;
        this->m_doc["utilisateur"] = this->mqtt_utilisateur;
        this->m_doc["MotDePasse"] = this->mqtt_motDePasse;

        serializeJsonPretty(this->m_doc, this->m_fichierConfiguration);

        this->m_fichierConfiguration.close();

        shouldSaveConfig = false;
    }
}

void ServeurMQTT::ReinitialiserWifi()
{
    this->m_wifiManager.resetSettings();
}

void ServeurMQTT::Initialiser()
{
    WiFi.mode(WIFI_STA);
    //ajouter la serialization json ici

    this->m_wifiManager.setSaveConfigCallback(SauvegardeConfigCallback);

    WiFiManagerParameter custom_mqtt_serveur("serveur", "mqtt serveur", this->m_serveur_mqtt, 40);
    WiFiManagerParameter custom_mqtt_port("port", "mqtt port", this->m_port_mqtt, 5);
    WiFiManagerParameter custom_mqtt_utitilisateur("utilisateur", "mqtt utilisateur", this->m_utilisateur, 30);
    WiFiManagerParameter custom_mqtt_motDePasse("motDePasse", "mqtt motDePasse", this->m_motDePasseUtilisateur, 100);

    this->m_wifiManager.addParameter(&custom_mqtt_serveur);
    this->m_wifiManager.addParameter(&custom_mqtt_port);
    this->m_wifiManager.addParameter(&custom_mqtt_utitilisateur);
    this->m_wifiManager.addParameter(&custom_mqtt_motDePasse);

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

    strcpy(this->mqtt_serveur, custom_mqtt_serveur.getValue());
    strcpy(this->mqtt_port, custom_mqtt_port.getValue());
    strcpy(this->mqtt_utilisateur, custom_mqtt_utitilisateur.getValue());
    strcpy(this->mqtt_motDePasse, custom_mqtt_motDePasse.getValue());

    this->m_client.setServer(this->mqtt_serveur, atoi(this->mqtt_port));
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

    char altitudeString[15];
    dtostrf(p_bme.m_altitude, 7, 3, altitudeString);
    Serial.print("Altitude: ");
    Serial.println(altitudeString);
    this->m_client.publish("esp32/altitude", altitudeString);
}

void ServeurMQTT::Loop(Bme280 p_bme, AffichageLCD p_lcd)
{
    if (!this->m_client.connected())
    {
        ConnecterMQTT(p_lcd);
    }
    else
    {
        long temps = millis();

        if (temps - this->m_tempsDernierMessage > 5000)
        {
            this->m_tempsDernierMessage = temps;
            this->m_client.loop();

            Publier(p_bme);
        }
    }
}
