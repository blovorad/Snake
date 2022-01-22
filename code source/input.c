#include "prototype.h"

//CATALOGUE DES INPUTS ASSEZ CLAIR A LA LECTURE
void getInput(Input *input)
{
	SDL_Event event;
	if(getLangue() == 0)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT :
					exit(EXIT_SUCCESS);
					break;
					
				case SDL_MOUSEBUTTONDOWN :
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						actualiseLeftButton(SDL_TRUE);
					}
					if(event.button.button == SDL_BUTTON_RIGHT)
					{
						actualiseRightButton(SDL_TRUE);
					}
					break;

				case SDL_MOUSEBUTTONUP :
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						actualiseLeftButton(SDL_FALSE);
					}
					if(event.button.button == SDL_BUTTON_RIGHT)
					{
						actualiseRightButton(SDL_FALSE);
					}
					break;
					
				case SDL_KEYDOWN :
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						//exit(EXIT_SUCCESS);
					}
					if(event.key.keysym.sym == SDLK_z)
					{
						input->z = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_s)
					{
						input->s = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_q)
					{
						input->q = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_d)
					{
						input->d = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						input->space = SDL_TRUE;
					}
					break;

				case SDL_KEYUP :
					if(event.key.keysym.sym == SDLK_z)
					{
						input->z = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_s)
					{
						input->s = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_q)
					{
						input->q = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_d)
					{
						input->d = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						input->space = SDL_FALSE;
					}
					break;

				default :
					break;
			}
		}
	}
	else if(getLangue() == 1)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT :
					exit(EXIT_SUCCESS);
					break;
					
				case SDL_MOUSEBUTTONDOWN :
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						actualiseLeftButton(SDL_TRUE);
					}
					if(event.button.button == SDL_BUTTON_RIGHT)
					{
						actualiseRightButton(SDL_TRUE);
					}
					break;

				case SDL_MOUSEBUTTONUP :
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						actualiseLeftButton(SDL_FALSE);
					}
					if(event.button.button == SDL_BUTTON_RIGHT)
					{
						actualiseRightButton(SDL_FALSE);
					}
					break;
					
				case SDL_KEYDOWN :
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						//exit(EXIT_SUCCESS);
					}
					if(event.key.keysym.sym == SDLK_w)
					{
						input->z = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_s)
					{
						input->s = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_a)
					{
						input->q = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_d)
					{
						input->d = SDL_TRUE;
					}
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						input->space = SDL_TRUE;
					}
					break;

				case SDL_KEYUP :
					if(event.key.keysym.sym == SDLK_w)
					{
						input->z = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_s)
					{
						input->s = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_a)
					{
						input->q = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_d)
					{
						input->d = SDL_FALSE;
					}
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						input->space = SDL_FALSE;
					}
					break;

				default :
					break;
			}
		}
	}
}