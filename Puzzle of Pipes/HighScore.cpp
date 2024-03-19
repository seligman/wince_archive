#include "main.h"
#include "resource.h"

#include "HighScore.h"

void CHighScore::SetHwnd(HWND hWnd) {
	m_hWnd = hWnd;
}

#define THE_KEY		_T("Software\\Seligman\\PuzzleOfPipes")
#define THE_HIVE	HKEY_CURRENT_USER

CHighScore::CHighScore() {

}

void CHighScore::Init() {
	DWORD dwTemp = 0;
	DWORD dwTemp2 = 0;

	m_hKey = 0;
	RegCreateKeyEx(THE_HIVE, THE_KEY, 0, REG_NONE,
		REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
		&m_hKey, &dwTemp);

	if (m_hKey == 0) {
		dwTemp = 0;
		RegOpenKeyEx(THE_HIVE, THE_KEY, 0, NULL, &m_hKey);
	}

	dwTemp = 4;
	dwTemp2 = REG_DWORD;
	if (RegQueryValueEx(m_hKey,_T("Score"),NULL, &dwTemp2, (LPBYTE) &m_nScore, &dwTemp) != ERROR_SUCCESS) {
		m_nScore = 0;
	}
	dwTemp = 4;
	dwTemp2 = REG_DWORD;
	if (RegQueryValueEx(m_hKey,_T("Level"),NULL, &dwTemp2, (LPBYTE) &m_nLevel, &dwTemp) != ERROR_SUCCESS) {
		m_nLevel = 0;
	}
	dwTemp = 15 * sizeof(TCHAR);
	m_szName = (LPTSTR) malloc (dwTemp);
	memset(m_szName,0,dwTemp);
	dwTemp2 = REG_SZ;
	if (RegQueryValueEx(m_hKey,_T("Name"),NULL, &dwTemp2, (LPBYTE) m_szName, &dwTemp) != ERROR_SUCCESS) {
		memset(m_szName,0,dwTemp);
	}

	m_hWnd = 0;
}

void CHighScore::UnInit() {

	RegSetValueEx(m_hKey,_T("Score"),0, REG_DWORD, (LPBYTE) &m_nScore, 4);
	RegSetValueEx(m_hKey,_T("Level"),0, REG_DWORD, (LPBYTE) &m_nLevel, 4);
	if (m_szName) {
		RegSetValueEx(m_hKey,_T("Name"),0, REG_SZ, (LPBYTE) m_szName, 
			_tcslen(m_szName) * sizeof(TCHAR));
	}

	if (m_szName) {
		free (m_szName);
	}
	RegCloseKey(m_hKey);

}

CHighScore::~CHighScore() {

}

#ifdef UNDER_CE
#include <aygshell.h>
bool ShowSIP(bool bShow) {
    SIPINFO si;
    bool bRet = false;

    memset( &si, 0, sizeof( si ) );
    si.cbSize = sizeof( si );

    if( SHSipInfo( SPI_GETSIPINFO, 0, &si, 0 ) ) {
        bRet = (si.fdwFlags & SIPF_ON);
        if (bShow) {
            si.fdwFlags |= SIPF_ON;
        } else {
            si.fdwFlags &= ~SIPF_ON;
        }

        SHSipInfo( SPI_SETSIPINFO, 0, &si, 0 );
    }
    return bRet;
}
#endif

void CHighScore::SetNewScore(int nScore, int nLevel) {

	if (nScore > m_nScore) {
		m_nScore = nScore;
		m_nLevel = nLevel;

#ifdef UNDER_CE
		bool bSip = ShowSIP(true);
#endif
		DialogProc(0, WM_USER_OBJECT, 0, (LPARAM) this);
		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_HIGHSCORE), m_hWnd, DialogProc);
		SetForegroundWindow(m_hWnd);
#ifdef UNDER_CE
		ShowSIP(bSip);
#endif
	}

}

BOOL CALLBACK CHighScore::DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static CHighScore* m_Parent = NULL;
	int i = 0;
	HDC hDC = 0;
	static HBRUSH hBrushBack = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	PAINTSTRUCT ps;

	if (uMsg == WM_USER_OBJECT) {
		m_Parent = (CHighScore*) lParam;
		return TRUE;
	} else {
		switch (uMsg) {
		case WM_CTLCOLORSTATIC:
			SetBkMode((HDC) wParam, TRANSPARENT);
			return (LRESULT) CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
		case WM_PAINT:
			hDC = BeginPaint(hWndDlg,&ps);
			SelectObject(hDC,hBrushBack);
			Rectangle(hDC,-1,-1,200,200);
			EndPaint(hWndDlg,&ps);
			return TRUE;

		case WM_INITDIALOG:
			if (m_Parent->m_szName) {
				SendDlgItemMessage(hWndDlg,IDC_NAME,WM_SETTEXT,0,(LPARAM) m_Parent->m_szName);
			}

			return TRUE;
		case WM_CLOSE:
			EndDialog(hWndDlg,IDOK);
			break;
		case WM_COMMAND :
			switch( LOWORD( (DWORD)wParam ) ) { 
			case IDOK:
				if (m_Parent->m_szName) {
					free(m_Parent->m_szName);
				}
				i = SendDlgItemMessage(hWndDlg, IDC_NAME, WM_GETTEXTLENGTH, 0, 0);
				if (i > 10) {
					i = 10;
				}
				m_Parent->m_szName = (LPTSTR) malloc ((2 + i) * sizeof(TCHAR));
				SendDlgItemMessage(hWndDlg, IDC_NAME, WM_GETTEXT, i+1, (LPARAM) m_Parent->m_szName);

				EndDialog(hWndDlg,IDOK);
				return TRUE;
			case IDCANCEL:
				EndDialog(hWndDlg,IDOK);
				return TRUE;
			default:
				return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
			}
		default:
			return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
		}
	}
	return DefWindowProc(hWndDlg, uMsg, wParam, lParam);
}

int CHighScore::GetLevel() {

	return (m_nLevel);

}

int CHighScore::GetScore() {

	return (m_nScore);

}

LPTSTR CHighScore::GetName() {

	return (m_szName);

}

