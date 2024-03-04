#include "main.h"
#include "MainWnd.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR szCmdLine, int iCmdShow) {

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

		HWND hWndParent = FindWindow(_T("HHTaskBar"), _T(""));
		HWND hWndChild = 0;

		hWndChild = GetWindow(hWndParent, GW_CHILD);
		while (hWndChild != NULL) {

			TCHAR szClass[2048];
			TCHAR szTitle[2048];

			GetClassName(hWndChild, szClass, 2048);
			GetWindowText(hWndChild, szTitle, 2048);

			if (_tcscmp(szClass, MAINWND_CLASS) == 0 &&
				_tcscmp(szTitle, MAINWND_TITLE) == 0) {

				PostMessage(hWndChild, WM_USER_TRIGGER, 0, 0);

				hWndChild = NULL;
			}

			if (hWndChild != NULL) {
				hWndChild = GetWindow(hWndChild, GW_HWNDNEXT);
			}
		}

		//EnumChildWindows
		//HWND hWndTarget = FindWindow(MAINWND_CLASS, MAINWND_TITLE);

		//if (MessageBox(NULL, _T("Palm Page is already running, do you wish to close it?"),
		//	_T("Palm Page"), MB_YESNO) == IDYES) {
		//	
		//	PostMessage(hWndTarget, WM_CLOSE, 0, 0);
		//	
		//}


	}

	return iReturn;
}

