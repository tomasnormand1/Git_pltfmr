#ifndef PHYSICS_H
#define PHYSICS_H

#include "SDL/SDL.h"


class Physics
{
    public:
        Physics();
        int check_collision(const SDL_Rect &recA, const SDL_Rect &recB);
        virtual ~Physics();
    protected:
    private:
};

#endif // PHYSICS_H
