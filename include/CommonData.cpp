#include <Arduino.h>
#include "Timer.cpp"

#ifndef _COMMON_DATA_
#define _COMMON_DATA_

namespace CommonData
{
    bool pcoverride = false; // true = zapnuto, false = vypnuto
    int artpoz[3] = {0, 0, 0};
    // blikání tečky při záporné hodnotě osy
    TIMER TmrBlink(500);
    bool blinkenabled = false;
    bool blinkstate = false;
}

#endif