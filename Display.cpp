#include "Display.h"

Display::Display(WORD DataIn, WORD Clk, WORD Cs)
{
	_pLedControl = new LedControl(DataIn,
		Clk,
		Cs,
		1//we have only one display
	);


	//The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
	_pLedControl->shutdown(0, false);
	/* Set the brightness to a medium values */
	_pLedControl->setIntensity(0, 8);
	/* and clear the display */
	_pLedControl->clearDisplay(0);
}

void Display::Write(DWORD Number)
{
	DWORD number;

	number = Number;

	for (BYTE i = 0; i < NUMBER_OF_CHARACTERS; i++)
	{
		_pLedControl->setDigit(DISPLAY_ADDRESS,
			i,
			number & ((1 << 4) - 1),
			false
		);

		number = number >> 4;
	}
}

void Display::Flush()
{

}
