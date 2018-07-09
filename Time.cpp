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

DWORD Time::GetTotalSeconds()
{
	return (_miliSeconds / (100ul));
}

DWORD Time::GetTotalMiliSeconds()
{
	return (_miliSeconds);
}

void Time::AddMiliSeconds(DWORD MiliSeconds)
{
	_miliSeconds += MiliSeconds;
}

void Time::SetTime(DWORD Seconds)
{
	_miliSeconds = Seconds * 100;
}