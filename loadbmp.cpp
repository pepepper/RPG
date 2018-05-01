#include <windows.h>
#include <SDL.h>
#include<locale.h>
#include <stdio.h>
extern SDL_Texture *SDL_map[256];
extern SDL_Texture *SDL_chara[256];
extern SDL_Event userevent;
extern SDL_Renderer *renderer;
char mapbmpname[256][512];
char charabmpname[256][512];
int LoadCharactorBitmap(int charanum){
	SDL_Surface *tempsurface;
	WCHAR errortextw[256];
	char errortext[256];
	tempsurface = SDL_LoadBMP(charabmpname[charanum]);
	SDL_SetColorKey(tempsurface, SDL_TRUE, SDL_MapRGB(tempsurface->format, 34, 177, 76));
	SDL_chara[charanum] = SDL_CreateTextureFromSurface(renderer, tempsurface);
	if(!SDL_chara[charanum]){
		sprintf(errortext, "IMG_Load:%s.\nProgram aborted.", SDL_GetError());
		mbstowcs(errortextw, errortext, 512);
		MessageBox(NULL, errortextw, NULL, MB_OK);
		userevent.type = SDL_QUIT;
		SDL_PushEvent(&userevent);
		return 1;
	}

	return 0;
}

int LoadMapBitmap(int mapnum){
	SDL_Surface *tempsurface;
	WCHAR errortextw[256];
	char errortext[256];
	tempsurface = SDL_LoadBMP(mapbmpname[mapnum]);
	SDL_map[mapnum]=SDL_CreateTextureFromSurface(renderer,tempsurface);
	if(!SDL_map[mapnum]){
		sprintf(errortext, "IMG_Load:%s.\nProgram aborted.", SDL_GetError());
		mbstowcs(errortextw, errortext, 512);
		MessageBox(NULL, errortextw, NULL, MB_OK);
		userevent.type = SDL_QUIT;
		SDL_PushEvent(&userevent);
		return 1;
	}
	return 0;
}

int ReadBmpNameFromFile(){
	FILE *fp;
	int i = 0;
	if((fp = fopen(".\\resources\\mapname.txt", "r"))==NULL){
		MessageBox(NULL, TEXT("\"mapname.txt\"\nCannot read this file.\nProgram aborted."), NULL, MB_OK);
		return 1;
	}
	while(fscanf(fp, "%s", mapbmpname[i])!=EOF){    /* データ処理 */
		i++;
	}
	fclose(fp);    /* ファイル・クローズ */

	if((fp = fopen(".\\resources\\charaname.txt", "r"))==NULL){
		MessageBox(NULL, TEXT("\"charaname.txt\"\nCannot read this file.\nProgram aborted."), NULL, MB_OK);
		return 1;
	}
	i = 0;
	while(fscanf(fp, "%s", charabmpname[i])!=EOF){    /* データ処理 */
		i++;
	}
	fclose(fp);    /* ファイル・クローズ */
	return 0;
}