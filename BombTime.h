#pragma once

#include "Types.h"
#include "Time.h"
#include <Arduino.h>

class BombTime:
	public Time
{
public:
	BombTime();
	BombTime(DWORD);
	BombTime(DWORD, DWORD);

	void AddMiliSeconds(DWORD);

	void Stop();
	void IncreaseRate(DWORD);

private:
	DWORD _increaseRate;
};