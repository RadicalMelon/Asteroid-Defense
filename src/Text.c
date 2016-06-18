#include "Text.h"

/*=================================================================================*/

Text* CreateText(TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour, const char* string, int x, int y)
{
    Text* text = malloc(sizeof(Text));
    RenderText(text, font, renderer, colour, string, x, y);
    return text;
}

/*=================================================================================*/

void RenderText(Text* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color colour, const char* string, int x, int y)
{
    SDL_Surface* text_surface = TTF_RenderText_Blended(font, string, colour);
    text->texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_QueryTexture(text->texture, NULL, NULL, &text->rect.w, &text->rect.h);
    text->rect.x = x;
    text->rect.y = y;
    SDL_FreeSurface(text_surface);
}

/*=================================================================================*/

void DrawText(Text* text, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, text->texture, NULL, &text->rect);
}

/*=================================================================================*/

void DestroyText(Text* text)
{
    SDL_DestroyTexture(text->texture);
    free(text);
}
