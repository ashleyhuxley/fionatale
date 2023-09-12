#ifndef INTRO_H
#define INTRO_H

#include <SDL/SDL.h>

class Intro
{
	public:
		Intro();
		~Intro();
		void play();

	private:
		bool drawTitle();
		bool drawCredits();
		bool drawCf();
		bool drawPlay();

		bool processEvents();

		SDL_Surface *play_o;
		SDL_Surface *play_w;
};

#endif
