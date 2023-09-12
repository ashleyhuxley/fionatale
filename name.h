#ifndef NAME_H
#define NAME_H

#include <SDL/SDL.h>
#include <string>

using namespace std;

class Name
{
	public:
		Name();
		string getName();

	private:
		char chars[7][4];
		int posX;
		int posY;
		string name;
		void select();
};

#endif
