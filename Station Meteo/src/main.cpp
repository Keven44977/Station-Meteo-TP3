#include <Arduino.h>
#include <StationMeteo.h>

StationMeteo stationMeteo;

void setup() {
  Serial.begin(115200);
  stationMeteo.Setup();
}

void loop() {
  stationMeteo.Executer();
}