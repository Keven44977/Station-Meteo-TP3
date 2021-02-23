#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::Setup()
{
    this->serveurMQTT.Configuration();
}

void StationMeteo::Executer()
{
    this->serveurMQTT.Loop();
    this->lcd.AfficherInfos(this->bme.EnvoyerTemperature(), this->bme.EnvoyerHumidite(), this->bme.EnvoyerPression(), this->bme.EnvoyerAltitude());
}
