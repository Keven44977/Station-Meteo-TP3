#pragma once
#include <Arduino.h>

class Bouton
{
private:
    const byte m_pinbouton;
    byte m_etatPrecedent;
    byte m_etatCourant;

public:
    Bouton(byte p_pinBouton);
    byte EstRelacher();
    byte EstAppuyer();
    byte EstMaintenu();
};