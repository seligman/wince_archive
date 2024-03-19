#include <windows.h>
#include "main.h"
#include <aygshell.h>
#include <sip.h>
#include <keybd.h>
#include "Movement.h"
#include "resource.h"

#include "MainWnd.h"

CMainWnd::CMainWnd() {
    MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) this, NULL);
	m_nCells = 0;
	m_nLastTrigger = 0;
	m_hInstance = 0;
	m_hWnd = 0;
	m_hbBuffer = 0;
	m_hdcBuffer = 0;
	m_pIMCallback = NULL;
	m_modeCur = mNrm;
	m_bLocked = false;
	m_bKeyAbort = false;

}

CMainWnd::~CMainWnd() {
    MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) NULL, NULL);
}

LRESULT CALLBACK CMainWnd::MainWndProc ( HWND hWnd, UINT iMsg, 
   WPARAM wParam, LPARAM lParam) {

    static CMainWnd * parent = (CMainWnd *) NULL;

    if (iMsg == WM_USER_OBJECT) {
        parent = (CMainWnd *) wParam;
        return 0;
    } else if ( parent != NULL ) {
        switch (iMsg) {

        case WM_CREATE :
            parent->m_hWnd = hWnd;
            return parent->OnCreate();

        case WM_CLOSE :
            return parent->OnClose();

        case WM_DESTROY :
            return parent->OnDestroy();

		case WM_PAINT :
			return parent->OnPaint(wParam, lParam);

		case WM_USER_GETINFO:
			return parent->OnUserGetInfo(wParam,lParam);

		case WM_MOUSEMOVE:
			return parent->OnMouseMove(LOWORD(lParam), HIWORD(lParam));

		case WM_LBUTTONDOWN:
			return parent->OnLButtonDown(LOWORD(lParam), HIWORD(lParam));

		case WM_LBUTTONUP:
			return parent->OnLButtonUp();

        }
    }


    return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnClose() {

    DestroyWindow(m_hWnd);

    return 0;

}

LRESULT CMainWnd::OnDestroy() {

	delete m_pMovement;
    return 0;
}

LRESULT CMainWnd::OnCreate() {

	m_pMovement = new CMovement;
	m_pMovement->Init(this);

    GetWindowRect (GetParent (m_hWnd), &m_rectDocked);

    return 0;
}

void CMainWnd::SetHwnd(HWND hWnd) {
	m_hWnd = hWnd;
}

void CMainWnd::SetHinstance(HINSTANCE hInstance) {
	m_hInstance = hInstance;
}

LRESULT CMainWnd::OnUserGetInfo(WPARAM wParam, LPARAM lParam) {
    RECT rect;
	
    switch (wParam) {
    case 0:
        m_pIMCallback = (IIMCallback *)lParam;
        break;
    case 1:
        m_imi = *(IMINFO *)lParam;
        break;
    case 2: // Called when ReceiveSipInfo method called
        GetClientRect (GetParent(m_hWnd), &rect);
        MoveWindow (m_hWnd, 0, 0, rect.right - rect.left,
                    rect.bottom - rect.top, TRUE);
        break;
    }
    return 0;
}

void CMainWnd::DrawInBitmap(HDC hDCTemp, DWORD nOffset, DWORD rsrc, DWORD x, DWORD y, DWORD cx, DWORD cy, DWORD sx = 0, DWORD sy = 0) {

	HDC hDCBuffer;
	HBITMAP hBitmap, hBitmapOld;
	hBitmap = LoadBitmap(m_hInstance, MAKEINTRESOURCE(rsrc));

	hDCBuffer = CreateCompatibleDC(hDCTemp);
	hBitmapOld = (HBITMAP) SelectObject(hDCBuffer, hBitmap);

	if (nOffset == 2) {
		x += 80;
	}

	BitBlt(m_hdcBuffer, x, y, cx, cy, hDCBuffer, sx, sy, SRCCOPY);

	SelectObject(hDCBuffer, hBitmapOld);
	DeleteDC(hDCBuffer);
	DeleteObject(hBitmap);
}

LRESULT CMainWnd::OnPaint(WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(m_hWnd, &ps);
	HDC hDCTemp = GetDC(m_hWnd);

	if (!m_hdcBuffer) {
		HDC hdcTempForBuffer;
		hdcTempForBuffer = GetDC(0);
		m_hdcBuffer = CreateCompatibleDC(hdcTempForBuffer);
		m_hbBuffer = CreateCompatibleBitmap(hdcTempForBuffer, 240,80);
		SelectObject(m_hdcBuffer, m_hbBuffer);
		ReleaseDC(0, hdcTempForBuffer);
	}

	DrawInBitmap(hDCTemp, 2, IDB_MIDDLE, 53, 10, 52, 60);
	if (m_bLocked) {
		switch (m_modeCur) {
		case mAlt:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_ALT_LOCKED_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_ALT_LOCKED_2, 53, 70, 52, 10);
			break;
		case mNum:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NUM_LOCKED_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NUM_LOCKED_2, 53, 70, 52, 10);
			break;
		case mCap:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_CAP_LOCKED_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_CAP_LOCKED_2, 53, 70, 52, 10);
			break;
		default:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NRM_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NRM_2, 53, 70, 52, 10);
			break;
		}
	} else {
		switch (m_modeCur) {
		case mAlt:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_ALT_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_ALT_2, 53, 70, 52, 10);
			break;
		case mNum:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NUM_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NUM_2, 53, 70, 52, 10);
			break;
		case mCap:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_CAP_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_CAP_2, 53, 70, 52, 10);
			break;
		default:
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NRM_1, 53, 0, 52, 10);
			DrawInBitmap(hDCTemp, 2, IDB_STATE_NRM_2, 53, 70, 52, 10);
			break;
		}
	}

	switch (m_modeCur) {
	case mAlt:
		DrawInBitmap(hDCTemp, 2, IDB_KEY_ALT_1, 0, 0, 53, 80);
		DrawInBitmap(hDCTemp, 2, IDB_KEY_ALT_2, 105, 0, 55, 80);
		break;
	case mNum:
		DrawInBitmap(hDCTemp, 2, IDB_KEY_NUM_1, 0, 0, 53, 80);
		DrawInBitmap(hDCTemp, 2, IDB_KEY_NUM_2, 105, 0, 55, 80);
		break;
	case mCap:
		DrawInBitmap(hDCTemp, 2, IDB_KEY_CAP_1, 0, 0, 53, 80);
		DrawInBitmap(hDCTemp, 2, IDB_KEY_CAP_2, 105, 0, 55, 80);
		break;
	default:
		DrawInBitmap(hDCTemp, 2, IDB_KEY_NRM_1, 0, 0, 53, 80);
		DrawInBitmap(hDCTemp, 2, IDB_KEY_NRM_2, 105, 0, 55, 80);
		break;
	}

	// for now
	DrawInBitmap(hDCTemp, 1, IDB_KEYPAD, 0, 0, 80, 80);

	switch (m_nLastTrigger) {
	case 20:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,0, 0, 40, 19,0,0);
		break;
	case 21:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,40, 0, 40, 19,40, 0);
		break;
	case 22:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,0, 19, 20, 20,0, 19);
		break;
	case 23:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,20, 19, 20, 20,20, 19);
		break;
	case 24:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,40, 19, 20, 20,40, 19);
		break;
	case 25:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,60, 19, 20, 59,60, 19);
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,40, 58, 40, 20,40, 58);
		break;
	case 26:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,0, 39, 20, 19,0, 39);
		break;
	case 27:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,20, 39, 20, 19,20, 39);
		break;
	case 28:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,40, 39, 20, 19,40, 39);
		break;
	case 29:
		DrawInBitmap(hDCTemp,1,IDB_KEYPAD_DOWN,0, 58, 40, 20,0, 58);
		break;
	}

	BitBlt(hDC, 0, 0, 240, 80, m_hdcBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hDCTemp);
	EndPaint(m_hWnd, &ps);
	return 0;
}

void CMainWnd::CharEntered(TypeEnum nType, TCHAR sChar) { 

	TCHAR	szChar[2];
	DWORD	dwTemp = 0;
	INT		nChar = 0;

	switch (nType) {
		case tSpace:
			sChar = _T(' ');
			//fall through
		case tChar:
			szChar[0] = sChar;
			szChar[1] = 0;
			m_pIMCallback->SendString((TCHAR *) &szChar, 1);
			break;
		case tEnter:
			nChar = VK_RETURN;
			m_pIMCallback->SendCharEvents(VK_RETURN, KeyStateDownFlag, 1, 
				(unsigned int *) &dwTemp,(unsigned int *) &nChar);
			break;
		case tBackSpace:
			nChar = VK_BACK;
			m_pIMCallback->SendCharEvents(VK_BACK, KeyStateDownFlag, 1, 
				(unsigned int *) &dwTemp,(unsigned int *) &nChar);
			break;
	}

};

void CMainWnd::NewMode(ModeEnum nMode, bool bLock) { 

	m_modeCur = nMode;
	m_bLocked = bLock;

	if (m_hWnd) {
		RECT rect;
		GetClientRect (m_hWnd, &rect);
		InvalidateRect (m_hWnd,&rect,FALSE);
	}

};

LRESULT CMainWnd::OnMouseMove(WORD x1, WORD y1) {
	if (!m_nCells) {
		HRSRC hResource = FindResource(m_hInstance, MAKEINTRESOURCE(IDR_CELLS), L"CELLS");
		HGLOBAL hResData = LoadResource(m_hInstance, hResource);
		m_nCells = (__int8 *) LockResource(hResData);

	}

	POINT pt[100];
	UINT  cpt = 0;
	UINT  i;
	GetMouseMovePoints(pt, 100, &cpt);
	for (i = 0; i < cpt; i++) {
		x1 = (WORD) (pt[i].x/4 - m_rectDocked.left);
		y1 = (WORD) (pt[i].y/4 - m_rectDocked.top);

		signed int x = x1;
		signed int y = y1;

		x -= 80;

		if (x < -80) { x = -80; }
		if (y < 0) { y = 0; }
		if (x > 159) { x = 159; }
		if (y > 79) { y = 79; }

		__int8 nCell = m_nCells[(y*160)+x];

		int nLastLast = m_nLastTrigger;

		m_nLastTrigger = 0;
		if (x >= 0) {
			if (nCell < 9) {
				m_pMovement->IntoPosition(nCell);
				m_nLastTrigger = 0;
			}
		} else {
			x += 80;
			nCell = x/20;
			if (y >= 0 && y < 19) {
				// nothing
			} else if (y >= 19 && y < 39) {
				nCell += 4;
			} else if (y >= 39 && y < 58) {
				nCell += 8;
			} else if (y >= 58 && y < 80) {
				nCell += 12;
			}

			switch (nCell) {
			case  0: m_nLastTrigger = 20; break;
			case  1: m_nLastTrigger = 20; break;
			case  2: m_nLastTrigger = 21; break;
			case  3: m_nLastTrigger = 21; break;
			case  4: m_nLastTrigger = 22; break;
			case  5: m_nLastTrigger = 23; break;
			case  6: m_nLastTrigger = 24; break;
			case  7: m_nLastTrigger = 25; break;
			case  8: m_nLastTrigger = 26; break;
			case  9: m_nLastTrigger = 27; break;
			case 10: m_nLastTrigger = 28; break;
			case 11: m_nLastTrigger = 25; break;
			case 12: m_nLastTrigger = 29; break;
			case 13: m_nLastTrigger = 29; break;
			case 14: m_nLastTrigger = 25; break;
			case 15: m_nLastTrigger = 25; break;
			}
		}

		
		if (nLastLast != m_nLastTrigger) {
			if (m_bKeyAbort) {
				m_nLastTrigger = 0;
			} else {
				m_bKeyAbort = true;
			}
			InvalidateRect(m_hWnd,NULL,FALSE);
			UpdateWindow(m_hWnd);
		}

	}

	return 0;
}

LRESULT CMainWnd::OnLButtonDown(WORD x1, WORD y1) {

	m_pMovement->Reset();

	SetCapture(m_hWnd);

	OnMouseMove(x1,y1);

	return 0;
}

LRESULT CMainWnd::OnLButtonUp() {
	ReleaseCapture();

	m_bKeyAbort = false;
	DWORD	dwTemp = 0;
	DWORD	dwTemp2 = 0;
	DWORD	nChar = 0;

	switch (m_nLastTrigger) {
	case 20:
		nChar = VK_TAB;
		m_pIMCallback->SendCharEvents(nChar, KeyStateDownFlag, 1, (unsigned int *) &dwTemp,(unsigned int *) &nChar);
		break;
	case 21:
		nChar = VK_BACK;
		m_pIMCallback->SendCharEvents(nChar, KeyStateDownFlag, 1, (unsigned int *) &dwTemp,(unsigned int *) &nChar);
		break;
	case 22:
		m_pIMCallback->SendCharEvents(VK_ESCAPE, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 23:
		m_pIMCallback->SendCharEvents(VK_UP, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 24:
		m_pIMCallback->SendCharEvents(VK_DELETE, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 25:
		nChar = VK_RETURN;
		m_pIMCallback->SendCharEvents(nChar, KeyStateDownFlag, 1, (unsigned int *) &dwTemp,(unsigned int *) &nChar);
		break;
	case 26:
		m_pIMCallback->SendCharEvents(VK_LEFT, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 27:
		m_pIMCallback->SendCharEvents(VK_DOWN, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 28:
		m_pIMCallback->SendCharEvents(VK_RIGHT, KeyStateDownFlag, 0, (LPUINT) &dwTemp, (LPUINT) &nChar);
		break;
	case 29:
		nChar = VK_SPACE;
		m_pIMCallback->SendCharEvents(nChar, KeyStateDownFlag, 1, (unsigned int *) &dwTemp,(unsigned int *) &nChar);
		break;
	}

	m_nLastTrigger = 0;
	InvalidateRect(m_hWnd,NULL,FALSE);

	return 0;
}