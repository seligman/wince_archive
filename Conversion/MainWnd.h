class CMainWnd;

#ifndef MAINWND_H__INCLUDED_
#define MAINWND_H__INCLUDED_

#include "main.h"
#include "resource.h"
#include <aygshell.h>

#ifdef POCKET_PC
#else
//  #include <cmdbar.h>
#endif

#include "DlgWnd.h"

#define MAINWND_GUID    L"{3F9D7C70-5F2B-11d4-B866-00B0D040070E}"
#define MAINWND_CLASS   L"ConversionsClass"
#define MAINWND_TITLE   L"Conversions"

#define WM_USER_OBJECT      WM_USER + 1
#define WM_USER_SYSTRAY     WM_USER + 2

struct MAINTYPE {
	LPTSTR szName;
	int nID;
	int cUnits;
	LPTSTR szUnits[75];
	double fUnits[75];
};

class CMainWnd {
public:
	CMainWnd();
	~CMainWnd();

	BOOL	PrevInst();
	HWND	Create(HINSTANCE);

	int			m_cTypes;
	MAINTYPE	m_Types[20];
    HWND        GetHwnd();
    void        DestroyMutex();

private:

	LRESULT	OnCreate();
	LRESULT	OnDestroy();
	LRESULT	OnClose();
    LRESULT OnCommand(WORD wNotifyCode, WORD wID, HWND /* hwndCtrl */);
    LRESULT OnSize(WORD x, WORD y);
    TCHAR * GetCurName(TCHAR * szName);
    void    CleanXML(TCHAR * szData);
    bool    LoadMoneyFile();


	static LRESULT CALLBACK	MainWndProc(HWND, UINT, WPARAM, LPARAM);

	void	ImportData(char * szData);

    SHACTIVATEINFO m_sai;
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	HANDLE		m_hMutex;

	CDlgWnd		m_DlgWnd;
};


#endif