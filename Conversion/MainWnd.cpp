#include "MainWnd.h"

TCHAR * DupeStr(TCHAR * szIn)
{
    TCHAR * szRet = (TCHAR *) malloc((_tcslen(szIn) + 1) * sizeof(TCHAR));
    _tcscpy(szRet, szIn);
    return szRet;
}

char * ConvertStr(LPWSTR szIn) 
{
    DWORD dwSize = wcslen(szIn);
    DWORD count = wcstombs(NULL, szIn, dwSize);
    char * szOut = (char *) malloc ((count + 1) * sizeof(char));
    memset(szOut, 0, ((count + 1) * sizeof(char)));
    wcstombs(szOut, szIn, dwSize);
    return szOut;
}

TCHAR * ConvertStr(LPSTR szIn)
{
	DWORD dwSize = strlen(szIn);
	DWORD count = mbstowcs(NULL, szIn, dwSize);
	TCHAR * szOut = (TCHAR *) malloc ((count + 1) * sizeof(TCHAR));
	memset(szOut, 0, ((count + 1) * sizeof(TCHAR)));
	mbstowcs(szOut, szIn, dwSize);
	return szOut;
}


CMainWnd::CMainWnd()
{
    m_sai.cbSize = sizeof(SHACTIVATEINFO);

    MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) this, NULL);
}

CMainWnd::~CMainWnd()
{
	MainWndProc ( NULL, WM_USER_OBJECT, (WPARAM) NULL, NULL);
}

void CMainWnd::DestroyMutex()
{
    CloseHandle(m_hMutex);
}

BOOL CMainWnd::PrevInst()
{
	m_hMutex = CreateMutex(NULL, TRUE, MAINWND_GUID);

	return (GetLastError() == ERROR_ALREADY_EXISTS);
}

HWND CMainWnd::Create(HINSTANCE hInstance)
{
	HWND		hWnd;
	WNDCLASS	wndclass;

	m_hInstance = hInstance;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = MainWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
	wndclass.lpszMenuName = NULL; 
	wndclass.lpszClassName = MAINWND_CLASS;

	RegisterClass ( &wndclass );

	hWnd = CreateWindowEx (NULL, MAINWND_CLASS, MAINWND_TITLE, 
		WS_VISIBLE, 
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);

	return hWnd;
}

LRESULT CMainWnd::OnSize(WORD x, WORD y)
{
	MoveWindow(m_DlgWnd.GetHwnd(), 0, 0, x, y, TRUE);

    return 0;
}

LRESULT CALLBACK CMainWnd::MainWndProc ( HWND hWnd, UINT iMsg, 
   WPARAM wParam, LPARAM lParam)
{

	static CMainWnd * parent = (CMainWnd *) NULL;

	if (iMsg == WM_USER_OBJECT)
    {
		parent = (CMainWnd *) wParam;
		return 0;
	}
    else if ( parent != NULL )
    {
		switch (iMsg)
        {
        case WM_COMMAND :
            return parent->OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND) lParam);
            break;
		case WM_CREATE :
			parent->m_hWnd = hWnd;
			return parent->OnCreate();
		case WM_CLOSE :
			return parent->OnClose();
		case WM_DESTROY :
			return parent->OnDestroy();
        case WM_SIZE :
            return parent->OnSize(LOWORD(lParam), HIWORD(lParam));
        case WM_ACTIVATE: 
            SHHandleWMActivate(hWnd, wParam, lParam, &parent->m_sai, 0); 
            break;
        case WM_SETTINGCHANGE: 
            SHHandleWMSettingChange(hWnd, wParam, lParam, &parent->m_sai);
            break; 
		}
	}

	return DefWindowProc (hWnd, iMsg, wParam, lParam);
}

LRESULT CMainWnd::OnClose()
{

	DestroyWindow(m_hWnd);

	return 0;

}

LRESULT CMainWnd::OnDestroy()
{

	PostQuitMessage(0);

	return 0;
}

void CMainWnd::ImportData(char * szData)
{

	m_cTypes = 0;
	char szTempType[10];
	char szTempName[100];
	char szTempValue[100];

	int nPosType = 0;
	int nPosName = 0;
	int nPosValue = 0;
    bool bSkip = false;

	szTempType[0] = 0;
	szTempName[0] = 0;
	szTempValue[0] = 0;

	int nCurType = 0;

	int i;
	for (i = 0; i < (signed) strlen(szData); i++)
    {
		switch (szData[i])
        {
		case '\r':
			break;
		case ':':
			nCurType ++;
			break;
		case '\n':
			if (nCurType == 2)
            {

				szTempType[nPosType] = 0;
				szTempName[nPosName] = 0;
				szTempValue[nPosValue] = 0;

				switch (szTempType[0])
                {
				case '1':
					m_Types[m_cTypes].cUnits = 0;
					m_Types[m_cTypes].nID = atoi(szTempValue);
					m_Types[m_cTypes].szName = ConvertStr(szTempName);
					m_cTypes ++;
                    if (_tcsncmp(m_Types[m_cTypes-1].szName, _T("Money ("), 7) == 0)
                    {
                        bSkip = LoadMoneyFile();
                    }
                    else
                    {
                        bSkip = false;
                    }
					break;
				case '2':
                    if (!bSkip)
                    {
					    m_Types[m_cTypes-1].szUnits[m_Types[m_cTypes-1].cUnits] = ConvertStr(szTempName);
					    #ifdef POCKET_PC
						    m_Types[m_cTypes-1].fUnits[m_Types[m_cTypes-1].cUnits] = atof(szTempValue);
					    #else
						    float fTemp;
						    double fTemp2;
						    sscanf(szTempValue, "%g", &fTemp);
						    fTemp2 = fTemp;
						    m_Types[m_cTypes-1].fUnits[m_Types[m_cTypes-1].cUnits] = fTemp2;
					    #endif
    
					    m_Types[m_cTypes-1].cUnits ++;
                    }
					break;
				}
				nPosType = 0;
				nPosName = 0;
				nPosValue = 0;
				nCurType = 0;
			}
			break;
		default:
			switch (nCurType)
            {
			case 0:
				szTempType[nPosType] = szData[i];
				nPosType ++;
				break;
			case 1:
				szTempValue[nPosValue] = szData[i];
				nPosValue ++;
				break;
			case 2:
				szTempName[nPosName] = szData[i];
				nPosName ++;
				break;
			}
			break;

		}

	}

}

LRESULT CMainWnd::OnCreate()
{
	HRSRC hrConv = FindResource(m_hInstance, 
		MAKEINTRESOURCE(IDR_CONVERSIONS), MAKEINTRESOURCE(ID_CUSTOM));

	HGLOBAL hgConv = LoadResource(m_hInstance, hrConv);
	char * szConv = (char *) LockResource(hgConv);

	ImportData(szConv);

	ShowWindow (m_hWnd, SW_SHOW);
	UpdateWindow (m_hWnd);

	int nCmdHeight = 0;
	RECT rect;

#ifdef POCKET_PC
	SHMENUBARINFO mbi = {0};
	mbi.cbSize = sizeof(SHMENUBARINFO);
	mbi.dwFlags = 0;
	mbi.hInstRes = m_hInstance;
	mbi.hwndParent = m_hWnd;
	mbi.nToolBarId = IDR_MAIN_TOOLBAR;
	mbi.nBmpId = 0;
	mbi.cBmpImages = 0;
	SHCreateMenuBar(&mbi);

	GetWindowRect(mbi.hwndMB, &rect);
	nCmdHeight = rect.bottom - rect.top;
#endif

	GetClientRect(m_hWnd, &rect);

	m_DlgWnd.Init(m_hInstance, m_hWnd, this);

	MoveWindow(m_DlgWnd.GetHwnd(), rect.left, rect.top, 
		rect.right-rect.left, rect.bottom-rect.top-nCmdHeight, TRUE);
	ShowWindow(m_DlgWnd.GetHwnd(), SW_SHOW);


	return 0;
}

LRESULT CMainWnd::OnCommand(WORD wNotifyCode, WORD wID, HWND /* hwndCtrl */)
{
    switch(wNotifyCode)
    {
    case 0:
    case 1:
        switch(wID)
        {
        case IDM_ABOUT:
            {
                MessageBox(m_hWnd, 
                    _T("Conversions v") VERSION_TEXT 
                    _T("\nby Scott Seligman\n\n<scott@\n  scottandmichelle.net>"), 
                    _T("Conversions"), 
                    MB_ICONINFORMATION);
            }
            break;

        case IDM_SWAP:
            m_DlgWnd.Swap();
            break;

        case IDM_UPDATE:
            m_DlgWnd.UpdateMoney();
            break;

        case IDM_EXIT:
            PostMessage(m_hWnd, WM_CLOSE, 0, 0);
            break;
        }
        break;
    }

    return 0;

}

HWND CMainWnd::GetHwnd()
{
    return m_hWnd;
}

void CMainWnd::CleanXML(TCHAR * szData)
{
    while (*szData && *szData != _T('>'))
    {
        if (*szData == _T('\''))
        {
            *szData = 0;
        }
        szData ++;
    }
}

TCHAR * CMainWnd::GetCurName(TCHAR * szName)
{
#define AbbrToDWORD(z) ((DWORD)((DWORD)(*z) + ((DWORD)(*(z + 1)) << 8) + ((DWORD)(*(z + 2)) << 16)))
#define CharToDWORD(a, b, c) ((((DWORD)a)) + (((DWORD)b) << 8) + (((DWORD)c) << 16))

    switch (AbbrToDWORD(szName))
    {
    case CharToDWORD('A','U','D'): return DupeStr(_T("Australian dollar (AUD)"));
    case CharToDWORD('B','G','N'): return DupeStr(_T("Bulgarian lev (BGN)"));
    case CharToDWORD('B','R','L'): return DupeStr(_T("Brasilian real (BRL)"));
    case CharToDWORD('C','A','D'): return DupeStr(_T("Canadian dollar (CAD)"));
    case CharToDWORD('C','H','F'): return DupeStr(_T("Swiss franc (CHF)"));
    case CharToDWORD('C','N','Y'): return DupeStr(_T("Chinese yuan renminbi (CNY)"));
    case CharToDWORD('C','Y','P'): return DupeStr(_T("Cyprus pound (CYP)"));
    case CharToDWORD('C','Z','K'): return DupeStr(_T("Czech koruna (CZK)"));
    case CharToDWORD('D','K','K'): return DupeStr(_T("Danish krone (DKK)"));
    case CharToDWORD('E','E','K'): return DupeStr(_T("Estonian kroon (EEK)"));
    case CharToDWORD('G','B','P'): return DupeStr(_T("Pound sterling (GBP)"));
    case CharToDWORD('H','K','D'): return DupeStr(_T("Hong Kong dollar (HKD)"));
    case CharToDWORD('H','R','K'): return DupeStr(_T("Croatian kuna (HRK)"));
    case CharToDWORD('H','U','F'): return DupeStr(_T("Hungarian forint (HUF)"));
    case CharToDWORD('I','D','R'): return DupeStr(_T("Indonesian rupiah (IDR)"));
    case CharToDWORD('I','S','K'): return DupeStr(_T("Icelandic krona (ISK)"));
    case CharToDWORD('J','P','Y'): return DupeStr(_T("Japanese yen (JPY)"));
    case CharToDWORD('K','R','W'): return DupeStr(_T("South Korean won (KRW)"));
    case CharToDWORD('L','T','L'): return DupeStr(_T("Lithuanian litas (LTL)"));
    case CharToDWORD('L','V','L'): return DupeStr(_T("Latvian lats (LVL)"));
    case CharToDWORD('M','T','L'): return DupeStr(_T("Maltese lira (MTL)"));
    case CharToDWORD('M','X','N'): return DupeStr(_T("Mexican peso (MXN)"));
    case CharToDWORD('M','Y','R'): return DupeStr(_T("Malaysian ringgit (MYR)"));
    case CharToDWORD('N','O','K'): return DupeStr(_T("Norwegian krone (NOK)"));
    case CharToDWORD('N','Z','D'): return DupeStr(_T("New Zealand dollar (NZD)"));
    case CharToDWORD('P','H','P'): return DupeStr(_T("Philippine peso (PHP)"));
    case CharToDWORD('P','L','N'): return DupeStr(_T("Polish zloty (PLN)"));
    case CharToDWORD('R','O','L'): return DupeStr(_T("Romanian leu (ROL)"));
    case CharToDWORD('R','O','N'): return DupeStr(_T("New Romanian leu (RON)"));
    case CharToDWORD('R','U','B'): return DupeStr(_T("Russian rouble (RUB)"));
    case CharToDWORD('S','E','K'): return DupeStr(_T("Swedish krona (SEK)"));
    case CharToDWORD('S','G','D'): return DupeStr(_T("Singapore dollar (SGD)"));
    case CharToDWORD('S','I','T'): return DupeStr(_T("Slovenian tolar (SIT)"));
    case CharToDWORD('S','K','K'): return DupeStr(_T("Slovakian koruna (SKK)"));
    case CharToDWORD('T','H','B'): return DupeStr(_T("Thai baht (THB)"));
    case CharToDWORD('T','R','L'): return DupeStr(_T("Turkish lira (TRL)"));
    case CharToDWORD('T','R','Y'): return DupeStr(_T("New Turkish lira (TRY)"));
    case CharToDWORD('U','S','D'): return DupeStr(_T("US dollar (USD)"));
    case CharToDWORD('Z','A','R'): return DupeStr(_T("South African rand (ZAR)"));
    default:
        return DupeStr(szName);
    }
}
                   
bool CMainWnd::LoadMoneyFile()
{
    TCHAR * szFile = (TCHAR *) malloc(10000 * 2);
    TCHAR * szOrigFile = szFile;
    TCHAR szName[MAX_PATH];
    GetFile(szName);
    HANDLE hFile = CreateFile(szName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        free(szFile);
        return false;
    }
    DWORD dwSize = GetFileSize(hFile, NULL);
    if (dwSize == 0)
    {
        free(szFile);
        return false;
    }
    DWORD dwRead = 0;
    ReadFile(hFile, szFile, dwSize, &dwRead, NULL);
    if (dwRead != dwSize)
    {
        free(szFile);
        return false;
    }
    CloseHandle(hFile);

    TCHAR szTemp[100];
    int nLeft = _tcslen(szFile);

    while (nLeft > 0)
    {
        if (_tcsnicmp(szFile, _T("<Cube time='"), 12) == 0)
        {
            szFile += 12;
            CleanXML(szFile);

            _tcscpy(szTemp, _T("Money ("));
            _tcscat(szTemp, szFile);
            _tcscat(szTemp, _T(")"));

            free(m_Types[m_cTypes-1].szName);
			m_Types[m_cTypes-1].szName = DupeStr(szTemp);

            m_Types[m_cTypes-1].szUnits[m_Types[m_cTypes-1].cUnits] = DupeStr(_T("Euro (EUR)"));
            m_Types[m_cTypes-1].fUnits[m_Types[m_cTypes-1].cUnits] = 1;
            m_Types[m_cTypes-1].cUnits ++;

        }
        else if (_tcsnicmp(szFile, _T("<Cube currency='"), 16) == 0)
        {
            szFile += 16;
            CleanXML(szFile);

            m_Types[m_cTypes-1].szUnits[m_Types[m_cTypes-1].cUnits] = GetCurName(szFile);
            szFile += 11;
            char * szVal = ConvertStr(szFile);
            m_Types[m_cTypes-1].fUnits[m_Types[m_cTypes-1].cUnits] = 1.0/atof(szVal);
            m_Types[m_cTypes-1].cUnits ++;
        }
        szFile ++;
        nLeft --;
    }

    free(szOrigFile);
    return true;
}

