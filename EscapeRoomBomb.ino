#include "Display.h"
#include "BombTimer.h"
#include "Keyboard.h"
#include "BombTime.h"

#define ALARM_PIN 9

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

BYTE initialTime[8];
BYTE initialTimeCount = 0;
BYTE setupMode = 1;

void setup() {
  Serial.begin(9600);
  pinMode(ALARM_PIN, OUTPUT);
  bombTimer = new BombTimer();
  bombTimer->SetTimer();


  keyboard.Start();
  bombTimer->TurnOn();
}

void loop() {
  if (!setupMode)
  {
    ITime* bombTime;

    bombTime = bombTimer->GetBombTime();
    display.Write(bombTime);

    if (0 == bombTime->GetTotalMiliSeconds())
    {
      display.Write(bombTime);

      Serial.println("make high");
      digitalWrite(ALARM_PIN, HIGH);
      bombTimer->Delay(2000);
      Serial.println("make LOW");
      digitalWrite(ALARM_PIN, LOW);

      //infinite loop
      while (1);
    }


  }
  //display.WriteInDecimal(1234567);

}

void SetupMode(DWORD Key)
{
  DWORD number;

  number = 0;

  initialTime[initialTimeCount++] = Key;
  for (int i = 0; i < initialTimeCount; i++)
  {
    number *= 10;
    number += initialTime[i];
  }

  display.WriteInDecimal(number);

  if (4 < initialTimeCount)
  {
    DWORD seconds;

    seconds = 0;

    seconds = initialTime[3] * 10 + initialTime[4];
    seconds += (initialTime[1] * 10 + initialTime[2]) * 60;
    seconds += (initialTime[0]) * 60 * 60;

    bombTimer->GetBombTime()->SetTime(seconds);
    bombTimer->StartBombTimer();
    setupMode = 0;
  }

}

void KeyPressed(BYTE Key)
{
  Serial.println(Key);
  if (setupMode)
  {
    if (11 == Key)
    {
      Key = 0;
    }

    SetupMode(Key);
    return;
  }

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
      bombTimer->StopBombTimer();
    }
    else
    {
      bombTimer->GetBombTime()->IncreaseRate(3);
    }


    insertedKeysCount = 0;
  }


}



