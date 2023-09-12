#ifndef SDL_HELPERS_H
#define SDL_HELPERS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

SDL_Surface *load_image(string filename);

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

void draw_rect(SDL_Surface *surface, int x, int y, int w, int h, int lineWidth);

void clear_screen(SDL_Surface *screen);

bool is_alpha(SDL_Surface *surface, int x, int y);

void animate_hitbox(SDL_Surface *screen);

Uint8 get_event(SDL_Event *event);

void fps_delay(int ticks);

#endif
