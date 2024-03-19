class CPipe;

#ifndef PIPE_H__INCLUDED__
#define PIPE_H__INCLUDED__

class CPipe {
public:
			CPipe();
			CPipe(CPipe & other);
			~CPipe();

	void	ResetPipe();

	Pipes	GetPipe();

	bool	GetUse();
	void	SetUse(bool bNewUse);

	bool	IsBlank();
	bool	IsSpecial();
	bool	IsStart();

	void	DrawPipe(HDC hdc, int x, int y);

	void	RandomPipe();
	void	SwapWith(CPipe & other);

	bool	operator==(CPipe & rhs);
	bool	operator==(Pipes rhs);
	CPipe&	operator=(CPipe & rhs);
	CPipe&	operator=(Pipes rhs);

	int		GetComplete(int nNum);
	void	SetComplete(int nNum, int nComplete);
	int		GetDir(int nNum);
	void	SetDir(int nNum, int nDir);
	bool	GetFast();
	void	SetFast(bool bFast);

	void	MoveActiveOut();
	bool	IsEntrance(int nDir, Entries point);
	Entries	WhichExit();

private:
	void	DrawComplete(HDC hdc, int x, int y);

	Pipes	m_Pipe;
	bool	m_bInUse;
	bool	m_bFastStart;

	int		m_nComplete[2];
	int		m_nDir[2];

	static	HDC		m_hdcPipes;
	static	HBITMAP	m_hbPipes;
	static	Entries	m_Entry[PipeCount][2][4]; // Pipe, Start/End, Dir
	static	bool	m_bEntryDone;
};

#endif
