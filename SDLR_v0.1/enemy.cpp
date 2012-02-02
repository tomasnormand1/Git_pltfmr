#include "enemy.h"
#include "Vector2.h"
#include "ImageManager.h"
#include "Setup.h"
#include "physics.h"
#include "Bullet.h"

#include "SDL/SDL.h"


enemy::enemy()
{
    //ctor
    Vector2 v1(rand()%400, 0);
    xycoords = v1;
    Vector2 v2( rand() % 30, rand() % 10 );
    xyvel = v2;

    width = 15;
    height = 15;

    lifetime = 0;
}

bool enemy::isdead()
{
    if(xycoords.vy > 600)
    {
        return true;
    }
    return false;
}

void enemy::show_baddies(ImageManager &i, Setup &s)
{
    i.drawenemies(xycoords.vx, xycoords.vy, s);
}

void enemy::move()
{
    xycoords = xycoords + xyvel;

    lifetime++;
}

enemy::~enemy()
{
    //dtor
}
