// soubor WifiModule.h

#ifndef WIFIMODULE_H
#define WIFIMODULE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WifiModule {
public:
  WifiModule();

  void connectToWifi(const char* ssid, const char* password);
  void startAPMode(const char* apSSID, const char* apPassword);
  void handleClientRequests();

private:
  void setupWebServer();
  
  ESP8266WebServer m_server;
};

#endif
