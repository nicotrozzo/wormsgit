#include "graphics.h"
#include <iostream>

using namespace std;

graphics::graphics()
{
	if (al_init_image_addon())
	{
		err.type = NO_GRAPH_ERR;
		bool error = false;
		/*Carga todos los bitmaps que va a usar*/
		string filename = "wwalk-F1.png";
		char number[3];
		size_t len = 1;
		display = al_create_display(1920,696);
		if(display != NULL)
		{
			for (int i = 0; (i < 15) && !error; i++)
			{
				wormWalking[i] = al_load_bitmap(filename.c_str());
				if (wormWalking[i] != NULL)
				{
					sprintf(number, "%d", i+2);
					filename.replace(strlen("wwalk_F"), (size_t)len, number);  //cambia el nombre al del siguiente archivo	
					if (i == 8)
					{
						len++;
					}
				}
				else
				{
					error = true;
					err.type = BITMAP_ERR;
					err.detail = "Error al cargar bitmap de worm caminando";
				}
			}
			filename = "wjump-F1.png";
			for (int i = 0; (i < 10) && !error; i++)
			{
				wormJumping[i] = al_load_bitmap(filename.c_str());
				if (wormJumping[i] != NULL)
				{
					sprintf(number, "%d", i + 2);
					filename.replace(strlen("wjump_F"), (size_t)1, number);  //cambia el nombre al del siguiente archivo	
				}
				else
				{
					error = true;
					err.type = BITMAP_ERR;
					err.detail = "Error al cargar bitmap de worm saltando";
				}
			}
			if (!error)
			{
				scenario = al_load_bitmap("Scenario.png");
				if (scenario != NULL)
				{
					al_draw_bitmap(scenario, 0, 0, 0);
					err.type = NO_GRAPH_ERR;
				}
				else
				{
					destroy();	//borra todos los bitmaps cargados
					err.type = BITMAP_ERR;
					err.detail = "Error al cargar el bitmap del escenario";
				}
			}
		}
		else
		{
			err.type = DISPLAY_ERR;
			err.detail = "Error al crear display";		
		}
	}
	else
	{
		err.type = IM_ADDON_ERR;
		err.detail = "Error al inicializar el Image Addon";
	}
}

void graphics::setWpointer(worm *wPointer[])
{
	ws[0] = wPointer[0];
	ws[1] = wPointer[1];
}
ALLEGRO_DISPLAY * graphics::getDisplayPointer(void)
{
	return display;
}

void graphics::draw()
{
	int i;
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(scenario, 0, 0, 0);
	for (i = 0; i < 2; i++)
	{
		if (ws[i]->getState() == MOVING)
		{
			if (ws[i]->isLookingRight())
			{
				al_draw_bitmap(wormWalking[getNumberOfMovingBitmap(ws[i]->getFrameCount())],(ws[i]->getPos()).x, (ws[i]->getPos()).y,ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(wormWalking[getNumberOfMovingBitmap(ws[i]->getFrameCount())], (ws[i]->getPos()).x, (ws[i]->getPos()).y,0);
			}
		}
		else if (ws[i]->getState() == JUMP)
		{
			if (ws[i]->isLookingRight())
			{
				al_draw_bitmap(wormJumping[getNumberOfJumpingBitmap(ws[i]->getFrameCount(),ws[i]->getJmpState())], (ws[i]->getPos()).x, (ws[i]->getPos()).y, ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(wormJumping[getNumberOfJumpingBitmap(ws[i]->getFrameCount(),ws[i]->getJmpState())], (ws[i]->getPos()).x, (ws[i]->getPos()).y, 0);
			}
		}
		else if (ws[i]->getState() == IDLE)
		{
			if (ws[i]->isLookingRight())
			{
				al_draw_bitmap(wormWalking[0], (ws[i]->getPos()).x, (ws[i]->getPos()).y, ALLEGRO_FLIP_HORIZONTAL);
			}
			else
			{
				al_draw_bitmap(wormWalking[0], (ws[i]->getPos()).x, (ws[i]->getPos()).y, 0);
			}
		}
	}
	al_flip_display();


}

unsigned int graphics::getNumberOfMovingBitmap(unsigned int frameCount)
{
	unsigned int ret;
	if (frameCount <= 5)
	{
		ret = 0;
	}
	else if (frameCount == 6)
	{
		ret = 1;
	}
	else if (frameCount == 7)
	{
		ret = 2;
	}
	else
	{
		frameCount -= 8;
		if (frameCount >= 14)	//pasa frameCount a la primera vuelta
		{
			frameCount -= 14;
			if (frameCount >= 14)
			{
				frameCount -= 14;
			}
		}
		if (frameCount == 13)
		{
			ret = 3;
		}
		else
		{
			ret = frameCount + 3;
		}
	}
	return ret;
}

unsigned int graphics::getNumberOfJumpingBitmap(unsigned int frameCount, jmpState state)
{
	unsigned int ret;
	if (state == JUMPING)
	{
		ret = 3;
	}
	else if (state == START_JUMPING)
	{
		if (frameCount <= 5)
		{
			ret = 0;
		}
		else if (frameCount == 6)
		{
			ret = 1;
		}
		else if (frameCount == 7)
		{
			ret = 2;
		}
	}
	else
	{
		ret = frameCount + 4;
	}
	return ret;
}

graphError graphics::getGraphError()
{
	return err;
}

void graphics::destroy()
{
	int i;
	if (display != NULL)
	{
		al_destroy_display(display);
	}
	for (i = 0; i < 15; i++)
	{
		if(wormWalking[i] != NULL)
			al_destroy_bitmap(wormWalking[i]);
	}
	for (i = 0; i < 10; i++)
	{
		if(wormJumping[i] != NULL)
			al_destroy_bitmap(wormJumping[i]);
	}
	if(scenario != NULL)
		al_destroy_bitmap(scenario);
}
