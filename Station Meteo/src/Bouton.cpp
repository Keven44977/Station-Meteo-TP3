#include "Bouton.h"

Bouton::Bouton(byte p_pinBouton) : m_pinbouton(p_pinBouton)
{
    pinMode(this->m_pinbouton, INPUT);
    this->m_etatPrecedent = digitalRead(p_pinBouton);
    this->m_etatCourant = this->m_etatPrecedent;
}

byte Bouton::EstMaintenu()
{
    return digitalRead(this->m_pinbouton);
}

byte Bouton::EstRelacher()
{
    byte estRelacher = false;

    this->m_etatCourant = !digitalRead(m_pinbouton);

    if (this->m_etatCourant != this->m_etatPrecedent)
    {
        estRelacher = true;
        this->m_etatPrecedent = this->m_etatCourant;
    }

    return estRelacher;
}

byte Bouton::EstAppuyer()
{
    digitalRead(m_pinbouton) ? this->m_etatPrecedent = false : this->m_etatPrecedent = true;

    return this->m_etatPrecedent;
}