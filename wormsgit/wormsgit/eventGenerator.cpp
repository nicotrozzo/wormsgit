#include "eventGenerator.h"

#define FPS 50.0

eventGenerator::eventGenerator()
{
	queue = NULL;
	timer = NULL;
	quit = false;
	queue = al_create_event_queue();
	if (queue != NULL)
	{
		timer = al_create_timer(1.0 / FPS);
		if (timer != 0)
		{
			err.type = NO_ERROR;
		}
		else
		{
			al_destroy_event_queue(queue);
			err.type = TIMER_ERR;
			err.detail = "Couldn't create timer\n";
		}
	}
	else
	{
		err.type = QUEUE_ERR;
		err.detail = "Couldn't create event queue"
	}
}

bool eventGenerator::quit()
{
	return quit;
}
