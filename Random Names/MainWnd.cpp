#include "MainWnd.h"

CMainWnd::CMainWnd() {
	MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) this, NULL);
}

CMainWnd::~CMainWnd() {
	MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) NULL, NULL);
}

BOOL CMainWnd::PrevInst() {
	m_hMutex = CreateMutex(NULL, TRUE, MAINWND_GUID);

	return (GetLastError() == ERROR_ALREADY_EXISTS);
}

HWND CMainWnd::Create(HINSTANCE hInstance) {

	HWND		hWnd;
	WNDCLASS	wndclass;

	m_hInstance = hInstance;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
#ifdef UNDER_CE
	wndclass.hCursor = NULL;
#else
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
#endif
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = MAINWND_CLASS;

	RegisterClass ( &wndclass );

#ifdef UNDER_CE
	hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_VISIBLE, 0, 0, 240, 320, 
		NULL, NULL, hInstance, NULL);
#else
	hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 320, 
		NULL, NULL, hInstance, NULL);
#endif

	return hWnd;
}

LRESULT CALLBACK CMainWnd::MainWndProc ( HWND hWnd, UINT iMsg, 
   WPARAM wParam, LPARAM lParam) {

	static CMainWnd * parent = (CMainWnd *) NULL;

	if (iMsg == WM_USER_OBJECT) {
		parent = (CMainWnd *) wParam;
		return 0;
	} else if ( parent != NULL ) {
		switch (iMsg) {

		case WM_CREATE :
			parent->m_hWnd = hWnd;
			return parent->OnCreate();

		case WM_CLOSE :
			return parent->OnClose();

		case WM_DESTROY :
			return parent->OnDestroy();


		}
	}

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnClose() {

	DestroyWindow(m_hWnd);

	return 0;
}

LRESULT CMainWnd::OnDestroy() {

	PostQuitMessage(0);

	return 0;
}

LRESULT CMainWnd::OnCreate() {

	RECT rt;
	GetClientRect(m_hWnd,&rt);

//#ifdef UNDER_CE
//	SystemParametersInfo(SPI_GETWORKAREA,0, &m_rtClose, 0);
//	m_rtClose.top = m_rtClose.bottom - CLOSE_Y;
//	m_rtClose.left = m_rtClose.right - CLOSE_X;
//#else
//	m_rtClose.top = rt.bottom - CLOSE_Y;
//	m_rtClose.left = rt.right - CLOSE_X;
//	m_rtClose.bottom = rt.bottom;
//	m_rtClose.right = rt.right;
//#endif

	m_Dlg.SetHwnd(m_hWnd);
	m_Dlg.Init();

	ShowWindow (m_hWnd, SW_SHOWNORMAL);
	UpdateWindow (m_hWnd);

	return 0;
}
