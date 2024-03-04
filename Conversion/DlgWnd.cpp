#include "DlgWnd.h"
#include "Commctrl.h"
#include <Commctrl.h>
#include "wininet.h"

#define ShowHourglass	SetCursor (LoadCursor (NULL, IDC_WAIT))
#define HideHourglass	SetCursor (LoadCursor (NULL, 0))

#include "Eval.h"
#include "Reg.h"

extern bool g_bReLaunch;

void CDlgWnd::Init(HINSTANCE hInstance, HWND hWnd, CMainWnd * parent)
{

	m_hInstance = hInstance;
	m_parent = parent;

	m_hWnd = CreateDialogParam(hInstance, 
			MAKEINTRESOURCE(IDD_MAIN), 
			hWnd, 
			(DLGPROC)DlgProc, 
			(LPARAM)this);
}

CDlgWnd::~CDlgWnd()
{
	DestroyWindow(m_hWnd);
}

CDlgWnd::CDlgWnd()
{
}

HWND CDlgWnd::GetHwnd()
{
	return m_hWnd;
}

void CDlgWnd::OnInitDialog()
{
	for (int i = 0; i < m_parent->m_cTypes; i++)
    {
		SendDlgItemMessage(m_hWnd, IDC_UNIT, CB_ADDSTRING, 0, (LPARAM) m_parent->m_Types[i].szName);
	}

    SendDlgItemMessage(m_hWnd, IDC_UNIT, CB_SETCURSEL, g_Reg.GetUnit(), 0);
    OnUnitSelChange();
    SendDlgItemMessage(m_hWnd, IDC_FROM, CB_SETCURSEL, g_Reg.GetFrom(), 0);
    SendDlgItemMessage(m_hWnd, IDC_TO, CB_SETCURSEL, g_Reg.GetTo(), 0);
    OnFromToChange();
}

void CDlgWnd::OnUnitSelChange()
{
	m_nCurSel = SendDlgItemMessage(m_hWnd, IDC_UNIT, CB_GETCURSEL, 0, 0);
    if (m_nCurSel == CB_ERR)
    {
        return;
    }
    g_Reg.SetUnit(m_nCurSel);

	SendDlgItemMessage(m_hWnd, IDC_FROM, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(m_hWnd, IDC_TO, CB_RESETCONTENT, 0, 0);

	SendDlgItemMessage(m_hWnd, IDC_FROM_EDIT, WM_SETTEXT, 0, (LPARAM) L"1");
	SendDlgItemMessage(m_hWnd, IDC_TO_EDIT, WM_SETTEXT, 0, (LPARAM) L"1");

	for (int i = 0; i < m_parent->m_Types[m_nCurSel].cUnits; i++)
    {
		SendDlgItemMessage(m_hWnd, IDC_FROM, CB_ADDSTRING, 0, (LPARAM) m_parent->m_Types[m_nCurSel].szUnits[i] );
		SendDlgItemMessage(m_hWnd, IDC_TO, CB_ADDSTRING, 0, (LPARAM) m_parent->m_Types[m_nCurSel].szUnits[i] );
	}
}

void CDlgWnd::Swap()
{
	int nFrom = SendDlgItemMessage(m_hWnd, IDC_FROM, CB_GETCURSEL, 0, 0);
	int nTo = SendDlgItemMessage(m_hWnd, IDC_TO, CB_GETCURSEL, 0, 0);

	SendDlgItemMessage(m_hWnd, IDC_FROM, CB_SETCURSEL, nTo, 0);
	SendDlgItemMessage(m_hWnd, IDC_TO, CB_SETCURSEL, nFrom, 0);

    OnFromToChange();
}

void CDlgWnd::OnFromToChange()
{
	int nFrom = SendDlgItemMessage(m_hWnd, IDC_FROM, CB_GETCURSEL, 0 ,0);
	int nTo = SendDlgItemMessage(m_hWnd, IDC_TO, CB_GETCURSEL, 0 ,0);

	if (nFrom == CB_ERR)
    {
		return;
	}

    g_Reg.SetFrom(nFrom);

	if (nTo == CB_ERR)
    {
		return;
	}
    g_Reg.SetTo(nTo);

	TCHAR szTemp[255];

	SendDlgItemMessage(m_hWnd, IDC_FROM_EDIT, WM_GETTEXT, 255, (LPARAM) szTemp);

	double nValue = EvalExp(szTemp);
	double nOut = 0;

	switch (m_parent->m_Types[m_nCurSel].nID)
    {
	case 1:
		nOut = nValue * m_parent->m_Types[m_nCurSel].fUnits[nFrom] / 
			m_parent->m_Types[m_nCurSel].fUnits[nTo];
		break;
	case 2:

		switch (nFrom)
        {
		case 0:
			nOut = nValue + 273.15;
			break;
		case 1:
			nOut = (5.0/9.0) * (nValue + 459.67);
			break;
		case 2:
			nOut = nValue;
			break;
		case 3:
			nOut = (5.0/9.0) * nValue;
			break;
		case 4:
			nOut = ((4.0/5.0) * nValue) + 273.15;
			break;
		}
		switch (nTo)
        {
		case 0:
			nOut = nOut - 273.15;
			break;
		case 1:
			nOut = ((9.0/5.0) * nOut) - 459.67;
			break;
		case 2:
			nOut = nOut;
			break;
		case 3:
			nOut = (9.0/5.0) * nOut;
			break;
		case 4:
			nOut = (5.0/4.0) * (nOut - 273.15);
			break;
		}
		break;
	}

	wsprintf(szTemp, L"%f", nOut);

	SendDlgItemMessage(m_hWnd, IDC_TO_EDIT, WM_SETTEXT, 0, (LPARAM) szTemp);
}

long __stdcall CDlgWnd::DlgProc(struct HWND__ * hDlg, unsigned int uMsg, unsigned int wParam, long lParam)
{

	static CDlgWnd * parent;

	switch (uMsg)
    {
	case WM_INITDIALOG:
		parent = (CDlgWnd *) lParam;
		parent->m_hWnd = hDlg;

		parent->OnInitDialog();

		break;

    case WM_SIZE:
        parent->OnSize(LOWORD(lParam), HIWORD(lParam));
        break;

	case WM_COMMAND:
		switch (HIWORD(wParam))
        {
		case EN_CHANGE:
		case CBN_SELCHANGE:
			switch (LOWORD(wParam))
            {
			case IDC_UNIT:
				parent->OnUnitSelChange();
				break;
			case IDC_FROM:
			case IDC_TO:
			case IDC_FROM_EDIT:
				parent->OnFromToChange();
			}
			break;
		default:
			switch (LOWORD (wParam))
            {
			case IDOK:
				EndDialog(hDlg, IDOK);
				return true;
			case IDCANCEL:
				EndDialog(hDlg, IDCANCEL);
				return true;
			}
			break;
		}
		break;
	default:
		return false;

	}
	return true;			
}

bool CDlgWnd::ReadXMLData()
{
	#define ShowError(err) MessageBox( \
		m_hWnd, \
		_T("There was an error reading the data from site: \"") \
		 err _T("\""), \
		_T("Conversions Error"), \
		MB_ICONERROR)

	bool bGoodData = true;	
	HINTERNET hInetOpen = NULL;
	HINTERNET hSession = NULL;
	HINTERNET hRequest = NULL;

	hInetOpen = InternetOpen(_T("Conversions"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hInetOpen == NULL)
	{
		ShowError(_T("InternetOpen Failed"));
		bGoodData = false;
	}

	if (bGoodData)
	{
		hSession = InternetConnect(hInetOpen, _T("www.ecb.int"),
			INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP,
			0, 0);

		if(hSession == NULL)
		{
			ShowError(_T("InternetConnect Failed"));
			bGoodData = false;
		}
	}

	if (bGoodData)
	{
		hRequest = HttpOpenRequest(hSession, _T("GET\0"), _T("/stats/eurofxref/eurofxref-daily.xml"),
			NULL, NULL, NULL, 0, 0);

		if(hRequest == NULL)
		{
			ShowError(_T("InternetRequest Failed"));
			bGoodData = false;
		}
	}

	if (bGoodData)
	{
		if(!HttpSendRequest(hRequest, NULL, 0, NULL, 0))
		{
			ShowError(_T("HttpSendRequest Failed"));
			bGoodData = false;
		}
	}

	DWORD numOfBytesAvbl;
    char * szData = (char *) malloc(10000);
	int nLeft = 10000;
	char * szCur = szData;

	if (bGoodData)
	{
		do
		{
			if (bGoodData)
			{
				if(!(InternetQueryDataAvailable( hRequest, &numOfBytesAvbl, 0, 0 )))
				{
					numOfBytesAvbl = 0;
					ShowError(_T("InternetQueryDataAvailable"));
					bGoodData = false;
				}
			}
			if ((signed) numOfBytesAvbl > nLeft)
			{
				ShowError(_T("Too much data received"));
				bGoodData = false;
				numOfBytesAvbl = 0;
			}
			if (bGoodData)
			{
				DWORD dwRead;
				if(!InternetReadFile(hRequest, szCur, numOfBytesAvbl, &dwRead))
				{
					numOfBytesAvbl = 0;
					ShowError(_T("Could not Read File"));
					bGoodData = false;
				}
				else
				{
					szCur += dwRead;
					nLeft -= dwRead;
				}   
			}
		} while (bGoodData && numOfBytesAvbl > 0);
	}

	if (bGoodData)
	{
        TCHAR * sz2 = (TCHAR *) malloc(10000 * 2);
        _stprintf(sz2, _T("%S"), szData);

        DWORD dwWrote = 0;
        TCHAR szFile[MAX_PATH];
        GetFile(szFile);

        HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, 
            NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        WriteFile(hFile, sz2, _tcslen(sz2) * sizeof TCHAR, &dwWrote, NULL);

        CloseHandle(hFile);

        free(sz2);

	}

	InternetCloseHandle(hRequest);
	InternetCloseHandle(hSession);
	InternetCloseHandle(hInetOpen);
    free(szData);

    return bGoodData;

}

void CDlgWnd::UpdateMoney()
{
    bool bRet = false;
    ShowHourglass;
    bRet = ReadXMLData();
    HideHourglass;

    if (bRet)
    {
        MessageBox(m_hWnd, _T("New data downloaded, Conversions will now close and re-open"), _T("Done"), MB_ICONINFORMATION);
        g_bReLaunch = true;
        PostMessage(m_parent->GetHwnd(), WM_CLOSE, 0, 0);
    }
}

void CDlgWnd::OnSize(WORD x, WORD y)
{
    UINT uiControls[] = {IDC_UNIT, IDC_FROM, IDC_TO, IDC_FROM_EDIT, IDC_TO_EDIT};
    bool bSmaller[] = {false, false, false, true, true};

    POINT pt;
    pt.x = 0;
    pt.y = 0;
    ScreenToClient(m_hWnd, &pt);

    for (int i = 0; i < sizeof(uiControls) / sizeof(UINT); i ++)
    {
        RECT rt;
        GetWindowRect(GetDlgItem(m_hWnd, uiControls[i]), &rt);
        OffsetRect(&rt, pt.x, pt.y);
        int nWidth = x - (rt.left * 2);
        if (bSmaller[i])
        {
            nWidth = (int)(((double)nWidth)*0.80);
        }
        MoveWindow(GetDlgItem(m_hWnd, uiControls[i]), 
            rt.left, rt.top, nWidth, rt.bottom - rt.top, TRUE);
    }

}