#include "Keyboard.h"


char rows[] = {7, 2, 3, 5};
char cols[] = {6, 8, 4};

Keyboard keyboard(rows,
cols);

void setup() {
  

  keyboard.Start();

  Serial.begin(9600);


}

void loop() {
  

}
