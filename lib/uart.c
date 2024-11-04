
#include <Atmel/REGX52.H>
#include "lib/uart.h"

#if Uart_ReceiveBuffEnabled

uint8 uartBuff[Uart_BuffSize];
uint32 uartBuffUsedSize = 0;

#endif /* Uart_ReceiveBuffEnabled */


void uartInit() {
    // working mode 1
    // 8bit uart
    // baud rate depends on timer 1
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;

    // disable baud rate double
    PCON &= 0x7f;

    // allow serial receiving
    REN = 1;
    // enable interrupt
    ES = 1;
    EA = 1;

    // using timer 1
    // 8bit mode, auto reload
    TMOD &= 0x0F;
    TMOD |= 0x20;

    // baud rate setting
    TL1 = 0xff;
    TH1 = Uart_TimerReloadValue;

    // interrupt here is useless
    ET1 = 0;
    // start timer
    TR1 = 1;
}

void uartSendBuff(const uint8 *buff, uint32 len) {
    uint32 i;
    for (i=0; i<len; i++) {
        SBUF = buff[i];
        while (!TI);
        TI = 0;
    }
}

void uartSendByte(uint8 byte) {
    SBUF = byte;
    while (!TI);
    TI = 0;
}

void uartReceiveInterrupt() interrupt 4 {
    uint8 byte;

    if (RI) {
        byte = SBUF;

        #if Uart_ReceiveByteEnabled
        uartRecieveByte(byte);
        #endif /* Uart_ReceiveByteEnabled */

        #if Uart_ReceiveBuffEnabled
        if (SBUF == Uart_BuffEndByte) {
            uartReceiveBuff(uartBuff, uartBuffUsedSize);
            uartBuffUsedSize = 0;
        } else uartBuff[uartBuffUsedSize ++] = byte;
        #endif /* Uart_ReceiveBuffEnabled */

        RI = 0;
    }
}