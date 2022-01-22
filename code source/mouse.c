#include "prototype.h"

Mouse mouse;

void initMouse(void)
{
	getMousePos();
	mouse.rightButton = SDL_FALSE;
	mouse.leftButton = SDL_FALSE;
	mouse.oldRightButton = SDL_FALSE;
	mouse.oldLeftButton = SDL_FALSE;
}

void getMousePos(void)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
}

void actualiseRightButton(SDL_bool newActualisation)
{
	mouse.oldRightButton = mouse.rightButton;
	mouse.rightButton = newActualisation;
}

void actualiseLeftButton(SDL_bool newActualisation)
{
	mouse.oldLeftButton = mouse.leftButton;
	mouse.leftButton = newActualisation;
}

void actualiseOldLeftButton(void)
{
	mouse.oldLeftButton = mouse.leftButton;
}

void actualiseOldRightButton(void)
{
	mouse.oldRightButton = mouse.rightButton;
}

SDL_bool getStateOfRightButton(void)
{
	return mouse.rightButton;
}

SDL_bool getStateOfOldRightButton(void)
{
	return mouse.oldRightButton;
}

SDL_bool getStateOfLeftButton(void)
{
	return mouse.leftButton;
}

SDL_bool getStateOfOldLeftButton(void)
{
	return mouse.oldLeftButton;
}

int getMouseX(void)
{
	return mouse.x;
}

int getMouseY(void)
{
	return mouse.y;
}

