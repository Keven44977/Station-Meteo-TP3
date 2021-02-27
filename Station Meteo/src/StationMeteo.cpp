#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::GestionMenuDemarrage()
{
    byte reinitialiserWifi = 0;

    //Si le bouton est maintenue au demarrage, il faut soit réinitialiser le wifi ou bien mettre le esp en veille
    if (this->m_bouton.EstMaintenu())
    {
        Serial.println("Mode Hors Ligne");
        this->m_lcd.AfficherMessageVeille(1);

        delay(5000);

        //Si après 5 secondes le bouton est toujours maintenue, il faut redémarrer les paramètres wifi
        if (this->m_bouton.EstMaintenu())
        {
            reinitialiserWifi = 1;
            Serial.println("Paramètres WifiManager réinitialisés");
            this->m_lcd.AfficherMessageReset();
        }
        else
        {
            //Sinon il faut mettre le esp32 en mode "modem sleep"
            this->m_modeHorsLigne = 1;
            btStop();
            WiFi.mode(WIFI_OFF);
        }

        delay(2500);
    }

    // Si le mode hors ligne est INACTIF
    if (!this->m_modeHorsLigne)
    {
        //Affiche que le mode veille est inactif
        this->m_lcd.AfficherMessageVeille(0);

        delay(2500);

        //Vérifie s'il faut réinitialiser les params wifi
        if (reinitialiserWifi)
        {
            this->m_serveurMQTT.ReinitialiserWifi();
        }

        //Initialisation standard
        this->m_lcd.AfficherMessageWifiManager();
        this->m_serveurMQTT.Initialiser();
    }
}

void StationMeteo::Setup()
{
    this->m_lcd.Initialiser();
    this->m_bme.Initialiser();
    GestionMenuDemarrage();
}

void StationMeteo::Executer()
{
    //Lis les informations du BME280
    this->m_bme.LireInformationBme280();

    //Publie sur MQTT si le esp est en mode actif
    if (!this->m_modeHorsLigne)
    {
        this->m_serveurMQTT.Loop(this->m_bme, this->m_lcd);
    }

    //Affiche les infos si le lcd est allumé
    if (this->m_allumerLCD)
    {
        this->m_lcd.AfficherInfos(this->m_bme.m_temperature, this->m_bme.m_humidite, this->m_bme.m_pression);
    }

    //Allume ou éteint l'écran si le bouton est appuyé
    if (this->m_bouton.EstRelacher() && this->m_bouton.EstAppuyer())
    {
        this->m_allumerLCD = !this->m_allumerLCD;
        this->m_allumerLCD ? this->m_lcd.Allumer() : this->m_lcd.Eteindre();
    }
}
