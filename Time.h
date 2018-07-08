#pragma once

#include "Types.h"
#include <Arduino.h>
#include "ITime.h"

class test
	: public ITime
{
public:

	BYTE GetHours()
	{
		return 1;
	}
	BYTE GetMinutes() {
		return 2;
	}
	BYTE GetSeconds() {
		return 3;
	}
	BYTE GetMiliSeconds() {
		return 4;
	}


};

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