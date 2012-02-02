#ifndef TIMER_H
#define TIMER_H
#include "SDL/SDL.h"


class Timer
{
    public:
        Timer();
        void start();
        void stop();
        int get_ticks();
        bool is_started();
        bool is_paused();
        virtual ~Timer();
    protected:
    private:
        int start_ticks;
        int paused_ticks;
        bool started;
        bool paused;
};

#endif // TIMER_H
