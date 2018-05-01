#include "savedata.h"
#include <windows.h>
#ifndef UNDER_CE
#include <stdio.h>
#endif //!UNDER_CE

int datasave() {
	static OPENFILENAME ofn = { 0 };
	static TCHAR strFile[MAX_PATH];
	HANDLE hFile;
	DWORD dwWriteSize;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = TEXT("Ouna Quest save files (*.sav)\0*.sav\0")
		TEXT("All files (*.*)\0*.*\0\0");
	ofn.lpstrFile = strFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = TEXT("sav");
	GetSaveFileName(&ofn);
	hFile = CreateFile(strFile, GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return 1;
	}

	WriteFile(hFile, &data, sizeof(data), &dwWriteSize, NULL);
	CloseHandle(hFile);
	return 0;

}

int dataload() {
	static OPENFILENAME ofn = { 0 };
	static TCHAR strFile[MAX_PATH];
	HANDLE hFile;
	DWORD wReadSize;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = TEXT("Ouna Quest save files (*.sav)\0*.sav\0")
		TEXT("All files (*.*)\0*.*\0\0");
	ofn.lpstrFile = strFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = TEXT("sav");
	GetOpenFileName(&ofn);
	hFile = CreateFile(strFile, GENERIC_READ, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return 1;
	}
	ReadFile(hFile, &data, GetFileSize(hFile, NULL), &wReadSize, NULL);
	CloseHandle(hFile);
	return 0;
}