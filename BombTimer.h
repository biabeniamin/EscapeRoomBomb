#include "Arduino.h"
#include "BombTime.h"
#include "Timer.h"


class BombTimer
	: public Timer
{
public:
	static BombTimer* GetInstance();

	BombTime* GetBombTime();

	void TimerEvent();
private:
	BombTimer();
	static BombTimer *_instance;

	BombTime* _pBombTime;
};