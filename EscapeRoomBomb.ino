#include "Display.h"

Display display(12, 11, 10);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  display.Write(0xFEDCBA987);

}
