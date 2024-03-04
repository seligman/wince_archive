#include "main.h"

enum enumOperands {
    operNull = 0,
    operMul,
    operDiv,
    operAdd,
    operSub,
    operPow,
    operCount
};

class CEvalValue {
public:
    CEvalValue();
    CEvalValue(bool bIsNumber, double nNumber, enumOperands nOper, int nLevel);
    ~CEvalValue();

    void            SetNext(CEvalValue * pNext);
    CEvalValue *    GetNext();

    void            SetPrev(CEvalValue * pPrev);
    CEvalValue *    GetPrev();

    bool    GetIsNumber();
    void    SetIsNumber(bool bIsNumber);

    double  GetValue();
    void    SetValue(double nValue);

    int     GetLevel();
    void    SetLevel(int nLevel);

    enumOperands    GetOperand();
    void            SetOperand(enumOperands operNew);

private:

    bool            m_bIsNumber;
    double          m_nValue;
    int             m_nLevel;
    enumOperands    m_oper;

    CEvalValue * m_pNext;
    CEvalValue * m_pPrev;
};

double EvalExp(LPTSTR szToEval);
