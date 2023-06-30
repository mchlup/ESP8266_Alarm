// soubor GSMModule.h

#ifndef GSMMODULE_H
#define GSMMODULE_H

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

class GSMModule {
public:
  GSMModule();
  void setup();
  void update();

  void setPhoneNumber(const String& phoneNumber);
  void setCallDuration(unsigned long callDuration);

private:
  const int GSM_TX_PIN = 6;
  const int GSM_RX_PIN = 7;

  const int PHONE_NUMBER_EEPROM_ADDR = 0;

  String m_phoneNumber;
  unsigned long m_callDuration;

  SoftwareSerial m_gsmSerial;
  bool m_gsmInitialized;
  unsigned long m_callStartTime;
  bool m_callActive;

  void initializeGSM();
  void sendSMS(const String& message);
  void makeCall();
  void endCall();
  void readPhoneNumberFromEEPROM();
  void savePhoneNumberToEEPROM();
};

#endif
