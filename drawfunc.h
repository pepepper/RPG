#pragma once
#include<Windows.h>
#include"savedata.h"
#include <SDL.h>
#define posX data.ouna.pos[1]
#define posY data.ouna.pos[2]
#define houkou data.ouna.houkou
extern SDL_Texture *SDL_map[256];
extern SDL_Texture *SDL_chara[256];
extern SDL_Renderer *renderer;
extern int opening;
void movemap(int);
void mapdraw();
void chardraw();
void drawmenu();
void movemenu(WPARAM);
void drawselectedmenu();
void selectmenu();
int backmenu();
void drawopening();
