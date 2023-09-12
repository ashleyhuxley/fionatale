#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "texture.h"
#include <map>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <string>

using namespace std;

class TextureManager
{
	public:
		static TextureManager& Instance();
		TexturePtr load(const string &filename);
		void init();
		void cleanUp();
		SDL_Surface* getText(string text, SDL_Color fg);
		SDL_Surface* getTitleText(string text, SDL_Color fg);
		SDL_Surface* getSmallText(string text, SDL_Color fg);

	private:
		map<string, TexturePtr> loadedTextures;
		TTF_Font *dtm;
		TTF_Font *title;
		TTF_Font *small;
};

#endif
