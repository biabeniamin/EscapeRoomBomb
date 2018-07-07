#include "Time.h"

Time::Time()
	: Time(0)
{
	
}

Time::Time(DWORD Seconds)
{
	_miliSeconds = Seconds * 100;
}

BYTE Time::GetHours()
{
	return ((_miliSeconds / (100ul * 60 * 60)) % 100);
}

BYTE Time::GetMinutes()
{
	return (_miliSeconds / (100ul * 60)) % 60;
}

BYTE Time::GetSeconds()
{
	return (_miliSeconds / (100ul)) % 60;
}

BYTE Time::GetMiliSeconds()
{
	return (_miliSeconds) % 100;
}