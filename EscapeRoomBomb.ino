#include "Display.h"
#include "BombTimer.h"
#include "Keyboard.h"
#include "BombTime.h"

char rows[] = {7, 2, 3, 5};
char cols[] = {6, 8, 4};

void KeyPressed(BYTE key);

Keyboard keyboard(rows,
                  cols,
                  &KeyPressed);

Display display(12, 11, 10);
BombTimer *bombTimer;

BYTE insertedKeys[4];
BYTE correctPin[] = {1, 2, 3, 4};
BYTE insertedKeysCount = 0;

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

void KeyPressed(BYTE Key)
{
  Serial.println(Key);
  
  insertedKeys[insertedKeysCount++] = Key;
  if (4 == insertedKeysCount)
  {
    BYTE isPinCorrect = 1;

    for (int i = 0; i < 4; i++)
    {
      if (correctPin[i] != insertedKeys[i])
      {
        isPinCorrect = 0;
      }
    }

    if (isPinCorrect)
    {
      Serial.println("Done!");
      bombTimer->GetBombTime()->Stop();
    }
    else
    {
      bombTimer->GetBombTime()->IncreaseRate(3);
    }


    insertedKeysCount = 0;
  }


}



