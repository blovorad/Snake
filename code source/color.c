#include "prototype.h"

SDL_Color getBlanc(int alpha)
{
	SDL_Color blanc = {255,255,255,alpha};
	return blanc;
}

SDL_Color getRouge(int alpha)
{
	SDL_Color rouge = {255,0,0,alpha};
	return rouge;
}

SDL_Color getBleu(int alpha)
{
	SDL_Color bleu = {0,0,255,alpha};
	return bleu;
}

SDL_Color getVert(int alpha)
{
	SDL_Color vert = {0,255,0,alpha};
	return vert;
}

SDL_Color getVertFoncer(int alpha)
{
	SDL_Color vert = {0,100,0,alpha};
	return vert;
}

SDL_Color getGris(int alpha)
{
	SDL_Color gris = {100,100,100,alpha};
	return gris;
}

SDL_Color getJaune(int alpha)
{
	SDL_Color jaune = {255, 255, 0, alpha};
	return jaune;
}

SDL_Color getNoir(int alpha)
{
	SDL_Color noir = {0,0,0,alpha};
	return noir;
}

SDL_Color getMarron(int alpha)
{
	SDL_Color marron = {100,41,0,alpha};
	return marron;
}