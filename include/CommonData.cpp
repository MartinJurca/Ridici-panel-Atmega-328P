#include <Arduino.h>

#ifndef _COMMON_DATA_
#define _COMMON_DATA_

namespace CommonData
{
    bool pcoverride = false; // true = zapnuto, false = vypnuto
    int artpoz[3] = {0, 0, 0};
}

#endif