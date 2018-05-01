#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "drawfunc.h"
#include "savedata.h"
#include "keyconf.h"
#include "object.h"
#include "inventory.h"
#include "map.h"
#include "event.h"
#include "loadbmp.h"
#include <SDL_surface.h>
#include <SDL_video.h>

mobstatus mobs[512];
savedata data;
SDL_Surface *drawSurface;
int opening=1;
SDL_Texture *SDL_map[256];
SDL_Texture *SDL_chara[256];
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event userevent;

void end(){
	for(int i=0;i<256; i++)	SDL_FreeSurface(SDL_map[i]);
	for(int i=0;i<256; i++)	SDL_FreeSurface(SDL_chara[i]);
	SDL_FreeSurface(drawSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int selectdirection(int direction){
	if(direction==Key[MU])return 0;
	else if(direction==Key[MD])return 1;
	else if(direction==Key[ML])return 2;
	else if(direction==Key[MR])return 3;
}

void init(){
	mapinit();
	iteminit();
	ReadReg();
	movemap(4);
}

void newgame(){
	//	eventinit();
	data.ouna.map=0;
	data.ouna.pos[1]=9;
	data.ouna.pos[2]=0;
	ReadBmpNameFromFile();
	LoadCharactorBitmap(0);
	LoadMapBitmap(0);
}

int WndProc(SDL_Event *e, int wp){
	static int flag=0;
	if(!opening){
		mapdraw();
		chardraw();
	} else{
		drawopening();
	}
	switch(e->type){
		case 	SDL_QUIT:
			end();
			return 0;
		case SDL_KEYDOWN:
			if(!flag)
				movemap(wp);
			else{
				movemenu(wp);
				drawmenu();
				drawselectedmenu();
			}
			if(e->key.keysym.sym==SDLK_ESCAPE){
				userevent.type=SDL_QUIT;
				SDL_PushEvent(&userevent);
				break;
			} else if(e->key.keysym.sym==Key[SL]){
				if(flag==1){
					selectmenu();
					drawmenu();
					drawselectedmenu();
				}
			} else if(e->key.keysym.sym==Key[CL]){
				if(flag==0){
					flag=1;
					drawmenu();
					drawselectedmenu();
				} else if(backmenu()){
					flag=0;
				}
			} else if(e->key.keysym.sym==Key[RS]){
				init();
				opening=1;
			} else if(e->key.keysym.sym==Key[KC]){
				//DialogBox(((LPCREATESTRUCT)(lp))->hInstance, TEXT("KEY"), hwnd, (DLGPROC)KeyDlgProc);
			}
			break;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	SDL_Event e;
	WCHAR errortextw[256];
	char errortext[256];
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		sprintf(errortext, "SDL_Init:%s.\nProgram aborted.", SDL_GetError());
		mbstowcs(errortextw, errortext, 512);
		MessageBox(NULL, errortextw, NULL, MB_OK);
		return 1;
	}
	if(window=SDL_CreateWindow("RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0)){
		sprintf(errortext, "SDL_Init:%s.\nProgram aborted.", SDL_GetError());
		mbstowcs(errortextw, errortext, 512);
		MessageBox(NULL, errortextw, NULL, MB_OK);
		return 1;
	}
	drawSurface=SDL_GetWindowSurface(window);
	init();
	while(SDL_PollEvent(&e)){
		SDL_UpdateWindowSurface(window);

	}
	return 0;
}

