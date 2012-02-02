#include "Particle.h"
#include "ImageManager.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <iostream>

using namespace std;

Particle::Particle()
:RED(1),
ORANGE(2),
GOLD(3),
GREEN(4),
BLUE(5),
PURPLE(6)
{
    animFrame = rand() % 5;
}

Particle::Particle(int x, int y)
:RED(1),
ORANGE(2),
GOLD(3),
GREEN(4),
BLUE(5),
PURPLE(6)
{
    animFrame = rand() % 50;
    xPos = x - 5 + (rand() % 20);
    yPos = y  + (rand() % 5);

    switch(rand() % 6)
    {
        case 0: type = RED; break;
        case 1: type = ORANGE; break;
        case 2: type = GOLD; break;
        case 3: type = GREEN; break;
        case 4: type = BLUE; break;
        case 5: type = PURPLE; break;
    }

    //cout << "type: " << type << "\n";
}

void Particle::showParticle(ImageManager &pIm1, Setup &pSet)
{
    pIm1.drawParticles(type, xPos, yPos, pSet);
    //im1.applySurface(xPos, yPos, source, dest);
    animFrame ++;
}

bool Particle::isDead()
{
    //frame = (frame + SDL_GetTicks() % 90);
    //cout << "frame: " << frame << "\n";
    if(animFrame > 50)
    {
        return true;
    }

    return false;
}

int const Particle::getType()
{
    return type;
}

int Particle::getXPos()
{
    return xPos;
}

int Particle::getYPos()
{
    return yPos;
}

Particle::~Particle()
{
    //dtor
}
