#include "main.h"

#ifndef REGISTRY_H__AE5DA2A0_3098_11d2_BABB_00104B0FDC01__INCLUDED__
#define REGISTRY_H__AE5DA2A0_3098_11d2_BABB_00104B0FDC01__INCLUDED__

/////////////////////////////////////////////////////////////////////////////
// CRegistryKey - To read and write from one registry key
// 

class CRegistryKey {
public:

			CRegistryKey(
				HKEY hkeyBranch, // The major branch to use
				LPTSTR szPath   // The remaining path to the key
				);

			~CRegistryKey();

	BOOL	SetRegValue(const LPTSTR szName, LPTSTR szData);
	BOOL	GetRegValue(const LPTSTR szName, LPTSTR szData);

	BOOL	SetRegValueDW(const LPTSTR szName, DWORD &dwData);
	BOOL	GetRegValueDW(const LPTSTR szName, DWORD &dwData);

	BOOL	GetRegValueBinaryAsDW(const LPTSTR szName, DWORD &dwData);

private:

	BOOL	m_bOpen;
	HKEY	m_hkeyItem;
};

#endif