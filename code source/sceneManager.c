#include "prototype.h"

SDL_bool printMainMenu;
SDL_bool printGame;
SDL_bool printOption;
SDL_bool printSelectDifficulty;

void initSceneManager(void)
{
	printMainMenu = SDL_FALSE;
	printGame = SDL_FALSE;
	printOption = SDL_FALSE;
	printSelectDifficulty = SDL_FALSE;
}

SDL_bool isActiveOption(void)
{
	return printOption;
}

SDL_bool isActiveMainMenu(void)
{
	return printMainMenu;
}

SDL_bool isActiveGame(void)
{
	return printGame;
}

SDL_bool isActiveSelectDifficulty(void)
{
	return printSelectDifficulty;
}

void setPrintSelectDifficulty(SDL_bool active)
{
	printSelectDifficulty = active;
}

void setPrintOption(SDL_bool active)
{
	printOption = active;
}

void setPrintMainMenu(SDL_bool active)
{
	printMainMenu = active;
}

void setPrintGame(SDL_bool active)
{
	printGame = active;
}
