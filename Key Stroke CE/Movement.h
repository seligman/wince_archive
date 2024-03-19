#ifndef MOVEMENT_H__INCLUDED
#define MOVEMENT_H__INCLUDED

enum ModeEnum {
    mNrm = 0,
    mCap = 1,
    mAlt = 2,
    mNum = 3
};

enum TypeEnum {
    tChar = 0,
    tCap = 1,
    tAlt = 2,
    tNum = 3,
    tEnter = 4,
    tBackSpace = 5,
    tSpace = 6,
    tNothing = 7
};


class IMovementListener {
public:
	virtual void CharEntered(TypeEnum nType, TCHAR sChar) { };
	virtual void NewMode(ModeEnum nMode, bool bLock) { };
};

class CMovement {
public:
	ModeEnum	GetMode();
	void		Reset();
	void		IntoPosition(int nPos);
	void		Init(IMovementListener * listener);

private:
	void		SetupArray();


	ModeEnum	m_nCurMode;
	bool		m_bModeLocked;

	TypeEnum	m_nTypes[4][9][9]; /* Mode, From, To */ 
	TCHAR		m_nChars[4][9][9];

	int			m_nLastPos1;
	int			m_nLastPos2;

	IMovementListener * m_listener;
};

#endif