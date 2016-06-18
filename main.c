#include "Globals.h"
#include "Timer.h"
#include "Background.h"
#include "Cannon.h"
#include "Shell.h"
#include "LinkedList.h"
#include "Asteroid.h"
#include "Text.h"

/*=================================================================================*/

int main(int argc, char* argv[])
{
    srand(time(NULL));

    // initialize SDL and its extensions
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // create essential things
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "resources/images/background.png");
    SDL_Texture* cannon_texture = IMG_LoadTexture(renderer, "resources/images/cannon.png");
    SDL_Texture* shell_texture = IMG_LoadTexture(renderer, "resources/images/shell.png");
    SDL_Texture* asteroid1_texture = IMG_LoadTexture(renderer, "resources/images/asteroid1.png");
    SDL_Texture* asteroid2_texture = IMG_LoadTexture(renderer, "resources/images/asteroid2.png");
    SDL_Texture* asteroid3_texture = IMG_LoadTexture(renderer, "resources/images/asteroid3.png");
    SDL_Surface* cursor_bitmap = IMG_Load("resources/images/cursor.png");
    TTF_Font* game_font = TTF_OpenFont("resources/fonts/font.ttf", FONT_SIZE);

    SDL_Cursor* cursor = SDL_CreateColorCursor(cursor_bitmap, cursor_bitmap->w / 2, cursor_bitmap->h / 2);
    SDL_SetCursor(cursor);
    SDL_SetWindowGrab(window, SDL_TRUE);

    SDL_Color text_colour = {255, 255, 255, 255};

    int lives = START_LIVES;
    char lives_text_buffer[256];
    sprintf(lives_text_buffer, LIVES_TEXT, lives);
    Text* lives_text = CreateText(game_font, renderer, text_colour, lives_text_buffer, 20, 20);

    float time_survived = 0.0;
    char time_survived_text_buffer[256];
    sprintf(time_survived_text_buffer, TIME_TEXT, (int) time_survived);
    Text* time_text = CreateText(game_font, renderer, text_colour, time_survived_text_buffer, 20, 50);
    int time_survived_old = 0;

    int score = 0;
    char score_text_buffer[256];
    sprintf(score_text_buffer, SCORE_TEXT, score);
    Text* score_text = CreateText(game_font, renderer, text_colour, score_text_buffer, 20, 80);

    Timer* timer = CreateTimer();
    Background* background = CreateBackground(background_texture);
    Cannon* cannon = CreateCannon(cannon_texture);

    ListNode* shell_list = NULL;

    SDL_Rect window_rect;
    SDL_GetWindowSize(window, &window_rect.w, &window_rect.h);
    window_rect.x = 0;
    window_rect.y = 0;

    Asteroid* asteroids[ASTEROID_NUMBER];
    for (int i = 0; i < ASTEROID_NUMBER; i++)
    {
        int decide = rand() % 3 + 1;
        switch (decide)
        {
        case 1:
            asteroids[i] = CreateAsteroid(asteroid1_texture);
            break;
        case 2:
            asteroids[i] = CreateAsteroid(asteroid2_texture);
            break;
        case 3:
            asteroids[i] = CreateAsteroid(asteroid3_texture);
            break;
        default:
            break;
        }
    }

    // main loop
    SDL_Event event;
    SDL_bool running = SDL_TRUE;
    while (running)
    {
        // update the timer
        UpdateTimer(timer);

        // check every event since last frame
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (cannon->can_shoot)
                    {
                        Shell* shell = CreateShell(shell_texture, cannon);
                        if (shell_list == NULL)
                        {
                            shell_list = CreateListNode(NULL, shell);
                        }
                        else
                        {
                            CreateListNode(shell_list, shell);
                        }
                        cannon->can_shoot = SDL_FALSE;
                        cannon->shoot_timer = 0.0;
                    }

                    if (!SDL_GetWindowGrab(window))
                    {
                        SDL_SetWindowGrab(window, SDL_TRUE);
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_SetWindowGrab(window, SDL_FALSE);
                }
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = SDL_FALSE;
                }
            }
        }

        // scroll the background
        UpdateBackground(background, timer->delta_time);
        UpdateCannon(cannon, timer->delta_time);

        time_survived += timer->delta_time;
        if ((int) time_survived > time_survived_old)
        {
            time_survived_old++;
            sprintf(time_survived_text_buffer, TIME_TEXT, (int) time_survived);
            RenderText(time_text, game_font, renderer, text_colour, time_survived_text_buffer, 20, 50);
        }

        if (shell_list != NULL)
        {
            for (int i = 0; i < GetLinkedListLength(shell_list); i++)
            {
                Shell* shell = GetListNodeValue(shell_list, i);
                UpdateShell(shell, timer->delta_time);
                if (!SDL_HasIntersection(&shell->rect, &window_rect))
                {
                    DestroyShell(shell);
                    RemoveListNode(&shell_list, i);
                }
            }
        }

        for (int i = 0; i < ASTEROID_NUMBER; i++)
        {
            UpdateAsteroid(asteroids[i], timer->delta_time);
            if (asteroids[i]->rect.y >= WINDOW_HEIGHT)
            {
                sprintf(lives_text_buffer, LIVES_TEXT, --lives);
                RenderText(lives_text, game_font, renderer, text_colour, lives_text_buffer, 20, 20);

                int decide = rand() % 3 + 1;
                switch (decide)
                {
                case 1:
                    SetAsteroidAttributes(asteroids[i], asteroid1_texture);
                    break;
                case 2:
                    SetAsteroidAttributes(asteroids[i], asteroid2_texture);
                    break;
                case 3:
                    SetAsteroidAttributes(asteroids[i], asteroid3_texture);
                    break;
                default:
                    break;
                }
            }

            if (shell_list != NULL)
            {
                for (int j = 0; j < GetLinkedListLength(shell_list); j++)
                {
                    Shell* shell = GetListNodeValue(shell_list, j);
                    if (SDL_HasIntersection(&shell->rect, &asteroids[i]->rect))
                    {
                        int decide = rand() % 3 + 1;
                        switch (decide)
                        {
                        case 1:
                            SetAsteroidAttributes(asteroids[i], asteroid1_texture);
                            break;
                        case 2:
                            SetAsteroidAttributes(asteroids[i], asteroid2_texture);
                            break;
                        case 3:
                            SetAsteroidAttributes(asteroids[i], asteroid3_texture);
                            break;
                        default:
                            break;
                        }

                        sprintf(score_text_buffer, SCORE_TEXT, ++score);
                        RenderText(score_text, game_font, renderer, text_colour, score_text_buffer, 20, 80);

                        DestroyShell(shell);
                        RemoveListNode(&shell_list, j);
                    }
                }
            }
        }

        if (lives <= 0)
        {
            running = SDL_FALSE;
        }

        // clear and draw everything to the screen
        SDL_RenderClear(renderer);
        DrawBackground(background, renderer);

        if (shell_list != NULL)
        {
            for (int i = 0; i < GetLinkedListLength(shell_list); i++)
            {
                DrawShell(GetListNodeValue(shell_list, i), renderer);
            }
        }

        for (int i = 0; i < ASTEROID_NUMBER; i++)
        {
            DrawAsteroid(asteroids[i], renderer);
        }

        DrawCannon(cannon, renderer);
        DrawText(lives_text, renderer);
        DrawText(time_text, renderer);
        DrawText(score_text, renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_FreeCursor(cursor);
    SDL_FreeSurface(cursor_bitmap);

    DestroyText(lives_text);
    DestroyText(time_text);
    DestroyText(score_text);
    TTF_CloseFont(game_font);

    for (int i = 0; i < ASTEROID_NUMBER; i++)
    {
        DestroyAsteroid(asteroids[i]);
    }

    // clean up
    if (shell_list != NULL)
    {
        for (int i = 0; i < GetLinkedListLength(shell_list); i++)
        {
            DestroyShell(GetListNodeValue(shell_list, i));
        }
    }
    DestroyLinkedList(shell_list);

    DestroyCannon(cannon);
    DestroyBackground(background);
    DestroyTimer(timer);

    SDL_DestroyTexture(asteroid1_texture);
    SDL_DestroyTexture(asteroid2_texture);
    SDL_DestroyTexture(asteroid3_texture);
    SDL_DestroyTexture(shell_texture);
    SDL_DestroyTexture(cannon_texture);
    SDL_DestroyTexture(background_texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // shut down SDL and extensions
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
