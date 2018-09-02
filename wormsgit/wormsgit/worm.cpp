#include "worm.h"
#include <cstdlib>


worm::worm(double xmin,double xmax, double floor, eventId left, eventId right, eventId up)
{
	frameCount = 0;
	xMin = xmin;
	xMax = xmax;
	yFloor = floor;
	pos.x = (rand() % (xmax - xmin)) + xmin;
	pos.y = floor;
	lookingRight = (bool)(rand() % 2);
	state = IDLE;
	moveKeys.left.key = left;
	moveKeys.left.pressed = false;
	moveKeys.right.key = right;
	moveKeys.right.pressed = false;
	moveKeys.up.key = up;
	moveKeys.up.pressed = false;
}

posType worm::getPos()
{
	return pos;
}

unsigned int worm::getFrameCount()
{
	return frameCount;
}

bool worm::isLookingRight()
{
	return lookingRight;
}

void worm::moveWorm(eventId key)
{
	switch (state)
	{
	case IDLE:
		if (key == moveKeys.up.key)
		{
			state = JUMP;
			jumpState = START_JUMPING;
		}
		else if((key == moveKeys.left.key) ||(key == moveKeys.right.key))
		{
			lookingRight = (key == moveKeys.right.key);	//true si apretaron para ir a la derecha, false sino
			state = MOVE;
			moveState = START_MOVING;
		}
		break;
	case MOVE:
		if ((key == moveKeys.left.key) || (key == moveKeys.right.key))
		{
			(key == moveKeys.right.key) ? move_fsm(RIGHT) : move_fsm(LEFT);
		}
		break;
	case JUMP:
		if (key == moveKeys.up.key)
		{
			jump_fsm(key);
		}
		break;
	}
}

void worm::stopWorm(eventId key)
{
	switch (state)
	{
	case MOVE:
		break;
	case JUMP:
		break;		//si esta en idle no hace nada con la tecla que soltaron
	}

}
/*Se llama cada vez que hay un evento de timer*/
void worm::update()
{
	frameCount++;
	switch (state)
	{
	case MOVE:
		move_update();
		break;
	case JUMP:
		jump_update();
		break;			//si esta en IDLE no hace nada con el evento de timer
	}

}

/*Se llama con true si apretaron tecla a la izquierda*/
void worm::move_update()
{
	switch (moveState)
	{
	case START_MOVING:
		if (frameCount == 5)
		{
			moveState = MOVING;
		}
		break;
	case MOVING:
		if( (frameCount == 50) || (frameCount == 36) || (frameCount == 22) )
		{
			int signo = (lookingRight ? 1 : -1);	//determina el signo del movimiento
			if( ((pos.x + signo * 9) > xMin) && ((pos.x + signo*9) < xMax) )
			{
				pos.x += signo * 9;
			}
			if (frameCount == 50)	//si termino el movimiento
			{
				moveState = START_MOVING;
				frameCount = 0;
			}
		}
		break;
	case STOP_MOVING:
		if ((frameCount == 50) || (frameCount == 36) || (frameCount == 22))
		{
			int signo = (lookingRight ? 1 : -1);	//determina el signo del movimiento
			if (((pos.x + signo * 9) > xMin) && ((pos.x + signo * 9) < xMax))
			{
				pos.x += signo * 9;
			}
			if (frameCount == 50)	//si termino el movimiento
			{
				state = IDLE;
				frameCount = 0;
			}
		}
		break;
	}
}

void worm::jump_update()
{
	switch (jumpState)
	{
	case START_JUMPING:
		if()
		break;
	case JUMPING:
		break;
	}
}