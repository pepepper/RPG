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
	item[1].NAME = "�s�V�s���̖�i�v���e�C��IN�j";
	item[1].CAPTION	= "�s�V�s���̖�A�v���e�C������Ń}�b�`���ȑ̂ɁI";
	item[1].event = 0;
	item[2].NAME = "�񕜖�";
	item[2].CAPTION = "�Ƃ���L�m�R�Ƒ���������Ƃł���";
	item[2].event = 0;
	item[3].NAME = "�񕜖�O���[�g";
	item[3].CAPTION = "�񕜖�ɂ͂��݂𐂂炵������";
	item[3].event = 0;
	item[4].NAME = "���T�F";
	item[4].CAPTION  = "�}�X�^�[�X�p�[�N�I";
	item[4].event = 0;
	*/
}