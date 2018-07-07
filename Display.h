#include "Types.h"
#include "LedControl.h"

#define NUMBER_OF_CHARACTERS 8
#define DISPLAY_ADDRESS 0

class Display
{
public:
	Display(WORD, WORD, WORD);

	void Write(DWORD);
	void Flush();

private:
	DWORD _number;

	LedControl *_pLedControl;
};