#include <Windows.h>
#include "object.h"
OBJECTDATA object;

void setitem() {
	HANDLE hFile;
	DWORD wReadSize;
	hFile = CreateFile(TEXT(".\\resources\\items.dat"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile==INVALID_HANDLE_VALUE){
		return;
	}
	ReadFile(hFile, &object, GetFileSize(hFile, NULL), &wReadSize, NULL);
	CloseHandle(hFile);
	/*
	item[1].NAME = "不老不死の薬（プロテインIN）";
	item[1].CAPTION	= "不老不死の薬、プロテイン入りでマッチョな体に！";
	item[1].event = 0;
	item[2].NAME = "回復薬";
	item[2].CAPTION = "とあるキノコと草を混ぜるとできる";
	item[2].event = 0;
	item[3].NAME = "回復薬グレート";
	item[3].CAPTION = "回復薬にはちみつを垂らしたもの";
	item[3].event = 0;
	item[4].NAME = "八卦炉";
	item[4].CAPTION  = "マスタースパーク！";
	item[4].event = 0;
	*/
}