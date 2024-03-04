class CMainWnd;

#ifndef MAINWND_H__INCLUDED
#define MAINWND_H__INCLUDED

#include "stdafx.h"

#define MAINWND_GUID	_T("{906FCA27-188F-48cb-8EB5-F28406207FD1}")
#define MAINWND_CLASS	_T("SoundControlClass")
#define MAINWND_TITLE	_T("SoundControl")

#define WM_USER_SYSTRAY		WM_USER + 2

#include "ControlDlg.h"

class CMainWnd: IMuteIcon {
public:
								CMainWnd();
								~CMainWnd();

			bool				PrevInst();
			HWND				Create(HINSTANCE);
			virtual void		ChangeTo(BOOL bMute);

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
	HICON			m_hIconMute;

	DWORD			m_dwLastVol;
	BOOL			m_bMute;


};

#endif