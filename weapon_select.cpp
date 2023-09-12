#include "weapon_select.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include <SDL/SDL_ttf.h>
#include "konami.h"
#include "returnexception.h"

WeaponSelect::WeaponSelect()
{
	title = NULL;

	bibleLabel = NULL;
	broccoliLabel = NULL;
	hornLabel = NULL;
	qmarkLabel = NULL;

	weapon = W_BIBLE;

	dildoLocked = true;

	konami = new KonamiSequence();
}

bool WeaponSelect::init()
{
	title = texMgr.getTitleText("Choose your Weapon", FT_COLOUR_WHITE);

	bibleLabel = texMgr.getText("Holy Bible", FT_COLOUR_WHITE);
	broccoliLabel = texMgr.getText("Broccoli", FT_COLOUR_WHITE);
	hornLabel = texMgr.getText("Hunting Horn", FT_COLOUR_WHITE);
	qmarkLabel = texMgr.getText("LOCKED", FT_COLOUR_GREY);
	dildoLabel = texMgr.getText("Bad Dragon", FT_COLOUR_WHITE);

	return true;
}

void WeaponSelect::cleanUp()
{
	SDL_FreeSurface(bibleLabel);
	SDL_FreeSurface(broccoliLabel);
	SDL_FreeSurface(hornLabel);
	SDL_FreeSurface(qmarkLabel);
	SDL_FreeSurface(dildoLabel);

	SDL_FreeSurface(title);

	delete(konami);
}

Weapon WeaponSelect::GetWeapon()
{
	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	bool quit = false;

	arrange();

	SDL_Flip(screen);

	SDL_Event event;

	while (!quit)
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
				case NES_UP:
					switch (weapon)
					{
						case W_BROCCOLI:
							weapon = W_BIBLE;
							menuMove->play();
							break;
						case W_DILDO:
							weapon = W_HORN;
							menuMove->play();
							break;
					}
					break;
				case NES_DOWN:
					switch (weapon)
					{
						case W_BIBLE:
							weapon = W_BROCCOLI;
							menuMove->play();
							break;
						case W_HORN:
							weapon = W_DILDO;
							menuMove->play();
							break;
					}
					break;
				case NES_LEFT:
					switch (weapon)
					{
						case W_HORN:
							weapon = W_BIBLE;
							menuMove->play();
							break;
						case W_DILDO:
							weapon = W_BROCCOLI;
							menuMove->play();
							break;
					}
					break;
				case NES_RIGHT:
					switch (weapon)
					{
						case W_BIBLE:
							weapon = W_HORN;
							menuMove->play();
							break;
						case W_BROCCOLI:
							weapon = W_DILDO;
							menuMove->play();
							break;
					}
					break;
				case NES_START:
					if (weapon != W_DILDO || (!dildoLocked))
					{
						menuSelect->play();
						return weapon;
					}
					break;
			}

			if (key != NES_NONE)
			{
				if (konami->IsCompletedBy(key))
				{
					dildoLocked = false;
				}

				arrange();
				SDL_Flip(screen);
			}
		}
	}
}

void WeaponSelect::arrange()
{
	TexturePtr bible = texMgr.load("assets/bible.png");
	TexturePtr broccoli = texMgr.load("assets/broccoli.png");
	TexturePtr qmark = texMgr.load("assets/qmark.png");
	TexturePtr dildo = texMgr.load("assets/dildo.png");
	TexturePtr horn = texMgr.load("assets/horn.png");
	TexturePtr heart = texMgr.load("assets/heart_red.png");

	SDL_FillRect(screen, NULL, 0x000000);

	bible->applyTo(48, 50, screen);
	broccoli->applyTo(48, 150, screen);
	horn->applyTo(208, 50, screen);

	apply_surface(80 - (bibleLabel->w / 2), 120, bibleLabel, screen);
	apply_surface(80 - (broccoliLabel->w / 2), 220, broccoliLabel, screen);
	apply_surface(240 - (hornLabel->w / 2), 120, hornLabel, screen);

	if (dildoLocked)
	{
		qmark->applyTo(208, 150, screen);
		apply_surface(240 - (qmarkLabel->w / 2), 220, qmarkLabel, screen);
	}
	else
	{
		dildo->applyTo(208, 150, screen);
		apply_surface(240 - (dildoLabel->w / 2), 220, dildoLabel, screen);
	}
	

	apply_surface(160 - (title->w / 2), 5, title, screen);

	switch (weapon)
	{
		case W_BIBLE:
			heart->applyTo(80 - (bibleLabel->w / 2) - 25, 118, screen);
			break;
		case W_BROCCOLI:
			heart->applyTo(80 - (broccoliLabel->w / 2) - 25, 218, screen);
			break;
		case W_HORN:
			heart->applyTo(240 - (hornLabel->w / 2) - 25, 118, screen);
			break;
		case W_DILDO:
			heart->applyTo(240 - (qmarkLabel->w / 2) - 35, 218, screen);
			break;
	}
}
