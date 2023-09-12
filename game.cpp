#include <SDL/SDL.h>
#include "game.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include "timer.h"
#include <SDL/SDL_ttf.h>
#include "texttyper.h"
#include "fight.h"
#include "act.h"
#include "mercy.h"
#include "log.h"
#include "item.h"
#include "pawbat.h"
#include "screm.h"

using namespace std;

Game::Game(string name, Weapon w) : player(name, w), fiona()
{

}

Game Game::current("", 0);

void Game::play()
{
	Log("---------- New Game ----------");
	Log("Selected the " + string(ToString(player.getWeapon())));

	MainMenu menu;
	FightAction fightAction;
	ActAction actAction;
	MercyAction mercyAction;
	ItemAction itemAction;

	TextTyper typer;

	SDL_FillRect(screen, NULL, 0x000000);
	fiona.drawMain();
	player.displayHp();
	SDL_Flip(screen);

	bool quit = false;

	ActActionResult actActionResult = AAR_NONE;

	while (!quit)
	{
		menu.reset();
		menu.draw(false);
		typer.type("FIONA stands in your way.", "");

		MainMenuAction action = menu.getAction();

		bool fionasGo = true;

		string usedItem;

		switch (action)
		{
			case MMA_FIGHT:
				switch (player.getWeapon())
				{
					case W_BIBLE:
						typer.type("Throw the book at her!", "");
						break;
					case W_BROCCOLI:
						typer.type("Eat your greens.", "");
						break;
					case W_HORN:
						typer.type("You summon the hounds.", "You... you MONSTER.");
						player.usedHounds = true;
						break;
					case W_DILDO:
						typer.type("Fiona recoils in disgust.", "");
						break;
				}

				if (!fiona.hit(fightAction.fight()))
				{
					return;
				}

				break;
			case MMA_ACT:
				actActionResult = actAction.act();
				if (actActionResult == AAR_NONE)
				{
					fionasGo = false;
				}
				else if (actActionResult == AAR_SPARE)
				{
					Game::current.fiona.canSpare = true;
					fionasGo = true;
				}
				else if (actActionResult == AAR_NOSPARE)
				{
					fionasGo = true;
				}
				break;
			case MMA_MERCY:
				if (mercyAction.mercy(fiona.canSpare && !player.usedHounds) == MA_NONE)
				{
					fionasGo = false;
				}
				else
				{
					return;
				}

				break;
			case MMA_ITEM:
				usedItem = itemAction.use();
				player.addHp(ItemAction::getHP(usedItem));

				if (usedItem == ITEM_TEA)
				{
					typer.type("You sip the tea.", "Lapsang Soushong. Mmmmmmmm.");
				}
				else if (usedItem == ITEM_COOKIE)
				{
					typer.type("You nibble the cookie.", "");
				}
				else if (usedItem == ITEM_COFFEE)
				{
					typer.type("Tastes like brown disappointment.", "");
				}
				else if (usedItem == ITEM_PIZZA)
				{
					typer.type("Cold, but still good.", "");
				}
				else if (usedItem == ITEM_HOTSAUCE)
				{
					typer.type("You open the bottle and take a sip", "of the liquid fire.");
					typer.type("The heat slows your movements.", "");
				}
				else if (usedItem == ITEM_TACO)
				{
					typer.type("Messy Mexican food.", "The best kind.");
					typer.type("Fiona watches you enviously.", "");
				}
				
				Log(player.getName() + " used " + usedItem + " (HP:" + to_string(player.getHp()) + ")");

				if (usedItem == "")
				{
					fionasGo = false;
				}
		}

		if (fionasGo)
		{
			menu.reset();

			int attack = rand() % 2;

			bool alive;

			switch (attack)
			{
				case 0:
					{
						Pawbat pawbat;
						alive = pawbat.fight();
					}
					break;
				case 1:
					{
						Screm screm;
						alive = screm.fight();
					}
					break;
			}

			if (!alive)
			{
				quit = true;
			}
		}
	}
}
