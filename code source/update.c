#include "prototype.h"

void update(Input *input)
{
	getMousePos();
	getInput(input);
	updateAudio();

	updateTrainer();

	if(isActiveGame())
	{
		updateGame(input);
	}
	if(isActiveMainMenu())
	{
		updateMainMenu();
	}
	if(isActiveOption())
	{
		updateOption();
	}
	if(isActiveSelectDifficulty())
	{
		updateSelectDifficulty();
	}
}