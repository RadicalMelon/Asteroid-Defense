#ifndef ASTEROID_H
#define ASTEROID_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    int angle;
    int rotation_speed;
} Asteroid;

/*=================================================================================*/

Asteroid* CreateAsteroid(SDL_Texture* texture);
void SetAsteroidAttributes(Asteroid* asteroid, SDL_Texture* texture);
void UpdateAsteroid(Asteroid* asteroid, float delta_time);
void DrawAsteroid(Asteroid* asteroid, SDL_Renderer* renderer);
void DestroyAsteroid(Asteroid* asteroid);

/*=================================================================================*/

#endif // ASTEROID_H
