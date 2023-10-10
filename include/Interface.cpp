#include <Arduino.h>
#include <Encoder.h>

#ifndef _INTERFACE_
#define _INTERFACE_
#define ENCODER_USE_INTERRUPTS

namespace Interface
{
    Encoder Enc(3, 2);
}

#endif