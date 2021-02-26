#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::Setup()
{
    this->m_lcd.Initialiser();
    this->m_bme.EtatInitial();    
    this->m_serveurMQTT.Configuration(this->m_lcd, this->m_bouton);
}

void StationMeteo::Executer()
{
    this->m_bme.LireInformationBme280();
    this->m_serveurMQTT.Loop(this->m_bme, this->m_lcd);

    //Affiche les infos si le lcd est allumé
    if(this->m_allumerLCD)
    {
     this->m_lcd.AfficherInfos(this->m_bme.m_temperature, this->m_bme.m_humidite, this->m_bme.m_pression, this->m_bme.m_altitude);
    }

    //Allume ou éteint l'écran si le bouton est appuyé
    if (this->m_bouton.EstRelacher()&& this->m_bouton.EstAppuyer())
    {
        this->m_allumerLCD = !this->m_allumerLCD;
        this->m_allumerLCD?this->m_lcd.Allumer():this->m_lcd.Eteindre();
    }
}
