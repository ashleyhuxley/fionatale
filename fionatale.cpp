#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include "sdl_helpers.h"
#include "weapon_select.h"
#include "fionatale.h"
#include "game.h"
#include "texturemanager.h"
#include "soundeffectmanager.h"
#include "texture.h"
#include "soundeffect.h"
#include "name.h"
#include "log.h"
#include "returnexception.h"
#include "intro.h"
#include <SDL/SDL_mixer.h>
#include "musicmanager.h"

using namespace std;

SDL_Surface *screen = NULL;
SDL_Joystick *stick = NULL;

SDL_Color FT_COLOUR_ORANGE = { 255, 127, 39 };
SDL_Color FT_COLOUR_BLUE = { 71, 130, 201 };
SDL_Color FT_COLOUR_WHITE = { 255, 255, 255 };
SDL_Color FT_COLOUR_GREY = { 180, 180, 180 };
SDL_Color FT_COLOUR_YELLOW = { 255, 255, 64 };

TextureManager &texMgr = TextureManager::Instance();
SoundManager &sndMgr = SoundManager::Instance();
MusicManager &musMgr = MusicManager::Instance();

int FRAMES_PER_SECOND = 30;
bool isWindow = false;

bool init()
{
	srand (time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	Uint32 flags = SDL_SWSURFACE;
	if (!isWindow)
	{
		flags = flags | SDL_FULLSCREEN;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, flags);

	if (screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 2048 ) == -1 )
    {
        return false;    
    }

    Mix_Init(MIX_INIT_MP3);

    stick = SDL_JoystickOpen( 0 );

	SDL_ShowCursor(SDL_DISABLE);

	texMgr.init();

	return true;
}

void load_files()
{
	TexturePtr bible = texMgr.load("assets/bible.png");
	TexturePtr broccoli = texMgr.load("assets/broccoli.png");
	TexturePtr buttons = texMgr.load("assets/buttons.png");
	TexturePtr dildo = texMgr.load("assets/dildo.png");
	TexturePtr heart8 = texMgr.load("assets/heart8.png");
	TexturePtr heart = texMgr.load("assets/heart_red.png");
	TexturePtr horn = texMgr.load("assets/horn.png");
	TexturePtr qmark = texMgr.load("assets/qmark.png");
	TexturePtr fen = texMgr.load("assets/fen.png");
	TexturePtr bg = texMgr.load("assets/bg.png");
	TexturePtr target = texMgr.load("assets/target.png");
	TexturePtr title = texMgr.load("assets/title.png");
	TexturePtr symbols = texMgr.load("assets/symbols.png");
	TexturePtr flee = texMgr.load("assets/flee.png");
	TexturePtr paw = texMgr.load("assets/paw.png");
	TexturePtr slash = texMgr.load("assets/slash.png");
	TexturePtr soul_die = texMgr.load("assets/soul-break.png");
	TexturePtr shards = texMgr.load("assets/shards.png");
	TexturePtr gameover = texMgr.load("assets/game-over.png");
	TexturePtr particle = texMgr.load("assets/particle.png");
	TexturePtr cf = texMgr.load("assets/cf.png");
	TexturePtr caramel = texMgr.load("assets/caramel.png");
	TexturePtr sparebg = texMgr.load("assets/sparebg.png");
	TexturePtr bluea = texMgr.load("assets/bluea.png");
	TexturePtr orangea = texMgr.load("assets/orangea.png");

	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");
	SoundEffectPtr text = sndMgr.load("assets/wav/text2.wav");
	SoundEffectPtr dust = sndMgr.load("assets/wav/dust.wav");
	SoundEffectPtr hit = sndMgr.load("assets/wav/hit.wav");
	SoundEffectPtr soulHit = sndMgr.load("assets/wav/soul-hit.wav");
	SoundEffectPtr heal = sndMgr.load("assets/wav/heal.wav");
	SoundEffectPtr soulSplit = sndMgr.load("assets/wav/soul-split.wav");
	SoundEffectPtr soulShatter = sndMgr.load("assets/wav/soul-shatter.wav");

	musMgr.load();
}

void clean_up()
{
	texMgr.cleanUp();

	SDL_JoystickClose(stick);
	TTF_Quit();
	Mix_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void newGame()
{
	musMgr.playMenu();

	// Name
	Name name;
	string player = name.getName();

	SDL_WM_SetCaption(player.c_str(), NULL);

	// Get Weapon
	WeaponSelect select;
	select.init();

	Weapon weapon = select.GetWeapon();

	select.cleanUp();

	musMgr.playFight();

	// Play Game
	Game game(player, weapon);
	Game::current = game;
	Game::current.play();
}

void parseArgs(int argc, char* args[])
{
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(args[i], "-fps") == 0)
		{
			FRAMES_PER_SECOND = stoi(args[i + 1]);
		}
		else if (strcmp(args[i], "-window") == 0)
		{
			isWindow = true;
		}
	}
}

int main (int argc, char* args[])
{
	parseArgs(argc, args);

	if (init() == false)
	{
		return -1;
	}

	load_files();

	Intro intro;

	bool quit = false;

	while (!quit)
	{
		try
		{
			intro.play();
			newGame();
		}
		catch (const ReturnException&)
		{
			quit = true;
		}
	}

	clean_up();

	return 0;
}
