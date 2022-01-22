//gcc source/*.c -o bin\prog.exe -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lm
// "C:\Users\gauti\Desktop\projet C\projetB"

#include "prototype.h"

Input input;

int main(int argc, char* argv[])
{
	atexit(cleanUp);

	SDL_bool go = SDL_TRUE;

	Timer time;
	
	time.previousTime = SDL_GetTicks();
	time.ms = 1000;

	init();

	while(go)
	{
		time.currentTime = SDL_GetTicks();

		if(time.currentTime > (time.previousTime + time.ms / MAX_FPS))
		{
			time.previousTime = time.currentTime;
			update(&input);
			draw();

		}
	}

	exit(EXIT_SUCCESS);
}