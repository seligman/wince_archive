class CGrid;
#include "main.h"


#include "HighScore.h"

#include "Score.h"
#include "Pipe.h"
#include "Grid.h"
#include "MainWnd.h"

void CScore::SetMainWnd(CMainWnd * pMainWnd) {
	m_pMainWnd = pMainWnd;
}

CScore::CScore() {
	m_szMsg = NULL;
	m_nLeft = 0;
	m_nScore = 0;
	m_nLevel = 0;
	m_hWnd = NULL;
	m_pHighScore = NULL;
}

CScore::~CScore() {
	if (m_szMsg) {
		free (m_szMsg);
	}
}

void CScore::SetLevel(int nLevel) {
	m_nLevel = nLevel;
	UpdateBoard();
}

void CScore::ResetScore() {
	m_nScore = 0;
	UpdateBoard();
}

void CScore::AddToScore(int nAdd) {
	m_nScore += nAdd;
	UpdateBoard();
}

void CScore::SetMessage(LPTSTR szMsg) {
	if (m_szMsg) {
		free (m_szMsg);
	}
	m_szMsg = (LPTSTR) malloc ((_tcslen(szMsg)+1) * sizeof(TCHAR));
	_tcscpy(m_szMsg, szMsg);
	UpdateBoard();
}

void CScore::SetLeft(int nLeft) {
	m_nLeft = nLeft;
	UpdateBoard();
}

void CScore::RemoveOneLeft() {
	if (m_nLeft > 0) {
		m_nLeft --;
		UpdateBoard();
	}
}

void CScore::UpdateBoard() {
//	InvalidateRect(m_hWnd, &m_rtLoc, FALSE);
//	UpdateWindow(m_hWnd);
	m_pMainWnd->QuickDraw(&m_rtLoc);
}


void CScore::Draw(HDC hdc, int x, int y) {
	SetTextColor(hdc, RGB(128,128,128));
	SetBkColor(hdc,RGB(0,0,0));

	RECT rt;
	rt.top = y;
	rt.left = x;
	rt.bottom = MAINWND_Y;
	rt.right = MAINWND_X - x;

	TCHAR sz[100] = _T("");
	wsprintf((TCHAR *) &sz,_T("Score: %d  Left: %d  Level: %d"),m_nScore, m_nLeft, m_nLevel);

	if (m_szMsg) {
		DrawText(hdc,(TCHAR *) m_szMsg, _tcslen((TCHAR *) m_szMsg), &rt, DT_CALCRECT);
		DrawText(hdc,(TCHAR *) m_szMsg, _tcslen((TCHAR *) m_szMsg), &rt, DT_NOCLIP);
	} else {
		DrawText(hdc,(TCHAR *) _T(" "), _tcslen((TCHAR *) _T(" ")), &rt, DT_CALCRECT);
		DrawText(hdc,(TCHAR *) _T(" "), _tcslen((TCHAR *) _T(" ")), &rt, DT_NOCLIP);
	}

	int i = rt.bottom - rt.top;
	rt.bottom += i;
	rt.top += i;
	rt.left = x;
	rt.right = MAINWND_X-x;

	DrawText(hdc,(TCHAR *) &sz, _tcslen((TCHAR *) &sz), &rt,  0);

	if (m_pHighScore) {
		if (m_pHighScore->GetLevel() != 0) {
			rt.bottom += i;
			rt.top += i;
			rt.left = x;
			rt.right = MAINWND_X-x;
			bool bName = false;
			if (m_pHighScore->GetName()) {
				if (_tcslen(m_pHighScore->GetName()) > 0) {
					bName = true;
				}
			}
			
			if (bName) {
				wsprintf((TCHAR *) &sz,_T("High Score: %s - %d (%d)"),m_pHighScore->GetName(), m_pHighScore->GetScore(), m_pHighScore->GetLevel());
			} else {
				wsprintf((TCHAR *) &sz,_T("High Score: %d (%d)"),m_pHighScore->GetScore(), m_pHighScore->GetLevel());
			}

			DrawText(hdc,(TCHAR *) &sz, _tcslen((TCHAR *) &sz), &rt,  0);


		}
	}
}

void CScore::SetValues(HWND hWnd, RECT & rt) {
	m_hWnd = hWnd;
	m_rtLoc.left = rt.left;
	m_rtLoc.right = rt.right;
	m_rtLoc.top = rt.top;
	m_rtLoc.bottom = rt.bottom;
}

int CScore::GetLevel() {
	return m_nLevel;
}

void CScore::SetHighScore(CHighScore * pHighScore) {
	m_pHighScore = pHighScore;
}

int	CScore::GetScore() {
	return m_nScore;
}