#include "BombTime.h"

BombTime::BombTime()
	: BombTime(1)
{

}

BombTime::BombTime(DWORD Rate)
	: BombTime(1 * 60 * 60, Rate)
{
}

BombTime::BombTime(DWORD Seconds, DWORD Rate)
{
	SetTime(Seconds);
	_increaseRate = Rate;
}

void BombTime::AddMiliSeconds(DWORD MiliSeconds)
{
	if (_miliSeconds < 60000
		&& ((int)_miliSeconds < (int)(MiliSeconds * _increaseRate)))
	{
		_miliSeconds = 0;
	}
	else
	{
		_miliSeconds += MiliSeconds * _increaseRate;
	}

}

void BombTime::Stop()
{
	_increaseRate = 0;
}

void BombTime::IncreaseRate(DWORD IncrementValue)
{
	_increaseRate += IncrementValue;
}