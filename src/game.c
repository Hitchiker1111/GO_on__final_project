#include "../include/game.h"

static int selection_game[4];

void DoGameLogic()
{
  // music and initialization
  tracks[0] = 0, tracks[1] = 1280;
  trackpos[0] = UP_MARGIN, trackpos[1] = UP_MARGIN + HEIGHT_OF_TRACK + GAP, trackpos[2] = trackpos[1] + HEIGHT_OF_TRACK + GAP;
  selection_game[CHARACTER_SELECT] = app.select, selection_game[TRACK_SELECT] = 1;
  ticks[1] = 0;
  InitCharacters();
  InitRoadblocks();
  Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].opening, 0);
  DrawGame();
  while (Mix_Playing(-1))
  {
    SDL_Delay(50);
  }
  Mix_Music *music_in_game = PlaySong("../res/sound/music/music_in_game.mp3");
  chunk_coin = InitChunk("../res/sound/chunk/coin.mp3");
  chunk_dead = InitChunk("../res/sound/chunk/dead.mp3");
// 主体
Game:
  DoMainPart();

  // 暂停画面
  if (app.keyboard[SDL_SCANCODE_ESCAPE])
  {
    app.keyboard[SDL_SCANCODE_ESCAPE] = false;
    Mix_PauseMusic();
    DoPauseLogic();
    if (app.keyboard[CONTINUE_GAME])
    {
      SDL_Log("continue!");
      app.keyboard[CONTINUE_GAME] = false;
      goto Game;
    }
    else if (app.keyboard[TO_MENU])
    {
      SDL_Log("back!");
      app.keyboard[TO_MENU] = false;
      goto Menu;
    }
  }

  // 死亡结算画面
  Mix_HaltMusic();
  Mix_HaltChannel(-1);
  Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].fail, 0);

  while (Mix_Playing(-1))
  {
    SDL_Delay(50);
  }

  DrawEndgame();

  Mix_PlayChannel(-1, chunk_dead, 0);
  Mix_Music *music_dead = PlaySong("../res/sound/chunk/kan.mp3");
  SDL_Event event;
  ticks[2] = SDL_GetTicks();
  bool flag = false;
  while ((SDL_GetTicks() - ticks[2]) < 13000 && !flag)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
      {
        flag = true;
        break;
      }
    }
  }
  EndChunk(chunk_dead);
  EndSong(music_dead);

Menu:
  QuitCharacters();
  QuitRoadblocks();
  EndSong(music_in_game);
}

static void DoGameInput()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    DoEvent(event);
  }
}

static void DrawGame()
{
  SDL_RenderClear(app.renderer);

  DrawGameBackground();

  DrawTracks();
  UpdateTracks();

  GenerateRoadblocks();
  DrawRoadblocks();
  UpdateRoadblocks();

  DrawCharacter();
  UpdateCharacter();

  SDL_RenderPresent(app.renderer);
}

static void HandleFps()
{
  SDL_Delay(1000 / FPS);
}

static void DrawGameBackground()
{
  SDL_Surface *surface_game_background = SurfaceInit("../res/img/background/RiNG.png");
  SDL_Texture *texture_game_background = TextureInit(app.renderer, surface_game_background);
  SDL_RenderCopy(app.renderer, texture_game_background, NULL, NULL);
  SDL_DestroyTexture(texture_game_background);
}

static void DrawTracks()
{
  SDL_Surface *surface_track = SurfaceInit("../res/img/background/track.png");
  SDL_Texture *texture_track = TextureInit(app.renderer, surface_track);
  SDL_SetTextureAlphaMod(texture_track, 200);
  for (int i = 0; i < 3; i++)
  {
    SDL_Rect rect_left_track = {.x = tracks[0], .y = trackpos[i], .w = WIDTH_OF_TRACK, .h = HEIGHT_OF_TRACK};
    SDL_Rect rect_right_track = {.x = tracks[1], .y = trackpos[i], .w = WIDTH_OF_TRACK, .h = HEIGHT_OF_TRACK};
    SDL_RenderCopy(app.renderer, texture_track, NULL, &rect_left_track);
    SDL_RenderCopy(app.renderer, texture_track, NULL, &rect_right_track);
  }
  SDL_DestroyTexture(texture_track);
}

static void UpdateTracks()
{
  int temp = abs(tracks[0] - RateInGame(ticks[1]));
  tracks[0] = 0 - temp % WIDTH_OF_TRACK;

  tracks[1] = tracks[0] + WIDTH_OF_TRACK;
}

static void InitCharacters()
{
  characters = malloc(NUM_OF_CHARACTERS * sizeof(Character));

  characters[0].surface = SurfaceInit("../res/img/character/soyorin.png");
  characters[0].opening = InitChunk("../res/sound/chunk/opening/soyorin.mp3");
  characters[0].boost = InitChunk("../res/sound/chunk/boost/soyorin.mp3");
  characters[0].fail = InitChunk("../res/sound/chunk/fail/soyorin.mp3");
  characters[0].move = InitChunk("../res/sound/chunk/move/soyorin.mp3");

  characters[1].surface = SurfaceInit("../res/img/character/tomori.png");
  characters[1].opening = InitChunk("../res/sound/chunk/opening/tomori.mp3");
  characters[1].boost = InitChunk("../res/sound/chunk/boost/tomori.mp3");
  characters[1].fail = InitChunk("../res/sound/chunk/fail/tomori.mp3");
  characters[1].move = InitChunk("../res/sound/chunk/move/tomori.mp3");

  characters[2].surface = SurfaceInit("../res/img/character/anon.png");
  characters[2].opening = InitChunk("../res/sound/chunk/opening/anon.mp3");
  characters[2].boost = InitChunk("../res/sound/chunk/boost/anon.mp3");
  characters[2].fail = InitChunk("../res/sound/chunk/fail/anon.mp3");
  characters[2].move = InitChunk("../res/sound/chunk/move/anon.mp3");

  characters[3].surface = SurfaceInit("../res/img/character/rikki.png");
  characters[3].opening = InitChunk("../res/sound/chunk/opening/rikki.mp3");
  characters[3].boost = InitChunk("../res/sound/chunk/boost/rikki.mp3");
  characters[3].fail = InitChunk("../res/sound/chunk/fail/rikki.mp3");
  characters[3].move = InitChunk("../res/sound/chunk/move/rikki.mp3");

  characters[4].surface = SurfaceInit("../res/img/character/rana.png");
  characters[4].opening = InitChunk("../res/sound/chunk/opening/rana.mp3");
  characters[4].boost = InitChunk("../res/sound/chunk/boost/rana.mp3");
  characters[4].fail = InitChunk("../res/sound/chunk/fail/rana.mp3");
  characters[4].move = InitChunk("../res/sound/chunk/move/rana.mp3");

  for (int i = 0; i < NUM_OF_CHARACTERS; i++)
  {
    characters[i].texture = TextureInit(app.renderer, characters[i].surface);
    SDL_QueryTexture(characters[i].texture, NULL, NULL, &characters[i].w, &characters[i].h);
    characters[i].x = (WIDTH_OF_TRACK - characters[0].w) / 2;
    characters[i].y = trackpos[TRACK2] - CHARACTERPOS;
  }
}

void QuitCharacters()
{
  SDL_DestroyTexture(characters[0].texture);
  free(characters);
}

static void DrawCharacter()
{
  SDL_Rect rect_character;
  rect_character.w = characters[selection_game[CHARACTER_SELECT]].w;
  rect_character.h = characters[selection_game[CHARACTER_SELECT]].h;
  rect_character.x = characters[selection_game[CHARACTER_SELECT]].x;
  rect_character.y = characters[selection_game[CHARACTER_SELECT]].y;
  SDL_Point point = {.x = rect_character.w / 2, .y = rect_character.h * 3 / 4};
  int a = SDL_RenderCopyEx(
      app.renderer,
      characters[selection_game[CHARACTER_SELECT]].texture,
      NULL,
      &rect_character,
      characters[selection_game[CHARACTER_SELECT]].angle,
      &point,
      SDL_FLIP_NONE);
  if (a < 0)
  {
    HANDLE_ERROR("RENDER CHARACTER");
  }
}

static void UpdateCharacter()
{
  if (is_jumping)
  {
    characters[selection_game[CHARACTER_SELECT]].y += characters[selection_game[CHARACTER_SELECT]].vy;
    characters[selection_game[CHARACTER_SELECT]].vy += characters[selection_game[CHARACTER_SELECT]].ay;
    if (characters[selection_game[CHARACTER_SELECT]].y >= ground)
    {
      characters[selection_game[CHARACTER_SELECT]].y = ground;
      is_jumping = false;
      SDL_Log("Jumped!");
    }
  }
  else if (is_rolling)
  {
    characters[selection_game[CHARACTER_SELECT]].angle += characters[selection_game[CHARACTER_SELECT]].v_angle;
    characters[selection_game[CHARACTER_SELECT]].v_angle += characters[selection_game[CHARACTER_SELECT]].a_angle;
    if (characters[selection_game[CHARACTER_SELECT]].angle >= 0)
    {
      characters[selection_game[CHARACTER_SELECT]].angle = 0;
      is_rolling = false;
      SDL_Log("Rolled!");
    }
  }
  else if (is_changing_tracks)
  {
    characters[selection_game[CHARACTER_SELECT]].y += characters[selection_game[CHARACTER_SELECT]].vy;
    int delta = abs(characters[selection_game[CHARACTER_SELECT]].y - trackpos[selection_game[TRACK_SELECT]] + CHARACTERPOS);
    if (delta <= CHANGE_VELOCITY)
    {
      characters[selection_game[CHARACTER_SELECT]].y = trackpos[selection_game[TRACK_SELECT]] - CHARACTERPOS;
      is_changing_tracks = false;
      SDL_Log("Track Changed!");
    }
  }
  else if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_S])
  {
    ChangeTracks();
  }
  else if (app.keyboard[SDL_SCANCODE_SPACE])
  {
    Jump();
  }
  else if (app.keyboard[SDL_SCANCODE_C])
  {
    Roll();
  }
}

static void Jump()
{
  SDL_Log("Jumping!");
  is_jumping = true;
  Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].move, 0);
  ground = characters[selection_game[CHARACTER_SELECT]].y;
  characters[selection_game[CHARACTER_SELECT]].ay = JUMP_ACCELERATION;
  characters[selection_game[CHARACTER_SELECT]].vy = JUMP_VELOCITY;

  app.keyboard[SDL_SCANCODE_SPACE] = false;
}

static void Roll()
{
  SDL_Log("Rolling!");
  is_rolling = true;
  Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].move, 0);
  characters[selection_game[CHARACTER_SELECT]].v_angle = SPIN_VELOCITY;
  characters[selection_game[CHARACTER_SELECT]].a_angle = SPIN_ACCELERATION;

  app.keyboard[SDL_SCANCODE_C] = false;
}

static void ChangeTracks()
{
  SDL_Log("Changing Tracks!");

  int temp = selection_game[TRACK_SELECT];
  if (app.keyboard[SDL_SCANCODE_W])
  {
    if (temp == 0)
    {
      SDL_Log("Track Neednot Change!");
      is_changing_tracks = false;
    }
    else
    {
      is_changing_tracks = true;
      Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].move, 0);
      selection_game[TRACK_SELECT] = temp - 1;
      characters[selection_game[CHARACTER_SELECT]].vy = -CHANGE_VELOCITY;
    }
  }
  else if (app.keyboard[SDL_SCANCODE_S])
  {
    if (temp == 2)
    {
      SDL_Log("Track Neednot Change!");
      is_changing_tracks = false;
    }
    else
    {
      is_changing_tracks = true;
      Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].move, 0);
      selection_game[TRACK_SELECT] = temp + 1;
      characters[selection_game[CHARACTER_SELECT]].vy = CHANGE_VELOCITY;
    }
  }

  app.keyboard[SDL_SCANCODE_W] = false;
  app.keyboard[SDL_SCANCODE_S] = false;
}

static void InitRoadblocks()
{
  roadblocks = calloc(TYPE_OF_ROADBLOCKS, sizeof(Roadblock));
  for (int i = 0; i < TYPE_OF_ROADBLOCKS; i++)
  {
    for (int j = 0; j < NUM_OF_TRACKS; j++)
    {
      roadblocks[i].list[j] = calloc(1, sizeof(LinkedList));
      InitList(roadblocks[i].list[j]);
    }
  }

  roadblocks[JUMP_BLOCK].surface = SurfaceInit("../res/img/roadblock/jump.png");
  roadblocks[JUMP_BLOCK].texture = TextureInit(app.renderer, roadblocks[JUMP_BLOCK].surface);
  SDL_QueryTexture(roadblocks[JUMP_BLOCK].texture, NULL, NULL, &roadblocks[JUMP_BLOCK].w, &roadblocks[JUMP_BLOCK].h);

  roadblocks[ROLL_BLOCK].surface = SurfaceInit("../res/img/roadblock/roll.png");
  roadblocks[ROLL_BLOCK].texture = TextureInit(app.renderer, roadblocks[ROLL_BLOCK].surface);
  SDL_QueryTexture(roadblocks[ROLL_BLOCK].texture, NULL, NULL, &roadblocks[ROLL_BLOCK].w, &roadblocks[ROLL_BLOCK].h);

  roadblocks[BLACKHOLE].surface = SurfaceInit("../res/img/roadblock/blackhole.png");
  roadblocks[BLACKHOLE].texture = TextureInit(app.renderer, roadblocks[BLACKHOLE].surface);
  SDL_QueryTexture(roadblocks[BLACKHOLE].texture, NULL, NULL, &roadblocks[BLACKHOLE].w, &roadblocks[BLACKHOLE].h);

  roadblocks[COIN].surface = SurfaceInit("../res/img/roadblock/coin.png");
  roadblocks[COIN].texture = TextureInit(app.renderer, roadblocks[COIN].surface);
  SDL_QueryTexture(roadblocks[COIN].texture, NULL, NULL, &roadblocks[COIN].w, &roadblocks[COIN].h);

  roadblocks[PARFAIT].surface = SurfaceInit("../res/img/roadblock/parfait.png");
  roadblocks[PARFAIT].texture = TextureInit(app.renderer, roadblocks[PARFAIT].surface);
  SDL_QueryTexture(roadblocks[PARFAIT].texture, NULL, NULL, &roadblocks[PARFAIT].w, &roadblocks[PARFAIT].h);
}

void QuitRoadblocks()
{
  for (int i = 0; i < TYPE_OF_ROADBLOCKS; i++)
  {
    SDL_DestroyTexture(roadblocks[i].texture);
  }
  for (int i = 0; i < TYPE_OF_ROADBLOCKS; i++)
  {
    for (int j = 0; j < NUM_OF_TRACKS; j++)
    {
      free(roadblocks[i].list[j]);
    }
  }
  free(roadblocks);
}

static void GenerateRoadblocks()
{
  if (!Safe(95))
  {
    int selected_type = selection_game[ROADBLOCK_TYPE_SELECT];
    int selected_track = selection_game[ROADBLOCK_TRACK_SELECT];

    // 避免素材重叠
    for (int j = 0; j < TYPE_OF_ROADBLOCKS; j++)
    {
      if (!IsEmpty(roadblocks[j].list[selected_track]) &&
          roadblocks[j].list[selected_track]->tail->pos.x > WIDTH_OF_WINDOW - roadblocks[selected_type].w - 20)
      {
        return;
      }
    }

    // 这难道不是个死局吗？
    int num_of_blackhole = 0;
    if (selected_type == BLACKHOLE)
    {
      for (int j = 0; j < NUM_OF_TRACKS; j++)
      {
        if (roadblocks[BLACKHOLE].list[j]->num || (roadblocks[BLACKHOLE].list[j]->num == 0 && selected_track == j))
        {
          num_of_blackhole++;
        }
      }
      if (num_of_blackhole == 3)
      {
        return;
      }
    }

    Append(
        roadblocks[selected_type].list[selected_track],
        WIDTH_OF_WINDOW,
        trackpos[selected_track]);
  }
}

// 概率检定
static bool Safe(int possibility)
{
  time_t a = decide_time;
  srand(time(&decide_time));
  if (a == decide_time)
  {
    return true;
  }

  int temp1 = rand();
  int temp2 = rand();
  double temp3 = ((double)temp1 + 1000 / (double)temp2 + 5000) * 1000;
  int b = (int)temp3;

  // 控制概率为 POSSIBILITY%
  if (GeneratePossibility(b, possibility))
  {
    int temp4 = b % (100 * (TYPE_OF_ROADBLOCKS - 1) + 10);
    if (temp4 / 100 < (TYPE_OF_ROADBLOCKS - 1))
    {
      selection_game[ROADBLOCK_TYPE_SELECT] = temp4 / 100;
    }
    else
    {
      selection_game[ROADBLOCK_TYPE_SELECT] = PARFAIT;
    }

    selection_game[ROADBLOCK_TRACK_SELECT] = b % NUM_OF_TRACKS;
    return false;
  }

  return true;
}
static void DrawRoadblocks()
{
  for (int i = 0; i < TYPE_OF_ROADBLOCKS; i++)
  {
    for (int j = 0; j < NUM_OF_TRACKS; j++)
    {
      TraverseRender(roadblocks[i].list[j], i);
    }
  }
}

static void UpdateRoadblocks()
{
  for (int i = 0; i < TYPE_OF_ROADBLOCKS; i++)
  {
    for (int j = 0; j < NUM_OF_TRACKS; j++)
    {
      TraverseUpdate(roadblocks[i].list[j], i);
    }
  }
}

static void TraverseRender(LinkedList *list, int i)
{
  if (list->head == NULL)
  {
    return;
  }

  Node *cur = list->head;
  do
  {
    SDL_Rect rect_roadblock = {
        .w = roadblocks[i].w,
        .h = roadblocks[i].h,
        .x = cur->pos.x,
        .y = cur->pos.y};
    SDL_RenderCopy(app.renderer, roadblocks[i].texture, NULL, &rect_roadblock);
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
}

static void TraverseUpdate(LinkedList *list, int i)
{
  if (list->head == NULL)
  {
    return;
  }
  Node *prev = list->tail;
  Node *cur = list->head;
  do
  {
    cur->pos.x -= (int)RateInGame(ticks[1]);
    if (cur->pos.x <= 0 - roadblocks[i].w)
    {
      if (IsSingleton(list))
      {
        Delete(list, prev);
        return;
      }
      Delete(list, prev);
    }
    prev = prev->next;
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
}

static bool GeneratePossibility(int num, int possibility)
{
  int a = num % 100;
  if (a < possibility)
  {
    return true;
  }
  return false;
}

static bool LiveCheck()
{
  int now_track = selection_game[TRACK_SELECT];
  CoinCheck(roadblocks[COIN].list[now_track]);
  ParfaitCheck(roadblocks[PARFAIT].list[now_track]);
  if (!JumpLive(roadblocks[JUMP_BLOCK].list[now_track]))
  {
    SDL_Log("at track %d, killed by jumpblock", now_track);
    return false;
  }
  if (!RollLive(roadblocks[ROLL_BLOCK].list[now_track]))
  {
    SDL_Log("at track %d, killed by rollblock", now_track);
    return false;
  }
  if (!ChangeTracksLive(roadblocks[BLACKHOLE].list[now_track]))
  {
    SDL_Log("at track %d, killed by blackhole", now_track);
    return false;
  }

  return true;
}

static bool JumpLive(LinkedList *list)
{
  if (list->head == NULL)
  {
    return true;
  }

  Node *cur = list->head;
  do
  {
    int distance = cur->pos.x - characters[selection_game[CHARACTER_SELECT]].x;
    if (distance > -30 && distance < 10)
    {
      return is_jumping || IsInvincible();
    }
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
  return true;
}

static bool RollLive(LinkedList *list)
{
  if (list->head == NULL)
  {
    return true;
  }

  Node *cur = list->head;
  do
  {
    int distance = cur->pos.x - characters[selection_game[CHARACTER_SELECT]].x;
    if (distance > -30 && distance < 10)
    {
      return is_rolling || IsInvincible();
    }
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
  return true;
}

static bool ChangeTracksLive(LinkedList *list)
{
  if (list->head == NULL)
  {
    return true;
  }

  Node *cur = list->head;
  do
  {
    int distance = cur->pos.x - characters[selection_game[CHARACTER_SELECT]].x;
    if (distance > -30 && distance < 10)
    {
      return is_changing_tracks || IsInvincible();
    }
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
  return true;
}

static void CoinCheck(LinkedList *list)
{
  if (list->head == NULL)
  {
    return;
  }
  Node *prev = list->tail;
  Node *cur = list->head;
  do
  {
    int distance = cur->pos.x - characters[selection_game[CHARACTER_SELECT]].x;
    if (distance > -30 && distance < 10)
    {
      app.points += 1;
      Mix_PlayChannel(-1, chunk_coin, 0);
      SDL_Log("get 1 point, total : %d !", app.points);
      SDL_Log("rate at : %d", RateInGame(ticks[1]));
      if (IsSingleton(list))
      {
        Delete(list, prev);
        return;
      }
      Delete(list, prev);
    }
    prev = prev->next;
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
}

static void ParfaitCheck(LinkedList *list)
{
  if (list->head == NULL)
  {
    return;
  }
  Node *prev = list->tail;
  Node *cur = list->head;
  do
  {
    int distance = cur->pos.x - characters[selection_game[CHARACTER_SELECT]].x;
    if (distance > -30 && distance < 10)
    {
      app.points += 5;
      Mix_PlayChannel(-1, characters[selection_game[CHARACTER_SELECT]].boost, 0);
      SDL_Log("get 5 points, total : %d !", app.points);
      ticks[0] = SDL_GetTicks64();
      if (IsSingleton(list))
      {
        Delete(list, prev);
        return;
      }
      Delete(list, prev);
    }
    prev = prev->next;
    cur = cur->next;
  } while (cur != NULL && cur != list->head);
}

static void DoMainPart()
{
  SDL_Log("In Game!");
  if (Mix_PausedMusic())
  {
    Mix_ResumeMusic();
  }

  while (!app.keyboard[SDL_SCANCODE_ESCAPE])
  {
    unsigned int temp1 = SDL_GetTicks64();

    DoGameInput();

    DrawGame();

    HandleFps();

    if (!LiveCheck())
    {
      is_jumping = false, is_rolling = false, is_changing_tracks = false;
      app.keyboard[SDL_SCANCODE_ESCAPE] = false;
      break;
    }

    unsigned int temp2 = SDL_GetTicks64();
    unsigned int duration = temp2 - temp1;
    ticks[1] += duration;
  }
}

static bool IsInvincible()
{
  if (ticks[0] == 0)
  {
    return false;
  }
  unsigned int temp = SDL_GetTicks64();
  unsigned int interval = temp - ticks[0];
  if (interval > 5000)
  {
    ticks[0] = 0;
    return false;
  }

  return true;
}

static void DrawEndgame()
{
  SDL_RenderClear(app.renderer);
  SDL_SetRenderDrawColor(app.renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderFillRect(app.renderer, NULL);
  SDL_Color color_dead = {0x21, 0x8e, 0xac, 0xff};

  TTF_Font *font_dead = TTF_OpenFont("../res/font/Silver.ttf", 500);
  SDL_Surface *surface_dead = TTF_RenderUTF8_Solid(font_dead, "菜", color_dead);
  SDL_Texture *texture_dead = TextureInit(app.renderer, surface_dead);
  SDL_Rect rect_dead;
  SDL_QueryTexture(texture_dead, NULL, NULL, &rect_dead.w, &rect_dead.h);
  rect_dead.x = (WIDTH_OF_WINDOW - rect_dead.w) / 2;
  rect_dead.y = 100;
  SDL_RenderCopy(app.renderer, texture_dead, NULL, &rect_dead);
  SDL_DestroyTexture(texture_dead);
  TTF_CloseFont(font_dead);

  char endgame_text[40] = {0};
  sprintf(endgame_text, "Final Score : %d points", app.points);
  TTF_Font *font_score = TTF_OpenFont("../res/font/Silver.ttf", 50);
  SDL_Surface *surface_score = TTF_RenderUTF8_Solid(font_score, endgame_text, color_dead);
  SDL_Texture *texture_score = TextureInit(app.renderer, surface_score);
  SDL_Rect rect_score;
  SDL_QueryTexture(texture_score, NULL, NULL, &rect_score.w, &rect_score.h);
  rect_score.x = (WIDTH_OF_WINDOW - rect_score.w) / 2;
  rect_score.y = 460;
  SDL_RenderCopy(app.renderer, texture_score, NULL, &rect_score);
  SDL_DestroyTexture(texture_score);

  sprintf(endgame_text, "Total time : %d seconds", ticks[1] / 1000);
  SDL_Surface *surface_time = TTF_RenderUTF8_Solid(font_score, endgame_text, color_dead);
  SDL_Texture *texture_time = TextureInit(app.renderer, surface_time);
  SDL_Rect rect_time;
  SDL_QueryTexture(texture_time, NULL, NULL, &rect_time.w, &rect_time.h);
  rect_time.x = (WIDTH_OF_WINDOW - rect_time.w) / 2;
  rect_time.y = 510;
  SDL_RenderCopy(app.renderer, texture_time, NULL, &rect_time);
  SDL_DestroyTexture(texture_time);
  TTF_CloseFont(font_score);

  SDL_RenderPresent(app.renderer);
}

unsigned int RateInGame(unsigned int time)
{
  unsigned int temp = time / 1000;
  double result = 10 + RATE * temp;
  unsigned int result_int = (unsigned int)result;
  return result_int > 35 ? 35 : result_int;
}