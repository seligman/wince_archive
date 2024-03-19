class CHighScore;

#ifndef HIGHSCORE_H__INCLUDED_
#define HIGHSCORE_H__INCLUDED_

class CHighScore {
public:
			CHighScore();
			~CHighScore();

	void	SetNewScore(int nScore, int nLevel);

	int		GetLevel();
	int		GetScore();
	LPTSTR	GetName();

	void	SetHwnd(HWND hWnd);

	void	Init();
	void	UnInit();

private:
	static BOOL CALLBACK CHighScore::DialogProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HKEY	m_hKey;
	LPTSTR	m_szName;
	int		m_nScore;
	int		m_nLevel;
	HWND	m_hWnd;
};

#endif