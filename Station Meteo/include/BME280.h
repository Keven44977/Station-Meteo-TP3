#pragma once
#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

class Bme280{
private:
    Adafruit_BME280 m_bme;
    const byte m_adresse_bme;
public:
    float m_temperature;
    float m_humidite;
    float m_pression;
    float m_altitude;
    
    Bme280(const byte p_adresse_bme);
    void Initialiser();
    void LireInformationBme280();
};