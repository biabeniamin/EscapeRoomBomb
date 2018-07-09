#include "Arduino.h"
#include "BombTime.h"
#include "Timer.h"


class BombTimer
	: public Timer
{
public:
	BombTimer();
	static BombTimer* GetInstance();

	BombTime* GetBombTime();

	void TimerEvent();
	void StartBombTimer();
	void StopBombTimer();
private:
	static BombTimer *_instance;

	BYTE _isBombTimerOn;

	BombTime* _pBombTime;
};