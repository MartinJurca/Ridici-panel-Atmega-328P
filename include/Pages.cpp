#include <Arduino.h>
#include "Communication.cpp"
#include "CommonData.cpp"
#include "Interface.cpp"
#include "Display.cpp"
#include "Timer.cpp"

#ifndef _PAGES_
#define _PAGES_

namespace Pages
{
    void _ShowFloat(int value, const double step_size);
    TIMER TmrSendOperate(5000);
    const double xystepsize = 0.04;
    const double zstepsize = 0.00625;
    void AxisMovement()
    {
        #ifdef DEBUG
        Serial.println("DEBUG: Entered AxisMovement page\n...");
        #endif
        while ((Interface::selectedswitch >= 1) && (Interface::selectedswitch <= 3))
        {
            if (CommonData::pcoverride)
            {
                Display::SetDots(false, false, true, false);
                Display::SetDigits('P', 'C', '#', '#');
                return;
            }
            bool sendmotion = false;
            if (abs(Interface::Enc.read()) >= 4) sendmotion = true;
            switch (Interface::selectedswitch)
            {
                case 1:
                {
                    _ShowFloat(CommonData::artpoz[0], xystepsize);
                    if (sendmotion)
                    {
                        int motionval = (Interface::Enc.read()) / 4;
                        Interface::Enc.write(Interface::Enc.read() - motionval * 4);
                        if (Interface::GetFlipSwitch()) Serial.println(String("[xc]") + String("<") + String(motionval) + ">#");
                        else Serial.println(String("[xf]") + String("<") + String(motionval) + ">#");
                    }
                    if (Interface::selectedbutton == 2)
                    {
                        Serial.println("[xn]#");
                        Display::SetDots(true, true, true, true);
                        Display::MaskDots();
                        Display::ShiftOutDigitsMemory();
                        while (Interface::selectedbutton == 2) delay(1);
                    }
                }
                break;
                case 2:
                {
                    _ShowFloat(CommonData::artpoz[1], xystepsize);
                    if (sendmotion)
                    {
                        int motionval = (Interface::Enc.read()) / 4;
                        Interface::Enc.write(Interface::Enc.read() - motionval * 4);
                        if (Interface::GetFlipSwitch()) Serial.println(String("[yc]") + String("<") + String(motionval) + ">#");
                        else Serial.println(String("[yf]") + String("<") + String(motionval) + ">#");
                    }
                    if (Interface::selectedbutton == 2)
                    {
                        Serial.println("[yn]#");
                        Display::SetDots(true, true, true, true);
                        Display::MaskDots();
                        Display::ShiftOutDigitsMemory();
                        while (Interface::selectedbutton == 2) delay(1);
                    }
                }
                break;
                case 3:
                {
                    _ShowFloat(CommonData::artpoz[2], zstepsize);
                    if (sendmotion)
                    {
                        int motionval = (Interface::Enc.read()) / 4;
                        Interface::Enc.write(Interface::Enc.read() - motionval * 4);
                        if (Interface::GetFlipSwitch()) Serial.println(String("[zc]") + String("<") + String(motionval) + ">#");
                        else Serial.println(String("[zf]") + String("<") + String(motionval) + ">#");
                    }
                    if (Interface::selectedbutton == 2)
                    {
                        Serial.println("[zn]#");
                        Display::SetDots(true, true, true, true);
                        Display::MaskDots();
                        Display::ShiftOutDigitsMemory();
                        while (Interface::selectedbutton == 2) delay(1);
                    }
                }
                break;
            }
        }
    }

    void _ShowFloat(int value, const double step_size)
    {
        // tečka
        Display::SetDots(false, false, false, true);
        // první část
        double frstvaldbl = step_size * double(value);
        int frstval = abs(int(frstvaldbl));
        String showfrstval = String(frstval);
        switch (showfrstval.length())
        {
            case 0: Display::SetDigits('#', '#', '#', 'x'); break;
            case 1: Display::SetDigits('#', '#', showfrstval[0], 'x'); break;
            case 2: Display::SetDigits('#', showfrstval[0], showfrstval[1], 'x'); break;
            case 3: Display::SetDigits(showfrstval[0], showfrstval[1], showfrstval[2], 'x'); break;
            default: Display::SetDigits(showfrstval[0], showfrstval[1], showfrstval[2], 'x'); break;
        }
        // druhá část
        frstvaldbl -= double(int(step_size * double(value)));
        frstvaldbl *= 10.0;
        int scndval = abs(int(frstvaldbl));
        Display::WriteInt(scndval, 3, 1);
    }

    void Unselected()
    {
        #ifdef DEBUG
        Serial.println("DEBUG: Entered Unselected page\n...");
        #endif
        Display::SetDots(true, true, true, true);
        Display::SetDigits('8', '8', '8', '8');
    }

    void Operate()
    {
        #ifdef DEBUG
        Serial.println("DEBUG: Entered Operate page\n...");
        #endif
        while(Interface::selectedswitch == 4)
        {
            Display::SetDots(false, false, true, false);
            Display::SetDigits('0', 'P', '#', '#');
            if (TmrSendOperate.Update()) Serial.println("[operate]#");
        }
    }
}

#endif