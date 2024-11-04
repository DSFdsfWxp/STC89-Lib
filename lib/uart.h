
#ifndef _lib_uart
#define _lib_uart

#include "lib/type.h"

/*
Baud Rate Available

12MHz, 12T, 8bit Timer
┌─────────┬────────────────────┬───────────────────┬────────────────────┬────────────────────┐
│ (index) │ Standard Baud Rate │ Actual Baud Rate  │ Inaccuracy         │ Timer Reload Value │
├─────────┼────────────────────┼───────────────────┼────────────────────┼────────────────────┤
│ 0       │ 600                │ 600.9615384615385 │ 0.9615384615384528 │ 204                │
│ 1       │ 1200               │ 1201.923076923077 │ 1.9230769230769056 │ 230                │
│ 2       │ 2400               │ 2403.846153846154 │ 3.846153846153811  │ 243                │
└─────────┴────────────────────┴───────────────────┴────────────────────┴────────────────────┘

11.0592MHz, 12T, 8bit Timer
┌─────────┬────────────────────┬──────────────────┬────────────┬────────────────────┐
│ (index) │ Standard Baud Rate │ Actual Baud Rate │ Inaccuracy │ Timer Reload Value │
├─────────┼────────────────────┼──────────────────┼────────────┼────────────────────┤
│ 0       │ 600                │ 600              │ 0          │ 208                │
│ 1       │ 1200               │ 1200             │ 0          │ 232                │
│ 2       │ 2400               │ 2400             │ 0          │ 244                │
│ 3       │ 4800               │ 4800             │ 0          │ 250                │
│ 4       │ 9600               │ 9600             │ 0          │ 253                │
│ 5       │ 14400              │ 14400            │ 0          │ 254                │
│ 6       │ 28800              │ 28800            │ 0          │ 255                │
└─────────┴────────────────────┴──────────────────┴────────────┴────────────────────┘

See /tool/uartBaudFinder.js for baud rates available on other 51.
*/

#define Uart_TimerReloadValue    (uint8)253
#define Uart_BuffEndByte         (uint8)'\n'
#define Uart_BuffSize            25

#define Uart_ReceiveByteEnabled  0
#define Uart_ReceiveBuffEnabled  1

void uartInit();
void uartSendBuff(const uint8 *buff, uint32 len);
void uartSendByte(uint8 byte);

#if Uart_ReceiveByteEnabled
extern void uartRecieveByte(uint8 byte);
#endif /* Uart_ReceiveByteEnabled */

#if Uart_ReceiveBuffEnabled
extern void uartReceiveBuff(const uint8 *buff, uint32 len);
#endif /* Uart_ReceiveBuffEnabled */

#endif /* _lib_uart */