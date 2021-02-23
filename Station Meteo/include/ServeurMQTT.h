#pragma once
#include <BME280.h>
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <WiFiManager.h>
#include <FS.h>
#include <ArduinoJson.h>

class ServeurMQTT
{
private:
    WiFiManager m_wifiManager;
    char mqtt_serveur[40];
    char mqtt_port[5];
    char mqtt_utilisateur[30];
    char mqtt_motDePasse[100];

	//const char* m_ssid_pointAcces = "StationMeteo1234";
	//const char* m_motDePasse_pointAcces = "StationMeteo1234";

	const char* m_serveur_mqtt = "192.168.2.52";
    const int m_port_mqtt = 1883;
    const char* m_utilisateur = "homeassistant";
    const char* m_motDePasseUtilisateur = "ahweeNg0heeyi5aeX1geegh7eip7oht8Biebo6icilu9shee0gai8kieCho5awie";

    unsigned long m_tempsDernierMessage;

    WiFiClient m_espClient;
    byte m_addr = 0x76;
    PubSubClient m_client = PubSubClient(m_espClient);
    Bme280 m_bme = Bme280(m_addr);

    void Reconnecter();
    void Publier();
public:
    ServeurMQTT();
    void Configuration();
    void Loop();
};