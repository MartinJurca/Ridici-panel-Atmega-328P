#include "CommandHandler.cpp"
#include "CommonData.cpp"

#ifndef _COMMUNICATION_
#define _COMMUNICATION_

namespace Communication
{
    CMD CH('#', '<', '>');

    void Begin()
    {
        Serial.begin(115200);
        Serial.setTimeout(1);
        CH.PridejPrikaz(1, "a", false); // PC override zapnuto
        CH.PridejPrikaz(2, "b", false); // PC override vypnuto
        CH.PridejPrikaz(3, "x", true);
        CH.PridejPrikaz(4, "y", true);
        CH.PridejPrikaz(5, "z", true);
    }

    void Update()
    {
        CH.Update();
        int command = 0, parameter = 0;
        if (CH.Next(command, parameter))
        {
            switch (command)
            {
                case 1: CommonData::pcoverride = true; break;
                case 2: CommonData::pcoverride = false; break;
                case 3: CommonData::artpoz[0] = parameter; break;
                case 4: CommonData::artpoz[1] = parameter; break;
                case 5: CommonData::artpoz[2] = parameter; break;
                default: break;
            }
        }
    }
}

#endif