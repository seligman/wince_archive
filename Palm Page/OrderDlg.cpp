#include "OrderDlg.h"
#include "commctrl.h"

void COrderDlg::Show(HWND hWnd, HINSTANCE hInstance) {
	InitCommonControls();

	m_hWndParent = hWnd;
	m_hInstance = hInstance;

	m_hbWhite = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

	m_Combos[0] = IDC_ORDER_1;
	m_Combos[1] = IDC_ORDER_2;
	m_Combos[2] = IDC_ORDER_3;
	m_Combos[3] = IDC_ORDER_4;
	m_Combos[4] = IDC_ORDER_5;
	m_Combos[5] = IDC_ORDER_6;

	DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_ORDER), 
			0, 
			(DLGPROC)DlgProc, 
			(LPARAM)this);

	DeleteObject(m_hbWhite);
}

long __stdcall COrderDlg::DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam) {

	static COrderDlg * parent;

	switch (uMsg) {
	case WM_INITDIALOG: {
		parent = (COrderDlg *) lParam;

		SetForegroundWindow(hDlg);

		int i;
		for (i = 0; i < 6; i++) {
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Okay Button");
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Time Display");
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Tasks Icon");
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Home Icon");
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Volume Icon");
			SendDlgItemMessage(hDlg, parent->m_Combos[i],CB_ADDSTRING, 0, (LPARAM) L"Battery Icon");

			SendDlgItemMessage(hDlg, parent->m_Combos[i], CB_SETCURSEL, parent->m_nOrder[i], 0);
		}

		}
		return false;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (LRESULT) parent->m_hbWhite;
		break;

	case WM_COMMAND:
		switch (LOWORD (wParam)) {
		case IDOK:
			{
				int i;
				int nTemp;
				for (i = 0; i < iconCount; i++) {
					parent->m_nOrder[i] = iconCount;
				}
				for (i = 0; i < iconCount; i++) {
					nTemp = SendDlgItemMessage(hDlg, parent->m_Combos[i], CB_GETCURSEL, 0, 0);
					if (parent->m_nOrder[nTemp] != iconCount) {
						MessageBox(hDlg, _T("Unable to save changes.  One display element has been specified twice, please correct."), _T("Error"), MB_ICONERROR);
						return true;
					} else {
						parent->m_nOrder[nTemp] = i;
					}
				}

			}

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
