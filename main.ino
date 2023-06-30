#include "EEPROMModule.h"
#include "WifiModule.h"
#include "AlarmModule.h"
#include "GSMModule.h"
#include "WebServerModule.h"
//#include "TimeClient.h"

//TimeClient timeClient;

void setup() {
  Serial.begin(115200);
  //WifiModule.connectToWifi("r6wifi", "internet") ;
  //timeClient.setup(ssid, password);
  //timeClient.setServer(ntpServer);
  //timeClient.setTimeOffset(2);  // Nastavení posunu času na +2 hodiny  
}

void loop() {
  //timeClient.update();
}
