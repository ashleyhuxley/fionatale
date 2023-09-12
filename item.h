#ifndef ITEM_H
#define ITEM_H

#include "SDL/SDL.h"
#include <string>
#include <vector>

using namespace std;

class ItemAction
{
	public:
		ItemAction();
		string use();

		static int getHP(string item);

	private:
		void draw();
		int selected;
};

#endif