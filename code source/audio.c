#include "prototype.h"

Sound *liste_music;
Sound *liste_soundFx;

int sizeListeMusic;
int sizeListeFx;
int volumeMusic;
int volumeFx;

void initAudio(int nbMusic, int nbFx)
{
	//initialisation des channels pour les son : 1 : FX
	Mix_AllocateChannels(1);
	
	FILE *fichier = fopen("source/fichier/config.CONFIG", "r");

	if(fichier == NULL)
	{
		SDL_Log("IMPOSSIBLE D'OUVRIR FICHIER CONFIG POUR LECTURE\n");
		exit(EXIT_FAILURE);
	}
	fseek(fichier, 1, SEEK_SET);

	fscanf(fichier, "%d %d", &volumeMusic, &volumeFx);

	fclose(fichier);
	fichier = NULL;

	/*volumeMusic = 2;
	volumeFx = 2;*/

	Mix_Volume(0, volumeFx * 12);
	Mix_VolumeMusic(volumeMusic * 12);
	//Creation du tableau
	liste_music = malloc(sizeof(Sound) * nbMusic);
	liste_soundFx = malloc(sizeof(Sound) * nbFx);

	if(liste_music == NULL || liste_soundFx == NULL)
	{
		SDL_Log("IMPOSSIBLE ALLOCATION MEMOIRE SOUND :%s",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//Remplisage du tableau musique
	sizeListeMusic = nbMusic;
	for(int i = 0; i < nbMusic; i++)
	{
		//Recuperation de la musique a charger
		char chemin[100] = {"source/sounds/musique"};
		char nMusic[2];
		char *extension = ".wav";

		sprintf(nMusic, "%d", i+1);

		strcat(chemin,nMusic);
		strcat(chemin,extension);

		//Chargement de la musique puis ajout a mon tableau
		liste_music[i].music = Mix_LoadMUS(chemin);
		if(liste_music[i].music == NULL)
		{
			SDL_Log("IMPOSSIBLE DE CHARGER LA MUSIQUE : %s",Mix_GetError());
			exit(EXIT_FAILURE);
		}
		liste_music[i].isPlaying = SDL_FALSE;
		liste_music[i].fx = NULL;
	}

	//Remplissage du tableau fx
	sizeListeFx = nbFx;
	for(int i = 0; i < nbFx; i++)
	{
		//Recuperation du fx a charger
		char chemin[100] = {"source/sounds/fx"};
		char nFx[2];
		char *extension = ".wav";

		sprintf(nFx, "%d", i+1);

		strcat(chemin,nFx);
		strcat(chemin,extension);

		//Chargement du fx puis ajout a mon tableau
		liste_soundFx[i].fx = Mix_LoadWAV(chemin);
		if(liste_soundFx[i].fx == NULL)
		{
			SDL_Log("IMPOSSIBLE DE CHARGER UN FX : %s",Mix_GetError());
			exit(EXIT_FAILURE);
		}
		liste_soundFx[i].isPlaying = SDL_FALSE;
		liste_soundFx[i].music = NULL;
	}

	startMusic(2, SDL_FALSE);
}

void upVolumeFx(void)
{
	volumeFx++;
	if(volumeFx > 10)
	{
		volumeFx = 10;
	}

	Mix_Volume(0, volumeFx * 12);
}

void downVolumeFx(void)
{
	volumeFx--;
	if(volumeFx < 0)
	{
		volumeFx = 0;
	}

	Mix_Volume(0, volumeFx * 12);
}

void upVolumeMusic(void)
{
	volumeMusic++;
	if(volumeMusic > 10)
	{
		volumeMusic = 10;
	}
	Mix_VolumeMusic(volumeMusic * 12);
}

void downVolumeMusic(void)
{
	volumeMusic--;
	if(volumeMusic < 0)
	{
		volumeMusic = 0;
	}
	Mix_VolumeMusic(volumeMusic * 12);
}

//Un genre de mixer audio
void updateAudio(void)
{
	if(isActiveGame() == SDL_TRUE)
	{
		for(int i = 0; i < 2; i++)
		{
			if(liste_music[i].isPlaying == SDL_TRUE)
			{
				if(Mix_PlayingMusic() == 0)
				{
					liste_music[i].isPlaying = SDL_FALSE;
					if(i == 1)
					{
						startMusic(0, SDL_FALSE);
						liste_music[0].isPlaying = SDL_TRUE;
					}
					else
					{
						startMusic(i + 1, SDL_FALSE);
						liste_music[i+1].isPlaying = SDL_TRUE;
					}
				}
			}
		}
	}
	else
	{
		for(int i = 2; i < 4; i++)
		{
			if(liste_music[i].isPlaying == SDL_TRUE)
			{
				if(Mix_PlayingMusic() == 0)
				{
					liste_music[i].isPlaying = SDL_FALSE;
					if(i == sizeListeMusic - 1)
					{
						startMusic(2, SDL_FALSE);
						liste_music[2].isPlaying = SDL_TRUE;
					}
					else
					{
						startMusic(i + 1, SDL_FALSE);
						liste_music[i+1].isPlaying = SDL_TRUE;
					}
				}
			}	
		}
	}
}

//fonction pour lancer un son
void startMusic(int music, SDL_bool loop)
{
	Mix_HaltMusic();
	for(int i = 0; i < sizeListeMusic; i++)
	{
		if(i != music)
		{
			if(liste_music[i].isPlaying == SDL_TRUE)
			{
				liste_music[i].isPlaying = SDL_FALSE;
			}
		}
		else if(i == music)
		{
			if(loop == SDL_TRUE)
			{
				Mix_PlayMusic(liste_music[i].music,-1);
				liste_music[i].isPlaying = SDL_TRUE;
			}
			else
			{
				Mix_PlayMusic(liste_music[i].music,0);
				liste_music[i].isPlaying = SDL_TRUE;
			}
		}
	}
}

//Fonction pour jouer le fx demander
void playFx(int fx)
{
	Mix_PlayChannel(0, liste_soundFx[fx].fx, 0);
}

int getVolumeMusic(void)
{
	return volumeMusic;
}

int getVolumeFx(void)
{
	return volumeFx;
}

//liberation de toute les musique et fx + free des mallocs
void cleanAudio(void)
{
	SDL_Log("CLEAN AUDIO\n");
	
	for(int i = 0; i < sizeListeMusic; i++)
	{
		if(liste_music[i].music != NULL)
		{
			Mix_FreeMusic(liste_music[i].music);
			liste_music[i].music = NULL;
		}
	}

	free(liste_music);
	liste_music = NULL;


	for(int i = 0; i < sizeListeFx; i++)
	{
		if(liste_soundFx[i].fx != NULL)
		{
			Mix_FreeChunk(liste_soundFx[i].fx);
			liste_soundFx[i].fx = NULL;
		}
	}

	free(liste_soundFx);
	liste_soundFx = NULL;
	sizeListeMusic = 0;
	sizeListeFx = 0;
}
