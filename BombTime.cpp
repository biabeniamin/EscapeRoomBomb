#include "BombTime.h"

BombTime::BombTime()
	: BombTime(1)
{

}

BombTime::BombTime(float Rate)
	: BombTime(1 * 60 * 60, Rate)
{
}

BombTime::BombTime(DWORD Seconds, float Rate)
{
	_miliSeconds = Seconds * 100;
	_increaseRate = Rate;
}

void BombTime::AddMiliSeconds(DWORD MiliSeconds)
{
	_miliSeconds += MiliSeconds;
}

void BombTime::IncreaseRate(float IncrementValue)
{
	_increaseRate += IncrementValue;
}