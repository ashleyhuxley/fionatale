#include "name.h"
#include "fionatale.h"
#include "sdl_helpers.h"
#include <string>
#include <ctime>
#include "timer.h"
#include <iostream>
#include "soundeffect.h"

using namespace std;

Name::Name()
{
	int c = 65;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (c <= 90)
			{
				chars[x][y] = char(c);
			}
			else
			{
				chars[x][y] = ' ';
			}

			c++;
		}
	}

	name = "";

	posX = 0;
	posY = 0;
}

string Name::getName()
{
	TexturePtr symbols = texMgr.load("assets/symbols.png");

	SoundEffectPtr menuMove = sndMgr.load("assets/wav/menu-move.wav");
	SoundEffectPtr menuSelect = sndMgr.load("assets/wav/menu-select.wav");

	bool done = false;
	SDL_Event event;

	Timer fps;

	while (!done)
	{
		fps.start();

		while (SDL_PollEvent(&event))
		{
			Uint8 key = get_event(&event);

			switch (key)
			{
				case NES_UP:
					posY--;
					if (posY == -1) { posY = 3; }
					menuMove->play();
					break;
				case NES_DOWN:
					posY++;
					if (posY == 4) { posY = 0; }
					menuMove->play();
					break;
				case NES_LEFT:
					posX--;
					if (posX == -1) { posX = 6; }
					menuMove->play();
					break;
				case NES_RIGHT:
					posX++;
					if (posX == 7) { posX = 0; }
					menuMove->play();
					break;
				case NES_START:
					if (name.length() > 0)
					{
						menuSelect->play();
						return name;
					}
					break;
				case NES_SELECT:
					return "DEBUG";
				case NES_B:
					if ((posX == 5) && (posY == 3))
					{
						if (name.length() > 0)
						{
							name = name.substr(0, name.length() - 1);
							menuSelect->play();
						}
					}
					else if ((posX == 6) && (posY == 3))
					{
						if (name.length() > 0)
						{
							menuSelect->play();
							return name;
						}
					}
					else
					{
						if (name.length() <= 10)
						{
							menuSelect->play();
							string s = string(1, chars[posX][posY]);
							name += s;
						}
					}
					break;
				case NES_A:
					if (name.length() > 0)
					{
						menuSelect->play();
						name = name.substr(0, name.length() - 1);
					}
					break;
			}
		}

		clear_screen(screen);

		string n = " ";
		if (name.length() > 0)
		{
			n = name;
		}

		SDL_Surface *title = texMgr.getTitleText("Name the fallen human", FT_COLOUR_WHITE);
		SDL_Surface *nameText = texMgr.getTitleText(n.c_str(), FT_COLOUR_ORANGE);

		apply_surface(160 - (title->w / 2), 10, title, screen);
		apply_surface(160 - (nameText->w / 2), 200, nameText, screen);

		for (int x = 0; x < 7; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				int xx = rand() % 2;
				int yy = rand() % 2;

				int dispX = 40 + (x * 40) + xx;
				int dispY = 60 + (y * 30) + yy;

				if ((x == 5) && (y == 3))
				{
					SDL_Rect rect;
					rect.w = 16;
					rect.h = 16;
					rect.y = 16;
					rect.x = 16;

					if ((x == posX) && (y == posY))
					{
						rect.x -= 16;
					}

					symbols->applyTo(dispX, dispY, screen, &rect);
				}
				else if ((x == 6) && (y == 3))
				{
					SDL_Rect rect;
					rect.w = 16;
					rect.h = 16;
					rect.y = 0;
					rect.x = 16;

					if ((x == posX) && (y == posY))
					{
						rect.x -= 16;
					}

					symbols->applyTo(dispX, dispY, screen, &rect);
				}
				else
				{
					string s = string(1, chars[x][y]);

					SDL_Color col;
					col = FT_COLOUR_WHITE;
					if ((x == posX) && (y == posY))
					{
						col = FT_COLOUR_YELLOW;
					}

					SDL_Surface *chs = texMgr.getText(s.c_str(), col);
					apply_surface(dispX, dispY, chs, screen);
					SDL_FreeSurface(chs);
				}
			}
		}

		SDL_Flip(screen);

		SDL_FreeSurface(title);
		SDL_FreeSurface(nameText);

		if (fps.get_ticks() < 1000 / 20)
		{
			SDL_Delay((1000 / 20) - fps.get_ticks());
		}
	}
}