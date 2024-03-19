#include "main.h"

#include "Pipe.h"
#include "HighScore.h"
#include "Score.h"

#include "Grid.h"
#include "MainWnd.h"


void CGrid::SetScore(CScore* pScore) {
	m_pScore = pScore;
	m_pScore->SetHighScore(&m_HighScore);
}

CGrid::CGrid() {
	m_nCurX = 0;
	m_nCurY = 0;
	m_nLastX = 0;
	m_nLastY = 0;
	m_nStartDelay = 0;
	m_nPipeDelay = 0;
	m_pScore = NULL;
	m_bIsBlocked = false;
	m_bFailed = false;
	m_bGameOver = false;
	m_cDown = 0;
	m_bFast = false;

	m_HighScore.Init();
}

CGrid::~CGrid() {
	m_HighScore.UnInit();
}

bool CGrid::IsCurrent(int x, int y) {
	return (m_nCurX == x && m_nCurY == y);
}

void CGrid::SelectCell(int x, int y, bool bChange, bool bDown) {

	if (m_bGameOver) {
		return;
	}

	if (m_bIsBlocked) {
		return;
	}

	if (m_bStartDelayed) {
		if (m_tickStart == 0) {
			m_tickStart = GetTickCount();
			m_pScore->SetMessage(_T(" "));
		}
	}

	if (bChange) {
		if (!m_Grid[x][y].GetUse()) {
			m_nLastY = m_nCurY;
			m_nLastX = m_nCurX;

			m_nCurX = x;
			m_nCurY = y;

			if (!m_Grid[m_nCurX][m_nCurY].IsSpecial()) {
				Pipes pipeLast;
				do {
					do {
						pipeLast = m_Grid[m_nCurX][m_nCurY].GetPipe();
						m_Grid[m_nCurX][m_nCurY].RandomPipe();
					} while (m_Grid[m_nCurX][m_nCurY].GetPipe() == pipeLast);
				} while (m_Grid[m_nCurX][m_nCurY].IsSpecial());
			}
			m_pScore->AddToScore(-5);
		}
	} else {
		if (bDown) {
			m_cDown ++;
		} else {
			m_cDown = 0;
		}

		if (IsCurrent(x,y)) {
			if (m_cDown >= 2) {
				if (m_Grid[x][y].IsStart()) {
					m_Grid[x][y].SetFast(!m_Grid[x][y].GetFast());
					m_bFast = m_Grid[x][y].GetFast();
				}
				if (m_bFast) {
					m_nStartDelay = 0;
					m_nPipeDelay = 0;
				}
				m_cDown = 0;
			}
			return;
		}

		m_nLastY = m_nCurY;
		m_nLastX = m_nCurX;

		m_nCurX = x;
		m_nCurY = y;

		bool bGood = false;
		if (abs(m_nCurX - m_nLastX) == 1 && m_nCurY == m_nLastY) {
			bGood = true;
		} else if (abs(m_nCurY - m_nLastY) == 1 && m_nCurX == m_nLastX) {
			bGood = true;
		}
		if (!bGood) {
			return;
		}
		if (m_Grid[m_nLastX][m_nLastY].GetUse() || m_Grid[m_nCurX][m_nCurY].GetUse()) {
			bGood = false;
		} else if (!m_Grid[m_nCurX][m_nCurY].IsBlank()) {
			bGood = false;
		} else if (m_Grid[m_nLastX][m_nLastY].IsSpecial()) {
			bGood = false;
		}
		if (!bGood) {
			return;
		}

		m_Grid[m_nLastX][m_nLastY].SwapWith(m_Grid[m_nCurX][m_nCurY]);

	}
}

void CGrid::ResetGrid(int nLevel) {
	int nBlanks = nLevel;
	int x;
	int y;

	m_bFast = false;
	m_cDown = 0;

	if (nLevel == 1) {
		m_pScore->ResetScore();
		m_pScore->SetMessage(_T("Tap on grid to begin game"));
	} else {
		m_pScore->SetMessage(_T("Tap to start level"));
	}
	m_pScore->SetLevel(nLevel);

	if (nLevel <= 9) {
		m_nStartDelay = 12000;
		m_nStartDelay -= nLevel * 1000;
	} else {
		m_nStartDelay = 2000;
	}

	if (nLevel <= 5) {
		m_nPipeDelay = (1-int(nLevel/3));
	} else {
		m_nPipeDelay = 0;
	}

	m_nCurPipeDelay = m_nPipeDelay;
	m_bStartDelayed = true;
	m_tickStart = 0;

	m_nToGo = nLevel + 4;
	if (m_nToGo > 20) {
		m_nToGo = 20;
	}

	if (nBlanks > 8) {
		nBlanks = 8;
	}
	nBlanks = 12 - nBlanks;

	for (x=0;x<PIPES_X;x++) {
		for (y=0;y<PIPES_Y;y++) {
			do {
				m_Grid[x][y].ResetPipe();
				m_Grid[x][y].RandomPipe();
			} while (m_Grid[x][y].IsBlank() || m_Grid[x][y].IsSpecial());
		}
	}

	while (nBlanks > 0) {
		do {
			x = rand() % PIPES_X;
			y = rand() % PIPES_Y;
		} while (m_Grid[x][y].IsBlank());
		m_Grid[x][y] = PipeBlank;
		nBlanks --;
	}

	nBlanks = nLevel - 1;
	if (nBlanks > 4) {
		nBlanks = 4;
	}

	int x2 = 0;
	int y2 = 0;
	bool bGood = false;

	while (nBlanks > 0) {
		do {
			x = rand() % PIPES_X;
			y = rand() % PIPES_Y;
		} while (m_Grid[x][y].IsBlank());
		bGood = true;
		for (x2 = x-1; x2 <= x+1; x2 ++) {
			for (y2 = x-1; y2 <= x+1; y2 ++) {
				if (x2 >= 0 && y2 >= 0 && x2 <= (PIPES_X-1) && y2 <= (PIPES_Y-1)) {
					if (m_Grid[x2][y2].IsSpecial()) {
						bGood = false;
					}
				}
			}
		}
		if (bGood) {
			m_Grid[x][y] = PipeBlock;
			nBlanks --;
		}
	}

	Pipes pipeType;

	switch (rand() % 4) {
	case 0:
		pipeType = PipeStartTop;
		break;
	case 1:
		pipeType = PipeStartBottom;
		break;
	case 2:
		pipeType = PipeStartLeft;
		break;
	default:
		pipeType = PipeStartRight;
		break;
	}

	bGood = false;
	do {
		do {
			x = (rand() % 4) + 2;
			y = (rand() % 4) + 2;
		} while (m_Grid[x][y].IsBlank() || m_Grid[x][y].IsSpecial());
		switch (pipeType) {
		case PipeStartTop:
			if (!m_Grid[x][y-1].IsSpecial()) {
				bGood = true;
			}
			break;
		case PipeStartBottom:
			if (!m_Grid[x][y+1].IsSpecial()) {
				bGood = true;
			}
			break;
		case PipeStartLeft:
			if (!m_Grid[x-1][y].IsSpecial()) {
				bGood = true;
			}
			break;
		case PipeStartRight:
			if (!m_Grid[x+1][y].IsSpecial()) {
				bGood = true;
			}
			break;
		}
	} while (!bGood);
	m_Grid[x][y] = pipeType;

	m_nWaterX = x;
	m_nWaterY = y;
	m_Grid[x][y].SetUse(true);
	m_Grid[x][y].SetDir(0,0);

	m_pScore->SetLeft(m_nToGo);

	InvalidateRect(m_hWnd,&m_rcPipes,FALSE);
	UpdateWindow(m_hWnd);

}

void CGrid::SetValues(HWND hWnd, RECT & rc) {
	m_hWnd = hWnd;
	m_rcPipes.left = rc.left;
	m_rcPipes.top = rc.top;
	m_rcPipes.bottom = rc.bottom;
	m_rcPipes.right = rc.right;
	m_HighScore.SetHwnd(m_hWnd);
}


CPipe& CGrid::GetPipe(int x, int y) {
	return m_Grid[x][y];
}

int	CGrid::GetToGo() {
	return m_nToGo;
}

int CGrid::GetStartDelay() {
	return m_nStartDelay;
}

int CGrid::GetPipeDelay() {
	return m_nPipeDelay;
}

bool CGrid::GetFast() {
	return m_bFast;
}

//void CGrid::OnTimer() {

//	if (m_bFast) {
//		xOnTimer();
//		xOnTimer();
//		xOnTimer();
//		xOnTimer();
//		xOnTimer();
//	} else {
//		xOnTimer();
//	}
//
//}

bool CGrid::OnTimer() {
	if (m_bGameOver) {
		if (GetTickCount() - m_tickBlockedStart >= (unsigned) 3000) {
			m_HighScore.SetNewScore(m_pScore->GetScore(),m_pScore->GetLevel());
			m_pScore->UpdateBoard();
			ResetGrid();
			m_bGameOver = false;
		} else {
			return false;
		}
	}

	if (m_bIsBlocked) {
		if (m_bFailed) {
			if (GetTickCount() - m_tickBlockedStart > 3000) {
				if (m_nToGo == 0) {
					ResetGrid(m_pScore->GetLevel() + 1);
				} else {
					m_bGameOver = true;
					m_pScore->SetMessage(_T("Game Over."));
					m_tickBlockedStart = GetTickCount();
				}
				m_bIsBlocked = false;
				m_bFailed = false;
			}
		}
		return false;
	}

	if (m_bStartDelayed) {
		if (m_tickStart != 0) {
			if (GetTickCount() - m_tickStart >= (unsigned) m_nStartDelay) {
				m_bStartDelayed = false;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	if (m_nCurPipeDelay <= 0) {
		m_nCurPipeDelay = m_nPipeDelay;
	} else {
		m_nCurPipeDelay --;
		return false;
	}

	CPipe * pCur = &m_Grid[m_nWaterX][m_nWaterY];
	CPipe * pNext;
	int x;
	int y;
	int i;
	bool bFound;
	bool bFailed = false;
	bool bRet = false;

	if(pCur->GetComplete(0) == 27) {
		bRet = true;
		pNext = NULL;

		x = m_nWaterX;
		y = m_nWaterY;

		switch (pCur->WhichExit()) {
		case Top:
			if ( y == 0 ) {
				bFailed = true;
			} else {
				y -= 1;
			}
			break;
		case Bottom:
			if ( y == (PIPES_Y-1) ) {
				bFailed = true;
			} else {
				y += 1;
			}
			break;
		case Left:
			if ( x == 0) {
				bFailed = true;
			} else {
				x -= 1;
			}
			break;
		case Right:
			if ( x == (PIPES_X-1)) {
				bFailed = true;
			} else {
				x += 1;
			}
			break;
		}

		if (!bFailed) {
			pNext = &m_Grid[x][y];
			bFound = false;
			i = 0;

			while (i<4 && !bFound) {
				if (pNext->IsEntrance(i,pCur->WhichExit())) {
					bFound = true;
				} else {
					i ++;
				}
			}
			if (bFound) {
				if (pNext->GetUse()) {
					m_pScore->AddToScore(20);
				} else {
					m_pScore->AddToScore(10);
				}
				if (m_nToGo > 0) {
					m_nToGo --;
					m_pScore->RemoveOneLeft();
				}

				pNext->MoveActiveOut();
				pNext->SetComplete(0,0);
				pNext->SetDir(0,i);
				pNext->SetUse(true);
				m_nWaterX = x;
				m_nWaterY = y;
			} else {
				bFailed = true;
			}
		}
		if (bFailed) {
			m_bIsBlocked = true;
			m_tickBlockedStart = GetTickCount();
			m_bFailed = true;
		}
	} else {
		pCur->SetComplete(0, pCur->GetComplete(0) + 1);
	}

	return bRet;
}

int CGrid::WaterX() {
	return (m_nWaterX);
}

int CGrid::WaterY() {
	return (m_nWaterY);
}

int CGrid::CurX() {
	return (m_nCurX);
}

int CGrid::CurY() {
	return (m_nCurY);
}

int CGrid::LastX() {
	return (m_nLastX);
}

int CGrid::LastY() {
	return (m_nLastY);
}