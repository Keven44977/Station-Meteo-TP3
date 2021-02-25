#include <AffichageLCD.h>

AffichageLCD::AffichageLCD(byte p_adresse) : m_adresseLCD(p_adresse)
{
}

void AffichageLCD::Initialiser()
{
    this->m_lcd = LiquidCrystal_I2C(this->m_adresseLCD, 16, 2);
    this->m_lcd.init();
    this->m_lcd.clear();    
    this->m_lcd.backlight();
    this->m_lcd.print("Station Meteo");
    delay(2500);
}

void AffichageLCD::Allumer()
{
    this->m_lcd.backlight();
}

void AffichageLCD::Eteindre()
{
    this->m_lcd.clear();
    this->m_lcd.noBacklight();
}

void AffichageLCD::AfficherMessageWifiManager()
{
    this->m_lcd.clear();
    this->m_lcd.print("Connexion au");
    this->m_lcd.setCursor(0,1);
    this->m_lcd.print("reseau wifi...");
}

void AffichageLCD::AfficherMessageMQTT()
{
    this->m_lcd.clear();
    this->m_lcd.print("Connexion au");
    this->m_lcd.setCursor(0, 1);
    this->m_lcd.print("serveur MQTT...");
}

void AffichageLCD::AfficherMessageReset(){
    this->m_lcd.clear();
    this->m_lcd.print("Parametres Wifi");
    this->m_lcd.setCursor(0,1);
    this->m_lcd.print("Reinitialises");
}

void AffichageLCD::AfficherInfos(float p_temperature, float p_humidite, float p_pression, float p_altitude)
{
    unsigned long temps = millis();

    if (temps - this->m_tempsPrecedent > 2500)
    {
        this->m_tempsPrecedent = temps;
        this->m_lcd.clear();

        if (this->m_changerDonnees)
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print("Temp: ");
            this->m_lcd.print(p_temperature);
            this->m_lcd.print("C");
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print("Hum: ");
            this->m_lcd.print(p_humidite);
            this->m_lcd.print("%");
        }
        else
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print("Pres: ");
            this->m_lcd.print(p_pression / 100.0f);
            this->m_lcd.print("hPa");
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print("Alt: ");
            this->m_lcd.print(p_altitude);
            this->m_lcd.print("m");
        }

        this->m_changerDonnees = !this->m_changerDonnees;
    }
}