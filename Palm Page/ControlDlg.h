class CControlDlg;

#ifndef CONTROLDLG_H__INCLUDED
#define CONTROLDLG_H__INCLUDED

class IMuteIcon {
public:
	virtual void ChangeTo(BOOL bMute) = 0;
};

class CControlDlg {
public:
			CControlDlg() {};
			~CControlDlg() {};

	void Show(HWND hWnd, HINSTANCE hInstance, DWORD * dwVol, BOOL * bMute);
	//, IMuteIcon * pimi

private:

	LRESULT		OnPaint(HDC hDC);


	static long __stdcall DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam);

	HWND		m_hWnd;
	DWORD *		m_dwVol;
	BOOL *		m_bMute;
	HINSTANCE	m_hInstance;
	//IMuteIcon *	m_pimi;
};

#endif
