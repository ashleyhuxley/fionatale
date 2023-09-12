#include "item.h"
#include "texturemanager.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include "texture.h"
#include "texttyper.h"
#include "returnexception.h"
#include "game.h"
#include "log.h"

using namespace std;

ItemAction::ItemAction()
{
}

int ItemAction::getHP(string item)
{
	if (item == ITEM_TEA)
	{
		return 5;
	}
	else if (item == ITEM_COOKIE)
	{
		return 6;
	}
	else if (item == ITEM_COFFEE)
	{
		return 4;
	}
	else if (item == ITEM_PIZZA)
	{
		return 12;
	}
	else if (item == ITEM_HOTSAUCE)
	{
		return 8;
	}
	else if (item == ITEM_TACO)
	{
		return 20;
	}
}

string ItemAction::use()
{
	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	if (Game::current.player.inventory.size() == 0)
	{
		TextTyper typer;
		typer.type("You have nothing left.", "");
		Log("Attempted to use but had nothing left");
		return "";
	}

	bool done = false;
	SDL_Event event;
	selected = 1;
	string result;

	draw();

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				throw ReturnException();
			}

			Uint8 key = get_event(&event);
			int t = selected;

			switch (key)
			{
				case NES_B:
					menuSelect->play();
					result = Game::current.player.inventory.at(selected - 1);
					Game::current.player.inventory.erase(Game::current.player.inventory.begin() + (selected - 1));
					return result;
				case NES_A:
					return "";
				case NES_UP:
					menuMove->play();
					switch (selected)
					{
						case 2: selected = 1; break;
						case 3: selected = 2; break;
						case 5: selected = 4; break;
						case 6: selected = 5; break;
					}
					break;
				case NES_DOWN:
					menuMove->play();
					switch (selected)
					{
						case 1: selected = 2; break;
						case 2: selected = 3; break;
						case 4: selected = 5; break;
						case 5: selected = 6; break;
					}
					break;
				case NES_LEFT:
					menuMove->play();
					switch (selected)
					{
						case 4: selected = 1; break;
						case 5: selected = 2; break;
						case 6: selected = 3; break;
					}
					break;
				case NES_RIGHT:
					menuMove->play();
					switch (selected)
					{
						case 1: selected = 4; break;
						case 2: selected = 5; break;
						case 3: selected = 6; break;
					}
					break;
			}

			if (selected > Game::current.player.inventory.size() || selected < 1)
			{
				selected = t;
			}

			if (key != NES_NONE)
			{
				draw();
			}
		}
	}
}

void ItemAction::draw()
{
	TexturePtr heart = texMgr.load("assets/heart8.png");

	int x = 25;
	int y = 133;

	draw_rect(screen, 5, 128, 310, 70, 2);

	int i = 1;

	for (string item : Game::current.player.inventory)
	{
		SDL_Surface *label = texMgr.getText(item, FT_COLOUR_WHITE);

		apply_surface(x, y, label, screen);

		SDL_FreeSurface(label);
		
		if (selected == i)
		{
			heart->applyTo(x - 12, y + 4, screen);
		}

		y += 20;

		if (y >= 193)
		{
			y = 133;
			x += 100;
		}

		i++;
	}

	SDL_Flip(screen);
}