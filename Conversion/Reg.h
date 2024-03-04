class CReg;

#ifndef REG_H__INCLUDED_
#define REG_H__INCLUDED_

#include "main.h"
#include "resource.h"

#define REG_UNIT        _T("Unit")
#define REG_FROM        _T("From")
#define REG_TO          _T("To")

class CReg
{
public:
            ~CReg();
            CReg();
    DWORD   GetUnit();
    DWORD   GetFrom();
    DWORD   GetTo();
    void    SetUnit(DWORD dwUnit);
    void    SetFrom(DWORD dwFrom);
    void    SetTo(DWORD dwTo);

private:
    DWORD   GetDWORD(LPTSTR szKey);
    LPTSTR  GetLPTSTR(LPTSTR szKey);
    void    SetDWORD(LPTSTR szKey, DWORD dwValue);
    void    SetLPTSTR(LPTSTR szKey, TCHAR * szValue);

    DWORD   m_dwUnit;
    DWORD   m_dwFrom;
    DWORD   m_dwTo;
};

extern CReg g_Reg;

#endif
