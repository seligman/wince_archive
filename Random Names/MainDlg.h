class CMainDlg;

#ifndef MAINDLG_H__INCLUDED_
#define MAINDLG_H__INCLUDED_

#include "main.h"
#include "resource.h"

class CMainDlg {
public:
			CMainDlg();
			~CMainDlg();

	void	SetHwnd(HWND hWnd);
	void	Init();

private:
	static BOOL CALLBACK DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	DWORD	FindRandomPos(int nType);
	void	RandomName(int nType, TCHAR * szName);
	void	AllRand();


	HWND	m_hWnd;
	HWND	m_hWndDlg;

	char *	m_szLastNames;
	char *	m_szFemale;
	char *	m_szMale;

	DWORD	m_nLastNames[COUNT_LASTNAMES + 5];
	DWORD	m_nFemale[COUNT_FEMALE + 5];
	DWORD	m_nMale[COUNT_MALE + 5];
};

#endif