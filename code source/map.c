#include "prototype.h"

Map map;
Quadrillage quadrillage;

void initMap(SDL_bool activeQuadrillage, int pMap)
{
	//INIT DE LA CARTE
	int nombre = 0;
	quadrillage.active = SDL_FALSE;

	//ouverture du fichier
	FILE *fichier = NULL;

	if(pMap == 1)
	{
		fichier = fopen("source/fichier/map1.MAP", "r");
	}
	else if(pMap == 2)
	{
		fichier = fopen("source/fichier/map2.MAP", "r");
	}
	else if(pMap == 3)
	{
		fichier = fopen("source/fichier/map3.MAP", "r");
	}

	if(fichier == NULL)
	{
		SDL_Log("ERROR OPEN FILE IN INIT MAP FOR READING");
		exit(EXIT_FAILURE);
	}

	fscanf(fichier, "%d %d", &map.width, &map.height);

	//malloc pour la map
	map.layer1 = malloc(sizeof(Tile) * map.height);

	if(map.layer1 == NULL)
	{
		SDL_Log("ERROR MALLOC FILE MAP");
		fclose(fichier);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < map.height; i++)
	{
		map.layer1[i] = malloc(sizeof(Tile) * map.width);
		if(map.layer1[i] == NULL)
		{
			SDL_Log("ERROR MALLOC FILE MAP");
			fclose(fichier);
			exit(EXIT_FAILURE);
		}
	}

	map.layer2 = malloc(sizeof(Tile) * map.height);

	if(map.layer2 == NULL)
	{
		SDL_Log("ERROR MALLOC FILE MAP");
		fclose(fichier);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < map.height; i++)
	{
		map.layer2[i] = malloc(sizeof(Tile) * map.width);
		if(map.layer2[i] == NULL)
		{
			SDL_Log("ERROR MALLOC FILE MAP");
			fclose(fichier);
			exit(EXIT_FAILURE);
		}
	}

	if(activeQuadrillage == SDL_TRUE)
	{
		quadrillage.layer1 = malloc(sizeof(Tile) * map.height);

		if(quadrillage.layer1 == NULL)
		{
			SDL_Log("ERROR MALLOC FILE MAP Quadrillage");
			fclose(fichier);
			exit(EXIT_FAILURE);
		}

		for(int i = 0; i < map.height; i++)
		{
			quadrillage.layer1[i] = malloc(sizeof(Tile) * map.width);
			if(quadrillage.layer1[i] == NULL)
			{
				SDL_Log("ERROR MALLOC FILE MAP Quadrillage");
				fclose(fichier);
				exit(EXIT_FAILURE);
			}
		}
	}

	//INIT QUADRILLAGE
	if(activeQuadrillage == SDL_TRUE)
	{
		quadrillage.active = SDL_TRUE;
		for(int i = 0; i < map.height; i++)
		{
			for(int j = 0; j < map.width ; j++)
			{
				quadrillage.layer1[i][j].couleur = getBlanc(50);
				quadrillage.layer1[i][j].fill = SDL_FALSE;
				quadrillage.layer1[i][j].number = 0;
				quadrillage.layer1[i][j].sprite.texture = NULL;
				quadrillage.layer1[i][j].sprite.currentDirection = 0;
				quadrillage.layer1[i][j].sprite.angle = 0;
				quadrillage.layer1[i][j].sprite.dimension.x = j * TILE_SIZE;
				quadrillage.layer1[i][j].sprite.dimension.y = i * TILE_SIZE;
				quadrillage.layer1[i][j].sprite.dimension.w = TILE_SIZE;
				quadrillage.layer1[i][j].sprite.dimension.h = TILE_SIZE;
			}
		}
	}
	//RECUPERATION TYPE DE CHAQUE TILE
	//LAYER 1
	for(int i = 0; i < map.height; i++)
	{
		for(int j = 0; j < map.width; j++)
		{
			map.layer1[i][j].sprite.dimension.w = TILE_SIZE;
			map.layer1[i][j].sprite.dimension.h = TILE_SIZE;
			map.layer1[i][j].sprite.dimension.x = j * TILE_SIZE;
			map.layer1[i][j].sprite.dimension.y = i * TILE_SIZE;
			map.layer1[i][j].sprite.texture = NULL;
			map.layer1[i][j].fill = SDL_TRUE;
			//printf("DIM : %d, %d, %d, %d\n",map.layer1[i][j].sprite.dimension.x,map.layer1[i][j].sprite.dimension.y,map.layer1[i][j].sprite.dimension.w,map.layer1[i][j].sprite.dimension.h);

			fscanf(fichier, "%d", &nombre);
			map.layer1[i][j].number = nombre;
			switch(nombre)
			{
				case 0 :
						map.layer1[i][j].couleur = getNoir(50);
					break;

				case 1 :
						map.layer1[i][j].couleur = getNoir(50);
					break;

				default :
					break;
			}
		}
	}
	//LAYER 2
	for(int i = 0; i < map.height; i++)
	{
		for(int j = 0; j < map.width; j++)
		{
			map.layer2[i][j].sprite.dimension.w = TILE_SIZE;
			map.layer2[i][j].sprite.dimension.h = TILE_SIZE;
			map.layer2[i][j].sprite.dimension.x = j * TILE_SIZE;
			map.layer2[i][j].sprite.dimension.y = i * TILE_SIZE;
			map.layer2[i][j].sprite.texture = NULL;
			map.layer2[i][j].fill = SDL_TRUE;

			fscanf(fichier, "%d", &nombre);
			map.layer2[i][j].number = nombre;
			switch(nombre)
			{
				case 0 :
						map.layer2[i][j].couleur = getNoir(255);
					break;

				case 1 :
						map.layer2[i][j].couleur = getMarron(255);
						map.layer2[i][j].sprite.texture = createTexture("source/graphics/block1.png", NULL);
					break;

				case 2 :
						map.layer2[i][j].couleur = getMarron(255);
						map.layer2[i][j].sprite.texture = createTexture("source/graphics/block1.png", NULL);
						//map.layer2[i][j].sprite.texture = createTexture("source/graphics/block2.png", NULL);

				default :
					break;
			}
		}
	}
	addApple();

	fclose(fichier);
}

void drawMap(void)
{
	for(int i = 0; i < map.height; i++)
	{
		for(int j = 0; j < map.width; j++)
		{
			if(map.layer1[i][j].sprite.texture != NULL)
			{
				drawTexture(map.layer1[i][j].sprite.texture, &map.layer1[i][j].sprite.dimension, NULL);
			}
			else
			{
				drawRect(&map.layer1[i][j].sprite.dimension, &map.layer1[i][j].fill, &map.layer1[i][j].couleur);
			}
			if(map.layer2[i][j].sprite.texture != NULL)
			{
				drawTexture(map.layer2[i][j].sprite.texture, &map.layer2[i][j].sprite.dimension, NULL);
			}
			else
			{
				if(map.layer2[i][j].number != 0)
				{
					drawRect(&map.layer2[i][j].sprite.dimension, &map.layer2[i][j].fill, &map.layer2[i][j].couleur);
				}
			}
			if(quadrillage.active == SDL_TRUE)
			{
				drawRect(&quadrillage.layer1[i][j].sprite.dimension, &quadrillage.layer1[i][j].fill, &quadrillage.layer1[i][j].couleur);
			}
		}
	}
}

void removeApple(int x, int y)
{
	int i = y / TILE_SIZE;
	int j = x / TILE_SIZE;

	if(i >= 0 && i < map.height && j >= 0 && j < map.width)
	{
		map.layer2[i][j].number = 0;
		map.layer2[i][j].couleur = getNoir(255);
		SDL_DestroyTexture(map.layer2[i][j].sprite.texture);
		map.layer2[i][j].sprite.texture = NULL;
	}
}

void addApple(void)
{
	SDL_bool placed = SDL_FALSE;
	int snakeSize = getSnakeSize();
	int i, j;
	int z;

	while(placed == SDL_FALSE)
	{
		j = rand() % map.width;
		i = rand() % map.height;
		if(map.layer2[i][j].number != 1)
		{
			placed = SDL_TRUE;
		}
		for(int z = 0; z < snakeSize; z++)
		{
			if(i == getYPosSnake(z, TILE_SIZE) && j == getXPosSnake(z, TILE_SIZE))
			{
				placed = SDL_FALSE;
			}
		}
	}

	map.layer2[i][j].number = 3;
	map.layer2[i][j].couleur = getRouge(255);
	map.layer2[i][j].sprite.texture = createTexture("source/graphics/pomme.png", NULL);
}

int getTileAt(int x, int y)
{
	int i = y / TILE_SIZE;
	int j = x / TILE_SIZE;

	if(i >= 0 && i < map.height && j >= 0 && j < map.width)
	{
		return map.layer2[i][j].number;
	}

	return -1;
}

void removeBlock(int x, int y)
{
	int i = y / TILE_SIZE;
	int j = x / TILE_SIZE;

	if(i >= 0 && i < map.height && j >= 0 && j < map.width)
	{
		map.layer2[i][j].number = 0;
		map.layer2[i][j].couleur = getNoir(255);
		SDL_DestroyTexture(map.layer2[i][j].sprite.texture);
		map.layer2[i][j].sprite.texture = NULL;
	} 
}

int getMapWidth(void)
{
	return map.width;
}

int getMapHeight(void)
{
	return map.height;
}

void cleanMap(void)
{
	//LE FREE DES MALLOC ET DES TEXTURE
	SDL_Log("CLEAN MAP EN COURS\n");
	for(int i = 0; i < map.height; i++)
	{
		for(int j = 0; j < map.width; j++)
		{
			if(map.layer1[i][j].sprite.texture != NULL)
			{
				SDL_DestroyTexture(map.layer1[i][j].sprite.texture);
				map.layer1[i][j].sprite.texture = NULL;
			}
		}
	}

	for(int i = 0; i < map.height; i++)
	{
		free(map.layer1[i]);
	}

	free(map.layer1);

	for(int i = 0; i < map.height; i++)
	{
		for(int j = 0; j < map.width; j++)
		{
			if(map.layer2[i][j].sprite.texture != NULL)
			{
				SDL_DestroyTexture(map.layer2[i][j].sprite.texture);
				map.layer2[i][j].sprite.texture = NULL;
			}
		}
	}

	for(int i = 0; i < map.height; i++)
	{
		free(map.layer2[i]);
	}

	free(map.layer2);

	if(quadrillage.active == SDL_TRUE)
	{
		for(int i = 0; i < map.height; i++)
		{
			for(int j = 0; j < map.width; j++)
			{
				if(quadrillage.layer1[i][j].sprite.texture != NULL)
				{
					SDL_DestroyTexture(quadrillage.layer1[i][j].sprite.texture);
					quadrillage.layer1[i][j].sprite.texture = NULL;
				}
			}
		}
		for(int i = 0; i < map.height; i++)
		{
			free(quadrillage.layer1[i]);
		}

		free(quadrillage.layer1);
	}

	SDL_Log("CLEAN MAP TERMINER\n");
}