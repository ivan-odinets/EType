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

#include "EType.h"

/*
 * ----------------------------------------------------------------------------
 *  string (fixed length)
 *  
 */

EString::EString(int offset)
{
  m_offset = offset;
  for (byte i = 0; i < MAX_STRING_LENGTH; i++)
    m_value[i] = EEPROM.read(m_offset+i);

  #ifdef ESP8266
  static EEPROM_init init;
  #endif
}
void EString::write(const char* value)
{
  if (strlen(value) < MAX_STRING_LENGTH)
    strcpy(m_value,value);
  
  for (byte i = 0; i < MAX_STRING_LENGTH; i++)
    EEPROM.write(m_offset+i,m_value[i]);

  #ifdef ESP8266
  EEPROM.commit();
  #endif
}

