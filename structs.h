#pragma once
#include <Windows.h>

typedef struct {
	int ATK;
	int DEF;
	int MATK;
	int MDEF;
	int SPD;
	int MAXHP;
	int MAXMP;
	int HP;
	int MP;
	int job;
}battlestatus;

typedef struct {
	int weapon;
	int head;
	int body;
	int hand;
	int foot;
}soubi;

typedef struct {
	int headdata[2][50];
	int bodydata[2][50];
	int armdata[2][50];
	int footdata[2][50];
	int weapondata[2][50];
}SOUBIS;

typedef struct {
	WCHAR NAME[20];
	int level;
	battlestatus battlestatus;
	int pos[2];
	soubi soubi;
	int map;
	int charactor;
	int houkou;
}mainstatus;

typedef struct {
	WCHAR NAME[20];
	int level;
	battlestatus battlestatus;
}status;

typedef struct{
	status mobstat;
	int bmpnum;
	int mappos[3];
}mobstatus;
