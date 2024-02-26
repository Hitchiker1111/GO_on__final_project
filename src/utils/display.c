#include "../../include/utils/display.h"

void InitDisplay()
{
  app.window = WindowInit("my heart will go on", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  app.renderer = RendererInit(app.window, -1, SDL_RENDERER_ACCELERATED);
}

void QuitDisplay()
{
  TTF_CloseFont(app.font);
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
}



SDL_Window *WindowInit(const char *title, int x, int y, int w, int h, Uint32 flags)
{
  SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, flags);
  if (window == NULL)
  {
    HANDLE_ERROR("WINDOW INIT");
  }
  return window;
}

SDL_Renderer *RendererInit(SDL_Window *window, int index, Uint32 flags)
{
  SDL_Renderer *renderer = SDL_CreateRenderer(window, index, flags);
  if (renderer == NULL)
  {
    HANDLE_ERROR("RENDERER INIT");
  }
  return renderer;
}

SDL_Surface *SurfaceInit(const char *file)
{
  SDL_Surface *surface = IMG_Load(file);
  if (surface == NULL)
  {
    HANDLE_ERROR("SURFACE GENERATE");
  }
  return surface;
}

SDL_Texture *TextureInit(SDL_Renderer *renderer, SDL_Surface *surface)
{
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  if (texture == NULL)
  {
    HANDLE_ERROR("TEXTURE GAIN");
  }
  return texture;
}

