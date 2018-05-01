typedef enum{SL,CL,MU,MD,ML,MR,KC,RS,KEYNUM}KEY;		/// ÉLÅ[ëÄçÏíËêî
extern unsigned int Key[KEYNUM];
static LPCTSTR keytype[KEYNUM]={TEXT("Select\0\0"),TEXT("Cancel,Menu\0\0"),TEXT("Up\0\0"),TEXT("Down\0\0"),TEXT("Left\0\0"),TEXT("Right\0\0"),TEXT("Keyconfig\0\0"),TEXT("Reset\0\0")};
BOOL CALLBACK KeyDlgProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK InputWindowProc(HWND,UINT,WPARAM,LPARAM);
VOID ReadReg();