#include "soul.h"
#include "fionatale.h"
#include "timer.h"
#include <tgmath.h>
#include "texttyper.h"
#include "returnexception.h"
#include "sdl_helpers.h"
#include "game.h"
#include <SDL/SDL.h>

using namespace std;

Soul::Soul()
{
	x = 33;
	y = 33;
	xVel = 0;
	yVel = 0;

	soul = texMgr.load("assets/heart8.png");
}

bool Soul::isMoving()
{
	return (xVel != 0) || (yVel != 0);
}

void Soul::handle_input(SDL_Event *event)
{
	if(event->type == SDL_KEYDOWN )
	{
		switch( event->key.keysym.sym )
		{
			case SDLK_UP: yVel -= soul->height() / 2; break;
			case SDLK_DOWN: yVel += soul->height() / 2; break;
			case SDLK_LEFT: xVel -= soul->width() / 2; break;
			case SDLK_RIGHT: xVel += soul->width() / 2; break;	
		}
	}
	else if(event->type == SDL_KEYUP)
	{
		switch( event->key.keysym.sym )
		{
			case SDLK_UP: yVel += soul->height() / 2; break;
			case SDLK_DOWN: yVel -= soul->height() / 2; break;
			case SDLK_LEFT: xVel += soul->width() / 2; break;
			case SDLK_RIGHT: xVel -= soul->width() / 2; break;   
		}		
	}
	else if (event->type == SDL_JOYAXISMOTION)
	{
		if( event->jaxis.axis == 0 )
		{
			if( ( event->jaxis.value > -8000 ) && ( event->jaxis.value < 8000 ) )
			{
				xVel = 0;
			}
			else
			{
				if( event->jaxis.value < 0 )
				{
					xVel = -soul->width() / 2;
				}
				else
				{
					xVel = soul->width() / 2;
				}
			}
		}
		else if( event->jaxis.axis == 1 )
		{
			if( ( event->jaxis.value > -8000 ) && ( event->jaxis.value < 8000 ) )
			{
				yVel = 0;
			}
			else
			{
				if( event->jaxis.value < 0 )
				{
					yVel = -soul->height() / 2;
				}
				else
				{
					yVel = soul->height() / 2;
				}
			}
		}
	}
}

void Soul::move()
{
	x += xVel;
	
	if( ( x + soul->width() > 66 ) )
	{
		x = 66 - soul->width();	
	}

	if (x < 0)
	{
		x = 0;
	}
	
	y += yVel;
	
	if( ( y + soul->height() > 66 ) )
	{
		y = 66 - soul->height();	
	}

	if (y < 0)
	{
		y = 0;
	}
}

void Soul::show()
{
	soul->applyTo( OFFSET_X + x, OFFSET_Y + y, screen );
}

bool Soul::hasCollidedWith(TexturePtr tex, int tx, int ty)
{
	int sx = x + OFFSET_X;
	int sy = y + OFFSET_Y;

	int x1 = max(sx, tx);
	int y1 = max(sy, ty);
	int x2 = min(sx + soul->width() - 1, tx + tex->width() - 1);
	int y2 = min(sy + soul->height() - 1, ty + tex->height() - 1);

	if ((x1 >= x2) || (y1 >= y2))
	{
		return false;
	}

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			bool texAlpha = tex->isAlpha(x - tx, y - ty);
			bool soulAlpha = soul->isAlpha(x - sx, y - sy);

			if (!texAlpha && !soulAlpha)
			{
				return true;
			}
		}
	}

	return false;
}

bool Soul::hasCollidedWith(SDL_Surface *tex, int tx, int ty)
{
	int sx = x + OFFSET_X;
	int sy = y + OFFSET_Y;

	int x1 = max(sx, tx);
	int y1 = max(sy, ty);
	int x2 = min(sx + soul->width() - 1, tx + tex->w - 1);
	int y2 = min(sy + soul->height() - 1, ty + tex->h - 1);

	if ((x1 >= x2) || (y1 >= y2))
	{
		return false;
	}

	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			bool texAlpha = is_alpha(tex, x - tx, y - ty);
			bool soulAlpha = soul->isAlpha(x - sx, y - sy);

			if (!texAlpha && !soulAlpha)
			{
				return true;
			}
		}
	}

	return false;
}

void Soul::die()
{
	musMgr.stop();

	SoundEffectPtr soulSplit = sndMgr.load("assets/wav/soul-split.wav");
	SoundEffectPtr soulShatter = sndMgr.load("assets/wav/soul-shatter.wav");

	int sx = x + OFFSET_X;
	int sy = y + OFFSET_Y;

	TexturePtr soul_die = texMgr.load("assets/soul-break.png");
	TexturePtr bits = texMgr.load("assets/shards.png");

	SDL_Rect r[4];
	r[0].x = 0; r[0].y = 0; r[0].w = 7; r[0].h = 7;
	r[1].x = 8; r[1].y = 0; r[1].w = 6; r[1].h = 5;
	r[2].x = 0; r[2].y = 8; r[2].w = 7; r[2].h = 7;
	r[3].x = 8; r[3].y = 8; r[3].w = 6; r[3].h = 5;

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;

	SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

	soulSplit->play();
	soul_die->applyTo(sx, sy, screen);

	SDL_Flip(screen);

	Timer t;
	t.start();
	while (t.get_ticks() < 2000) {}

	bool done = false;
	Timer animate;
	Timer fps;

	animate.start();

	int bx[2];
	int by[2];

	double a[2];
	double b[2];

	a[0] = 30;
	b[0] = 50;

	a[1] = 30;
	b[1] = 10;

	int ri = 0;

	soulShatter->play();

	while (!done)
	{
		fps.start();

		SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

		ri = (animate.get_ticks() / 150) % 4;

		for (int i = 0; i < 2; i++)
		{
			bx[i] = animate.get_ticks() / (1000 / 160) - a[i];
			by[i] = (b[i] / a[i]) * sqrt((a[i] * a[i]) - (bx[i] - a[i] * bx[i] - a[i])) * -1;

			bits->applyTo(bx[i] + sx + a[i], by[i] + sy, screen, &r[ri]);
			bits->applyTo(sx - (bx[i] + a[i]), by[i] + sy, screen, &r[ri]);
		}

		SDL_Flip(screen);

		if (bx[0] + sx > 320 && bx[1] + sx > 320)
		{
			done = true;
		}

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	musMgr.playDead();

	TexturePtr gameover = texMgr.load("assets/game-over.png");
	gameover->applyTo(0, 0, screen);
	SDL_Flip(screen);

	TextTyper typer;
	typer.type("You cannot give up just yet...", "", false);
	SDL_Delay(1000);
	typer.type(Game::current.player.getName() + "!", "Stay determined...", false);

	done = false;

	SDL_Event event;

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				throw ReturnException();
			}

			Uint8 key = get_event(&event);

			switch (key)
			{
				case NES_START:
				case NES_A:
				case NES_B:
					done = true;
					break;
			}
		}
	}
}
