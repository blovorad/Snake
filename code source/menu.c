#include "prototype.h"

Bouton liste_bouton[4];
Texte creditTexte;
Texte titleTexte;
Panel background;
int nbBouton;

//createBouton(int x, int y, int w, int h, SDL_Texture *panelTexture, SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, fill ,fonction)

void initMainMenu(void)
{
	setPrintMainMenu(SDL_TRUE);

	nbBouton = 4;
	//Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
	if(getLangue() == 0)
	{
		liste_bouton[0] = createBouton(300, 150, 200, 50, NULL, getGris(255), "COMMENCEZ", getNoir(255), getFont1(), SDL_FALSE, 1);
		liste_bouton[1] = createBouton(300, 225, 200, 50, NULL, getGris(255), "OPTION", getNoir(255), getFont1(), SDL_FALSE, 2);
		liste_bouton[2] = createBouton(300, 300, 200, 50, NULL, getGris(255), "QUITTER", getNoir(255), getFont1(), SDL_FALSE, 0);
		liste_bouton[3] = createBouton(650, 500, 128, 64, "source/graphics/drapeauFrançais.png", getGris(255), NULL, getNoir(255), getFont1(), SDL_FALSE, 14);

		titleTexte = createTexte(200, 50, 400, 50, "SNAKE REMAKE", getNoir(255), getFont1());
		creditTexte = createTexte(200, 550, 400, 50, "JEU CREER PAR BLOVORAD", getNoir(255), getFont1());
	}
	else if(getLangue() == 1)
	{
		liste_bouton[0] = createBouton(300, 150, 200, 50, NULL, getGris(255), "START", getNoir(255), getFont1(), SDL_FALSE, 1);
		liste_bouton[1] = createBouton(300, 225, 200, 50, NULL, getGris(255), "OPTION", getNoir(255), getFont1(), SDL_FALSE, 2);
		liste_bouton[2] = createBouton(300, 300, 200, 50, NULL, getGris(255), "QUIT", getNoir(255), getFont1(), SDL_FALSE, 0);
		liste_bouton[3] = createBouton(650, 500, 128, 64, "source/graphics/drapeauAnglais.png", getGris(255), NULL, getNoir(255), getFont1(), SDL_FALSE, 14);

		titleTexte = createTexte(200, 50, 400, 50, "SNAKE REMAKE", getNoir(255), getFont1());
		creditTexte = createTexte(200, 550, 400, 50, "GAME MADE BY BLOVORAD", getNoir(255), getFont1());
	}
	background = createPanel(0, 0, 800, 600, "source/graphics/background1.png", getGris(255), SDL_FALSE);
}

void updateMainMenu(void)
{
	int mX = getMouseX();
	int mY = getMouseY();

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

void drawMainMenu(void)
{
	if(background.sprite.texture != NULL)
	{
		drawTexture(background.sprite.texture, &background.sprite.dimension, NULL);
	}
	else
	{
		drawRect(&background.sprite.dimension, &background.fill, &background.couleur);
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
		if(liste_bouton[i].texte.sprite.texture != NULL)
		{
			drawTexture(liste_bouton[i].texte.sprite.texture, &liste_bouton[i].texte.sprite.dimension, NULL);
		}
	}
	drawTexture(creditTexte.sprite.texture, &creditTexte.sprite.dimension, NULL);
	drawTexture(titleTexte.sprite.texture, &titleTexte.sprite.dimension, NULL);
}

void cleanMainMenu(void)
{
	setPrintMainMenu(SDL_FALSE);

	SDL_Log("CLEAN MAIN MENU EN COURS\n");
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

	if(creditTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(creditTexte.sprite.texture);
		creditTexte.sprite.texture = NULL;
	}
	if(titleTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(titleTexte.sprite.texture);
		titleTexte.sprite.texture = NULL;
	}

	if(background.sprite.texture != NULL)
	{
		SDL_DestroyTexture(background.sprite.texture);
		background.sprite.texture = NULL;
	}
	SDL_Log("CLEAN MAIN MENU TERMINER\n");
}
/*typedef struct 
{
	
	SDL_Texture *texture;
	SDL_Rect dimension;
	int currentDirection;
	int angle;

}Sprite;*/
/*typedef struct 
{
	
	Panel panel;
	Texte texte;
	SDL_bool isHover, isPressed;

}Bouton;
typedef struct 
{

	Sprite sprite;
	SDL_Color couleur;

}Texte;

typedef struct 
{
	
	Sprite sprite;
	SDL_bool fill;
	SDL_Color couleur;

}Panel;*/