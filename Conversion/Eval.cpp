#include "eval.h"
#include <tchar.h>
//#include "utils.h"

CEvalValue::CEvalValue()
{
    m_pNext = NULL;
    m_pPrev = NULL;
    m_bIsNumber = false;
    m_nValue = 0;
    m_nLevel = 0;
    m_oper = operCount;
}

CEvalValue::CEvalValue(bool bIsNumber, double nNumber, enumOperands nOper, int nLevel)
{
    m_pNext = NULL;
    m_pPrev = NULL;
    m_bIsNumber = bIsNumber;
    m_nValue = nNumber;
    m_oper = nOper;
    m_nLevel = nLevel;
}

CEvalValue::~CEvalValue()
{
    if (m_pNext)
    {
        delete m_pNext;
    }
}

void CEvalValue::SetNext(CEvalValue * pNext)
{
    m_pNext = pNext;
}

CEvalValue * CEvalValue::GetNext()
{
    return m_pNext;
}

void CEvalValue::SetPrev(CEvalValue * pPrev)
{
    m_pPrev = pPrev;
}

CEvalValue * CEvalValue::GetPrev()
{
    return m_pPrev;
}

bool CEvalValue::GetIsNumber()
{
    return m_bIsNumber;
}

void CEvalValue::SetIsNumber(bool bIsNumber)
{
    m_bIsNumber = bIsNumber;
}

double CEvalValue::GetValue()
{
    return m_nValue;
}

void CEvalValue::SetValue(double nValue)
{
    m_nValue = nValue;
    m_bIsNumber = true;
}

int CEvalValue::GetLevel()
{
    return m_nLevel;
}

void CEvalValue::SetLevel(int nLevel)
{
    m_nLevel = nLevel;
}

enumOperands CEvalValue::GetOperand()
{
    return m_oper;
}

void CEvalValue::SetOperand(enumOperands operNew)
{
    m_oper = operNew;
    m_bIsNumber = false;
}

const TCHAR szAllNums[] = _T("0123456789.");
const TCHAR szAllOpers[] = _T("+-/*()^");

TCHAR * CopyStr(TCHAR * szIn)
{
	TCHAR * szRet = (TCHAR *) malloc((_tcslen(szIn) + 1) * sizeof(TCHAR));
	_tcscpy(szRet, szIn);
	return szRet;
}

double EvalExp(LPTSTR szToEval)
{

    TCHAR * szWork = CopyStr(szToEval);
    int nPos = 0;
    int nStart = 0;
    bool bInValue = false;
    bool bInOper = false;
    int nTemp;
    bool bValue;
    bool bOper;
    int nCount = 0;
    double nRet;

    CEvalValue * pFirst = NULL;
    CEvalValue * pLast = NULL;
    CEvalValue * pCur = NULL;
    int             nLevel = 0;
    int             nMaxLevel = 0;

    int nLen = _tcslen(szToEval);

    for (nPos = 0; nPos <= nLen; nPos ++)
    {
        bValue = false;
        bOper = false;
        for (nTemp = 0; nTemp < (sizeof szAllNums / sizeof TCHAR)-1; nTemp ++)
        {
            if (szAllNums[nTemp] == szToEval[nPos])
            {
                bValue = true;
                break;
            }
        }
        if (!bValue)
        {
            for (nTemp = 0; nTemp < (sizeof szAllOpers / sizeof TCHAR)-1; nTemp ++)
            {
                if (szAllOpers[nTemp] == szToEval[nPos])
                {
                    bOper = true;
                    break;
                }
            }
        }
 
        int nParseStart;
        int nParseEnd;
        bool bParseValue;
        bool bParse;

        bParse = false;

        if (bValue)
        {
            if (bInOper)
            {
                nParseStart = nStart;
                nParseEnd = nPos;
                bParseValue = bInValue;
                bParse = true;
                bInOper = false;
                nStart = nPos;
            }
            if (!bInValue)
            {
                nStart = nPos;
                bInValue = true;
            }
        }
        else if (bOper)
        {
            if (bInOper || bInValue)
            {
                nParseStart = nStart;
                nParseEnd = nPos;
                bParseValue = bInValue;
                bParse = true;
            }

            nStart = nPos;
            bInOper = true;
            bInValue = false;
        }
        else if (bInOper || bInValue)
        {
            nParseStart = nStart;
            nParseEnd = nPos;
            bParseValue = bInValue;
            bParse = true;
            bInValue = false;
            bInOper = false;
            nStart = nPos;
        }

        if (bParse)
        {

            memcpy(szWork, szToEval + nParseStart, (nParseEnd - nParseStart) * (sizeof TCHAR));
            szWork[nParseEnd - nParseStart] = 0;

            pCur = NULL;
            if (bParseValue)
            {
                pCur = new CEvalValue(true, _tcstod(szWork, NULL), operCount, nLevel);
            }
            else
            {
                enumOperands oper;
                switch (szWork[0])
                {
                case _T('+'):
                    oper = operAdd;
                    pCur = new CEvalValue(false, 0, oper, nLevel);
                    break;
                case _T('-'):
                    oper = operSub;
                    pCur = new CEvalValue(false, 0, oper, nLevel);
                    break;
                case _T('/'):
                    oper = operDiv;
                    pCur = new CEvalValue(false, 0, oper, nLevel);
                    break;
                case _T('*'):
                    oper = operMul;
                    pCur = new CEvalValue(false, 0, oper, nLevel);
                    break;
                case _T('^'):
                    oper = operPow;
                    pCur = new CEvalValue(false, 0, oper, nLevel);
                    break;
                case _T('('):
                    nLevel ++;
                    if (nLevel > nMaxLevel)
                    {
                        nMaxLevel = nLevel;
                    }
                    break;
                case _T(')'):
                    nLevel --;
                    break;
                }
            }
            if (pCur)
            {
                nCount ++;
                if (pFirst)
                {
                    pLast->SetNext(pCur);
                    pCur->SetPrev(pLast);
                    pLast = pCur;
                }
                else
                {
                    pFirst = pCur;
                    pLast = pCur;
                }
            }

        }
    }

    if (nCount == 0)
    {
        return 0;
    }
    else if (nCount == 1)
    {
        if (pFirst->GetIsNumber())
        {
            nRet = pFirst->GetValue();
            delete pFirst;
            return nRet;
        }
        else
        {
            delete pFirst;
            return 0;
        }
    }

    CEvalValue * pPrev;
    CEvalValue * pNext;
    CEvalValue * pTemp;

    nLevel = nMaxLevel+1;

    do {
        nLevel --;
        if (nLevel < 0)
        {
            delete pFirst;
            return 0;
        }
        nCount = 0;
        // Negate any numerical values
        for (pCur = pFirst; pCur; pCur = pCur->GetNext())
        {
            if (!pCur->GetIsNumber() && pCur->GetOperand() == operSub)
            {
                if (pCur->GetNext() && 
                    pCur->GetNext()->GetIsNumber() && 
                    pCur->GetLevel() == pCur->GetNext()->GetLevel())
                {
                    if (!pCur->GetPrev() ||
                        (pCur->GetPrev() &&
                         pCur->GetPrev()->GetLevel() == pCur->GetLevel() &&
                         !pCur->GetPrev()->GetIsNumber()
                         ))
                    {
                        pCur->GetNext()->SetValue(-(pCur->GetNext()->GetValue()));
                        pCur->SetOperand(operNull);
                    }
                }
            }
        }

        // Process Operands
        int nCur;

        enumOperands operCur[3];
        int nOpers;
        for (nCur = 1; nCur < 3; nCur ++)
        {
            if (nCur == 1)
            {
                operCur[0] = operMul;
                operCur[1] = operDiv;
                operCur[2] = operPow;
                nOpers = 3;
            }
            else
            {
                operCur[0] = operSub;
                operCur[1] = operAdd;
                nOpers = 2;
            }
            for (pCur = pFirst; pCur; pCur = pCur->GetNext())
            {
                if (!pCur->GetIsNumber() && pCur->GetLevel() == nLevel && 
                    ( (nOpers >= 1 && pCur->GetOperand() == operCur[0]) ||
                      (nOpers >= 2 && pCur->GetOperand() == operCur[1]) ||
                      (nOpers >= 3 && pCur->GetOperand() == operCur[2]) ) )
                {
                    pPrev = pCur;
                    pNext = pCur;
                    while (pPrev && !pPrev->GetIsNumber())
                    {
                        pPrev = pPrev->GetPrev();
                    }
                    while (pNext && !pNext->GetIsNumber())
                    {
                        pNext = pNext->GetNext();
                    }
                    if (!pNext || !pPrev || pPrev->GetLevel() != nLevel || pNext->GetLevel() != nLevel)
                    {
                        delete pFirst;
                        return 0;
                    }

                    switch (pCur->GetOperand())
                    {
                    case operMul:
                        pPrev->SetValue(pPrev->GetValue() * pNext->GetValue());
                        break;
                    case operDiv:
                        pPrev->SetValue(pPrev->GetValue() / pNext->GetValue());
                        break;
                    case operAdd:
                        pPrev->SetValue(pPrev->GetValue() + pNext->GetValue());
                        break;
                    case operSub:
                        pPrev->SetValue(pPrev->GetValue() - pNext->GetValue());
                        break;
                    case operPow:
                        pPrev->SetValue(pow(pPrev->GetValue(), pNext->GetValue()));
                        break;
                    }
                    pCur->SetOperand(operNull);
                    pNext->SetOperand(operNull);
                }
            }
        }

        // Remove any null operands
        pCur = pFirst;
        while (pCur)
        {
            if (pCur->GetLevel() == nLevel)
            {
                pCur->SetLevel(nLevel-1);
            }
            if (pCur->GetOperand() == operNull)
            {
                pTemp = pCur->GetNext();
                if (pCur->GetPrev())
                {
                    pCur->GetPrev()->SetNext(pTemp);
                }
                if (pCur->GetNext())
                {
                    pCur->GetNext()->SetPrev(pCur->GetPrev());
                }
                pCur->SetNext(NULL);
                if (pCur == pFirst)
                {
                    pFirst = pTemp;
                }

                delete pCur;
                pCur = pTemp;
            }
            else
            {
                nCount ++;
                pCur = pCur->GetNext();
            }
        }

    } while (nCount != 1);

    if (pFirst->GetIsNumber())
    {
        nRet = pFirst->GetValue();
        delete pFirst;
        return nRet;
    }
    else
    {
        delete pFirst;
        return 0;
    }

}
