#ifndef BULLET_H
#define BULLET_H

#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#include "ImageManager.h"
#include "Setup.h"

class ImageManager;
class Setup;

class Bullet
{
    public:
        Bullet();
        Bullet(int bx, int by, int bxv, int byv);
        const int getBulletX();
        const int getBulletY();
        void showBullet(ImageManager &pIm1, Setup &pSet);
        bool isDeadB();
        virtual ~Bullet();
    protected:
    private:
        int WIDTH;
        int HEIGHT;
        int x;
        int y;
        int xvel;
        int yvel;
        int lifetime;

};

#endif // BULLET_H
