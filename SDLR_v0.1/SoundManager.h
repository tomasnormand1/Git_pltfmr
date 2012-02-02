#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include <string>
#include <vector>

class SoundManager
{
    public:
        SoundManager();
        bool soundFiles();
        void playAll();
        void cleanSound();
        Mix_Music* getTrack(int i);
        virtual ~SoundManager();
    protected:
    private:
        std::vector<Mix_Music*> tracks;
        Mix_Music *bgm;
};

#endif // SOUNDMANAGER_H
