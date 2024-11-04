
#include "lib/i2c.h"
#include "lib/time.h"

uint16 i2cClkDelayT = 0;
uint16 i2cClkHalfDelayT = 0;

bool i2cWriteStart(uint8 addr, bool read) {
    I2c_SdaPort = 1;
    I2c_SclPort = 1;
    delay50Us(i2cClkHalfDelayT);
    I2c_SdaPort = 0;
    delay50Us(i2cClkHalfDelayT);
    I2c_SclPort = 0;
    return i2cWriteByte((addr << 1) | read);
}

void i2cWriteEnd() {
    I2c_SclPort = 0;
    I2c_SdaPort = 0;
    delay50Us(i2cClkDelayT);
    I2c_SclPort = 1;
    delay50Us(i2cClkHalfDelayT);
    I2c_SdaPort = 1;
    delay50Us(i2cClkHalfDelayT);
}

void i2cNopClock(uint16 cnt) {
    uint16 i;
    I2c_SdaPort = 0;
    for (i=0; i<cnt; i++) {
        I2c_SclPort = 0;
        delay50Us(i2cClkDelayT);
        I2c_SclPort = 1;
        delay50Us(i2cClkDelayT);
    }
}

void i2cSetClockFreq(uint16 freq) {
    i2cClkDelayT = 20000 / freq;
    i2cClkHalfDelayT = i2cClkDelayT / 2;
}

uint8 i2cReadByte() {
    uint8 res, i;
    res = 0;

    for (i=0; i<8; i++) {
        I2c_SclPort = 0;
        delay50Us(i2cClkDelayT);
        I2c_SdaPort = 1;
        I2c_SclPort = 1;
        delay50Us(i2cClkDelayT);
        res = res << 1;
        res |= I2c_SdaPort;
    }

    I2c_SclPort = 0;
    return res;
}

void i2cWriteAck(bool isAck) {
    I2c_SclPort = 0;
    I2c_SdaPort = !isAck;
    delay50Us(i2cClkDelayT);
    I2c_SclPort = 1;
    delay50Us(i2cClkDelayT);
    I2c_SclPort = 0;
}

bool i2cWriteByte(uint8 byte) {
    uint8 i, ack;

    for (i=0; i<8; i++) {
        I2c_SclPort = 0;
        I2c_SdaPort = (byte >> 7);
        byte = byte << 1;
        delay50Us(i2cClkDelayT);
        I2c_SclPort = 1;
        delay50Us(i2cClkDelayT);
    }

    // read ack
    I2c_SclPort = 0;
    // poll up for read
    I2c_SdaPort = 1;
    delay50Us(i2cClkDelayT);
    I2c_SclPort = 1;
    delay50Us(i2cClkDelayT);
    ack = !I2c_SdaPort;
    I2c_SclPort = 0;

    return ack;
}