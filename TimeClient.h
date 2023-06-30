/*
  Serial.print("Datum: ");
  Serial.print(timeClient.year);
  Serial.print("-");
  Serial.print(timeClient.month);
  Serial.print("-");
  Serial.println(timeClient.day);

  Serial.print("Čas: ");
  Serial.print(timeClient.hours);
  Serial.print(":");
  if (timeClient.minutes < 10) {
    Serial.print("0"); // Přidá nulu pro jednocifernou minutu
  }
  Serial.println(timeClient.minutes);
*/

#ifndef TimeClient_h
#define TimeClient_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class TimeClient {
public:
  TimeClient();
  void setup(const char* ssid, const char* password);
  void update();
  unsigned long getEpochTime();
  void setTimeOffset(int offset);
  void setServer(const char* serverName);
  
private:
  void sendNTPPacket();
  void processNTPResponse();

  const char* _ssid;
  const char* _password;
  const char* _serverName;
  int _timeOffset;
  unsigned long _epochTime;
  unsigned long _lastUpdate;
  
  WiFiUDP _udp;
  IPAddress _timeServerIP;
  byte _packetBuffer[48];

public:
  int year;
  int month;
  int day;
  int hours;
  int minutes;
};

#endif
