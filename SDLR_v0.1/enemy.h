#ifndef ENEMY_H
#define ENEMY_H

#include "Vector2.h"
#include "ImageManager.h"
#include "Setup.h"

class Vector2;

class enemy
{
    public:
        enemy();
        bool isdead();
        // move the enemy
        void move();
        //blit enemy
        void show_baddies(ImageManager &i, Setup &s);
        virtual ~enemy();
    protected:
    private:
        // x and y coords (null)
        Vector2 xycoords;
        Vector2 xyvel;

        int width;
        int height;

        int lifetime;
};

#endif // ENEMY_H
