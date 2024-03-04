class CMainWnd;

#ifndef MAINWND_H__INCLUDED__
#define MAINWND_H__INCLUDED__

#include "MainDlg.h"

class CMainWnd {
public:
			CMainWnd();
			~CMainWnd();

	BOOL	PrevInst();
	HWND	Create(HINSTANCE);

private:
	LRESULT	OnCreate();
	LRESULT	OnDestroy();
	LRESULT	OnClose();

	static LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	HANDLE		m_hMutex;

	CMainDlg	m_Dlg;
};

#endif