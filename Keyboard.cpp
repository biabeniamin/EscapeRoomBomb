#include "Keyboard.h"

Keyboard* Keyboard::_instance = 0;

Keyboard::Keyboard(BYTE* PRows,
	BYTE* PCols,
	void(*Event)(BYTE))
{
	_pKeyPressedEvent = Event;

	for (int i = 0; i < ROWS; i++)
	{
		_pRows[i] = PRows[i];

		pinMode(_pRows[i], INPUT_PULLUP);
	}

	for (int i = 0; i < COLS; i++)
	{
		_pCols[i] = PCols[i];
		pinMode(_pCols[i], OUTPUT);
	}

	//stop interrupts
	cli();

	// set entire TCCR2A register to 0
	TCCR2A = 0;
	// same for TCCR2B
	TCCR2B = 0;
	//initialize counter value to 0
	TCNT2 = 0;
	// frequency will be 49.7Hz
	OCR2A = 156;
	// turn on CTC mode
	TCCR2A |= (1 << WGM21);
	// Set CS01 and CS00 bits for 64 prescaler
	TCCR2B |= (1 << CS22);
	TCCR2B |= (1 << CS20);

	Stop();

	//allow interrupts
	sei();

	_instance = this;
}

Keyboard* Keyboard::GetInstance()
{
	return _instance;
}

void Keyboard::Start()
{
	TIMSK2 |= (1 << OCIE2A);
}

void Keyboard::Stop()
{
	TIMSK2 &= 0xFF ^ (1 << OCIE2A);
}

BYTE Keyboard::GetKey(BYTE Row,
	BYTE Col)
{
	return (Row * 3) + (Col + 1);
}

void Keyboard::TimerEvent()
{
	BYTE wasKeyDetected;

	wasKeyDetected = 0;
	for (BYTE i = 0; i < COLS; i++)
	{
		digitalWrite(_pCols[i], LOW);
		for (BYTE j = 0; j < ROWS; j++)
		{
			if (!digitalRead(_pRows[j]))
			{
				BYTE key;
				
				wasKeyDetected = 1;

				key = GetKey(j,
					i);
				if (key == _lastKeyPressed)
				{
					continue;
				}

				_pKeyPressedEvent(key);

				_lastKeyPressed = key;
				
			}
		}
		digitalWrite(_pCols[i], HIGH);
	}

	if (!wasKeyDetected)
	{
		_lastKeyPressed = 0;
	}
}

ISR(TIMER2_COMPA_vect) { //timer0 interrupt 2kHz toggles pin 8
						 //generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
	Keyboard *pInstance;

	pInstance = Keyboard::GetInstance();
	if (!pInstance)
	{
		return;
	}

	pInstance->TimerEvent();
}