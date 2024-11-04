
#ifndef _lib_pwm
#define _lib_pwm

#include "lib/type.h"

extern void (*pwmTrigger)(uint8 status);

void pwmStart(uint16 timerReloadValue, uint8 duty);
void pwmSetDuty(uint8 duty);
void pwmStop();

#endif /* _lib_pwm */