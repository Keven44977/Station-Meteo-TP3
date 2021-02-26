#pragma once
#include <BME280.h>
#include <AffichageLCD.h>
#include <ServeurMQTT.h>
#include <Bouton.h>
#include "WiFi.h"

class StationMeteo 
{
private:
    ServeurMQTT m_serveurMQTT;
    const byte m_addrLcd = 0x27;
    const byte m_addr = 0x76;
    byte m_pinBouton = 26;

    Bme280 m_bme = Bme280(m_addr);
    AffichageLCD m_lcd = AffichageLCD(m_addrLcd);
    Bouton m_bouton = Bouton(m_pinBouton);

    byte m_allumerLCD;
    byte m_modeHorsLigne;

    void GestionMenuDemarrage();
public:
    StationMeteo();
    void Setup();
    void Executer();
};