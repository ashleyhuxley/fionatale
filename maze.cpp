#include "maze.h"
#include "timer.h"
#include "soul.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include <SDL/SDL.h>

Maze::Maze()
{

}

bool Maze::fight()
{
	Soul soul;

	bool done = false;

	animate_hitbox(screen);

	SDL_Surface *temp = SDL_DisplayFormat(screen);
	SDL_BlitSurface(screen, NULL, temp, NULL);

	Timer fps;
	Timer animate;
	Timer coolOff;

	animate.start();

	SDL_Event event;

	while (!done)
	{
		fps.start();



		fps_delay(fps.get_ticks());
	}
}
