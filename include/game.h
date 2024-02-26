#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "./utils/input.h"
#include "./utils/display.h"
#include "./utils/audio.h"
#include "./utils/linkedlist.h"
#include "menu.h"

#define NUM_OF_TRACKS 3
#define TRACK1 0
#define TRACK2 1
#define TRACK3 2

#define UP_MARGIN 250
#define DOWN_MARGIN 60
#define HEIGHT_OF_TRACK 100
#define WIDTH_OF_TRACK 1280
#define GAP 55
#define CHARACTERPOS 60

#define JUMP_ACCELERATION 6
#define JUMP_VELOCITY -35
#define SPIN_ACCELERATION 6
#define SPIN_VELOCITY -32
#define CHANGE_VELOCITY 35

#define CHARACTER_SELECT 0
#define TRACK_SELECT 1
#define ROADBLOCK_TYPE_SELECT 2
#define ROADBLOCK_TRACK_SELECT 3

#define RATE 0.10

#define FPS 200

#define NUM_OF_CHARACTERS 5
#define TYPE_OF_ROADBLOCKS 5

#define JUMP_BLOCK 0
#define ROLL_BLOCK 1
#define BLACKHOLE 2
#define COIN 3
#define PARFAIT 4

#define NUM_OF_ROADBLOCKS 0
#define BLOCK_X_POS 0
#define BLOCK_Y_POS 1

#define POSSIBILITY 90

typedef struct
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  Mix_Chunk *opening;
  Mix_Chunk *fail;
  Mix_Chunk *boost;
  Mix_Chunk *move;
  int w, h;
  int x, y;
  int vy, ay;
  double angle;
  double v_angle, a_angle;
} Character;

typedef struct
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  int w, h;
  LinkedList *list[3];
} Roadblock;

void DoGameLogic();
void QuitRoadblocks();
void QuitCharacters();
unsigned int RateInGame(unsigned int time);

static int tracks[2];
static int trackpos[3];
static Character *characters;
static Roadblock *roadblocks;

static bool is_changing_tracks, is_jumping, is_rolling;
static int ground;
static time_t decide_time;
static unsigned int ticks[100];
static Mix_Chunk *chunk_coin;
static Mix_Chunk *chunk_dead;

static void DoGameInput();
static void DrawGame();
static void HandleFps();
static void DrawGameBackground();
static void UpdateTracks();
static void DrawTracks();
static void InitCharacters();
static void DrawCharacter();
static void UpdateCharacter();
static void Jump();
static void Roll();
static void ChangeTracks();
static void InitRoadblocks();
static void GenerateRoadblocks();
static bool Safe(int possibility);
static bool GeneratePossibility(int num, int possibility);
static void DrawRoadblocks();
static void TraverseRender(LinkedList *list, int i);
static void UpdateRoadblocks();
static void TraverseUpdate(LinkedList *list, int i);
static bool LiveCheck();
static bool JumpLive(LinkedList *list);
static bool RollLive(LinkedList *list);
static bool ChangeTracksLive(LinkedList *list);
static void CoinCheck(LinkedList *list);
static void ParfaitCheck(LinkedList *list);
static bool IsInvincible();
static void DrawEndgame();
static void DoMainPart();


#endif