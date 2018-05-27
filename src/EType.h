/*
 * ----------------------------------------------------------------------------
 *
 *  This file is part of EType library
 * 
 *  EType library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EType library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EType library.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef ETYPE_H
#define ETYPR_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <EEPROM.h>

#define MAX_STRING_LENGTH 32

/*
 * ----------------------------------------------------------------------------
 * Before any operations with EEPROM on ESP8266 we need to call function
 * EEPROM.begin()
 * 
 */

#ifdef ESP8266
  #include "spi_flash.h"
  class EEPROM_init {
  public:
    EEPROM_init() {EEPROM.begin(SPI_FLASH_SEC_SIZE);}
  };
#endif

/*
 * ----------------------------------------------------------------------------
 *  Anything
 *  
 */


template<class C>
class EType {
public:
  EType(int offset);
  
  operator C() const { return m_value; }
  const C* operator->() const { return &m_value; }
  C operator=(const C& value);
  bool operator==(const C& value) {return value == m_value;}
  bool operator!=(const C& value) {return value != m_value;}
  static int size() { return sizeof(C); }
private:
  C m_value;
  int m_offset;
};


template<class C>
EType<C>::EType(int offset)
{
  #ifdef ESP8266
  static EEPROM_init init;
  #endif  
  m_offset = offset;
  byte* p = (byte*)(void*)&m_value;
  for (byte i = 0; i < sizeof(C); i++)
    *p++ = EEPROM.read(m_offset+i);

}
template<class C>
C EType<C>::operator=(const C& value)
{
  m_value = value;
  const byte* p = (const byte*)(const void*)&m_value;
  #ifdef ESP8266
  for (byte i = 0; i < sizeof(C); i++) {
    EEPROM.write(m_offset+i, *p++);
    EEPROM.commit();
  }
  #else
  for (byte i = 0; i < sizeof(C); i++)
    EEPROM.update(m_offset+i, *p++);
  #endif
  
  return m_value;
}

/*
 * ----------------------------------------------------------------------------
 *  byte
 *  
 */

template<>
class EType<byte> 
{
public:
  EType(int offset) {
    #ifdef ESP8266
    static EEPROM_init init;
    #endif
    m_offset = offset;
    m_value = EEPROM.read(m_offset);
  }
  
  operator byte() const { return m_value; }
  byte operator=(const byte& value) {
      m_value = value;
      #ifdef ESP8266
      EEPROM.write(m_offset, value);
      EEPROM.commit();
      #else
      EEPROM.update(m_offset, value);
      #endif
      return m_value;
  }
  bool operator==(const byte& value) {return value == m_value;}
  bool operator!=(const byte& value) {return value != m_value;}
  const byte* operator->() const { return &m_value; }
  static byte size() {return 1;}
private:
  int m_offset;
  byte m_value;
};

typedef EType<byte> EByte;

/*
 * ----------------------------------------------------------------------------
 *  char
 *  
 */

typedef EType<char> EChar;

/*
 * ----------------------------------------------------------------------------
 *  int
 *  
 */

typedef EType<int> EInt;

/*
 * ----------------------------------------------------------------------------
 *  string (fixed length)
 *  
 */

class EString {
public:
  EString(int offset);
  
  operator const char*() const { return m_value; }
  char* operator=(const char* arg) { this->write(arg);return m_value; }
  char* operator=(const String& arg) { this->write(arg.c_str());return m_value; }
  bool operator==(const char* arg) { return strcmp(m_value,arg) == 0; }
  bool operator!=(const char* arg) { return !(strcmp(m_value,arg) == 0); }
  static int size() { return MAX_STRING_LENGTH; }
private:
  void write(const char* value);
  int m_offset;
  char m_value[MAX_STRING_LENGTH];
};

typedef EType<uint32_t> EIPAddress;


#endif //EEPROM_VALUES_H
