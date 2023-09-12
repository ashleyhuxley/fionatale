#include "act.h"
#include "SDL/SDL.h"
#include "sdl_helpers.h"
#include "fionatale.h"
#include "texttyper.h"
#include "item.h"
#include "log.h"
#include "returnexception.h"
#include "game.h"

using namespace std;

ActAction::ActAction()
{
	hasGibbed = false;
	hasArgued = false;
	hasScritched = false;
	hasCited = false;
}

void ActAction::draw()
{
	SDL_Surface *gibLabel = texMgr.getText("Gib", FT_COLOUR_WHITE);
	SDL_Surface *argueLabel = texMgr.getText("Argue", FT_COLOUR_WHITE);
	SDL_Surface *flirtLabel = texMgr.getText("Flirt", FT_COLOUR_WHITE);
	SDL_Surface *scremLabel = texMgr.getText("Screm", FT_COLOUR_WHITE);
	SDL_Surface *scritchLabel = texMgr.getText("Scritch", FT_COLOUR_WHITE);
	SDL_Surface *citeLabel = texMgr.getText("Cite", FT_COLOUR_WHITE);

	TexturePtr heart = texMgr.load("assets/heart8.png");

	draw_rect(screen, 5, 128, 310, 70, 2);

	apply_surface(25, 133, gibLabel, screen);
	apply_surface(25, 151, argueLabel, screen);
	apply_surface(25, 169, flirtLabel, screen);
	apply_surface(160, 133, scremLabel, screen);
	apply_surface(160, 151, scritchLabel, screen);

	if (hasArgued)
	{
		apply_surface(160, 169, citeLabel, screen);
	}

	switch (action)
	{
		case ACTION_GIB:
			heart->applyTo(12, 138, screen);
			break;
		case ACTION_ARGUE:
			heart->applyTo(12, 156, screen);
			break;
		case ACTION_FLIRT:
			heart->applyTo(12, 174, screen);
			break;
		case ACTION_SCREM:
			heart->applyTo(145, 138, screen);
			break;
		case ACTION_SCRITCH:
			heart->applyTo(145, 156, screen);
			break;
		case ACTION_CITE:
			heart->applyTo(145, 174, screen);
			break;
	}

	SDL_Flip(screen);

	SDL_FreeSurface(gibLabel);
	SDL_FreeSurface(argueLabel);
	SDL_FreeSurface(flirtLabel);
	SDL_FreeSurface(scremLabel);
	SDL_FreeSurface(scritchLabel);
	SDL_FreeSurface(citeLabel);
}

ActActionResult ActAction::act()
{
	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	action = ACTION_GIB;

	SDL_Event event;

	bool done = false;

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

			GibResult gibResult;

			switch (key)
			{
				case NES_B:
					menuSelect->play();
					switch (action)
					{
						case ACTION_GIB:
							gibResult = Gib();
							if (gibResult == GIB_NONE)
							{
								return AAR_NONE;
							}
							else if (gibResult == GIB_GIBBED)
							{
								hasGibbed = true;
							}
							else
							{
								hasGibbed = false;
							}
							
							break;
						case ACTION_ARGUE:
							Argue();
							hasArgued = true;
							break;
						case ACTION_FLIRT:
							Flirt();
							break;
						case ACTION_SCRITCH:
							Scritch();
							hasScritched = true;
							break;
						case ACTION_CITE:
							Cite();
							hasCited = true;
							break;
						case ACTION_SCREM:
							Screm();
							break;
					}

					if (hasGibbed && hasCited && hasScritched)
					{
						return AAR_SPARE;
					}
					else
					{
						return AAR_NOSPARE;
					}

					break;
				case NES_A:
					return AAR_NONE;
				case NES_UP:
					menuMove->play();
					switch (action)
					{
						case ACTION_ARGUE:
							action = ACTION_GIB;
							break;
						case ACTION_FLIRT:
							action = ACTION_ARGUE;
							break;
						case ACTION_SCRITCH:
							action = ACTION_SCREM;
							break;
						case ACTION_CITE:
							action = ACTION_SCRITCH;
							break;
					}
					break;
				case NES_DOWN:
					menuMove->play();
					switch (action)
					{
						case ACTION_GIB:
							action = ACTION_ARGUE;
							break;
						case ACTION_ARGUE:
							action = ACTION_FLIRT;
							break;
						case ACTION_SCREM:
							action = ACTION_SCRITCH;
							break;
						case ACTION_SCRITCH:
							if (hasArgued)
							{
								action = ACTION_CITE;
							}
							break;
					}
					break;
				case NES_LEFT:
					menuMove->play();
					switch (action)
					{
						case ACTION_SCREM:
							action = ACTION_GIB;
							break;
						case ACTION_SCRITCH:
							action = ACTION_ARGUE;
							break;
						case ACTION_CITE:
							action = ACTION_FLIRT;
							break;
					}
					break;
				case NES_RIGHT:
					menuMove->play();
					switch (action)
					{
						case ACTION_GIB:
							action = ACTION_SCREM;
							break;
						case ACTION_ARGUE:
							action = ACTION_SCRITCH;
							break;
						case ACTION_FLIRT:
							if (hasArgued)
							{
								action = ACTION_CITE;
							}
							break;
					}
					break;
			}

			if (key != NES_NONE)
			{
				draw();
			}
		}
	}
}

GibResult ActAction::Gib()
{
	TextTyper typer;

	if (Game::current.player.usedHounds)
	{
		Log("Attempted to gib after using hounds");
		typer.type("Fiona bats the item from your hands", "");
		typer.type("She doesn't want anything from you.", "");
		return GIB_NOTGIBBED;
	}

	if (Game::current.player.inventory.size() == 0)
	{
		Log("Attempted to gib but had nothing.");
		typer.type("You have nothing left to offer.", "");
		return GIB_NOTGIBBED;
	}

	ItemAction itemAction;
	string item = itemAction.use();

	if (item == ITEM_TEA)
	{
		Log("Gibbed the tea.");
		typer.type("You pour Fiona a nice cup of tea.", "");
		typer.type("She sips the tea happily.", "");
		return GIB_GIBBED;
	}
	else if (item == ITEM_COOKIE)
	{
		Log("Gibbed the cookie.");
		typer.type("Fiona nibbles the cookie.", "");
		return GIB_GIBBED;
	}
	else if (item == ITEM_COFFEE)
	{
		Log("Gibbed the coffee.");
		typer.type("Fiona looks at you quizzically,", "but declines the beverage.");
		return GIB_GIBBED;
	}
	else if (item == ITEM_PIZZA)
	{
		Log("Gibbed the pizza.");
		typer.type("Fiona turns her nose up at the offering.", "");
		typer.type("Pineapple on pizza?", "What sort of monster ARE you?");
		return GIB_GIBBED;
	}
	else if (item == ITEM_HOTSAUCE)
	{
		Log("Gibbed the hot sauce");
		typer.type("Fiona appreciates your taste in sauces.", "");
		return GIB_GIBBED;
	}
	else if (item == ITEM_TACO)
	{
		Log("Gibbed the taco.");
		typer.type("Fiona's favourite.", "'Taco bout' a good choice!");
		return GIB_GIBBED;
	}
	else
	{
		return GIB_NONE;
	}
}

void ActAction::Argue()
{
	Log("Argued with Fiona");
	TextTyper typer;
	typer.type("You present an argument to Fiona.", "");
	typer.type("Fiona doubts your credibility.", "");
	hasArgued = true;
}

void ActAction::Flirt()
{
	Log("Flirted with Fiona");
	TextTyper typer;
	typer.type("You flirt with Fiona.", "");
	typer.type("She seems entirely uninterested.", "");
}

void ActAction::Screm()
{
	Log("Scremed at Fiona");
	TextTyper typer;
	typer.type("You scream at Fiona.", "");
	typer.type("Fiona screeches back thrice as hard.", "");
	typer.type("Fiona screeches herself out of the room.", "");
	Game::current.fiona.scremOut();
}

void ActAction::Scritch()
{
	TextTyper typer;

	if (hasGibbed && !usedHounds)
	{
		Log("Scritched Fiona");
		typer.type("Fiona leans forward and purrs softly.", "");
		if (hasCited)
		{
			typer.type("She doesn't seem to want to fight any more.", "");
		}
		hasScritched = true;
	}
	else
	{
		Log("Could not scritch Fiona");
		typer.type("Fiona snarls and bats your hand away.", "");
		typer.type("She hasn't warmed up to you yet.", "");
	}
}

void ActAction::Cite()
{
	Log("Cited sources for argument");
	TextTyper typer;
	typer.type("You cite the sources for your argument.", "");
	typer.type("Fiona seems impressed by your knowledge", "of science.");
	if (hasGibbed && hasScritched)
	{
		typer.type("Fiona doesn't seem to want to fight any more.", "");
	}
	hasCited = true;
}
