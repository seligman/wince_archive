#include "SelDlg.h"

int CSelDlg::Show(HWND hWnd, HINSTANCE hInstance, bool bScrollLast) {

	m_bScrollLast = bScrollLast;

	m_iRet = actionNone;
	m_cAction = 0;

	DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_SEL), 
			0, 
			(DLGPROC)DlgProc, 
			(LPARAM)this);

	return m_iRet;

}



long __stdcall CSelDlg::DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam) {

	static CSelDlg * parent;

	switch (uMsg) {
	case WM_INITDIALOG:
		parent = (CSelDlg *) lParam;

		parent->m_actionList[parent->m_cAction++] = actionDeleteToTop;
		SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Delete To Top"));

		parent->m_actionList[parent->m_cAction++] = actionDisable;
		SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Disable Accelerators"));

		parent->m_actionList[parent->m_cAction++] = actionAutoScroll;
		SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Auto Scroll"));

		if (parent->m_bScrollLast) {
			parent->m_actionList[parent->m_cAction++] = actionAutoScrollLast;
			SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Auto Scroll - Last Speed"));

			parent->m_actionList[parent->m_cAction++] = actionAutoScrollIncrease;
			SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Auto Scroll - Increase Speed"));
			
			parent->m_actionList[parent->m_cAction++] = actionAutoScrollDecrease;
			SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_ADDSTRING, 0, (LPARAM) _T("Auto Scroll - Decrease Speed"));
		}

		SetForegroundWindow(hDlg);
		SetFocus(GetDlgItem(hDlg, IDC_ACTIONLIST));
		return false;

	case WM_COMMAND:
		switch (LOWORD (wParam)) {
		case IDOK:

			int iRet;
			iRet = SendMessage(GetDlgItem(hDlg, IDC_ACTIONLIST), LB_GETCURSEL, 0, 0);

			if (iRet == LB_ERR) {
				parent->m_iRet = actionNone;
			} else {
				parent->m_iRet = parent->m_actionList[iRet];
			}

			EndDialog(hDlg, IDOK);

			return true;
		case IDCANCEL:
			parent->m_iRet = actionNone;
			EndDialog(hDlg, IDCANCEL);
			return true;
		
		}
		break;
	default:
		return false;

	}
	return true;			
}
