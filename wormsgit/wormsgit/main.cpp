#include <iostream>
#include <cstdlib>
#include <ctime>
#include "eventGenerator.h"
#include "worm.h"
#include "graphics.h"

void dispatch();

using namespace std;

int main(void)
{
	if (al_init())	//inicializa allegro en el main porque lo usan dos clases
	{
		srand(time(NULL));
		graphics graph;
		if (graph.error() == NO_ERROR)
		{
			eventGenerator ev(graph.getDisplay());	//le envia un puntero al display para que reciba los eventos
			if (ev.getError() == NO_ERROR)
			{
				worm ws[2];
				while (!ev.quit())
				{
					if (ev.hayEvento())
					{
						dispatch(ev.getEvent());
					}
				}
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