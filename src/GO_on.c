#include "../include/GO_on.h"

App app;

int main(int argc, char *argv[])
{
  InitApp();
  InitAudio();
  InitDisplay();

  SDL_Log("新年快乐！");

  while (!app.keyboard[SDL_SCANCODE_ESCAPE])
  {
    DoMenuLogic();

    DoGameLogic();
  }

  atexit(&QuitApp);
  atexit(&QuitDisplay);
  atexit(&QuitAudio);
  atexit(&QuitCharacters);
  atexit(&QuitRoadblocks);
  return 0;
}

static void InitApp()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
  {
    HANDLE_ERROR("INIT SDL");
  }
  if (!IMG_Init(IMG_INIT_PNG))
  {
    HANDLE_ERROR("INIT IMAGE");
  }
  if (!Mix_Init(MIX_INIT_MP3))
  {
    HANDLE_ERROR("INIT MIXER");
  }
  if (TTF_Init() == -1)
  {
    HANDLE_ERROR("INIT TTF");
  }
  app.keyboard = calloc(SDL_NUM_SCANCODES + 15, sizeof(bool));
}

static void QuitApp()
{
  SDL_Quit();
  IMG_Quit();
  Mix_Quit();
  TTF_Quit();
  free(app.keyboard);
}