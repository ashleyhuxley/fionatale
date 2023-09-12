#include "konami.h"
#include "fionatale.h"

KonamiSequence::KonamiSequence()
{
	code[0] = NES_UP;
	code[1] = NES_UP;
	code[2] = NES_DOWN;
	code[3] = NES_DOWN;
	code[4] = NES_LEFT;
	code[5] = NES_RIGHT;
	code[6] = NES_LEFT;
	code[7] = NES_RIGHT;
	code[8] = NES_B;
	code[9] = NES_A;

	length = 9;
	target = 10;
}

bool KonamiSequence::IsCompletedBy(Uint8 key)
{
	// Ignore _UP key events
	if (key > 20)
	{
		return false;
	}

	offset %= target;

	if (key == code[offset])
	{
		offset++;
	}
	else if (key == code[0])
	{
		offset = 2;
	}

	return offset > length;
}