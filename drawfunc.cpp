#include <Windows.h>
#include "map.h"
#include "drawfunc.h"
#include "savedata.h"
#include "keyconf.h"
#include "event.h"
#include "object.h"
#include <SDL_ttf.h>
#include <stdio.h>
//衡山毛筆フォント行書
char MENUITEM[6][32] = {"アイテム", "装備", "ステータス", "セーブ", "ロード", "終了"};
extern SDL_Event userevent;
int oldmenu;
int olditem[2];
SDL_Rect chardest = {288, 224, 32, 32};
int destX;
int destY;
SDL_Rect dest;
int menupos = 0;
int menuypos = 0;
int menumode = 0;
SDL_Rect rect[10];
SDL_Rect textrect[8];
TTF_Font *font;
SDL_Surface *texts[7];
SDL_Texture *text;
SDL_Color color = {255, 255, 255};

void deinitfont(){
	for(int i = 0;i<7;i++)SDL_FreeSurface(texts[i]);
	TTF_CloseFont(font);
}

int initfont(){
	char errortext[512];
	if(TTF_Init()==-1){
		sprintf(errortext, "TTF_Init: %s\nProgram aborted.", SDL_GetError());
		return 1;
	}
	font = TTF_OpenFont("font.ttf", 40);
}

void initrect(){
	rect[0].x = rect[0].y = 32;
	rect[0].w = 188;
	rect[0].h = 330;
	rect[1].x = rect[1].y = 32;
	rect[1].w = 188;
	rect[1].h = 330;
	rect[2].x = 252;
	rect[2].y = 32;
	rect[2].w = 356;
	rect[2].h = 384;
	rect[3].x = 32;
	rect[3].y = 378;
	rect[3].w = 188;
	rect[3].h = 38;
	textrect[0].x = textrect[0].y = textrect[1].x = textrect[2].x = textrect[3].x = textrect[4].x = textrect[5].x = 38;
	textrect[1].y = 93;
	textrect[2].y = 148;
	textrect[3].y = 203;
	textrect[4].y = 258;
	textrect[5].y = 313;
}

void movemap(int direction){
	switch(direction){
		case 0://up
			if(posY>0&&mapregeons[data.ouna.map].mapregeon[posY-1][posX]==0)
				posY = posY-1;
			houkou = 32;
			break;

		case 1://down
			if(posY<31&&mapregeons[data.ouna.map].mapregeon[posY+1][posX]==0)
				posY = posY+1;
			houkou = 0;
			break;

		case 2://left
			if(posX>0&&mapregeons[data.ouna.map].mapregeon[posY][posX-1]==0)
				posX = posX-1;
			houkou = 96;
			break;

		case 3://right
			if(posX<31&&mapregeons[data.ouna.map].mapregeon[posY][posX+1]==0)
				posX = posX+1;
			houkou = 69;
			break;
		default:
			break;

	}
	if(mapregeons[data.ouna.map].mapregeon[posY][posX]!=0&&mapregeons[0].mapregeon[posY][posX]!=1)MapEvent(mapregeons[0].mapregeon[posY][posX]);
	dest.x = posX*-32+288;
	dest.y = posY*-32+224;
}

void mapdraw(){
	SDL_RenderCopy(renderer, SDL_map[data.ouna.map], NULL, &dest);
}

void chardraw(){
	SDL_RenderCopy(renderer, SDL_chara[data.ouna.charactor], NULL, &chardest);
}

void drawmenutext(RECT *rect){
	for(int i = 0;i<6;i++){
		if(!(texts[i] = TTF_RenderUTF8_Blended(font, MENUITEM[i], color))){
			// ここでエラーを処理する. 少なくともTTF_GetErrorを表示したほうがよい
		} else{
			text = SDL_CreateTextureFromSurface(renderer, texts[i]);
			SDL_RenderCopy(renderer, text, NULL, &textrect[i]);
		}
	}
}

void drawitemmenutext(RECT *rect){
	int i = 0;
	while(data.itemdata[0][i]){
		texts[i] = TTF_RenderUTF8_Blended(font,item , color);
		i++;
	}
	ExtTextOut(hdc, 38, 38, NULL, rect, TEXT("回復薬"), lstrlen(TEXT("回復薬")), NULL);
	ExtTextOut(hdc, 38, 63, NULL, rect, TEXT("回復薬グレート"), lstrlen(TEXT("回復薬グレート")), NULL);
	ExtTextOut(hdc, 38, 88, NULL, rect, TEXT("ステータス"), lstrlen(TEXT("ステータス")), NULL);
	ExtTextOut(hdc, 38, 113, NULL, rect, TEXT("セーブ"), lstrlen(TEXT("セーブ")), NULL);
	ExtTextOut(hdc, 38, 138, NULL, rect, TEXT("ロード"), lstrlen(TEXT("ロード")), NULL);
	ExtTextOut(hdc, 38, 163, NULL, rect, TEXT("終了"), lstrlen(TEXT("終了")), NULL);
}

void drawitemusemenutext(RECT *rect){
	ExtTextOut(hdc, 38, 38, NULL, rect, TEXT("使う"), lstrlen(TEXT("使う")), NULL);
	ExtTextOut(hdc, 38, 63, NULL, rect, TEXT("捨てる"), lstrlen(TEXT("捨てる")), NULL);
}

void drawsoubimenutext(RECT *rect){
	ExtTextOut(hdc, 38, 266, NULL, rect, TEXT("鉄の剣"), lstrlen(TEXT("鉄の剣")), NULL);
	ExtTextOut(hdc, 38, 291, NULL, rect, TEXT("派手なほかに特徴のない剣"), lstrlen(TEXT("派手なほかに特徴のない剣")), NULL);
	ExtTextOut(hdc, 38, 316, NULL, rect, TEXT("同の件"), lstrlen(TEXT("ステータス")), NULL);
	ExtTextOut(hdc, 38, 341, NULL, rect, TEXT("セーブ"), lstrlen(TEXT("セーブ")), NULL);
	ExtTextOut(hdc, 38, 366, NULL, rect, TEXT("ロード"), lstrlen(TEXT("ロード")), NULL);
	ExtTextOut(hdc, 38, 391, NULL, rect, TEXT("終了"), lstrlen(TEXT("終了")), NULL);
}

void drawmenu(){
	if(menumode==0){
		SelectObject(hdc, hmenuFont);
		SDL_FillRect(drawSurface, &rect[0], SDL_MapRGB(drawSurface->format, 0, 0, 255));
		SDL_FillRect(drawSurface, &rect[1], SDL_MapRGB(drawSurface->format, 0, 0, 255));
		SDL_FillRect(drawSurface, &rect[2], SDL_MapRGB(drawSurface->format, 0, 0, 255));
		SDL_FillRect(drawSurface, &rect[3], SDL_MapRGB(drawSurface->format, 0, 0, 255));
		drawmenutext(&rect);
	} else if(menumode==1){
		// 長方形の左上隅の x 座標 長方形の左上隅の y 座標 長方形の右下隅の x 座標 長方形の右下隅の y 座標
		Rectangle(hdc, 32, 32, 608, 416);
		drawitemmenutext(&rect);
	} else if(menumode==2){
		Rectangle(hdc, 32, 32, 304, 228);
		Rectangle(hdc, 336, 32, 576, 228);
		Rectangle(hdc, 32, 260, 576, 420);
		drawsoubimenutext(&rect);
	} else if(menumode==3){
		Rectangle(hdc, 32, 32, 304, 228);
		Rectangle(hdc, 336, 32, 576, 228);
		Rectangle(hdc, 32, 260, 576, 420);
		drawitemmenutext(&rect);
	} else if(menumode==4){
		Rectangle(hdc, 32, 32, 608, 416);// ブラシを戻す
		drawitemmenutext(&rect);
		SelectObject(hdc, hGreenBrush);
		Rectangle(hdc, 512, 320, 608, 416);
		SelectObject(hdc, hBlueBrush);
	}
}

void movemenu(WPARAM wp){
	switch(wp){
		case 0://up
			if(menupos>0)
				menupos = menupos-1;
			else menupos = 14;
			break;

		case 1://down
			if(menupos<5||(menumode==1&&menupos<14))
				menupos = menupos+1;
			else menupos = 0;
			break;
		case 2:
			if(menuypos==0){
				menuypos = 1;
			} else menuypos = 0;
			break;
		case 3:
			if(menuypos==1){
				menuypos = 0;
			} else menuypos = 1;
			break;
		default:
			break;
	}
}

void drawselectedmenu(){
	SelectObject(hdc, hWhitePen);
	if(menumode==0)
		Rectangle(hdc, 37, menupos*55+37, 215, menupos*55+82);
	else if(menumode==1)
		Rectangle(hdc, menuypos*305+37, menupos*25+37, menuypos*305+298, menupos*25+59);
	else if(menumode==2)
		Rectangle(hdc, menuypos*272+37, menupos*25+265, menuypos*272+298, menupos*25+287);
	else if(menumode==3)
		Rectangle(hdc, menuypos*272+37, menupos*25+265, menuypos*272+298, menupos*25+287);
	else if(menumode==4)
		Rectangle(hdc, menuypos*272+37, menupos*25+265, menuypos*272+298, menupos*25+287);
	SelectObject(hdc, GetStockObject(BLACK_PEN));
	DeleteObject(hWhitePen);
}

void selectmenu(){
	if(menumode==0){
		switch(menupos){
			case 0:
				oldmenu = menupos;
				menupos = 0;
				menumode = 1;
				break;

			case 1:
				oldmenu = menupos;
				menupos = 0;
				menumode = 2;
				break;

			case 2:
				oldmenu = menupos;
				menupos = 0;
				menumode = 3;
				break;

			case 3:
				datasave();
				break;

			case 4:
				dataload();
				break;

			case 5:
				userevent.type = SDL_QUIT;
				SDL_PushEvent(&userevent);
				break;

		}
	} else if(menumode==1){

		menumode = 4;
	}
}

int backmenu(){
	if(!(menumode==0)){
		menupos = oldmenu;
		menumode = 0;
		return 0;
	} else{
		return 1;
	}

}

void drawopening(){

	opening = 0;
}

