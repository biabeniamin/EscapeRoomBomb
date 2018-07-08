#include "Arduino.h"
#include "Time.h"

#define TIMER_INHERITANCE


class Timer
{
public:
	static Timer* GetInstance();

	void SetTimer();

	void TurnOn();
	void TurnOff();
	bool IsTimerOn();

	void Delay(DWORD miliSeconds);

	void TimerEvent();

	DWORD Timer::GetTotalTimerTicks();
	Time* GetUpTime();

protected:
	Timer();
	DWORD _timerTicks;
	Time *_pUpTime;

private:
	static Timer *_instance;

	
	


};