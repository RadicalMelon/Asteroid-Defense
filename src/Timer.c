#include "Timer.h"

/*=================================================================================*/

Timer* CreateTimer(void)
{
    Timer* timer = malloc(sizeof(Timer));
    timer->last_time = 0;
    timer->current_time = 0;
    timer->frame_time = 0;
    timer->delta_time = 0.0;
    return timer;
}

/*=================================================================================*/

void UpdateTimer(Timer* timer)
{
    timer->last_time = timer->current_time;
    timer->current_time = SDL_GetTicks();
    timer->frame_time = timer->current_time - timer->last_time;

    if (1000.0 / FRAME_RATE_LIMIT > timer->frame_time)
    {
        SDL_Delay((1000.0 / FRAME_RATE_LIMIT - timer->frame_time) * 2);
    }

    timer->delta_time = timer->frame_time / 1000.0;
}

/*=================================================================================*/

void DestroyTimer(Timer* timer)
{
    free(timer);
}
