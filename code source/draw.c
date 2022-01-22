#include "prototype.h"

void draw(void)
{
	//couleur du fond
	if(SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255) != 0)
	{
		SDL_Log("IMPOSSIBLE DE METTRE EN NOIR FOND ECRAN : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//application de la couleur puis nettoyage du reste
	SDL_RenderClear(getRenderer());

	if(SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255) != 0)
	{
		SDL_Log("IMPOSSIBLE DE METTRE EN NOIR FOND ECRAN : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//tout les draw utile
	if(isActiveGame())
	{
		drawGame();
	}
	if(isActiveMainMenu())
	{
		drawMainMenu();
	}
	if(isActiveOption())
	{
		drawOption();
	}
	if(isActiveSelectDifficulty())
	{
		drawSelectDifficulty();
	}
	
	drawTrainer();

	//affichage des draw
	SDL_RenderPresent(getRenderer());
	
	//on soulage le processeur
	SDL_Delay(1);

}

void drawLine(int *x1, int *y1, int *x2, int *y2, SDL_Color *couleur)
{
	setRenderColor(couleur);

	if(SDL_RenderDrawLine(getRenderer(), *x1, *y1, *x2, *y2) != 0)
	{
		SDL_Log("IMPOSSIBLE DE DRAW LINE  :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void drawPoint(int *x, int *y, SDL_Color *couleur)
{
	setRenderColor(couleur);

	if(SDL_RenderDrawPoint(getRenderer(), *x, *y) != 0)
	{
		SDL_Log("IMPOSSIBLE DE DRAW POINT :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void drawRect(SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur)
{
	setRenderColor(couleur);

	if(*fill == SDL_TRUE)
	{
		SDL_RenderFillRect(getRenderer(), r);
	}
	else
	{
		SDL_RenderDrawRect(getRenderer(), r);
	}
}

void drawTexture(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src)
{
	if(SDL_RenderCopy(getRenderer(), texture, src, dst) != 0)
	{
		SDL_Log("IMPOSSIBLE D'AFFICHER LA TEXTURE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void drawTextureEx(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src, int angle)
{
	if(SDL_RenderCopyEx(getRenderer(), texture, src, dst, angle, NULL, SDL_FALSE) != 0)
	{
		SDL_Log("IMPOSSIBLE D'AFFICHER LA TEXTUREEX :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void setRenderColor(SDL_Color *couleur)
{
	if(SDL_SetRenderDrawColor(getRenderer(),couleur->r, couleur->g, couleur->b, couleur->a) != 0)
	{
		SDL_Log("IMPOSSIBLE DE METTRE LA COULEUR :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}
}
