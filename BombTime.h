#pragma once

#include "Types.h"
#include "Time.h"
#include <Arduino.h>

class BombTime:
	public Time
{
public:
	BombTime();
	BombTime(float);
	BombTime(DWORD,float);

	void AddMiliSeconds(DWORD);
	void IncreaseRate(float);

private:
	float _increaseRate;
};