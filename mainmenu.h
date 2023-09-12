#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL/SDL.h>
#include "fionatale.h"

class MainMenu
{
	public:
		MainMenu();
		MainMenuAction getAction();
		void draw(bool showHeart);
		void reset();

	private:
		SDL_Rect clips[8];
		MainMenuAction action;
};

#endif
