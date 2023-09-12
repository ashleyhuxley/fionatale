#include "texture.h"
#include "SDL/SDL.h"
#include "sdl_helpers.h"

Texture::Texture(SDL_Surface *surf)
{
	surface = surf;
}

void Texture::applyTo(int x, int y, SDL_Surface* destination, SDL_Rect* clip)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(surface, clip, destination, &offset);
}

void Texture::applyTo(int x, int y, SDL_Surface* destination)
{
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(surface, NULL, destination, &offset);
}

bool Texture::isAlpha(int x, int y)
{
	return is_alpha(surface, x, y);
}

int Texture::width()
{
	return surface->w;
}

int Texture::height()
{
	return surface->h;
}