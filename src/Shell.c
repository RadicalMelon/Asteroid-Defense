#include "Shell.h"
#include "Cannon.h"

/*=================================================================================*/

Shell* CreateShell(SDL_Texture* texture, struct Cannon* cannon)
{
    Shell* shell = malloc(sizeof(Shell));
    shell->angle = cannon->angle;

    shell->texture = texture;
    SDL_QueryTexture(shell->texture, NULL, NULL, &shell->rect.w, &shell->rect.h);

    // set the shell's centre to the centre of the cannon
    shell->rect.x = (cannon->rect.x + (cannon->rect.w / 2)) - shell->rect.w / 2;
    shell->rect.y = (cannon->rect.y + (cannon->rect.h / 2)) - shell->rect.h / 2;

    // find out the distance between where the mouse clicked and where the shell is
    float x = (shell->rect.x + (shell->rect.w / 2)) - cannon->mouse_pos_x;
    float y = (shell->rect.y + (shell->rect.h / 2)) - cannon->mouse_pos_y;

    // find the hypotenuse from the shell to where the mouse clicked
    int length = sqrt(pow(x, 2) + pow(y, 2));

    // normalize the vector
    x /= length;
    y /= length;

    // set the shells velocity
    shell->move_x = x * SHELL_SPEED;
    shell->move_y = y * SHELL_SPEED;

    return shell;
}

/*=================================================================================*/

void UpdateShell(Shell* shell, float delta_time)
{
    shell->rect.x -= shell->move_x * delta_time;
    shell->rect.y -= shell->move_y * delta_time;
}

/*=================================================================================*/

void DrawShell(Shell* shell, SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, shell->texture, NULL, &shell->rect, shell->angle, NULL, SDL_FLIP_NONE);
}

/*=================================================================================*/

void DestroyShell(Shell* shell)
{
    free(shell);
}
