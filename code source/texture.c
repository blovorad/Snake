#include "prototype.h"

SDL_Texture *createTexture(char *chemin, SDL_Rect *rect)
{
	//Variable obligatoire pour créer une texture
	SDL_Texture *texture = NULL;
	SDL_Surface *surface = IMG_Load(chemin);

	//Controle si l'image a bien été charger dans la surface
	if(surface == NULL)
	{
		SDL_Log("IMPOSSIBLE DE LOAD LA TEXTURE DANS LA SURFACE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//fonction qui retourne la texture si elle est créer
	texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
	//plus besoin de la surface, FREE OBLIGATOIRE
	SDL_FreeSurface(surface);
	surface = NULL;

	//On regarde si pas d'erreur
	if(texture == NULL)
	{
		SDL_Log("IMPOSSIBLE DE CREATE TEXTURE POUR LA SURFACE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Si on lui a passer un rect, alors on donne ses dimensions, sinon ça veut dire qu'on s'en fout
	if(rect != NULL)
	{
		if(SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) != 0)
		{
			SDL_Log("IMPOSSIBLE DE PRENDRE DIMENSION TEXTURE :%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	//return de la texture que l'on a créer, on retourne l'adresse de cette texture en vrai !
	return texture;
}