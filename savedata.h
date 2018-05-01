#pragma once
#include "structs.h"

typedef struct{
	mainstatus ouna;
	status friend1;
	status friend2;
	status friend3;
	int itemdata[2][200];//memo[たて][よこ] [0][i]アイテム種類 [1][i]アイテム個数
	SOUBIS soubi;
	int playtime;
	int money;
	int eventflag[512];
}savedata;

extern mobstatus mobs[512];
extern savedata data;
int datasave();
int dataload();