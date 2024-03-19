class CGrid;

#ifndef GRID_H__INCLUDED__
#define GRID_H__INCLUDED__

class CPipe;
class CScore;
class CHighScore;

class CGrid {
public:
			CGrid();
			~CGrid();

	void	ResetGrid(int nLevel = 1);
	bool	IsCurrent(int x, int y);
	void	SelectCell(int x, int y, bool bChange, bool bDown);

	CPipe&	GetPipe(int x, int y);
	int		GetToGo();

	int		GetStartDelay();
	int		GetPipeDelay();
	int		WaterX();
	int		WaterY();
	int		CurX();
	int		CurY();
	int		LastX();
	int		LastY();

	bool	GetFast();
	bool	OnTimer();
	void	SetScore(CScore* pScore);

	void	SetValues(HWND hWnd, RECT & rc);

private:

//	void	xOnTimer();

	CPipe	m_Grid[PIPES_X][PIPES_Y];
	int		m_nToGo;

	int		m_cDown;
	int		m_nWaterX;
	int		m_nWaterY;

	int		m_nCurX;
	int		m_nCurY;

	int		m_nLastX;
	int		m_nLastY;

	int		m_nStartDelay;
	int		m_nPipeDelay;

	bool	m_bGameOver;
	bool	m_bStartDelayed;
	bool	m_bFast;
	int		m_nCurPipeDelay;
	DWORD	m_tickStart;

	CScore*		m_pScore;
	CHighScore	m_HighScore;

	bool	m_bIsBlocked;
	DWORD	m_tickBlockedStart;
	bool	m_bFailed;

	HWND	m_hWnd;
	RECT	m_rcPipes;
};

#endif
