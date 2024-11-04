
#ifndef _lib_eeprom
#define _lib_eeprom

#include "lib/type.h"
#include "lib/i2c.h"

// Supported AT24Cxx series eeprom

void eepromStart(uint8 i2cAddr, uint16 i2cFreq, uint16 pageSize);
void eepromEnd();

void eepromReadBuff(uint32 addr, uint8 *buff, uint32 len);
uint8 eepromReadByte(uint32 addr);

void eepromWriteBuff(uint32 addr, uint8 *buff, uint32 len);
void eepromWriteByte(uint32 addr, uint8 byte);

void eepromFill(uint32 addr, uint8 byte, uint32 len);

#endif /* _lib_eeprom */