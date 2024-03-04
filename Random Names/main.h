#pragma once

#ifdef UNDER_CE
#pragma warning ( disable : 4201 )
#pragma warning ( disable : 4514 )
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

#ifndef UNDER_CE
//#define _T(f)			f
//#define _tcslen(f)		strlen(f)
//#define _tcscpy(f,g)	strcpy(f,g)
#include "tchar.h"
#endif

#define MAINWND_GUID	_T("{1A572760-485F-11d4-B860-00B0D040070E}")
#define MAINWND_CLASS	_T("RandNamesClass")
#define MAINWND_TITLE	_T("Random Names")

#define WM_USER_OBJECT	(WM_USER + 10)

extern HINSTANCE g_hInstance;

#define COUNT_LASTNAMES		1140
#define COUNT_MALE			1006
#define COUNT_FEMALE		1003
