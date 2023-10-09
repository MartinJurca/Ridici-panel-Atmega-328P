#include<Arduino.h>
#include <SPI.h>
#ifndef _DISPLAY_
#define _DISPLAY_
namespace Display
{
    void MaskDots();
    SPISettings AVR328P_SPIsettings(8000000, MSBFIRST, 3);
    //0123456789ABCDEFP-_
    const uint8_t digits[19] = {0b00000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001, 0b01001001, 0b01000001, 0b00011111, 0b00000001, 0b00011001, 0b00010001, 0b11000001, 0b01100011, 0b10000101, 0b01100001, 0b01110001, 0b00110001, 0b11111101, 0b11101111};
    uint8_t digitsmemory[4] = {0, 0, 0, 0};
    bool dotsmemory[4] = {false, false, false, false};
    const uint8_t regclkdelay = 10; //uS
    //
    void Begin()
    {
        pinMode(10, OUTPUT);
        digitalWrite(10, LOW);
        SPI.begin();
    }

    void ShiftOut(const uint8_t data)
    {
        SPI.beginTransaction(AVR328P_SPIsettings);
        digitalWrite(10, LOW);
        delayMicroseconds(regclkdelay);
        SPI.transfer(data);
        digitalWrite(10, HIGH);
        delayMicroseconds(regclkdelay);
        digitalWrite(10, LOW);
        SPI.endTransaction();
    }

    void Blank()
    {
        SPI.beginTransaction(AVR328P_SPIsettings);
        digitalWrite(10, LOW);
        delayMicroseconds(regclkdelay);
        for (uint8_t i = 0; i < 4; i++) SPI.transfer(0b11111111);
        digitalWrite(10, HIGH);
        delayMicroseconds(regclkdelay);
        digitalWrite(10, LOW);
        SPI.endTransaction();
    }

    void BlankMemory()
    {
        SPI.beginTransaction(AVR328P_SPIsettings);
        digitalWrite(10, LOW);
        delayMicroseconds(regclkdelay);
        for (uint8_t i = 0; i < 4; i++)
        {
            digitsmemory[i] = 0b11111111;
            dotsmemory[i] = false;
            SPI.transfer(0b11111111);
        }
        digitalWrite(10, HIGH);
        delayMicroseconds(regclkdelay);
        digitalWrite(10, LOW);
        SPI.endTransaction();
        MaskDots();
    }

    void ShiftOutDigitsMemory()
    {
        SPI.beginTransaction(AVR328P_SPIsettings);
        digitalWrite(10, LOW);
        delayMicroseconds(regclkdelay);
        for (int8_t i = 3; i >= 0; i--) SPI.transfer(digitsmemory[i]);
        digitalWrite(10, HIGH);
        delayMicroseconds(regclkdelay);
        digitalWrite(10, LOW);
        SPI.endTransaction();
    }

    void MaskDots()
    {
        const uint8_t dot = 0b11111110;
        const uint8_t nodot = 0b11111111;
        for (uint8_t i = 0; i < 4; i++)
        {
            if (dotsmemory[i]) digitsmemory[i] = digitsmemory[i] & dot;
            else digitsmemory[i] = digitsmemory[i] & nodot;
        }
    }

    void SetDots(const bool dot1, const bool dot2, const bool dot3, const bool dot4)
    {
        dotsmemory[0] = dot1;
        dotsmemory[0] = dot2;
        dotsmemory[0] = dot3;
        dotsmemory[0] = dot4;
    }

    void SetDot(const bool state, const uint8_t index)
    {
        if (index > 3) return;
        dotsmemory[index] = state;
    }

    uint8_t MapDigit(const char digit)
    {
        switch (digit)
        {
            case '0': return digits[0];
            case '1': return digits[1];
            case '2': return digits[2];
            case '3': return digits[3];
            case '4': return digits[4];
            case '5': return digits[5];
            case '6': return digits[6];
            case '7': return digits[7];
            case '8': return digits[8];
            case '9': return digits[9];
            case 'a': return digits[10];
            case 'b': return digits[11];
            case 'c': return digits[12];
            case 'd': return digits[13];
            case 'e': return digits[14];
            case 'f': return digits[15];
            case 'p': return digits[16];
            case 'A': return digits[10];
            case 'B': return digits[11];
            case 'C': return digits[12];
            case 'D': return digits[13];
            case 'E': return digits[14];
            case 'F': return digits[15];
            case 'P': return digits[16];
            case '-': return digits[17];
            case '_': return digits[18];
            default: return 0b11111111;
        }
    }

    void SetDigits (const char dig1, const char dig2, const char dig3, const char dig4)
    {
        uint8_t digit1 = MapDigit(dig1);
        uint8_t digit2 = MapDigit(dig2);
        uint8_t digit3 = MapDigit(dig3);
        uint8_t digit4 = MapDigit(dig4);
        if (digit1 != 0b11111111) digitsmemory[0] = digit1;
        if (digit2 != 0b11111111) digitsmemory[1] = digit2;
        if (digit3 != 0b11111111) digitsmemory[2] = digit3;
        if (digit4 != 0b11111111) digitsmemory[3] = digit4;
        /*
        switch (dig1)
        {
            case '0': digitsmemory[0] = digits[0]; break;
            case '1': digitsmemory[0] = digits[1]; break;
            case '2': digitsmemory[0] = digits[2]; break;
            case '3': digitsmemory[0] = digits[3]; break;
            case '4': digitsmemory[0] = digits[4]; break;
            case '5': digitsmemory[0] = digits[5]; break;
            case '6': digitsmemory[0] = digits[6]; break;
            case '7': digitsmemory[0] = digits[7]; break;
            case '8': digitsmemory[0] = digits[8]; break;
            case '9': digitsmemory[0] = digits[9]; break;
            case 'a': digitsmemory[0] = digits[10]; break;
            case 'b': digitsmemory[0] = digits[11]; break;
            case 'c': digitsmemory[0] = digits[12]; break;
            case 'd': digitsmemory[0] = digits[13]; break;
            case 'e': digitsmemory[0] = digits[14]; break;
            case 'f': digitsmemory[0] = digits[15]; break;
            case 'p': digitsmemory[0] = digits[16]; break;
            case 'A': digitsmemory[0] = digits[10]; break;
            case 'B': digitsmemory[0] = digits[11]; break;
            case 'C': digitsmemory[0] = digits[12]; break;
            case 'D': digitsmemory[0] = digits[13]; break;
            case 'E': digitsmemory[0] = digits[14]; break;
            case 'F': digitsmemory[0] = digits[15]; break;
            case 'P': digitsmemory[0] = digits[16]; break;
            case '-': digitsmemory[0] = digits[17]; break;
            case '_': digitsmemory[0] = digits[18]; break;
            default: break;
        }
        switch (dig2)
        {
            case '0': digitsmemory[1] = digits[0]; break;
            case '1': digitsmemory[1] = digits[1]; break;
            case '2': digitsmemory[1] = digits[2]; break;
            case '3': digitsmemory[1] = digits[3]; break;
            case '4': digitsmemory[1] = digits[4]; break;
            case '5': digitsmemory[1] = digits[5]; break;
            case '6': digitsmemory[1] = digits[6]; break;
            case '7': digitsmemory[1] = digits[7]; break;
            case '8': digitsmemory[1] = digits[8]; break;
            case '9': digitsmemory[1] = digits[9]; break;
            case 'a': digitsmemory[1] = digits[10]; break;
            case 'b': digitsmemory[1] = digits[11]; break;
            case 'c': digitsmemory[1] = digits[12]; break;
            case 'd': digitsmemory[1] = digits[13]; break;
            case 'e': digitsmemory[1] = digits[14]; break;
            case 'f': digitsmemory[1] = digits[15]; break;
            case 'p': digitsmemory[1] = digits[16]; break;
            case 'A': digitsmemory[1] = digits[10]; break;
            case 'B': digitsmemory[1] = digits[11]; break;
            case 'C': digitsmemory[1] = digits[12]; break;
            case 'D': digitsmemory[1] = digits[13]; break;
            case 'E': digitsmemory[1] = digits[14]; break;
            case 'F': digitsmemory[1] = digits[15]; break;
            case 'P': digitsmemory[1] = digits[16]; break;
            case '-': digitsmemory[1] = digits[17]; break;
            case '_': digitsmemory[1] = digits[18]; break;
            default: break;
        }
        switch (dig3)
        {
            case '0': digitsmemory[2] = digits[0]; break;
            case '1': digitsmemory[2] = digits[1]; break;
            case '2': digitsmemory[2] = digits[2]; break;
            case '3': digitsmemory[2] = digits[3]; break;
            case '4': digitsmemory[2] = digits[4]; break;
            case '5': digitsmemory[2] = digits[5]; break;
            case '6': digitsmemory[2] = digits[6]; break;
            case '7': digitsmemory[2] = digits[7]; break;
            case '8': digitsmemory[2] = digits[8]; break;
            case '9': digitsmemory[2] = digits[9]; break;
            case 'a': digitsmemory[2] = digits[10]; break;
            case 'b': digitsmemory[2] = digits[11]; break;
            case 'c': digitsmemory[2] = digits[12]; break;
            case 'd': digitsmemory[2] = digits[13]; break;
            case 'e': digitsmemory[2] = digits[14]; break;
            case 'f': digitsmemory[2] = digits[15]; break;
            case 'p': digitsmemory[2] = digits[16]; break;
            case 'A': digitsmemory[2] = digits[10]; break;
            case 'B': digitsmemory[2] = digits[11]; break;
            case 'C': digitsmemory[2] = digits[12]; break;
            case 'D': digitsmemory[2] = digits[13]; break;
            case 'E': digitsmemory[2] = digits[14]; break;
            case 'F': digitsmemory[2] = digits[15]; break;
            case 'P': digitsmemory[2] = digits[16]; break;
            case '-': digitsmemory[2] = digits[17]; break;
            case '_': digitsmemory[2] = digits[18]; break;
            default: break;
        }
        switch (dig4)
        {
            case '0': digitsmemory[3] = digits[0]; break;
            case '1': digitsmemory[3] = digits[1]; break;
            case '2': digitsmemory[3] = digits[2]; break;
            case '3': digitsmemory[3] = digits[3]; break;
            case '4': digitsmemory[3] = digits[4]; break;
            case '5': digitsmemory[3] = digits[5]; break;
            case '6': digitsmemory[3] = digits[6]; break;
            case '7': digitsmemory[3] = digits[7]; break;
            case '8': digitsmemory[3] = digits[8]; break;
            case '9': digitsmemory[3] = digits[9]; break;
            case 'a': digitsmemory[3] = digits[10]; break;
            case 'b': digitsmemory[3] = digits[11]; break;
            case 'c': digitsmemory[3] = digits[12]; break;
            case 'd': digitsmemory[3] = digits[13]; break;
            case 'e': digitsmemory[3] = digits[14]; break;
            case 'f': digitsmemory[3] = digits[15]; break;
            case 'p': digitsmemory[3] = digits[16]; break;
            case 'A': digitsmemory[3] = digits[10]; break;
            case 'B': digitsmemory[3] = digits[11]; break;
            case 'C': digitsmemory[3] = digits[12]; break;
            case 'D': digitsmemory[3] = digits[13]; break;
            case 'E': digitsmemory[3] = digits[14]; break;
            case 'F': digitsmemory[3] = digits[15]; break;
            case 'P': digitsmemory[3] = digits[16]; break;
            case '-': digitsmemory[3] = digits[17]; break;
            case '_': digitsmemory[3] = digits[18]; break;
            default: break;
        }
        */
    }

    void SetDigits(const char* parray)
    {
        uint8_t digit1 = MapDigit(parray[0]);
        uint8_t digit2 = MapDigit(parray[1]);
        uint8_t digit3 = MapDigit(parray[2]);
        uint8_t digit4 = MapDigit(parray[3]);
        if (digit1 != 0b11111111) digitsmemory[0] = digit1;
        if (digit2 != 0b11111111) digitsmemory[1] = digit2;
        if (digit3 != 0b11111111) digitsmemory[2] = digit3;
        if (digit4 != 0b11111111) digitsmemory[3] = digit4;
        /*
        for (int i = 0; i < 4; i++)
        {
            switch (parray[i])
            {
                case '0': digitsmemory[i] = digits[0]; break;
                case '1': digitsmemory[i] = digits[1]; break;
                case '2': digitsmemory[i] = digits[2]; break;
                case '3': digitsmemory[i] = digits[3]; break;
                case '4': digitsmemory[i] = digits[4]; break;
                case '5': digitsmemory[i] = digits[5]; break;
                case '6': digitsmemory[i] = digits[6]; break;
                case '7': digitsmemory[i] = digits[7]; break;
                case '8': digitsmemory[i] = digits[8]; break;
                case '9': digitsmemory[i] = digits[9]; break;
                case 'a': digitsmemory[i] = digits[10]; break;
                case 'b': digitsmemory[i] = digits[11]; break;
                case 'c': digitsmemory[i] = digits[12]; break;
                case 'd': digitsmemory[i] = digits[13]; break;
                case 'e': digitsmemory[i] = digits[14]; break;
                case 'f': digitsmemory[i] = digits[15]; break;
                case 'p': digitsmemory[i] = digits[16]; break;
                case 'A': digitsmemory[i] = digits[10]; break;
                case 'B': digitsmemory[i] = digits[11]; break;
                case 'C': digitsmemory[i] = digits[12]; break;
                case 'D': digitsmemory[i] = digits[13]; break;
                case 'E': digitsmemory[i] = digits[14]; break;
                case 'F': digitsmemory[i] = digits[15]; break;
                case 'P': digitsmemory[i] = digits[16]; break;
                case '-': digitsmemory[i] = digits[17]; break;
                case '_': digitsmemory[i] = digits[18]; break;
                default: break;
            }
        }
        */
    }

    void WriteInt(const int value, const uint8_t index, const uint8_t maxlenght = 4)
    {
        if (index > 4) return;
        if (maxlenght > 4) return;
        char map[4] = {'x', 'x', 'x', 'x'};
        String val = String(value);
        uint8_t lcnt = 0;
        for (uint8_t i = index; (i - index) < val.length(); i++)
        {
            if (i > 3) break;
            if (!(lcnt < maxlenght)) break;
            map[i] = val[i - index];
            lcnt++;
        }
        //
        SetDigits(map);
    }

    void WriteString(const String value, const uint8_t index, const uint8_t maxlenght = 4)
    {
        if (index > 4) return;
        if (maxlenght > 4) return;
        char map[4] = {'x', 'x', 'x', 'x'};
        uint8_t lcnt = 0;
        for (uint8_t i = index; (i - index) < value.length(); i++)
        {
            if (i > 3) break;
            if (!(lcnt < maxlenght)) break;
            map[i] = value[i - index];
            lcnt++;
        }
        //
        SetDigits(map);
    }
}
#endif