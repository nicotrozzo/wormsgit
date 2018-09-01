#pragma once
#include "eventGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>	//para tener Pi

typedef enum {}wormState;

typedef struct
{
	unsigned int x;
	unsigned int y;
}posType;

typedef struct  //aca se cargaran las teclas con las que el worm hara cada movimiento
{
	eventId left;
	eventId up;
	eventId right;
}wormKeys;

class worm
{
public:
	worm();
	posType getPos();
	unsigned int getFrameCount();
	bool lookingRight();
	void update(eventType);

private:
	wormKeys moveKeys;
	wormState state;
	posType pos;
	const double speed = 1.5;
	const double g = 0.24;
	const double angle = M_PI / 3.0;
	bool lookingRight;
	unsigned int frameCount;
};

