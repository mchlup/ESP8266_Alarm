#include "TimeClient.h"
#include <WiFiUdp.h>

TimeClient::TimeClient() {
  _ssid = nullptr;
  _password = nullptr;
  _serverName = nullptr;
  _timeOffset = 0;
  _epochTime = 0;
  _lastUpdate = 0;
}

void TimeClient::setup(const char* ssid, const char* password) {
  _ssid = ssid;
  _password = password;
  
  WiFi.begin(_ssid, _password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  _udp.begin(8888);
}

void TimeClient::update() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - _lastUpdate >= 1000) {
    _lastUpdate = currentMillis;
    sendNTPPacket();
    
    if (_udp.parsePacket()) {
      processNTPResponse();
    }
  }

  struct tm * timeinfo;
  time_t epochTime = getEpochTime();
  timeinfo = gmtime(&epochTime);
  
  year = timeinfo->tm_year + 1900;
  month = timeinfo->tm_mon + 1;
  day = timeinfo->tm_mday;
  hours = timeinfo->tm_hour;
  minutes = timeinfo->tm_min;
}

unsigned long TimeClient::getEpochTime() {
  return _epochTime + (_timeOffset * 3600);
}

void TimeClient::setTimeOffset(int offset) {
  _timeOffset = offset;
}

void TimeClient::setServer(const char* serverName) {
  _serverName = serverName;
  WiFi.hostByName(_serverName, _timeServerIP);
}

void TimeClient::sendNTPPacket() {
  memset(_packetBuffer, 0, 48);
  _packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  _packetBuffer[1] = 0;            // Stratum, or type of clock
  _packetBuffer[2] = 6;            // Polling Interval
  _packetBuffer[3] = 0xEC;         // Peer Clock Precision
  _packetBuffer[12] = 49;
  _packetBuffer[13] = 0x4E;
  _packetBuffer[14] = 49;
  _packetBuffer[15] = 52;

  _udp.beginPacket(_timeServerIP, 123);
  _udp.write(_packetBuffer, 48);
  _udp.endPacket();
}

void TimeClient::processNTPResponse() {
  _udp.read(_packetBuffer, 48);
  
  unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
  unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  
  const unsigned long seventyYears = 2208988800UL;
  _epochTime = secsSince1900 - seventyYears;
}
