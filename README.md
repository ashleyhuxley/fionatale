# fionatale

A minigame based on UNDERTALE by Toby Fox. This game is designed to run on a Raspberry Pi with a 320 x 240 LCD display and a NES controller, although it will run on Linux and Windows and can be controlled using a keyboard (Arrow Keys + A, B and Space).

Fionatale features my original character, Fiona Sapphire, as a character to beat in an Undertale style encounter.

Choose your weapon from one of four things that Fiona does not like. Fiona despises hunting, so choosing the hunting horn will unlock hard mode. A mystery item can be unlocked using a particular sequence of key presses...

The object of the game is to work out how to spare Fiona by taking the correct sequence of actions, in true Undertale style. It is also possible to fight, and Fiona will attack the player using her two attacks - swiping with her paw, or screaming at the player - she's a Fennec after all!

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