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
		for (int i = 0; (i < 15) && !error; i++)
		{
			wormWalking[i] = al_load_bitmap(filename.c_str());
			if (wormWalking[i] != NULL)
			{
				filename.erase(filename.length()-strlen(".png"), (size_t)1);
				filename.push_back(i + '2');	//cambia el nombre al del siguiente archivo
			}
			else
			{
				err.type = BITMAP_ERR;
				err.detail = "Error al cargar bitmap de worm";
			}
		}
		filename = "wjump-F1.png";
		for (int i = 0; (i < 10) && !error; i++)
		{
			wormJumping[i] = al_load_bitmap(filename.c_str());
			if (wormJumping[i] != NULL)
			{
				filename.erase(filename.length()-strlen(".png"), (size_t)1);
				filename.push_back(i + '2');
			}
			else
			{
				err.type = BITMAP_ERR;
				err.detail = "Error al cargar bitmap de worm";
			}
		}
		scenario = al_load_bitmap("scenario.png");
		if ((scenario != NULL) && !error)
		{
			display = al_create_display(al_get_bitmap_width(scenario),al_get_bitmap_height(scenario));
			if (display == NULL)
			{
				err.type = DISPLAY_ERR;
				err.detail = "Error al crear display";
			}
		}
		else
		{
			err.type = BITMAP_ERR;
			err.detail = "Error al cargar el bitmap del escenario";
		}
	}
	else
	{
		err.type = IM_ADDON_ERR;
		err.detail = "Error al inicializar el Image Addon";
	}
}

void graphics::draw()
{

}
