const baudRateLst = [
    600,
    1200,
    2400,
    4800,
    9600,
    14400,
    19200,
    28800,
    38400,
    57600,
    115200,
    100000,
    200000,
    230400,
    250000,
    460800,
    500000,
    921600,
    1000000,
    1500000,
    2000000,
    2500000,
    3000000,
    4000000,
    5000000,
    6000000,
    7500000,
    8000000,
    9000000,
    10000000
];

const mcuFreq = 11.0592e6;
/** double baud rate (SMOD) */
const baudRateDouble = false;
/** 12T or 6T */
const mcuMachineCycleMode = 12;
/** max abs(actualBaudRate - standardBaudRate) you accepted */
const maxInaccuracyAccepted = 18;
/** timer value bits */
const timerBits = 8;

let timerMax = Math.pow(2, timerBits);
let f = t => (baudRateDouble ? 2 : 1) / 32 * mcuFreq / mcuMachineCycleMode / (timerMax - t);
let res = {};

for (let t = 0; t < timerMax; t++) {
    let ab = f(t);
    for (let sb of baudRateLst) {
        let inaccuracy = Math.abs(ab - sb);
        if (inaccuracy > maxInaccuracyAccepted) continue;
        if (res[sb] && res[sb].Inaccuracy <= inaccuracy) continue;
        res[sb] = { "Standard Baud Rate": sb, "Actual Baud Rate": ab, "Inaccuracy": Math.abs(ab - sb), "Timer Reload Value": t };
    }
}

console.table(Object.values(res));