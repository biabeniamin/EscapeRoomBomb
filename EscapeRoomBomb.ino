#include "Display.h"
#include "BombTimer.h"
#include "Keyboard.h"
#include "BombTime.h"

#define ALARM_PIN 5

#define PIN_ERASE_INTERVAL 1000

char rows[] = {9, 13, 11, 10};
char cols[] = {7, 8, 6};

void KeyPressed(BYTE key);

Keyboard keyboard(rows,
                  cols,
                  &KeyPressed);

Display display(A0, A2, A1);
BombTimer *bombTimer;

BYTE insertedKeys[4];
BYTE correctPin[] = {9, 9, 9, 9};
BYTE insertedKeysCount = 0;

BYTE initialTime[8];
BYTE initialTimeCount = 0;
BYTE setupMode = 1;

DWORD lastKeyPress;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(ALARM_PIN, HIGH);
  bombTimer = new BombTimer();
  bombTimer->SetTimer();


  keyboard.Start();
  bombTimer->TurnOn();

  display.Write(0xFFFFFFFF);

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
      digitalWrite(ALARM_PIN, LOW);
      bombTimer->Delay(2000);
      Serial.println("make LOW");
      digitalWrite(ALARM_PIN, HIGH);

      //infinite loop
      while (1);
    }


  }
  //display.WriteInDecimal(1234567);

}

void SetupMode(DWORD Key)
{
  Serial.print("Setup ");
  Serial.println(Key);
  DWORD number;

  number = 0;
  if (1 == setupMode)
  {
    initialTime[initialTimeCount++] = Key;
    for (int i = 0; i < initialTimeCount; i++)
    {
      number *= 10;
      number += initialTime[i];
    }

    if (4 < initialTimeCount)
    {
      DWORD seconds;

      seconds = 0;

      seconds = initialTime[3] * 10 + initialTime[4];
      seconds += (initialTime[1] * 10 + initialTime[2]) * 60;
      seconds += (initialTime[0]) * 60 * 60;

      bombTimer->GetBombTime()->SetTime(seconds);
      setupMode = 2;
      insertedKeysCount = 0;
      number = 9999;
      Serial.println("End setup 1");
    }
  }
  else if (2 == setupMode)
  {
    correctPin[insertedKeysCount++] = Key;
    for (int i = 0; i < 4; i++)
    {
      number *= 10;
      number += correctPin[i];

      Serial.print("correct pin ");
      Serial.println(correctPin[i]);
    }

    if (3 < insertedKeysCount)
    {
      setupMode = 0;
      insertedKeysCount = 0;
      bombTimer->StartBombTimer();
    }
  }

  Serial.println(number);
  display.WriteInDecimal(number);

}

void KeyPressed(BYTE Key)
{
  if (PIN_ERASE_INTERVAL < (bombTimer->GetUpTime()->GetTotalMiliSeconds() - lastKeyPress))
  {
    insertedKeysCount = 0;
  }

  lastKeyPress = bombTimer->GetUpTime()->GetTotalMiliSeconds();
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
      Serial.println("Increase rate!");
      bombTimer->GetBombTime()->IncreaseRate(3);
    }


    insertedKeysCount = 0;
  }


}



