#ifndef DISPLAY_H
#define DISPLAY_H

#include "../common.h"
#include "audio.h"

#define WIDTH_OF_WINDOW 1280
#define HEIGHT_OF_WINDOW 720

typedef void (*Action)();
typedef struct
{
  char const *name;
  int x, y, w, h;
  SDL_Color color;
  Action action;
} Widget;

void InitDisplay();
void QuitDisplay();


SDL_Window *WindowInit(const char *title, int x, int y, int w, int h, Uint32 flags);
SDL_Renderer *RendererInit(SDL_Window *window, int index, Uint32 flags);
SDL_Surface *SurfaceInit(const char *file);
SDL_Texture *TextureInit(SDL_Renderer *renderer, SDL_Surface *surface);

#endif