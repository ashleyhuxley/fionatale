#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL.h>
#include <memory>
#include <iostream>

class Texture
{
	public:
		Texture(SDL_Surface *surf);
		void applyTo(int x, int y, SDL_Surface* destination, SDL_Rect* clip);
		void applyTo(int x, int y, SDL_Surface* destination);
		bool isAlpha(int x, int y);
		int width();
		int height();

	private:
		SDL_Surface *surface;
};

typedef std::shared_ptr<Texture> TexturePtr;

#endif
