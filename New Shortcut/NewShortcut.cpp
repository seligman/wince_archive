// NewShortcut.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include "resource.h"

#define CF_FILE		52224 //e-115
#define CF_FILE2	52237 //ipaq
#define CF_FILE3	49939 //ce emu


int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
 	// TODO: Place code here.
	MessageBox(0, L"Debug test version 3.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);

	if (!OpenClipboard(0)) {
		MessageBox(0, L"Unable to open the clipboard.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);
		return 0;
	}

	UINT nFormat = EnumClipboardFormats(0);
	UINT nFormatFound = 0;
	bool bFound = false;
	while (nFormat != 0) {
		TCHAR sz[100];
		wsprintf(sz, L"%d", nFormat);
//		MessageBox(0, sz, L"zz", MB_TOPMOST);
		if (nFormat == CF_FILE || nFormat == CF_FILE2 || nFormat == CF_FILE3) {
			bFound = true;
			nFormatFound = nFormat;
			nFormat = 0;
		} else {
			nFormat = EnumClipboardFormats(nFormat);
		}
	}

	if (!bFound) {
		MessageBox(0, L"Can't find a file in the clipboard.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);
		return 0;
	}

//	HANDLE hMem = GetClipboardData(CF_FILE);
	HANDLE hMem = GetClipboardData(nFormat);
	if (hMem == 0) {
		MessageBox(0, L"Unable to get the clipboard data.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);
		return 0;
	}

	int nSize = LocalSize(hMem);
	char * pData = (char *) hMem;

	DWORD dw11 =  0;
	HANDLE hf1 = CreateFile(L"\\New Shortcut.dat",GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(hf1, pData, nSize, &dw11, NULL);
	CloseHandle(hf1);
	MessageBox(0, L"data written to file.", L"New Shortcut", MB_TOPMOST);

	int nPos = 0;
	int nStart = 0;
	for (nPos = nSize-6; nPos > 0; nPos --) {
		if (pData[nPos] == 1) {
			nStart = nPos + 1;
			nPos = 0;
		}
	}

	if (nStart == 0) {
		MessageBox(0, L"Unable to parse the file data.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);
		return 0;
	}

	TCHAR * szFile = (TCHAR*) (pData + nStart);

	if (_tcslen(szFile) == 0) {
		MessageBox(0, L"Unable to parse the file data.", L"New Shortcut", MB_TOPMOST | MB_ICONEXCLAMATION);
		return 0;
	}

	//MessageBox(0, szFile, L"test", MB_TOPMOST);

	TCHAR szOut[2048];
	TCHAR szFinal[2048];
	wsprintf(szOut, L"%d#\"%s\"",_tcslen(szFile)+2, szFile);
	wsprintf(szFinal, L"A new shortcut has been placed in the root directory as\n\n\"New Shortcut\"\n\npointing to the file\n\n\"%s\"",szFile);

	char szOut2[2048];
	int nOutSize = wcstombs(szOut2, szOut, 2048);

	HANDLE hf = CreateFile(L"\\New Shortcut.lnk",GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	DWORD dw1 = 0;
	WriteFile(hf, szOut2, nOutSize, &dw1, NULL);
	CloseHandle(hf);

	MessageBox(0, szFinal, L"New Shortcut", MB_TOPMOST);

	CloseClipboard();

	return 0;
}

