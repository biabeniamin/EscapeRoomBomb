#include "Types.h"
#include <Arduino.h>

class Time
{
public:
	Time();
	Time(DWORD);
	
	BYTE GetHours();
	BYTE GetMinutes();
	BYTE GetSeconds();
	BYTE GetMiliSeconds();

private:
	DWORD _miliSeconds;
};