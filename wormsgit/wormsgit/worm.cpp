#include "worm.h"
#include <cstdlib>

#define FLOOR_Y 616
#define X_MAX 1212
#define X_MIN 701

worm::worm(double x, double y)
{
	frameCount = 0;
	pos.x = x;
	pos.y = y;
	/*
	pos.x = (rand()%(X_MAX-X_MIN)) + X_MIN;
	pos.y = FLOOR_Y;
	*/
}

posType worm::getPos()
{
	return pos;
}

unsigned int worm::getFrameCount()
{
	return frameCount;
}

bool worm::lookingRight()
{
	return lookingRight;
}

void worm::update(eventId key)
{
	if (key == moveKeys.right)
	{
		frameCount < 50 ? frameCount++ : frameCount = 0;

	}
	else if (key == moveKeys.left)
	{

	}
	else(key == moveKeys.up)
	{

	}
}