#include "prototype.h"

void (*liste_event[DIM_EVENT])(void);

void initEvent(void)
{
	liste_event[0] = &quitGame;
	liste_event[1] = &startGame;
	liste_event[2] = &goToOption;
	liste_event[3] = &goToMenu;
	liste_event[4] = &backToMenu;
	liste_event[5] = &setFullscreen;
	liste_event[6] = &setEasy;
	liste_event[7] = &setMedium;
	liste_event[8] = &setHard;
	liste_event[9] = &setQuadrillage;
	liste_event[10] = &addVolumeFx;
	liste_event[11] = &removeVolumeFx;
	liste_event[12] = &addVolumeMusique;
	liste_event[13] = &removeVolumeMusique;
	liste_event[14] = &setLangue;
}

void quitGame(void)
{
	playFx(3);
	exit(EXIT_SUCCESS);
}

void startGame(void)
{
	playFx(3);
	cleanMainMenu();
	initSelectDifficulty();
}

void setLangue(void)
{
	playFx(3);
	if(getLangue() == 0)
	{
		changeLangue(1);
	}
	else if(getLangue() == 1)
	{
		changeLangue(0);
	}
}

void addVolumeMusique(void)
{
	playFx(3);
	upVolumeMusic();
}

void removeVolumeMusique(void)
{
	playFx(3);
	downVolumeMusic();
}	

void addVolumeFx(void)
{
	playFx(3);
	upVolumeFx();
}

void removeVolumeFx(void)
{
	playFx(3);
	downVolumeFx();
}

void setQuadrillage(void)
{
	changeQuadrillage();
}

void setEasy(void)
{
	playFx(3);
	cleanSelectDifficulty();
	setSelectLevel(1);
	initGame();
	initMap(getQuadrillageActive(), 1);
}

void setMedium(void)
{
	playFx(3);
	cleanSelectDifficulty();
	setSelectLevel(2);
	initGame();
	initMap(getQuadrillageActive(), 2);
}

void setHard(void)
{
	playFx(3);
	cleanSelectDifficulty();
	setSelectLevel(3);
	initGame();
	initMap(getQuadrillageActive(), 3);
}

void setFullscreen(void)
{
	playFx(3);
	if(getFullscreen() == SDL_TRUE)
	{
		if(SDL_SetWindowFullscreen(getWindow(), 0) != 0)
		{
			SDL_Log("ERROR FAIL SETFULLSCREEN EVENT :%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		changeFullscreen(SDL_FALSE);
	}
	else if(getFullscreen() == SDL_FALSE)
	{
		if(SDL_SetWindowFullscreen(getWindow(), SDL_WINDOW_FULLSCREEN) != 0)
		{
			SDL_Log("ERROR FAIL SETFULLSCREEN EVENT :%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}
		changeFullscreen(SDL_TRUE);
	}

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
}

void goToOption(void)
{
	playFx(3);
	cleanMainMenu();
	initOption();
}

void goToMenu(void)
{
	playFx(3);
	if(isActiveOption())
	{
		cleanOption();
	}
	else if(isActiveSelectDifficulty())
	{
		cleanSelectDifficulty();
	}
	else if(isActiveGame())
	{
		startMusic(2, SDL_FALSE);
		cleanGame();
	}

	initMainMenu();
}

void backToMenu(void)
{
	playFx(4);
	startMusic(2, SDL_FALSE);
	cleanGame();
	initMainMenu();
}

void playEvent(int event)
{
	if(event > -1 && event < DIM_EVENT)
	{
		(*liste_event[event])();
	}
}