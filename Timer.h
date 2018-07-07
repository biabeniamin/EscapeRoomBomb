#include "Arduino.h"
#include "Time.h"

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
private:
	Timer();
	static Timer *_instance;

	Time *_pUpTime;
	DWORD _timerTicks;


};