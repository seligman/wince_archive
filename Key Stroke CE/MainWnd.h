#pragma once

//#define MAINWND_GUID    _T("{5C66A7A0-22BB-11d4-B859-00B0D040070E}")
//#define MAINWND_CLASS   _T("KeyStrokeCE")
//#define MAINWND_TITLE   _T("KeyStrokeCE")

#include "Movement.h"

class CMainWnd : public IMovementListener {
public:
                                CMainWnd();
                                ~CMainWnd();

			void		SetHwnd(HWND hWnd);
			void		SetHinstance(HINSTANCE hInstance);

			LRESULT		OnUserGetInfo (WPARAM wParam, LPARAM lParam);
			LRESULT		OnPaint(WPARAM wParam, LPARAM lParam);
            LRESULT		OnCreate();
            LRESULT		OnDestroy();
            LRESULT     OnClose();
			LRESULT		OnMouseMove(WORD x, WORD y);
			LRESULT		OnLButtonDown(WORD x1, WORD y1);
			LRESULT		OnLButtonUp();

    static  LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);

	// Movement events
	virtual void CharEntered(TypeEnum nType, TCHAR sChar);
	virtual void NewMode(ModeEnum nMode, bool bLock);
private:

	void DrawInBitmap(HDC hDCTemp, DWORD nOffset, DWORD rsrc, DWORD x, DWORD y, DWORD cx, DWORD cy, DWORD sx, DWORD sy);

	bool			m_bKeyAbort;
    HWND            m_hWnd;
    HINSTANCE       m_hInstance;

	HBITMAP			m_hbBuffer;
	HDC				m_hdcBuffer;

	IIMCallback *	m_pIMCallback;
	RECT			m_rectDocked;
	IMINFO			m_imi;

	ModeEnum		m_modeCur;
	bool			m_bLocked;

	__int8 *		m_nCells;
	int				m_nLastTrigger;

	CMovement *		m_pMovement;
};
