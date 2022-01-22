#ifndef __STRUCTURE__H__
#define __STRUCTURE__H__

#include "define.h"

enum direction
{
	HAUT,
	BAS,
	GAUCHE,
	DROITE
};

enum boutonEtat
{
	NONE,
	HOVER,
	PRESSED
};

typedef struct 
{

	int x, y;

}Vecteur;

typedef struct 
{
	
	SDL_Texture *texture;
	SDL_Rect dimension;
	int currentDirection;
	int angle;

}Sprite;

typedef struct 
{

	int previousTime;
	int currentTime;
	int ms;

}Timer;

typedef struct 
{

	Sprite sprite;
	SDL_Color couleur;
	SDL_bool fill;
	int number;

}Tile;

typedef struct 
{
	
	Tile **layer1;
	Tile **layer2;
	int width, height;

}Map;

typedef struct 
{
	
	Tile **layer1;
	SDL_bool active;

}Quadrillage;

typedef struct 
{
	
	Sprite partieCorps[DIM_SNAKE];
	SDL_bool direction[4];
	Vecteur vitesse;
	Timer movingTimer;
	int nbPartis;
	int angle;

}Snake;

typedef struct 
{
	
	Vecteur vitesse;
	Timer lifeRemaning;
	SDL_Point coordonner;
	SDL_Color couleur;
	SDL_bool used;

}Point;

typedef struct 
{

	SDL_bool z,s,q,d,space;

}Input;

typedef struct 
{

	int x1,y1,x2,y2;
	Vecteur vitesse;
	int startX, startY;	
	int angle;

}Ligne;

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

}Panel;

typedef struct 
{
	
	Panel panel;
	Texte texte;
	SDL_bool isHover, isPressed;
	SDL_Texture *boutonTexture[3];
	int currentEtat;
	int alpha;
	int event;

}Bouton;

typedef struct 
{
	
	SDL_bool rightButton, leftButton;
	SDL_bool oldRightButton, oldLeftButton;
	int x, y;

}Mouse;

typedef struct 
{
	
	SDL_bool isPlaying;
	Mix_Chunk *fx;
	Mix_Music *music;

}Sound;

typedef struct 
{

	Sprite sprite;
	SDL_Color couleur;

}Background;

typedef struct 
{
	
	Sprite sprite;
	Vecteur vitesse;
	Timer moving;
	SDL_bool isActive;

}Boule;

typedef struct 
{

	Sprite sprite;
	SDL_Rect tailleReel;
	SDL_Color couleur;
	SDL_bool empty;
	SDL_bool fill;

}Barre;

#endif