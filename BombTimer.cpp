#include "BombTimer.h"

BombTimer* BombTimer::_instance = 0;

BombTimer* BombTimer::GetInstance()
{
	return _instance;
}

BombTimer::BombTimer()
	: Timer()
{
	_pBombTime = new BombTime();

	_isBombTimerOn = 1;

	_instance = this;
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

	if (1 == _isBombTimerOn)
	{
		_pBombTime->AddMiliSeconds(-1);
	}

	if (0 == _pBombTime->GetTotalSeconds())
	{
		_pBombTime->SetTime(0);
		StopBombTimer();

		
	}
}

void BombTimer::StartBombTimer()
{
	_isBombTimerOn = 1;
}

void BombTimer::StopBombTimer()
{
	_isBombTimerOn = 0;
}

ISR(TIMER0_COMPA_vect) { //timer0 interrupt 2kHz toggles pin 8
						 //generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
	BombTimer* pInstance;

	pInstance = 0;

	pInstance = BombTimer::GetInstance();
	if (pInstance)
	{
		pInstance->TimerEvent();
	}
	
}