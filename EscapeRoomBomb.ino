#include "Display.h"

Display display(12, 11, 10);

void setup() {
  Serial.begin(9600);

}

void loop() {
  Time *t = new Time(3900);
  display.Write(t);
  //display.WriteInDecimal(1234567);

}
