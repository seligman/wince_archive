class CMainWnd;

#ifndef MAINWND_H__INCLUDED
#define MAINWND_H__INCLUDED

#include "main.h"

#define MAINWND_GUID	_T("{840B15CA-A2F4-465f-A464-124D19BDD658}")
#define MAINWND_CLASS	_T("PocketNavClass")
#define MAINWND_TITLE	_T("PocketNav")

#define WM_USER_SYSTRAY		WM_USER + 2
#define WM_USER_TRIGGER		WM_USER + 3

#define MAX_WINDOWS			20
#define MAX_LINKS			4

class CMainWnd {
public:
								CMainWnd();
								~CMainWnd();

			bool				PrevInst();
			HWND				Create(HINSTANCE);

private:

            HWND                Create2();
			LRESULT 			OnCreate();
			LRESULT 			OnDestroy();
			LRESULT 			OnClose();
			LRESULT				OnSysTray(DWORD dwID);
			LRESULT				OnCommand(WORD wID);
			LRESULT				OnMeasureItem(UINT idCtl, LPMEASUREITEMSTRUCT lpmis);
			LRESULT				OnDrawItem(UINT idCtl, LPDRAWITEMSTRUCT lpdis);
			LRESULT				OnPaint();
			LRESULT				OnLButtonDown(int x, int y, WPARAM, LPARAM);
			LRESULT				OnLButtonDblClick(int x, int y);
			LRESULT				OnLButtonUp(int x, int y, WPARAM, LPARAM);
			LRESULT				OnTimer(WPARAM);
			LRESULT				OnMouseMove(int x, int y);
			void				OnTimerClock(bool bForce);
			
	static	LRESULT CALLBACK	MainWndProc(HWND, UINT, WPARAM, LPARAM);
	static	LRESULT CALLBACK	MainWndProc2(HWND, UINT, WPARAM, LPARAM);
	static	BOOL				EnumWindowsProc(HWND hWnd, DWORD lParam);

			void				AddWindow(LPTSTR);
			void				AppendWindows();
			void				CloseAll(bool);

			void				SaveSettings();
			void				LoadSettings();
			int					CalcActive(int x, int y);
			bool				CanClose(HWND hWnd);
			int					MakeOrder(int * nOrder);
			void				GetOrder(int * nOrder, int nIncoming);
			void				ShowSound();
			void				LaunchLink();
			void				CreateMainMenu();
			void				CleanUpMenu();
			void				CloseRemoteWindow(HWND);
			void				DisplayPopupLinks();
			void				DestroyPopupLinks();
			void				CloseActiveProg();
            void                SafeSetForeground(HWND hWnd);


	enum enumMenu {
		//programs
		menuSep01,
		menuCloseAll,
		menuCloseAllButTop,
		menuSep02,
		menuOptions,
			menuOptToday,
			menuOptTask,
			menuOptCloseIcon,
			menuOptBattery,
			menuOptSound,
			menuOptPPC2k2,
			menuSep03,
			menuOptTapNHold,
			menuOptSounds,
			menuOptIconBorder,
			menuOptOldStrokes,
			menuOptHideIcons,
			menuSep04,
			menuOptSpeed,
			menuOptOrder,
			menuSep05,
			menuAbout,
		menuCloseSelf,
		//---
		menuFirstProgram
	};

	class CWinInfo {
	public:
		HWND	hWnd;
		LPTSTR	szCaption;
	};

	// ---- Sound Variables
	DWORD			m_dwLastVol;
	BOOL			m_bMute;

	// ---- GDI Buffers
	HICON			m_hIcons[12];
	HICON			m_hiBorderIcon;
	HBITMAP			m_hbClose;
	HBITMAP			m_hbCloseSel;

	// ---- Current States
	DWORD			m_nSelected;
	bool			m_bButtonDown;
	int				m_nIconClicked;
	int				m_nIconX;
	int				m_nIconY;
	int				m_nTimerActive;
	DWORD			m_nTimerCheck;
	DWORD			m_nTimerCheckStart;
	DWORD			m_dwLastPos;
	bool			m_bMenuDown;
	bool			m_bDesktopVisible;

	// ---- Standard Windows variables
	static CMainWnd * m_pMainWnd;
	HMENU			m_hMenu;
	HWND			m_hWnd;
	HINSTANCE		m_hInstance;
	HANDLE			m_hMutex;
	HWND			m_hWndFore;
	HWND			m_hWndParent;

	// ---- Display
	bool			m_bShowOK;
	bool			m_bSmall;
	int				m_nWidth;
	bool			m_bIsPPC2k2;

	// ---- Enumeration
	CWinInfo		m_cwiEnums[MAX_WINDOWS + 1];
	int				m_cWindows;
	bool			m_bEnumActive;
	DWORD			m_dwpidLastEnumInstance;
	bool			m_bNoCaptions;

	// ---- Options
	bool			m_bOptTask;
	bool			m_bOptToday;
	bool			m_bOptTapNHold;
	bool			m_bOptCloseSound;
	bool			m_bOptIconBorder;
	bool			m_bOptOldStrokes;
	bool			m_bOptHideIcons;
	bool			m_bOptCloseIcon;
	bool			m_bOptPPC2k2;
	DWORD			m_dwOptShortTime;
	DWORD			m_dwOptLongTime;
	LPTSTR			m_szLastCaption;

	// ----- Popup Shortcuts
	bool			m_bDisplayed;
	HWND			m_hWndLinks[MAX_LINKS];

};

#endif