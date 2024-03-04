#include "stdafx.h"
#include "MainWnd.h"
#include "resource.h"

CMainWnd * CMainWnd::m_pMainWnd = NULL;

CMainWnd::CMainWnd() {
	m_pMainWnd = this;
	m_hInstance = 0;
}

CMainWnd::~CMainWnd() {
	m_pMainWnd = NULL;
}

bool CMainWnd::PrevInst() {
	m_hMutex = CreateMutex(NULL, true, MAINWND_GUID);

	return (GetLastError() == ERROR_ALREADY_EXISTS);
}

HWND CMainWnd::Create(HINSTANCE hInstance) {
	m_hInstance = hInstance;
	m_hIconMain = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));

    WNDCLASSW wc;

    wc.style = 0 ;
    wc.lpfnWndProc = (WNDPROC) MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;                      
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = MAINWND_CLASS;

    RegisterClass(&wc);

	HWND hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU , 
		0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	memset(&m_nid, 0, sizeof(m_nid));

	m_nid.cbSize = sizeof(m_nid);
	m_nid.hWnd = hWnd;
	m_nid.uID = 123;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE;
	m_nid.uCallbackMessage = WM_USER_SYSTRAY;
	//m_nid.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_MAINICON));
	m_nid.hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_MAINICON),
									IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

	
	int nRet = Shell_NotifyIcon(NIM_ADD, &m_nid);

	return hWnd;
	
}

LRESULT CALLBACK CMainWnd::MainWndProc( HWND hWnd, UINT iMsg, 
										WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {

	case WM_CREATE :
		m_pMainWnd->m_hWnd = hWnd;
		return m_pMainWnd->OnCreate();

	case WM_CLOSE :
		return m_pMainWnd->OnClose();

	case WM_DESTROY :
		return m_pMainWnd->OnDestroy();

	case WM_USER_SYSTRAY :
		return m_pMainWnd->OnSysTray(lParam);

	}

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnSysTray(DWORD dwID) {

	if (dwID == WM_LBUTTONDOWN) {
		keybd_event(VK_OFF,0,0,0);
		keybd_event(VK_OFF,0,KEYEVENTF_KEYUP,0);
	}

	return 0;
}

LRESULT CMainWnd::OnClose() {

	DestroyWindow(m_hWnd);

	Shell_NotifyIcon(NIM_DELETE, &m_nid);

	return 0;

}

LRESULT CMainWnd::OnDestroy() {

	PostQuitMessage(0);

	return 0;
}

LRESULT CMainWnd::OnCreate() {

	return 0;
}

