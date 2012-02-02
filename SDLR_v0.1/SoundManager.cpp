#include "SoundManager.h"
#include "Setup.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


SoundManager::SoundManager()
{
    bgm = NULL;

    //vector <Mix_Music*> tracks;
    //ctor
}

bool SoundManager::soundFiles()
{
    // sound files
    bgm = Mix_LoadMUS("res/music/aband.wav");


    if(bgm == NULL)
    {
        cout << "bgm = null \n";
        return false;
    }

    cout << "bgm = !null \n";
    tracks.push_back(bgm);
    cout << "push back bgm \n";
    return true;
}

void SoundManager::playAll()
{
    Mix_PlayMusic(bgm, -1);
}


void SoundManager::cleanSound()
{
    for(int i = 0; i < tracks.size(); i++)
    {
        Mix_FreeMusic(tracks.at(i));
    }

    tracks.clear();

    Mix_CloseAudio();
}

Mix_Music* SoundManager::getTrack(int i)
{
    return tracks.at(i);
}

SoundManager::~SoundManager()
{
    //dtor
}
