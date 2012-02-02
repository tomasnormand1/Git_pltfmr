#include "physics.h"
#include "SDL/SDL.h"

Physics::Physics()
{
    //ctor
}

int Physics::check_collision(const SDL_Rect &recA, const SDL_Rect &recB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // calculate sides of rectangles
    leftA = recA.x;
    rightA = recA.x + recA.w;
    topA = recA.y;
    bottomA = recA.y + recA.h;

    leftB = recB.x;
    rightB = recB.x + recB.w;
    topB = recB.y;
    bottomB = recB.y + recB.h;

    // check for collisions
    /*
    if(leftA < rightB && rightA > leftB && leftA < leftB && !((topA < topB) || (bottomA > bottomB)))
        // right side collision
    	return 1;
    if(leftA < rightB && rightA > leftB && leftA > leftB && !((topA < topB) || (bottomA > bottomB)))
        // right side collision
        return 2;
    if(topA < bottomB && bottomA > topB && bottomA < bottomB && !((rightA < leftB) || (leftA > rightB)))
        // bottom side collision
        return 3;
    if(topA < bottomB && bottomA > topB && bottomA > bottomB && !((rightA < leftB) || (leftA > rightB)))
        // top side collision
        return 4;
    */


    // normal col det
    if(leftA >= rightB)
        return 0;
    if(rightA <= leftB)
        return 0;
    if(topA >= bottomB)
        return 0;
    if(bottomA <= topB)
        return 0;


    // else if none, return true
    return 1;
}

Physics::~Physics()
{
    //dtor
}
