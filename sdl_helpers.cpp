#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "fionatale.h"
#include "timer.h"

using namespace std;

SDL_Surface *load_image(string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

Uint8 get_event(SDL_Event *event)
{
	if (event->type == SDL_JOYAXISMOTION)
	{
		if (event->jaxis.axis == 0)
		{
			if( ( event->jaxis.value < -8000 ) || ( event->jaxis.value > 8000 ) )
			{
				if( event->jaxis.value < 0 )
				{
					return NES_LEFT;
				}
				else
				{
					return NES_RIGHT;
				}
			}
		}
		else
		{
			if( ( event->jaxis.value < -8000 ) || ( event->jaxis.value > 8000 ) )
			{
				if( event->jaxis.value < 0 )
				{
					return NES_UP;
				}
				else
				{
					return NES_DOWN;
				}
			}
		}
	}
	else if (event->type == SDL_JOYBUTTONDOWN)
	{
		return event->jbutton.button;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
			case SDLK_RETURN:
			case SDLK_b:
				return NES_B;
			case SDLK_SPACE:
				return NES_START;
			case SDLK_RCTRL:
			case SDLK_LCTRL:
				return NES_SELECT;
			case SDLK_a:
			case SDLK_ESCAPE:
				return NES_A;
			case SDLK_UP:
				return NES_UP;
			case SDLK_DOWN:
				return NES_DOWN;
			case SDLK_LEFT:
				return NES_LEFT;
			case SDLK_RIGHT:
				return NES_RIGHT;
		}
	}

	return NES_NONE;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

bool is_alpha(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

	Uint32 pixelColor = *(Uint32*)p;

	Uint8 red, green, blue, alpha;
	SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);

	return alpha < 250;
}

void draw_rect(SDL_Surface *surface, int x, int y, int w, int h, int lineWidth)
{
	SDL_Rect outer;
	outer.x = x;
	outer.y = y;
	outer.w = w;
	outer.h = h;

	SDL_Rect inner;
	inner.x = x + lineWidth;
	inner.y = y + lineWidth;
	inner.w = w - (2 * lineWidth);
	inner.h = h - (2 * lineWidth);

	SDL_FillRect( surface, &outer, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
	SDL_FillRect( surface, &inner, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );
}

void clear_screen(SDL_Surface *screen)
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;
	SDL_FillRect(screen, &r, 0x000000);
}

void animate_hitbox(SDL_Surface *screen)
{
	int width = 310;
	Timer fps;
	Timer animate;
	animate.start();

	int time = 1000;
	int max = 70;

	while (width > max)
	{
		fps.start();

		width = 310 - (animate.get_ticks() / (time / 240));
		if (width < max)
		{
			width = max;
		}

		SDL_Rect r;
		r.x = 0;
		r.y = 128;
		r.w = 320;
		r.h = 70;
		SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
		draw_rect(screen, (320 - width) / 2, 128, width, 70, 2);

		SDL_Flip(screen);

		if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		{
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
}

void fps_delay(int ticks)
{
	if( ticks < 1000 / FRAMES_PER_SECOND )
	{
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - ticks );
	}
}
