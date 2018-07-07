#include "Display.h"
#include "Timer.h"

Display display(12, 11, 10);
Time *t = new Time(100);
Timer *timer;

void setup() {
  Serial.begin(9600);
  timer = Timer::GetInstance();
  timer->SetTimer();
  timer->TurnOn();
  
  pinMode(8, OUTPUT);
}

void loop() {
  t->AddMiliSeconds(-1);
  display.Write(timer->GetUpTime());
  //display.WriteInDecimal(1234567);

}



