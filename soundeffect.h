#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL/SDL_mixer.h>
#include <memory>
#include <iostream>

class SoundEffect
{
	public:
		SoundEffect(Mix_Chunk *effect);	
		void play();

	private:
		Mix_Chunk *effect;
};

typedef std::shared_ptr<SoundEffect> SoundEffectPtr;

#endif
