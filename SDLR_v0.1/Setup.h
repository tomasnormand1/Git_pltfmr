#ifndef SETUP_H
#define SETUP_H
#include "SDL/SDL.h"


class Setup
{
    public:
        Setup();
        bool init();
        SDL_Surface* getScreen();
        int getFPS();
        void freeScreen();
        int getLevelW();
        int getLevelH();
        SDL_Rect getCamera();
        void setCameraX(int x);
        void setCameraY(int y);
        virtual ~Setup();
    protected:
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        const int SCREEN_BPP;
        const int FRAMES_PER_SECOND;
        const int LEVEL_WIDTH;
        const int LEVEL_HEIGHT;
        SDL_Surface *screen;
        SDL_Rect camera;
};

#endif // SETUP_H
