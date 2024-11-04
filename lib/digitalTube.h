
#ifndef _lib_digitalTube
#define _lib_digitalTube

#include <Atmel/REGX52.H>
#include "lib/type.h"

#define DigitalTube_DataPort      P0
#define DigitalTube_SelectPort_A  P2_2
#define DigitalTube_SelectPort_B  P2_3
#define DigitalTube_SelectPort_C  P2_4

#define DigitalTube_PoolSize           8
#define DigitalTube_CharHexMapEnabled  1

#define DigitalTube_C_1 (uint8)0x06
#define DigitalTube_C_2 (uint8)0x5b
#define DigitalTube_C_3 (uint8)0x4f
#define DigitalTube_C_4 (uint8)0x66
#define DigitalTube_C_5 (uint8)0x6d
#define DigitalTube_C_6 (uint8)0x7d
#define DigitalTube_C_7 (uint8)0x07
#define DigitalTube_C_8 (uint8)0x7f
#define DigitalTube_C_9 (uint8)0x6f
#define DigitalTube_C_0 (uint8)0x3f

#define DigitalTube_C_a (uint8)0x77
#define DigitalTube_C_b (uint8)0x7c
#define DigitalTube_C_c (uint8)0x39
#define DigitalTube_C_d (uint8)0x5e
#define DigitalTube_C_e (uint8)0x79
#define DigitalTube_C_f (uint8)0x71

#define DigitalTube_C_Dot  (uint8)0x80
#define DigitalTube_C_Null (uint8)0x00

#if DigitalTube_CharHexMapEnabled
extern code const uint8 digitalTubeCharMap[16];
#endif /* DigitalTube_CharHexMapEnabled */

extern uint8 digitalTubePool[DigitalTube_PoolSize];

void digitalTubeScanOutput();

#endif /* _lib_digitalTube */