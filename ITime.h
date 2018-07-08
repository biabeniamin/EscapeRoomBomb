#pragma once

#include "Types.h"
#include <Arduino.h>

class ITime
{
public:
	virtual BYTE GetHours() = 0;
	virtual BYTE GetMinutes() = 0;
	virtual BYTE GetSeconds() = 0;
	virtual BYTE GetMiliSeconds() = 0;
};