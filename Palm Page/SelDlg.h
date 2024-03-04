class CSelDlg;

#ifndef SELDLG_H__INCLUDED
#define SELDLG_H__INCLUDED

#include "main.h"

class CSelDlg {
public:
	enum enumActions {
		actionDisable,
		actionAutoScroll,
		actionAutoScrollLast,
		actionAutoScrollIncrease,
		actionAutoScrollDecrease,
		actionDeleteToTop,
		actionNone,
		actionCount
	};

			CSelDlg() {};
			~CSelDlg() {};

	int Show(HWND, HINSTANCE, bool);


private:
	static long __stdcall DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam);

	bool	m_bScrollLast;

	int		m_actionList[actionCount];
	int		m_cAction;
	int		m_iRet;
};

#endif