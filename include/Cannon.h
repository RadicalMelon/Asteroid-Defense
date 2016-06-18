#ifndef CANNON_H
#define CANNON_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct Cannon
{
    SDL_Texture* texture;
    SDL_Rect rect;
    int angle;
    int mouse_pos_x;
    int mouse_pos_y;
    float shoot_timer;
    SDL_bool can_shoot;
} Cannon;

/*=================================================================================*/

Cannon* CreateCannon(SDL_Texture* texture);
void UpdateCannon(Cannon* cannon, float delta_time);
void DrawCannon(Cannon* cannon, SDL_Renderer* renderer);
void DestroyCannon(Cannon* cannon);

/*=================================================================================*/

#endif // CANNON_H
