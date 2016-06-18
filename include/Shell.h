#ifndef SHELL_H
#define SHELL_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
    int angle;
    int move_x;
    int move_y;
} Shell;

 struct Cannon;

/*=================================================================================*/

Shell* CreateShell(SDL_Texture* texture, struct Cannon* cannon);
void UpdateShell(Shell* shell, float delta_time);
void DrawShell(Shell* shell, SDL_Renderer* renderer);
void DestroyShell(Shell* shell);

/*=================================================================================*/

#endif // SHELL_H
