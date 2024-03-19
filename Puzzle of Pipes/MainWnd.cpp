#include "main.h"

#include "Pipe.h"
#include "HighScore.h"
#include "Grid.h"
#include "Score.h"
#include "resource.h"

#include "MainWnd.h"

CMainWnd::CMainWnd() {
	MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) this, NULL);
	srand(GetTickCount());

	m_bKeyDown = false;

	m_hPenBlue = CreatePen(PS_SOLID,1,RGB(0,0,255));
	m_hBrushBlue = CreateSolidBrush(RGB(0,0,255));

	m_Grid.SetScore(&m_Score);
	m_Score.SetMainWnd(this);
	m_Grid.ResetGrid();

	m_bMouseDown = false;
	m_bTimerActive = false;
}

CMainWnd::~CMainWnd() {
	MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) NULL, NULL);

	DeleteObject(SelectObject(m_hdcBuffer, m_hbBufferOld));
	DeleteDC(m_hdcBuffer);

	DeleteObject(m_hPenBlue);
	DeleteObject(m_hBrushBlue);
}

BOOL CMainWnd::PrevInst() {
	m_hMutex = CreateMutex(NULL, TRUE, MAINWND_GUID);

	return (GetLastError() == ERROR_ALREADY_EXISTS);
}

HWND CMainWnd::Create(HINSTANCE hInstance) {

	HWND		hWnd;
	WNDCLASS	wndclass;

	m_hInstance = hInstance;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
#ifdef UNDER_CE
	wndclass.hCursor = NULL;
#else
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
#endif
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = MAINWND_CLASS;

	RegisterClass ( &wndclass );

#ifdef UNDER_CE
	hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
#ifdef POCKET_PC
		WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, MAINWND_X, MAINWND_Y, 
#else
		WS_VISIBLE, 0, 0, MAINWND_X, MAINWND_Y, 
#endif
		NULL, NULL, hInstance, NULL);
#else
	hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
		CW_USEDEFAULT, CW_USEDEFAULT, MAINWND_X, MAINWND_Y, 
		NULL, NULL, hInstance, NULL);
#endif

	return hWnd;
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
			return parent->OnPaint((HDC) wParam);

		case WM_LBUTTONDOWN :
			return parent->OnLButtonDown(wParam, (int) LOWORD(lParam), (int) HIWORD(lParam));

		case WM_LBUTTONUP :
			return parent->OnLButtonUp(wParam, (int) LOWORD(lParam), (int) HIWORD(lParam));

		case WM_MOUSEMOVE :
			return parent->OnMouseMove(wParam, (int) LOWORD(lParam), (int) HIWORD(lParam));

		case WM_TIMER :
			return parent->OnTimer(wParam);

		case WM_KEYDOWN :
			return parent->OnKeyDown((int) wParam, lParam);

		case WM_KEYUP :
			return parent->OnKeyUp((int) wParam, lParam);

		case WM_ACTIVATE :
			return parent->OnActivateApp(LOWORD(wParam));

		}
	}

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnActivateApp(WORD fActive) {
	if (fActive == WA_ACTIVE || fActive == WA_CLICKACTIVE) {
		if (!m_bTimerActive) {
			SetTimer(m_hWnd,1,100,NULL);
			m_bTimerActive = true;
		}
	} else {
		if (m_bTimerActive) {
			KillTimer(m_hWnd,1);
			m_bTimerActive = false;
		}
	}

	return 0;
}


LRESULT CMainWnd::OnKeyDown(int /* nVirtKey */, DWORD /* lKeyData */) {
	m_bKeyDown = true;

	return 0;
}

LRESULT CMainWnd::OnKeyUp(int /* nVirtKey */, DWORD /* lKeyData */) {
	m_bKeyDown = false;

	return 0;
}

LRESULT CMainWnd::OnTimer(DWORD /*wTimerID*/) {

	if (!m_bTimerActive) {
		KillTimer(m_hWnd,1);
		m_bTimerActive = false;
	}

	HDC hdcTemp = GetDC(m_hWnd);

	RECT rc;
	rc.left = m_Grid.WaterX() * PIPE_SIZE + m_nOffsetX;
	rc.top = m_Grid.WaterY() * PIPE_SIZE + m_nOffsetY;
	rc.right = rc.left + PIPE_SIZE;
	rc.bottom = rc.top + PIPE_SIZE;
	OnPaintReal(m_hdcBuffer, &rc);
	BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
	//InvalidateRect(m_hWnd, &rc, FALSE);

	int i;
	int j;
	if (m_Grid.GetFast()) {
		j = 5;
	} else {
		j = 1;
	}
	for (i = 0; i < j; i ++) {
		m_Grid.OnTimer();
//		if (m_Grid.OnTimer()) {
//			j += 10;
//		}
		rc.left = m_Grid.WaterX() * PIPE_SIZE + m_nOffsetX;
		rc.top = m_Grid.WaterY() * PIPE_SIZE + m_nOffsetY;
		rc.right = rc.left + PIPE_SIZE;
		rc.bottom = rc.top + PIPE_SIZE;
		OnPaintReal(m_hdcBuffer, &rc);
		BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
		//InvalidateRect(m_hWnd, &rc, FALSE);
	}
	ReleaseDC(m_hWnd, hdcTemp);

//	UpdateWindow(m_hWnd);

	return 0;
}

LRESULT CMainWnd::OnMouseMove(DWORD /* fwKeys */, int x, int y) {

#ifdef UNDER_CE
	POINT pt[100];
	UINT  cpt = 0;
	UINT  i;
	GetMouseMovePoints(pt, 100, &cpt);
	for (i = 0; i < cpt; i++) {
		x = pt[i].x/4;
		y = pt[i].y/4 - Y_TOP;

#endif

	if (m_bMouseDown) {
		if (x >= m_nOffsetX && 
			y >= m_nOffsetY &&
			x <= m_nOffsetX + PIPE_SIZE * PIPES_X && 
			y <= m_nOffsetY + PIPE_SIZE * PIPES_Y) {

			x = (x - m_nOffsetX)/PIPE_SIZE;
			y = (y - m_nOffsetY)/PIPE_SIZE;

			if (x != m_Grid.CurX() || y != m_Grid.CurY()) {

				m_Grid.SelectCell(x, y, m_bKeyDown, false);

				HDC hdcTemp = GetDC(m_hWnd);
				RECT rc;
				rc.left = m_Grid.LastX() * PIPE_SIZE + m_nOffsetX;
				rc.top = m_Grid.LastY() * PIPE_SIZE + m_nOffsetY;
				rc.right = rc.left + PIPE_SIZE;
				rc.bottom = rc.top + PIPE_SIZE;
				OnPaintReal(m_hdcBuffer, &rc);
				BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
				//InvalidateRect(m_hWnd, &rc, FALSE);

				rc.left = m_Grid.CurX() * PIPE_SIZE + m_nOffsetX;
				rc.top = m_Grid.CurY() * PIPE_SIZE + m_nOffsetY;
				rc.right = rc.left + PIPE_SIZE;
				rc.bottom = rc.top + PIPE_SIZE;
				OnPaintReal(m_hdcBuffer, &rc);
				BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
				//InvalidateRect(m_hWnd, &rc, FALSE);
				ReleaseDC(m_hWnd, hdcTemp);

				//UpdateWindow(m_hWnd);
			}
		}
	}


#ifdef UNDER_CE
  }
#endif

	return 0;
}

LRESULT CMainWnd::OnLButtonUp(DWORD /* fwKeys */, int /* x */, int /* y */) {

	m_bMouseDown = false;

	return 0;
}

LRESULT CMainWnd::OnLButtonDown(DWORD /* fwKeys */, int x, int y) {

	m_bMouseDown = true;

	if (x >= m_nOffsetX && 
		y >= m_nOffsetY &&
		x <= m_nOffsetX + PIPE_SIZE * PIPES_X && 
		y <= m_nOffsetY + PIPE_SIZE * PIPES_Y) {

		m_Grid.SelectCell(
			(x - m_nOffsetX)/PIPE_SIZE,
			(y - m_nOffsetY)/PIPE_SIZE,
			m_bKeyDown, true
			);

		HDC hdcTemp = GetDC(m_hWnd);
		RECT rc;
		rc.left = m_Grid.LastX() * PIPE_SIZE + m_nOffsetX;
		rc.top = m_Grid.LastY() * PIPE_SIZE + m_nOffsetY;
		rc.right = rc.left + PIPE_SIZE;
		rc.bottom = rc.top + PIPE_SIZE;
		OnPaintReal(m_hdcBuffer, &rc);
		BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
		//InvalidateRect(m_hWnd, &rc, FALSE);

		rc.left = m_Grid.CurX() * PIPE_SIZE + m_nOffsetX;
		rc.top = m_Grid.CurY() * PIPE_SIZE + m_nOffsetY;
		rc.right = rc.left + PIPE_SIZE;
		rc.bottom = rc.top + PIPE_SIZE;
		OnPaintReal(m_hdcBuffer, &rc);
		BitBlt(hdcTemp, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top,m_hdcBuffer, rc.left, rc.top, SRCCOPY);
		//InvalidateRect(m_hWnd, &rc, FALSE);
		ReleaseDC(m_hWnd, hdcTemp);

		//UpdateWindow(m_hWnd);
	} else {
		POINT pt;
		pt.x = x;
		pt.y = y;
		if (PtInRect(&m_rtClose,pt)) {
			if (MessageBox(
				m_hWnd,
				_T("Are you sure that you want to quit?"),
				_T("Puzzle Of Pipes"),
				MB_YESNO | MB_ICONQUESTION) == IDYES) {
				
				PostMessage(m_hWnd,WM_CLOSE,0,0);

			}
		}
	}

	return 0;
}

LRESULT CMainWnd::OnPaint(HDC) {
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(m_hWnd, &ps);

	HDC hDCBuffer = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC,MAINWND_X,MAINWND_Y+10);
	HBITMAP hBitmapOld = (HBITMAP) SelectObject(hDCBuffer, hBitmap);

	OnPaintReal(hDCBuffer, &ps.rcPaint, true);

	BitBlt(hDC,0,0,MAINWND_X,MAINWND_Y,hDCBuffer,0,0,SRCCOPY);

	SelectObject(hDCBuffer,hBitmapOld);
	DeleteObject(hBitmap);

	EndPaint(m_hWnd,&ps);

	return 0;
}

void CMainWnd::OnPaintReal(HDC hDCBuffer, RECT * rtPaint, bool bBlack) {
	if (bBlack) {
		HBRUSH hbOldBlack = (HBRUSH) SelectObject(hDCBuffer,CreateSolidBrush(RGB(0,0,0)));
		Rectangle(hDCBuffer, rtPaint->left, rtPaint->top, rtPaint->right , rtPaint->bottom);
		DeleteObject(SelectObject(hDCBuffer, hbOldBlack));
	}

	int x;
	int y;

	RECT rc;
	RECT rcTemp;

	HPEN hPenOld = (HPEN) SelectObject(hDCBuffer,m_hPenBlue);
	HBRUSH hBrushOld = (HBRUSH) SelectObject(hDCBuffer, m_hBrushBlue);

	for (x=0;x<PIPES_X;x++) {
		for (y=0;y<PIPES_Y;y++) {
			rc.left = x * PIPE_SIZE + m_nOffsetX;
			rc.top = y * PIPE_SIZE + m_nOffsetY;
			rc.right = rc.left + PIPE_SIZE;
			rc.bottom = rc.top + PIPE_SIZE;
			if (IntersectRect(&rcTemp,rtPaint,&rc)) {
				m_Grid.GetPipe(x,y).DrawPipe(
					hDCBuffer,
					rc.left,
					rc.top);
			}
		}
	}

	if (IntersectRect(&rcTemp, rtPaint, &m_rtClose)) {
		HDC hdcCloseTemp = CreateCompatibleDC(hDCBuffer);

		HBITMAP hbClose = LoadBitmap(g_hInstance,MAKEINTRESOURCE(IDB_CLOSE));
		HBITMAP hbCloseOld = (HBITMAP) SelectObject(hdcCloseTemp, hbClose);

		BitBlt(hDCBuffer,m_rtClose.left,m_rtClose.top,CLOSE_X,CLOSE_Y,hdcCloseTemp,0,0,SRCCOPY);

		SelectObject(hdcCloseTemp, hbCloseOld);
		DeleteObject(hbClose);
		DeleteDC(hdcCloseTemp);
	}

	rc.left = m_nScoreX;
	rc.top = m_nScoreY;
	rc.bottom = MAINWND_Y;
	rc.right = MAINWND_X;

	if (IntersectRect(&rcTemp, rtPaint, &rc)) {
		m_Score.Draw(hDCBuffer, m_nScoreX, m_nScoreY);
	}



	SelectObject(hDCBuffer, hPenOld);
	SelectObject(hDCBuffer, hBrushOld);

}

LRESULT CMainWnd::OnClose() {

	DestroyWindow(m_hWnd);

	return 0;
}

LRESULT CMainWnd::OnDestroy() {

	PostQuitMessage(0);

	return 0;
}

LRESULT CMainWnd::OnCreate() {

	RECT rt;
	GetClientRect(m_hWnd,&rt);

	HDC hdc = GetDC(m_hWnd);
	m_hdcBuffer = CreateCompatibleDC(hdc);
	m_hbBufferOld = (HBITMAP) SelectObject(m_hdcBuffer, CreateCompatibleBitmap(hdc, 240, 320));
	ReleaseDC(m_hWnd, hdc);

#ifdef UNDER_CE
#ifdef POCKET_PC
	m_rtClose.top = rt.bottom - CLOSE_Y;
	m_rtClose.left = rt.right - CLOSE_X * 2;
	m_rtClose.bottom = rt.bottom;
	m_rtClose.right = m_rtClose.left + CLOSE_X;
#else
	SystemParametersInfo(SPI_GETWORKAREA,0, &m_rtClose, 0);
	m_rtClose.top = m_rtClose.bottom - CLOSE_Y;
	m_rtClose.left = m_rtClose.right - CLOSE_X;
#endif
#else
	m_rtClose.top = rt.bottom - CLOSE_Y;
	m_rtClose.left = rt.right - CLOSE_X;
	m_rtClose.bottom = rt.bottom;
	m_rtClose.right = rt.right;
#endif

	m_nOffsetX = ((rt.right - rt.left)/2) - (PIPE_SIZE * (PIPES_X/2));
	m_nOffsetY = m_nOffsetX; // ((rt.bottom - rt.top)/2) - (PIPE_SIZE * 4);

	m_nScoreX = 10;
	m_nScoreY = m_nOffsetY + PIPE_SIZE * PIPES_Y + m_nOffsetY;

	rt.left = m_nScoreX;
	rt.top = m_nScoreY;
	rt.bottom = MAINWND_Y;
	rt.right = MAINWND_X;

	m_Score.SetValues(m_hWnd, rt);

	rt.left = m_nOffsetX;
	rt.top = m_nOffsetY;
	rt.right = rt.left + PIPE_SIZE * PIPES_X;
	rt.bottom = rt.top + PIPE_SIZE * PIPES_Y;

	m_Grid.SetValues(m_hWnd, rt);

	ShowWindow (m_hWnd, SW_SHOWNORMAL);
	UpdateWindow (m_hWnd);

	if (!m_bTimerActive) {
		SetTimer(m_hWnd,1,100,NULL);
		m_bTimerActive = true;
	}

	return 0;
}

void CMainWnd::QuickDraw(RECT * rc) {

	HDC hdcTemp = GetDC(m_hWnd);
	OnPaintReal(m_hdcBuffer, rc, true);
	BitBlt(hdcTemp, rc->left, rc->top, rc->right-rc->left, rc->bottom-rc->top,m_hdcBuffer, rc->left, rc->top, SRCCOPY);
	ReleaseDC(m_hWnd, hdcTemp);
}