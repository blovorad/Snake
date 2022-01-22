#include "prototype.h"

//CATALOGUE DES FONT
TTF_Font *font1;

void initFont1(void)
{
	font1 = TTF_OpenFont("source/fonts/fontMainMenu.ttf", 20);

	if(font1 == NULL)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER LA FONT :%s",TTF_GetError());
		exit(EXIT_FAILURE);
	}
}

TTF_Font *getFont1(void)
{
	return font1;
}

void cleanFont1(void)
{
	SDL_Log("CLEAN FONT1 EN COURS\n");
	if(font1 != NULL)
	{
		TTF_CloseFont(font1);
		font1 = NULL;
	}	
	SDL_Log("CLEAN FONT1 TERMINER\n");
}