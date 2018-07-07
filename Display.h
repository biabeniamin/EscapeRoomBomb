#include "Types.h"
#include "LedControl.h"
#include "Time.h"

#define NUMBER_OF_CHARACTERS 8
#define DISPLAY_ADDRESS 0

class Display
{
public:
	Display(WORD, WORD, WORD);

	void Write(DWORD);
	void WriteInDecimal(DWORD);
	void Write(Time*);
	void Flush();

private:
	DWORD _number;

	LedControl *_pLedControl;
};