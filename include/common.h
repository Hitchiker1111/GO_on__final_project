#ifndef COMMON_H
#define COMMON_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define CONTINUE_GAME SDL_NUM_SCANCODES + 2
#define TO_MENU SDL_NUM_SCANCODES + 6

#define HANDLE_ERROR(msg)                      \
  SDL_Log(msg " ERROR: %s\n", SDL_GetError()); \
  SDL_Quit();                                  \
  exit(EXIT_FAILURE);

typedef struct
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  bool *keyboard;
  int points;
  int type;
  int select;
} App;

extern App app;

#endif