// soubor AlarmModule.cpp

#include "AlarmModule.h"

Alarm::Alarm() {}

void Alarm::setup() {
  pinMode(PLOVAK_PIN, INPUT_PULLUP);
  pinMode(AC230_PIN, INPUT_PULLUP);
  pinMode(REZERVA_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Nastavení výchozích hodnot
  m_plovakState = false;
  m_ac230State = false;
  m_rezervaState = false;
  m_alarmStartTime = 0;
  m_alarmDuration = 30000; // Výchozí doba trvání alarmu: 30 sekund
  m_alarmActive = false;
  m_alarmTriggered = false;
}

void Alarm::update() {
  readInputs();
  updateAlarm();
}

void Alarm::readInputs() {
  // Čtení stavů vstupů s odrušováním
  static unsigned long plovakLastDebounceTime = 0;
  static unsigned long ac230LastDebounceTime = 0;
  static unsigned long rezervaLastDebounceTime = 0;

  unsigned long currentMillis = millis();

  // Plovák
  if (currentMillis - plovakLastDebounceTime > DEBOUNCE_TIME) {
    bool plovakReading = digitalRead(PLOVAK_PIN);
    if (plovakReading != m_plovakState) {
      plovakLastDebounceTime = currentMillis;
      m_plovakState = plovakReading;
    }
  }

  // AC230
  if (currentMillis - ac230LastDebounceTime > DEBOUNCE_TIME) {
    bool ac230Reading = digitalRead(AC230_PIN);
    if (ac230Reading != m_ac230State) {
      ac230LastDebounceTime = currentMillis;
      m_ac230State = ac230Reading;
    }
  }

  // Rezerva
  if (currentMillis - rezervaLastDebounceTime > DEBOUNCE_TIME) {
    bool rezervaReading = digitalRead(REZERVA_PIN);
    if (rezervaReading != m_rezervaState) {
      rezervaLastDebounceTime = currentMillis;
      m_rezervaState = rezervaReading;
    }
  }
}

void Alarm::updateAlarm() {
  if (m_plovakState || m_ac230State || m_rezervaState) {
    if (!m_alarmActive) {
      activateAlarm();
    }
  } else {
    if (m_alarmActive) {
      unsigned long currentMillis = millis();
      if (currentMillis - m_alarmStartTime >= m_alarmDuration) {
        deactivateAlarm();
      }
    }
  }
}

void Alarm::activateAlarm() {
  m_alarmActive = true;
  m_alarmTriggered = true;
  m_alarmStartTime = millis();

  // Spustit bzučák
  controlBuzzer(true);

  // Další akce při aktivaci alarmu (např. odeslání zprávy)
  // ...
}

void Alarm::deactivateAlarm() {
  m_alarmActive = false;
  m_alarmTriggered = false;

  // Zastavit bzučák
  controlBuzzer(false);

  // Další akce při deaktivaci alarmu (např. zaznamenání do logu)
  // ...
}

void Alarm::controlBuzzer(bool state) {
  digitalWrite(BUZZER_PIN, state ? HIGH : LOW);
}
