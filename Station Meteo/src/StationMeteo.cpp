#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::Setup()
{
    this->serveurMQTT.Configuration();
    this->lcd.Initialiser();
    this->bme.EtatInitial();
}

void StationMeteo::Executer()
{
    this->bme.LireInformationBme280();
    this->serveurMQTT.Loop(this->bme);

    if(this->allumerLCD)
    {
     this->lcd.AfficherInfos(this->bme.m_temperature, this->bme.m_humidite, this->bme.m_pression, this->bme.m_altitude);
    }

    if (this->bouton.EstRelacher() && this->bouton.EstAppuyer())
    {
        this->allumerLCD = !this->allumerLCD;
        this->allumerLCD?this->lcd.Allumer():this->lcd.Eteindre();
    }
}
