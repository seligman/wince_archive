#include "main.h"
#include "ControlDlg.h"
#include "resource.h"
#include "commctrl.h"

void CControlDlg::Show(HWND hWnd, HINSTANCE hInstance, DWORD * dwVol, BOOL * bMute) {
//, IMuteIcon * pimi
//	m_pimi = pimi;
	m_dwVol = dwVol;
	m_bMute = bMute;
	m_hInstance = hInstance;

	InitCommonControls();

	DialogBoxParam(hInstance, 
			MAKEINTRESOURCE(IDD_CONTROL), 
			0, 
			(DLGPROC)DlgProc, 
			(LPARAM)this);

}

long __stdcall CControlDlg::DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam) {

	static CControlDlg * parent;

	RECT rt;
	RECT rt2;
	DWORD dwTest = 128;

	switch (uMsg) {
	case WM_HSCROLL:
	case WM_VSCROLL:
		dwTest = SendMessage(GetDlgItem(hDlg, IDC_SLIDER), TBM_GETPOS, 0, 0);
		dwTest = 255 - dwTest;
		(*(parent->m_dwVol)) = dwTest;
		if (!(*(parent->m_bMute))) {
			dwTest = dwTest | (dwTest << 8) | (dwTest << 16) | (dwTest << 24) ;
			waveOutSetVolume(0,dwTest);
		}

		return 0;

	case WM_INITDIALOG:
		parent = (CControlDlg *) lParam;
		parent->m_hWnd = hDlg;
		GetWindowRect(hDlg,&rt2);
		SystemParametersInfo(SPI_GETWORKAREA, NULL, &rt, NULL);
		//SetWindowPos(hDlg,HWND_TOPMOST,rt.right-rt2.right,rt.bottom-rt2.bottom,0,0,SWP_NOSIZE | SWP_NOACTIVATE);
		SetWindowPos(hDlg,HWND_TOPMOST,rt.right-rt2.right,rt.top,0,0,SWP_NOSIZE | SWP_NOACTIVATE);

		SendMessage(GetDlgItem(hDlg, IDC_SLIDER), TBM_SETRANGE, TRUE, MAKELONG(0, 255));

		if ((*(parent->m_bMute))) {
			dwTest = 255-(*(parent->m_dwVol));
			SendMessage(GetDlgItem(hDlg, IDC_MUTE), BM_SETCHECK, BST_CHECKED, 0);
		} else {
			waveOutGetVolume(0,&dwTest);
			dwTest = 255-((dwTest & 0xFF00) >> 8);
		}

		SendMessage(GetDlgItem(hDlg, IDC_SLIDER), TBM_SETPOS, TRUE, dwTest);

		break;

	case WM_COMMAND:
		switch (LOWORD (wParam)) {
		case IDC_MUTE:
			if (HIWORD(wParam) == BN_CLICKED) {
				if (
					SendMessage(GetDlgItem(hDlg, IDC_MUTE), BM_GETCHECK, 0, 0) 
					== BST_CHECKED) {
					(*(parent->m_bMute)) = TRUE;
//					parent->m_pimi->ChangeTo(TRUE);
				} else {
					(*(parent->m_bMute)) = FALSE;
//					parent->m_pimi->ChangeTo(FALSE);
				}
				if (!(*(parent->m_bMute))) {
					dwTest = (*(parent->m_dwVol));
					dwTest = dwTest | (dwTest << 8) | (dwTest << 16) | (dwTest << 24) ;
				} else {
					dwTest = 0;
				}
				waveOutSetVolume(0,dwTest);
			}
			return 0;

		case IDC_OK:
		case IDOK:
			EndDialog(hDlg, IDOK);
			return true;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		}
		break;
	case WM_PAINT:
		return parent->OnPaint((HDC) wParam);

	case WM_LBUTTONDOWN:
		EndDialog(hDlg, IDOK);

	default:
		return false;

	}
	return true;			
}

LRESULT CControlDlg::OnPaint(HDC hDC) {

	PAINTSTRUCT ps;
	HDC hDCDraw = BeginPaint(m_hWnd, &ps);
	POINT pt[3];

//	HPEN hPenHi = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
//	HPEN hPenDa = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

	HPEN hPenHi = CreatePen(PS_SOLID, 1, RGB(127,127,127));
	HPEN hPenDa = CreatePen(PS_SOLID, 1, RGB(127,127,127));
	HPEN hPenOld = (HPEN) SelectObject(hDCDraw,hPenHi);

	pt[0].x = 25;
	pt[0].y = 30;

	pt[1].x = 8;
	pt[1].y = 30;

	pt[2].x = 25;
	pt[2].y = 107;

	Polyline(hDCDraw,pt,3);

	pt[0].x = 25;
	pt[0].y = 107;

	pt[1].x = 25;
	pt[1].y = 30;

	SelectObject(hDCDraw,hPenDa);
	Polyline(hDCDraw,pt,2);

	SelectObject(hDCDraw,hPenOld);
	DeleteObject(hPenDa);
	DeleteObject(hPenHi);

	EndPaint(m_hWnd,&ps);

	return 0;
}