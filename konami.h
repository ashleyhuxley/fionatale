#ifndef KONAMI_H
#define KONAMI_H

#include <SDL/SDL.h>

class KonamiSequence
{
	public:
		KonamiSequence();
		bool IsCompletedBy(Uint8 key);
	private:
		Uint8 code[10];
		int offset;
		int length;
		int target;
};

#endif
