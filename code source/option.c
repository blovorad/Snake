#include "prototype.h"

Bouton liste_bouton[6];
Texte liste_texte[2];
Barre liste_barre[2];
Panel background;
int nbBouton;
int nbTexte;
int nbBarre;
//createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
//Barre createBarre(int x, int y, int w, int h, SDL_Color color)
//createBouton(int x, int y, int w, int h, SDL_Texture *panelTexture, SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, fill, fonction)
void initOption(void)
{
	setPrintOption(SDL_TRUE);

	nbBouton = 6;
	nbTexte = 2;
	nbBarre = 2;

	if(getLangue() == 0)
	{
		liste_bouton[0] = createBouton(275, 500, 250, 50, NULL, getGris(255), "MENU PRINCIPALE", getNoir(255), getFont1(), SDL_FALSE, 3);
		liste_bouton[1] = createBouton(275, 50, 250, 50, NULL, getGris(255), "FULLSCREEN", getNoir(255), getFont1(), SDL_FALSE, 5);
		liste_bouton[2] = createBouton(150, 200, 100, 50, NULL, getGris(255), "MOINS", getNoir(255), getFont1(), SDL_FALSE, 13);
		liste_bouton[3] = createBouton(550, 200, 100, 50, NULL, getGris(255), "PLUS", getNoir(255), getFont1(), SDL_FALSE, 12);
		liste_bouton[4] = createBouton(150, 350, 100, 50, NULL, getGris(255), "MOINS", getNoir(255), getFont1(), SDL_FALSE, 11);
		liste_bouton[5] = createBouton(550, 350, 100, 50, NULL, getGris(255), "PLUS", getNoir(255), getFont1(), SDL_FALSE, 10);

		liste_texte[0] = createTexte(300, 150, 200, 50, "VOLUME MUSIQUES", getBlanc(255), getFont1());
		liste_texte[1] = createTexte(300, 300, 200, 50, "VOLUME EFFETS", getBlanc(255), getFont1());
	}
	else if(getLangue() == 1)
	{
		liste_bouton[0] = createBouton(275, 500, 250, 50, NULL, getGris(255), "MAIN MENU", getNoir(255), getFont1(), SDL_FALSE, 3);
		liste_bouton[1] = createBouton(275, 50, 250, 50, NULL, getGris(255), "FULLSCREEN", getNoir(255), getFont1(), SDL_FALSE, 5);
		liste_bouton[2] = createBouton(150, 200, 100, 50, NULL, getGris(255), "DOWN", getNoir(255), getFont1(), SDL_FALSE, 13);
		liste_bouton[3] = createBouton(550, 200, 100, 50, NULL, getGris(255), "UP", getNoir(255), getFont1(), SDL_FALSE, 12);
		liste_bouton[4] = createBouton(150, 350, 100, 50, NULL, getGris(255), "DOWN", getNoir(255), getFont1(), SDL_FALSE, 11);
		liste_bouton[5] = createBouton(550, 350, 100, 50, NULL, getGris(255), "UP", getNoir(255), getFont1(), SDL_FALSE, 10);

		liste_texte[0] = createTexte(300, 150, 200, 50, "VOLUME MUSICS", getBlanc(255), getFont1());
		liste_texte[1] = createTexte(300, 300, 200, 50, "VOLUME EFFECTS", getBlanc(255), getFont1());
	}

	liste_barre[0] = createBarre(275, 200, 250, 50, getBlanc(255));
	liste_barre[1] = createBarre(275, 350, 250, 50, getBlanc(255));

	background = createPanel(0, 0, 800, 600, "source/graphics/background1.png", getNoir(255), SDL_TRUE);
}

void updateOption(void)
{
	int mX = getMouseX();
	int mY = getMouseY();

	liste_barre[0].sprite.dimension.w = (getVolumeMusic() * liste_barre[0].tailleReel.w) / 10;
	liste_barre[1].sprite.dimension.w = (getVolumeFx() * liste_barre[1].tailleReel.w) / 10;

	for(int i = 0; i < nbBouton; i++)
	{
		int x = liste_bouton[i].panel.sprite.dimension.x;
		int y = liste_bouton[i].panel.sprite.dimension.y;
		int w = liste_bouton[i].panel.sprite.dimension.w;
		int h = liste_bouton[i].panel.sprite.dimension.h;

		if(mX > x && mX < x + w && mY > y && mY < y + h)
		{
			if(liste_bouton[i].isHover == SDL_FALSE)
			{
				liste_bouton[i].isHover = SDL_TRUE;
				liste_bouton[i].currentEtat = HOVER;
				liste_bouton[i].panel.couleur = getBleu(liste_bouton[i].alpha);
			}
		}
		else
		{
			if(liste_bouton[i].isHover == SDL_TRUE)
			{
				liste_bouton[i].isHover = SDL_FALSE;
				liste_bouton[i].currentEtat = NONE;
				liste_bouton[i].panel.couleur = getGris(liste_bouton[i].alpha);
			}
		}

		if(liste_bouton[i].isHover == SDL_TRUE && liste_bouton[i].isPressed == SDL_FALSE && 
			getStateOfLeftButton() == SDL_TRUE && getStateOfOldLeftButton() == SDL_FALSE)
		{
			liste_bouton[i].isPressed = SDL_TRUE;
			liste_bouton[i].currentEtat = PRESSED;
			liste_bouton[i].panel.couleur = getMarron(liste_bouton[i].alpha);
			playEvent(liste_bouton[i].event);
		}
		else
		{
			if(liste_bouton[i].isPressed == SDL_TRUE && getStateOfLeftButton() == SDL_FALSE)
			{
				liste_bouton[i].isPressed = SDL_FALSE;
				liste_bouton[i].currentEtat = NONE;
				liste_bouton[i].panel.couleur = getGris(liste_bouton[i].alpha);
			}
		}
	}
	actualiseOldLeftButton();
}

void drawOption(void)
{
	drawTexture(background.sprite.texture, &background.sprite.dimension, NULL);

	for(int i = 0; i < nbTexte; i++)
	{
		drawTexture(liste_texte[i].sprite.texture, &liste_texte[i].sprite.dimension, NULL);
	}

	for(int  i = 0; i < nbBarre; i++)
	{
		drawRect(&liste_barre[i].sprite.dimension, &liste_barre[i].fill, &liste_barre[i].couleur);
		drawRect(&liste_barre[i].tailleReel, &liste_barre[i].empty, &liste_barre[i].couleur);
	}	

	for(int i = 0; i < nbBouton; i++)
	{
		int current = liste_bouton[i].currentEtat;
		if(liste_bouton[i].boutonTexture[current] == NULL)
		{
			drawRect(&liste_bouton[i].panel.sprite.dimension, &liste_bouton[i].panel.fill, &liste_bouton[i].panel.couleur);
		}
		else
		{
			drawTexture(liste_bouton[i].boutonTexture[current], &liste_bouton[i].panel.sprite.dimension, NULL);
		}
		drawTexture(liste_bouton[i].texte.sprite.texture, &liste_bouton[i].texte.sprite.dimension, NULL);
	}
}

void cleanOption(void)
{
	setPrintOption(SDL_FALSE);

	SDL_Log("CLEAN OPTION EN COURS\n");
	for(int i = 0; i < nbTexte; i++)
	{
		if(liste_texte[i].sprite.texture != NULL)
		{
			SDL_DestroyTexture(liste_texte[i].sprite.texture);
			liste_texte[i].sprite.texture = NULL;
		}
	}

	for(int i = 0; i < nbBouton; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(liste_bouton[i].boutonTexture[j] != NULL)
			{	
				SDL_DestroyTexture(liste_bouton[i].boutonTexture[j]);
				liste_bouton[i].boutonTexture[j] = NULL;
			}
		}
		if(liste_bouton[i].texte.sprite.texture != NULL)
		{
			SDL_DestroyTexture(liste_bouton[i].texte.sprite.texture);
			liste_bouton[i].texte.sprite.texture = NULL;
		}
	}

	if(background.sprite.texture != NULL)
	{
		SDL_DestroyTexture(background.sprite.texture);
		background.sprite.texture = NULL;
	}
	SDL_Log("CLEAN OPTION TERMINER\n");
}