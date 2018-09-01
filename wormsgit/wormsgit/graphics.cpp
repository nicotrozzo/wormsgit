#include "graphics.h"
#include <iostream>

using namespace std;

graphics::graphics()
{
	bool error = false;
	string filename = "wwalk-F1";
	for (int i = 0; (i < 15) && !error; i++)
	{
		wormWalking[i] = al_load_bitmap(filename.c_str());	
		if (wormWalking[i] != NULL)
		{
			filename.erase(filename.length(), (size_t)1);
			filename.push_back(i + '2');	//cambia el nombre al del siguiente archivo
		}
		else
		{
			err.type = BITMAP_ERR;
			err.detail = "Error al cargar bitmap de worm";
		}
	}
	filename = "wjump-F1";
	for (int i = 0; (i < 10) && !error; i++)
	{
		wormJumping[i] = al_load_bitmap(filename.c_str());
		if (wormJumping[i] != NULL)
		{
			filename.erase(filename.length(), (size_t)1);
			filename.push_back(i + '2');
		}
		else
		{
			err.type = BITMAP_ERR;
			err.detail = "Error al cargar bitmap de worm";
		}
	}
}


