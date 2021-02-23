#include <StationMeteo.h>

StationMeteo::StationMeteo() {}

void StationMeteo::Setup()
{
    this->serveurMQTT.Configuration();
}

void StationMeteo::Executer()
{
    this->serveurMQTT.Loop();
}
