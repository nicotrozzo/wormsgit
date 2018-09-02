#pragma once
#include "eventGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>	//para tener Pi

typedef enum {IDLE,MOVE,JUMP}wormState;
typedef enum {START_MOVING,MOVING,STOP_MOVING}movState;
typedef enum{START_JUMPING,JUMPING}jmpState;

typedef struct
{
	double x;
	double y;
}posType;

typedef struct
{
	eventId key;
	bool pressed;
}wKey;

typedef struct  //aca se cargaran las teclas con las que el worm hara cada movimiento
{
	wKey left;
	wKey up;
	wKey right;
}wormKeys;

class worm
{
public:
	worm(double xmin,double xmax,double floor,eventId left,eventId right,eventId up);
	posType getPos();
	wormState getState();
	unsigned int getFrameCount();
	bool isLookingRight();
	void moveWorm(eventId key);
	void stopWorm(eventId key);
	void update();
	void move_update();
private:
	wormKeys moveKeys;
	wormState state;	//este estado solo indica si esta quieto, caminando o saltando
	movState moveState;	//si esta caminando, indica en que estado del movimiento esta
	jmpState jumpState;	//si esta saltando, indica en que estado del salto esta
	posType pos;
	double xMin;
	double xMax;
	double yFloor;
	const double speed = 1.5;
	const double g = 0.24;
	const double angle = M_PI / 3.0;
	bool lookingRight;
	unsigned int frameCount;
	
};

