#pragma once
#include <FS.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <AffichageLCD.h>
#include <BME280.h>

class ServeurMQTT
{
private:
    WiFiManager m_wifiManager;
    char mqtt_serveur[40];
    char mqtt_port[5];
    char mqtt_utilisateur[30];
    char mqtt_motDePasse[100];
    
    const char* m_fichier = "/configuration.json";
    File m_fichierConfiguration;
    DynamicJsonDocument m_doc = DynamicJsonDocument(1024);

	//const char* m_ssid_pointAcces = "StationMeteo1234";
	//const char* m_motDePasse_pointAcces = "StationMeteo1234";

    //Kev: .90
    //Dust: .52
    //Cegep: 10.200.80.175
	const char* m_serveur_mqtt = "192.168.2.90";
    const char* m_port_mqtt = "1883";
    const char* m_utilisateur = "admin";
    const char* m_motDePasseUtilisateur = "adminadmin";

    unsigned long m_tempsDernierMessage;

    WiFiClient m_espClient;
    PubSubClient m_client = PubSubClient(m_espClient);

    void ConnecterMQTT(AffichageLCD p_lcd);
    void Publier(Bme280 p_bme);
public:
    ServeurMQTT();
    void ReinitialiserWifi();
    void Initialiser();
    void Loop(Bme280 p_bme, AffichageLCD p_lcd);
    void LectureCongiguration();
};