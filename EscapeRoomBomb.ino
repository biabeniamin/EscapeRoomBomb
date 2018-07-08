#include "Display.h"
#include "BombTimer.h"
#include "Keyboard.h"
#include "BombTime.h"

char rows[] = {7, 2, 3, 5};
char cols[] = {6, 8, 4};

Keyboard keyboard(rows,
cols);

Display display(12, 11, 10);
BombTimer *bombTimer;

void setup() {
  Serial.begin(9600);
  bombTimer = BombTimer::GetInstance();
  bombTimer->SetTimer();
  bombTimer->TurnOn();

  keyboard.Start();
}

void loop() {
  display.Write(bombTimer->GetBombTime());
  //display.WriteInDecimal(1234567);

}



