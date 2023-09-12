#ifndef TEXTTYPER_H
#define TEXTTYPER_H

#include <string>
#include "timer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

using namespace std;

class TextTyper
{
	public:
		TextTyper();
		void type(string txt1, string txt2, bool box = true);

	private:
		TTF_Font *font;
};

#endif
