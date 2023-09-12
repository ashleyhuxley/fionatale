#include "mercy.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include "timer.h"
#include "log.h"
#include "returnexception.h"
#include "game.h"

using namespace std;

MercyAction::MercyAction()
{

}

void MercyAction::draw(bool canSpare)
{
	SDL_Surface *runLabel = texMgr.getText("Flee", FT_COLOUR_WHITE);
	SDL_Surface *spareLabel = texMgr.getText("Spare", FT_COLOUR_YELLOW);

	TexturePtr heart = texMgr.load("assets/heart8.png");

	draw_rect(screen, 5, 128, 310, 70, 2);

	apply_surface(40, 133, runLabel, screen);

	if (canSpare)
	{
		apply_surface(40, 151, spareLabel, screen);
	}

	switch (action)
	{
		case MA_RUN:
			heart->applyTo(12, 138, screen);
			break;
		case MA_SPARE:
			heart->applyTo(12, 156, screen);
			break;
	}
	
	SDL_Flip(screen);

	SDL_FreeSurface(runLabel);
	SDL_FreeSurface(spareLabel);
}

MercyActionResult MercyAction::mercy(bool canSpare)
{
	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	bool done = false;

	action = MA_RUN;

	SDL_Event event;

	draw(canSpare);

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
				case NES_A:
					return MA_NONE;
				case NES_B:
					menuSelect->play();
					if (action == MA_RUN)
					{
						Log("Ran away.");
						playRunAnimation();
					}
					else
					{
						Log("Spared Fiona!");
						Game::current.fiona.spare();
					}
					return action;
				case NES_UP:
				case NES_DOWN:
					menuMove->play();
					if (canSpare)
					{
						if (action == MA_RUN)
						{
							action = MA_SPARE;
						}
						else
						{
							action = MA_RUN;
						}
					}
					break;
			}

			if (key != NES_NONE)
			{
				draw(canSpare);
			}
		}
	}
}

void MercyAction::playRunAnimation()
{
	SoundEffectPtr fleeSound = sndMgr.load("assets/wav/flee.wav");
	fleeSound->play();

	TexturePtr flee = texMgr.load("assets/flee.png");
	SDL_Surface *text = texMgr.getText("I've got better to do...", FT_COLOUR_WHITE);
	
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 8;
	rect.h = 12;

	Timer fps;
	Timer animate;

	animate.start();

	int x = 20;
	int sprite = 0;
	while (x > 0)
	{
		fps.start();

		draw_rect(screen, 5, 128, 310, 70, 2);

		apply_surface(40, 133, text, screen);
		flee->applyTo(x, 138, screen, &rect);

		if (animate.get_ticks() > 120)
		{
			if (rect.x == 0)
			{
				rect.x = 8;
			}
			else
			{
				rect.x = 0;
			}

			x -= 2;

			animate.start();
		}

		SDL_Flip(screen);

		if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
		}
	}

	SDL_FreeSurface(text);
}