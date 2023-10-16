//
//#define TEST
//#define DEBUG_ISR
#define DEBUG_COMMUNICATION
#define DEPLOY
//
#include <Arduino.h>
#include "Display.cpp"
#include "CommandHandler.cpp"
#include "Interface.cpp"
#pragma region TimerInterrupt
#define USE_TIMER_1     false
#define USE_TIMER_2     true
#define USE_TIMER_3     false
#define USE_TIMER_4     false
#define USE_TIMER_5     false
#if ( defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)  || \
        defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_MINI) ||    defined(ARDUINO_AVR_ETHERNET) || \
        defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT)   || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_PRO)      || \
        defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_FEATHER328P) || \
        defined(ARDUINO_AVR_METRO) || defined(ARDUINO_AVR_PROTRINKET5) || defined(ARDUINO_AVR_PROTRINKET3) || defined(ARDUINO_AVR_PROTRINKET5FTDI) || \
        defined(ARDUINO_AVR_PROTRINKET3FTDI) )
  #define USE_TIMER_1     true
  #warning Using Timer1
#else          
  #define USE_TIMER_3     true
  #warning Using Timer3
#endif
#include "TimerInterrupt.h"
#pragma endregion
#include "Communication.cpp"
#include "Pages.cpp"

void _TimerInterruptISR();

void setup()
{
  Communication::Begin();
  Display::Begin();
  Interface::Begin();
  ITimer2.init();
  ITimer2.attachInterruptInterval(50, _TimerInterruptISR);
}
int cnt = 0;
void loop()
{
  #ifdef DEPLOY
  switch (Interface::selectedswitch)
  {
    case 1: Pages::AxisMovement(); break;
    case 2: Pages::AxisMovement(); break;
    case 3: Pages::AxisMovement(); break;
    case 4: Pages::Operate(); break;
    default: Pages::Unselected(); break;
  }
  #endif
  #ifdef TEST
  Serial.print(String(Interface::GetEncButton()) + "\t");
  Serial.print(String(Interface::GetFlipSwitch()) + "\t");
  Serial.print(Interface::selectedbutton);
  Serial.print("\t");
  Serial.println(Interface::selectedswitch);
  String enc = String(Interface::Enc.read());
  int lnght = enc.length();
  switch (lnght)
  {
    case 1: Display::SetDigits('x', '#', '#', '#'); break;
    case 2: Display::SetDigits('x', 'x', '#', '#'); break;
    case 3: Display::SetDigits('x', 'x', 'x', '#'); break;
    default: break;
  }
  Display::WriteInt(Interface::Enc.read(), 0);
  delay(50);
  #endif
}

void _TimerInterruptISR()
{
  Interface::AnUpdate();
  Communication::Update();
  #ifdef DEBUG_ISR
  Serial.println("DEBUG: Timer ISR done. Results:");
  Serial.println("selectedswitch: " + String(Interface::selectedswitch));
  Serial.println("selectedbutton:" + String(Interface::selectedbutton));
  Serial.println("flipswitch:" + String(Interface::GetFlipSwitch()));
  Serial.println("EncButton: " + String(Interface::GetEncButton()));
  //Serial.println("EncVal: " + String(Interface::Enc.read()));
  Serial.println("time: " + String(millis()));
  Serial.println("...");
  #endif
}