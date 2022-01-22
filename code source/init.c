#include "prototype.h"

SDL_Window *screen;
SDL_Renderer *renderer;
int screenWidth;
int screenHeight;
int langue;
float scaleX;
float scaleY;
SDL_bool fullscreen;

void init(void)
{
	srand(time(NULL));
	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER LA SDL : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	fullscreen = SDL_FALSE;

	FILE *fichier = fopen("source/fichier/config.CONFIG", "r");
	int verif = 0;

	if(fichier == NULL)
	{
		SDL_Log("ERROR OPEN FILE CONFIG IN INI READINGT\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fichier, "%d", &verif);

	if(verif == 0)
	{
		screen = SDL_CreateWindow("SNAKE BLOVORAD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	}
	else if(verif == 1)
	{
		screen = SDL_CreateWindow("SNAKE BLOVORAD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_FULLSCREEN);	
		fullscreen = SDL_TRUE;
	}
	else
	{
		SDL_Log("ERROR IN FILE CONFIG\n");
		exit(EXIT_FAILURE);
	}

	fseek(fichier, 5, SEEK_SET);

	fscanf(fichier, "%d", &langue);

	fclose(fichier);
	fichier = NULL;

	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	if(screen == NULL || renderer == NULL)
	{
		SDL_Log("IMPOSSIBLE CREATION FENETRE OU RENDERER : %s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//ON RECUPERE LES DIMENSIONS
	screenWidth = 800;
	screenHeight = 600;

	//ON ACTIVE LA TRANSPARENCE
	if(SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
	{
		SDL_Log("IMPOSSIBLE D'ACTIVER LA TRANSPARENCE :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//ON INIT LA LIB D'ECRITURE
	if(TTF_Init() != 0)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER TTF :%s",TTF_GetError());
		exit(EXIT_FAILURE);
	}

	//ON INIT LA LIB DE SON
	if(Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		SDL_Log("IMPOSSIBLE DE CHARGER MIXER :%s",Mix_GetError());
		exit(EXIT_FAILURE);
	}

	scaleX = (float)screenWidth/(float)BASE_SCREENWIDTH;
	scaleY = (float)screenHeight/(float)BASE_SCREENHEIGHT;


	initEvent();
	initSceneManager();
	initFont1();
	initMouse();
	initAudio(5,8);
	initMainMenu();
	initTrainer();
}

//FONCTION DE RECUPERATION

SDL_bool getFullscreen(void)
{
	return fullscreen;
}

void changeFullscreen(SDL_bool active)
{
	fullscreen = active;
}

int getLangue(void)
{
	return langue;
}

float getScaleX(void)
{
	return scaleX;
}

float getScaleY(void)
{
	return scaleY;
}

SDL_Renderer *getRenderer(void)
{
	return renderer;
}

SDL_Window *getWindow(void)
{
	return screen;
}

int getWidth(void)
{
	return screenWidth;
}

int getHeight(void)
{
	return screenHeight;
}

void saveConfig(void)
{
	SDL_Log("SAUVEGARDE EN COURS\n");
	FILE *fichier = fopen("source/fichier/config.CONFIG", "w");

	if(fichier == NULL)
	{
		SDL_Log("ERROR OPEN FILE FOR WRITING IN SETFULLSCREEN\n");
		exit(EXIT_FAILURE);
	}

	if(getFullscreen() == SDL_FALSE)
	{
		fputs("0 ", fichier);
	}
	else if(getFullscreen() == SDL_TRUE)
	{
		fputs("1 ", fichier);
	}

	char fx[2];
	char musique[2];
	char espace[5] = " ";

	sprintf(fx, "%d", getVolumeFx());
	sprintf(musique, "%d", getVolumeMusic());

	fputs(musique, fichier);

	strcat(espace, fx);

	fputs(espace, fichier);

	if(getLangue() == 0)
	{
		fputs(" 0", fichier);
	}
	else if(getLangue() == 1)
	{
		fputs(" 1", fichier);
	}

	fclose(fichier);
	SDL_Log("SAUVEGARDE TERMINER\n");
}

void changeLangue(int n)
{
	langue = n;
	cleanMainMenu();
	initMainMenu();
}

//LE GRAND NETTOYAGE
void cleanUp(void)
{
	SDL_Log("----CLEAN GENERAL EN COURS----\n");

	saveConfig();

	cleanFont1();
	if(isActiveGame())
	{
		cleanGame();
	}
	if(isActiveMainMenu())
	{
		cleanMainMenu();
	}
	if(isActiveOption())
	{
		cleanOption();
	}
	if(isActiveSelectDifficulty())
	{
		cleanSelectDifficulty();
	}

	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if(screen != NULL)
	{
		SDL_DestroyWindow(screen);
		screen = NULL;
	}

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}