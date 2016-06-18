#include "Asteroid.h"

/*=================================================================================*/

Asteroid* CreateAsteroid(SDL_Texture* texture)
{
    Asteroid* asteroid = malloc(sizeof(Asteroid));
    SetAsteroidAttributes(asteroid, texture);
    return asteroid;
}

/*=================================================================================*/

void SetAsteroidAttributes(Asteroid* asteroid, SDL_Texture* texture)
{
    asteroid->texture = texture;
    SDL_QueryTexture(asteroid->texture, NULL, NULL, &asteroid->rect.w, &asteroid->rect.h);
    asteroid->rect.x = rand() % (WINDOW_WIDTH - asteroid->rect.w);
    asteroid->rect.y = -(rand() % ASTEROID_START_MAX + asteroid->rect.h);
    while ((asteroid->rotation_speed = ((float) rand() / (float) RAND_MAX) * (ASTEROID_ROTATION_RANGE - -ASTEROID_ROTATION_RANGE) + -ASTEROID_ROTATION_RANGE) == 0);
}

/*=================================================================================*/

void UpdateAsteroid(Asteroid* asteroid, float delta_time)
{
    asteroid->rect.y += ASTEROID_SPEED * delta_time;
    if ((asteroid->angle += asteroid->rotation_speed) >= 360)
    {
        asteroid->angle = 0;
    }
}

/*=================================================================================*/

void DrawAsteroid(Asteroid* asteroid, SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, asteroid->texture, NULL, &asteroid->rect, asteroid->angle, NULL, SDL_FLIP_NONE);
}

/*=================================================================================*/

void DestroyAsteroid(Asteroid* asteroid)
{
    free(asteroid);
}
