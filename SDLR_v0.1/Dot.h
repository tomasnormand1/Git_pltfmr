#ifndef DOT_H
#define DOT_H

#include "Setup.h"
#include "SDL/SDL.h"
#include "ImageManager.h"
#include "Particle.h"
#include "Bullet.h"
#include "World.h"
#include "Vector2.h"

#include <deque>

//#define TOTAL_PARTICLES 30;

using namespace std;

class Particle;
class Bullet;
class ImageManager;
class Setup;
class Vector2;

class Dot
{
    public:
        Dot();
        // handles key presses and adjusts vel
        void handle_input(SDL_Event &e);
        //return x and y vel
        const int getxvel();
        const int getyvel();
        //get mouse vector
        void change_heading(SDL_Event &e);
        // shoots bullets
        void shoot(Setup &pSet);
        //jump
        void jump();
        // moves the dot
        void move(Setup &set, World &pworld, Uint32 deltaTime);
        // show the dot
        //void show(SDL_Surface *source, SDL_Surface *dest, SDL_Surface *pSource, SDL_Surface *pDest);
        // show particles
        int const getPlayerX();
        int const getPlayerY();
        // get the anim frame
        int const get_anim_frame();
        // get the collision
        bool boxLoop(World &pworld);
        // loop through bullets, and show call draw functions
        void showBulletD(ImageManager &pIm1, Setup &pSet);
        // pretty much just loop through particles and call draw on each
        void showParticleD(ImageManager &pIm1, Setup &pSet);

        // set camera position
        void setCamera(Setup &s);

        virtual ~Dot();

    protected:
    private:
        // height and width of dot
        const int DOT_HEIGHT;
        const int DOT_WIDTH;
        const int GRAVITY;
        const int MAX_VEL;
        const int TOTAL_PARTICLES;
        const int TOTAL_BULLETS;
        // min and max gravity values for jumping
        const int MIN_G_VAL;
        const int MAX_G_VAL;

        // array of particle objects
        Particle *particleArray[1000];
        // array of bullets
        deque <Bullet> bulletArray;
        // global aiming vector for player
        Vector2 aim_vector;
        // offsets
        float playerX;
        float playerY;
        // x and y velocities
        float xVel;
        float yVel;
        //animation stuff
        // frame is the fram in teh animation we are at
        // anim status is the status of the character
        int anim_frame_r;
        int anim_frame_l;
        int anim_status;
        int frame_counter;
        // flags for key presses
        bool up;
        bool left;
        bool right;
        bool space;
        int shotcounter;
        float jumpspeed;
        bool jumping;
        bool falling;

        // flag for collision
        int collisionflag;
};

#endif // DOT_H
