# fionatale

A minigame based on UNDERTALE by Toby Fox. This game is designed to run on a Raspberry Pi with a 320 x 240 LCD display and a NES controller.

## Dependencies

libsdl1.2-dev
libsdl-image1.2-dev
libsdl-mixer1.2-dev
libsdl-ttf2.0-dev


## Compiling on Windows using MinGW

Install GCC and the SDL libraries:

```
pacman -S mingw-w64-i686-gcc
pacman -S mingw-w64-i686-SDL
pacman -S mingw-w64-i686-SDL_image
pacman -S mingw-w64-i686-SDL_ttf
pacman -S mingw-w64-i686-SDL_mixer
```

Run the followung command:

```
g++ fionatale.cpp sdl_helpers.cpp weapon_select.cpp konami.cpp game.cpp timer.cpp texttyper.cpp mainmenu.cpp fight.cpp act.cpp texture.cpp texturemanager.cpp name.cpp mercy.cpp item.cpp pawbat.cpp soul.cpp player.cpp attack.cpp fiona.cpp intro.cpp soundeffect.cpp soundeffectmanager.cpp musicmanager.cpp screm.cpp maze.cpp -w -std=c++11 -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image -o fionatale.exe -Dmain=SDL_main -lSDLmain -mwindows
```