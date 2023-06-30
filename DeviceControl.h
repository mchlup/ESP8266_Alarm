// soubor DeviceControl.h

#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <Arduino.h>
#include <EEPROM.h>

#include "WifiModule.h"
#include "AlarmModule.h"
#include "GSMModule.h"

class DeviceControl {
public:
  DeviceControl();

  void setup();
  void update();

  // Metody pro ovládání zařízení přes příkazový řádek
  void setPhoneNumber(const String& phoneNumber);
  void setWifiCredentials(const String& ssid, const String& password);
  void setAPCredentials(const String& apSSID, const String& apPassword);
  void setAlarmDuration(unsigned long alarmDuration);
  void setAlarmMode(bool smsMode);
  void activateAlarm();
  void deactivateAlarm();

private:
  // Proměnné pro uchovávání konfigurace
  String m_phoneNumber;
  String m_ssid;
  String m_password;
  String m_apSSID;
  String m_apPassword;
  unsigned long m_alarmDuration;
  bool m_smsMode;

  // Instance modulů
  WifiModule m_wifiModule;
  AlarmModule m_alarmModule;
  GSMModule m_gsmModule;

  // Adresy EEPROM pro ukládání konfigurace
  const int PHONE_NUMBER_EEPROM_ADDR = 0;
  const int SSID_EEPROM_ADDR = 20;
  const int PASSWORD_EEPROM_ADDR = 40;
  const int AP_SSID_EEPROM_ADDR = 60;
  const int AP_PASSWORD_EEPROM_ADDR = 80;
  const int ALARM_DURATION_EEPROM_ADDR = 100;
  const int SMS_MODE_EEPROM_ADDR = 120;

  // Metody pro čtení/zápis konfigurace do EEPROM
  void readConfigurationFromEEPROM();
  void saveConfigurationToEEPROM();
};

#endif