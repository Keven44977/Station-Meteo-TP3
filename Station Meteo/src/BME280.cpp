#include <bme280.h>

Bme280::Bme280(byte p_adresse_bme) : m_adresse_bme(p_adresse_bme) {}

void Bme280::EtatInitial() 
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
    EtatInitial();

    this->m_temperature = this->m_bme.readTemperature();
    this->m_humidite = this->m_bme.readHumidity();
    this->m_pression = this->m_bme.readPressure();
    this->m_altitude = this->m_bme.readAltitude(1013.25);
}

float Bme280::EnvoyerAltitude()
{
    return this->m_altitude;
}

float Bme280::EnvoyerTemperature()
{
    return this->m_temperature;
}

float Bme280::EnvoyerHumidite()
{
    return this->m_humidite;
}

float Bme280::EnvoyerPression()
{
    return this->m_pression;
}
