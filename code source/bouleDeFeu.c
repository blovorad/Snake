#include "prototype.h"

Boule boule;

void initBouleDeFeu(int x, int y, Vecteur vitesse)
{
	boule.isActive = SDL_TRUE;

	boule.sprite.texture = createTexture("source/graphics/orbe.png", NULL);
	boule.sprite.dimension.x = x * TILE_SIZE;
	boule.sprite.dimension.y = y * TILE_SIZE;
	boule.sprite.dimension.w = TILE_SIZE;
	boule.sprite.dimension.h = TILE_SIZE;

	boule.vitesse = vitesse;

	boule.moving.previousTime = SDL_GetTicks();
	boule.moving.currentTime = 0;
	boule.moving.ms = 50;
}

void updateBouleDeFeu(void)
{
	int n = 0;

	if(boule.isActive)
	{
		boule.moving.currentTime = SDL_GetTicks();
		if(boule.moving.currentTime > (boule.moving.previousTime + boule.moving.ms))
		{
			boule.sprite.dimension.x += boule.vitesse.x;
			boule.sprite.dimension.y += boule.vitesse.y;

			if(boule.vitesse.x > 0)
			{
				for(int z = 0; z < 200; z++)
				{
					int x = -(rand() % boule.sprite.dimension.w) + boule.sprite.dimension.x;
					int y = (rand() % boule.sprite.dimension.h) + boule.sprite.dimension.y;
					addTrainer(x, y, 100, 0, 0, getJaune(255));
				}
			}
			if(boule.vitesse.x < 0)
			{
				for(int z = 0; z < 200; z++)
				{
					int x = (rand() % boule.sprite.dimension.w) + (boule.sprite.dimension.x + boule.sprite.dimension.w);
					int y = (rand() % boule.sprite.dimension.h) + boule.sprite.dimension.y;
					addTrainer(x, y, 100, 0, 0, getJaune(255));
				}
			}
			if(boule.vitesse.y > 0)
			{
				for(int z = 0; z < 200; z++)
				{
					int x = (rand() % boule.sprite.dimension.w) + boule.sprite.dimension.x;
					int y = -(rand() % boule.sprite.dimension.h) + boule.sprite.dimension.y;
					addTrainer(x, y, 100, 0, 0, getJaune(255));
				}
			}
			if(boule.vitesse.y < 0)
			{
				for(int z = 0; z < 200; z++)
				{
					int x = (rand() % boule.sprite.dimension.w) + boule.sprite.dimension.x;
					int y = (rand() % boule.sprite.dimension.h) + (boule.sprite.dimension.y + boule.sprite.dimension.h);
					addTrainer(x, y, 100, 0, 0, getJaune(255));
				}
			}

			boule.moving.previousTime = boule.moving.currentTime;
		}
		if(boule.sprite.dimension.x + boule.sprite.dimension.w < 0 || boule.sprite.dimension.x >= getWidth() || boule.sprite.dimension.y < 0 || boule.sprite.dimension.y >= getMapHeight() * TILE_SIZE)
		{
			cleanBouleDeFeu();
		}

		n = getTileAt(boule.sprite.dimension.x, boule.sprite.dimension.y);

		if(n == 1 || n == 2)
		{
			removeBlock(boule.sprite.dimension.x, boule.sprite.dimension.y);
			createExplosion();
			cleanBouleDeFeu();
		}
		if(n == 3)
		{
			removeApple(boule.sprite.dimension.x, boule.sprite.dimension.y);
			addApple();
		}
	}
}

void drawBouleDeFeu(void)
{
	if(boule.isActive)
	{
		drawTexture(boule.sprite.texture, &boule.sprite.dimension, NULL);
	}
}

void createExplosion(void)
{
	playFx(7);
	
	for(int i = 0; i < 360; i++)
	{
		int x = boule.sprite.dimension.x + boule.sprite.dimension.w / 2;
		int y = boule.sprite.dimension.y + boule.sprite.dimension.h / 2;
		int vx = rand() % 50 * cos(rand() % 360);
		int vy = rand() % 50 * sin(rand() % 360);
		addTrainer(x, y, 200, vx, vy, getJaune(255));
	}
}

SDL_bool isActiveBouleDeFeu(void)
{
	return boule.isActive;
}

void cleanBouleDeFeu(void)
{
	if(boule.isActive)
	{
		if(boule.sprite.texture != NULL)
		{
			SDL_DestroyTexture(boule.sprite.texture);
			boule.sprite.texture = NULL;
		}
		boule.isActive = SDL_FALSE;
	}
}