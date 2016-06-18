#ifndef TIMER_H
#define TIMER_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct
{
    int last_time;
    int current_time;
    int frame_time;
    float delta_time;
} Timer;

/*=================================================================================*/

Timer* CreateTimer(void);
void UpdateTimer(Timer* timer);
void DestroyTimer(Timer* timer);

/*=================================================================================*/

#endif // TIMER_H
