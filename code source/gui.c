#include "prototype.h"

Panel createPanel(int x, int y, int w, int h, char *texture, SDL_Color color, SDL_bool pFill)
{
	Panel myPanel;
	if(texture == NULL)
	{
		myPanel.sprite.texture = NULL;
	}
	else
	{
		myPanel.sprite.texture = createTexture(texture, NULL);
	}

	myPanel.sprite.dimension.x = x * getScaleX();
	myPanel.sprite.dimension.y = y * getScaleY();
	myPanel.sprite.dimension.w = w * getScaleX();
	myPanel.sprite.dimension.h = h * getScaleY();
	myPanel.sprite.currentDirection = 0;
	myPanel.sprite.angle = 0;
	myPanel.couleur = color;
	myPanel.fill = pFill;

	return myPanel;
}

/*typedef struct 
{

	Sprite sprite;
	SDL_Rect tailleReel;
	SDL_Color couleur;
	SDL_bool empty;
	SDL_bool fill;

}Barre;*/

Barre createBarre(int x, int y, int w, int h, SDL_Color color)
{
	Barre myBarre;

	myBarre.sprite.texture = NULL;
	myBarre.sprite.dimension.x = x;
	myBarre.sprite.dimension.y = y;
	myBarre.sprite.dimension.w = w;
	myBarre.sprite.dimension.h = h;

	myBarre.couleur = color;
	myBarre.empty = SDL_FALSE;
	myBarre.fill = SDL_TRUE;
	myBarre.tailleReel = myBarre.sprite.dimension;

	return myBarre;
}

Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
{
	Texte myTexte;
	if(texte != NULL)
	{
		//int TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h)
		int width, height;

		if(TTF_SizeText(font, texte, &width, &height) != 0)
		{
			SDL_Log("IMPOSSIBLE DE PRENDRE SIZE TEXTE DANS CREATE TEXTE GUI : %s",TTF_GetError());
			exit(EXIT_FAILURE);
		}

		SDL_Surface *surface;

		surface = TTF_RenderText_Blended(font, texte, color);

		myTexte.sprite.texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
		SDL_FreeSurface(surface);
		surface = NULL;

		if(myTexte.sprite.texture == NULL)
		{
			SDL_Log("IMPOSSIBLE DE CRRER LA TEXTURE TEXTE :%s",SDL_GetError());
			exit(EXIT_FAILURE);
		}

		myTexte.sprite.dimension.x = (x + ((w - width) / 2)) * getScaleX();
		myTexte.sprite.dimension.y = (y + ((h - height) / 2)) * getScaleY();
		myTexte.sprite.dimension.w = width * getScaleX();
		myTexte.sprite.dimension.h = height * getScaleY();
		myTexte.sprite.angle = 0;
		myTexte.sprite.currentDirection = 0;
		myTexte.couleur = color;
	}

	return myTexte;
}

Bouton createBouton(int x, int y, int w, int h, char *panelTexture, SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event)
{
	Bouton myBouton;

	myBouton.panel = createPanel(x, y, w, h, NULL, panelColor, pFill);
	myBouton.texte = createTexte(x, y, w, h, ptexte, texteColor, font);
	myBouton.isHover = SDL_FALSE;
	myBouton.isPressed = SDL_FALSE;
	myBouton.alpha = panelColor.a;
	myBouton.event = event;
	myBouton.currentEtat = NONE;

	if(panelTexture == NULL)
	{
		char chemin1[100] = {"source/graphics/bouton1"};
		char chemin2[100] = {"source/graphics/bouton1"};
		char chemin3[100] = {"source/graphics/bouton1"};

		char *extension = ".png";

		char *hover = "Hover";
		char *pressed = "Pressed";

		strcat(chemin2, hover);
		strcat(chemin3, pressed);

		strcat(chemin1, extension);
		strcat(chemin2, extension);
		strcat(chemin3, extension);

		myBouton.boutonTexture[0] = createTexture(chemin1, NULL);
		myBouton.boutonTexture[1] = createTexture(chemin2, NULL);
		myBouton.boutonTexture[2] = createTexture(chemin3, NULL);
	}
	else
	{
		myBouton.boutonTexture[0] = createTexture(panelTexture, NULL);
		myBouton.boutonTexture[1] = createTexture(panelTexture, NULL);
		myBouton.boutonTexture[2] = createTexture(panelTexture, NULL);
	}
	return myBouton;
}