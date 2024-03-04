#include "MainDlg.h"
#include "resource.h"

void CMainDlg::AllRand() {

	TCHAR szName[50];

	RandomName(3,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_M1), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(3,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_M2), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(3,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_M3), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(3,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_M4), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(3,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_M5), WM_SETTEXT, 0, (LPARAM) &szName);


	RandomName(2,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_F1), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(2,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_F2), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(2,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_F3), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(2,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_F4), WM_SETTEXT, 0, (LPARAM) &szName);

	RandomName(2,szName);
	SendMessage(GetDlgItem(m_hWndDlg, IDC_F5), WM_SETTEXT, 0, (LPARAM) &szName);

}

void CMainDlg::SetHwnd(HWND hWnd) {
	m_hWnd = hWnd;
}

CMainDlg::CMainDlg() {


}

CMainDlg::~CMainDlg() {

}

DWORD CMainDlg::FindRandomPos(int nType) {

	DWORD * pnOffset;
	char * szNames;
	int nCount;
	switch (nType) {
	case 1:
		pnOffset = m_nLastNames;
		szNames = m_szLastNames;
		nCount = COUNT_LASTNAMES;
		break;

	case 2:
		pnOffset = m_nFemale;
		szNames = m_szFemale;
		nCount = COUNT_FEMALE;
		break;

	default: //case 3:
		pnOffset = m_nMale;
		szNames = m_szMale;
		nCount = COUNT_MALE;
		break;

	}

	int nRnd = rand() % nCount;

	return (((DWORD)szNames) + (pnOffset[nRnd]));

}

void CMainDlg::RandomName(int nType, TCHAR * szName) {

	int nPos = 0;
	int nPos2 = 0;
	int dwp = 0;

	nPos = 0;
	dwp = FindRandomPos(nType);
	while ( (*(char*)(dwp + nPos)) != 0 ) {
		szName[nPos2] = (TCHAR) (*(char*)(dwp + nPos));
		nPos2 ++;
		nPos ++;
	};
	szName[nPos2] = (TCHAR) 32;
	nPos2 ++;

	nPos = 0;
	dwp = FindRandomPos(1);
	while ( (*(char*)(dwp + nPos)) != 0 ) {
		szName[nPos2] = (TCHAR) (*(char*)(dwp + nPos));
		nPos2 ++;
		nPos ++;
	};
	szName[nPos2] = (TCHAR) 0;
	nPos2 ++;

}

void CMainDlg::Init() {

	int nPos = 0;

	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_MALE), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_M1), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_M2), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_M3), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_M4), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_M5), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_FEMALE), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_F1), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_F2), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_F3), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_F4), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);
	SetWindowPos(GetDlgItem(m_hWndDlg, IDC_F5), 0, 16, nPos += 16, 0, 0, SWP_NOSIZE);

	HRSRC hResInfo;
	HGLOBAL hGlobal;

	hResInfo = FindResource(g_hInstance,MAKEINTRESOURCE(IDR_LASTNAMES),_T("NAMES"));
	hGlobal = LoadResource(g_hInstance, hResInfo);
	m_szLastNames = (char *) LockResource(hGlobal);

	hResInfo = FindResource(g_hInstance,MAKEINTRESOURCE(IDR_FEMALE),_T("NAMES"));
	hGlobal = LoadResource(g_hInstance, hResInfo);
	m_szFemale = (char *) LockResource(hGlobal);

	hResInfo = FindResource(g_hInstance,MAKEINTRESOURCE(IDR_MALE),_T("NAMES"));
	hGlobal = LoadResource(g_hInstance, hResInfo);
	m_szMale = (char *) LockResource(hGlobal);

	DWORD i;
	nPos = 0;
	m_nLastNames[0] = 0;
	for (i = 1; i < COUNT_LASTNAMES; i++) {
		while ( m_szLastNames[nPos] != 0 ) {
			nPos ++;
		}
		nPos ++;
		m_nLastNames[i] = nPos;
	}

	nPos = 0;
	m_nFemale[0] = 0;
	for (i = 1; i < COUNT_FEMALE; i++) {
		while ( m_szFemale[nPos] != 0 ) {
			nPos ++;
		}
		nPos ++;
		m_nFemale[i] = nPos;
	}

	nPos = 0;
	m_nMale[0] = 0;
	for (i = 1; i < COUNT_MALE; i++) {
		while ( m_szMale[nPos] != 0 ) {
			nPos ++;
		}
		nPos ++;
		m_nMale[i] = nPos;
	}

	DialogProc(0, WM_USER_OBJECT, 0, (LPARAM) this);
	CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_MAINDLG), m_hWnd, DialogProc);
	ShowWindow(m_hWndDlg, SW_SHOW);

	AllRand();;

}

//void CMainDlg::SetNewScore(int nScore, int nLevel) {
//
//	if (nScore > m_nScore) {
//		m_nScore = nScore;
//		m_nLevel = nLevel;
//
//		DialogProc(0, WM_USER_OBJECT, 0, (LPARAM) this);
//		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_MainDlg), m_hWnd, DialogProc);
//		SetForegroundWindow(m_hWnd);
//	}
//
//}

BOOL CALLBACK CMainDlg::DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static CMainDlg* m_Parent = NULL;
	HDC hDC = 0;
	static HBRUSH hBrushBack = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	PAINTSTRUCT ps;

	if (uMsg == WM_USER_OBJECT) {
		m_Parent = (CMainDlg*) lParam;
		return TRUE;
	} else {
		switch (uMsg) {
		case WM_CTLCOLORSTATIC :
		case WM_CTLCOLOREDIT :
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (LRESULT) CreateSolidBrush(GetSysColor(COLOR_BTNFACE));


		case WM_PAINT:
			hDC = BeginPaint(hWndDlg,&ps);
			SelectObject(hDC,hBrushBack);
			Rectangle(hDC,-1,-1,320,320);
			EndPaint(hWndDlg,&ps);
			return TRUE;

		case WM_INITDIALOG:
			m_Parent->m_hWndDlg = hWndDlg;
			return TRUE;

		case WM_CLOSE:
			PostMessage(m_Parent->m_hWnd,WM_CLOSE,0,0);
			EndDialog(hWndDlg,IDOK);
			break;

		case WM_COMMAND :
			switch( LOWORD( (DWORD)wParam ) ) { 
			case IDOK:
				PostMessage(m_Parent->m_hWnd,WM_CLOSE,0,0);
				EndDialog(hWndDlg,IDOK);
				return TRUE;

			case IDCANCEL:
				PostMessage(m_Parent->m_hWnd,WM_CLOSE,0,0);
				EndDialog(hWndDlg,IDOK);
				return TRUE;

			case IDC_MORENAMES:
				m_Parent->AllRand();
				break;

			default:
				return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
			}
		default:
			return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
		}
	}
	return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
}

