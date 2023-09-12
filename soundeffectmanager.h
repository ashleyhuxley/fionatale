#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "soundeffect.h"
#include <map>
#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

class SoundManager
{
	public:
		static SoundManager& Instance();
		SoundEffectPtr load(const string &filename);

	private:
		map<string, SoundEffectPtr> loadedEffects;
};

#endif
