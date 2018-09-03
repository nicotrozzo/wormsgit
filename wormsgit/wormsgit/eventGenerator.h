#pragma once
#include <allegro5/allegro.h>
#include <iostream>

using namespace std;

typedef enum { NO_EVENTID, KEY_RIGHT, KEY_UP, KEY_LEFT, KEY_D, KEY_W, KEY_A }eventId;
typedef enum { NO_EVENT, POSSIBLE_WORM_MOVE, POSSIBLE_WORM_STOP, REFRESH}eventNum;
typedef enum { NO_ERROR, TIMER_ERR, QUEUE_ERR, KEYBOARD_ERR, }evErrType;

typedef struct
{
	eventNum type;
	eventId key;	//se usa para las teclas
}eventType;

typedef struct
{
	evErrType type;
	string detail;
}eventError;

class eventGenerator
{
public:
	eventGenerator(ALLEGRO_DISPLAY* display,double);
	bool quit();
	bool eventPresent();
	eventType getEvent();
	void startTimer();
	void destroy();
	eventError getError();

private:
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT alEvent;
	bool close;
	eventError err;
	eventType ev;
	bool allegroToEvent();
	eventId allegroKeyToEventId();

};