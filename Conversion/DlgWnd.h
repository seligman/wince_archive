class CDlgWnd;

#include "main.h"
#include "MainWnd.h"

#ifndef DLGWND_H__INCLUDED
#define DLGWND_H__INCLUDED

class CDlgWnd {
public:
			CDlgWnd();
			~CDlgWnd();

	void    Init(HINSTANCE hInstance, HWND hWnd, CMainWnd * parent);

	HWND    GetHwnd();
    void    UpdateMoney();
    void    Swap();

private:

    bool    ReadXMLData();
	void	OnInitDialog();
	void	OnUnitSelChange();
	void	OnFromToChange();
    void    OnSize(WORD x, WORD y);

	static long __stdcall DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam);

	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	CMainWnd *	m_parent;

	int			m_nCurSel;
};

#endif
