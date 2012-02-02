#include "Timer.h"
#include "SDL/SDL.h"


Timer::Timer()
{
    //ctor
    start_ticks = 0;
    started = false;
    paused_ticks = 0;
    paused = false;

}

void Timer::start()
{
    started = true;
    paused = false;
    start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
    started = false;
    paused = false;
}

int Timer::get_ticks()
{
    if(started == true)
    {
        if(paused == true)
        {
            return paused_ticks;
        }
        else
        {
            return SDL_GetTicks() - start_ticks;
        }
    }
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

Timer::~Timer()
{
    //dtor
}
