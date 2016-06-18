#include "Cannon.h"

/*=================================================================================*/

Cannon* CreateCannon(SDL_Texture* texture)
{
    // create the cannon and set the texture
    Cannon* cannon = malloc(sizeof(Cannon));
    cannon->texture = texture;

    // set the size and the position of the cannon
    SDL_QueryTexture(cannon->texture, NULL, NULL, &cannon->rect.w, &cannon->rect.h);
    cannon->rect.x = WINDOW_WIDTH;
    cannon->rect.y = WINDOW_HEIGHT;
    cannon->rect.x /= 2;
    cannon->rect.x -= cannon->rect.w / 2;
    cannon->rect.y -= cannon->rect.h / 2;

    // set some other properties
    cannon->angle = 0;
    cannon->mouse_pos_x = 0;
    cannon->mouse_pos_y = 0;
    cannon->shoot_timer = 0.0;
    cannon->can_shoot = SDL_TRUE;

    return cannon;
}

/*=================================================================================*/

void UpdateCannon(Cannon* cannon, float delta_time)
{
    // get the position of the mouse
    SDL_GetMouseState(&cannon->mouse_pos_x, &cannon->mouse_pos_y);
    // do some complex maths to get the angle between the mouse and the cannon
    cannon->angle = ((atan2((cannon->rect.y + (cannon->rect.h / 2)) - cannon->mouse_pos_y, (cannon->rect.x + (cannon->rect.w / 2)) - cannon->mouse_pos_x) * 180.0000) / 3.1416) - 90;
    if (!cannon->can_shoot)
    {
        cannon->shoot_timer += delta_time;
        if (cannon->shoot_timer >= CANNON_DELAY_TIME)
        {
            cannon->shoot_timer = 0.0;
            cannon->can_shoot = SDL_TRUE;
        }
    }
}

/*=================================================================================*/

void DrawCannon(Cannon* cannon, SDL_Renderer* renderer)
{
    // draw the cannon facing the mouse
    SDL_RenderCopyEx(renderer, cannon->texture, NULL, &cannon->rect, cannon->angle, NULL, SDL_FLIP_NONE);
}

/*=================================================================================*/

void DestroyCannon(Cannon* cannon)
{
    free(cannon);
}
