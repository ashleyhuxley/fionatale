#ifndef SOUL_H
#define SOUL_H

#include "texture.h"
#include "texturemanager.h"
#include <SDL/SDL.h>
#include <string>

using namespace std;

class Soul
{
    private:
	    int x, y;
	    int xVel, yVel;
	    TexturePtr soul;

	    bool hasDbgd;
    
    public:
	    Soul();
	    void handle_input(SDL_Event *event);
	    void move();
    	void show();
    	bool hasCollidedWith(TexturePtr tex, int sx, int sy);
    	bool hasCollidedWith(SDL_Surface *tex, int sx, int sy);
    	void die();
    	bool isMoving();
};

const int OFFSET_X = 127;
const int OFFSET_Y = 130;

#endif
