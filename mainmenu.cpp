#include "mainmenu.h"
#include "SDL/SDL.h"
#include "sdl_helpers.h"
#include "fionatale.h"
#include "returnexception.h"

MainMenu::MainMenu()
{
	action = MMA_NONE;

	int i = 0;

	for (int x = 0; x < 110; x += 55)
	{
		for (int y = 0; y < 84; y += 21)
		{
			clips[i].x = x;
			clips[i].y = y;
			clips[i].w = 55;
			clips[i].h = 21;
			i++;
		}
	}
}

void MainMenu::reset()
{
	action = MMA_NONE;
}

void MainMenu::draw(bool showHeart)
{
	TexturePtr buttons = texMgr.load("assets/buttons.png");
	TexturePtr heart8 = texMgr.load("assets/heart8.png");

	buttons->applyTo(5, 215, screen, &clips[0]);
	buttons->applyTo(90, 215, screen, &clips[1]);
	buttons->applyTo(175, 215, screen, &clips[2]);
	buttons->applyTo(260, 215, screen, &clips[3]);

	switch (action)
	{
		case MMA_FIGHT:
			buttons->applyTo(5, 215, screen, &clips[4]);
			if (showHeart) { heart8->applyTo(9, 222, screen); }
			break;
		case MMA_ACT:
			buttons->applyTo(90, 215, screen, &clips[5]);
			if (showHeart) { heart8->applyTo(94, 222, screen); }
			break;
		case MMA_ITEM:
			buttons->applyTo(175, 215, screen, &clips[6]);
			if (showHeart) { heart8->applyTo(179, 222, screen); }
			break;
		case MMA_MERCY:
			buttons->applyTo(260, 215, screen, &clips[7]);
			if (showHeart) { heart8->applyTo(264, 222, screen); }
			break;
	}
}

MainMenuAction MainMenu::getAction()
{
	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	bool hasItem = false;
	SDL_Event event;

	action = MMA_FIGHT;
	draw(true);
	SDL_Flip(screen);

	while (!hasItem)
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
				case NES_LEFT:
					switch (action)
					{
						case MMA_ACT:
							action = MMA_FIGHT;
							menuMove->play();
							break;
						case MMA_ITEM:
							action = MMA_ACT;
							menuMove->play();
							break;
						case MMA_MERCY:
							action = MMA_ITEM;
							menuMove->play();
							break;
					}
					break;
				case NES_RIGHT:
					switch (action)
					{
						case MMA_FIGHT:
							action = MMA_ACT;
							menuMove->play();
							break;
						case MMA_ACT:
							action = MMA_ITEM;
							menuMove->play();
							break;
						case MMA_ITEM:
							action = MMA_MERCY;
							menuMove->play();
							break;
					}
					break;
				case NES_B:
					hasItem = true;
					menuSelect->play();
					break;
			}

			if (key != NES_NONE)
			{
				draw(true);
				SDL_Flip(screen);
			}
		}
	}

	draw(false);
	SDL_Flip(screen);

	return action;
}