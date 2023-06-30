// soubor GSMModule.cpp

#include "GSMModule.h"

GSMModule::GSMModule() : m_gsmSerial(GSM_RX_PIN, GSM_TX_PIN) {}

void GSMModule::setup() {
  m_gsmSerial.begin(9600);
  m_gsmInitialized = false;
  m_callStartTime = 0;
  m_callActive = false;

  readPhoneNumberFromEEPROM();
}

void GSMModule::update() {
  if (!m_gsmInitialized) {
    initializeGSM();
  }

  if (m_callActive) {
    unsigned long currentMillis = millis();
    if (currentMillis - m_callStartTime >= m_callDuration) {
      endCall();
    }
  }
}

void GSMModule::setPhoneNumber(const String& phoneNumber) {
  m_phoneNumber = phoneNumber;
  savePhoneNumberToEEPROM();
}

void GSMModule::setCallDuration(unsigned long callDuration) {
  m_callDuration = callDuration;
}

void GSMModule::initializeGSM() {
  m_gsmSerial.println("AT");
  delay(1000);

  m_gsmSerial.println("AT+CPIN?");
  delay(1000);

  m_gsmSerial.println("AT+CMGF=1");
  delay(1000);

  m_gsmSerial.println("AT+CNMI=2,2,0,0,0");
  delay(1000);

  m_gsmInitialized = true;
}

void GSMModule::sendSMS(const String& message) {
  m_gsmSerial.println("AT+CMGS=\"" + m_phoneNumber + "\"");
  delay(1000);

  m_gsmSerial.println(message);
  delay(100);

  m_gsmSerial.println((char)26);
  delay(1000);
}

void GSMModule::makeCall() {
  m_gsmSerial.println("ATD" + m_phoneNumber + ";");
  delay(1000);
  m_callStartTime = millis();
  m_callActive = true;
}

void GSMModule::endCall() {
  m_gsmSerial.println("ATH");
  delay(1000);
  m_callActive = false;
}

void GSMModule::readPhoneNumberFromEEPROM() {
  int addr = PHONE_NUMBER_EEPROM_ADDR;
  byte b;
  m_phoneNumber = "";

  do {
    b = EEPROM.read(addr);
    if (b != 0) {
      m_phoneNumber += (char)b;
      addr++;
    }
  } while (b != 0);
}

void GSMModule::savePhoneNumberToEEPROM() {
  int addr = PHONE_NUMBER_EEPROM_ADDR;

  for (int i = 0; i < m_phoneNumber.length(); i++) {
    EEPROM.write(addr, m_phoneNumber[i]);
    addr++;
  }
  EEPROM.write(addr, 0);
}
