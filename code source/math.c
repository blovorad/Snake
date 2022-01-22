#include "prototype.h"

//Fonction qui nous revoie une valeur absolue en ####INT####
int absolue(int *a, int *b)
{
	int c = *a - *b;
	if(c < 0)
	{
		c = -c;
	}

	return c;
}

//Fonction de collision
SDL_bool collide(SDL_Rect *a, SDL_Rect *b)
{
	return SDL_HasIntersection(a, b);
}