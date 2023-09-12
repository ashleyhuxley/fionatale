#include "player.h"
#include "sdl_helpers.h"
#include "fionatale.h"

using namespace std;

Player::Player(string playerName, Weapon w)
{
	name = playerName;
	weapon = w;
	hp = 20;
	usedHounds = false;

	inventory.push_back(ITEM_TACO);
	inventory.push_back(ITEM_COOKIE);
	inventory.push_back(ITEM_HOTSAUCE);
	inventory.push_back(ITEM_PIZZA);
	inventory.push_back(ITEM_TEA);
	inventory.push_back(ITEM_COFFEE);
}

Weapon Player::getWeapon()
{
	return weapon;
}

void Player::displayHp()
{
	SDL_Rect r;
	r.x = 0;
	r.y = 198;
	r.w = 320;
	r.h = 16;

	SDL_FillRect(screen, &r, 0x000000);

	SDL_Surface *nameTxt = texMgr.getSmallText(name, FT_COLOUR_YELLOW);
	apply_surface(10, 199, nameTxt, screen);
	SDL_FreeSurface(nameTxt);

	SDL_Surface *hpTxt = texMgr.getSmallText("HP", FT_COLOUR_YELLOW);
	apply_surface(80, 199, hpTxt, screen);
	SDL_FreeSurface(hpTxt);

	SDL_Rect outer;
	outer.x = 100;
	outer.y = 202;
	outer.w = 20;
	outer.h = 10;

	SDL_Rect inner;
	inner.x = 100;
	inner.y = 202;
	inner.w = hp;
	inner.h = 10;

	SDL_FillRect( screen, &outer, SDL_MapRGB( screen->format, 0xFF, 0x00, 0x00 ) );
	SDL_FillRect( screen, &inner, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0x40 ) );

	SDL_Surface *numTxt = texMgr.getSmallText(to_string(hp) + " / 20", FT_COLOUR_YELLOW);
	apply_surface(150, 199, numTxt, screen);
	SDL_FreeSurface(numTxt);

	SDL_Flip(screen);
}

string Player::getName()
{
	return name;
}

int Player::getHp()
{
	return hp;
}

void Player::addHp(int hpToAdd)
{
	SoundEffectPtr heal = sndMgr.load("assets/wav/heal.wav");
	heal->play();

	hp += hpToAdd;

	if (hp > 20)
	{
		hp = 20;
	}

	displayHp();
}

bool Player::hit(int hitHp)
{
	hp -= hitHp;

	displayHp();

	if (hp <= 0)
	{
		return false;
	}

	SoundEffectPtr soulHit = sndMgr.load("assets/wav/soul-hit.wav");
	soulHit->play();
	return true;
}