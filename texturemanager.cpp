#include "texturemanager.h"
#include "SDL/SDL_image.h"

using namespace std;

TextureManager& TextureManager::Instance()
{
	static TextureManager instance;
	return instance;
}

TexturePtr TextureManager::load(const string &filename)
{
	auto texIterator = loadedTextures.find(filename);
	if (texIterator != loadedTextures.end())
	{
		return texIterator->second;
	}

	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	TexturePtr newTexture = make_shared<Texture>(optimizedImage);

	loadedTextures.insert(make_pair(filename, newTexture));

	return newTexture;
}

void TextureManager::init()
{
	dtm = TTF_OpenFont("assets/DTM-Sans.ttf", 14);
	title = TTF_OpenFont("assets/DTM-Sans.ttf", 26);
	small = TTF_OpenFont("assets/DTM-Sans.ttf", 12);
}

void TextureManager::cleanUp()
{
	TTF_CloseFont(dtm);
	TTF_CloseFont(title);
	TTF_CloseFont(small);
}

SDL_Surface* TextureManager::getText(string text, SDL_Color fg)
{
	return TTF_RenderText_Solid(dtm, text.c_str(), fg);
}

SDL_Surface* TextureManager::getTitleText(string text, SDL_Color fg)
{
	return TTF_RenderText_Solid(title, text.c_str(), fg);
}

SDL_Surface* TextureManager::getSmallText(string text, SDL_Color fg)
{
	return TTF_RenderText_Solid(small, text.c_str(), fg);
}