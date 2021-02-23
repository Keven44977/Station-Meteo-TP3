#include <AffichageLCD.h>

AffichageLCD::AffichageLCD(){}

AffichageLCD::AffichageLCD(byte p_adresse)
{
    this->m_adresseLCD = p_adresse;
    this->m_lcd = LiquidCrystal_I2C(this->m_adresseLCD, 16, 2);
}

void AffichageLCD::AfficherInfos(float p_temperature, float p_humidite, float p_pression, float p_altitude)
{
    long temp = millis();

    if (temp - this->m_tempsPrecedent > 2000)
    {
        this->m_tempsPrecedent = temp;

        m_lcd.clear();

        if (this->m_changerDonnees)
        {
            m_lcd.setCursor(0, 0);
            m_lcd.print("Temperature: " + String(p_temperature) + "*C");
            m_lcd.setCursor(0, 1);
            m_lcd.print("Humidité: " + String(p_humidite) + "%");
        }
        else
        {
            m_lcd.setCursor(0, 0);
            m_lcd.print("Pression: " + String(p_pression / 100) + "hPa");
            m_lcd.setCursor(0, 1);
            m_lcd.print("Altitude: " + String(p_pression) + "m");
        }

        this->m_changerDonnees = !this->m_changerDonnees;
    }
}