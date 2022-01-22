#include "prototype.h"

Bouton liste_bouton[5];
Texte explication;
Texte deplacement;
Texte bouleDeFeu1;
Texte bouleDeFeu2;
Panel background;
Panel textePanel;

int levelSelect;
int nbBouton;

SDL_bool quadrillageActive;

void initSelectDifficulty(void)
{
	setPrintSelectDifficulty(SDL_TRUE);

	nbBouton = 5;
	//Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
	if(getLangue() == 0)
	{
		liste_bouton[0] = createBouton(300, 275, 200, 50, NULL, getGris(255), "FACILE", getNoir(255), getFont1(), SDL_FALSE, 6);
		liste_bouton[1] = createBouton(300, 350, 200, 50, NULL, getGris(255), "MOYEN", getNoir(255), getFont1(), SDL_FALSE, 7);
		liste_bouton[2] = createBouton(300, 425, 200, 50, NULL, getGris(255), "DIFFICILE", getNoir(255), getFont1(), SDL_FALSE, 8);
		liste_bouton[3] = createBouton(250, 500, 300, 50, NULL, getGris(255), "QUADRILLAGE ON", getNoir(255), getFont1(), SDL_FALSE, 9);
		liste_bouton[4] = createBouton(50, 530, 150, 50, NULL, getGris(255), "RETOUR", getNoir(255), getFont1(), SDL_FALSE, 3);

		explication = createTexte(250, 200, 300, 50, "CHOIX DE DIFFICULTER", getNoir(255), getFont1());
		bouleDeFeu1 = createTexte(275, 50, 300, 50, "SI VOTRE SCORE ATTEINT 200", getRouge(255), getFont1());
		bouleDeFeu2 = createTexte(275, 75, 300, 50, "PRESSEZ ESPACE POUR CREER UNE EXPLOSION", getRouge(255), getFont1());
		deplacement = createTexte(275, 115, 300, 50, "UTILISER ZQSD POUR VOUS DEPLACEZ", getRouge(255), getFont1());
	}
	else if(getLangue() == 1)
	{
		liste_bouton[0] = createBouton(300, 275, 200, 50, NULL, getGris(255), "EASY", getNoir(255), getFont1(), SDL_FALSE, 6);
		liste_bouton[1] = createBouton(300, 350, 200, 50, NULL, getGris(255), "MEDIUM", getNoir(255), getFont1(), SDL_FALSE, 7);
		liste_bouton[2] = createBouton(300, 425, 200, 50, NULL, getGris(255), "HARD", getNoir(255), getFont1(), SDL_FALSE, 8);
		liste_bouton[3] = createBouton(250, 500, 300, 50, NULL, getGris(255), "QUADRILLAGE ON", getNoir(255), getFont1(), SDL_FALSE, 9);
		liste_bouton[4] = createBouton(50, 530, 150, 50, NULL, getGris(255), "RETURN", getNoir(255), getFont1(), SDL_FALSE, 3);

		explication = createTexte(250, 200, 300, 50, "CHOOSE A DIFFICULTY", getNoir(255), getFont1());
		bouleDeFeu1 = createTexte(275, 50, 300, 50, "IF YOUR SCORE >= 200", getRouge(255), getFont1());
		bouleDeFeu2 = createTexte(275, 75, 300, 50, "PRESS SPACE TO THROW FIREBALL", getRouge(255), getFont1());
		deplacement = createTexte(275, 115, 300, 50, "USE WASD TO MOVE", getRouge(255), getFont1());
	}
		background = createPanel(0, 0, 800, 600, "source/graphics/background2.png", getNoir(255), SDL_TRUE);
		textePanel = createPanel(75, 30, 700, 150, "source/graphics/bouton1.png", getNoir(255), SDL_TRUE);

	quadrillageActive = SDL_TRUE;
}

void updateSelectDifficulty(void)
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

void drawSelectDifficulty(void)
{
	drawTexture(background.sprite.texture, &background.sprite.dimension, NULL);
	drawTexture(textePanel.sprite.texture, &textePanel.sprite.dimension, NULL);
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
	drawTexture(explication.sprite.texture, &explication.sprite.dimension, NULL);
	drawTexture(bouleDeFeu1.sprite.texture, &bouleDeFeu1.sprite.dimension, NULL);
	drawTexture(bouleDeFeu2.sprite.texture, &bouleDeFeu2.sprite.dimension, NULL);	
	drawTexture(deplacement.sprite.texture, &deplacement.sprite.dimension, NULL);
}

void setSelectLevel(int level)
{
	levelSelect = level;
}

int getLevel(void)
{
	return levelSelect;
}

void changeQuadrillage(void)
{
	for(int j = 0; j < 3; j++)
	{
		if(liste_bouton[3].boutonTexture[j] != NULL)
		{	
			SDL_DestroyTexture(liste_bouton[3].boutonTexture[j]);
			liste_bouton[3].boutonTexture[j] = NULL;
		}
		if(liste_bouton[3].texte.sprite.texture != NULL)
		{
			SDL_DestroyTexture(liste_bouton[3].texte.sprite.texture);
			liste_bouton[3].texte.sprite.texture = NULL;
		}
	}

	if(quadrillageActive == SDL_TRUE)
	{
		quadrillageActive = SDL_FALSE;
		liste_bouton[3] = createBouton(250, 500, 300, 50, NULL, getGris(255), "QUADRILLAGE OFF", getNoir(255), getFont1(), SDL_FALSE, 9);
	}
	else if(quadrillageActive == SDL_FALSE)
	{
		quadrillageActive = SDL_TRUE;
		liste_bouton[3] = createBouton(250, 500, 300, 50, NULL, getGris(255), "QUADRILLAGE ON", getNoir(255), getFont1(), SDL_FALSE, 9);
	}
}

SDL_bool getQuadrillageActive(void)
{
	return quadrillageActive;
}

void cleanSelectDifficulty(void)
{
	setPrintSelectDifficulty(SDL_FALSE);

	SDL_Log("CLEAN SELECT DIFFICULTY EN COURS\n");
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

	if(textePanel.sprite.texture != NULL)
	{
		SDL_DestroyTexture(textePanel.sprite.texture);
		textePanel.sprite.texture = NULL;
	}
	if(background.sprite.texture != NULL)
	{
		SDL_DestroyTexture(background.sprite.texture);
		background.sprite.texture = NULL;
	}
	if(deplacement.sprite.texture != NULL)
	{
		SDL_DestroyTexture(deplacement.sprite.texture);
		deplacement.sprite.texture = NULL;
	}
	if(explication.sprite.texture != NULL)
	{
		SDL_DestroyTexture(explication.sprite.texture);
		explication.sprite.texture = NULL;
	}
	if(bouleDeFeu1.sprite.texture != NULL)
	{
		SDL_DestroyTexture(bouleDeFeu1.sprite.texture);
		bouleDeFeu1.sprite.texture = NULL;
	}
	if(bouleDeFeu2.sprite.texture != NULL)
	{
		SDL_DestroyTexture(bouleDeFeu2.sprite.texture);
		bouleDeFeu2.sprite.texture = NULL;
	}
	SDL_Log("CLEAN SELECT DIFFICULTY TERMINER\n");
}