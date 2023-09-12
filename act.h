#ifndef ACT_H
#define ACT_H

#include "SDL/SDL.h"
#include "fionatale.h"
#include <vector>
#include <string>

using namespace std;

typedef Uint8 GibResult;

const GibResult GIB_NONE = 0;
const GibResult GIB_GIBBED = 1;
const GibResult GIB_NOTGIBBED = 2;

class ActAction
{
	public:
		ActAction();
		ActActionResult act();

	private:
		Action action;
		void draw();

		GibResult Gib();
		void Argue();
		void Flirt();
		void Screm();
		void Scritch();
		void Cite();

		bool hasGibbed;
		bool hasArgued;
		bool hasScritched;
		bool hasCited;
		bool usedHounds;

		string player;
};

#endif