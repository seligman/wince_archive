#include "stdafx.h"
#include <commctrl.h>
#ifdef UNDER_CE
#include <aygshell.h>
#include <sipapi.h>
#else
#include <stdio.h>
#include <math.h>
#endif
#include "resource.h"
#include "Phyllis.h"

#ifdef COMPUTER_VS_COMPUTER
int g_nCurrentNum = 0;
#define CUR_START	0
#define CUR_END		0
#define CUR_REPS	10000 // 10000
#endif

// A global variable so the window procedures can find us
CMainWnd * g_pmw = NULL;

// Another global to get the instance to some ancient code
HINSTANCE g_hInstance = NULL;

// For drawing the cards in the options dialog
#ifdef UNDER_CE
#define CARD_TOP 117
#else
#define CARD_TOP 140
#endif
#define CARD_LEFT 10
#define CARD_BORDER 3

#ifndef UNDER_CE
void CMainWnd::SetDefFont(HWND hDlg, int nItem)
{
	static HFONT hFont = NULL;
	if (hFont == NULL)
	{
		hFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
	}

	SendDlgItemMessage(hDlg, nItem, WM_SETFONT, (WPARAM) hFont, 0);
}
#endif

void CMainWnd::GameIsOver(bool bWon)
{
	InvalidateRect(m_hWnd, NULL, FALSE);
	UpdateWindow(m_hWnd);

	if (bWon)
	{
		MessageBox(m_hWnd,
			_T("Game Over: You win!"), 
			_T("Game Over"), 
			MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(m_hWnd,
			_T("Game Over: You lost."), 
			_T("Game Over"), 
			MB_ICONINFORMATION);
	}
}

void CMainWnd::PlaceMultiFaceUp(int * nToPlay, TCHAR * szType)
{
	m_nPlayCard = (*nToPlay);
	m_szType[0] = szType;

	DialogBox(m_hInst, (LPCTSTR)IDD_FACEUP_DROP, m_hWnd, (DLGPROC)MyPlaceFaceUp);
    InvalidateRect(m_hWnd, NULL, FALSE);

    UpdateWindow(m_hWnd);
    Sleep(500);

	(*nToPlay) = m_nPlayCard;
}

void CMainWnd::EatOneCard(int * nEatCard, TCHAR ** szType)
{
	int i;
	for (i = 0; i < 3; i ++)
	{
		m_szType[i] = szType[i];
	}

	DialogBox(m_hInst, (LPCTSTR)IDD_EAT_ONE, m_hWnd, (DLGPROC)MyEatOne);
    InvalidateRect(m_hWnd, NULL, FALSE);

    UpdateWindow(m_hWnd);
    Sleep(500);

	(*nEatCard) = m_nPlayCard;
}

void CMainWnd::PlaceFaceUpInit(HWND hDlg)
{
	ClientToScreen(m_hWnd, &m_ptTapped);

	RECT rtMain;
	RECT rtButton;

	RECT rtWindow;

	GetWindowRect(m_hWnd, &rtWindow);

	GetWindowRect(hDlg, &rtMain);
	GetWindowRect(GetDlgItem(hDlg, IDC_CARD1), &rtButton);

	OffsetRect(&rtMain, -rtMain.left, -rtMain.top);
	OffsetRect(&rtButton, -rtButton.left, -rtButton.top);

	int i;
	int nControl = IDC_CARD3;
	for (i = 3; i > m_nPlayCard; i--)
	{
		rtMain.bottom -= rtButton.bottom;
		ShowWindow(GetDlgItem(hDlg, nControl), SW_HIDE);
		nControl --;
	}

	int x = m_ptTapped.x - ((rtMain.right) / 2);
	int y = m_ptTapped.y - ((rtMain.bottom) / 2);
	if (x < rtWindow.left)
	{
		x = rtWindow.left;
	}
	if (x > rtWindow.right - rtMain.right)
	{
		x = rtWindow.right - rtMain.right;
	}
	if (y < rtWindow.top)
	{
		y = rtWindow.top;
	}
	if (y > rtWindow.bottom - rtMain.bottom)
	{
		y = rtWindow.bottom - rtMain.bottom;
	}

	MoveWindow(hDlg, x, y, rtMain.right, rtMain.bottom, FALSE);

	m_nPlayCard = 0;
}

LRESULT CALLBACK CMainWnd::MyPlaceFaceUp(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
		case WM_INITDIALOG:
#ifdef UNDER_CE
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIPDOWN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
#else
			SetDefFont(hDlg, IDC_HOWMANY);
			SetDefFont(hDlg, IDC_CARD1);
			SetDefFont(hDlg, IDC_CARD2);
			SetDefFont(hDlg, IDC_CARD3);
#endif
			g_pmw->PlaceFaceUpInit(hDlg);
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_CARD1:
					g_pmw->m_nPlayCard = 1;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD2:
					g_pmw->m_nPlayCard = 2;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD3:
					g_pmw->m_nPlayCard = 3;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
			}
			break;
	}
    return FALSE;
}

void CMainWnd::EatOneInit(HWND hDlg)
{
	ClientToScreen(m_hWnd, &m_ptTapped);

	RECT rtMain;
	RECT rtButton;

	RECT rtWindow;

	GetWindowRect(m_hWnd, &rtWindow);

	GetWindowRect(hDlg, &rtMain);
	GetWindowRect(GetDlgItem(hDlg, IDC_CARD1), &rtButton);

	OffsetRect(&rtMain, -rtMain.left, -rtMain.top);
	OffsetRect(&rtButton, -rtButton.left, -rtButton.top);

	int i;
	int j;
	int nControl = IDC_CARD3;
	int nControl2;
	RECT rtTemp;
	POINT ptTemp = {0};
	ScreenToClient(hDlg, &ptTemp);
	for (i = 2; i >= 0; i--)
	{
		if (m_szType[i] == NULL)
		{
			rtMain.bottom -= rtButton.bottom;
			ShowWindow(GetDlgItem(hDlg, nControl), SW_HIDE);
			nControl2 = nControl + 1;
			for (j = i + 1; j < 4; j ++)
			{
				GetWindowRect(GetDlgItem(hDlg, nControl2), &rtTemp);
				OffsetRect(&rtTemp, ptTemp.x, ptTemp.y);
				OffsetRect(&rtTemp, 0, -rtButton.bottom);
				MoveWindow(GetDlgItem(hDlg, nControl2), rtTemp.left, rtTemp.top, 
					rtTemp.right - rtTemp.left, rtTemp.bottom - rtTemp.top, TRUE);
				nControl2 ++;
			}
		}
		else
		{
			SendDlgItemMessage(hDlg, nControl, WM_SETTEXT, 0, (LPARAM) m_szType[i]);
		}
		nControl --;
	}

	int x = m_ptTapped.x - ((rtMain.right) / 2);
	int y = m_ptTapped.y - ((rtMain.bottom) / 2);
	if (x < rtWindow.left)
	{
		x = rtWindow.left;
	}
	if (x > rtWindow.right - rtMain.right)
	{
		x = rtWindow.right - rtMain.right;
	}
	if (y < rtWindow.top)
	{
		y = rtWindow.top;
	}
	if (y > rtWindow.bottom - rtMain.bottom)
	{
		y = rtWindow.bottom - rtMain.bottom;
	}

	MoveWindow(hDlg, x, y, rtMain.right, rtMain.bottom, FALSE);

	m_nPlayCard = 0;
}

LRESULT CALLBACK CMainWnd::MyEatOne(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
		case WM_INITDIALOG:
#ifdef UNDER_CE
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIPDOWN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
#else
			SetDefFont(hDlg, IDC_HOWMANY);
			SetDefFont(hDlg, IDC_CARD1);
			SetDefFont(hDlg, IDC_CARD2);
			SetDefFont(hDlg, IDC_CARD3);
			SetDefFont(hDlg, IDC_CARD4);
#endif
			g_pmw->EatOneInit(hDlg);
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_CARD1:
					g_pmw->m_nPlayCard = 1;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD2:
					g_pmw->m_nPlayCard = 2;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD3:
					g_pmw->m_nPlayCard = 3;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD4:
					g_pmw->m_nPlayCard = 0;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
			}
			break;
	}
    return FALSE;
}

void CMainWnd::GameHasChanged()
{
	// Just redraw the game when this happens
#ifndef COMPUTER_VS_COMPUTER
	InvalidateRect(m_hWnd, NULL, FALSE);
	UpdateWindow(m_hWnd);
#endif
}

CMainWnd::CMainWnd()
{
	m_hInst = NULL;				
	m_hWnd = NULL;
#ifdef UNDER_CE
	m_hwndCB = NULL;
#endif
	m_hbGreen = NULL;
	m_hdcBuffer = NULL;
	m_hbBuffer = NULL;
}

CMainWnd::~CMainWnd()
{
	if (m_hbGreen)
	{
		xuntrack(m_hbGreen);
		DeleteObject(m_hbGreen);
	}
	if (m_hbBuffer)
	{
		xuntrack(m_hbBuffer);
		DeleteObject(m_hbBuffer);
	}
	if (m_hdcBuffer)
	{
		xuntrack(m_hdcBuffer);
		DeleteObject(m_hdcBuffer);
	}

}

void CMainWnd::AboutInit(HWND hDlg)
{

	TCHAR szVersion[MAX_LOADSTRING];			
	TCHAR szVersionInfo[MAX_LOADSTRING+20];		

	LoadString(m_hInst, IDS_VERSION, szVersion, MAX_LOADSTRING);

	_stprintf(szVersionInfo, _T("Phyllis version %s"), szVersion);

	SendDlgItemMessage(hDlg, IDC_VERSION, WM_SETTEXT, 0, (LPARAM) szVersionInfo);

}

LRESULT CALLBACK CMainWnd::MyAbout(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
		case WM_INITDIALOG:
#ifdef UNDER_CE
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
#else
			SetDefFont(hDlg, IDOK);
			SetDefFont(hDlg, IDC_VERSION);
			SetDefFont(hDlg, IDC_LINE1);
			SetDefFont(hDlg, IDC_LINE2);
			SetDefFont(hDlg, IDC_LINE3);
#endif
			g_pmw->AboutInit(hDlg);
			return TRUE; 

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

int CMainWnd::GetNumberToDrop(int nMax)
{
	m_nToDrop = nMax;

	DialogBox(m_hInst, (LPCTSTR)IDD_DROP_CARD, m_hWnd, (DLGPROC)MyDrop);
    InvalidateRect(m_hWnd, NULL, FALSE);

    UpdateWindow(m_hWnd);
    Sleep(500);

	return m_nToDrop;
}

void CMainWnd::DropInit(HWND hDlg)
{
	ClientToScreen(m_hWnd, &m_ptTapped);

	RECT rtMain;
	RECT rtButton;

	RECT rtWindow;

	GetWindowRect(m_hWnd, &rtWindow);

	GetWindowRect(hDlg, &rtMain);
	GetWindowRect(GetDlgItem(hDlg, IDC_CARD1), &rtButton);

	OffsetRect(&rtMain, -rtMain.left, -rtMain.top);
	OffsetRect(&rtButton, -rtButton.left, -rtButton.top);

	int i;
	int nControl = IDC_CARD4;
	for (i = 4; i > m_nToDrop; i--)
	{
		rtMain.bottom -= rtButton.bottom;
		ShowWindow(GetDlgItem(hDlg, nControl), SW_HIDE);
		nControl --;
	}

	int x = m_ptTapped.x - ((rtMain.right) / 2);
	int y = m_ptTapped.y - ((rtMain.bottom) / 2);
	if (x < rtWindow.left)
	{
		x = rtWindow.left;
	}
	if (x > rtWindow.right - rtMain.right)
	{
		x = rtWindow.right - rtMain.right;
	}
	if (y < rtWindow.top)
	{
		y = rtWindow.top;
	}
	if (y > rtWindow.bottom - rtMain.bottom)
	{
		y = rtWindow.bottom - rtMain.bottom;
	}

	MoveWindow(hDlg, x, y, rtMain.right, rtMain.bottom, FALSE);

	m_nToDrop = 0;
}

LRESULT CALLBACK CMainWnd::MyDrop(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
		case WM_INITDIALOG:
#ifdef UNDER_CE
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIPDOWN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
#else
			SetDefFont(hDlg, IDC_HOWMANY);
			SetDefFont(hDlg, IDC_CARD1);
			SetDefFont(hDlg, IDC_CARD2);
			SetDefFont(hDlg, IDC_CARD3);
			SetDefFont(hDlg, IDC_CARD4);
#endif
			g_pmw->DropInit(hDlg);
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_CARD1:
					g_pmw->m_nToDrop = 1;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD2:
					g_pmw->m_nToDrop = 2;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD3:
					g_pmw->m_nToDrop = 3;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
				case IDC_CARD4:
					g_pmw->m_nToDrop = 4;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
					break;
			}
			break;
	}
    return FALSE;
}

void CMainWnd::StatsInit(HWND hDlg)
{
	TCHAR sz[100];

	_stprintf(sz, _T("%d"), m_pGame->GetWins());
	SendDlgItemMessage(hDlg, IDC_WINS, WM_SETTEXT, 0, (LPARAM) sz);

	_stprintf(sz, _T("%d"), m_pGame->GetLoses());
	SendDlgItemMessage(hDlg, IDC_LOSES, WM_SETTEXT, 0, (LPARAM) sz);

	if (m_pGame->GetLoses() + m_pGame->GetWins() == 0)
	{
		_tcscpy(sz, _T("--"));
	}
	else
	{
		_stprintf(sz, _T("%3.1f%%"), 
			((double)(m_pGame->GetWins())) / 
			((double)(m_pGame->GetLoses() + m_pGame->GetWins())) * ((double)100)
			);
	}
	SendDlgItemMessage(hDlg, IDC_PERCENTAGE, WM_SETTEXT, 0, (LPARAM) sz);
}

void CMainWnd::StatsReset(HWND hDlg)
{
	if (MessageBox(hDlg, _T("Are you sure that you want to reset the wins and loses?"), 
		_T("Verify"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
	{
		m_pGame->ResetWinsLoses();

		SendDlgItemMessage(hDlg, IDC_WINS, WM_SETTEXT, 0, (LPARAM) _T("0"));
		SendDlgItemMessage(hDlg, IDC_LOSES, WM_SETTEXT, 0, (LPARAM) _T("0"));
		SendDlgItemMessage(hDlg, IDC_PERCENTAGE, WM_SETTEXT, 0, (LPARAM) _T("--"));

		MessageBox(hDlg, _T("Wins and loses reset."), _T("Reset"), MB_ICONINFORMATION);
	}

}

LRESULT CALLBACK CMainWnd::MyStats(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
		case WM_INITDIALOG:
#ifdef UNDER_CE
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
#else
			SetDefFont(hDlg, IDOK);
			SetDefFont(hDlg, IDC_INFO_WINS);
			SetDefFont(hDlg, IDC_WINS);
			SetDefFont(hDlg, IDC_INFO_LOSES);
			SetDefFont(hDlg, IDC_LOSES);
			SetDefFont(hDlg, IDC_INFO_PERCENTAGE);
			SetDefFont(hDlg, IDC_PERCENTAGE);
			SetDefFont(hDlg, IDC_RESET);
#endif
			g_pmw->StatsInit(hDlg);
			return TRUE; 

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDOK:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			case IDC_RESET:
				g_pmw->StatsReset(hDlg);
				return TRUE;
			}
			break;
	}
    return FALSE;
}

void CMainWnd::OptionsOnInit(HWND hDlg)
{
	// Show the current settings

	if (m_pGame->GetOptEndGame())
	{
		SendDlgItemMessage(hDlg, IDC_ENDGAME, BM_SETCHECK, BST_CHECKED, 0);
	}
	if (m_pGame->GetOptGroupCards())
	{
		SendDlgItemMessage(hDlg, IDC_GROUPCARDS, BM_SETCHECK, BST_CHECKED, 0);
	}

	SendDlgItemMessage(hDlg, IDC_DIFF, CB_ADDSTRING, 0, (LPARAM) _T("Beginner"));
	SendDlgItemMessage(hDlg, IDC_DIFF, CB_ADDSTRING, 0, (LPARAM) _T("Medium"));

	SendDlgItemMessage(hDlg, IDC_DIFF, CB_SETCURSEL, 
		m_pGame->GetOptDiff() - 1, 0);
}

void CMainWnd::OptionsOnOK(HWND hDlg)
{
	// Save the state of the check box
	//  (the card selection is saved when it changes)
	if (SendDlgItemMessage(hDlg, IDC_ENDGAME, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		m_pGame->SetOptEndGame(true);
	}
	else
	{
		m_pGame->SetOptEndGame(false);
	}

	if (SendDlgItemMessage(hDlg, IDC_GROUPCARDS, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		m_pGame->SetOptGroupCards(true);
	}
	else
	{
		m_pGame->SetOptGroupCards(false);
	}

	int nDiff = SendDlgItemMessage(hDlg, IDC_DIFF, CB_GETCURSEL, 0, 0) + 1;

	if (nDiff != m_pGame->GetOptDiff())
	{
		m_pGame->SetOptDiff(nDiff);
	}

#ifndef UNDER_CE
	InvalidateRect(m_hWnd, NULL, FALSE);
	UpdateWindow(m_hWnd);
#endif
}

void CMainWnd::OptionsLButtonUp(HWND hDlg, int x, int y)
{
	// They tapped on the options dialog, see if it was on a card

	int x1 = CARD_LEFT;
	int y1 = CARD_TOP;

	int x2 = x1 + ((m_pGame->GetCardX() + (CARD_BORDER * 2)) * 6);
	int y2 = y1 + (m_pGame->GetCardY() + (CARD_BORDER * 2));

	if (x >= x1 && x <= x2 &&
		y >= y1 && y <= y2)
	{
		// yep it was, go ahead and change the selection
		m_pGame->SetOptCard( ( (x - x1) / (m_pGame->GetCardX() + (CARD_BORDER * 2)) ) + 1);
		InvalidateRect(hDlg, NULL, FALSE);
	}
}

void CMainWnd::OptionsPaint(HWND hDlg)
{
	// Paint the available cards

	int y = CARD_TOP;
	int x = CARD_LEFT;

	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hDlg, &ps);

	HPEN hPenOld;
	HBRUSH hBrushOld;
#ifdef UNDER_CE
	HPEN hPenWhite = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOW));
	xtrack(hPenWhite);
	HBRUSH hBrushWhite = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	xtrack(hBrushWhite);
#else
	HPEN hPenWhite = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNFACE));
	xtrack(hPenWhite);
	HBRUSH hBrushWhite = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	xtrack(hBrushWhite);
#endif
	
	HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	xtrack(hPenBlack);
	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0,0,0));
	xtrack(hBrushBlack);

	int i;
	for (i = 0; i < 6; i++)
	{

		if (m_pGame->GetOptCard() - 1 == i)
		{
			hPenOld = (HPEN) SelectObject(hdc, hPenBlack);
			hBrushOld = (HBRUSH) SelectObject(hdc, hBrushBlack);
		}
		else
		{
			hPenOld = (HPEN) SelectObject(hdc, hPenWhite);
			hBrushOld = (HBRUSH) SelectObject(hdc, hBrushWhite);
		}

		Rectangle(hdc, x, y, x + m_pGame->GetCardX() + ((CARD_BORDER * 2) ), 
			y + m_pGame->GetCardY() + ((CARD_BORDER * 2) ));

		SelectObject(hdc, hPenOld);
		SelectObject(hdc, hBrushOld);

		m_pGame->DrawBackCard(hdc, x + CARD_BORDER, y + CARD_BORDER, i + 1);
		x += m_pGame->GetCardX() + (CARD_BORDER * 2);
	}

	xuntrack(hPenBlack);
	DeleteObject(hPenBlack);
	xuntrack(hBrushBlack);
	DeleteObject(hBrushBlack);
	xuntrack(hPenWhite);
	DeleteObject(hPenWhite);
	xuntrack(hBrushWhite);
	DeleteObject(hBrushWhite);

	EndPaint(hDlg, &ps);
}

LRESULT CALLBACK CMainWnd::MyOptions(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	SHINITDLGINFO shidi;
#endif

	switch (message)
	{
	case WM_PAINT:
		g_pmw->OptionsPaint(hDlg);
		return TRUE;

	case WM_LBUTTONUP:
		g_pmw->OptionsLButtonUp(hDlg, LOWORD(lParam), HIWORD(lParam));
		return TRUE;

	case WM_INITDIALOG:
#ifdef UNDER_CE
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hDlg;
		SHInitDialog(&shidi);
#else
		SetDefFont(hDlg, IDOK);
		SetDefFont(hDlg, IDC_ENDGAME);
		SetDefFont(hDlg, IDC_GROUPCARDS);
		SetDefFont(hDlg, IDC_DRAWSTYLE);
		SetDefFont(hDlg, IDC_DIFF);
		SetDefFont(hDlg, IDC_DIFF_TEXT);


#endif
		g_pmw->OptionsOnInit(hDlg);
		return TRUE; 

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			g_pmw->OptionsOnOK(hDlg);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
    return FALSE;
}

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
    g_hInstance = hInstance;

	MSG			msg;
	HACCEL		hAccelTable;

	g_pmw = new CMainWnd();
	xtrack(g_pmw);

	if (!g_pmw->InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PHYLLIS);

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	xuntrack(g_pmw);
	delete g_pmw;

	xcleanup();

	return msg.wParam;
}

ATOM CMainWnd::MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass)
{
	WNDCLASS	wc;

	m_hbGreen = CreateSolidBrush(RGB(0,128,0));
	xtrack(m_hbGreen);
	HDC hdc = GetDC(0);
	m_hdcBuffer = CreateCompatibleDC(hdc);
	xtrack(m_hdcBuffer);
	m_hbBuffer = CreateCompatibleBitmap(hdc, 320, 320);
	xtrack(m_hbBuffer);
	SelectObject( m_hdcBuffer, m_hbBuffer);
	SelectObject(m_hdcBuffer, m_hbGreen);
	ReleaseDC(0, hdc);

    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHYLLIS));
#ifdef UNDER_CE
    wc.hCursor			= 0;
#else
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
#endif
    wc.hbrBackground	= (HBRUSH) m_hbGreen;
#ifdef UNDER_CE
    wc.lpszMenuName		= NULL;
#else
    wc.lpszMenuName		= MAKEINTRESOURCE(IDM_MENU);
#endif
    wc.lpszClassName	= szWindowClass;

	return RegisterClass(&wc);
}

BOOL CMainWnd::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd = NULL;
	TCHAR	szTitle[MAX_LOADSTRING];			
	TCHAR	szWindowClass[MAX_LOADSTRING];		

	m_hInst = hInstance;		
	
	LoadString(hInstance, IDC_PHYLLIS, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

#ifdef UNDER_CE
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) 
	{
		SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));
		return 0;
	} 
#endif

	MyRegisterClass(hInstance, szWindowClass);
	
	RECT	rect;
	GetClientRect(hWnd, &rect);
	
#ifdef UNDER_CE
	m_hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);
#else
	m_hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE | WS_BORDER | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 240, //240, 320, 
		NULL, NULL, hInstance, NULL);
#endif

    m_hWndInfo = CreateWindow(_T("STATIC"), _T(""), 
        WS_BORDER | WS_CHILD | SS_CENTER, 0, 0, 0, 0, m_hWnd, NULL, hInstance, NULL);

	if (!m_hWnd)
	{	
		return FALSE;
	}
	
#ifdef UNDER_CE
	{
		SHINITDLGINFO sid = {0};

		sid.dwMask = SHIDIM_FLAGS;
		sid.hDlg = m_hWnd;
		sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN | SHIDIF_SIPDOWN;

		SHInitDialog(&sid);
	}
#endif

#ifdef COMPUTER_VS_COMPUTER
#ifdef UNDER_CE
	ShowWindow(m_hWnd, nCmdShow);
#else
	ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
#endif
#else
	ShowWindow(m_hWnd, nCmdShow);
#endif
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CMainWnd::OnCommand(WORD wmId, WORD wmEvent)
{
	switch (wmId)
	{	
	case IDM_GAME_STATS:
		DialogBox(m_hInst, (LPCTSTR)IDD_STATS, m_hWnd, (DLGPROC)MyStats);
		break;
	case IDM_GAME_OPTIONS:
		DialogBox(m_hInst, (LPCTSTR)IDD_OPTIONS, m_hWnd, (DLGPROC)MyOptions);
		break;
	case IDM_HELP_ABOUT:
		DialogBox(m_hInst, (LPCTSTR)IDD_ABOUTBOX, m_hWnd, (DLGPROC)MyAbout);
		break;
	case IDM_GAME_EXIT:
		SendMessage(m_hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)m_hWnd);
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;
	case IDOK:
		SendMessage(m_hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)m_hWnd);
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		break;
	case IDM_GAME_NEW:
        if (m_pGame->GameInProgress())
        {
            if (MessageBox(m_hWnd, 
                _T("A game is currently in progress.  Are you sure you want to forfeit the game and start over?"), 
                _T("Give up?"), 
                MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES)
            {
        		m_pGame->DealNewGame();
            }

        }
        else
        {
#ifdef COMPUTER_VS_COMPUTER
			double nResults[CUR_END - CUR_START + 1];
			TCHAR sz[1000];

			for (g_nCurrentNum = CUR_START; g_nCurrentNum <= CUR_END; g_nCurrentNum ++)
			{
				sgenrand(24601);
				m_pGame->ResetWinsLoses();

				int i;
				int nTickLast = GetTickCount();
				OutputDebugString(_T(" Number Total   Wins  Loses  Percentage\n"));
				for (i = 0; i < CUR_REPS; i ++)
				{
        			m_pGame->DealNewGame();
					if (GetTickCount() - nTickLast >= 1000)
					{
						nTickLast += 1000;
						_stprintf(sz, _T(" %5d  %5d  %5d  %5d     %4.1f%%\n"), g_nCurrentNum, i, 
							m_pGame->GetWins(), m_pGame->GetLoses(),
							((double)(m_pGame->GetWins())) / 
							((double)(m_pGame->GetLoses() + m_pGame->GetWins())) * ((double)100)
							);
						OutputDebugString(sz);
					}
				}
				OutputDebugString(_T("==================================\n"));
				OutputDebugString(_T(" Number Total   Wins  Loses  Percentage\n"));

				_stprintf(sz, _T(" %5d  %5d  %5d  %5d     %4.1f%%\n"), g_nCurrentNum, i, 
					m_pGame->GetWins(), m_pGame->GetLoses(),
					((double)(m_pGame->GetWins())) / 
					((double)(m_pGame->GetLoses() + m_pGame->GetWins())) * ((double)100)
					);
            
				OutputDebugString(sz);

				nResults[g_nCurrentNum - CUR_START] = 
					((double)(m_pGame->GetWins())) / 
					((double)(m_pGame->GetLoses() + m_pGame->GetWins())) * ((double)100);
			}

			OutputDebugString(_T("==================================\n"));
			double dMax = 0;
			int nMax = 0;
			for (g_nCurrentNum = CUR_START; g_nCurrentNum <= CUR_END; g_nCurrentNum ++)
			{
				if (nResults[g_nCurrentNum - CUR_START] > dMax)
				{
					dMax = nResults[g_nCurrentNum - CUR_START];
					nMax = g_nCurrentNum;
				}
				_stprintf(sz, _T(" %5d %9.5f%%\n"), g_nCurrentNum, 
					nResults[g_nCurrentNum - CUR_START]);
				OutputDebugString(sz);
			}
			OutputDebugString(_T("----------------------------------\n"));
			_stprintf(sz, _T(" %5d %9.5f%%\n"), nMax, dMax);
			OutputDebugString(sz);

            PostMessage(m_hWnd, WM_CLOSE, 0, 0);
#else
        	m_pGame->DealNewGame();
#endif
        }
		break;
	}
	return 0;
}

LRESULT CMainWnd::OnCreate(HWND hWnd)
{
    m_bDown = false;
    m_bTipActive = false;
	m_hWnd = hWnd;

	m_pGame = new CGame();
	xtrack(m_pGame);

	m_pGame->Init(this);
	// Start a new game when we're created
#ifndef COMPUTER_VS_COMPUTER
	m_pGame->DealNewGame();
#endif

#ifdef UNDER_CE
	m_hwndCB = CreateRpCommandBar(hWnd);
    memset (&m_sai, 0, sizeof (m_sai));
    m_sai.cbSize = sizeof (m_sai);
#endif

#ifdef COMPUTER_VS_COMPUTER
    PostMessage(m_hWnd, WM_COMMAND, LOWORD(IDM_GAME_NEW), 0);
#endif
	return 0;
}

LRESULT CMainWnd::OnPaint()
{
	// Paint the whole game into a buffer and bitblt it to the
	//  screen (otherwise it's Flicker 'R Us)
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(m_hWnd, &ps);

	RECT rt;
	GetClientRect(m_hWnd, &rt);
	InflateRect(&rt, 2, 2);
	Rectangle(m_hdcBuffer, rt.left, rt.top, rt.right, rt.bottom);
	InflateRect(&rt, -2, -2);

	m_pGame->DrawIt(m_hdcBuffer, &rt);
	BitBlt(hdc, rt.left, rt.top, 
		rt.right - rt.left, rt.bottom - rt.top, 
		m_hdcBuffer, 0, 0, SRCCOPY);
	EndPaint(m_hWnd, &ps);

	return 0;
}

LRESULT CMainWnd::OnDestroy()
{
	xuntrack(m_pGame);
	delete m_pGame;

#ifdef UNDER_CE
	CommandBar_Destroy(m_hwndCB);
#endif
	PostQuitMessage(0);
	return 0;
}

LRESULT CMainWnd::OnActivate(WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	// Make the shell happier
	SHHandleWMActivate(m_hWnd, wParam, lParam, &m_sai, FALSE);
#endif
    return 0;
}

LRESULT CMainWnd::OnSettingChange(WPARAM wParam, LPARAM lParam)
{
#ifdef UNDER_CE
	// Make the shell happier
	SHHandleWMSettingChange(m_hWnd, wParam, lParam, &m_sai);
#endif
	return 0;
}

LRESULT CMainWnd::OnLButtonUp(int x, int y)
{
	ReleaseCapture();

    KillTimer(m_hWnd, TIMER_TAP_N_HOLD);
	m_bDown = false;

    if (m_bTipActive)
    {
        ShowWindow(m_hWndInfo, SW_HIDE);
    }
    else
    {
		m_ptTapped.x = x;
		m_ptTapped.y = y;
    	// Let the game know the user is trying to win
	    m_pGame->Tapped(x, y);
    }

	return 0;
}

LRESULT CMainWnd::OnEraseBkGnd()
{
	// Don't let windows erase our screen.
	return TRUE;
}

LRESULT CMainWnd::OnClose()
{
    if (m_pGame->GameInProgress())
    {
        if (MessageBox(m_hWnd, 
            _T("A game is currently in progress.  Are you sure you want to give up this game?"), 
            _T("Give up?"), 
            MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES)
        {
        	DestroyWindow(m_hWnd);
        }

    }
    else
    {
        DestroyWindow(m_hWnd);
    }

    return 0;
}

LRESULT CALLBACK CMainWnd::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
    case WM_CLOSE:
        return g_pmw->OnClose();
    case WM_LBUTTONDOWN:
        return g_pmw->OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONUP:
		return g_pmw->OnLButtonUp(LOWORD(lParam), HIWORD(lParam));
	case WM_COMMAND:
		return g_pmw->OnCommand(LOWORD(wParam), HIWORD(wParam));
	case WM_CREATE:
		return g_pmw->OnCreate(hWnd);
	case WM_PAINT:
		return g_pmw->OnPaint();
	case WM_DESTROY:
		return g_pmw->OnDestroy();
	case WM_ACTIVATE:
		return g_pmw->OnActivate(wParam, lParam);
	case WM_ERASEBKGND:
		return g_pmw->OnEraseBkGnd();
    case WM_TIMER:
        return g_pmw->OnTimer();
    case WM_MOUSEMOVE:
        return g_pmw->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
	case WM_SETTINGCHANGE:
		return g_pmw->OnSettingChange(wParam, lParam);
     	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

#ifdef UNDER_CE
HWND CMainWnd::CreateRpCommandBar(HWND hwnd)
{
	SHMENUBARINFO mbi;

	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = IDM_MENU;
	mbi.hInstRes   = m_hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;

	if (!SHCreateMenuBar(&mbi)) 
		return NULL;

	return mbi.hwndMB;
}

#endif

LRESULT CMainWnd::OnTimer()
{
    if (GetTickCount() - m_nDownTick >= 500)
    {
        TCHAR szInfo[20];
        int nNum = 0;
        if (m_pGame->IsInDraw(m_ptDown))
        {
            nNum = m_pGame->NumberOfDraw();
        }
        else if (m_pGame->IsInDiscard(m_ptDown))
        {
            nNum = m_pGame->NumberOfDiscard();
        }

        if (nNum > 0)
        {
            if (nNum == 1)
            {
                _tcscpy(szInfo, _T("1 card"));
            }
            else
            {
                _stprintf(szInfo, _T("%d cards"), nNum);
            }

            POINT ptDim;
            ptDim.x = 80;
            ptDim.y = 20;
            POINT pt;
            pt.x = m_ptDown.x - ptDim.x/2;
            pt.y = m_ptDown.y - ptDim.y;
            if (pt.y < 0)
            {
                pt.y = 0;
            }
            if (pt.x < 0)
            {
                pt.x = 0;
            }

            MoveWindow(m_hWndInfo, pt.x, pt.y, ptDim.x, ptDim.y, FALSE);
            SetWindowText(m_hWndInfo, szInfo);

            ShowWindow(m_hWndInfo, SW_SHOW);
            UpdateWindow(m_hWndInfo);
            m_bTipActive = true;
        }

        KillTimer(m_hWnd, TIMER_TAP_N_HOLD);
        
    }

    return 0;
}

LRESULT CMainWnd::OnLButtonDown(int x, int y)
{
	SetCapture(m_hWnd);

    m_bDown = true;
    m_bTipActive = false;
    m_ptDown.x = x;
    m_ptDown.y = y;
    m_nDownTick = GetTickCount();

    SetTimer(m_hWnd, TIMER_TAP_N_HOLD, 50, NULL);

    return 0;
}

LRESULT CMainWnd::OnMouseMove(int x, int y)
{
    if (!m_bTipActive)
    {
		if (abs(x - m_ptDown.x) > 4 || abs(y - m_ptDown.y) > 4)
		{
	        KillTimer(m_hWnd, TIMER_TAP_N_HOLD);
		    ShowWindow(m_hWndInfo, SW_HIDE);
		}
    }

    return 0;
}