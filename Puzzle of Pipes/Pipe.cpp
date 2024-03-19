#include "main.h"
#include "resource.h"

#include "Pipe.h"

Entries	CPipe::m_Entry[PipeCount][2][4];
HDC		CPipe::m_hdcPipes = 0;
HBITMAP	CPipe::m_hbPipes = 0;
bool	CPipe::m_bEntryDone = false;

void CPipe::ResetPipe() {
	m_Pipe = PipeBlank;
	m_bInUse = 0;
	m_nComplete[0] = 0;
	m_nComplete[1] = 0;
	m_nDir[0] = 5;
	m_nDir[1] = 5;
	m_bFastStart = false;
}

CPipe::CPipe() {
	m_Pipe = PipeBlank;
	m_bInUse = false;
	m_bFastStart = false;
	m_nComplete[0] = 0;
	m_nComplete[1] = 0;
	m_nDir[0] = 5;
	m_nDir[1] = 5;

	if (!m_bEntryDone) {

		m_bEntryDone = true;

		int i;
		int j;
		int k;
		for (i = 0; i < PipeCount; i++) {
			for (j = 0; j < 2; j++) {
				for (k = 0; k < 4; k++) {
					m_Entry[i][j][k] = Blocked;
				}
			}
		}

		m_Entry[PipeLeftBottom][0][0] = Left;
		m_Entry[PipeLeftBottom][1][0] = Bottom;
		m_Entry[PipeLeftBottom][0][1] = Bottom;
		m_Entry[PipeLeftBottom][1][1] = Left;
		m_Entry[PipeLeftTop][0][0] = Left;
		m_Entry[PipeLeftTop][1][0] = Top;
		m_Entry[PipeLeftTop][0][1] = Top;
		m_Entry[PipeLeftTop][1][1] = Left;
		m_Entry[PipeRightBottom][0][0] = Right;
		m_Entry[PipeRightBottom][1][0] = Bottom;
		m_Entry[PipeRightBottom][0][1] = Bottom;
		m_Entry[PipeRightBottom][1][1] = Right;
		m_Entry[PipeRightTop][0][0] = Right;
		m_Entry[PipeRightTop][1][0] = Top;
		m_Entry[PipeRightTop][0][1] = Top;
		m_Entry[PipeRightTop][1][1] = Right;
		m_Entry[PipeCross][0][0] = Top;
		m_Entry[PipeCross][1][0] = Bottom;
		m_Entry[PipeCross][0][1] = Bottom;
		m_Entry[PipeCross][1][1] = Top;
		m_Entry[PipeCross][0][2] = Left;
		m_Entry[PipeCross][1][2] = Right;
		m_Entry[PipeCross][0][3] = Right;
		m_Entry[PipeCross][1][3] = Left;
		m_Entry[PipeVertical][0][0] = Top;
		m_Entry[PipeVertical][1][0] = Bottom;
		m_Entry[PipeVertical][0][1] = Bottom;
		m_Entry[PipeVertical][1][1] = Top;
		m_Entry[PipeHorizontal][0][0] = Left;
		m_Entry[PipeHorizontal][1][0] = Right;
		m_Entry[PipeHorizontal][0][1] = Right;
		m_Entry[PipeHorizontal][1][1] = Left;
		m_Entry[PipeStartTop][0][0] = Middle;
		m_Entry[PipeStartTop][1][0] = Top;
		m_Entry[PipeStartBottom][0][0] = Middle;
		m_Entry[PipeStartBottom][1][0] = Bottom;
		m_Entry[PipeStartLeft][0][0] = Middle;
		m_Entry[PipeStartLeft][1][0] = Left;
		m_Entry[PipeStartRight][0][0] = Middle;
		m_Entry[PipeStartRight][1][0] = Right;
	}
}

CPipe::CPipe(CPipe & other) {
	CPipe();

	m_Pipe = other.GetPipe();
}

bool CPipe::GetUse() {
	return m_bInUse;
}

void CPipe::SetUse(bool bNewUse) {
	m_bInUse = bNewUse;
}

CPipe::~CPipe() {
	// nothing
}

Pipes CPipe::GetPipe() {
	return m_Pipe;
}

void CPipe::SwapWith(CPipe& other) {
	CPipe tmp(*this);
	(* this) = other;
	other = tmp;
}

bool CPipe::operator==(CPipe & rhs) {
	return (rhs.GetPipe() == m_Pipe);
}

bool CPipe::operator==(Pipes rhs) {
	return (rhs == m_Pipe);
}

CPipe& CPipe::operator=(CPipe & rhs) {
	m_Pipe = rhs.GetPipe();
	return (*this);
}

CPipe& CPipe::operator=(Pipes rhs) {
	m_Pipe = rhs;
	return (*this);
}

bool CPipe::IsBlank() {
	return (m_Pipe == PipeBlank);
}

bool CPipe::IsSpecial() {
	return (m_Pipe == PipeBlock || 
		m_Pipe == PipeStartTop || 
		m_Pipe == PipeStartBottom || 
		m_Pipe == PipeStartLeft || 
		m_Pipe == PipeStartRight);
}

bool CPipe::IsStart() {
	return (m_Pipe == PipeStartTop || 
		m_Pipe == PipeStartBottom || 
		m_Pipe == PipeStartLeft || 
		m_Pipe == PipeStartRight);
}

void CPipe::RandomPipe() {
	m_Pipe = (Pipes) (rand() % PipeCount);
	m_bInUse = false;
	m_bFastStart = false;
	m_nComplete[0] = 0;
	m_nComplete[1] = 0;
	m_nDir[0] = 5;
	m_nDir[1] = 5;
}

void CPipe::DrawPipe(HDC hdc, int x, int y) {

	if (!m_hdcPipes) {
		m_hdcPipes = CreateCompatibleDC(hdc);
		m_hbPipes = LoadBitmap(g_hInstance,MAKEINTRESOURCE(IDB_ALL_PIPES));
		SelectObject(m_hdcPipes, m_hbPipes);
	}

	if (m_bFastStart) {
		switch(m_Pipe) {
		case PipeStartTop:
			BitBlt(hdc, x, y, PIPE_SIZE, PIPE_SIZE, m_hdcPipes, 0, PIPE_SIZE * (13), SRCCOPY);
			break;
		case PipeStartBottom:
			BitBlt(hdc, x, y, PIPE_SIZE, PIPE_SIZE, m_hdcPipes, 0, PIPE_SIZE * (16), SRCCOPY);
			break;
		case PipeStartLeft:
			BitBlt(hdc, x, y, PIPE_SIZE, PIPE_SIZE, m_hdcPipes, 0, PIPE_SIZE * (14), SRCCOPY);
			break;
		default: //case PipeStartRight:
			BitBlt(hdc, x, y, PIPE_SIZE, PIPE_SIZE, m_hdcPipes, 0, PIPE_SIZE * (15), SRCCOPY);
			break;
		}
	} else {
		BitBlt(hdc, x, y, PIPE_SIZE, PIPE_SIZE, m_hdcPipes, 0, PIPE_SIZE * ((UINT) m_Pipe), SRCCOPY);
	}

	if (m_bInUse) {
		DrawComplete(hdc, x, y);
	}

}

void CPipe::DrawComplete(HDC hdc, int x, int y) {

	int nPart;

	for (nPart = 0; nPart < 2; nPart++) {

		if (m_nDir[nPart] != 5) {

			RECT rt1 = {0,0,0,0};
			RECT rt2 = {0,0,0,0};
			bool bValid1 = false;
			bool bValid2 = false;
			Entries entryStart = m_Entry[m_Pipe][0][m_nDir[nPart]];
			Entries entryEnd = m_Entry[m_Pipe][1][m_nDir[nPart]];

			if ( ( entryStart == Top || entryStart == Bottom ) &&
				( entryEnd == Top || entryEnd == Bottom ) ) {
				if (m_Pipe == PipeCross) {
					bValid1 = true;
					rt1.left = 12;
					rt1.right = 16;
					if (entryStart == Top) {
						rt1.top = 0;
						if (m_nComplete[nPart] < 11) {
							rt1.bottom = m_nComplete[nPart]+1;
						} else {
							rt1.bottom = 11;
							if (m_nComplete[nPart] >= 17) {
								bValid2 = true;
								rt2.left = 12;
								rt2.right = 16;
								rt2.top = 17;
								rt2.bottom = m_nComplete[nPart] + 1;
							}
						}
					} else {
						if (m_nComplete[nPart] < 10) {
							rt1.top = 27 - m_nComplete[nPart];
						} else {
							rt1.top = 17;
							if (m_nComplete[nPart] >= 17) {
								bValid2 = true;
								rt2.left = 12;
								rt2.right = 16;
								rt2.top = 27 - m_nComplete[nPart];
								rt2.bottom = 11;
							}
						}
						rt1.bottom = PIPE_SIZE;
					}
					//break
				} else {
					bValid1 = true;
					rt1.left = 12;
					rt1.right = 16;
					if (entryStart == Top) {
						rt1.top = 0;
						rt1.bottom = m_nComplete[nPart]+1;
					} else {
						rt1.top = 27 - m_nComplete[nPart];
						rt1.bottom = 27+1;
					}
				}
			} else if ( ( entryStart == Left || entryStart == Right ) &&
				( entryEnd == Left || entryEnd == Right ) ) {
				bValid1 = true;
				rt1.top = 12;
				rt1.bottom = 16;
				if (entryStart == Left) {
					rt1.left = 0;
					rt1.right = m_nComplete[nPart]+1;
				} else {
					rt1.left = 27 - m_nComplete[nPart];
					rt1.right = 27+1;
				}
			} else if ( entryStart == Middle ) {
				if (m_nComplete[nPart] > 12) {
					switch(entryEnd) {
					case Top:
						rt1.left = 12;
						rt1.right = 16;
						rt1.top = 27 - m_nComplete[nPart];
						rt1.bottom = 16;
						break;
					case Bottom:
						rt1.left = 12;
						rt1.right = 16;
						rt1.bottom = m_nComplete[nPart]+1;
						rt1.top = 12;
						break;
					case Left:
						rt1.top = 12;
						rt1.bottom = 16;
						rt1.right = 16;
						rt1.left = 27 - m_nComplete[nPart];
						break;
					case Right:
						rt1.top = 12;
						rt1.bottom = 16;
						rt1.left = 12;
						rt1.right = m_nComplete[nPart]+1;
						break;
					}
					bValid1 = true;
				}
			} else {
				int i = m_nComplete[nPart];
				int j = m_nComplete[nPart];
				if (i > 15) {
					i = 15;
				}

				switch(entryStart) {
				case Top:
					rt1.left = 12;
					rt1.right = 16;
					rt1.top = 0;
					rt1.bottom = i+1;
					break;
				case Bottom:
					rt1.left = 12;
					rt1.right = 16;
					rt1.bottom = 27+1;
					rt1.top = 27-i;
					break;
				case Left:
					rt1.top = 12;
					rt1.bottom = 16;
					rt1.right = i+1;
					rt1.left = 0;
					break;
				case Right:
					rt1.top = 12;
					rt1.bottom = 16;
					rt1.right = 27+1;
					rt1.left = 27-i;
					break;
				}
				bValid1 = true;
				if (m_nComplete[nPart] >= 14) {
					switch(entryEnd) {
					case Top:
						rt2.left = 12;
						rt2.right = 16;
						rt2.bottom = 15;
						rt2.top = 27-j;
						break;
					case Bottom:
						rt2.left = 12;
						rt2.right = 16;
						rt2.bottom = j+1;
						rt2.top = 16;
						break;
					case Left:
						rt2.top = 12;
						rt2.bottom = 16;
						rt2.right = 16;
						rt2.left = 27-j;
						break;
					case Right:
						rt2.top = 12;
						rt2.bottom = 16;
						rt2.right = j+1;
						rt2.left = 12;
						break;
					}
					bValid2 = true;
				}

			} // drawing of rects

			if (bValid1) {
				Rectangle(hdc,
					rt1.left + x, rt1.top + y,
					rt1.right + x, rt1.bottom + y);
			}
			if (bValid2) {
				Rectangle(hdc,
					rt2.left + x, rt2.top + y,
					rt2.right + x, rt2.bottom + y);
			}

		} // verify peice isn't blocked

	} // looping through the two inner peices

}

void CPipe::MoveActiveOut() {
	m_nComplete[1] = m_nComplete[0];
	m_nDir[1] = m_nDir[0];
	m_nDir[0] = 5;
	m_nComplete[0] = 0;
}

bool CPipe::IsEntrance(int nDir, Entries point) {
	switch(point) {
	case Left:
		return(m_Entry[m_Pipe][0][nDir] == Right);
	case Right:
		return(m_Entry[m_Pipe][0][nDir] == Left);
	case Top:
		return(m_Entry[m_Pipe][0][nDir] == Bottom);
	default: //case Bottom:
		return(m_Entry[m_Pipe][0][nDir] == Top);
	}
}

Entries CPipe::WhichExit() {
	return (m_Entry[m_Pipe][1][m_nDir[0]]);
}

int CPipe::GetComplete(int nNum) {
	return m_nComplete[nNum];
}

void CPipe::SetComplete(int nNum, int nComplete) {
	m_nComplete[nNum] = nComplete;
}

int CPipe::GetDir(int nNum) {
	return m_nDir[nNum];
}

void CPipe::SetDir(int nNum, int nDir) {
	m_nDir[nNum] = nDir;
}

bool CPipe::GetFast() {
	return m_bFastStart;
}

void CPipe::SetFast(bool bFast) {
	m_bFastStart = bFast;
}
