#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

/*=================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*=================================================================================*/

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Asteroid Defense"
#define FRAME_RATE_LIMIT 60
#define SHELL_SPEED 2500
#define BACKGROUND_SCROLL_SPEED 150
#define CANNON_DELAY_TIME 0.2
#define ASTEROID_NUMBER 5
#define ASTEROID_START_MAX 1000
#define ASTEROID_SPEED 500
#define ASTEROID_ROTATION_RANGE 5
#define START_LIVES 5
#define LIVES_TEXT "LIVES: %d"
#define TIME_TEXT "TIME: %d"
#define SCORE_TEXT "SCORE: %d"
#define FONT_SIZE 24

/*=================================================================================*/

#endif // DEFINES_H_INCLUDED
