#include <bme280.h>

Bme280::Bme280(byte p_adresse_bme) : m_adresse_bme(p_adresse_bme) {}

void Bme280::Initialiser() 
{
    if (!this->m_bme.begin(this->m_adresse_bme))
    {
        Serial.println("BME280 non valid, non trouvee");
        while (1);
    }
    this->m_bme.begin(this->m_adresse_bme);
}

void Bme280::LireInformationBme280()
{
    this->m_temperature = this->m_bme.readTemperature();
    this->m_humidite = this->m_bme.readHumidity();
    this->m_pression = this->m_bme.readPressure();
}
