#include "prototype.h"

Point liste_trainer[DIM_TRAINER];
int nbTrainer;

void initTrainer(void)
{
	nbTrainer = 0;
	for(int i = 0; i < DIM_TRAINER; i++)
	{
		liste_trainer[i].used = SDL_FALSE;
	}
}

void updateTrainer(void)
{	
	for(int i = 0; i < nbTrainer; i++)
	{
		liste_trainer[i].coordonner.x += liste_trainer[i].vitesse.x;
		liste_trainer[i].coordonner.y += liste_trainer[i].vitesse.y;
		liste_trainer[i].lifeRemaning.currentTime = SDL_GetTicks();
		if(liste_trainer[i].lifeRemaning.currentTime > (liste_trainer[i].lifeRemaning.previousTime + liste_trainer[i].lifeRemaning.ms))
		{
			liste_trainer[i].used = SDL_FALSE;
		}
	}
	removeTrainer();
}

void drawTrainer(void)
{
	for(int i = 0; i < nbTrainer; i++)
	{
		if(liste_trainer[i].used == SDL_TRUE)
		{
			drawPoint(&liste_trainer[i].coordonner.x, &liste_trainer[i].coordonner.y, &liste_trainer[i].couleur);
		}
	}
}

void addTrainer(int x, int y, int vie, int vx, int vy, SDL_Color couleur)
{
	if(nbTrainer < DIM_TRAINER - 2)
	{
		nbTrainer++;

		liste_trainer[nbTrainer - 1].vitesse.x = vx;
		liste_trainer[nbTrainer - 1].vitesse.y = vy;
		liste_trainer[nbTrainer - 1].coordonner.x = x;
		liste_trainer[nbTrainer - 1].coordonner.y = y;
		liste_trainer[nbTrainer - 1].lifeRemaning.ms = vie;
		liste_trainer[nbTrainer - 1].lifeRemaning.currentTime = 0;
		liste_trainer[nbTrainer - 1].lifeRemaning.previousTime = SDL_GetTicks();
		liste_trainer[nbTrainer - 1].couleur = couleur;
		liste_trainer[nbTrainer - 1].used = SDL_TRUE;
	}
}

void removeTrainer(void)
{
	int j = 0;
	if(nbTrainer > 0)
	{
		while(j < nbTrainer)
		{
			if(liste_trainer[j].used == SDL_FALSE)
			{
				for(int k = j; k < nbTrainer; k++)
				{
					Point tmp;
					tmp = liste_trainer[k + 1];
					liste_trainer[k + 1] = liste_trainer[k];
					liste_trainer[k] = tmp;
				}
				nbTrainer--;
			}
			j++;
		}
	}
}

void cleanFx(void)
{
	nbTrainer = 0;
}