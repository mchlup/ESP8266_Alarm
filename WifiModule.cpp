// soubor WifiModule.cpp

#include "WifiModule.h"

WifiModule::WifiModule() {}

void WifiModule::connectToWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  
  // Wait for connection to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Connection successful
  Serial.println("Connected to WiFi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void WifiModule::startAPMode(const char* apSSID, const char* apPassword) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSSID, apPassword);
  
  Serial.println("Access Point created");
  Serial.print("SSID: ");
  Serial.println(apSSID);
  Serial.print("Password: ");
  Serial.println(apPassword);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  setupWebServer();
}

void WifiModule::handleClientRequests() {
  m_server.handleClient();
}

void WifiModule::setupWebServer() {
  m_server.on("/", HTTP_GET, [this](){
    m_server.send(200, "text/plain", "Hello, world!");
  });
  
  m_server.begin();
  Serial.println("Web server started");
}
