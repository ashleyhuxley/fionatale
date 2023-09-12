#include "fight.h"
#include "SDL/SDL.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include "timer.h"
#include <ctime>
#include "log.h"
#include "returnexception.h"
#include "game.h"

using namespace std;

FightAction::FightAction()
{

}

int FightAction::fight()
{
	TexturePtr target = texMgr.load("assets/target.png");

	bool done = false;
	SDL_Event event;

	int shots = 1;

	switch (Game::current.player.getWeapon())
	{
		case W_DILDO:
			shots = 2;
			break;
		case W_HORN:
			shots = 3;
			break;
	}

	int offsets[3];
	offsets[0] = rand() % 1000 + 50;
	offsets[1] = offsets[0] + (rand() % 500) + 50;
	offsets[2] = offsets[1] + (rand() % 500) + 50;

	int scores[3];
	scores[0] = 0;
	scores[1] = 0;
	scores[2] = 0;

	int x[3];
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;

	int i = 0;

	Timer fps;
	Timer animate;
	animate.start();

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
				int s = abs(160 - x[i]);

				if (s <= 5) {
					scores[i] = 6;
				}
				else if (s < 15) {
					scores[i] = 3;
				}
				else if (s < 100) {
					scores[i] = 1;
				}

				i++;

				if (i == shots)
				{
					done = true;
				}
			}
		}

		draw_rect(screen, 5, 128, 310, 70, 2);
		target->applyTo(8, 131, screen);

		for (int j = 0; j < shots; j++)
		{
			if (animate.get_ticks() > offsets[j])
			{
				x[j] = (animate.get_ticks() - offsets[j]) / 3.5;
			}

			if ((x[j] > 10) && (x[j] < 300) && (j >= i))
			{
				SDL_Rect rect;
				rect.x = x[j];
				rect.y = 131;
				rect.w = 4;
				rect.h = 64;

				SDL_FillRect( screen, &rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
			}
		}

		SDL_Flip(screen);

		if (x[0] > 500)
		{
			done = true;
		}

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	string scoreStr = to_string(scores[0]) + " : " + to_string(scores[1]) + " : " + to_string(scores[2]);
	Log("Scored " + scoreStr);

	int total = scores[0] + scores[1] + scores[2];

	if (total > 0)
	{
		Game::current.fiona.slash();
	}

	return total;
}

