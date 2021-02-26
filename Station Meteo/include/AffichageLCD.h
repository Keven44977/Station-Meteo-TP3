#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class AffichageLCD
{
private:
    LiquidCrystal_I2C m_lcd = LiquidCrystal_I2C(0x00, 0, 0);
    const byte m_adresseLCD;
    unsigned long m_tempsPrecedent;
    char m_changerDonnees;

public:
    AffichageLCD(const byte p_adresse);
    void Initialiser();
    void Allumer();
    void Eteindre();
    void AfficherMessageVeille(byte p_estEnVeille);
    void AfficherMessageMQTT();
    void AfficherMessageWifiManager();
    void AfficherMessageReset();
    void AfficherInfos(float p_temp, float p_humidite, float p_pression, float p_altitude);
};