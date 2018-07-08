#pragma once

#include "Types.h"
#include <Arduino.h>
#include "ITime.h"

class Time
	: public ITime
{
public:
	Time();
	Time(DWORD);
	
	BYTE GetHours();
	BYTE GetMinutes();
	BYTE GetSeconds();
	BYTE GetMiliSeconds();

	void AddMiliSeconds(DWORD);

protected:
	DWORD _miliSeconds;
};