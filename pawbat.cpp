#include "pawbat.h"
#include "soul.h"
#include "sdl_helpers.h"
#include "fionatale.h"
#include "timer.h"
#include "returnexception.h"
#include "game.h"
#include "log.h"

Pawbat::Pawbat()
{

}

bool Pawbat::fight()
{
	Soul soul;

	animate_hitbox(screen);

	SDL_Surface *temp = SDL_DisplayFormat(screen);
	SDL_BlitSurface(screen, NULL, temp, NULL);

	TexturePtr paw = texMgr.load("assets/paw.png");

	bool done = false;

	SDL_Event event;

	Timer fps;
	Timer animate;
	Timer coolOff;

	animate.start();

	int speed = 600;
	int delay = 1400;

	if (Game::current.player.usedHounds)
	{
		speed = 400;
		delay = 1000;
	}

	int bat = 3;

	int sides[bat];

	for (int i = 0; i < bat + 1; i++)
	{
		sides[i] = rand() % 2 == 0;
	}

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

		Game::current.player.displayHp();

		SDL_Rect area;
		area.x = 0;
		area.y = 128;
		area.w = 320;
		area.h = 70;
		SDL_FillRect( screen, &area, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

		draw_rect( screen, 125, 128, 70, 70, 2 );

		int x;
		int y;

		double side = 0.04;
		if (sides[bat])
		{
			side *= -1;
		}

		if (animate.get_ticks() < delay)
		{
			y = 1 / (speed / 66) - 43;
		}
		else
		{
			y = (animate.get_ticks() - delay) / (speed / 86) - 33;
		}

		x = side * (y * y);

		int px = x + 140;
		int py = y + 145;

		if (animate.get_ticks() > (delay / 2))
		{
			paw->applyTo(px, py, screen);
		}

		if (!coolOff.is_started())
		{
			if (soul.hasCollidedWith(paw, px, py))
			{
				int hp = 4;
				if (Game::current.player.usedHounds)
				{
					hp = 8;
				}

				Log("Fiona pawbatted the player.");
				if (!Game::current.player.hit(hp))
				{
					Log("The player died.");
					soul.die();
					return false;
				}
				
				coolOff.start();
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

		if (animate.get_ticks() > (speed + delay))
		{
			bat--;
			animate.start();
			if (bat == 0)
			{
				done = true;
			}
		}

		SDL_Flip(screen);

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	apply_surface(0, 0, temp, screen);
	Game::current.player.displayHp();
	SDL_Flip(screen);

	SDL_FreeSurface(temp);

	return true;
}
