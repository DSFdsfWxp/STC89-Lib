
#include "lib/time.h"
#include "lib/digitalTube.h"

#if DigitalTube_CharHexMapEnabled

code const uint8 digitalTubeCharMap[] = {
    DigitalTube_C_0, DigitalTube_C_1, DigitalTube_C_2, DigitalTube_C_3,
    DigitalTube_C_4, DigitalTube_C_5, DigitalTube_C_6, DigitalTube_C_7,
    DigitalTube_C_8, DigitalTube_C_9, DigitalTube_C_a, DigitalTube_C_b,
    DigitalTube_C_c, DigitalTube_C_d, DigitalTube_C_e, DigitalTube_C_f
};

#endif /* DigitalTube_CharHexMapEnabled */

uint8 digitalTubePool[DigitalTube_PoolSize] = {0};

void digitalTubeScanOutput() {
    uint8 i;

    for (i=0; i<DigitalTube_PoolSize; i++) {
        // clear before we specify next tube
        // prevent shadow of last char appear in other positions
        DigitalTube_DataPort = DigitalTube_C_Null;

        DigitalTube_SelectPort_A = i & 1;
        DigitalTube_SelectPort_B = (i & 2) >> 1;
        DigitalTube_SelectPort_C = (i & 4) >> 2;

        DigitalTube_DataPort = digitalTubePool[i];
        delayMs(1);
    }
}