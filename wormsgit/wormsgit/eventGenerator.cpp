#include "eventGenerator.h"

#define FPS 50.0

eventGenerator::eventGenerator(ALLEGRO_DISPLAY *display)	//recibe puntero al display para recibir el evento de cierre
{
	queue = NULL;
	timer = NULL;
	quit = false;
	if (al_install_keyboard())
	{
		queue = al_create_event_queue();
		if (queue != NULL)
		{
			timer = al_create_timer(1.0 / FPS);
			if (timer != 0)
			{
				err.type = NO_ERROR;
				al_register_event_source(queue, al_get_timer_event_source(timer));
				al_register_event_source(queue, al_get_keyboard_event_source());
				al_register_event_source(queue, al_get_display_event_source(display));
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
			err.detail = "Couldn't create event queue\n";
		}
	}
	else
	{
		err.type = KEYBOARD_ERR;
		err.detail = "Couldn't install keyboard\n";
	}
}

bool eventGenerator::quit()
{
	return quit;
}
