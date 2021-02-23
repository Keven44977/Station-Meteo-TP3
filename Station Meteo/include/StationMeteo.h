#pragma once
#include <BME280.h>
#include <affichageLCD.h>
#include <BME280.h>
#include <ServeurMQTT.h>
#include <Arduino.h>

class StationMeteo 
{
private:
    ServeurMQTT serveurMQTT;
    byte addrLcd = 0x27;
    byte addr = 0x76;
    Bme280 bme = Bme280(addr);
    AffichageLCD lcd = AffichageLCD(addrLcd);
public:
    StationMeteo();
    void Setup();
    void Executer();
};