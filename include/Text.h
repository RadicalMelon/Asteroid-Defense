#ifndef TEXT_H
#define TEXT_H

/*=================================================================================*/

#include "../Globals.h"

/*=================================================================================*/

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
} Text;

/*=================================================================================*/

Text* CreateText(TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour, const char* string, int x, int y);
void RenderText(Text* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour, const char* string, int x, int y);
void DrawText(Text* text, SDL_Renderer* renderer);
void DestroyText(Text* text);

/*=================================================================================*/

#endif // TEXT_H
