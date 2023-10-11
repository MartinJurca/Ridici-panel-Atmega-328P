#include <Arduino.h>
#include <Encoder.h>

#ifndef _INTERFACE_
#define _INTERFACE_
#define ENCODER_USE_INTERRUPTS

namespace Interface
{
    Encoder Enc(3, 2);
    const uint16_t switchpositions[6] = {168, 337, 508, 680, 851, 1023}; //z leva do prava
    const uint16_t buttonpositions[2] = {339, 1023}; //Č-Z
    const uint8_t switchpin = A5;
    const uint8_t buttonpin = A4;
    const uint8_t encbuttonpin = 4;
    const uint8_t flipswitchpin = 5;
    const uint8_t maxdelta = 2;
    const uint8_t tolerance = 20;
    int switchmem[2] = {0, 0};
    int buttonmem[2] = {0, 0};
    uint8_t selectedswitch = 0; // 0-nic, 123456
    uint8_t selectedbutton = 0; // 0-nic, 1-červená, 2-zelená

    void Begin()
    {
        pinMode(encbuttonpin, INPUT_PULLUP);
        pinMode(switchpin, INPUT);
        pinMode(buttonpin, INPUT);
        pinMode(flipswitchpin, INPUT_PULLUP);
        pinMode(encbuttonpin, INPUT_PULLUP);
    }

    void AnUpdate()
    {
        switchmem[1] = switchmem[0];
        switchmem[0] = analogRead(switchpin);
        buttonmem[1] = buttonmem[0];
        buttonmem[0] = analogRead(buttonpin);
        int switchdelta = abs(switchmem[0] - switchmem[1]);
        int buttondelta = abs(buttonmem[0] - buttonmem[1]);
        if (switchdelta <= maxdelta)
        {
            if (switchmem[0] < 50)
            {
                selectedswitch = 0;
            }
            if ((switchmem[0] < (switchpositions[0] + tolerance)) && (switchmem[0] > (switchpositions[0] - tolerance)))
            {
                selectedswitch = 1;
            }
            if ((switchmem[0] < (switchpositions[1] + tolerance)) && (switchmem[0] > (switchpositions[1] - tolerance)))
            {
                selectedswitch = 2;
            }
            if ((switchmem[0] < (switchpositions[2] + tolerance)) && (switchmem[0] > (switchpositions[2] - tolerance)))
            {
                selectedswitch = 3;
            }
            if ((switchmem[0] < (switchpositions[3] + tolerance)) && (switchmem[0] > (switchpositions[3] - tolerance)))
            {
                selectedswitch = 4;
            }
            if ((switchmem[0] < (switchpositions[4] + tolerance)) && (switchmem[0] > (switchpositions[4] - tolerance)))
            {
                selectedswitch = 5;
            }
            if ((switchmem[0] < (switchpositions[5] + tolerance)) && (switchmem[0] > (switchpositions[5] - tolerance)))
            {
                selectedswitch = 6;
            }
        }
        if (buttondelta <= maxdelta)
        {
            if (buttonmem[0] < 50)
            {
                selectedbutton = 0;
            }
            if ((buttonmem[0] < (buttonpositions[0] + tolerance)) && (buttonmem[0] > (buttonpositions[0] - tolerance)))
            {
                selectedbutton = 1;
            }
            if ((buttonmem[0] < (buttonpositions[1] + tolerance)) && (buttonmem[0] > (buttonpositions[1] - tolerance)))
            {
                selectedbutton = 2;
            }
        }
    }

    bool GetEncButton()
    {
        if (digitalRead(encbuttonpin)) return false;
        else return true;
    }

    bool GetFlipSwitch()
    {
        if (digitalRead(flipswitchpin)) return false;
        else return true;
    }
}

#endif