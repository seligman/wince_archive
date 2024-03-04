// FixKeys.cpp : Defines the entry point for the application.
//

#include "stdafx.h"


int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	SetCursor (LoadCursor (NULL, IDC_WAIT));
	int i;
	for (i=0;i<256;i++) {
 		keybd_event(i,0,KEYEVENTF_KEYUP | KEYEVENTF_SILENT, 0);
	}
    SetCursor (LoadCursor (NULL, 0));

	MessageBox(0,L"Keyboard status has been reset.",L"Fix Keys",MB_ICONINFORMATION);

	return 0;
}

extern "C" void wWinMainCRTStartup() {
	WinMain(0,0,0,0);
}