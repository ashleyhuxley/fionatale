#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include "fionatale.h"
#include <SDL/SDL_ttf.h>
#include "mainmenu.h"
#include "player.h"
#include <string>
#include "fiona.h"

using namespace std;

class Game
{
	public:
		Game(string name, Weapon w);
		
		static Game current;

		void play();

		Player player;
		Fiona fiona;

	private:

};

#endif
