#include "main.h"
#include "MainWnd.h"

extern bool g_bReLaunch = false;


int WINAPI WinMain2 (HINSTANCE hInstance, HINSTANCE, 
            LPTSTR, int)
{

    CMainWnd    mwMain;
    MSG         msg;
    HWND        hWnd;
    int         iReturn = 0;

    if ( (!mwMain.PrevInst()) )
    {

        hWnd = mwMain.Create(hInstance);

        while (GetMessage (&msg, NULL, 0, 0))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }

        mwMain.DestroyMutex();

        iReturn = msg.wParam;
    }
    else
    {
		hWnd = FindWindow(MAINWND_CLASS, MAINWND_TITLE);
		SetForegroundWindow(hWnd);
		return 0;
	}

    return iReturn;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE, 
            LPTSTR, int)
{
    int i;
    i = WinMain2(hInstance, 0, 0, 0);
    if (g_bReLaunch)
    {
        TCHAR szFile[MAX_PATH];
        GetModuleFileName(0, szFile, MAX_PATH);
        TCHAR szFile2[MAX_PATH+2];

        _tcscpy(szFile2, _T("\""));
        _tcscat(szFile2, szFile);
        _tcscat(szFile2, _T("\""));

	    SHELLEXECUTEINFO sei = {0};
	    sei.lpVerb = _T("open");
	    sei.lpFile = szFile2;
	    sei.cbSize = sizeof sei;

    	ShellExecuteEx(&sei);
    }

    return i;
}

void GetFile(LPTSTR szFile)
{

    GetModuleFileName(NULL, szFile, MAX_PATH);
    while (_tcslen(szFile) > 0 && szFile[_tcslen(szFile)-1] != _T('\\'))
    {
        szFile[_tcslen(szFile)-1] = 0;
    }
    _tcscat(szFile, _T("Conversions.xml"));
}

