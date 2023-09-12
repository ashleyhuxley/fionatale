#ifndef MERCY_H
#define MERCY_H

#include "SDL/SDL.h"
#include "fionatale.h"
#include <string>

using namespace std;

class MercyAction
{
	public:
		MercyAction();
		MercyActionResult mercy(bool canSpare);

	private:
		string player;
		void draw(bool canSpare);
		MercyActionResult action;
		void playRunAnimation();
};

#endif