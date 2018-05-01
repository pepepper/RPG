#pragma once

typedef struct {
	char NAME[32];
	char CAPTION[256];
	int event;
}ITEM;

typedef struct {
	char NAME[32];
	char CAPTION[256];
	int DEF;
	int MDEF;
}HEAD,BODY,ARM,FOOT;

typedef struct {
	char NAME[32];
	char CAPTION[256];
	int ATK;
	int DEF;
}WEAPON;

typedef struct{
	ITEM item[200];
	HEAD head[200];
	BODY body[200];
	ARM arm[200];
	FOOT foot[200];
	WEAPON weapon[200];
}OBJECTDATA;
extern OBJECTDATA object;
void setitem();
