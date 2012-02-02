#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_opengl.h"

#include <string>
#include <sstream>
#include <iostream>

#include "Dot.h"
#include "Setup.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include "Particle.h"
#include "Bullet.h"
//#include "Physics.h"
#include "World.h"
// Copyright Tomas Normand

using namespace std;

/**

kind of in order...

TODO:

done -- put test rect into world
done -- check collision in movement function
done -- make player hit the wall
done -- scrolling levels
done -- shooting bullets
done -- tiled map with boxes
done -- make into platformer

change to openGL

add velocity to particles
particles on collisions
do player movement by time instead of frames
enemies
random background generation using diamond squared
sounds with collisions
quantise sounds to a 16 beat track
game saves
gui
high score board




*/

int main ( int argc, char** argv )
{
    Setup setup1;
    //cerr << "address of Setup: " << &setup1 << '\n';
    ImageManager im1;
    SoundManager sm1;
    Dot myDot;
    World world1;
    cout << "rest of main \n";

    if(setup1.init() == false)
    {
        return 1;
    }
    //newScreen = setup1.getScreen();

    if(im1.loadFont() == false)
    {
        return 1;
    }


    if(im1.getFiles() == false)
    {
        cout << "error  loading images" << endl;
        return 1;
    }


    if(sm1.soundFiles() == false)
    {
        cout << "error loading sounds \n";
        return 1;
    }

    if(world1.set_tiles() == false)
    {
    	cout  << "error loading map \n";
    	return 1;
    }
    //Mix_Music* bgm = sm1.getTrack(0);
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // centre the bitmap on screen
    //SDL_Rect dstrect;
    //dstrect.x = (screen->w - bmp->w) / 2;
    //dstrect.y = (screen->h - bmp->h) / 2;

    Timer frames1;
    Timer delta;
    delta.start();

    // program main loop
    bool done = false;
    while (done == false)
    {
        frames1.start();
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            //cout << &event << endl;
            //SDL_Event *e = &event;

            myDot.change_heading(event);
            myDot.handle_input(event);

            if(event.type == SDL_QUIT)
            {
                done = true;
            }
            // get keystates
            //Uint8 *keystates = SDL_GetKeyState(NULL);

            if(event.type == SDL_KEYDOWN)
            {

                if(event.key.keysym.sym == SDLK_p)
                {
                    if(Mix_PlayingMusic() == 0)
                    {
                        sm1.playAll();
                    }
                    else
                    {
                        if(Mix_PausedMusic() == 1)
                        {
                            Mix_ResumeMusic();
                        }
                        else
                        {
                            Mix_PauseMusic();
                        }
                    }
                }

                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = true;
                }
            }
        }

        myDot.move(setup1, world1, delta.get_ticks());
        myDot.shoot(setup1);
        delta.start();
        myDot.setCamera(setup1);

        im1.drawAll(myDot, setup1, world1);
        myDot.showParticleD(im1, setup1);

        im1.drawPlayer(setup1, myDot);
        myDot.showBulletD(im1, setup1);



        /**
        Uint8 *keystates = SDL_GetKeyState(NULL);
        if(keystates[SDLK_p])
        {
            // key state template
        }
        **/


        //SDL_Surface* test = TTF_RenderText_Solid(im1.getFont(), "test", im1.getColour());
        //im1.applySurface(10, 10, test, newScreen);



        if(SDL_Flip(setup1.getScreen()) == -1)
        {
            return 1;
        }

        //framecount++;

        //cout << "frames" << SDL_GetTicks() << endl;

        if(frames1.get_ticks() < 1000 / setup1.getFPS())
        {
            SDL_Delay((1000 / setup1.getFPS()) - frames1.get_ticks());
            //cout << "delay" << 1000 / setup1.getFPS() - frames1.get_ticks();
        }

    }// end main loop

    //Mix_FreeMusic(bgm);
    setup1.freeScreen();
    im1.clean();
    sm1.cleanSound();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
