#include "Bouton.h"

Bouton::Bouton(byte p_pinBouton) : m_pinbouton(p_pinBouton)
{
    pinMode(this->m_pinbouton, INPUT);
    this->m_etatPrecedent = !digitalRead(p_pinBouton);
    this->m_etatCourant = this->m_etatPrecedent;
}

byte Bouton::EstRelacher()
{
    byte estRelacher = false;

    this->m_etatCourant = !digitalRead(m_pinbouton);

    if (this->m_etatCourant != this->m_etatPrecedent)
    {
        estRelacher = true;
        Serial.println("relacher");
        this->m_etatPrecedent = this->m_etatCourant;
    }

    return estRelacher;
}

byte Bouton::EstAppuyer()
{
    digitalRead(m_pinbouton) ? this->m_etatPrecedent = false : this->m_etatPrecedent = true;
    Serial.println("Appuyer");
    return this->m_etatPrecedent;
}