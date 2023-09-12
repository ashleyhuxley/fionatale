OBJS = fionatale.cpp sdl_helpers.cpp weapon_select.cpp konami.cpp game.cpp timer.cpp texttyper.cpp mainmenu.cpp fight.cpp act.cpp texture.cpp texturemanager.cpp name.cpp mercy.cpp item.cpp pawbat.cpp soul.cpp player.cpp attack.cpp fiona.cpp intro.cpp soundeffect.cpp soundeffectmanager.cpp musicmanager.cpp screm.cpp maze.cpp

OBJ_NAME = fionatale

CC = g++

COMPILER_FLAGS = -w -std=c++11

LINKER_FLAGS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
