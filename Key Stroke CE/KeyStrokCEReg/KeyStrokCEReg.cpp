// KeyStrokCEReg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#define CREATE_KEY(b,d) 	RegCreateKeyEx(HKEY_CLASSES_ROOT,\
								b,\
								NULL,NULL,0,KEY_ALL_ACCESS,NULL,&hk,&dw);\
							memset(&sz,0,100);\
							_tcscpy((TCHAR*)&sz,\
								d\
								);\
							RegSetValueEx(hk,L"",0,REG_SZ,(const unsigned char*) &sz,_tcslen(sz)*2+2);\
							RegCloseKey(hk);


int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	HKEY hk;
	DWORD dw;
	TCHAR sz[100] = L"";

	CREATE_KEY(
		L"CLSID\\{E74C82A5-22A0-11d4-B859-00B0D040070E}",
		L"Key Stroke CE")

	CREATE_KEY(
		L"CLSID\\{E74C82A5-22A0-11d4-B859-00B0D040070E}\\DefaultIcon",
		L"\\windows\\KeyStrokeCE.dll,0")

	CREATE_KEY(
		L"CLSID\\{E74C82A5-22A0-11d4-B859-00B0D040070E}\\InprocServer32",
		L"\\windows\\KeyStrokeCE.dll")

	CREATE_KEY(
		L"CLSID\\{E74C82A5-22A0-11d4-B859-00B0D040070E}\\IsSIPInputMethod",
		L"1")

	MessageBox(0, L"Creation of registry keys for Key Stroke CE complete.", L"KeyStrokeCE", MB_ICONINFORMATION);

	return 0;
}

