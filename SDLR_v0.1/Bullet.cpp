#include "Bullet.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "ImageManager.h"
#include "Setup.h"
#include "Vector2.h"

Bullet::Bullet()
{
    WIDTH = 1;
    HEIGHT = 1;
    x = 0;
    y = 0;
    xvel = 5;
    yvel = 0;

    lifetime = 0;
}

Bullet::Bullet(int bx, int by, int bxv, int byv)
{
    WIDTH = 1;
    HEIGHT = 1;
    x = bx;
    y = by;
    Vector2 v(bxv, byv);
    xvel = bxv; //+ (rand()+3 % 5);
    yvel = byv; //+ (rand()+2 % 5);

    lifetime = 0;
}

const int Bullet::getBulletX()
{
    return x;
}

const int Bullet::getBulletY()
{
    return y;
}

void Bullet::showBullet(ImageManager &pIm1, Setup &pSet)
{
    x += xvel; //+ (rand() + 3 % 5);
    y += yvel; //+ (rand() + 1 % 5);
    // call imagemanager to draw the bullet to teh screen
    pIm1.drawBullets(x, y, pSet);

    lifetime++;
}

bool Bullet::isDeadB()
{
    if(lifetime > 100)
    {
        return true;
    }

    return false;
}

Bullet::~Bullet()
{
    //dtor
}
