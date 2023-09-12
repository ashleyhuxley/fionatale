#ifndef FIONATALE_H
#define FIONATALE_H

#include "texturemanager.h"
#include "soundeffectmanager.h"
#include "musicmanager.h"

using namespace std;

typedef Uint8 Action;
typedef Uint8 MainMenuAction;
typedef Uint8 Weapon;
typedef Uint8 MercyActionResult;
typedef Uint8 ActActionResult;

const ActActionResult AAR_NONE = 0;
const ActActionResult AAR_NOSPARE = 1;
const ActActionResult AAR_SPARE = 2;

const Action ACTION_NOACTION = 0;
const Action ACTION_GIB = 1;
const Action ACTION_ARGUE = 2;
const Action ACTION_FLIRT = 3;
const Action ACTION_SCREM = 4;
const Action ACTION_SCRITCH = 5;
const Action ACTION_CITE = 6;

const MainMenuAction MMA_NONE = 0;
const MainMenuAction MMA_FIGHT = 1;
const MainMenuAction MMA_ACT = 2;
const MainMenuAction MMA_ITEM = 3;
const MainMenuAction MMA_MERCY = 4;

const Weapon W_BIBLE = 1;
const Weapon W_BROCCOLI = 2;
const Weapon W_HORN = 3;
const Weapon W_DILDO = 4;

const MercyActionResult MA_NONE = 0;
const MercyActionResult MA_RUN = 1;
const MercyActionResult MA_SPARE = 2;

const string ITEM_TACO = "Taco";
const string ITEM_COOKIE = "Cookie";
const string ITEM_HOTSAUCE = "Hot Sauce";
const string ITEM_PIZZA = "Hawaiian Pizza";
const string ITEM_TEA = "Cup of Tea";
const string ITEM_COFFEE = "Cup of Coffee";

const Uint8 NES_SELECT = 8;
const Uint8 NES_START = 9;
const Uint8 NES_B = 0;
const Uint8 NES_A = 1;
const Uint8 NES_UP = 2;
const Uint8 NES_DOWN = 3;
const Uint8 NES_LEFT = 4;
const Uint8 NES_RIGHT = 5;
const Uint8 NES_NONE = 10;

extern SDL_Color FT_COLOUR_ORANGE;
extern SDL_Color FT_COLOUR_BLUE;
extern SDL_Color FT_COLOUR_WHITE;
extern SDL_Color FT_COLOUR_GREY;
extern SDL_Color FT_COLOUR_YELLOW;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

extern TextureManager &texMgr;
extern SoundManager &sndMgr;
extern MusicManager &musMgr;

extern int FRAMES_PER_SECOND;

extern SDL_Surface *screen;

inline const char* ToString(Weapon w)
{
	switch (w)
	{
		case W_BIBLE: return "Bible";
		case W_BROCCOLI: return "Broccoli";
		case W_HORN: return "Horn";
		case W_DILDO: return "Dildo";
		default: return "[Unknown]";
	}
}

#endif
