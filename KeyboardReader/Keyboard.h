#pragma once

#include <Arduino.h>
#include "Types.h"

#define ROWS 4
#define COLS 3

class Keyboard
{
public:
	Keyboard(BYTE*,
		BYTE*);

	static Keyboard* GetInstance();

	void Start();
	void Stop();

	void TimerEvent();

private:
	static Keyboard* _instance;
	BYTE _pRows[4];
	BYTE _pCols[4];
	BYTE _lastKeyPressed;

	BYTE GetKey(BYTE,
		BYTE);
	
};