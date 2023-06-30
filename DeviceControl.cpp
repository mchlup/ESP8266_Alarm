// soubor DeviceControl.cpp

#include "DeviceControl.h"

DeviceControl::DeviceControl() {}

void DeviceControl::setup() {
  // Inicializace modulů
  m_wifiModule = WifiModule();
  m_alarmModule = AlarmModule();
  m_gsmModule = GSMModule();

  // Načtení konfigurace z EEPROM
  readConfigurationFromEEPROM();

  // Nastavení konfigurace pro moduly
  m_gsmModule.setPhoneNumber(m_phoneNumber);
  m_wifiModule.connectToWifi(m_ssid.c_str(), m_password.c_str());
  m_wifiModule.startAPMode(m_apSSID.c_str(), m_apPassword.c_str());
  m_alarmModule.setAlarmDuration(m_alarmDuration);
}

void DeviceControl::update() {
  // Aktualizace modulů
  m_wifiModule.handleClientRequests();
  m_alarmModule.update();
  m_gsmModule.update();
}

void DeviceControl::setPhoneNumber(const String& phoneNumber) {
  m_phoneNumber = phoneNumber;
  saveConfigurationToEEPROM();
  m_gsmModule.setPhoneNumber(m_phoneNumber);
}

void DeviceControl::setWifiCredentials(const String& ssid, const String& password) {
  m_ssid = ssid;
  m_password = password;
  saveConfigurationToEEPROM();
  m_wifiModule.connectToWifi(m_ssid.c_str(), m_password.c_str());
}

void DeviceControl::setAPCredentials(const String& apSSID, const String& apPassword) {
  m_apSSID = apSSID;
  m_apPassword = apPassword;
  saveConfigurationToEEPROM();
  m_wifiModule.startAPMode(m_apSSID.c_str(), m_apPassword.c_str());
}

void DeviceControl::setAlarmDuration(unsigned long alarmDuration) {
  m_alarmDuration = alarmDuration;
  saveConfigurationToEEPROM();
  m_alarmModule.setAlarmDuration(m_alarmDuration);
}

void DeviceControl::setAlarmMode(bool smsMode) {
  m_smsMode = smsMode;
  saveConfigurationToEEPROM();
}

void DeviceControl::activateAlarm() {
  m_alarmModule.activateAlarm();
}

void DeviceControl::deactivateAlarm() {
  m_alarmModule.deactivateAlarm();
}

void DeviceControl::readConfigurationFromEEPROM() {
  // Načtení konfigurace z EEPROM
  m_phoneNumber = EEPROM.readString(PHONE_NUMBER_EEPROM_ADDR);
  m_ssid = EEPROM.readString(SSID_EEPROM_ADDR);
  m_password = EEPROM.readString(PASSWORD_EEPROM_ADDR);
  m_apSSID = EEPROM.readString(AP_SSID_EEPROM_ADDR);
  m_apPassword = EEPROM.readString(AP_PASSWORD_EEPROM_ADDR);
  m_alarmDuration = EEPROM.readULong(ALARM_DURATION_EEPROM_ADDR);
  m_smsMode = EEPROM.readBool(SMS_MODE_EEPROM_ADDR);
}

void DeviceControl::saveConfigurationToEEPROM() {
  // Uložení konfigurace do EEPROM
  EEPROM.writeString(PHONE_NUMBER_EEPROM_ADDR, m_phoneNumber);
  EEPROM.writeString(SSID_EEPROM_ADDR, m_ssid);
  EEPROM.writeString(PASSWORD_EEPROM_ADDR, m_password);
  EEPROM.writeString(AP_SSID_EEPROM_ADDR, m_apSSID);
  EEPROM.writeString(AP_PASSWORD_EEPROM_ADDR, m_apPassword);
  EEPROM.writeULong(ALARM_DURATION_EEPROM_ADDR, m_alarmDuration);
  EEPROM.writeBool(SMS_MODE_EEPROM_ADDR, m_smsMode);
}
