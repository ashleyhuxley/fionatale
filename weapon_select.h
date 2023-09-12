#ifndef WEAPON_SELECT_H
#define WEAPON_SELECT_H

#include <SDL/SDL.h>
#include "fionatale.h"
#include <SDL/SDL_ttf.h>
#include "konami.h"
#include "texturemanager.h"

class WeaponSelect
{
	public:
		WeaponSelect();
		bool init();
		void cleanUp();
		Weapon GetWeapon();

	private:
		SDL_Surface *title;

		SDL_Surface *bibleLabel;
		SDL_Surface *broccoliLabel;
		SDL_Surface *hornLabel;
		SDL_Surface *qmarkLabel;
		SDL_Surface *dildoLabel;

		Weapon weapon;

		void arrange();

		KonamiSequence *konami;

		bool dildoLocked;
};

#endif
