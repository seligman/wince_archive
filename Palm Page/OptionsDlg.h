class COptionsDlg;

#ifndef OPTIONSDLG_H__INCLUDED
#define OPTIONSDLG_H__INCLUDED

#include "main.h"

class COptionsDlg {
public:
			COptionsDlg() {};
			~COptionsDlg() {};

	void	Show(HWND, HINSTANCE);

	HWND		m_hWndParent;
	HINSTANCE	m_hInstance;

	DWORD*		m_pdwShortTime;
	DWORD*		m_pdwLongTime;

	DWORD		m_dwShortTime;
	DWORD		m_dwLongTime;

	HANDLE		m_hbWhite;

private:
	static long __stdcall DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam);

};

#endif