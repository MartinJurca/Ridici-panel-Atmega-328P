#include <Arduino.h>
#include "Display.cpp"
#include "CommandHandler.cpp"
#include "Interface.cpp"

void setup()
{
  Serial.begin(115200);
  Display::Begin();
  Display::BlankMemory();
}
int cnt = 0;
void loop()
{
  int (*func)(int);
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
  delay(1);
}