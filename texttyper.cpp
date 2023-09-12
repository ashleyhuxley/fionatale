#include "texttyper.h"
#include <string>
#include <SDL/SDL_ttf.h>
#include "fionatale.h"
#include "sdl_helpers.h"
#include "returnexception.h";

using namespace std;

const int SPEED = 50;

TextTyper::TextTyper()
{

}

void TextTyper::type(string text1, string text2, bool box)
{
	SoundEffectPtr textSnd = sndMgr.load("assets/wav/text2.wav");

	bool done = false;
	bool skip = false;

	Timer fps;
	Timer textTimer;

	SDL_Event event;

	textTimer.start();
	int oldChars = 0;

	int yOffset = 0;
	if (!box)
	{
		yOffset = 40;
	}

	if (box)
	{
		draw_rect(screen, 5, 128, 310, 70, 2);
	}
	else
	{
		SDL_Rect r;
		r.x = 0; r.y = 150; r.w = 320; r.h = 190;
		SDL_FillRect( screen, &r, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
	}
	
	while (!done)
	{
		fps.start();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				throw ReturnException();
			}

			Uint8 key = get_event(&event);

			if (key == NES_B)
			{
				if (skip || (textTimer.get_ticks() / SPEED > (text1.length() + text2.length())))
				{
					done = true;
				}
				else
				{
					skip = true;
				}
			}
		}

		int chars = textTimer.get_ticks() / SPEED;
		if (skip)
		{
			chars = text1.length() + text2.length();
		}

		if (chars <= text1.length())
		{
			SDL_Surface *frame = texMgr.getText(text1.substr(0, chars), FT_COLOUR_WHITE);
			apply_surface(15, 133 + yOffset, frame, screen);
			SDL_Flip(screen);
			SDL_FreeSurface(frame);
		}
		else
		{
			if (chars > text1.length() + text2.length())
			{
				chars = text1.length() + text2.length();
			}

			SDL_Surface *frame1 = texMgr.getText(text1, FT_COLOUR_WHITE);
			apply_surface(15, 133 + yOffset, frame1, screen);

			SDL_Surface *frame2 = texMgr.getText(text2.substr(0, chars - text1.length()), FT_COLOUR_WHITE);
			apply_surface(15, 153 + yOffset, frame2, screen);

			SDL_Flip(screen);

			SDL_FreeSurface(frame1);
			SDL_FreeSurface(frame2);
		}

		if (chars > oldChars)
		{
			textSnd->play();
			oldChars = chars;
		}

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
}
