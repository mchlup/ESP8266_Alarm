// soubor EEPROMModule.h

#ifndef EEPROMMODULE_H
#define EEPROMMODULE_H

#include <Arduino.h>
#include <EEPROM.h>

template <class T>
class EEPROMModule {
public:
  EEPROMModule(int address, const T& defaultValue)
    : m_address(address), m_defaultValue(defaultValue) {}

  T read() {
    T value;
    EEPROM.get(m_address, value);
    if (value == m_defaultValue) {
      return m_defaultValue;
    }
    return value;
  }

  void write(const T& value) {
    EEPROM.put(m_address, value);
    EEPROM.commit();
  }

private:
  int m_address;
  T m_defaultValue;
};

#endif
