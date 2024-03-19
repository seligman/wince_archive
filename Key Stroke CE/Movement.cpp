class IMovementListener;
class CMovement;

#ifndef movement_cpp__included__
#define movement_cpp__included__

#include <windows.h>
#include "Movement.h"

ModeEnum CMovement::GetMode() {
	return m_nCurMode;
}

void CMovement::Reset() {
	m_nLastPos1 = 4;
	m_nLastPos2 = 4;
}

void CMovement::IntoPosition(int nPos) {
	TypeEnum nType = tNothing;
	TCHAR sChar = 0;

	if (nPos == 4) {
		if (m_nLastPos1 != 4) {
			if (m_nLastPos2 == 4) {
				m_nLastPos2 = m_nLastPos1;
				m_nLastPos1 = 4;
			}
			nType = m_nTypes[m_nCurMode][m_nLastPos2][m_nLastPos1];
			sChar = m_nChars[m_nCurMode][m_nLastPos2][m_nLastPos1];
			m_nLastPos1 = 4;
			m_nLastPos2 = 4;
		}
	} else {
		if (nPos != m_nLastPos1) {
			if (m_nLastPos2 == 4) {
				m_nLastPos2 = m_nLastPos1;
			}
			m_nLastPos1 = nPos;
		}
	}

	if (nType != tNothing) {
		m_listener->CharEntered(nType, sChar);

		if (nType == tAlt || nType == tCap || nType == tNum) {
			if (m_nCurMode == nType) {
				if (m_bModeLocked) {
					m_bModeLocked = false;
					m_nCurMode = mNrm;
					m_listener->NewMode(m_nCurMode, false);
				} else {
					m_bModeLocked = true;
					m_listener->NewMode(m_nCurMode, true);
				}
			} else {
				m_bModeLocked = false;
				m_nCurMode = (ModeEnum) nType;
				m_listener->NewMode(m_nCurMode, false);
			}
		} else if (m_bModeLocked == false && m_nCurMode != mNrm) {
			m_nCurMode = mNrm;
			m_listener->NewMode(m_nCurMode, false);
		}

	}

}

void CMovement::SetupArray() {
	int m = 0;
	int f = 0;
	int t = 0;

	for (m = 0; m <= 3; m++) {
		for (f = 0; f <= 8; f++) {
			for (t =0; t <= 8; t++) {
				m_nTypes[m][f][t] = tNothing;
			}
		}
	}

	for (m = 0; m <= 3; m++) {
        m_nTypes[m][1][0] = tAlt; // Square
        m_nTypes[m][1][4] = tBackSpace;
        m_nTypes[m][1][2] = tCap; // Up
        m_nTypes[m][7][6] = tEnter;
        m_nTypes[m][7][4] = tSpace;
        m_nTypes[m][7][8] = tNum; // Circle
	}

    // 0 - Normal
    m_nTypes[0][0][6] = tChar; m_nChars[0][0][6] = _T('q');
    m_nTypes[0][0][3] = tChar; m_nChars[0][0][3] = _T('m');
    m_nTypes[0][0][4] = tChar; m_nChars[0][0][4] = _T('a');
    m_nTypes[0][0][1] = tChar; m_nChars[0][0][1] = _T('s');
    m_nTypes[0][0][2] = tChar; m_nChars[0][0][2] = _T('k');

    m_nTypes[0][3][0] = tChar; m_nChars[0][3][0] = _T('h');
    m_nTypes[0][3][4] = tChar; m_nChars[0][3][4] = _T('e');
    m_nTypes[0][3][6] = tChar; m_nChars[0][3][6] = _T('c');

    m_nTypes[0][6][0] = tChar; m_nChars[0][6][0] = _T('v');
    m_nTypes[0][6][3] = tChar; m_nChars[0][6][3] = _T('w');
    m_nTypes[0][6][4] = tChar; m_nChars[0][6][4] = _T('o');
    m_nTypes[0][6][7] = tChar; m_nChars[0][6][7] = _T('g');
    m_nTypes[0][6][8] = tChar; m_nChars[0][6][8] = _T('z');

    m_nTypes[0][2][0] = tChar; m_nChars[0][2][0] = _T('p');
    m_nTypes[0][2][1] = tChar; m_nChars[0][2][1] = _T('f');
    m_nTypes[0][2][4] = tChar; m_nChars[0][2][4] = _T('n');
    m_nTypes[0][2][5] = tChar; m_nChars[0][2][5] = _T('l');
    m_nTypes[0][2][8] = tChar; m_nChars[0][2][8] = _T('x');

    m_nTypes[0][5][2] = tChar; m_nChars[0][5][2] = _T('u');
    m_nTypes[0][5][4] = tChar; m_nChars[0][5][4] = _T('t');
    m_nTypes[0][5][8] = tChar; m_nChars[0][5][8] = _T('y');
    
    m_nTypes[0][8][6] = tChar; m_nChars[0][8][6] = _T('b');
    m_nTypes[0][8][7] = tChar; m_nChars[0][8][7] = _T('d');
    m_nTypes[0][8][4] = tChar; m_nChars[0][8][4] = _T('i');
    m_nTypes[0][8][5] = tChar; m_nChars[0][8][5] = _T('r');
    m_nTypes[0][8][2] = tChar; m_nChars[0][8][2] = _T('j');

    // 1 - Upper Case
    m_nTypes[1][0][6] = tChar; m_nChars[1][0][6] = _T('Q');
    m_nTypes[1][0][3] = tChar; m_nChars[1][0][3] = _T('M');
    m_nTypes[1][0][4] = tChar; m_nChars[1][0][4] = _T('A');
    m_nTypes[1][0][1] = tChar; m_nChars[1][0][1] = _T('S');
    m_nTypes[1][0][2] = tChar; m_nChars[1][0][2] = _T('K');

    m_nTypes[1][3][0] = tChar; m_nChars[1][3][0] = _T('H');
    m_nTypes[1][3][4] = tChar; m_nChars[1][3][4] = _T('E');
    m_nTypes[1][3][6] = tChar; m_nChars[1][3][6] = _T('C');

    m_nTypes[1][6][0] = tChar; m_nChars[1][6][0] = _T('V');
    m_nTypes[1][6][3] = tChar; m_nChars[1][6][3] = _T('W');
    m_nTypes[1][6][4] = tChar; m_nChars[1][6][4] = _T('O');
    m_nTypes[1][6][7] = tChar; m_nChars[1][6][7] = _T('G');
    m_nTypes[1][6][8] = tChar; m_nChars[1][6][8] = _T('Z');

    m_nTypes[1][2][0] = tChar; m_nChars[1][2][0] = _T('P');
    m_nTypes[1][2][1] = tChar; m_nChars[1][2][1] = _T('F');
    m_nTypes[1][2][4] = tChar; m_nChars[1][2][4] = _T('N');
    m_nTypes[1][2][5] = tChar; m_nChars[1][2][5] = _T('L');
    m_nTypes[1][2][8] = tChar; m_nChars[1][2][8] = _T('X');

    m_nTypes[1][5][2] = tChar; m_nChars[1][5][2] = _T('U');
    m_nTypes[1][5][4] = tChar; m_nChars[1][5][4] = _T('T');
    m_nTypes[1][5][8] = tChar; m_nChars[1][5][8] = _T('Y');
    
    m_nTypes[1][8][6] = tChar; m_nChars[1][8][6] = _T('B');
    m_nTypes[1][8][7] = tChar; m_nChars[1][8][7] = _T('D');
    m_nTypes[1][8][4] = tChar; m_nChars[1][8][4] = _T('I');
    m_nTypes[1][8][5] = tChar; m_nChars[1][8][5] = _T('R');
    m_nTypes[1][8][2] = tChar; m_nChars[1][8][2] = _T('J');

    // 2 - Alt / Symbols
    m_nTypes[2][0][6] = tNothing;
    m_nTypes[2][0][3] = tChar; m_nChars[2][0][3] = _T('@');
    m_nTypes[2][0][4] = tChar; m_nChars[2][0][4] = _T('/');
    m_nTypes[2][0][1] = tChar; m_nChars[2][0][1] = _T('\\');
    m_nTypes[2][0][2] = tChar; m_nChars[2][0][2] = _T('|');

    m_nTypes[2][3][0] = tChar; m_nChars[2][3][0] = _T('#');
    m_nTypes[2][3][4] = tChar; m_nChars[2][3][4] = _T(';');
    m_nTypes[2][3][6] = tChar; m_nChars[2][3][6] = _T(':');

    m_nTypes[2][6][0] = tChar; m_nChars[2][6][0] = _T('^');
    m_nTypes[2][6][3] = tChar; m_nChars[2][6][3] = _T('*');
    m_nTypes[2][6][4] = tChar; m_nChars[2][6][4] = _T('*');
    m_nTypes[2][6][7] = tChar; m_nChars[2][6][7] = _T('{');
    m_nTypes[2][6][8] = tChar; m_nChars[2][6][8] = _T('}');

    m_nTypes[2][2][0] = tChar; m_nChars[2][2][0] = _T('(');
    m_nTypes[2][2][1] = tChar; m_nChars[2][2][1] = _T(')');
    m_nTypes[2][2][4] = tChar; m_nChars[2][2][4] = _T(',');
    m_nTypes[2][2][5] = tChar; m_nChars[2][2][5] = _T('[');
    m_nTypes[2][2][8] = tChar; m_nChars[2][2][8] = _T(']');

    m_nTypes[2][5][2] = tChar; m_nChars[2][5][2] = _T('"');
    m_nTypes[2][5][4] = tChar; m_nChars[2][5][4] = _T('\'');
    m_nTypes[2][5][8] = tChar; m_nChars[2][5][8] = _T('&');
    
    m_nTypes[2][8][6] = tChar; m_nChars[2][8][6] = _T('_');
    m_nTypes[2][8][7] = tChar; m_nChars[2][8][7] = _T('-');
    m_nTypes[2][8][4] = tChar; m_nChars[2][8][4] = _T('.');
    m_nTypes[2][8][5] = tChar; m_nChars[2][8][5] = _T('?');
    m_nTypes[2][8][2] = tChar; m_nChars[2][8][2] = _T('!');

    // 3 - Numbers
    m_nTypes[3][0][6] = tChar; m_nChars[3][0][6] = _T('2');
    m_nTypes[3][0][3] = tChar; m_nChars[3][0][3] = _T('1');
    m_nTypes[3][0][4] = tChar; m_nChars[3][0][4] = _T('0');
    m_nTypes[3][0][1] = tChar; m_nChars[3][0][1] = _T('<');
    m_nTypes[3][0][2] = tChar; m_nChars[3][0][2] = _T('>');

    m_nTypes[3][3][0] = tChar; m_nChars[3][3][0] = _T('#');
    m_nTypes[3][3][4] = tChar; m_nChars[3][3][4] = _T('3');
    m_nTypes[3][3][6] = tChar; m_nChars[3][3][6] = _T('4');

    m_nTypes[3][6][0] = tChar; m_nChars[3][6][0] = _T('/');
    m_nTypes[3][6][3] = tChar; m_nChars[3][6][3] = _T('*');
    m_nTypes[3][6][4] = tChar; m_nChars[3][6][4] = _T('5');
    m_nTypes[3][6][7] = tChar; m_nChars[3][6][7] = _T('6');
    m_nTypes[3][6][8] = tChar; m_nChars[3][6][8] = _T('7');

    m_nTypes[3][2][0] = tChar; m_nChars[3][2][0] = _T('(');
    m_nTypes[3][2][1] = tChar; m_nChars[3][2][1] = _T(')');
    m_nTypes[3][2][4] = tChar; m_nChars[3][2][4] = _T(',');
    m_nTypes[3][2][5] = tChar; m_nChars[3][2][5] = _T('[');
    m_nTypes[3][2][8] = tChar; m_nChars[3][2][8] = _T(']');

    m_nTypes[3][5][2] = tChar; m_nChars[3][5][2] = _T('+');
    m_nTypes[3][5][4] = tChar; m_nChars[3][5][4] = _T('=');
    m_nTypes[3][5][8] = tChar; m_nChars[3][5][8] = _T('-');
    
    m_nTypes[3][8][6] = tChar; m_nChars[3][8][6] = _T('$');
    m_nTypes[3][8][7] = tChar; m_nChars[3][8][7] = _T('%');
    m_nTypes[3][8][4] = tChar; m_nChars[3][8][4] = _T('.');
    m_nTypes[3][8][5] = tChar; m_nChars[3][8][5] = _T('8');
    m_nTypes[3][8][2] = tChar; m_nChars[3][8][2] = _T('9');

}

void CMovement::Init(IMovementListener * listener) {
	m_listener = listener;

	m_nLastPos1 = 4;
	m_nLastPos2 = 4;
	m_nCurMode = mNrm;
	m_bModeLocked = false;

	m_listener->NewMode(m_nCurMode, false);

	SetupArray();
}


#endif