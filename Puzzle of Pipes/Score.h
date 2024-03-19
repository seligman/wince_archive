class CScore;

#ifndef SCORE_H__INCLUDED_
#define SCORE_H__INCLUDED_

class CMainWnd;
class CHighScore;

class CScore {
public:
			CScore();
			~CScore();

	void	ResetScore();
	void	AddToScore(int nAdd);
	void	SetLevel(int nLevel);
	int		GetLevel();
	void	SetMessage(LPTSTR szMsg);

	void	SetLeft(int nLeft);
	void	RemoveOneLeft();

	void	Draw(HDC hdc, int x, int y);
	void	SetValues(HWND hWnd, RECT & rt);
	void	SetMainWnd(CMainWnd * pMainWnd);
	void	SetHighScore(CHighScore * pHighScore);
	void	UpdateBoard();
	int		GetScore();

private:

	CMainWnd* m_pMainWnd;
	CHighScore*	m_pHighScore;
	RECT	m_rtLoc;

	HWND	m_hWnd;
	LPTSTR	m_szMsg;
	int		m_nScore;
	int		m_nLeft;
	int		m_nLevel;
};

#endif