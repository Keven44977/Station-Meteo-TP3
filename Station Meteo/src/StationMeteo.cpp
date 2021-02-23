#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::Setup()
{
    this->serveurMQTT.Configuration();
    this->lcd.Initialiser();
}

void StationMeteo::Executer()
{
    this->serveurMQTT.Loop();
    this->bme.LireInformationBme280();
    this->lcd.AfficherInfos(this->bme.EnvoyerTemperature(), this->bme.EnvoyerHumidite(), this->bme.EnvoyerPression(), this->bme.EnvoyerAltitude());
}
