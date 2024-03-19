#include "main.h"
#include "Pipe.h"
#include "HighScore.h"
#include "Grid.h"
#include "Score.h"
#include "MainWnd.h"

extern HINSTANCE g_hInstance = 0;

int WINAPI WinMain (
			HINSTANCE hInstance, 
			HINSTANCE /* hPrevInstance */, 
            LPTSTR /* szCmdLine */, 
			int /* iCmdShow */) {

    MSG			msg;
    HWND		hWnd;
    CMainWnd	mwMain;
    int			iReturn = 0;

    if ( (!mwMain.PrevInst()) ) {

		g_hInstance = hInstance;
        hWnd = mwMain.Create(hInstance);

        while (GetMessage (&msg, NULL, 0, 0)) {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }

        iReturn = msg.wParam;
    } else {
		SetForegroundWindow(FindWindow(MAINWND_CLASS,MAINWND_TITLE));
	}

    return iReturn;
}
