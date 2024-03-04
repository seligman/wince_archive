// PowerOff.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MainWnd.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPWSTR szCmdLine, int iCmdShow) {

	CMainWnd  	mwMain;
	MSG			msg;
	HWND		hWnd;
	int			iReturn = 0;

    if ( (!mwMain.PrevInst()) ) {

		hWnd = mwMain.Create(hInstance);

		while (GetMessage (&msg, NULL, 0, 0)) {
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

		iReturn = msg.wParam;
	} else {

		HWND hWndTarget = FindWindow(MAINWND_CLASS, MAINWND_TITLE);

		if (MessageBox(NULL, _T("PowerOff is already running, do you wish to close it?"),
			_T("PowerOff"), MB_YESNO) == IDYES) {
			
			PostMessage(hWndTarget, WM_CLOSE, 0, 0);
			
		}

	}

	return iReturn;
}

