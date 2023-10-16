#include "CommandHandler.cpp"
#include "CommonData.cpp"

#ifndef _COMMUNICATION_
#define _COMMUNICATION_

namespace Communication
{
    //CMD CH('#', '<', '>');

    void Begin()
    {
        Serial.begin(115200);
        Serial.setTimeout(1);
        /*
        CH.PridejPrikaz(1, "a", false); // PC override zapnuto
        CH.PridejPrikaz(2, "b", false); // PC override vypnuto
        CH.PridejPrikaz(3, "x", true);
        CH.PridejPrikaz(4, "y", true);
        CH.PridejPrikaz(5, "z", true);
        */
    }

    void Update()
    {
        if (Serial.available() > 1)
        {
            int parameter = 0;
            bool noparameter = false;
            String datain = Serial.readStringUntil('#');
            String sparameter = "";
            datain.toLowerCase();
            if (datain.length() <= 1) return;
            int lpoz = datain.indexOf('<');
            int rpoz = datain.indexOf('>');
            if (((lpoz == -1) || (rpoz == -1)) || ((rpoz - lpoz) <= 1)) noparameter = true;
            else
            {
                sparameter = datain.substring(lpoz + 1, rpoz);
                parameter = sparameter.toInt();
            }
            if (datain.indexOf('a') != -1) CommonData::pcoverride = true;
            else if (datain.indexOf('b') != -1) CommonData::pcoverride = false;
            else if (!noparameter)
            {
                if (datain.indexOf('x') != -1) CommonData::artpoz[0] = parameter;
                else if (datain.indexOf('y') != -1) CommonData::artpoz[1] = parameter;
                else if (datain.indexOf('z') != -1) CommonData::artpoz[2] = parameter;
            }
            //
            /*
            switch (command)
            {
                case 1: CommonData::pcoverride = true; break;
                case 2: CommonData::pcoverride = false; break;
                case 3: CommonData::artpoz[0] = parameter; break;
                case 4: CommonData::artpoz[1] = parameter; break;
                case 5: CommonData::artpoz[2] = parameter; break;
                default: break;
            }
            */
            #ifdef DEBUG_COMMUNICATION
            Serial.println("DEBUG: Data recieved! Results:");
            Serial.println("parameter: " + String(parameter));
            Serial.println("artPoz[0]: " + String(CommonData::artpoz[0]));
            Serial.println("artPoz[1]: " + String(CommonData::artpoz[1]));
            Serial.println("artPoz[2]: " + String(CommonData::artpoz[2]));
            Serial.println("pcoverride: " + String(CommonData::pcoverride));
            Serial.println("...");
            #endif
        }
    }
}

#endif