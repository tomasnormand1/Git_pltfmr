#include <cstdlib>
#include <string>
#include <iostream>
#include "Setup.h"
//#include "SoundManager.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

/**
TODO
FIX THE CONSTANTS

*/

//1024
//768
Setup::Setup()
:SCREEN_WIDTH(1024),
SCREEN_HEIGHT(768),
SCREEN_BPP(32),
FRAMES_PER_SECOND(60),
LEVEL_WIDTH(1024),
LEVEL_HEIGHT(768)
{
    screen = NULL;
    camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    //ctor
}

bool Setup::init()
{
    // init
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    std::cout << "screen w: " << SCREEN_WIDTH << '\n' << "screen h: " << SCREEN_HEIGHT << '\n'
    << "screen bpp: " << SCREEN_BPP << '\n' << "fps: " << FRAMES_PER_SECOND << std::endl;
    // set up screen, with, height, depth, new surface
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_DOUBLEBUF);

    //if error in screen init, end
    if(screen == NULL)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // initialise ttf font
    if(TTF_Init() == -1)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    //init the mixer
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return false;
    }

    // set window caption
    SDL_WM_SetCaption("first program", NULL);

    // seed rand
    //srand(SDL_GetTicks());

    return true;
}

SDL_Surface* Setup::getScreen()
{
    return screen;
}

int Setup::getFPS()
{
    return FRAMES_PER_SECOND;
}

void Setup::freeScreen()
{
    SDL_FreeSurface(screen);
}

int Setup::getLevelW()
{
    return LEVEL_WIDTH;
}

int Setup::getLevelH()
{
    return LEVEL_HEIGHT;
}

SDL_Rect Setup::getCamera()
{
    return camera;
}

void Setup::setCameraX(int x)
{
    camera.x = x;
}

void Setup::setCameraY(int y)
{
    camera.y = y;
}

Setup::~Setup()
{
    //dtor
}
