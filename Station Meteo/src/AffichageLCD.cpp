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

void AffichageLCD:: AfficherMessageVeille(byte p_estEnVeille)
{
    this->m_lcd.clear();
    this->m_lcd.print("Mode veille");
    this->m_lcd.setCursor(0,1);

    p_estEnVeille?this->m_lcd.print("Actif"):this->m_lcd.print("Inactif");
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

void AffichageLCD::AfficherInfos(float p_temperature, float p_humidite, float p_pression)
{
    unsigned long temps = millis();

    if (temps - this->m_tempsPrecedent > 2500)
    {
        this->m_tempsPrecedent = temps;
        this->m_lcd.clear();

        if (this->m_changerDonnees)
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print(String("Temp: ") + String(p_temperature) + String(char(223)) + String("C"));
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print(String("Humidite: ")+ String(p_humidite) + String("%"));
        }
        else
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print(String("Pression: "));
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print(String(p_pression/1000.0f)+ String("kPa"));
        }

        this->m_changerDonnees = !this->m_changerDonnees;
    }
}