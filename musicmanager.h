#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <SDL/SDL_mixer.h>

class MusicManager
{
	public:
		MusicManager();
		~MusicManager();

		static MusicManager& Instance();
		void load();
		void stop();
		void playMenu();
		void playDead();
		void playIntro();
		void playFight();
		void playSpare();

	private:
		Mix_Music *intro;
		Mix_Music *dead;
		Mix_Music *menu;
		Mix_Music *fight;
		Mix_Music *spare;
};

#endif
