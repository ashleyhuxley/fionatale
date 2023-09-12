#ifndef PLAYER_H
#define PLAYER_H

#include <SDL/SDL.h>
#include <string>
#include "fionatale.h"
#include <vector>

using namespace std;

class Player
{
	public:
		Player(string playerName, Weapon w);
		string getName();
		int getHp();
		void addHp(int hpToAdd);
		bool hit(int hpHit);
		void displayHp();
		Weapon getWeapon();
		vector<string> inventory;
		bool usedHounds;

	private:
		string name;
		int hp;
		Weapon weapon;
};

#endif
