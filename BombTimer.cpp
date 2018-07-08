#include "BombTimer.h"

BombTimer* BombTimer::_instance = 0;

BombTimer* BombTimer::GetInstance()
{
	if (!_instance)
	{
		_instance = new BombTimer();
	}

	return _instance;
}

BombTimer::BombTimer()
	: Timer()
{
	_pBombTime = new BombTime();
}

BombTime* BombTimer::GetBombTime()
{
	return _pBombTime;
}

void BombTimer::TimerEvent()
{
	//every 32 miliseconds
	_timerTicks++;
	_pUpTime->AddMiliSeconds(1);
	_pBombTime->AddMiliSeconds(-1);
}

ISR(TIMER0_COMPA_vect) { //timer0 interrupt 2kHz toggles pin 8
						 //generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
	BombTimer::GetInstance()->TimerEvent();
}