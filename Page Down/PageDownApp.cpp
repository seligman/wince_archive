#include "stdafx.h"
#include "PageDownApp.h"

HINSTANCE			hInst;			// The current instance
HWND				g_hWndOld;

ATOM				MyRegisterClass	(HINSTANCE, LPTSTR);
BOOL				InitInstance	(HINSTANCE, int);
LRESULT CALLBACK	WndProc			(HWND, UINT, WPARAM, LPARAM);

//#define DOWN_KEY VK_DOWN
//#define DOWN_KEY VK_NEXT
#define DOWN_KEY VK_PRIOR

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow) {


	g_hWndOld =  GetForegroundWindow();
	HWND hWndTemp = FindWindow(_T("PageDownAppClass"), _T("PageDownApp"));
	if (hWndTemp != 0) {
		PostMessage(hWndTemp, WM_USER, 0, 0);
		return 0;
	}

	MSG msg;


	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
	
}

ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass) {
	WNDCLASS	wc;

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAGEDOWNAPP));
    wc.hCursor			= 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND	hWnd;

	hInst = hInstance;

	MyRegisterClass(hInstance, _T("PageDownAppClass"));

	hWnd = CreateWindow(_T("PageDownAppClass"), _T("PageDownApp"),
		WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) {	
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	static DWORD nLastActive = GetTickCount();
	static bool bOne = false;

	switch (message) {
		case WM_ACTIVATE:
			SetForegroundWindow(g_hWndOld);
			break;

		case WM_TIMER:
			if (!bOne) {
				static DWORD nLastTick = GetTickCount();
				DWORD nTick = GetTickCount();
				if (nTick - nLastTick > 150) {
					bOne = true;
					keybd_event(DOWN_KEY,0,0,0);
					keybd_event(DOWN_KEY,0,KEYEVENTF_KEYUP,0);
					nLastActive = GetTickCount();
					//KillTimer(hWnd, 1);
					//SetTimer(hWnd, 1, 500, NULL);
				}
			}
			if ((GetTickCount() - nLastActive) > (250 * 10 * 1)) {
				PostMessage(hWnd, WM_CLOSE, 0, 0);
			}


			break;
		case WM_CREATE:
			SetTimer(hWnd, 1, 50, NULL);
			ShowWindow(hWnd,SW_SHOWNOACTIVATE);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_USER:
			SetForegroundWindow(g_hWndOld);
			keybd_event(DOWN_KEY,0,0,0);
			keybd_event(DOWN_KEY,0,KEYEVENTF_KEYUP,0);
			nLastActive = GetTickCount();
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

