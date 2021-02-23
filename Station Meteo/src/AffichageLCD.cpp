#include <AffichageLCD.h>

AffichageLCD::AffichageLCD(byte p_adresse) : m_adresseLCD(p_adresse)
{
}

void AffichageLCD::Initialiser()
{
    this->m_lcd = LiquidCrystal_I2C(this->m_adresseLCD, 16, 2);
    this->m_lcd.init();
    this->m_lcd.backlight();
    this->m_lcd.clear();
    this->m_lcd.print("Station Meteo");
}

void AffichageLCD::AfficherInfos(float p_temperature, float p_humidite, float p_pression, float p_altitude)
{
    long temps = millis();

    if (temps - this->m_tempsPrecedent > 2000)
    {
        this->m_tempsPrecedent = temps;
        this->m_lcd.clear();

        if (this->m_changerDonnees)
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print("Temp: ");
            this->m_lcd.print(p_temperature);
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print("Humidite: ");
            this->m_lcd.print(p_humidite);
        }
        else
        {
            this->m_lcd.setCursor(0, 0);
            this->m_lcd.print("Pression: ");
            this->m_lcd.print(p_pression);
            this->m_lcd.setCursor(0, 1);
            this->m_lcd.print("Altitude: ");
            this->m_lcd.print(p_altitude);
        }

        this->m_changerDonnees = !this->m_changerDonnees;
    }
}