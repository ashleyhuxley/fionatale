#include "soundeffect.h"
#include <SDL/SDL_mixer.h>
#include "sdl_helpers.h"

SoundEffect::SoundEffect(Mix_Chunk *eff)
{
	effect = eff;
}

void SoundEffect::play()
{
	Mix_PlayChannel( -1, effect, 0 );
}
