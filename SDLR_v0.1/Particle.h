#ifndef PARTICLE_H
#define PARTICLE_H

#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "ImageManager.h"
#include "Setup.h"

class ImageManager;
class Setup;


class Particle
{
    public:
        Particle();
        Particle(int x, int y);
        void showParticle(ImageManager &pIm1, Setup &pSet);
        void setCoords(int x, int y);
        bool isDead();
        int const getType();
        int getXPos();
        int getYPos();
        virtual ~Particle();
    protected:
    private:
        const int RED;
        const int ORANGE;
        const int GOLD;
        const int GREEN;
        const int BLUE;
        const int PURPLE;

        int xPos;
        int yPos;

        int animFrame;

        int type;

        //friend class Dot;
        //friend class ImageManager;

        //ImageManager im1;
};

#endif // PARTICLE_H
