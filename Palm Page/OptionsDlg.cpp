#include "OptionsDlg.h"
#include "commctrl.h"

void COptionsDlg::Show(HWND hWnd, HINSTANCE hInstance) {
	InitCommonControls();

	m_hWndParent = hWnd;
	m_hInstance = hInstance;

	m_dwShortTime = (* m_pdwShortTime);
	m_dwLongTime = (* m_pdwLongTime);

	m_hbWhite = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

	DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_OPTIONS), 
			0, 
			(DLGPROC)DlgProc, 
			(LPARAM)this);

	DeleteObject(m_hbWhite);
}

long __stdcall COptionsDlg::DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam) {

//	TCHAR sz[1000];
//	wsprintf(sz, L"hWnd: %08x / uMsg: %08x / wParam: %08x / lParam %08x\n", hDlg, uMsg, wParam, lParam);
//	OutputDebugString(sz);


	static COptionsDlg * parent;

	switch (uMsg) {
	case WM_INITDIALOG:
		parent = (COptionsDlg *) lParam;

		SendDlgItemMessage(hDlg, IDC_SHORT_SPIN, UDM_SETRANGE, 0, MAKELONG(100,2));
		SendDlgItemMessage(hDlg, IDC_LONG_SPIN, UDM_SETRANGE, 0, MAKELONG(100,2));

		SendDlgItemMessage(hDlg, IDC_LONG_SPIN, UDM_SETPOS, 0, MAKELONG((*parent->m_pdwLongTime)/50, 0));
		SendDlgItemMessage(hDlg, IDC_SHORT_SPIN, UDM_SETPOS, 0, MAKELONG((*parent->m_pdwShortTime)/50, 0));

		{
			TCHAR sz[100] = _T("");
			_itot((*parent->m_pdwShortTime), sz, 10);
			SendDlgItemMessage(hDlg, IDC_SHORT, WM_SETTEXT, 0, (LPARAM) sz);
			_itot((*parent->m_pdwLongTime), sz, 10);
			SendDlgItemMessage(hDlg, IDC_LONG, WM_SETTEXT, 0, (LPARAM) sz);

		}

		SetForegroundWindow(hDlg);

		return false;

	case WM_VSCROLL:
		{
			int nPos = (short int) HIWORD(wParam);
			HWND hWndSpin = (HWND) lParam;
			TCHAR sz[100] = _T("");
			_itot(nPos * 50, sz, 10);

			if (hWndSpin == GetDlgItem(hDlg, IDC_SHORT_SPIN)) {
				SendDlgItemMessage(hDlg, IDC_SHORT, WM_SETTEXT, 0, (LPARAM) sz);
				parent->m_dwShortTime = nPos * 50;
			} else {
				SendDlgItemMessage(hDlg, IDC_LONG, WM_SETTEXT, 0, (LPARAM) sz);
				parent->m_dwLongTime = nPos * 50;
			}

		}
		break;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (LRESULT) parent->m_hbWhite;
		break;

	case WM_NOTIFY:
		{
			NMHDR * pnmh = (NMHDR *) lParam;
			if (pnmh->code == UDN_DELTAPOS) {
				NM_UPDOWN * lpnmud = (NM_UPDOWN *) lParam;

				if (LOWORD(wParam) == IDC_SHORT_SPIN) {
					int nOtherPos = LOWORD(SendDlgItemMessage(hDlg, IDC_LONG_SPIN, UDM_GETPOS, 0, 0));
					if (lpnmud->iDelta + lpnmud->iPos > nOtherPos - 2) {
						lpnmud->iDelta = 0;
						return true;
					}
				} else {
					int nOtherPos = LOWORD(SendDlgItemMessage(hDlg, IDC_SHORT_SPIN, UDM_GETPOS, 0, 0));
					if (lpnmud->iDelta + lpnmud->iPos < nOtherPos + 2) {
						lpnmud->iDelta = 0;
						return true;
					}
				}
			}
		}
		break;
	case WM_COMMAND:
		switch (LOWORD (wParam)) {
		case IDOK:

			(* parent->m_pdwLongTime) = parent->m_dwLongTime;
			(* parent->m_pdwShortTime) = parent->m_dwShortTime;

			EndDialog(hDlg, IDOK);
			return true;
		case IDCANCEL:

			EndDialog(hDlg, IDCANCEL);
			return true;
		}
		break;
	default:
		return false;

	}
	return true;			
}
