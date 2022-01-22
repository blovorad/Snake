#include "prototype.h"

Snake snake;
SDL_bool block;

void initSnake(void)
{
	//Au début du jeu on a 3 partis de corps
	snake.nbPartis = 3;

	//Le rect de position
	SDL_Rect r1 = {160, 160, TILE_SIZE, TILE_SIZE};
	SDL_Rect r2 = {128, 160, TILE_SIZE, TILE_SIZE};
	SDL_Rect r3 = {96, 160, TILE_SIZE, TILE_SIZE};

	block = SDL_FALSE;

	//Init de toute les caractèristiques
	for(int i = 0; i < 4; i++)
	{
		snake.direction[i] = SDL_FALSE;
	}


	//chargement une fois de la texture
	snake.partieCorps[0].texture = createTexture("source/graphics/snakeHead.png", NULL);
	snake.partieCorps[1].texture = createTexture("source/graphics/snake.png", NULL);
	snake.partieCorps[2].texture = createTexture("source/graphics/snakeQueue.png", NULL);

	for(int i = 1; i < snake.nbPartis; i++)
	{
		snake.partieCorps[i].angle = 90;
		snake.partieCorps[i].currentDirection = DROITE;
	}

	snake.partieCorps[0].dimension = r1;
	snake.partieCorps[1].dimension = r2;
	snake.partieCorps[2].dimension = r3;

	snake.vitesse.x = snake.partieCorps[0].dimension.w;
	snake.vitesse.y = 0;
	snake.partieCorps[0].currentDirection = DROITE;
	snake.direction[snake.partieCorps[0].currentDirection] = SDL_TRUE;

	snake.partieCorps[0].angle = 90;

	snake.movingTimer.currentTime = 0;
	snake.movingTimer.previousTime = SDL_GetTicks();
	snake.movingTimer.ms = 100;
}

void updateSnake(Input *input)
{
	snake.movingTimer.currentTime = SDL_GetTicks();

	if(snake.movingTimer.currentTime > (snake.movingTimer.previousTime + snake.movingTimer.ms))
	{
		movingSnake(input);
		snake.movingTimer.previousTime = snake.movingTimer.currentTime;
	}
}

void drawSnake(void)
{
	//le draw classique
	for(int i = 0; i < snake.nbPartis; i++)
	{
		drawTextureEx(snake.partieCorps[i].texture, &snake.partieCorps[i].dimension, NULL, snake.partieCorps[i].angle);
	}
}

void addNewCorps(void)
{
	snake.nbPartis++;
	snake.partieCorps[snake.nbPartis - 1].texture = snake.partieCorps[snake.nbPartis - 2].texture;
	snake.partieCorps[snake.nbPartis - 1].dimension = snake.partieCorps[snake.nbPartis - 2].dimension;
	snake.partieCorps[snake.nbPartis - 1].angle = snake.partieCorps[snake.nbPartis - 2].angle;
	snake.partieCorps[snake.nbPartis - 2].texture = snake.partieCorps[1].texture;
}

void movingSnake(Input *input)
{
	int oldX = snake.partieCorps[0].dimension.x;
	int oldY = snake.partieCorps[0].dimension.y;
	int n = 0;

	if(block == SDL_FALSE)
	{
		//On regarde les input pour le déplacement puis si on regarde pas en BAS pour éviter un gameplay "bizarre"
		if(input->z && snake.partieCorps[0].currentDirection != BAS)
		{
			snake.vitesse.x = 0;
			snake.vitesse.y = -snake.partieCorps[0].dimension.h;

			snake.direction[snake.partieCorps[0].currentDirection] = SDL_FALSE;
			snake.partieCorps[0].currentDirection = HAUT;
			snake.direction[snake.partieCorps[0].currentDirection] = SDL_TRUE;
			snake.partieCorps[0].angle = 0;
		}
		//Sinon on regarde les input pour le déplacement puis si on regarde pas en HAUT pour éviter un gameplay "bizarre"
		else if(input->s && snake.partieCorps[0].currentDirection != HAUT)
		{
			snake.vitesse.x = 0;
			snake.vitesse.y = snake.partieCorps[0].dimension.h;

			snake.direction[snake.partieCorps[0].currentDirection] = SDL_FALSE;
			snake.partieCorps[0].currentDirection = BAS;
			snake.direction[snake.partieCorps[0].currentDirection] = SDL_TRUE;
			snake.partieCorps[0].angle = 180;
		}
		//Sinon on regarde les input pour le déplacement puis si on regarde pas en DROITE pour éviter un gameplay "bizarre"
		else if(input->q && snake.partieCorps[0].currentDirection != DROITE)
		{
			snake.vitesse.x = -snake.partieCorps[0].dimension.w;
			snake.vitesse.y = 0;

			snake.direction[snake.partieCorps[0].currentDirection] = SDL_FALSE;
			snake.partieCorps[0].currentDirection = GAUCHE;
			snake.direction[snake.partieCorps[0].currentDirection] = SDL_TRUE;
			snake.partieCorps[0].angle = 270;
		}
		//Sinon on regarde les input pour le déplacement puis si on regarde pas en GAUCHE pour éviter un gameplay "bizarre"
		else if(input->d && snake.partieCorps[0].currentDirection != GAUCHE)
		{
			snake.vitesse.x = snake.partieCorps[0].dimension.w;
			snake.vitesse.y = 0;

			snake.direction[snake.partieCorps[0].currentDirection] = SDL_FALSE;
			snake.partieCorps[0].currentDirection = DROITE;
			snake.direction[snake.partieCorps[0].currentDirection] = SDL_TRUE;
			snake.partieCorps[0].angle = 90;
		}
	}

	//On déplacement les partis du corps !
	for(int i = snake.nbPartis - 1; i > 0; i--)
	{
		int j = i - 1;

		if(snake.partieCorps[i].dimension.x != snake.partieCorps[j].dimension.x || 
			snake.partieCorps[i].dimension.y != snake.partieCorps[j].dimension.y)
		{
			snake.partieCorps[i].dimension.x = snake.partieCorps[j].dimension.x;
			snake.partieCorps[i].dimension.y = snake.partieCorps[j].dimension.y;
			snake.partieCorps[i].angle = snake.partieCorps[j].angle;
			if(snake.partieCorps[i].currentDirection != snake.partieCorps[j].currentDirection)
			{
				snake.partieCorps[i].currentDirection = snake.partieCorps[j].currentDirection;
			}
		}
	}

	if(block == SDL_FALSE)
	{
		if(snake.partieCorps[snake.nbPartis - 1].currentDirection == BAS)
		{
			for(int z = 0; z < 40; z++)
			{
				int x, y;
				x = (rand() % snake.partieCorps[snake.nbPartis - 1].dimension.w) + snake.partieCorps[snake.nbPartis - 1].dimension.x;
				y = -(rand() % snake.partieCorps[snake.nbPartis - 1].dimension.h) + snake.partieCorps[snake.nbPartis - 1].dimension.y;
				addTrainer(x, y, 200, 0, 0, getBlanc(255));
			}
		}
		else if(snake.partieCorps[snake.nbPartis - 1].currentDirection == HAUT)
		{
			for(int z = 0; z < 40; z++)
			{
				int x, y;
				x = (rand() % snake.partieCorps[snake.nbPartis - 1].dimension.w) + snake.partieCorps[snake.nbPartis - 1].dimension.x;
				y = (rand() % snake.partieCorps[snake.nbPartis - 1].dimension.h) + snake.partieCorps[snake.nbPartis - 1].dimension.y + 32;
				addTrainer(x, y, 200, 0, 0, getBlanc(255));
			}
		}
		else if(snake.partieCorps[snake.nbPartis - 1].currentDirection == DROITE)
		{
			for(int z = 0; z < 40; z++)
			{
				int x, y;
				x =	(rand() % snake.partieCorps[snake.nbPartis - 1].dimension.w) + snake.partieCorps[snake.nbPartis - 1].dimension.x - 32;
				y = (rand()	% snake.partieCorps[snake.nbPartis - 1].dimension.h) + snake.partieCorps[snake.nbPartis - 1].dimension.y;

				addTrainer(x, y, 200, 0, 0, getBlanc(255));
			}
		}
		else if(snake.partieCorps[snake.nbPartis - 1].currentDirection == GAUCHE)
		{
			for(int z = 0; z < 40; z++)
			{
				int x, y;
				x =	(rand() % snake.partieCorps[snake.nbPartis - 1].dimension.w) + snake.partieCorps[snake.nbPartis - 1].dimension.x + 32;
				y = (rand() % snake.partieCorps[snake.nbPartis - 1].dimension.h) + snake.partieCorps[snake.nbPartis - 1].dimension.y;

				addTrainer(x, y, 200, 0, 0, getBlanc(255));
			}
		}
	}

	//On deplace la tête
	if(block == SDL_FALSE)
	{
		snake.partieCorps[0].dimension.x += snake.vitesse.x;
		snake.partieCorps[0].dimension.y += snake.vitesse.y;
	}

	//verification pour eviter de sortir de la map
	if(snake.partieCorps[0].dimension.x < 0)
	{
		snake.partieCorps[0].dimension.x = getWidth() - snake.partieCorps[0].dimension.w;
	}
	if(snake.partieCorps[0].dimension.x >= getWidth())
	{
		snake.partieCorps[0].dimension.x = 0;
	}

	if(snake.partieCorps[0].dimension.y < 0)
	{
		snake.partieCorps[0].dimension.y = getMapHeight()*TILE_SIZE - snake.partieCorps[0].dimension.h;
	}
	if(snake.partieCorps[0].dimension.y >= getMapHeight()*TILE_SIZE)
	{
		snake.partieCorps[0].dimension.y = 0;
	}

	//la on vois si on est pas rentrer dans un morceau de "NOUS"
	int verif = 1;
	while(block == SDL_FALSE && verif < snake.nbPartis)
	{
		if(snake.partieCorps[0].dimension.x == snake.partieCorps[verif].dimension.x && 
			snake.partieCorps[0].dimension.y == snake.partieCorps[verif].dimension.y)
		{
			block = SDL_TRUE;
			snake.partieCorps[0].dimension.x = oldX;
			snake.partieCorps[0].dimension.y = oldY;
			activeEnd();
		}
		verif++;
	}

	n = getTileAt(snake.partieCorps[0].dimension.x, snake.partieCorps[0].dimension.y);

	//ici on a perdus !
	if(n == 1 || n == 2)	
	{
		block = SDL_TRUE;
		snake.partieCorps[0].dimension.x = oldX;
		snake.partieCorps[0].dimension.y = oldY;
		activeEnd();
	}

	//Ici on regarde si on a pas manger un bonbon
	if(n == 3)
	{
		int fxPlay = 0;
		fxPlay = rand() % 3;
		
		playFx(fxPlay);
		addNewCorps();
		addScore(50);
		removeApple(snake.partieCorps[0].dimension.x, snake.partieCorps[0].dimension.y);
		addApple();
	}
}

int getSnakeSize(void)
{
	return snake.nbPartis;
}

int getXPosSnake(int i, int diviseur)
{
	return snake.partieCorps[i].dimension.x / diviseur;
}

int getYPosSnake(int i, int diviseur)
{
	return snake.partieCorps[i].dimension.y / diviseur;
}

Vecteur getSnakeVitesse(void)
{
	return snake.vitesse;
}

SDL_bool isBlock(void)
{
	return block;
}

void cleanSnake(void)
{
	SDL_Log("CLEAN SNAKE EN COURS\n");
	//Le cassage des TEXTURES
	if(snake.partieCorps[0].texture != NULL)
	{
		SDL_DestroyTexture(snake.partieCorps[0].texture);
		snake.partieCorps[0].texture = NULL;
	}
	if(snake.partieCorps[1].texture != NULL)
	{
		SDL_DestroyTexture(snake.partieCorps[1].texture);
		snake.partieCorps[1].texture = NULL;
	}
	if(snake.partieCorps[snake.nbPartis - 1].texture != NULL)
	{
		SDL_DestroyTexture(snake.partieCorps[snake.nbPartis - 1].texture);
		snake.partieCorps[snake.nbPartis - 1].texture = NULL;
	}
	SDL_Log("CLEAN SNAKE TERMINER\n");

	/*//On enlève le malloc précedent, celui fait dans INITSNAKE
	free(snake.partieCorps);
	snake.partieCorps = NULL;*/
}

/*Sprite *partieCorps;
	Vecteur vitesse;
	int nbPartis;*/