#include <Arduino.h>
#include <Encoder.h>
#include "Display.cpp"
#include "CommandHandler.cpp"

void setup()
{
  Serial.begin(115200);
  Display::Begin();
  Display::BlankMemory();
}
int cnt = 0;
void loop()
{
  Display::WriteString("PC" + String(cnt), 0, 4);
  Display::ShiftOutDigitsMemory();
  cnt++;
  delay(1);
}