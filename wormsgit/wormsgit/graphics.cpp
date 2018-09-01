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
		filename.erase(filename.length(), (size_t)1); 
		filename.push_back(i + '2');	//cambia el nombre al del siguiente archivo
	}
	filename = "wjump-F1";
	for (int i = 0; (i < 10) && !error; i++)
	{
		wormJumping[i] = al_load_bitmap(filename.c_str());
		filename.erase(filename.length(), (size_t)1);
		filename.push_back(i + '2');
	}
}


