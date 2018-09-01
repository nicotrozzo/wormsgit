#include <iostream>
#include <cstdlib>
#include <ctime>
#include "eventGenerator.h"
#include "worm.h"
#include "graphics.h"

#define FPS 50.0

void dispatch();

using namespace std;

int main(void)
{
	if (al_init())	//inicializa allegro en el main porque lo usan dos clases
	{
		srand(time(NULL));
		worm *ws[2];
		graphics graph;
		if (graph.error() == NO_ERROR)
		{
			eventGenerator ev(graph.getDisplayPointer(),FPS);	//le envia un puntero al display para que reciba los eventos
			if (ev.getError() == NO_ERROR)
			{
				worm w1,w2;
				ws[0] = &w1;
				ws[1] = &w2;
				ev.startTimer();
				while (!ev.quit())
				{
					if (ev.eventPresent())
					{
						dispatch(ev.getEvent());
					}
				}
				ev.destroy();
			}
			else
			{

			}
		}
		else
		{

		}
	}
	else
	{
		cout << "No se pudo inicializar allegro" << endl;
	}
}


void dispatch(eventType ev)
{
	switch (ev.num)
	{
	case POSSIBLE_WORM_MOVE:
		if ()

			break;
	case POSSIBLE_WORM_STOP:

		break;
	case CLOSE_DISPLAY:

		break;
	case REFRESH:

		break;
	}
}