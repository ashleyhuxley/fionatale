#include "fiona.h"
#include "texture.h"
#include "log.h"
#include <string>
#include "sdl_helpers.h"
#include <SDL/SDL.h>
#include "timer.h"
#include "returnexception.h"

using namespace std;

Fiona::Fiona()
{
	hp = 20;
	canSpare = false;
}

void Fiona::drawMain()
{
	TexturePtr bg = texMgr.load("assets/bg.png");
	TexturePtr fen = texMgr.load("assets/fen.png");

	bg->applyTo(0, 0, screen);
	fen->applyTo(135, 3, screen);
}

bool Fiona::hit(int hpHit)
{
	SoundEffectPtr hit = sndMgr.load("assets/wav/hit.wav");
	hit->play();

	hp -= hpHit;

	Log("Player attacked FIONA. Fiona's HP is " + to_string(hp));

	if (hp <= 0)
	{
		die();
	}

	return hp > 0;
}

void Fiona::scremOut()
{
	TexturePtr bg = texMgr.load("assets/bg.png");
	TexturePtr fen = texMgr.load("assets/fen.png");

	int x = 135;
	int y = 3;

	Timer fps;

	while (y + 122 > 0)
	{
		fps.start();

		bg->applyTo(0, 0, screen);
		fen->applyTo(x, y, screen);

		x += 2;
		y -= 3;

		SDL_Flip(screen);

		if (fps.get_ticks() < (1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

	fen->applyTo(135, 3, screen);
}

void Fiona::die()
{
	TexturePtr bg = texMgr.load("assets/bg.png");
	TexturePtr particle = texMgr.load("assets/particle.png");
	TexturePtr fen = texMgr.load("assets/fen.png");

	SoundEffectPtr dust = sndMgr.load("assets/wav/dust.wav");

	bg->applyTo(0, 0, screen);

	int particles = 150;

	int x[particles];
	int y[particles];
	int v[particles];

	dust->play();

	for (int i = 0; i < particles; i++)
	{
		int xx = 0;
		int yy = 0;

		while (fen->isAlpha(xx, yy))
		{
			xx = rand() % 50;
			yy = rand() % 122;
		}

		x[i] = xx;
		y[i] = yy;

		v[i] = rand() % 5 + 1;

		particle->applyTo(x[i] + 135, y[i] + 3, screen);
	}

	SDL_Delay(2000);

	Timer time;
	Timer fps;

	time.start();

	while (time.get_ticks() < 3000)
	{
		fps.start();

		bg->applyTo(0, 0, screen);

		for (int j = 0; j < particles; j++)
		{
			y[j] -= v[j];
			particle->applyTo(x[j] + 135, y[j] + 3, screen);
		}

		SDL_Flip(screen);

		if (fps.get_ticks() < (1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}
}

void Fiona::slash()
{
	int delay = 60;

	TexturePtr slash = texMgr.load("assets/slash.png");
	TexturePtr bg = texMgr.load("assets/bg.png");
	TexturePtr fen = texMgr.load("assets/fen.png");

    SDL_Rect r;
    int x = 20;

    for (int i = 0; i < 6; i++)
    {
    	bg->applyTo(0, 0, screen);
		fen->applyTo(135, 3, screen);

    	switch (i)
    	{
    		case 0: r.x = 18; r.y = 48; r.w = 6; r.h = 8; x = 20; break;
    		case 1: r.x = 0; r.y = 44; r.w = 6; r.h = 24; x = 23; break;
    		case 2: r.x = 0; r.y = 0; r.w = 8; r.h = 44; x = 23; break;
    		case 3: r.x = 8; r.y = 0; r.w = 10; r.h = 66; x = 15; break;
    		case 4: r.x = 18; r.y = 0; r.w = 16; r.h = 34; x = 51; break;
    		case 5: r.x = 18; r.y = 34; r.w = 16; r.h = 14; x = 70; break;
    	}

	    slash->applyTo(157, x, screen, &r);
	    SDL_Flip(screen);
	    SDL_Delay(delay);
    }

    for (int i = 0; i < 10; i++)
    {
    	int ox = rand() % 6;
    	int oy = rand() % 6;

    	bg->applyTo(0, 0, screen);
		fen->applyTo(132 + ox, oy, screen);

		SDL_Flip(screen);
	    SDL_Delay(delay);
    }

    bg->applyTo(0, 0, screen);
	fen->applyTo(135, 3, screen);
}

void Fiona::spare()
{
	musMgr.playSpare();
	
	TexturePtr caramel = texMgr.load("assets/caramel.png");
	TexturePtr bg = texMgr.load("assets/sparebg.png");

	bool done = false;

	Timer fps;
	Timer animate;

	animate.start();

	int frame = 0;

	SDL_Rect r[5];

	for (int i = 0; i < 5; i++)
	{
		r[i].x = i * 170;
		r[i].y = 0;
		r[i].w = 170;
		r[i].h = 180;
	}

	SDL_Event event;

	while (!done)
	{
		fps.start();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				throw ReturnException();
			}

			Uint8 key = get_event(&event);

			if (key == NES_B)
			{
				done = true;
			}
		}

		bg->applyTo(0, 0, screen);

		frame = ((animate.get_ticks() / 100) % 8);
		if (frame == 7)
		{
			frame = 1;
		}
		else if (frame == 6)
		{
			frame = 2;
		}
		else if (frame == 5)
		{
			frame = 3;
		}

		caramel->applyTo(0, 60, screen, &r[frame]);
		SDL_Flip(screen);

		fps_delay(fps.get_ticks());
	}
}
