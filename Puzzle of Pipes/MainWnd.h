class CMainWnd;

#ifndef MAINWND_H__INCLUDED__
#define MAINWND_H__INCLUDED__

#define CLOSE_X		36
#define CLOSE_Y		20

class CScore;
class CGrid;
class CScore;

class CMainWnd {
public:
			CMainWnd();
			~CMainWnd();

	BOOL	PrevInst();
	HWND	Create(HINSTANCE);

	void	QuickDraw(RECT * rt);

private:
	LRESULT	OnCreate();
	LRESULT	OnDestroy();
	LRESULT	OnClose();
	LRESULT OnPaint(HDC hDC);
	LRESULT	OnLButtonDown(DWORD fwKeys, int x, int y);
	LRESULT	OnLButtonUp(DWORD fwKeys, int x, int y);
	LRESULT	OnMouseMove(DWORD fwKeys, int x, int y);
	LRESULT OnTimer(DWORD wTimerID);
	LRESULT	OnKeyDown(int nVirtKey, DWORD lKeyData);
	LRESULT	OnKeyUp(int nVirtKey, DWORD lKeyData);
	LRESULT OnActivateApp(WORD fActive);
	void	OnPaintReal(HDC hDCBuffer, RECT * rtPaint, bool bBlack = false);

	static LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

	RECT		m_rtClose;
	HDC			m_hdcBuffer;
	HBITMAP		m_hbBufferOld;

	bool		m_bMouseDown;
	bool		m_bTimerActive;

	HBRUSH		m_hBrushBlue;
	HPEN		m_hPenBlue;

	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	HANDLE		m_hMutex;

	int			m_nOffsetX;
	int			m_nOffsetY;

	int			m_nScoreX;
	int			m_nScoreY;

	CGrid		m_Grid;
	CScore		m_Score;
	bool		m_bKeyDown;
};

#endif