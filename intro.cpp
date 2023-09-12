#include "intro.h"
#include "returnexception.h"
#include "texture.h"
#include <SDL/SDL.h>
#include "fionatale.h"
#include "sdl_helpers.h"
#include <cmath>
#include "timer.h"
#include <vector>
#include <algorithm>

using namespace std;

Intro::Intro()
{
	play_o = texMgr.getText("[ Press START ]", FT_COLOUR_ORANGE);
	play_w = texMgr.getText("[ Press START ]", FT_COLOUR_WHITE);
}

Intro::~Intro()
{
	SDL_FreeSurface(play_o);
	SDL_FreeSurface(play_w);
}

bool Intro::processEvents()
{
	SDL_Event event;

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
				return true;
		}
	}

	return false;
}

void Intro::play()
{
	musMgr.playIntro();

	TexturePtr title = texMgr.load("assets/title.png");

	bool quit = false;
	int item = 0;

	while (quit == false)
	{
		quit = processEvents();

		switch (item)
		{
			case 0: quit = drawTitle(); break;
			case 2: quit = drawCredits(); break;
			case 3: quit = drawCf(); break;
			case 4: quit = drawPlay(); break;
		}

	
		item++;

		if (item == 4)
		{
			item = 0;
		}
	}

	musMgr.stop();
}

bool Intro::drawCredits()
{
	return false;
}

bool Intro::drawCf()
{
	SDL_Surface *temp = SDL_DisplayFormat(screen);
	SDL_BlitSurface(screen, NULL, temp, NULL);

	for (int i = 0; i < 256; i++)
	{
		SDL_SetAlpha( temp, SDL_SRCALPHA, 255 - i);
		clear_screen(screen);
		apply_surface(0, 0, temp, screen);
		SDL_Flip(screen);
		SDL_Delay(3);
	}

	SDL_FreeSurface(temp);

	TexturePtr cf = texMgr.load("assets/cf.png");

	Timer tick;
	Timer fps;

	tick.start();

	SDL_Rect r1;
	SDL_Rect r2;
	r1.x = 0; r1.y = 0; r1.w = 320; r1.h = 162;
	r2.x = 0; r2.y = 163; r2.w = 320; r2.h = 162;

	while (tick.get_ticks() < 5000)
	{
		fps.start();

		if (processEvents())
		{
			return true;
		}

		if ((tick.get_ticks() / 500) % 2 == 0)
		{
			cf->applyTo(0, 30, screen, &r1);
			apply_surface(160 - (play_o->w / 2), 210, play_o, screen);
		}
		else
		{
			cf->applyTo(0, 30, screen, &r2);
			apply_surface(160 - (play_w->w / 2), 210, play_w, screen);
		}

		SDL_Flip(screen);

		fps_delay(fps.get_ticks());
	}

	return false;
}

bool Intro::drawPlay()
{
	return false;
}

bool Intro::drawTitle()
{
	TexturePtr title = texMgr.load("assets/title.png");

	bool quit = false;
	SDL_Event event;

	Timer t;

	std::vector<int> tiles;
	for (int i = 0; i < 193; ++i) tiles.push_back(i); 

	random_shuffle(tiles.begin(), tiles.end());

  	for (vector<int>::iterator it = tiles.begin(); it != tiles.end(); ++it)
  	{
		int x = (*it % 16) * 20;
		int y = floor(*it / 16) * 20;

		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = 20;
		rect.h = 20;

		title->applyTo(x, y, screen, &rect);
		
		SDL_Flip(screen);

		SDL_Delay(5);
	}

	Timer delay;
	Timer fps;
	delay.start();

	while (delay.get_ticks() < 4000)
	{
		fps.start();

		if ((delay.get_ticks() / 500) % 2 == 0)
		{
			apply_surface(160 - (play_o->w / 2), 210, play_o, screen);
		}
		else
		{
			apply_surface(160 - (play_w->w / 2), 210, play_w, screen);
		}

		SDL_Flip(screen);

		if (processEvents())
		{
			return true;
		}

		fps_delay(fps.get_ticks());
	}

	return false;
}
