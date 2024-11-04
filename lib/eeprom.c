
#include "lib/time.h"
#include "lib/eeprom.h"

uint8  eepromI2cAddr  = 0;
uint16 eepromI2cFreq  = 0;
uint16 eepromPageSize = 0;

void eepromStart(uint8 i2cAddr, uint16 i2cFreq, uint16 pageSize) {
    eepromI2cAddr = i2cAddr;
    eepromI2cFreq = i2cFreq;
    eepromPageSize = pageSize;
}

void eepromEnd() {
    eepromI2cAddr = 0;
    eepromI2cFreq = 0;
    eepromPageSize = 0;
}

void eepromReadBuff(uint32 addr, uint8 *buff, uint32 len) {
    uint8 i;
    i = 0;
    i2cSetClockFreq(eepromI2cFreq);
    while(!i2cWriteStart(eepromI2cAddr, false));
    i2cWriteByte(addr);
    i2cWriteStart(eepromI2cAddr, true);

    while (i < len) {
        buff[i ++] = i2cReadByte();
        i2cWriteAck(i < len);
    }

    i2cWriteEnd();
}

uint8 eepromReadByte(uint32 addr) {
    uint8 res;
    eepromReadBuff(addr, &res, 1);
    return res;
}

void eepromWriteBuff(uint32 addr, uint8 *buff, uint32 len) {
    uint32 i;
    i2cSetClockFreq(eepromI2cFreq);

    for (i=0; i<len; i++, addr++) {
        // switch to next page
        if (addr % eepromPageSize == 0 || !i) {
            if (i) i2cWriteEnd();
            while (!i2cWriteStart(eepromI2cAddr, false));
            i2cWriteByte(addr);
        }
        
        i2cWriteByte(buff[i]);
    }

    i2cWriteEnd();
}

void eepromWriteByte(uint32 addr, uint8 byte) {
    eepromWriteBuff(addr, &byte, 1);
}

void eepromFill(uint32 addr, uint8 byte, uint32 len) {
    uint32 i;
    i2cSetClockFreq(eepromI2cFreq);

    for (i=0; i<len; i++, addr++) {
        if (addr % eepromPageSize == 0 || !i) {
            if (i) i2cWriteEnd();
            while (!i2cWriteStart(eepromI2cAddr, false));
            i2cWriteByte(addr);
        }
        
        i2cWriteByte(byte);
    }

    i2cWriteEnd();
}