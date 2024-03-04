class CMainWnd;

#ifndef PHYLLIS_H__INCLUDED_
#define PHYLLIS_H__INCLUDED_

#include "Game.h"

#define MENU_HEIGHT 26
#define MAX_LOADSTRING 100

#define TIMER_TAP_N_HOLD    1

class CMainWnd : public IGameWatcher
{
public:
					CMainWnd();
					~CMainWnd();

	BOOL			InitInstance	(HINSTANCE, int);

	// From IGameWatcher
	virtual void	GameHasChanged();
	virtual int		GetNumberToDrop(int nMax);
	virtual void	GameIsOver(bool bWon);
	virtual void	PlaceMultiFaceUp(int * nToPlay, TCHAR * szType);
	virtual void	EatOneCard(int * nEatCard, TCHAR ** szType);

private:
	LRESULT OnCommand(WORD wmId, WORD wmEvent);
	LRESULT OnCreate(HWND hWnd);
	LRESULT OnPaint();
	LRESULT OnDestroy();
	LRESULT OnActivate(WPARAM wParam, LPARAM lParam);
	LRESULT OnSettingChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonUp(int x, int y);
	LRESULT OnEraseBkGnd();
    LRESULT OnClose();
    LRESULT OnTimer();
    LRESULT OnLButtonDown(int x, int y);
    LRESULT OnMouseMove(int x, int y);

	static LRESULT CALLBACK MyAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	AboutInit(HWND hDlg);

	static LRESULT CALLBACK MyDrop(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	DropInit(HWND hDlg);

	static LRESULT CALLBACK MyPlaceFaceUp(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	PlaceFaceUpInit(HWND hDlg);

	static LRESULT CALLBACK MyEatOne(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	EatOneInit(HWND hDlg);

	static LRESULT CALLBACK MyOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	OptionsOnInit(HWND hDlg);
	void	OptionsOnOK(HWND hDlg);
	void	OptionsLButtonUp(HWND hDlg, int x, int y);
	void	OptionsPaint(HWND hDlg);

	static LRESULT CALLBACK MyStats(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void	StatsInit(HWND hDlg);
	void	StatsReset(HWND hDlg);

#ifndef UNDER_CE
	static void	SetDefFont(HWND hDlg, int nItem);
#endif

	ATOM	MyRegisterClass	(HINSTANCE, LPTSTR);
	HWND	CreateRpCommandBar(HWND);

	static LRESULT CALLBACK	WndProc (HWND, UINT, WPARAM, LPARAM);

	HINSTANCE		m_hInst;				
	HWND			m_hWnd;
    HWND            m_hWndInfo;
#ifdef UNDER_CE
	HWND			m_hwndCB;					
	SHACTIVATEINFO	m_sai;
#endif

	int				m_nToDrop;
	POINT			m_ptTapped;

	HDC				m_hdcBuffer;
	HBITMAP			m_hbBuffer;
	HBRUSH			m_hbGreen;

    bool            m_bDown;
    bool            m_bTipActive;
    DWORD           m_nDownTick;
    POINT           m_ptDown;

	CGame *			m_pGame;

	int				m_nPlayCard;
	TCHAR *			m_szType[3];
};

#endif
