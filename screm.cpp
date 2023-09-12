#include "screm.h"
#include "soul.h"
#include "timer.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "returnexception.h"
#include <cmath>
#include "log.h"

Screm::Screm()
{
	
}

bool Screm::fight()
{
	TexturePtr bluea = texMgr.load("assets/bluea.png");
	TexturePtr orangea = texMgr.load("assets/orangea.png");

	Soul soul;

	int speed = 5000;
	if (Game::current.player.usedHounds)
	{
		speed = 3000;
	}

	animate_hitbox(screen);

	SDL_Surface *temp = SDL_DisplayFormat(screen);
	SDL_BlitSurface(screen, NULL, temp, NULL);

	bool done = false;

	Timer fps;
	Timer animate;
	Timer coolOff;

	animate.start();

	SDL_Event event;

	const int screms = 5;

	int x[screms];
	int y[screms];
	bool c[screms];

	for (int i = 0; i < screms; i++)
	{
		x[i] = 0; y[i] = 0;
		c[i] = (rand() % 2 == 0);
	}

	const double f = 30;

	while (!done)
	{
		fps.start();

		while( SDL_PollEvent( &event ) )
		{
			if(event.type == SDL_QUIT)
			{
				throw ReturnException();
			}

			soul.handle_input(&event);
		}

		soul.move();

		apply_surface(0, 0, temp, screen);

		for (int p = 0; p < screms; p++)
		{
			x[p] = (animate.get_ticks() / (speed / 320)) - (p * (bluea->width() + 28));

			y[p] = 163 + (16 * sin(0.18 * x[p])) - (bluea->height() / 2);

			if (x[screms - 1] > 200)
			{
				done = true;
			}

			if (c[p])
			{
				bluea->applyTo(x[p], y[p], screen);
			}
			else
			{
				orangea->applyTo(x[p], y[p], screen);
			}

			if (!coolOff.is_started())
			{
				if (soul.hasCollidedWith(bluea, x[p], y[p]))
				{
					bool moving = soul.isMoving();
					bool blue = c[p];

					if ((blue && moving) || (!blue && !moving))
					{
						Log("Fiona screeched at the player.");

						int hp = 4;
						if (Game::current.player.usedHounds)
						{
							hp = 8;
						}

						if (!Game::current.player.hit(hp))
						{
							Log("The player died.");
							soul.die();
							return false;
						}
						
						coolOff.start();
					}
				}

				soul.show();
			}
			else
			{
				if (coolOff.get_ticks() > 1000)
				{
					coolOff.stop();
				}

				if ((coolOff.get_ticks() / 100) % 2 == 0)
				{
					soul.show();
				}
			}
		}

		Game::current.player.displayHp();
		SDL_Flip(screen);

		fps_delay(fps.get_ticks());
	}

	apply_surface(0, 0, temp, screen);
	Game::current.player.displayHp();
	SDL_Flip(screen);
	return true;
}
