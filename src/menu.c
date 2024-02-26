#include "../include/menu.h"

static Widget widgets[3][6];
static int selection_menu[3]; // 每个数代表不同菜单的选项序号（从0开始）
static bool exit_menu;

void DoMenuLogic()
{
  SDL_Log("In Menu!");
  Mix_Music *music_menu = PlaySong("../res/sound/music/haruhigake.mp3");
  Mix_PlayMusic(music_menu, -1);

  exit_menu = false;
  InitWidgets();

  // 主菜单
Main_menu:
  selection_menu[TYPE_MAIN] = 0;
  app.type = TYPE_MAIN;
  DrawMenu();
  SDL_Event event;
  while (SDL_WaitEvent(&event) && !exit_menu)
  {
    DoEvent(event);
    DoWidget(NUM_OF_MENU_WIDGETS);
    DrawMenu();
    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
      app.keyboard[SDL_SCANCODE_ESCAPE] = false;
      exit(EXIT_SUCCESS);
    }
  }
  exit_menu = false;

  // 次级菜单
  selection_menu[TYPE_SECONDARY] = 0;
  app.type = TYPE_SECONDARY;
  DrawSecondaryMenu();
  while (SDL_WaitEvent(&event) && !exit_menu)
  {
    DrawSecondaryMenu();
    DoEvent(event);
    DoWidget(NUM_OF_SECONDARY_WIDGETS);

    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
      app.keyboard[SDL_SCANCODE_ESCAPE] = false;
      goto Main_menu;
    }
  }
  exit_menu = false;
  EndSong(music_menu);
}

void DoPauseLogic()
{
  Mix_PauseMusic();
  app.type = TYPE_PAUSE;
  selection_menu[TYPE_PAUSE] = 1;
  SDL_Event event;
  while (SDL_WaitEvent(&event) && !exit_menu)
  {
    DrawPause();
    DoEvent(event);
    DoWidget(NUM_OF_PAUSE_WIDGETS);

    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
      app.keyboard[SDL_SCANCODE_ESCAPE] = false;
      ActionToGame();
    }
  }
  exit_menu = false;
}

void InitWidgets()
{
  widgets[TYPE_MAIN][START_GAME] = (Widget){"Start Game", 540, 360, WIDTH_OF_MENU_WIDGETS + 40, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_MAIN][EXIT_GAME] = (Widget){"Exit Game", 540, 460, WIDTH_OF_MENU_WIDGETS, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionExitGame};
  widgets[TYPE_SECONDARY][0] = (Widget){"soyo", 540, 110, WIDTH_OF_MENU_WIDGETS - 30, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_SECONDARY][1] = (Widget){"tomori", 540, 210, WIDTH_OF_MENU_WIDGETS - 30, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_SECONDARY][2] = (Widget){"anon", 540, 310, WIDTH_OF_MENU_WIDGETS - 30, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_SECONDARY][3] = (Widget){"rikki", 540, 410, WIDTH_OF_MENU_WIDGETS - 30, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_SECONDARY][4] = (Widget){"rana", 540, 510, WIDTH_OF_MENU_WIDGETS - 30, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionStartGame};
  widgets[TYPE_PAUSE][BACK_TO_GAME] = (Widget){"Back to Game", 540, 250, WIDTH_OF_MENU_WIDGETS + 70, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionToGame};
  widgets[TYPE_PAUSE][BACK_TO_MENU] = (Widget){"Back to Menu", 540, 350, WIDTH_OF_MENU_WIDGETS + 70, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionToMenu};
  widgets[TYPE_PAUSE][PAUSE_EXIT_GAME] = (Widget){"Exit Game", 540, 450, WIDTH_OF_MENU_WIDGETS, HEIGHT_OF_MENU_WIDGETS, {0x21, 0x8e, 0xac, 0xff}, ActionExitGame};
}

void DoWidget(int a)
{
  if (app.keyboard[SDL_SCANCODE_UP] || app.keyboard[SDL_SCANCODE_W])
  {
    PrevWidget(a);
    app.keyboard[SDL_SCANCODE_W] = false;
  }
  if (app.keyboard[SDL_SCANCODE_DOWN] || app.keyboard[SDL_SCANCODE_S])
  {
    NextWidget(a);
    app.keyboard[SDL_SCANCODE_S] = false;
  }
  if (app.keyboard[SDL_SCANCODE_SPACE] || app.keyboard[SDL_SCANCODE_RETURN])
  {
    ActWidget();
  }
}

void PrevWidget(int a)
{
  selection_menu[app.type] = (selection_menu[app.type] - 1 + a) % a;
}

void NextWidget(int a)
{
  selection_menu[app.type] = (selection_menu[app.type] + 1) % a;
}

void ActWidget()
{
  app.keyboard[SDL_SCANCODE_RETURN] = false;
  app.keyboard[SDL_SCANCODE_SPACE] = false;
  void (*action)() = widgets[app.type][selection_menu[app.type]].action;
  if (action)
  {
    action();
  }
  selection_menu[app.type] = 0;
}

void ActionStartGame()
{
  app.select = selection_menu[TYPE_SECONDARY];
  exit_menu = true;
}

void ActionExitGame()
{
  exit(EXIT_SUCCESS);
}

void ActionToMenu()
{
  exit_menu = true;
  app.keyboard[TO_MENU] = true;
}

void ActionToGame()
{
  exit_menu = true;
  app.keyboard[CONTINUE_GAME] = true;
}

void DrawMenu()
{
  SDL_RenderClear(app.renderer);

  DrawMenuBackground();

  DrawWidget(&widgets[TYPE_MAIN][0]);
  DrawWidget(&widgets[TYPE_MAIN][1]);
  DrawSelection();

  SDL_RenderPresent(app.renderer);
}

void DrawMenuBackground()
{
  SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderFillRect(app.renderer, NULL);

  SDL_Surface *surface_my_go = SurfaceInit("../res/img/background/title.png");
  SDL_Texture *texture_my_go = TextureInit(app.renderer, surface_my_go);
  SDL_Rect rect_my_go = {.x = 0, .y = 0};
  SDL_QueryTexture(texture_my_go, NULL, NULL, &rect_my_go.w, &rect_my_go.h);
  SDL_RenderCopy(app.renderer, texture_my_go, NULL, &rect_my_go);
  SDL_DestroyTexture(texture_my_go);

  SDL_Surface *surface_CPL = SurfaceInit("../res/img/background/CPL.png");
  SDL_Texture *texture_CPL = TextureInit(app.renderer, surface_CPL);
  SDL_Rect rect_CPL;
  SDL_QueryTexture(texture_CPL, NULL, NULL, &rect_CPL.w, &rect_CPL.h);
  rect_CPL.x = WIDTH_OF_WINDOW - rect_CPL.w;
  rect_CPL.y = 0;
  SDL_RenderCopy(app.renderer, texture_CPL, NULL, &rect_CPL);
  SDL_DestroyTexture(texture_CPL);

  TTF_Font *font_title = TTF_OpenFont("../res/font/Silver.ttf", 200);
  SDL_Color color_title = {0x21, 0x8e, 0xac, 0xff};
  SDL_Surface *surface_title = TTF_RenderText_Blended(font_title, "GO on!!!!!", color_title);
  SDL_Texture *texture_title = TextureInit(app.renderer, surface_title);
  SDL_Rect rect_title;
  SDL_QueryTexture(texture_title, NULL, NULL, &rect_title.w, &rect_title.h);
  rect_title.x = (WIDTH_OF_WINDOW - rect_title.w) / 2;
  rect_title.y = (HEIGHT_OF_WINDOW - rect_title.h) / 2 - 150;
  SDL_RenderCopy(app.renderer, texture_title, NULL, &rect_title);
  SDL_DestroyTexture(texture_title);
  TTF_CloseFont(font_title);
}

void DrawSelection()
{
  SDL_Surface *surface_selection = SurfaceInit("../res/img/background/cursor.png");
  SDL_Texture *texture_selection = TextureInit(app.renderer, surface_selection);
  SDL_Rect rect_selection;
  SDL_QueryTexture(texture_selection, NULL, NULL, &rect_selection.w, &rect_selection.h);
  rect_selection.x = widgets[app.type][selection_menu[app.type]].x - rect_selection.w - 20;
  rect_selection.y = widgets[app.type][selection_menu[app.type]].y + 30;
  SDL_RenderCopy(app.renderer, texture_selection, NULL, &rect_selection);
  SDL_DestroyTexture(texture_selection);
}

void DrawWidget(Widget *widget)
{
  TTF_Font *font_widget = TTF_OpenFont("../res/font/Silver.ttf", 100);
  SDL_Surface *surface_widget = TTF_RenderText_Blended(font_widget, (*widget).name, (*widget).color);
  SDL_Texture *texture_widget = TextureInit(app.renderer, surface_widget);
  SDL_Rect rect_widget = {.x = widget->x, .y = widget->y, .w = widget->w, .h = widget->h};
  SDL_RenderCopy(app.renderer, texture_widget, NULL, &rect_widget);
  SDL_DestroyTexture(texture_widget);
  TTF_CloseFont(font_widget);
}

static void DrawPause()
{
  SDL_RenderClear(app.renderer);

  SDL_Surface *surface_my_go = SurfaceInit("../res/img/background/title.png");
  SDL_Texture *texture_my_go = TextureInit(app.renderer, surface_my_go);
  SDL_Rect rect_my_go = {.x = 0, .y = 0};
  SDL_QueryTexture(texture_my_go, NULL, NULL, &rect_my_go.w, &rect_my_go.h);
  SDL_RenderCopy(app.renderer, texture_my_go, NULL, &rect_my_go);
  SDL_DestroyTexture(texture_my_go);

  SDL_Surface *surface_CPL = SurfaceInit("../res/img/background/CPL.png");
  SDL_Texture *texture_CPL = TextureInit(app.renderer, surface_CPL);
  SDL_Rect rect_CPL;
  SDL_QueryTexture(texture_CPL, NULL, NULL, &rect_CPL.w, &rect_CPL.h);
  rect_CPL.x = WIDTH_OF_WINDOW - rect_CPL.w;
  rect_CPL.y = 0;
  SDL_RenderCopy(app.renderer, texture_CPL, NULL, &rect_CPL);
  SDL_DestroyTexture(texture_CPL);

  DrawWidget(&widgets[2][BACK_TO_GAME]);
  DrawWidget(&widgets[2][BACK_TO_MENU]);
  DrawWidget(&widgets[2][PAUSE_EXIT_GAME]);

  DrawSelection();

  SDL_RenderPresent(app.renderer);
}

void DrawSecondaryMenu()
{
  SDL_RenderClear(app.renderer);

  SDL_Surface *surface_my_go = SurfaceInit("../res/img/background/title.png");
  SDL_Texture *texture_my_go = TextureInit(app.renderer, surface_my_go);
  SDL_Rect rect_my_go = {.x = 0, .y = 0};
  SDL_QueryTexture(texture_my_go, NULL, NULL, &rect_my_go.w, &rect_my_go.h);
  SDL_RenderCopy(app.renderer, texture_my_go, NULL, &rect_my_go);
  SDL_DestroyTexture(texture_my_go);

  SDL_Surface *surface_CPL = SurfaceInit("../res/img/background/CPL.png");
  SDL_Texture *texture_CPL = TextureInit(app.renderer, surface_CPL);
  SDL_Rect rect_CPL;
  SDL_QueryTexture(texture_CPL, NULL, NULL, &rect_CPL.w, &rect_CPL.h);
  rect_CPL.x = WIDTH_OF_WINDOW - rect_CPL.w;
  rect_CPL.y = 0;
  SDL_RenderCopy(app.renderer, texture_CPL, NULL, &rect_CPL);
  SDL_DestroyTexture(texture_CPL);

  for (int i = 0; i < NUM_OF_SECONDARY_WIDGETS; i++)
  {
    DrawWidget(&widgets[TYPE_SECONDARY][i]);
  }

  DrawSelection();

  SDL_RenderPresent(app.renderer);
}