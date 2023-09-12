#include "soundeffectmanager.h"
#include <SDL/SDL_mixer.h>

using namespace std;

SoundManager& SoundManager::Instance()
{
	static SoundManager instance;
	return instance;
}

SoundEffectPtr SoundManager::load(const string &filename)
{
	auto texIterator = loadedEffects.find(filename);
	if (texIterator != loadedEffects.end())
	{
		return texIterator->second;
	}

	Mix_Chunk* effect = NULL;

	effect = Mix_LoadWAV(filename.c_str());

	if (effect == NULL)
	{
		cout << "Could not load " << filename << endl;
	}

	SoundEffectPtr effectPtr = make_shared<SoundEffect>(effect);

	loadedEffects.insert(make_pair(filename, effectPtr));

	return effectPtr;
}
