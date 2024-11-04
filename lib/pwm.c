
#include <STDIO.H>
#include <STDLIB.H>
#include <Atmel/REGX52.H>
#include "lib/pwm.h"
#include "lib/uart.h"

void (*pwmTrigger)(uint8 status) = NULL;
uint16 pwmTimerReloadValue;
uint16 pwmUpReloadValue, pwmDownReloadValue;
uint8 pwmStatus;

void pwmStart(uint16 timerReloadValue, uint8 duty) {
    pwmTimerReloadValue = timerReloadValue;
    pwmStatus = 0;
    pwmSetDuty(duty);

    // 16bit timer, manual reload needed, timer 0
    TMOD &= 0xf0;
    TMOD |= 0x01;

    TL0 = 0xff;
    TH0 = 0xff;

    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}

void pwmSetDuty(uint8 duty) {
    pwmUpReloadValue = (uint16)((uint32)(0xffffu - pwmTimerReloadValue) * (100 - duty) / 100 + pwmTimerReloadValue);
    pwmDownReloadValue = (uint16)((uint32)(0xffffu - pwmTimerReloadValue) * duty / 100 + pwmTimerReloadValue);
}

void pwmStop() {
    pwmTrigger = NULL;
    TR0 = 0;
}

void pwmTimerInterrupt() interrupt 1 {
    uint16 v;
    if (!pwmTrigger) return;

    pwmStatus = !pwmStatus;
    v = pwmStatus ? pwmUpReloadValue : pwmDownReloadValue;

    if (v != 0xffffu)
        pwmTrigger(pwmStatus);
    
    // manual reload
    TL0 = v;
    TH0 = v >> 8;
}
