#pragma once
#include <BME280.h>
#include <affichageLCD.h>
#include <BME280.h>
#include <ServeurMQTT.h>
#include <Arduino.h>

class StationMeteo 
{
private:
    AffichageLCD lcd;
    ServeurMQTT serveurMQTT;
    byte addr = 0x76;
    Bme280 bme = Bme280(addr);
public:
    StationMeteo();
    void Setup();
    void Executer();
};