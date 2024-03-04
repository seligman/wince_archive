#include "stdafx.h"
#include "Registry.h"

#ifndef UNDER_CE
#include <malloc.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// Implememtation of CRegistryKey 
// 

CRegistryKey::CRegistryKey(HKEY hkeyBranch, LPTSTR szPath) {
	m_bOpen = FALSE;

	DWORD				dwDisposition;
	LONG				lResult;

#ifdef UNDER_CE
	lResult = RegCreateKeyEx(
		hkeyBranch,
		szPath,
		0,
		_T(""),
		0,
		0,
		NULL,
		&m_hkeyItem,
		&dwDisposition);
#else
	lResult = RegCreateKeyEx(
		hkeyBranch, 
		szPath, 
		0, 
		REG_NONE,
		REG_OPTION_NON_VOLATILE, 
		KEY_WRITE|KEY_READ, 
		NULL,
		&m_hkeyItem, 
		&dwDisposition);
#endif

	m_bOpen = (lResult == ERROR_SUCCESS);
}

BOOL CRegistryKey::SetRegValue(const LPTSTR szName, LPTSTR szData) {
	if (!m_bOpen) {
		return FALSE;
	}

	DWORD	dwReserved = 0;
	LONG	lResult;

	lResult = RegSetValueEx(
		m_hkeyItem,
		szName,
		dwReserved,
		REG_SZ,
		(const unsigned char *) szData,
		_tcslen(szData) + 1);

	return (lResult == ERROR_SUCCESS);
}

BOOL CRegistryKey::GetRegValue(const LPTSTR szName, LPTSTR szData) {
	if (!m_bOpen) {
		return FALSE;
	}

	DWORD			dwReserved = 0;
	DWORD			dwType = 0;
	LONG			lResult;
	LPTSTR			szBuffer;
	DWORD			dwBufferLen;

	lResult = RegQueryValueEx(
		m_hkeyItem,
		szName,
		&dwReserved,
		&dwType,
		NULL,
		&dwBufferLen);

	if (dwBufferLen == 0) {
		return FALSE;
	}

	szBuffer = (LPTSTR) malloc (dwBufferLen * sizeof(TCHAR));
	_tcscpy(szBuffer, _T(""));

	lResult = RegQueryValueEx(
		m_hkeyItem,
		szName,
		&dwReserved,
		&dwType,
		(unsigned char *) szBuffer,
		&dwBufferLen);

	if ((lResult == ERROR_SUCCESS) & (dwType == REG_SZ)) {
		szData = szBuffer;
		free (szBuffer);

		return TRUE;
	} else {
		if (dwBufferLen > 0) {
			free (szBuffer);
		}

		return FALSE;
	}

}

BOOL CRegistryKey::SetRegValueDW(const LPTSTR szName, DWORD &dwData) {
	if (!m_bOpen) {
		return FALSE;
	}

	DWORD	dwReserved = 0;
	LONG	lResult;

	lResult = RegSetValueEx(
		m_hkeyItem,
		szName,
		dwReserved,
		REG_DWORD,
		(const unsigned char *) &dwData,
		sizeof(dwData));

	return (lResult == ERROR_SUCCESS);
}

BOOL CRegistryKey::GetRegValueDW(const LPTSTR szName, DWORD &dwData) {
	if (!m_bOpen) {
		return FALSE;
	}

	DWORD			dwReserved = 0;
	DWORD			dwType = 0;
	LONG			lResult;
	DWORD			dwBufferLen = sizeof(dwData);

	lResult = RegQueryValueEx(
		m_hkeyItem,
		szName,
		0,
		&dwType,
		NULL,
		&dwBufferLen);

	if (dwType != REG_DWORD) {
		return FALSE;
	}

	lResult = RegQueryValueEx(
		m_hkeyItem,
		szName,
		0,
		&dwType,
		(unsigned char *) &dwData,
		&dwBufferLen);

	if ((lResult == ERROR_SUCCESS) & (dwType == REG_DWORD)) {
		return TRUE;
	} else {
		return FALSE;
	}

}

CRegistryKey::~CRegistryKey() {

	if (m_bOpen) {
		RegCloseKey(m_hkeyItem);
	}

}

