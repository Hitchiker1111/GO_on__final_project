#include "../../include/utils/input.h"

static void DoQuit(SDL_QuitEvent quit);
static void DoKeydown(SDL_KeyboardEvent key);
static void DoKeyup(SDL_KeyboardEvent key);
static void DoMousebuttondown(SDL_MouseButtonEvent button);
static void DoMousebuttonup(SDL_MouseButtonEvent button);

void DoEvent(SDL_Event event)
{
  switch (event.type)
  {
  case SDL_QUIT:
    DoQuit(event.quit);
    return;
  case SDL_KEYDOWN:
    DoKeydown(event.key);
    break;
  case SDL_KEYUP:
    DoKeyup(event.key);
    break;
  case SDL_MOUSEBUTTONDOWN:
    DoMousebuttondown(event.button);
    break;
  case SDL_MOUSEBUTTONUP:
    DoMousebuttonup(event.button);
    break;
  default:
    break;
  }
}

static void DoQuit(SDL_QuitEvent quit)
{
  app.keyboard[SDL_SCANCODE_ESCAPE] = true;
  SDL_Log("Quit! %d", quit.timestamp);
}

static void DoKeydown(SDL_KeyboardEvent key)
{
  app.keyboard[key.keysym.scancode] = true;
  SDL_Log("Key Pressed : %s!", SDL_GetKeyName(key.keysym.sym));
}

static void DoKeyup(SDL_KeyboardEvent key)
{
  app.keyboard[key.keysym.scancode] = false;
  SDL_Log("Key Released : %s!", SDL_GetKeyName(key.keysym.sym));
}

static void DoMousebuttondown(SDL_MouseButtonEvent button)
{
  switch (button.button)
  {
  case SDL_BUTTON_LEFT:
    SDL_Log("Mouse Pressed : Left!");
    break;
  case SDL_BUTTON_RIGHT:
    SDL_Log("Mouse Pressed : Right!");
    break;
  case SDL_BUTTON_MIDDLE:
    SDL_Log("Mouse Pressed : Middle!");
    break;
  default:
    SDL_Log("Function DoMousebuttondown switched to default!");
    break;
  }
}

static void DoMousebuttonup(SDL_MouseButtonEvent button)
{
  switch (button.button)
  {
  case SDL_BUTTON_LEFT:
    SDL_Log("Mouse Released : Left!");
    break;
  case SDL_BUTTON_RIGHT:
    SDL_Log("Mouse Released : Right!");
    break;
  case SDL_BUTTON_MIDDLE:
    SDL_Log("Mouse Released : Middle!");
    break;
  default:
    SDL_Log("Function DoMousebuttonup switched to default!");
    break;
  }
}