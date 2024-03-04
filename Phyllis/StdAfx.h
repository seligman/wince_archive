// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DB0D178F_EE1E_42C5_8F88_40BB216C96BD__INCLUDED_)
#define AFX_STDAFX_H__DB0D178F_EE1E_42C5_8F88_40BB216C96BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef UNDER_CE
#if (_WIN32_WCE <= 211)
#error This project can not be built for H/PC Pro 2.11 or earlier platforms.
#endif
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>
#ifndef UNDER_CE
#include <tchar.h>
#define ASSERT(a) (void())
#endif


// Local Header Files
#include "Tracker.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DB0D178F_EE1E_42C5_8F88_40BB216C96BD__INCLUDED_)
