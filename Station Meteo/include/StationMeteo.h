#pragma once
#include <BME280.h>
#include <affichageLCD.h>
#include <BME280.h>
#include <ServeurMQTT.h>
#include <Arduino.h>
#include <Bouton.h>

class StationMeteo 
{
private:
    ServeurMQTT serveurMQTT;
    byte addrLcd = 0x27;
    byte addr = 0x76;
    byte pinBouton = 26;

    Bme280 bme = Bme280(addr);
    AffichageLCD lcd = AffichageLCD(addrLcd);
    Bouton bouton = Bouton(pinBouton);

    byte allumerLCD = 1;
public:
    StationMeteo();
    void Setup();
    void Executer();
};