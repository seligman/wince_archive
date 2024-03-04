class CMainWnd;

#ifndef MAINWND_H__INCLUDED
#define MAINWND_H__INCLUDED

#include "stdafx.h"

#define MAINWND_GUID	_T("{B94CD85D-A91B-4c8a-AD54-2D9080E954F1}")
#define MAINWND_CLASS	_T("PowerOffClass")
#define MAINWND_TITLE	_T("PowerOff")

#define WM_USER_SYSTRAY		WM_USER + 2

class CMainWnd {
public:
								CMainWnd();
								~CMainWnd();

			bool				PrevInst();
			HWND				Create(HINSTANCE);

private:

			LRESULT 			OnCreate();
			LRESULT 			OnDestroy();
			LRESULT 			OnClose();
			LRESULT				OnSysTray(DWORD dwID);
			
	static	LRESULT CALLBACK	MainWndProc(HWND, UINT, WPARAM, LPARAM);

	static CMainWnd * m_pMainWnd;

	NOTIFYICONDATA	m_nid;
	HWND			m_hWnd;
	HINSTANCE		m_hInstance;
	HANDLE			m_hMutex;
	HICON			m_hIconMain;

};

#endif