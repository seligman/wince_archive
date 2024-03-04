class COrderDlg;

#ifndef ORDERDLG_H__INCLUDED
#define ORDERDLG_H__INCLUDED

#include "main.h"

class COrderDlg {
public:
			COrderDlg() {};
			~COrderDlg() {};

	void		Show(HWND, HINSTANCE);

	HWND		m_hWndParent;
	HINSTANCE	m_hInstance;

	HANDLE		m_hbWhite;

	int			m_nOrder[iconCount];

private:

	DWORD		m_Combos[iconCount];

	static long __stdcall DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam);
};

#endif