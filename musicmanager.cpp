#include "musicmanager.h"


MusicManager& MusicManager::Instance()
{
	static MusicManager instance;
	return instance;
}

MusicManager::MusicManager()
{
	dead = NULL;
	intro = NULL;
	menu = NULL;
	fight = NULL;
	spare = NULL;
}

void MusicManager::load()
{
	dead = Mix_LoadMUS("assets/mp3/determination.mp3");
	intro = Mix_LoadMUS("assets/mp3/undertale.mp3");
	menu = Mix_LoadMUS("assets/mp3/menu.mp3");
	fight = Mix_LoadMUS("assets/mp3/hopes-and-dreams.mp3");
	spare = Mix_LoadMUS("assets/mp3/caramelldansen.mp3");
}

void MusicManager::stop()
{
	Mix_HaltMusic();
}

void MusicManager::playIntro()
{
	if( Mix_PlayingMusic() != 0 )
	{
		stop();
	}

	Mix_PlayMusic(intro, -1);
}

void MusicManager::playDead()
{
	if( Mix_PlayingMusic() != 0 )
	{
		stop();
	}

	Mix_PlayMusic(dead, -1);
}

void MusicManager::playMenu()
{
	if( Mix_PlayingMusic() != 0 )
	{
		stop();
	}

	Mix_PlayMusic(menu, -1);
}

void MusicManager::playFight()
{
	if( Mix_PlayingMusic() != 0 )
	{
		stop();
	}

	Mix_PlayMusic(fight, -1);
}

void MusicManager::playSpare()
{
	if( Mix_PlayingMusic() != 0 )
	{
		stop();
	}

	Mix_PlayMusic(spare, -1);
}

MusicManager::~MusicManager()
{
	Mix_FreeMusic( dead );
	Mix_FreeMusic( intro );
	Mix_FreeMusic( menu );
	Mix_FreeMusic( fight );
	Mix_FreeMusic( spare );
}