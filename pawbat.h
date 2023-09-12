#ifndef PAWBAT_H
#define PAWBAT_H

#include <SDL/SDL.h>
#include "soul.h"
#include "player.h"
#include "attack.h"

class Pawbat : public Attack
{
	public:
		Pawbat();
		bool fight();

};

#endif
