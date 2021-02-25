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
    ServeurMQTT m_serveurMQTT;
    byte m_addrLcd = 0x27;
    byte m_addr = 0x76;
    byte m_pinBouton = 26;

    Bme280 m_bme = Bme280(m_addr);
    AffichageLCD m_lcd = AffichageLCD(m_addrLcd);
    Bouton m_bouton = Bouton(m_pinBouton);

    byte m_allumerLCD = 1;
public:
    StationMeteo();
    void Setup();
    void Executer();
};