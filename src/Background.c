#include "Background.h"

/*=================================================================================*/

Background* CreateBackground(SDL_Texture* texture)
{
    // create a background object
    Background* background = malloc(sizeof(Background));

    // load the background texture and get its size
    background->texture = texture;
    int background_width, background_height;
    SDL_QueryTexture(background->texture, NULL, NULL, &background_width, &background_height);

    // set the source rect
    background->source_rect.w = background_width;
    background->source_rect.h = background_height / 2;
    background->source_rect.x = 0;
    background->source_rect.y = 0;

    // set the destination rect
    background->destination_rect.w = background_width;
    background->destination_rect.h = background_height / 2;
    background->destination_rect.x = 0;
    background->destination_rect.y = 0;

    return background;
}

/*=================================================================================*/

void UpdateBackground(Background* background, float delta_time)
{
    // if the source rect is at the bottom of the destination rect, reset it to the top
    background->source_rect.y += BACKGROUND_SCROLL_SPEED * delta_time;
    if (background->source_rect.y >= background->destination_rect.h)
    {
        background->source_rect.y = 0;
    }
}

/*=================================================================================*/

void DrawBackground(Background* background, SDL_Renderer* renderer)
{
    // draw the visible part of the background
    SDL_RenderCopy(renderer, background->texture, &background->source_rect, &background->destination_rect);
}

/*=================================================================================*/

void DestroyBackground(Background* background)
{
    free(background);
}
