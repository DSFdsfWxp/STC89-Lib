
#ifndef _lib_i2c
#define _lib_i2c

#include <Atmel/REGX52.H>
#include "lib/type.h"

// I2c master for single i2c port
// Max i2c clock frequency supported up to 500

#define I2c_SclPort P2_1
#define I2c_SdaPort P2_0

bool i2cWriteStart(uint8 addr, bool read);
void i2cWriteEnd();
void i2cNopClock(uint16 cnt);
void i2cSetClockFreq(uint16 freq);

uint8 i2cReadByte();
void i2cWriteAck(bool isAck);
bool i2cWriteByte(uint8 byte);

#endif /* _lib_i2c */