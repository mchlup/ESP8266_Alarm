// soubor AlarmModule.h

#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>

class Alarm {
public:
  Alarm();
  void setup();
  void update();

private:
  // Pinová nastavení
  const int PLOVAK_PIN = 2;
  const int AC230_PIN = 3;
  const int REZERVA_PIN = 4;
  const int BUZZER_PIN = 5;

  // Časy pro odrušování filtru (v milisekundách)
  const unsigned long DEBOUNCE_TIME = 50;
  const unsigned long TRIGGER_DELAY = 500;

  // Stavy vstupů
  bool m_plovakState;
  bool m_ac230State;
  bool m_rezervaState;

  // Časy pro měření doby trvání alarmu
  unsigned long m_alarmStartTime;
  unsigned long m_alarmDuration;

  // Stavy alarmu
  bool m_alarmActive;
  bool m_alarmTriggered;

  // Metody pro zpracování vstupů
  void readInputs();
  void updateAlarm();
  void activateAlarm();
  void deactivateAlarm();

  // Metoda pro ovládání bzučáku
  void controlBuzzer(bool state);
};

#endif
