#pragma once
#include <allegro5/allegro.h>
#include <iostream>

using namespace std;
typedef enum { NO_EVENTID, KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_D, KEY_W, KEY_A }eventId;
typedef enum { NO_EVENT, POSSIBLE_WORM_MOVE, POSSIBLE_WORM_STOP, REFRESH, CLOSE_DISPLAY }eventNum;

typedef struct
{
	eventNum num;
	eventId id;	//se usa para las teclas
}eventType;

typedef enum { NO_ERROR, TIMER_ERR, QUEUE_ERR , KEYBOARD_ERR, }errType;

typedef struct
{
	errType type;
	string detail;
}eventError;

class eventGenerator
{
public:
	eventGenerator();
	bool quit();
	bool eventPresent();
	eventType getEvent();
	void destroy();

private:
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT ev;
	bool quit;
	eventError err;


};

