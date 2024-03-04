#define MY_POWER_CHECK
#ifdef MY_POWER_CHECK
    bool g_bWhite = false;
#endif

#include "MainWnd.h"
#include "resource.h"
#include "registry.h"
#include "OptionsDlg.h"
#include "ControlDlg.h"

#include <aygshell.h>

bool g_bHiDPI = false;
#define DPI(a,b) (g_bHiDPI?(b):(a))

#define MW_DESKCLASS	_T("DesktopExplorerWindow")
#define MW_DESKWIN		_T("Desktop")
#define MW_DESKWIN2		_T("Today Screen")

#define MW_REGKEY		_T("Software\\Seligman\\PocketNav")

#define TIMER_CLOCK		1
#define TIMER_TAPNHOLD	2

#define TOP_OFFSET		0

//#define LOG_ENUM_DEBUG

#ifndef LOG_ENUM_DEBUG

#define LM(a,b) void()

#else

#define LM(a,b) xLM(__LINE__,a,b)

void xLM(DWORD nLine, TCHAR * szNote, HWND hWndWindow) {
	static DWORD nLastTick = GetTickCount();
	DWORD nTick = GetTickCount();

	TCHAR szOutput[2000];
	TCHAR szTime[255];

	GetTimeFormat(LOCALE_USER_DEFAULT, NULL, NULL, NULL, szTime, 255);

	TCHAR szClass[255];
	TCHAR szTitle[255];

	if (hWndWindow != 0) {
		GetClassName(hWndWindow, szClass, 255);
		int nTick2 = GetTickCount() - nTick;
		GetWindowText(hWndWindow, szTitle, 255);
		int nTick3 = GetTickCount() - nTick;

		wsprintf(szOutput, L"%d: %s (%d - %4d) - %08x - %s ([%s]/[%s] %d/%d)\r\n",
			nLine, szTime, nTick, nTick - nLastTick, hWndWindow, szNote, szClass, szTitle, nTick2, nTick3);
	} else {
		wsprintf(szOutput, L"%d: %s (%d - %4d) - %08x - %s\r\n",
			nLine, szTime, nTick, nTick - nLastTick, hWndWindow, szNote);
	}
	nLastTick = nTick;


	HANDLE hFile = CreateFile(L"\\PocketNav - Debug.txt", GENERIC_READ | GENERIC_WRITE, 
		0, NULL, OPEN_ALWAYS, NULL, NULL);

	SetFilePointer(hFile, 0, 0, FILE_END);

	char * szFin[2000];
	wcstombs((char*)szFin, szOutput, 2000);

	DWORD dwRet = 0;
	WriteFile(hFile, szFin, strlen((char*)szFin), &dwRet, NULL);

	CloseHandle(hFile);
}
#endif

#define REG_POPMENUFONTKEY TEXT("SYSTEM\\GWE\\Menu\\PopFnt")
#define REG_NAME TEXT("Nm")
#define REG_HEIGHT TEXT("Ht")
#define REG_INPOINTS TEXT("HtInPts")
#define REG_ITALIC TEXT("It")
#define REG_WEIGHT TEXT("Wt")
#define REG_CHARSET TEXT("CS")

/* LOGFONT information for owner drawing */

static LOGFONT lfont = {
  -12, 0, 0, 0, 0x0, 0x00, 0x00, 0x00, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
  CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH,
  TEXT("")
};


HFONT CreateMenuFont(BOOL bItalic, HDC hDC) {
	LONG res;
	TCHAR fontname[80];
	DWORD italic, weight, charset;
	DWORD sz, datatype;
    DWORD inpoints;
    int height;
	HKEY hKey;
	
	res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REG_POPMENUFONTKEY,
		REG_OPTION_NON_VOLATILE, KEY_READ, &hKey);
	if (res == ERROR_SUCCESS) {
		sz = sizeof(fontname);
		res = RegQueryValueEx(hKey, REG_NAME, (LPDWORD)NULL, &datatype,
			(LPBYTE)fontname, &sz);
		
		if (res == ERROR_SUCCESS) {
			lstrcpy(lfont.lfFaceName, fontname);
		}
		
		sz = sizeof(DWORD);
		res = RegQueryValueEx(hKey, REG_INPOINTS, (LPDWORD)NULL, &inpoints,
			(LPBYTE)&height, &sz);
		if (res != ERROR_SUCCESS) {
            inpoints = 0;
        }

        sz = sizeof(DWORD);
		res = RegQueryValueEx(hKey, REG_HEIGHT, (LPDWORD)NULL, &datatype,
			(LPBYTE)&height, &sz);
		if (res == ERROR_SUCCESS) {
            if (inpoints != 0)
            {
                // Add 96 to make it look right
                //  it's a hack, but a best guess
                lfont.lfHeight = -(((height+96) * GetDeviceCaps(hDC, LOGPIXELSY)) / 7200);
            }
            else
            {
			    lfont.lfHeight = (LONG)height;
            }
		}
		
		sz = sizeof(DWORD);
		res = RegQueryValueEx(hKey, REG_ITALIC, (LPDWORD)NULL, &datatype,
			(LPBYTE)&italic, &sz);
		if (res == ERROR_SUCCESS) {
			lfont.lfItalic = (BYTE)italic;
		}
		
		sz = sizeof(DWORD);
		res = RegQueryValueEx(hKey, REG_WEIGHT, (LPDWORD)NULL, &datatype,
			(LPBYTE)&weight, &sz);
		if (res == ERROR_SUCCESS) {
			lfont.lfWeight = weight;
		}
		
		sz = sizeof(DWORD);
		res = RegQueryValueEx(hKey, REG_CHARSET, (LPDWORD)NULL, &datatype,
			(LPBYTE)&charset, &sz);
		if (res == ERROR_SUCCESS) {
			lfont.lfCharSet = (BYTE)charset;
		}
		RegCloseKey(hKey);
	}

	lfont.lfItalic = bItalic;

	return CreateFontIndirect(&lfont); 

}

int CMainWnd::MakeOrder(int * nOrder) {

	int nRet = 0;
	int nMult = 1;
	int nRemain = iconCount;
	int j;
	int i;
	int nCopyOrder[iconCount];

	for (i = 0; i < iconCount; i++) {
		nCopyOrder[i] = nOrder[i];
	}

	for (i = 0; i < iconCount; i++) {
		nRet += nCopyOrder[i] * nMult;
		for (j = i + 1; j < iconCount; j++) {
			if (nCopyOrder[j] > nCopyOrder[i]) {
				nCopyOrder[j] --;
			}
		}
		nMult *= nRemain;
		nRemain --;
	}

	return nRet;

}

void CMainWnd::GetOrder(int * nOrder, int nIncoming) {
	int i;
	int j;
	int nCur = iconCount;
	int nLeft[iconCount+1];
	for (i = 0; i < iconCount; i++) {
		nLeft[i] = i;
	};
	nLeft[iconCount] = 0;

	for (i = 0; i < iconCount; i++) {
		nOrder[i] = nLeft[nIncoming % nCur];
		for (j = nIncoming % nCur; j < iconCount; j++) {
			nLeft[j] = nLeft[j+1];
		}
		nIncoming /= nCur;
		nCur --;
	}
}

void CMainWnd::SaveSettings() {

	DWORD dwSetting;
	CRegistryKey * reg;

	reg = new CRegistryKey(HKEY_LOCAL_MACHINE, MW_REGKEY);

	dwSetting = m_bOptToday?1:0;
	reg->SetRegValueDW(_T("Today"), dwSetting);

	dwSetting = m_bOptPPC2k2?1:0;
	reg->SetRegValueDW(_T("PPC2k2"), dwSetting);

	dwSetting = m_bOptOldStrokes?1:0;
	reg->SetRegValueDW(_T("OldStrokes"), dwSetting);

	dwSetting = m_bOptTask?1:0;
	reg->SetRegValueDW(_T("Task"), dwSetting);

	dwSetting = m_bOptCloseIcon?1:0;
	reg->SetRegValueDW(_T("CloseIcon"), dwSetting);

	dwSetting = m_bOptTapNHold?1:0;
	reg->SetRegValueDW(_T("TapNHold"), dwSetting);

	dwSetting = m_bOptCloseSound?1:0;
	reg->SetRegValueDW(_T("CloseSound"), dwSetting);

	dwSetting = m_dwOptShortTime;
	reg->SetRegValueDW(_T("ShortTime"), dwSetting);

	dwSetting = m_dwOptLongTime;
	reg->SetRegValueDW(_T("LongTime"), dwSetting);

	dwSetting = m_bOptIconBorder?1:0;
	reg->SetRegValueDW(_T("IconBorder"), dwSetting);

	dwSetting = m_bOptHideIcons?1:0;
	reg->SetRegValueDW(_T("HideIcons"), dwSetting);

	delete reg;

}

void CMainWnd::LoadSettings() {
	DWORD dwSetting;
	CRegistryKey * reg;

	reg = new CRegistryKey(HKEY_LOCAL_MACHINE, MW_REGKEY);

	if (reg->GetRegValueDW(_T("PPC2k2"), dwSetting)) {
		m_bOptPPC2k2 = (dwSetting==1?true:false);
	} else {
		m_bOptPPC2k2 = true;
	}

	if (reg->GetRegValueDW(_T("Today"),dwSetting)) {
		m_bOptToday = (dwSetting==1?true:false);
	} else {
		m_bOptToday = true;
	}

	if (reg->GetRegValueDW(_T("OldStrokes"),dwSetting)) {
		m_bOptOldStrokes = (dwSetting==1?true:false);
	} else {
		m_bOptOldStrokes = false;
	}

	if (reg->GetRegValueDW(_T("IconBorder"), dwSetting)) {
		m_bOptIconBorder = (dwSetting==1?true:false);
	} else {
		m_bOptIconBorder = false;
	}

	if (reg->GetRegValueDW(_T("Task"),dwSetting)) {
		m_bOptTask = (dwSetting==1?true:false);
	} else {
		m_bOptTask = true;
	}

	if (reg->GetRegValueDW(_T("CloseIcon"),dwSetting)) {
		m_bOptCloseIcon = (dwSetting==1?true:false);
	} else {
		m_bOptCloseIcon = false;
	}

	if (reg->GetRegValueDW(_T("TapNHold"),dwSetting)) {
		m_bOptTapNHold = (dwSetting==1?true:false);
	} else {
		m_bOptTapNHold = false;
	}

	if (reg->GetRegValueDW(_T("ShortTime"),dwSetting)) {
		m_dwOptShortTime = dwSetting;
	} else {
		m_dwOptShortTime = 100;
	}

	if (reg->GetRegValueDW(_T("LongTime"),dwSetting)) {
		m_dwOptLongTime = dwSetting;
	} else {
		m_dwOptLongTime = 500;
	}

	if (reg->GetRegValueDW(_T("CloseSound"),dwSetting)) {
		m_bOptCloseSound = (dwSetting==1?true:false);
	} else {
		m_bOptCloseSound = false;
	}

	if (reg->GetRegValueDW(_T("HideIcons"), dwSetting)) {
		m_bOptHideIcons = (dwSetting==1?true:false);
	} else {
		m_bOptHideIcons = false;
	}


	delete reg;
}

LRESULT CMainWnd::OnPaint() {

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hWnd, &ps);
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbBufferOld = (HBITMAP) SelectObject(hdcBuffer, CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN)+DPI(60,120), DPI(26,52)));

	DWORD dwColor = 0;
	if (m_bOptPPC2k2) {
		bool bFound = false;
		CRegistryKey reg(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Color"));
		if (reg.GetRegValueBinaryAsDW(_T("8"), dwColor)) {
			bFound = true;
		}
		if (!bFound) {
			typedef COLORREF (CALLBACK *COLORAPI)(int nParam);
			static HMODULE hMod = NULL;
			static COLORAPI pColor = NULL;
			static bool bAttempted = false;
			if (!bAttempted)
			{
				hMod = LoadLibrary(_T("commctrl.dll"));
				if (hMod) {
					pColor = (COLORAPI) GetProcAddress(hMod, (LPTSTR) 77);
				}
				bAttempted = true;
			}
			if (pColor)
			{
				dwColor = pColor( 0x10000008 );
				bFound = true;
			}
		}
		if (!bFound)
		{
			dwColor = GetSysColor(COLOR_ACTIVECAPTION);
		}

	} else {
		dwColor = GetSysColor(COLOR_ACTIVECAPTION);
	}

#ifdef MY_POWER_CHECK
    if (g_bWhite)
    {
        dwColor = RGB(255,255,255);
    }
#endif
    
    
    HBRUSH hbrBufferOld = (HBRUSH) SelectObject(hdcBuffer, CreateSolidBrush(dwColor));
	
	Rectangle(hdcBuffer, -1, -1, GetSystemMetrics(SM_CXSCREEN) + DPI(62,124), DPI(28,56));
	DeleteObject(SelectObject(hdcBuffer, hbrBufferOld));

	// draw icons
	int nPos = GetSystemMetrics(SM_CXSCREEN);
	if (m_bOptPPC2k2) {
		nPos -= DPI(15,31);
		if (m_bOptIconBorder) {
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hiBorderIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		}
		DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==1?1:0], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		nPos -= DPI(16,32);
		if (m_bOptIconBorder) {
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hiBorderIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		}
		if (m_bShowOK) {
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==3?9:8], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		} else {
			if (m_bDesktopVisible) {
				// desktop window, do nothing
			} else {
				DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==3?11:10], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
			}
		}
	} else {
		if (m_bShowOK) {
			nPos -= DPI(21,42);
			DrawIconEx(hdcBuffer, nPos, DPI(4,8), m_hIcons[m_nSelected==3?5:4], DPI(19,38), DPI(19,38), 0, FALSE, DI_NORMAL);
		}
		if (m_bOptToday) {
			nPos -= DPI(18,36);
			if (m_bOptIconBorder) {
				DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hiBorderIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
			}
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==2?3:2], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		}
		if (m_bOptTask) {
			nPos -= DPI(18,36);
			if (m_bOptIconBorder) {
				DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hiBorderIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
			}
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==1?1:0], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		}
		if (m_bOptCloseIcon) {
			nPos -= DPI(18,36);
			if (m_bOptIconBorder) {
				DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hiBorderIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
			}
			DrawIconEx(hdcBuffer, nPos, DPI(5,10), m_hIcons[m_nSelected==4?7:6], DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		}


		// draw time
		if (!m_bSmall) {
			nPos -= DPI(50,100);
			RECT rt;
			rt.top = 0;
			rt.left = nPos;
			rt.right = nPos + DPI(48,96);
			rt.bottom = DPI(26,52);
			SetBkMode(hdcBuffer, TRANSPARENT);
			SetTextColor(hdcBuffer, RGB(255,255,255));

			LOGFONT lf;
			lf.lfHeight = -(10 * GetDeviceCaps(hdc, LOGPIXELSY) / 72);
			lf.lfWidth = 0;
			lf.lfEscapement = 0;
			lf.lfOrientation = 0;
			lf.lfWeight = 700;
			lf.lfItalic = FALSE;
			lf.lfUnderline = FALSE;
			lf.lfStrikeOut = FALSE;
			lf.lfCharSet = ANSI_CHARSET;
			lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
			lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			lf.lfQuality = DEFAULT_QUALITY;
			lf.lfPitchAndFamily = DEFAULT_PITCH;
			_tcscpy(lf.lfFaceName, _T("Tahoma"));

			HFONT hfOld = (HFONT) SelectObject(hdcBuffer, CreateFontIndirect(&lf));

			TCHAR szTime[100];

			SYSTEMTIME st;
			GetLocalTime(&st);
			GetTimeFormat(LOCALE_USER_DEFAULT, TIME_NOSECONDS, &st, NULL, szTime, 100);

			// -- Begin STRIP_TIME
			#define STRIP_TIME(c, o, n) \
			if (\
				_tcscmp(\
					((TCHAR*)&szTime) + (_tcslen(szTime)-c)\
					,\
					o\
					) == 0\
				) \
			{\
				_tcscpy((TCHAR*)&szTime + (_tcslen(szTime)-c), n);\
			}
			// -- End STRIP_TIME

				 STRIP_TIME(5, L" a.m.", L"a")
			else STRIP_TIME(5, L" p.m.", L"p")
			else STRIP_TIME(5, L" A.M.", L"a")
			else STRIP_TIME(5, L" P.M.", L"p")
			else STRIP_TIME(4, L"a.m.", L"a")
			else STRIP_TIME(4, L"p.m.", L"p")
			else STRIP_TIME(4, L"A.M.", L"a")
			else STRIP_TIME(4, L"P.M.", L"p")
			else STRIP_TIME(3, L" am", L"a")
			else STRIP_TIME(3, L" pm", L"p")
			else STRIP_TIME(3, L" AM", L"a")
			else STRIP_TIME(3, L" PM", L"p")
			else STRIP_TIME(2, L"am", L"a")
			else STRIP_TIME(2, L"pm", L"p")
			else STRIP_TIME(2, L"AM", L"a")
			else STRIP_TIME(2, L"PM", L"p")

			DrawText(hdcBuffer, szTime, _tcslen(szTime), &rt, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			DeleteObject(SelectObject(hdcBuffer, hfOld));
		}
	}

	BitBlt(hdc, m_nWidth - (GetSystemMetrics(SM_CXSCREEN)-nPos)-DPI(100,200), 0, GetSystemMetrics(SM_CXSCREEN), DPI(26,52), hdcBuffer, nPos-DPI(100,200), 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBuffer, hbBufferOld));
	DeleteDC(hdcBuffer);
	EndPaint(m_hWnd, &ps);

	return 0;
}

int CMainWnd::CalcActive(int x, int y) {

	//1 Today
	//2 Task
	//3 Ok

	x += GetSystemMetrics(SM_CXSCREEN) - m_nWidth;
	x = GetSystemMetrics(SM_CXSCREEN) - x;
	int nActive = 0;
	if (m_bOptPPC2k2) {
		if ((x > 0) && (x < DPI(16,32))) {
			nActive = 2;
		} else {
			nActive = 3;
		}
	} else {
		if (m_bShowOK) {
			x = x - DPI(21,42);
			if (x < 0) {
				nActive = 3;
			}
		}
		if ((x > 0) && (x < DPI(18,36))) {
			if (m_bOptToday) {
				nActive = 1;
			} else if (!m_bOptToday && m_bOptTask) {
				nActive = 2;
			} else if (!m_bOptToday && !m_bOptTask && m_bOptCloseIcon) {
				nActive = 4;
			}
		} else if ((x > DPI(18,36)) && (x < DPI(36,72))) {
			if (m_bOptToday && m_bOptTask) {
				nActive = 2;
			} else if ((m_bOptToday || m_bOptTask) && m_bOptCloseIcon) {
				nActive = 4;
			} else {
				nActive = -1;
			}
		} else if (x > DPI(36,72)) {
			nActive = -1;
		}
	}

	return nActive;
}

LRESULT CMainWnd::OnLButtonDown(int x, int y, WPARAM wParam, LPARAM lParam) {

	SetCapture(m_hWnd);

	m_bButtonDown = true;
	m_nIconClicked = 0;
	m_nIconX = x;
	m_nIconY = y;

	if (CalcActive(x,y) == 3) {
		m_nTimerActive = 3;
		m_nSelected = 3;
		InvalidateRect(m_hWnd, NULL, FALSE);
		UpdateWindow(m_hWnd);

	} else if (CalcActive(x,y) == -1) {
		m_nSelected = -1;
		m_nTimerActive = -1;

		POINT pt;
		pt.x = x;
		pt.y = y;
		ClientToScreen(m_hWnd, &pt);
		ScreenToClient(m_hWndParent, &pt);
		if (m_bOptTask) {
			pt.x += DPI(18,36);
		}
		if (m_bOptToday) {
			pt.x += DPI(18,36);
		}

		SendMessage(m_hWndParent, WM_LBUTTONDOWN, wParam,  MAKEWPARAM(pt.x, pt.y));
		SetCapture(m_hWnd);

	} else {
		if (m_bOptTapNHold) {
			switch (CalcActive(x,y)) {
			case 1:
				m_nIconClicked = 1;
				m_nTimerActive = 1;
				m_nTimerCheck = GetTickCount() + m_dwOptLongTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
				break;
			case 2:
				m_nIconClicked = 2;
				m_nTimerActive = 2;
				m_nTimerCheck = GetTickCount() + m_dwOptLongTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
				break;
			case 4:
				m_nIconClicked = 3;
				m_nTimerActive = 3;
				m_nTimerCheck = GetTickCount() + m_dwOptLongTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
			}
		} else {
			m_nIconClicked = CalcActive(x,y);
		}
	}

	return 0;
}

void CMainWnd::LaunchLink() {

	SHELLEXECUTEINFO sei;

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS; //SEE_MASK_FLAG_NO_UI | 
	sei.hwnd = 0;
	sei.lpVerb = L"open";
	sei.lpFile = L"\\windows\\PocketNav Link.lnk";
	sei.lpParameters = NULL;
	sei.lpDirectory = NULL;
	sei.nShow = SW_SHOW;
	sei.hInstApp = NULL;

	ShellExecuteEx(&sei);

}

LRESULT CMainWnd::OnLButtonUp(int x, int y, WPARAM wParam, LPARAM lParam) {

	if (m_bDisplayed) {
		//try to find links here
		ReleaseCapture();

		RECT rt;
		POINT pt;
		pt.x = LOWORD(GetMessagePos());
		pt.y = HIWORD(GetMessagePos());
		int i;
		int nFound = -1;
		for (i = 0; i < MAX_LINKS; i++) {
			GetWindowRect(m_hWndLinks[i], &rt);
			if (PtInRect(&rt, pt)) {
				nFound = i;
			}
		}
		
		DestroyPopupLinks();

		switch (nFound) {
		case -1:
			break;
		case 0:
			ShowSound();
			break;
		case 1:
			LaunchLink();
			break;
		case 2:
			SafeSetForeground(FindWindow(MW_DESKCLASS, MW_DESKWIN));
			break;
		case 3:
			CloseActiveProg();
			break;
		}

		return 0;
	}

	ReleaseCapture();

	if (m_nSelected == 3) {
		POINT pt;
		pt.x = x;
		pt.y = y;
		if (m_bOptPPC2k2) {
			pt.x += DPI(15,30);
		}
		ClientToScreen(m_hWnd, &pt);
		ScreenToClient(m_hWndParent, &pt);

		SendMessage(m_hWndParent, WM_LBUTTONDOWN, wParam,  MAKEWPARAM(pt.x, pt.y));
		SendMessage(m_hWndParent, WM_LBUTTONUP, wParam,  MAKEWPARAM(pt.x, pt.y));

		m_nSelected = 0;
		InvalidateRect(m_hWnd, NULL, FALSE);
		OnTimer(TIMER_CLOCK);
		
	} else if (m_nSelected == -1) {
		m_nSelected = 0;
		POINT pt;
		pt.x = x;
		pt.y = y;
		ClientToScreen(m_hWnd, &pt);
		ScreenToClient(m_hWndParent, &pt);
		if (m_bOptTask) {
			pt.x += DPI(18,36);
		}
		if (m_bOptToday) {
			pt.x += DPI(18,36);
		}
		if (m_bOptCloseIcon) {
			pt.x += DPI(18,36);
		}

		SendMessage(m_hWndParent, WM_LBUTTONUP, wParam,  MAKEWPARAM(pt.x, pt.y));

	} else {

	    static LONG nLast = 0;
	    LONG nCur = GetTickCount();
	    if (nCur - nLast <= 500) {
		    OnLButtonDblClick(x,y);
		    return 0;
	    }
	    nLast = nCur;

	    if (!m_bButtonDown) {
		    return(0);
	    }
	    m_bButtonDown = false;

		if (m_bOptTapNHold) {
			switch (CalcActive(x,y)) {
			case 1:
				m_nTimerActive = 11;
				m_nTimerCheck = GetTickCount() + m_dwOptShortTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
				break;
			case 2:
				m_nTimerActive = 12;
				m_nTimerCheck = GetTickCount() + m_dwOptShortTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
				break;
			case 4:
				m_nTimerActive = 14;
				m_nTimerCheck = GetTickCount() + m_dwOptShortTime;
				m_nTimerCheckStart = GetTickCount();
				SetTimer(m_hWnd, TIMER_TAPNHOLD, 50, NULL);
				break;
				//Old code to popup link/sound control
			default:
				if (m_bOptOldStrokes) {
					if (m_nIconClicked == 2 || m_nIconClicked == 1) {
						if (abs(m_nIconX-x) >= DPI(20,40) && abs(m_nIconX-x) <= DPI(60,120) &&
							abs(y-m_nIconY) >= 0 && abs(y-m_nIconY) <= DPI(5,10)) {
							m_nTimerActive = -1;
							ShowSound();
						} else if (abs(m_nIconX-x) >= DPI(60,120) && (m_nIconX-x) <= DPI(120,240) &&
							abs(y-m_nIconY) >= 0 && abs(y-m_nIconY) <= DPI(5,10)) {
							LaunchLink();
						}
					}
				}
				break;
			}
		} else {
			switch (CalcActive(x,y)) {
			case 1:
				m_nSelected = 2;
				InvalidateRect(m_hWnd, NULL, FALSE);
				UpdateWindow(m_hWnd);
				SafeSetForeground(FindWindow(MW_DESKCLASS, MW_DESKWIN));
				m_nSelected = 0;
				InvalidateRect(m_hWnd, NULL, FALSE);
				break;
			case 2:
				OnSysTray(WM_LBUTTONDOWN);
				break;
			case 4:
				CloseActiveProg();
				break;
				//old code to popup link/sound control
			default:
				if (m_bOptOldStrokes) {
					if (m_nIconClicked == 2 || m_nIconClicked == 1) {
						if (abs(m_nIconX-x) >= DPI(20,40) && abs(m_nIconX-x) <= DPI(60,120) &&
							abs(y-m_nIconY) >= 0 && abs(y-m_nIconY) <= DPI(5,10)) {
							m_nTimerActive = -1;
							ShowSound();
						} else if (abs(m_nIconX-x) >= DPI(60,120) && (m_nIconX-x) <= DPI(120,240) &&
							abs(y-m_nIconY) >= 0 && abs(y-m_nIconY) <= DPI(5,10)) {
							LaunchLink();
						}
					}
				}
				break;

			}
		}
	}

	return 0;
}

LRESULT CMainWnd::OnLButtonDblClick(int x, int y) {
	m_bButtonDown = false;
	m_nTimerActive = 0;

	switch (CalcActive(x,y)) {
	case 4:
	case 1:
		OnSysTray(WM_LBUTTONDOWN);
		break;
	case 2: // Close Active Prog (menupop)
		if (m_bOptTapNHold) {
			CloseActiveProg();
		}
		break;
	}

	return 0;
}

void CMainWnd::CloseActiveProg() {
	m_bNoCaptions = true;
	AppendWindows();
	m_bNoCaptions = false;

	if (CanClose(m_cwiEnums[1].hWnd)) {
		if (m_bOptCloseSound) {
			PlaySound(L"MenuPop", NULL, SND_ASYNC); 
		}
		
		CloseRemoteWindow(m_cwiEnums[1].hWnd);
		if (m_cWindows > 1) {
			SafeSetForeground(m_cwiEnums[2].hWnd);
		}
	}
}

CMainWnd * CMainWnd::m_pMainWnd = NULL;

bool CMainWnd::CanClose(HWND hWnd) {
	DWORD dwpidDesktop = NULL;
	DWORD dwpidCompare = NULL;

	GetWindowThreadProcessId(FindWindow(MW_DESKCLASS, MW_DESKWIN),&dwpidDesktop);
	GetWindowThreadProcessId(hWnd, &dwpidCompare);

	if (dwpidCompare == dwpidDesktop) {
		return false;
	} else {
		return true;
	}
}

void CMainWnd::ShowSound() {
	CControlDlg dlg;
	dlg.Show(m_hWnd, m_hInstance, &m_dwLastVol, &m_bMute);
}


CMainWnd::CMainWnd() {

    HDC hdc = GetDC(0);
    if (GetDeviceCaps(hdc, LOGPIXELSX) > 96)
    {
        g_bHiDPI = true;
    }
    ReleaseDC(0, hdc);

	m_bIsPPC2k2 = false;
	m_bMute = FALSE;
	m_dwLastVol = 0;
	m_bEnumActive = false;
	m_bShowOK = false;
	m_bSmall = false;
	m_bButtonDown = false;
	m_nTimerActive = 0;
	m_bNoCaptions = false;
	m_dwOptShortTime = 100;
	m_dwOptLongTime = 500;
	m_bOptCloseSound = false;
	m_hWndFore = NULL;
	m_szLastCaption = NULL;
	m_dwLastPos = 0;
	m_bMenuDown = false;
	m_bDisplayed = false;
	m_bDesktopVisible = false;

	m_bOptPPC2k2 = false;
	m_bOptCloseIcon = false;
	m_bOptTask = true;
	m_bOptToday = true;
	m_bOptTapNHold = true;
	m_bOptIconBorder = false;
	m_bOptOldStrokes = false;
	m_bOptHideIcons = false;
	m_nSelected = 0;

	for(int i=0; i <= MAX_WINDOWS; i++) {
		m_cwiEnums[i].szCaption = NULL;
	}

	m_pMainWnd = this;

}

CMainWnd::~CMainWnd() {
	m_pMainWnd = NULL;
	if (m_szLastCaption) {
		free(m_szLastCaption);
	}
}

bool CMainWnd::PrevInst() {
	m_hMutex = CreateMutex(NULL, true, MAINWND_GUID);

	return (GetLastError() == ERROR_ALREADY_EXISTS);
}

HWND CMainWnd::Create(HINSTANCE hInstance) {
	m_hInstance = hInstance;

	m_hIcons[0] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OPT_TASK), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[1] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OPT_TASK_SEL), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[2] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OPT_TODAY), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[3] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OPT_TODAY_SEL), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[4] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OK), IMAGE_ICON, DPI(19,38), DPI(19,38), 0);
	m_hIcons[5] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_OK_SEL), IMAGE_ICON, DPI(19,38), DPI(19,38), 0);
	m_hIcons[6] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_MYCLOSE), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[7] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_MYCLOSE_SEL), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[8] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_2OK), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[9] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_2OK_SEL), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[10] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_2CLOSE), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hIcons[11] = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_2CLOSE_SEL), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
	m_hiBorderIcon = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_BORDER_ICON), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);

	m_hbClose = LoadBitmap(hInstance, MAKEINTRESOURCE(DPI(IDB_CLOSE,IDB_CLOSE2)));
	m_hbCloseSel = LoadBitmap(hInstance, MAKEINTRESOURCE(DPI(IDB_CLOSE_SEL,IDB_CLOSE2_SEL)));

    WNDCLASSW wc;

    wc.style = 0 ;
    wc.lpfnWndProc = (WNDPROC) MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;                      
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject(RGB(255,255,0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = MAINWND_CLASS;

    RegisterClass(&wc);

	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, NULL);

	m_hWndParent = FindWindow(_T("HHTaskBar"), _T(""));

	if (m_bOptPPC2k2) {
		m_nWidth = DPI(32,64);
	} else {
		m_nWidth = DPI(82,164);
	}
	HWND hWnd = CreateWindowEx(NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_CHILD | WS_VISIBLE, 
		GetSystemMetrics(SM_CXSCREEN)-m_nWidth, DPI(TOP_OFFSET,(TOP_OFFSET) * 2), 
        DPI(82+25,(82+25)*2), DPI(26,52), 
		m_hWndParent, NULL, hInstance, NULL);

    Create2();

    return hWnd;
	
}

HWND CMainWnd::Create2() {

    WNDCLASSW wc;

    wc.style = 0 ;
    wc.lpfnWndProc = (WNDPROC) MainWndProc2;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;  
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH) GetStockObject(RGB(255,255,0));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = MAINWND_CLASS _T("2");

    RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(NULL, MAINWND_CLASS _T("2"), MAINWND_TITLE, 
		0, 
		0, 0, 
        10, 10, 
		NULL, NULL, m_hInstance, NULL);

	return hWnd;
	
}

LRESULT CALLBACK CMainWnd::MainWndProc2( HWND hWnd, UINT iMsg, 
				                         WPARAM wParam, LPARAM lParam) {

	switch (iMsg) {
    case WM_SETTINGCHANGE:
        m_pMainWnd->OnTimerClock(true);
    }

    return 0;
}

LRESULT CALLBACK CMainWnd::MainWndProc( HWND hWnd, UINT iMsg, 
										WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {

	case WM_CREATE :
		m_pMainWnd->m_hWnd = hWnd;
		return m_pMainWnd->OnCreate();

	case WM_CLOSE :
		return m_pMainWnd->OnClose();

	case WM_DESTROY :
		return m_pMainWnd->OnDestroy();

	case WM_USER_SYSTRAY :
		return m_pMainWnd->OnSysTray(lParam);

	case WM_USER_TRIGGER :
		if (m_pMainWnd->m_bMenuDown) {
			SendMessage(FindWindow(L"MNU", L""), WM_CANCELMODE, 0, 0);

			return 0;
		} else {
			m_pMainWnd->SafeSetForeground(m_pMainWnd->m_hWnd);
			return m_pMainWnd->OnSysTray(WM_LBUTTONDOWN);
		}

	case WM_COMMAND:
		return m_pMainWnd->OnCommand(LOWORD(wParam));

	case WM_MEASUREITEM:
		return m_pMainWnd->OnMeasureItem((UINT) wParam, (LPMEASUREITEMSTRUCT) lParam);

	case WM_DRAWITEM:
		return m_pMainWnd->OnDrawItem((UINT) wParam, (LPDRAWITEMSTRUCT) lParam);

	case WM_PAINT:
		return m_pMainWnd->OnPaint();

	case WM_LBUTTONDOWN:
		return m_pMainWnd->OnLButtonDown(LOWORD(lParam), HIWORD(lParam), wParam, lParam);

	case WM_LBUTTONUP:
		return m_pMainWnd->OnLButtonUp(LOWORD(lParam), HIWORD(lParam), wParam, lParam);

	case WM_MOUSEMOVE:
		return m_pMainWnd->OnMouseMove(LOWORD(lParam), HIWORD(lParam));

	case WM_TIMER:
		return m_pMainWnd->OnTimer(wParam);

    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE)
        {
            if (m_pMainWnd->m_bDisplayed)
            {
                m_pMainWnd->DestroyPopupLinks();
            }
        }
        break;
    case WM_CANCELMODE:
            if (m_pMainWnd->m_bDisplayed)
            {
                m_pMainWnd->DestroyPopupLinks();
            }
            break;
	}

    if (m_pMainWnd->m_bDisplayed)
    {
        TCHAR sz[100];
        _stprintf(sz, _T("Displayed: %08x %08x %08x"), iMsg, wParam, lParam);

        LM(sz, 0);
    }

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnMouseMove(int x, int y) {

	if (m_nTimerActive > 0) {
		DWORD nNow = GetTickCount();
		m_nTimerCheck += nNow - m_nTimerCheckStart;
		m_nTimerCheckStart = nNow;

	}

	if (!m_bOptOldStrokes) {
		if (abs(y-m_nIconY)*abs(y-m_nIconY) + abs(x-m_nIconX)*abs(x-m_nIconX) > DPI(400,800)) {
			m_nTimerActive = -1;
			DisplayPopupLinks();
		};
	}

	return 0;
}

void CMainWnd::DestroyPopupLinks() {
	if (m_bOptOldStrokes) {
		return;
	}
	if (!m_bDisplayed) {
		return;
	}

	m_bDisplayed = false;

	int i;
	for (i = 0; i < MAX_LINKS; i++) {
		DestroyWindow(m_hWndLinks[i]);
	}
}

void CMainWnd::DisplayPopupLinks() {
	if (m_bOptOldStrokes) {
		return;
	}
	if (m_bDisplayed) {
		return;
	}

	m_bDisplayed = true;

	HICON hiBorder = (HICON) LoadImage(m_hInstance, MAKEINTRESOURCE(IDI_BIG_BORDER), IMAGE_ICON, DPI(20,40), DPI(20,40), 0);

	int i;
	int x;
	int y;
	int nIcon;

	for (i = 0; i < MAX_LINKS; i++) {
		switch (i) {
		case 0:
			x = GetSystemMetrics(SM_CXSCREEN) - (DPI(240 - 142,(240 - 142) * 2)); y = DPI(26,52);
			nIcon = IDI_VOLUME;
			break;
		case 1:
			x = GetSystemMetrics(SM_CXSCREEN) - (DPI(240 - 157,(240 - 157) * 2)); y = DPI(49,98);
			nIcon = IDI_OPT_TASK;
			break;
		case 2:
			x = GetSystemMetrics(SM_CXSCREEN) - (DPI(240 - 182,(240 - 182) * 2)); y = DPI(60,120);
			nIcon = IDI_OPT_TODAY;
			break;
		case 3:
			x = GetSystemMetrics(SM_CXSCREEN) - (DPI(240 - 209,(240 - 209) * 2)); y = DPI(63,126);
			nIcon = IDI_MYCLOSE;
			break;
		}

		//handle the legacy support here
		if (m_bSmall) {
			y = (GetSystemMetrics(SM_CYSCREEN)-DPI(26,52))-y;
		}


		m_hWndLinks[i] = CreateWindowEx(
			WS_EX_TOPMOST, _T("STATIC"), NULL, 
			WS_VISIBLE, x, y, DPI(20,40), DPI(20,40),
			0, NULL, m_hInstance, NULL);

		HICON hIcon;
		HDC hDC;
		UpdateWindow(m_hWndLinks[i]);
		hIcon = (HICON) LoadImage(m_hInstance, MAKEINTRESOURCE(nIcon), IMAGE_ICON, DPI(16,32), DPI(16,32), 0);
		hDC = GetDC(m_hWndLinks[i]);
		DrawIconEx(hDC, 0, 0, hiBorder, DPI(20,40), DPI(20,40), 0, FALSE, DI_NORMAL);
		DrawIconEx(hDC, DPI(2,4), DPI(2,4), hIcon, DPI(16,32), DPI(16,32), 0, FALSE, DI_NORMAL);
		ReleaseDC(m_hWndLinks[i], hDC);
	}

}


LRESULT CMainWnd::OnTimer(WPARAM wID) {
	switch (wID) {
	case TIMER_CLOCK:
		OnTimerClock(false);
		break;
	case TIMER_TAPNHOLD:
		if (GetTickCount() >= m_nTimerCheck) {
			KillTimer(m_hWnd, TIMER_TAPNHOLD);
			int nPrivateActive = m_nTimerActive;

			m_nTimerActive = 0;
			m_bButtonDown = false;

			switch(nPrivateActive) {
			case 1: //hold events
				if (m_bOptTapNHold) {
					OnSysTray(WM_LBUTTONDOWN);
				}
				m_bButtonDown = false;
				break;
			case 2:
				if (m_bOptTapNHold) {
					OnSysTray(WM_LBUTTONDOWN);
				}
				m_bButtonDown = false;
				break;
			case 14:
			case 11: // tap, no double click
				m_nSelected = 2;
				InvalidateRect(m_hWnd, NULL, FALSE);
				UpdateWindow(m_hWnd);
				SafeSetForeground(FindWindow(MW_DESKCLASS, MW_DESKWIN));
				m_nSelected = 0;
				InvalidateRect(m_hWnd, NULL, FALSE);
				break;
			case 12: // Flip Windows (menusel)
				if (m_bOptTapNHold) {
					m_bNoCaptions = true;
					AppendWindows();
					m_bNoCaptions = false;
					if (m_cWindows > 1) {
						SetWindowPos(m_cwiEnums[1].hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
						SafeSetForeground(m_cwiEnums[2].hWnd);
					}

				} else {
					OnSysTray(WM_LBUTTONDOWN);
				}
				break;
			}
		}

		break;
	}
	return 0;
}

void CMainWnd::OnTimerClock(bool bForce) {
	static int nLast = -1;
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_hWndFore = GetForegroundWindow();
	bool bShouldShowOK = false;
	if (m_hWndFore) {
		DWORD dwExStyle = GetWindowLong(m_hWndFore, GWL_EXSTYLE);
		if (WS_EX_CAPTIONOKBTN & dwExStyle) {
			RECT rt;
			GetWindowRect(m_hWndFore, &rt);
			if (rt.top <= DPI(26,52) && rt.left <= 0 && 
				rt.right >= DPI(239,478) && rt.bottom >= DPI(94,188)) {
				bShouldShowOK = true;
			}
		}
	}

	bool bShouldDesktopVisible = false;
	//DWORD dwpidDesktop;
	//DWORD dwpidCompare;
	//GetWindowThreadProcessId(FindWindow(MW_DESKCLASS, MW_DESKWIN),&dwpidDesktop);
	//GetWindowThreadProcessId(GetForegroundWindow(), &dwpidCompare);
	//if (dwpidCompare == dwpidDesktop) {
    if (GetForegroundWindow() == FindWindow(MW_DESKCLASS, MW_DESKWIN)) {
		bShouldDesktopVisible = true;
	}


	RECT rt;
	GetWindowRect(m_hWndParent, &rt);
	bool bShouldSmall = false;
	if (rt.top != 0) {
		bShouldSmall = true;
	}
	bool bShouldPPC2k2 = m_bOptPPC2k2;
	if (bForce || (bShouldSmall != m_bSmall) || 
		((!m_bSmall) & (bShouldShowOK != m_bShowOK)) || 
		(m_bIsPPC2k2 != bShouldPPC2k2) ||
		(m_bIsPPC2k2 && (bShouldDesktopVisible != m_bDesktopVisible))) {
		m_bSmall = bShouldSmall;
		m_bIsPPC2k2 = false;
		nLast = -1;
		if (m_bSmall) {
			SetWindowPos(m_hWnd, 0, GetSystemMetrics(SM_CXSCREEN) - DPI(50,100), TOP_OFFSET, DPI(50,100), 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
			m_nWidth = DPI(50,100);
		} else {
			if (bShouldPPC2k2) {
				m_bIsPPC2k2 = bShouldPPC2k2;
				m_bShowOK = bShouldShowOK;
				m_nWidth = DPI(32,64);
				SetWindowPos(m_hWnd, 0, GetSystemMetrics(SM_CXSCREEN) - DPI(30,60), TOP_OFFSET, DPI(30,60), 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
				if (bShouldDesktopVisible != m_bDesktopVisible)
				{
					m_bDesktopVisible = bShouldDesktopVisible;
					InvalidateRect(m_hWnd, NULL, FALSE);
				}
			} else {
				if (bShouldShowOK) {
					m_bShowOK = bShouldShowOK;
					SetWindowPos(m_hWnd, 0, GetSystemMetrics(SM_CXSCREEN) - DPI(82-23,(82-23) * 2), TOP_OFFSET, DPI(82+23,(82+23) * 2), 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
					m_nWidth = DPI(82+23,(82+23) * 2);
				} else {
					m_bShowOK = bShouldShowOK;
					SetWindowPos(m_hWnd, 0, GetSystemMetrics(SM_CXSCREEN) - DPI(82,164), TOP_OFFSET, DPI(82,164), 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
					m_nWidth = DPI(82,164);
				}
			}
		}
	}

	if (nLast != st.wMinute) {
		nLast = st.wMinute;
		InvalidateRect(m_hWnd, NULL, FALSE);
#ifdef MY_POWER_CHECK
        bool bWhite = g_bWhite;
	    SYSTEM_POWER_STATUS_EX spse;
	    GetSystemPowerStatusEx(&spse, FALSE);

	    if (spse.ACLineStatus == AC_LINE_ONLINE &&
            spse.BatteryFlag != BATTERY_FLAG_CHARGING)
        {
            bWhite = true;
        }
        else
        {
            bWhite = false;
        }

        if (bWhite != g_bWhite)
        {
            g_bWhite = bWhite;
		    InvalidateRect(m_hWnd, NULL, FALSE);
        }
#endif
	}


}

LRESULT CMainWnd::OnCommand(WORD wID) {

	if (wID > menuFirstProgram) {
		bool bLeftSide = true;
		DWORD dwClick = GetMessagePos();

		if (LOWORD(dwClick) > (GetSystemMetrics(SM_CXSCREEN)-DPI(18,36))) {
			bLeftSide = false;
		}
		if (dwClick == m_dwLastPos) {
			bLeftSide = true;
		}
		m_dwLastPos = dwClick;

		if (bLeftSide) {
			SafeSetForeground(m_cwiEnums[wID - menuFirstProgram].hWnd);
		} else {

			if (CanClose(m_cwiEnums[wID - menuFirstProgram].hWnd)) {

				CloseRemoteWindow(m_cwiEnums[wID - menuFirstProgram].hWnd);
			}

		}

	} else {
		switch (wID) {
		case menuAbout:
			MessageBox(GetForegroundWindow(), _T("PocketNav  v") VERSION_TCHAR _T("\n\nCreated by Scott Seligman\n<scott@\n   scottandmichelle.net>\n(c) ") VERSION_YEAR_T,_T("About..."), MB_ICONINFORMATION | MB_TOPMOST);
			break;
		case menuOptHideIcons:
			m_bOptHideIcons = !m_bOptHideIcons;
			if (m_bOptHideIcons) {
				CheckMenuItem(m_hMenu, menuOptHideIcons, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptHideIcons, MF_BYCOMMAND | MF_UNCHECKED);
			}
			SaveSettings();
			break;

		case menuOptPPC2k2:
			m_bOptPPC2k2 = !m_bOptPPC2k2;
			if (m_bOptPPC2k2) {
				CheckMenuItem(m_hMenu, menuOptPPC2k2, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptPPC2k2, MF_BYCOMMAND | MF_UNCHECKED);
			}
			InvalidateRect(m_hWnd, NULL, FALSE);
			SaveSettings();
			break;

		case menuOptSpeed:
			{
				COptionsDlg dlg;
				dlg.m_pdwLongTime = &m_dwOptLongTime;
				dlg.m_pdwShortTime = &m_dwOptShortTime;
				dlg.Show(m_hWnd, m_hInstance);
				SaveSettings();
				OnTimer(TIMER_CLOCK);
			}
			break;
		case menuOptOldStrokes:
			m_bOptOldStrokes = !m_bOptOldStrokes;
			if (m_bOptOldStrokes) {
				CheckMenuItem(m_hMenu, menuOptOldStrokes, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptOldStrokes, MF_BYCOMMAND | MF_UNCHECKED);
			}
			SaveSettings();
			break;
		case menuOptSounds:
			m_bOptCloseSound = !m_bOptCloseSound;
			if (m_bOptCloseSound) {
				CheckMenuItem(m_hMenu, menuOptSounds, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptSounds, MF_BYCOMMAND | MF_UNCHECKED);
			}
			SaveSettings();
			break;
		case menuOptToday:
			if (m_bOptToday) {
				if (m_bOptTask || m_bOptCloseIcon) {
					m_bOptToday = false;
				}
			} else {
				if (m_bOptTask && m_bOptCloseIcon) {
					MessageBox(m_hWnd, L"Only two icons can be selected at once", L"Error", MB_TOPMOST);
					return 0;
				}
				m_bOptToday= true;
			}
			if (m_bOptToday) {
				CheckMenuItem(m_hMenu, menuOptToday, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptToday, MF_BYCOMMAND | MF_UNCHECKED);
			}
			InvalidateRect(m_hWnd, NULL, FALSE);
			SaveSettings();
			break;
		case menuOptTask:
			if (m_bOptTask) {
				if (m_bOptToday || m_bOptCloseIcon) {
					m_bOptTask = false;
				}
			} else {
				if (m_bOptToday && m_bOptCloseIcon) {
					MessageBox(m_hWnd, L"Only two icons can be selected at once", L"Error", MB_TOPMOST);
					return 0;
				}
				m_bOptTask = true;
			}
			if (m_bOptTask) {
				CheckMenuItem(m_hMenu, menuOptTask, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptTask, MF_BYCOMMAND | MF_UNCHECKED);
			}
			InvalidateRect(m_hWnd, NULL, FALSE);
			SaveSettings();
			break;
		case menuOptCloseIcon:
			if (m_bOptCloseIcon) {
				if (m_bOptTask || m_bOptCloseIcon) {
					m_bOptCloseIcon = false;
				}
			} else {
				if (m_bOptToday && m_bOptTask) {
					MessageBox(m_hWnd, L"Only two icons can be selected at once", L"Error", MB_TOPMOST);
					return 0;
				}
				m_bOptCloseIcon = true;
			}
			if (m_bOptCloseIcon) {
				CheckMenuItem(m_hMenu, menuOptCloseIcon, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptCloseIcon, MF_BYCOMMAND | MF_UNCHECKED);
			}
			InvalidateRect(m_hWnd, NULL, FALSE);
			SaveSettings();
			break;
		case menuOptIconBorder:
			m_bOptIconBorder = !m_bOptIconBorder;
			if (m_bOptIconBorder) {
				CheckMenuItem(m_hMenu, menuOptIconBorder, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptIconBorder, MF_BYCOMMAND | MF_UNCHECKED);
			}
			InvalidateRect(m_hWnd, NULL, FALSE);
			SaveSettings();
			break;

		case menuOptTapNHold:
			m_bOptTapNHold = !m_bOptTapNHold;
			if (m_bOptTapNHold) {
				CheckMenuItem(m_hMenu, menuOptTapNHold, MF_BYCOMMAND | MF_CHECKED);
			} else {
				CheckMenuItem(m_hMenu, menuOptTapNHold, MF_BYCOMMAND | MF_UNCHECKED);
			}
			SaveSettings();
			break;

		case menuCloseSelf:
			PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			break;

		case menuCloseAll:
			CloseAll(false);
			SafeSetForeground(FindWindow(MW_DESKCLASS, MW_DESKWIN));
			break;

		case menuCloseAllButTop:
			CloseAll(true);
			break;

		}
	}

	return 0;
}

void CMainWnd::CloseAll(bool bButActive) {

	int i = 0;
	int nStart;
	if (bButActive) {
		nStart = 2;
	} else {
		nStart = 1;
	}
	for (i = nStart; i <= m_cWindows; i ++) {
		if (CanClose(m_cwiEnums[i].hWnd)) {
			CloseRemoteWindow(m_cwiEnums[i].hWnd);
		}
	}


}

void CMainWnd::CloseRemoteWindow(HWND hWnd) {
	ShowWindow(hWnd, FALSE);
	SafeSetForeground(hWnd);
	
	keybd_event(VK_CONTROL, 0, KEYEVENTF_SILENT, 0);
	keybd_event('Q', 0, KEYEVENTF_SILENT, 0);
	keybd_event('Q', 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_SILENT | KEYEVENTF_KEYUP, 0);

	PostMessage(hWnd, WM_CLOSE, 0, 0);
}

LRESULT CMainWnd::OnSysTray(DWORD dwID) {

	if (m_bEnumActive) {
		return 0;
	}

	if (dwID == WM_LBUTTONDOWN) {

		m_nSelected = 1;
		InvalidateRect(m_hWnd, NULL, FALSE);
		UpdateWindow(m_hWnd);

		RECT rect;
		SystemParametersInfo(SPI_GETWORKAREA, NULL, &rect, NULL);

		AppendWindows();

		SafeSetForeground(m_hWnd);

		rect.top = DPI(26,52);
		rect.bottom = DPI(320 - 26,(320 - 26) * 2);

		EnableMenuItem(m_hMenu, menuOptToday, (m_bOptPPC2k2?TRUE:FALSE));
		EnableMenuItem(m_hMenu, menuOptTask, (m_bOptPPC2k2?TRUE:FALSE));
		EnableMenuItem(m_hMenu, menuOptCloseIcon, (m_bOptPPC2k2?TRUE:FALSE));
		if (m_bSmall) {
			m_bMenuDown = true;
			TrackPopupMenuEx(m_hMenu, 
				TPM_LEFTALIGN | TPM_BOTTOMALIGN, 
				rect.right, 
				rect.bottom, 
				m_hWnd, 
				NULL);
			if (m_hMenu != NULL) {
				CleanUpMenu();
			}
		} else {
			m_bMenuDown = true;
			TrackPopupMenuEx(m_hMenu, 
				TPM_LEFTALIGN | TPM_TOPALIGN, 
				rect.right, 
				rect.top, 
				m_hWnd, 
				NULL);
			if (m_hMenu != NULL) {
				CleanUpMenu();
			}
		}
	}

	return 0;
}

void CMainWnd::CleanUpMenu() {
	m_bMenuDown = false;

	m_nSelected = 0;
	InvalidateRect(m_hWnd, NULL, FALSE);

	for (int i = 1; i <= m_cWindows; i ++) {
		if (m_hMenu != NULL) {
			DeleteMenu(m_hMenu, 0, MF_BYPOSITION);
		}
		free (m_cwiEnums[i].szCaption);
	}

	if (m_hMenu == NULL) {
		m_pMainWnd->CreateMainMenu();
	}

	m_bEnumActive = false;
}



LRESULT CMainWnd::OnClose() {

	DestroyWindow(m_hWnd);

	return 0;

}

LRESULT CMainWnd::OnDestroy() {

	PostQuitMessage(0);

	return 0;
}

#include "shlobj.h"

LRESULT CMainWnd::OnCreate() {

	LoadSettings();

	SetTimer(m_hWnd, TIMER_CLOCK, 500, 0);

	CreateMainMenu();

	return 0;
}

void CMainWnd::CreateMainMenu() {
	m_hMenu = CreatePopupMenu();

	AppendMenu(m_hMenu, MF_SEPARATOR, menuSep01, 0);
	AppendMenu(m_hMenu,	MF_STRING, menuCloseAll, _T("Close All"));
	AppendMenu(m_hMenu,	MF_STRING, menuCloseAllButTop, _T("Close All But Active"));
	AppendMenu(m_hMenu, MF_SEPARATOR, menuSep02, 0);

	HMENU hMenuTemp = CreatePopupMenu();
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptToday?MF_CHECKED:0), menuOptToday, _T("Today Icon"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptTask?MF_CHECKED:0), menuOptTask, _T("Tasks Icon"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptCloseIcon?MF_CHECKED:0), menuOptCloseIcon, _T("Close Icon"));

	bool bPPC2k2 = false;

	OSVERSIONINFO osvi = {0};
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if (osvi.dwMajorVersion > 3) {
		bPPC2k2 = true;
	} else if (osvi.dwMinorVersion > 0) {
		bPPC2k2 = true;
	} else if (osvi.dwBuildNumber >= 11171) {
		bPPC2k2 = true;
	} else {
		bPPC2k2 = false;
	}
#ifdef DEBUG
	bPPC2k2 = true;
#endif

	if (bPPC2k2) {
		AppendMenu(hMenuTemp, MF_STRING | (m_bOptPPC2k2?MF_CHECKED:0), menuOptPPC2k2, _T("PocketPC 2002 UI"));
	}

//	/* - */ AppendMenu(hMenuTemp, MF_STRING | (m_bOptTask?MF_CHECKED:0), menuOptBattery, _T("Battery Icon"));
//	/* - */ AppendMenu(hMenuTemp, MF_STRING | (m_bOptTask?MF_CHECKED:0), menuOptSound, _T("Sound Icon"));
	AppendMenu(hMenuTemp, MF_SEPARATOR, menuSep03, 0);
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptTapNHold?MF_CHECKED:0), menuOptTapNHold, _T("Tap and Hold"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptCloseSound?MF_CHECKED:0), menuOptSounds, _T("Sound on Close"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptIconBorder?MF_CHECKED:0), menuOptIconBorder, _T("Icon Backdrops"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptOldStrokes?MF_CHECKED:0), menuOptOldStrokes, _T("Single Action Strokes"));
	AppendMenu(hMenuTemp, MF_STRING | (m_bOptHideIcons?MF_CHECKED:0), menuOptHideIcons, _T("Hide program icons"));
	AppendMenu(hMenuTemp, MF_SEPARATOR, menuSep04, 0);
	AppendMenu(hMenuTemp, MF_STRING, menuOptSpeed, _T("Set Click Speed..."));
//	/* - */ AppendMenu(hMenuTemp, MF_STRING, menuOptOrder, _T("Set Icon Placement..."));
	AppendMenu(hMenuTemp, MF_SEPARATOR, menuSep05, 0);
	AppendMenu(hMenuTemp, MF_STRING, menuAbout, _T("About..."));

	AppendMenu(m_hMenu,	MF_STRING | MF_POPUP, (UINT) hMenuTemp, _T("Options"));
	AppendMenu(m_hMenu,	MF_STRING, menuCloseSelf, _T("Exit PocketNav"));
}

void CMainWnd::AddWindow(LPTSTR szCaption) {

	m_cWindows ++;

	if (m_bNoCaptions) {

		m_cwiEnums[m_cWindows].szCaption = NULL;

	} else {

		if (_tcscmp(szCaption, MW_DESKWIN) == 0) {
			szCaption = MW_DESKWIN2;
		} 

		m_cwiEnums[m_cWindows].szCaption = (LPTSTR) malloc (256 * sizeof(TCHAR));

		_tcscpy(m_cwiEnums[m_cWindows].szCaption, szCaption);

		InsertMenu(m_hMenu, 
			menuSep01, 
			MF_BYCOMMAND | MF_STRING | MF_OWNERDRAW, 
			menuFirstProgram + m_cWindows, 
			m_cwiEnums[m_cWindows].szCaption
            
            );

	}

}

void CMainWnd::AppendWindows() {

	if (m_bEnumActive) {
		return;
	}

	m_cWindows = 0;
	m_bEnumActive = true;

	m_dwpidLastEnumInstance = NULL;
	LM(L"-------- Beginning enum", 0);
	EnumWindows((WNDENUMPROC) EnumWindowsProc, (long) this);
	LM(L"------- End of enum", 0);

	if (m_bNoCaptions) {
		m_bEnumActive = false;
	}

}

BOOL CMainWnd::EnumWindowsProc(HWND hWnd, DWORD lParam) {
	LM(L"Called into enum windows proc", 0);
	LM(L"Window check", hWnd);

	CMainWnd * parent = (CMainWnd *) lParam;

	DWORD dwpidCurrent;
	GetWindowThreadProcessId(hWnd, &dwpidCurrent);

	bool bAdd = true;
	if (IsWindow(hWnd) && 
		IsWindowVisible(hWnd)) {

		int iLength = GetWindowTextLength(hWnd);

		if (iLength > 0) {

			LPTSTR szCaption = (LPTSTR) malloc(sizeof(TCHAR) * (iLength+2));
			GetWindowText(hWnd, szCaption, iLength+1);

			if (parent->m_dwpidLastEnumInstance == dwpidCurrent) {
				//see if it's the same caption
				if (parent->m_cWindows >= 1) {
					if (parent->m_szLastCaption) {
						if (_tcscmp(parent->m_szLastCaption, szCaption) == 0) {
							bAdd = false;
						}
					}
				}
			}

			if (_tcscmp(_T("Internet Explorer"), szCaption) == 0) {
				//tap right nonsense
				// how long till the international community complains?
				bAdd = true;
			}


			if (bAdd) {
				if ((lstrcmp(szCaption, L"CursorWindow") != 0) &&
					(lstrcmp(szCaption, L"Pocket PC Emulation") != 0) &&
					(lstrcmp(szCaption, L"MS_SIPBUTTON") != 0)) {

					LM(L"This is a good window", 0);
					parent->m_dwpidLastEnumInstance = dwpidCurrent;

					parent->AddWindow(szCaption);
					parent->m_cwiEnums[parent->m_cWindows].hWnd = hWnd;
				}
			}

			if (parent->m_szLastCaption) {
				free(parent->m_szLastCaption);
			}
			parent->m_szLastCaption = szCaption;
		}

	}

	if (parent->m_cWindows > MAX_WINDOWS) {
		LM(L"Too many windows", 0);
		return false;
	} else {
		LM(L"Done with enum, next", 0);
		return true;
	}

}

LRESULT CMainWnd::OnMeasureItem(UINT idCtl, LPMEASUREITEMSTRUCT lpmis) {


	HDC hdc;
	hdc = GetDC(m_hWnd);
	SIZE t;
	//LOGFONT lf;

	//GetObject(GetStockObject(SYSTEM_FONT), sizeof(lf), &lf);
	//lf.lfWeight = FW_BOLD;

	HFONT hfont;
	if (_tcscmp(m_cwiEnums[lpmis->itemID - menuFirstProgram].szCaption, MW_DESKWIN2) == 0) {
//		lf.lfItalic = TRUE;
		hfont = CreateMenuFont(TRUE, hdc);
	} else {
		hfont = CreateMenuFont(FALSE, hdc);
	}

	HFONT hfontOld = (HFONT) SelectObject(hdc, hfont);

	GetTextExtentPoint32(hdc, m_cwiEnums[lpmis->itemID - menuFirstProgram].szCaption, 
		_tcslen(m_cwiEnums[lpmis->itemID - menuFirstProgram].szCaption), &t);

	lpmis->itemWidth = DPI(16,32) + t.cx + DPI(10,20) + DPI(20,40);
	lpmis->itemHeight = (DPI(16,32)>t.cy ? DPI(16,32) : t.cy) + DPI(2,4);

    SelectObject(hdc, hfontOld);
	DeleteObject(hfont);

	ReleaseDC(m_hWnd, hdc);

    return 0;
}

LRESULT CMainWnd::OnDrawItem(UINT idCtl, LPDRAWITEMSTRUCT lpdis) {
	HICON hiconWin = NULL;

	RECT rect;
	HPEN hpen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_MENU));
	HPEN hpenOld = (HPEN) SelectObject(lpdis->hDC, hpen);

	CopyRect(&rect, &lpdis->rcItem);

	Rectangle(lpdis->hDC, 
		lpdis->rcItem.left,
		lpdis->rcItem.top,
		lpdis->rcItem.right,
		lpdis->rcItem.bottom);

	rect.left += DPI(2,4);
	rect.top += DPI(2,4);

	bool bLoadedIcon = false;


	if (!m_bOptHideIcons) {
		if (_tcscmp(
			m_cwiEnums[lpdis->itemID - menuFirstProgram].szCaption, 
			MW_DESKWIN2) != 0) {

			hiconWin = (HICON) GetClassLong(m_cwiEnums[lpdis->itemID - 
				menuFirstProgram].hWnd, GCL_HICON);

			if (hiconWin == NULL) {
				bLoadedIcon = true;
				DWORD dwProcessID;

				GetWindowThreadProcessId(
					m_cwiEnums[lpdis->itemID - menuFirstProgram].hWnd, 
					&dwProcessID);

				LPTSTR szEXE = (LPTSTR) malloc (512 * sizeof(TCHAR));

				GetModuleFileName((HINSTANCE) dwProcessID, szEXE, 512);
				ExtractIconEx(szEXE, 0, NULL, &hiconWin, 1);

				free (szEXE);
			}

		}
	}

	HBITMAP hbClose;
	if (lpdis->itemState & ODS_SELECTED) {
		HBRUSH	hb = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		HPEN	hp = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_HIGHLIGHT));
		HBRUSH	hbOld = (HBRUSH) SelectObject(lpdis->hDC, hb);
		HPEN	hpOld = (HPEN) SelectObject(lpdis->hDC, hp);

		Rectangle(lpdis->hDC, lpdis->rcItem.left, lpdis->rcItem.top,
			lpdis->rcItem.right, lpdis->rcItem.bottom);

		SelectObject(lpdis->hDC, hbOld);
		SelectObject(lpdis->hDC, hpOld);
		DeleteObject(hp);
		DeleteObject(hb);
		hbClose = m_hbCloseSel;
	} else {
		hbClose = m_hbClose;
	}

	if (hiconWin != NULL) {
		DrawIconEx(lpdis->hDC, rect.left, rect.top,
			hiconWin, 
			DPI(16,32), DPI(16,32), 0, NULL, DI_NORMAL);
	}

	
	if (CanClose(m_cwiEnums[lpdis->itemID - menuFirstProgram].hWnd)) {

		HDC hdcClose = CreateCompatibleDC(lpdis->hDC);
		HBITMAP hbCloseOld = (HBITMAP) SelectObject(hdcClose, hbClose);
		

		BitBlt(lpdis->hDC, rect.right - DPI(18,36), rect.top, DPI(16,32), DPI(16,32), hdcClose, 0, 0, SRCCOPY);

		SelectObject(hdcClose, hbCloseOld);
		DeleteDC(hdcClose);

	}

	if (bLoadedIcon) {
		DeleteObject(hiconWin);
	}

	rect.left += DPI(16,32) + DPI(4,8);

	//LOGFONT lf;

	//GetObject(GetStockObject(SYSTEM_FONT), sizeof(lf), &lf);
	//lf.lfWeight = FW_BOLD;

	HFONT hfont;
	if (_tcscmp(
		m_cwiEnums[lpdis->itemID - menuFirstProgram].szCaption, 
		MW_DESKWIN2) == 0) {

		hfont = CreateMenuFont(TRUE, lpdis->hDC);
		//lf.lfItalic = TRUE;

	} else {
		hfont = CreateMenuFont(FALSE, lpdis->hDC);
	}

	//HFONT hfont = CreateFontIndirect(&lf);
	HFONT hfontOld = (HFONT) SelectObject(lpdis->hDC, hfont);

	SetBkMode(lpdis->hDC, TRANSPARENT);
	if (lpdis->itemState & ODS_SELECTED) {
		SetTextColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	} else {
		SetTextColor(lpdis->hDC, GetSysColor(COLOR_MENUTEXT));
	}

	DrawText(
		lpdis->hDC, 
		m_cwiEnums[lpdis->itemID - menuFirstProgram].szCaption, 
		_tcslen(m_cwiEnums[lpdis->itemID - menuFirstProgram].szCaption), 
		&rect, 
		DT_LEFT | DT_NOPREFIX);

	SelectObject(lpdis->hDC, hfontOld);
	SelectObject(lpdis->hDC, hpenOld);
	DeleteObject(hfont);
	DeleteObject(hpen);

	return 0;
}

void CMainWnd::SafeSetForeground(HWND hWnd)
{
    if (hWnd == FindWindow(MW_DESKCLASS, MW_DESKWIN))
    {
        SetForegroundWindow(hWnd);
        SetForegroundWindow(hWnd);
        InvalidateRect(hWnd, NULL, FALSE);
    }
    else
    {
        SetForegroundWindow(hWnd);
    }
}