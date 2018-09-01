#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>



class graphics
{
public:
	graphics();

private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP * wormWalking[15];
	ALLEGRO_BITMAP * wormJumping[10];
	errorType err;
};

