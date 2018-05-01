#include "resource.h"
#include <windows.h>
#include "keyconf.h"
#include <stdio.h>
LPCTSTR KeyCodeName[]={TEXT("BackSpace"),TEXT("Tab"),TEXT("Clear"),TEXT("Enter"),TEXT("Shift"),TEXT("Ctrl"),TEXT("Alt"),TEXT("Pause"),TEXT("Shift+CapsLock"),TEXT("Esc"),TEXT("無変換"),TEXT("Space"),TEXT("PageUp"),TEXT("PageDown"),TEXT("End"),TEXT("Home"),TEXT("←"),TEXT("↑"),TEXT("→"),TEXT("↓"),TEXT("PrintScreen"),TEXT("Insert"),TEXT("Delete"),TEXT("0"),TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("5"),TEXT("6"),TEXT("7"),TEXT("8"),TEXT("9"),TEXT("A"),TEXT("B"),TEXT("C"),TEXT("D"),TEXT("E"),TEXT("F"),TEXT("G"),TEXT("H"),TEXT("I"),TEXT("J"),TEXT("K"),TEXT("L"),TEXT("M"),TEXT("N"),TEXT("O"),TEXT("P"),TEXT("Q"),TEXT("R"),TEXT("S"),TEXT("T"),TEXT("U"),TEXT("V"),TEXT("W"),TEXT("X"),TEXT("Y"),TEXT("Z"),TEXT("左Windows"),TEXT("右Windows"),TEXT("ApplicationMenu"),TEXT("Num0"),TEXT("Num1"),TEXT("Num2"),TEXT("Num3"),TEXT("Num4"),TEXT("Num5"),TEXT("Num6"),TEXT("Num7"),TEXT("Num8"),TEXT("Num9"),TEXT("*"),TEXT("+"),TEXT("-"),TEXT("."),TEXT("/"),TEXT("F1"),TEXT("F2"),TEXT("F3"),TEXT("F4"),TEXT("F5"),TEXT("F6"),TEXT("F7"),TEXT("F8"),TEXT("F9"),TEXT("F10"),TEXT("F11"),TEXT("F12"),TEXT("NumLock"),TEXT("ScrollLock"),TEXT(":"),TEXT(";"),TEXT(","),TEXT("-"),TEXT("."),TEXT("/"),TEXT("@"),TEXT("["),TEXT("\\"),TEXT("]"),TEXT("^"),TEXT("\\"),TEXT("半角/全角"),TEXT("前候補"),TEXT("CapsLock"),TEXT("カタカナひらがな")};
unsigned int Key[KEYNUM]={'Z','X',VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_F12,VK_F1};	/// 操作キー
TCHAR KeyName[KEYNUM][128]={TEXT("Z"),TEXT("X"),TEXT("↑"),TEXT("↓"),TEXT("←"),TEXT("→"),TEXT("F12"),TEXT("F1")};
const int DefaultKey[KEYNUM]={'Z','X',VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_F12,VK_F1};	/// 操作キー
const TCHAR DefaultKeyName[KEYNUM][256]={TEXT("Z"),TEXT("X"),TEXT("↑"),TEXT("↓"),TEXT("←"),TEXT("→"),TEXT("F12"),TEXT("F1")};
LPCTSTR KeyTypeandName[KEYNUM]={TEXT("SelectKey"),TEXT("Cancel,MenuKey"),TEXT("UpKey"),TEXT("DownKey"),TEXT("LeftKey"),TEXT("RightKey"),TEXT("KeyconfigKey"),TEXT("ResetKey")};

VOID WriteReg(){
	TCHAR msg[8];
	for(int i=0;i < KEYNUM;i++){
		wsprintf(msg, TEXT("%u"), Key[i]);
		WritePrivateProfileString(TEXT("KeyConfig"),keytype[i],msg,TEXT(".\\RPG01.ini"));
		WritePrivateProfileString(TEXT("KeyConfig"),(LPCTSTR)KeyTypeandName[i],(LPCTSTR)KeyName[i],TEXT(".\\RPG01.ini"));
	}
}
VOID ReadReg(){
	FILE *file;
	if(file=fopen("RPG01.ini","r")){
		fclose(file);
		for(int i=0;i < KEYNUM;i++){
			Key[i] = GetPrivateProfileInt(TEXT("KeyConfig"),keytype[i],0,TEXT(".\\RPG01.ini"));
			GetPrivateProfileString(TEXT("KeyConfig"),KeyTypeandName[i],TEXT("NULL"),KeyName[i],2048,TEXT(".\\RPG01.ini"));
		}
	}
}

int compar(const WPARAM *val1, const WPARAM *val2) {
    if ( *val1 < *val2 ) {
        return -1;
    } else if ( *val1 == * val2 ) {
        return 0;
    } else {
        return 1;
    }
}

void KeyConfigReset(){
	for(int i=0;i <= KEYNUM;i++){
		Key[i] = DefaultKey[i];
		for(int j=0;j < 256;j++) KeyName[i][j] = DefaultKeyName[i][j];
	}
	return;
}

BOOL CALLBACK KeyDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam){
	static KEY button;
	static TCHAR tempKeyText[KEYNUM][32];
	const TCHAR ope[KEYNUM][32]={TEXT("決定"),TEXT("キャンセル・メニュー"),TEXT("上移動"),TEXT("下移動"),TEXT("左移動"),TEXT("右移動"),TEXT("キーコンフィグ"),TEXT("リセット")};
	const DWORD IDC[KEYNUM]={IDC_BSL,IDC_BCL,IDC_BMU,IDC_BMD,IDC_BML,IDC_BMR,IDC_BKC,IDC_BRS};
	TCHAR str[128];
	RECT rc;
	int i,k;
	WPARAM *result;

	switch(uMsg){
		case WM_INITDIALOG:
			for(i=0;i<=KEYNUM;i++){
				wsprintf(str,TEXT("%ls ： %ls"),ope[i],KeyName[i]);
				SetWindowText(GetDlgItem(hDlg,IDC[i]),str);
			}
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDOK:
					for(i=0;i<KEYNUM-1;i++){		/// 一つのキーが複数の操作に
						for(k=i+1;k<KEYNUM;k++){	/// 割り当てられていないか？
							if(Key[i]==Key[k]){
								MessageBox(hDlg,TEXT("同じキーが複数の操作に割り当てられています"),NULL,MB_OK);
								return TRUE;
							}
						}
					}
					/// 異常なし
					for(i=0;i<KEYNUM;i++){
						if(tempKeyText[i][0])wcscpy(KeyName[i],tempKeyText[i]);
					}
					EndDialog(hDlg,IDOK);
					WriteReg();
					return TRUE;
				case IDCANCEL: EndDialog(hDlg,IDCANCEL); return TRUE;
				case IDRESET: KeyConfigReset(); return TRUE;
				case IDC_BSL: button=SL; break;
				case IDC_BCL: button=CL; break;
				case IDC_BMU: button=MU; break;
				case IDC_BMD: button=MD; break;
				case IDC_BML: button=ML; break;
				case IDC_BMR: button=MR; break;
				case IDC_BKC: button=KC; break;
				case IDC_BRS: button=RS; break;
				default: return FALSE;
			}
			wsprintf(str,TEXT("%s\n\n現在のキー：%s"),ope[button],tempKeyText[button]);
			GetWindowRect(hDlg,&rc);
			CreateWindow(TEXT("Input"),NULL,WS_POPUP | WS_VISIBLE,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,hDlg,NULL,((LPCREATESTRUCT)lParam)->hInstance,str);
			return TRUE;
		case WM_INPUT:
			Key[button]=(unsigned int)wParam;
			result = (WPARAM *)bsearch(&Key[button], KeyCode, sizeof(KeyCode) / sizeof(KeyCode[0]), sizeof(WPARAM),(int (*)(const void *, const void *))compar);
			lstrcpyn(tempKeyText[button],KeyCodeName[(int)(result - &KeyCode[0])],32);
			wsprintf(str,TEXT("%ls ： %ls"),ope[button],tempKeyText[button]);
			SetWindowText(GetDlgItem(hDlg,IDC[button]),str);
			return TRUE;
	}
	return FALSE;
}

/// 入力キー取得ウィンドウのプロシージャ
LRESULT CALLBACK InputWindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rc;
	static BOOL paint;
	TCHAR str[128];
	static TCHAR params[64];
	const TCHAR *explain=TEXT("新たに割り当てたい\nキーを押して下さい");

	switch(uMsg){
		case WM_CREATE:
			wcscpy(params,(TCHAR*)(((LPCREATESTRUCT)lParam)->lpCreateParams));
			GetClientRect(hWnd,&rc); rc.top=50;
			paint=TRUE; SetTimer(hWnd,1,500,NULL);
			return 0;
		case WM_TIMER:
			paint=!paint;
			InvalidateRect(hWnd,NULL,TRUE);
			return 0;
		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
			SetTextColor(hdc,RGB(0,255,0)); SetBkColor(hdc,RGB(0,0,0));
			if(paint) wsprintf(str,TEXT("%s\n\n%s"),params,explain);
			else wcscpy(str,params);
			DrawText(hdc,str,-1,&rc,DT_CENTER);
			EndPaint(hWnd,&ps);		/// ↓タスクバーの項目をクリックする事で
			return 0;				/// ↓再び最前面になった場合はフォーカスを失っている
		case WM_WINDOWPOSCHANGED: SetForegroundWindow(hWnd); return 0;
		case WM_KEYDOWN:
			PostMessage(GetWindow(hWnd,GW_OWNER),WM_INPUT,wParam,lParam);
			KillTimer(hWnd,1); DestroyWindow(hWnd);
			return 0;

	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
