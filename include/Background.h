#ifndef BACKGROUND_H
#define BACKGROUND_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect source_rect;
    SDL_Rect destination_rect;
} Background;

/*=================================================================================*/

Background* CreateBackground(SDL_Texture* texture);
void UpdateBackground(Background* background, float delta_time);
void DrawBackground(Background* background, SDL_Renderer* renderer);
void DestroyBackground(Background* background);

/*=================================================================================*/

#endif // BACKGROUND_H
