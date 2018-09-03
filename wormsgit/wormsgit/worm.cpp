#include "worm.h"
#include <cstdlib>
#include <cmath>	

worm::worm(double xmin,double xmax, double floor, eventId left, eventId right, eventId up)
{
	frameCount = 0;
	xMin = xmin;
	xMax = xmax;
	yFloor = floor;
	pos.x = (rand() %  (int)(xmax - xmin)) + xmin;
	pos.y = floor;
	lookingRight = (bool)(rand() % 2);
	state = IDLE;
	moveKeys.left = left;
	moveKeys.right = right;
	moveKeys.up = up;
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
		if (key == moveKeys.up)
		{
			state = JUMP;
			jumpState = START_JUMPING;
		}
		else if((key == moveKeys.left) || (key == moveKeys.right))
		{
			lookingRight = (key == moveKeys.right);	//true si apretaron para ir a la derecha, false si apretaron a la izquierda
			state = MOVE;
			moveState = START_MOVING;
		}
		break;
	case MOVE:
		if( ((key == moveKeys.left) && !lookingRight) || ((key == moveKeys.right) && lookingRight))
		{
			if (moveState == STOP_MOVING)
			{
				moveState = MOVING;
			}
		}
		break;	//no hace nada si esta en estado de jump
	}
}

wormState worm::getState()
{
	return state;
}

void worm::stopWorm(eventId key)
{
	switch (state)
	{
	case MOVE:
		if ((lookingRight && (key == moveKeys.right)) || (!lookingRight && (key == moveKeys.left)))	//si soltaron la tecla que lo estaba moviendo
		{
			if (moveState == MOVING)
			{
				moveState = STOP_MOVING;
			}
			else if(moveState == START_MOVING)
			{
				state = IDLE;
			}
		}
		break;
	case JUMP:
		if (jumpState == START_JUMPING)	//solo le interesa que suelten la tecla si esta por empezar a saltar
		{
			state = IDLE;
		}
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
		if (frameCount == 8)
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
		if (frameCount == 8)
		{
			jumpState = JUMPING;
		}
		break;
	case JUMPING:
		if (frameCount < 2 * speed*sin(angle) / g)	//si todavia no termino el tiro oblicuo
		{
			int signo = (lookingRight ? 1 : -1);	//determina el signo del movimiento
			pos.y = yFloor - speed * sin(angle)*(frameCount - 8) + g / 2.0 * (frameCount - 8)*(frameCount - 8);	//formula de tiro oblicuo para la altura
			pos.x += signo * speed*cos(angle); //formula de tiro oblicuo para la posicion horizontal
		}
		else	//sino, termino el tiro
		{
			pos.y = yFloor;
			jumpState = LANDING;
			frameCount = 0;
		}
		break;
	case LANDING:
		if (frameCount == 6)
		{
			state = IDLE;
		}
		break;
	}
}

jmpState worm::getJmpState()
{
	return jumpState;
}