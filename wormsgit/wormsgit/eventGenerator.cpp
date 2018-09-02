#include "eventGenerator.h"



eventGenerator::eventGenerator(ALLEGRO_DISPLAY *display,double fps)	//recibe puntero al display para recibir el evento de cierre
{
	queue = NULL;
	timer = NULL;
	close = false;
	ev.key = NO_EVENTID;
	ev.type = NO_EVENT;
	if (al_install_keyboard())
	{
		queue = al_create_event_queue();
		if (queue != NULL)
		{
			timer = al_create_timer(1.0 / fps);
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


void eventGenerator::startTimer()
{
	al_start_timer(timer);
}

bool eventGenerator::quit()
{
	return close;
}

bool eventGenerator::eventPresent()
{
	bool ret = false;
	if (al_get_next_event(queue, &alEvent))
	{
		ret = allegroToEvent();	//se fija si el evento de allegro tambien es un evento para el programa. ret es true si se usa el evento de allegro
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool eventGenerator::allegroToEvent()
{
	bool ret = false;
	switch (alEvent.type)
	{
		case ALLEGRO_EVENT_TIMER:
			ev.type = REFRESH;
			ret = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:	//si apretaron para cerrar el display, la proxima vez que le pregunten avisa que hay que salir
			ev.type = NO_EVENT;
			close = true;
			break;
		case ALLEGRO_KEY_DOWN:	//si apretaron una tecla, se fija que sea una de las que espera
			if( (ev.key = allegroKeyToEventId()) != NO_EVENTID )
			{
				ev.type = POSSIBLE_WORM_MOVE;
				ret = true;
			}
			break;
		case ALLEGRO_KEY_UP:	//si soltaron una tecla, se fija que sea una de las que espera
			if( (ev.key = allegroKeyToEventId()) != NO_EVENTID)
			{
				ev.type = POSSIBLE_WORM_STOP;
				ret = true;
			}
			break;
	}
	return ret;
}

/*Devuelve un evento interno en caso que sea una de las teclas esperadas*/
eventId eventGenerator::allegroKeyToEventId()
{
	eventId ret;
	switch (alEvent.keyboard.keycode)
	{
	case ALLEGRO_KEY_A:
		ret = KEY_A;
		break;
	case ALLEGRO_KEY_W:
		ret = KEY_W;
		break;
	case ALLEGRO_KEY_D:
		ret = KEY_D;
		break;
	case ALLEGRO_KEY_LEFT:
		ret = KEY_LEFT;
		break;
	case ALLEGRO_KEY_UP:
		ret = KEY_UP;
		break;
	case ALLEGRO_KEY_RIGHT:
		ret = KEY_RIGHT;
		break;
	default:
		ret = NO_EVENTID;
	}
	return ret;
}

eventType eventGenerator::getEvent()
{
	return ev;
}

eventError eventGenerator :: getError()
{
	return err;
}

void eventGenerator::destroy()
{
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
}