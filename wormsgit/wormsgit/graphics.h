#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "worm.h"

typedef enum{NO_GRAPH_ERR,BITMAP_ERR,IM_ADDON_ERR,DISPLAY_ERR}graphErrType;

typedef struct
{
	graphErrType type;
	string detail;
}graphError;

class graphics
{
public:
	graphics();
	void setWpointer(worm *wPointer[]);
	void draw();
	ALLEGRO_DISPLAY * getDisplayPointer();
	graphError getGraphError();
private:
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP * wormWalking[15];
	ALLEGRO_BITMAP * wormJumping[10];
	ALLEGRO_BITMAP * scenario;
	graphError err;
	worm *ws[2];
};

