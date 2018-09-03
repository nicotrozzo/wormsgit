#include <iostream>
#include <cstdlib>
#include <ctime>
#include "eventGenerator.h"
#include "worm.h"
#include "graphics.h"

#define FPS 50.0
#define FLOOR_Y 616
#define X_MAX 1212
#define X_MIN 701
#define CANTWORMS 2

void dispatch(eventType ev, worm* worms[], unsigned int wormCount, graphics *graph);

using namespace std;



int main(void)
{
	if (al_init())	//inicializa allegro en el main porque lo usan dos clases
	{
		srand(time(NULL));
		worm *ws[CANTWORMS];
		graphics graph;
		if( (graph.getGraphError()).type == NO_GRAPH_ERR)
		{
			eventGenerator ev(graph.getDisplayPointer(),FPS);	//le envia un puntero al display para que reciba los eventos
			if( (ev.getError()).type == NO_ERROR)
			{
				worm w1(X_MIN,X_MAX,FLOOR_Y,KEY_A,KEY_D,KEY_W),w2(X_MIN, X_MAX, FLOOR_Y,KEY_LEFT,KEY_RIGHT,KEY_UP);	//el worm 1 se mueve con las letras y el 2 con las flechitas
				ws[0] = &w1;
				ws[1] = &w2;
				graph.setWpointer(ws);
				ev.startTimer();
				while (!ev.quit())
				{
					if (ev.eventPresent())
					{
						dispatch(ev.getEvent(),ws,CANTWORMS,&graph);
					}
				}
				ev.destroy();
				graph.destroy();
			}
			else
			{
				cout << ((ev.getError()).detail).c_str() << endl;
				getchar();
			}
		}
		else
		{
			cout << ((graph.getGraphError()).detail).c_str() << endl;
			getchar();
		}
	}
	else
	{
		cout << "No se pudo inicializar allegro" << endl;
	}
}


void dispatch(eventType ev,worm* worms[],unsigned int wormCount,graphics *graph)
{
	unsigned int i;
	switch (ev.type)
	{
	case POSSIBLE_WORM_MOVE:
		for (i = 0; i < wormCount; i++)
		{
			worms[i]->moveWorm(ev.key);
		}
		break;
	case POSSIBLE_WORM_STOP:
		for (i = 0; i < wormCount; i++)
		{
			worms[i]->stopWorm(ev.key);
		}
		break;
	case REFRESH:
		for (i = 0; i < wormCount; i++)
		{
			worms[i]->update();
		}
		graph->draw();
		break;
	}
}