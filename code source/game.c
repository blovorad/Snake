#include "prototype.h"

Panel panel1;
Texte texte1;
Texte scoreTexte;
int scoreAll[6];
SDL_bool hasNewHighScore;

Panel panel2;
Texte defaiteTexte;
Texte congratulationTexte;
Bouton defaiteBouton;

Timer timeTexteBouleFeu;

int score;

/*typedef struct 
{

	Uint32 previousTime;
	Uint32 currentTime;
	int ms;

}Timer;*/

void initGame(void)
{
	setPrintGame(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);

	score = 0;
	loadHighScore();

	initSnake();
	initGameGui();
	startMusic(0, SDL_FALSE);
}

void updateGame(Input *input)
{
	updateSnake(input);
	updateBouleDeFeu();

	//void addTrainer(int x, int y, int vie, int vx, int vy, SDL_Color couleur)
	//panel2 = createPanel(250, 100, 300, 250, NULL, getGris(100), SDL_TRUE);
	//int vx = rand() % 50 * cos(rand() % 360);
	//int vy = rand() % 50 * sin(rand() % 360);

	if(hasNewHighScore == SDL_TRUE)
	{
		playFx(7);
		int x, y, vx, vy;
		int whereX = rand() % 800;
		int whereY = rand() % 600;

		for(int i = 0; i < 100; i++)
		{
			int angle = rand() % 360;
			while(angle < 10)
			{
				angle = rand() % 360;
			}

			x = whereX;
			y = whereY;
			vx = rand() % 10 * cos(angle);
			vy = rand() % 10 * sin(angle);

			addTrainer(x, y, 1000, vx, vy, getBlanc(255));
		}
	}

	if(isBlock())
	{
		manageExitGame();
	}
	else if(isBlock() == SDL_FALSE)
	{
		if(input->space && score >= 200 && isActiveBouleDeFeu() == SDL_FALSE)
		{
			Vecteur vitesse = getSnakeVitesse();
			playFx(6);
			if(vitesse.x > 0)
			{
				initBouleDeFeu(getXPosSnake(0, TILE_SIZE) + 1, getYPosSnake(0, TILE_SIZE), vitesse);
			}
			else if(vitesse.x < 0)
			{
				initBouleDeFeu(getXPosSnake(0, TILE_SIZE) - 1, getYPosSnake(0, TILE_SIZE), vitesse);
			}
			else if(vitesse.y > 0)
			{
				initBouleDeFeu(getXPosSnake(0, TILE_SIZE), getYPosSnake(0, TILE_SIZE) + 1, vitesse);
			}
			else if(vitesse.y < 0)
			{
				initBouleDeFeu(getXPosSnake(0, TILE_SIZE), getYPosSnake(0, TILE_SIZE) - 1, vitesse);
			}
			addScore(-200);
		}
	}
}

void drawGame(void)
{
	drawMap();
	drawSnake();
	drawBouleDeFeu();
	drawGameGui();
}

void cleanGame(void)
{
	setPrintGame(SDL_FALSE);

	hasNewHighScore = SDL_FALSE;
	cleanSnake();
	cleanMap();
	cleanGameGui();
}

void loadHighScore(void)
{
	FILE *fichier = fopen("source/fichier/score.SCORE", "r");

	fscanf(fichier, "%d %d %d %d %d %d", &scoreAll[0], &scoreAll[1], &scoreAll[2], &scoreAll[3], &scoreAll[4], &scoreAll[5]);

	fclose(fichier);
	fichier = NULL;
}

void saveHighScore(void)
{
	FILE *fichier = fopen("source/fichier/score.SCORE", "w");

	fprintf(fichier, "%d %d %d %d %d %d", scoreAll[0], scoreAll[1], scoreAll[2], scoreAll[3], scoreAll[4], scoreAll[5]);

	fclose(fichier);
	fichier = NULL;
}

void activeEnd(void)
{
	playFx(5);
	startMusic(4, SDL_TRUE);
	SDL_ShowCursor(SDL_ENABLE);
	hasNewHighScore = SDL_FALSE;

	int level = getLevel();

	if(level == 1)
	{
		if(score > scoreAll[1])
		{
			scoreAll[1] = score;
			hasNewHighScore = SDL_TRUE;
		}
	}
	else if(level == 2)
	{
		if(score > scoreAll[3])
		{
			scoreAll[3] = score;
			hasNewHighScore = SDL_TRUE;
		}
	}
	else if(level == 3)
	{
		if(score > scoreAll[5])
		{
			scoreAll[5] = score;
			hasNewHighScore = SDL_TRUE;
		}
	}

	if(hasNewHighScore == SDL_TRUE)
	{
		if(getLangue() == 0)
		{
			defaiteTexte = createTexte(300, 150, 200, 50, "FELICITATION !", getRouge(255), getFont1());
			congratulationTexte = createTexte(300, 175, 200, 50, "NOUVEAU RECORD", getRouge(255), getFont1());
		}
		else if(getLangue() == 1)
		{
			defaiteTexte = createTexte(300, 150, 200, 50, "CONGRATULATION !", getRouge(255), getFont1());
			congratulationTexte = createTexte(300, 175, 200, 50, "NEW RECORD", getRouge(255), getFont1());
		}
	}
	
	if(scoreTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(scoreTexte.sprite.texture);
		scoreTexte.sprite.texture = NULL;
	}
	
	char myScoreTexte[3];
	sprintf (myScoreTexte, "%d", score);

	scoreTexte = createTexte(425, 225, 50, 50, myScoreTexte, getRouge(255), getFont1());

	if(texte1.sprite.texture != NULL)
	{
		SDL_DestroyTexture(texte1.sprite.texture);
		texte1.sprite.texture = NULL;
	}

	texte1 = createTexte(325, 225, 50, 50, "SCORE:", getRouge(255), getFont1());
	cleanFx();
}

void manageExitGame(void)
{
	int mX = getMouseX();
	int mY = getMouseY();

	int x = defaiteBouton.panel.sprite.dimension.x;
	int y = defaiteBouton.panel.sprite.dimension.y;
	int w = defaiteBouton.panel.sprite.dimension.w;
	int h = defaiteBouton.panel.sprite.dimension.h;

	if(mX > x && mX < x + w && mY > y && mY < y + h)
	{
		if(defaiteBouton.isHover == SDL_FALSE)
		{
			defaiteBouton.isHover = SDL_TRUE;
			defaiteBouton.currentEtat = HOVER;
			defaiteBouton.panel.couleur = getBleu(defaiteBouton.alpha);
		}
	}
	else
	{
		if(defaiteBouton.isHover == SDL_TRUE)
		{
			defaiteBouton.isHover = SDL_FALSE;
			defaiteBouton.currentEtat = NONE;
			defaiteBouton.panel.couleur = getMarron(defaiteBouton.alpha);
		}
	}

	if(defaiteBouton.isHover == SDL_TRUE && defaiteBouton.isPressed == SDL_FALSE && 
		getStateOfLeftButton() == SDL_TRUE && getStateOfOldLeftButton() == SDL_FALSE)
	{
		defaiteBouton.isPressed = SDL_TRUE;
		defaiteBouton.currentEtat = PRESSED;
		defaiteBouton.panel.couleur = getMarron(defaiteBouton.alpha);
		playEvent(defaiteBouton.event);
	}
	else
	{
		if(defaiteBouton.isPressed == SDL_TRUE && getStateOfLeftButton() == SDL_FALSE)
		{
			defaiteBouton.isPressed = SDL_FALSE;
			defaiteBouton.currentEtat = NONE;
			defaiteBouton.panel.couleur = getMarron(defaiteBouton.alpha);
		}
	}

	actualiseOldLeftButton();
}


void addScore(int pScore)
{
	//createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
	if(scoreTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(scoreTexte.sprite.texture);
		scoreTexte.sprite.texture = NULL;
	}
	
	score += pScore;
	char myScoreTexte[3];
	sprintf (myScoreTexte, "%d", score);

	scoreTexte = createTexte(270, 580, 50, 20, myScoreTexte, getRouge(255), getFont1());
}

void initGameGui()
{
	char myScoreTexte[10];
	sprintf (myScoreTexte, "%d", score);

	panel1 = createPanel(0, 575, 800, 50, NULL, getGris(50), SDL_TRUE);
	texte1 = createTexte(100, 580, 200, 20, "SCORE:", getRouge(255), getFont1());
	scoreTexte = createTexte(270, 580, 50, 20, myScoreTexte, getRouge(255), getFont1());

	if(getLangue() == 0)
	{
		defaiteTexte = createTexte(300, 150, 200, 50, "DOMMAGE...", getRouge(255), getFont1());
		defaiteBouton = createBouton(300, 275, 200, 50, NULL, getGris(150), "QUITTER", getNoir(255), getFont1(), SDL_TRUE, 4);
	}
	else if(getLangue() == 1)
	{
		defaiteTexte = createTexte(300, 150, 200, 50, "OH NOO...", getRouge(255), getFont1());
		defaiteBouton = createBouton(300, 275, 200, 50, NULL, getGris(150), "EXIT", getNoir(255), getFont1(), SDL_TRUE, 4);
	}

	panel2 = createPanel(250, 100, 300, 250, NULL, getGris(100), SDL_TRUE);
}
//Bouton createBouton(int x, int y, int w, int h, SDL_Texture *panelTexture, SDL_Color panelColor, char *ptexte, SDL_Color texteColor, TTF_Font *font, SDL_bool pFill, int event)

void drawGameGui()
{

	if(isBlock())
	{
		drawRect(&panel2.sprite.dimension, &panel2.fill, &panel2.couleur);
		drawTexture(defaiteTexte.sprite.texture, &defaiteTexte.sprite.dimension, NULL);

		if(hasNewHighScore == SDL_TRUE)
		{
			drawTexture(congratulationTexte.sprite.texture, &congratulationTexte.sprite.dimension, NULL);
		}

		int current = defaiteBouton.currentEtat;
		if(defaiteBouton.boutonTexture == NULL)
		{
			drawRect(&defaiteBouton.panel.sprite.dimension, &defaiteBouton.panel.fill, &defaiteBouton.panel.couleur);
		}
		else
		{
			drawTexture(defaiteBouton.boutonTexture[current], &defaiteBouton.panel.sprite.dimension, NULL);
		}
		if(defaiteBouton.texte.sprite.texture != NULL)
		{
			drawTexture(defaiteBouton.texte.sprite.texture, &defaiteBouton.texte.sprite.dimension, NULL);
		}
	}

	drawRect(&panel1.sprite.dimension, &panel1.fill, &panel1.couleur);
	drawTexture(texte1.sprite.texture, &texte1.sprite.dimension, NULL);
	drawTexture(scoreTexte.sprite.texture, &scoreTexte.sprite.dimension, NULL);
}

void cleanGameGui()
{	
	saveHighScore();
	cleanBouleDeFeu();
	cleanFx();

	for(int i = 0; i < 3; i++)
	{
		if(panel1.sprite.texture != NULL)
		{
			SDL_DestroyTexture(panel1.sprite.texture);
			panel1.sprite.texture = NULL;
		}
		if(defaiteBouton.boutonTexture[i] != NULL)
		{
			SDL_DestroyTexture(defaiteBouton.boutonTexture[i]);
			defaiteBouton.boutonTexture[i] = NULL;
		}
	}

	if(congratulationTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(congratulationTexte.sprite.texture);
		congratulationTexte.sprite.texture = NULL;
	}
	if(texte1.sprite.texture != NULL)
	{
		SDL_DestroyTexture(texte1.sprite.texture);
		texte1.sprite.texture = NULL;
	}
	if(scoreTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(scoreTexte.sprite.texture);
		scoreTexte.sprite.texture = NULL;
	}
	if(defaiteBouton.texte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(defaiteBouton.texte.sprite.texture);
		defaiteBouton.texte.sprite.texture = NULL;
	}
	if(defaiteTexte.sprite.texture != NULL)
	{
		SDL_DestroyTexture(defaiteTexte.sprite.texture);
		defaiteTexte.sprite.texture = NULL;
	}
}
//drawTexture(SDL_Texture *texture, SDL_Rect *dst, SDL_Rect *src)
//drawRect(SDL_Rect *r, SDL_bool *fill, SDL_Color *couleur)
//Texte createTexte(int x, int y, int w, int h, char *texte, SDL_Color color, TTF_Font *font)
//createPanel(int x, int y, int w, int h, SDL_Texture *texture, SDL_Color color)