#pragma once
#include <BME280.h>
#include <affichageLCD.h>
#include <ServeurMQTT.h>
#include <Arduino.h>

class StationMeteo 
{
private:
    AffichageLCD lcd;
    ServeurMQTT serveurMQTT;
public:
    StationMeteo();
    void Setup();
    void Executer();
};