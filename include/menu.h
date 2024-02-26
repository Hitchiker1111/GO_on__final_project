#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "./utils/display.h"
#include "./utils/input.h"


#define NUM_OF_MENU_WIDGETS 2
#define NUM_OF_PAUSE_WIDGETS 3
#define NUM_OF_SECONDARY_WIDGETS 5
#define WIDTH_OF_MENU_WIDGETS 200
#define HEIGHT_OF_MENU_WIDGETS 100

#define TYPE_MAIN 0
#define TYPE_SECONDARY 1
#define TYPE_PAUSE 2

#define START_GAME 0
#define EXIT_GAME 1

#define BACK_TO_GAME 0
#define BACK_TO_MENU 1
#define PAUSE_EXIT_GAME 2


void DoMenuLogic();
static void DrawMenu();


void InitWidgets();
void DoWidget(int a);

void PrevWidget(int a);
void NextWidget(int a);
void ActWidget();

void ActionStartGame();
void ActionExitGame();
void ActionToMenu();
void ActionToGame();

void DrawMenuBackground();
void DrawWidget(Widget *widget);
void DrawSelection();
void DrawSecondaryMenu();

void DoPauseLogic();
static void DrawPause();

#endif