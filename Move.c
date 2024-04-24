#include <AT89X52.h>
#include "Move.h"
#include "Param.h"
extern delay_nus(unsigned int i);
extern delay_nms(unsigned int i);

void Forward(Uchar speedl, Uchar speedr)
{
	Uint a = 0, b = 0;
	a = 1500 + speedl;
	b = 1500 - speedr;
	Left_Engine = 1;
	delay_nus(a);
	Left_Engine = 0;
	Right_Engine = 1;
	delay_nus(b);
	Right_Engine = 0;
	delay_nms(15);
}

void turnRightSteps(Uchar r)
{
	while (r > 0)
	{
		Left_Engine = 1;
		delay_nus(1590);
		Left_Engine = 0;
		Right_Engine = 1;
		delay_nus(1590);
		Right_Engine = 0;
		delay_nms(20);
		r--;
	}
}

void turnLeftSteps(Uchar l)
{
	while (l > 0)
	{
		Left_Engine = 1;
		delay_nus(1410);
		Left_Engine = 0;
		Right_Engine = 1;
		delay_nus(1410);
		Right_Engine = 0;
		delay_nms(20);
		l--;
	}
}

void turnRight(void)
{
	turnRightSteps(TurnRightSteps);
}

void turnLeft(void)
{
	turnLeftSteps(TurnLeftSteps);
}

void turnBack(void)
{
	turnLeft();
	turnLeft();
}

void turnBackL(void)
{
	turnLeft();
	turnLeft();
}

void turnBackR(void)
{
	turnRight();
	turnRight();
}