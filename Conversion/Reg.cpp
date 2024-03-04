#pragma warning( disable : 4996)
#include "Reg.h"

#define BOOK_REG_HIVE   HKEY_CURRENT_USER
#define BOOK_REG_KEY    _T("SOFTWARE\\Seligman\\Conversion")

CReg g_Reg;

CReg::CReg()
{
    m_dwUnit = GetDWORD(REG_UNIT);
    m_dwFrom = GetDWORD(REG_FROM);
    m_dwTo = GetDWORD(REG_TO);
}

CReg::~CReg()
{
    //nothing
}

DWORD CReg::GetUnit()
{
    return m_dwUnit;
}

void CReg::SetUnit(DWORD dwUnit)
{
    m_dwUnit = dwUnit;
    SetDWORD(REG_UNIT, dwUnit);
}

DWORD CReg::GetFrom()
{
    return m_dwFrom;
}

void CReg::SetFrom(DWORD dwFrom)
{
    m_dwFrom = dwFrom;
    SetDWORD(REG_FROM, dwFrom);
}

DWORD CReg::GetTo()
{
    return m_dwTo;
}

void CReg::SetTo(DWORD dwTo)
{
    m_dwTo = dwTo;
    SetDWORD(REG_TO, dwTo);
}

DWORD CReg::GetDWORD(LPTSTR szKey)
{
    HKEY hKey = NULL;
    DWORD dwRet = (DWORD)-1;

    RegOpenKeyEx(BOOK_REG_HIVE, BOOK_REG_KEY, 
        REG_OPTION_NON_VOLATILE, KEY_READ, &hKey);

    if (hKey != NULL && hKey != INVALID_HANDLE_VALUE)
    {
        DWORD dwValue = 0;
        DWORD dwType = 0;
        DWORD dwSize = sizeof dwValue;
        RegQueryValueEx(hKey, szKey, 0, &dwType, (LPBYTE) &dwValue, &dwSize);
        RegCloseKey(hKey);
        if (dwType == REG_DWORD && dwSize == sizeof dwValue)
        {
            dwRet = dwValue;
        }
    }

    return dwRet;
}

void CReg::SetLPTSTR(LPTSTR szKey, LPTSTR szValue)
{
    HKEY hKey = NULL;
    DWORD dwCreate = NULL;

#ifdef UNDER_CE
    RegCreateKeyEx(
        BOOK_REG_HIVE,
        BOOK_REG_KEY, 0, _T(""),
        0, 0, NULL, &hKey, &dwCreate);
#else
    RegCreateKeyEx(
        BOOK_REG_HIVE, BOOK_REG_KEY, 0, 
        REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
        &hKey, &dwCreate);
#endif
    RegSetValueEx(hKey, szKey, 0, REG_SZ, (LPBYTE) szValue, 
        (_tcslen(szValue) + 1) * sizeof(TCHAR));
    RegCloseKey(hKey);
}

LPTSTR CReg::GetLPTSTR(LPTSTR szKey)
{
    HKEY hKey = NULL;
    static TCHAR szRet[MAX_PATH] = {0};
    _tcscpy(szRet, _T(""));

    RegOpenKeyEx(BOOK_REG_HIVE, BOOK_REG_KEY, 
        REG_OPTION_NON_VOLATILE, KEY_READ, &hKey);

    if (hKey != NULL && hKey != INVALID_HANDLE_VALUE)
    {
        DWORD dwType = 0;
        DWORD dwSize = MAX_PATH * sizeof(TCHAR);
        RegQueryValueEx(hKey, szKey, 0, &dwType, (LPBYTE) szRet, &dwSize);
        RegCloseKey(hKey);
    }

    return szRet;
}

void CReg::SetDWORD(LPTSTR szKey, DWORD dwValue)
{
    HKEY hKey = NULL;
    DWORD dwCreate = NULL;

#ifdef UNDER_CE
    RegCreateKeyEx(
        BOOK_REG_HIVE,
        BOOK_REG_KEY, 0, _T(""),
        0, 0, NULL, &hKey, &dwCreate);
#else
    RegCreateKeyEx(
        BOOK_REG_HIVE, BOOK_REG_KEY, 0, 
        REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
        &hKey, &dwCreate);
#endif
    RegSetValueEx(hKey, szKey, 0, REG_DWORD, (LPBYTE) &dwValue, sizeof dwValue);
    RegCloseKey(hKey);
}
