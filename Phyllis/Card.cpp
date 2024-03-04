#include "stdafx.h"
#include "Card.h"

const LPTSTR CCard::m_szSuits[] = 
{
	_T("Diamond"),
	_T("Heart"),
	_T("Spade"),
	_T("Club"),
};

const LPTSTR CCard::m_szTypes[] = 
{
	_T("Ace"),
	_T("Two"),
	_T("Three"),
	_T("Four"),
	_T("Five"),
	_T("Six"),
	_T("Seven"),
	_T("Eight"),
	_T("Nine"),
	_T("Ten"),
	_T("Jack"),
	_T("Queen"),
	_T("King"),
};


const int CCard::m_CardLookup[] = 
{
 1, 5, 9,13,17,21,25,29,33,37,41,45,49,
 2, 6,10,14,18,22,26,30,34,38,42,46,50,
 3, 7,11,15,19,23,27,31,35,39,43,47,51,
 0, 4, 8,12,16,20,24,28,32,36,40,44,48,
};

void CCard::Init()
{
	m_pcNext = NULL;
#if defined(DEBUG) || defined(_DEBUG)
	#define NO_CARD 4242
	m_nCard = NO_CARD;
#endif
	m_bPlaceHolder = false;
}

CCard::CCard()
{
	Init();
}

CCard::CCard(int nNewCard, int nNewOrder)
{
	Init();

	SetCard(nNewCard);
	SetOrder(nNewOrder);
}

CCard * CCard::GetNext()
{
	return m_pcNext;
}

void CCard::SetNext(CCard * pcNewNext)
{
	m_pcNext = pcNewNext;
}

bool CCard::GetPlaceHolder()
{
	return m_bPlaceHolder;
}

void CCard::SetPlaceHolder(bool bNewPlaceHolder)
{
	m_bPlaceHolder = bNewPlaceHolder;
}

CCard::~CCard()
{

	if (m_pcNext)
	{
		xuntrack(m_pcNext);
		delete m_pcNext;
	}

}

int CCard::GetCard()
{
	ASSERT(m_nCard != NO_CARD);

	return m_nCard;
}

void CCard::SetCard(int nNewCard)
{
	ASSERT(nNewCard >= 0);
	ASSERT(nNewCard <= 51);

	m_nCard = nNewCard;
}

int CCard::GetOrder()
{
	return m_nOrder;
}

void CCard::SetOrder(int nNewOrder)
{
	m_nOrder = nNewOrder;
}

enumSuit CCard::GetSuit()
{
	ASSERT(m_nCard != NO_CARD);

	return (enumSuit)(m_nCard / 13);
}

enumType CCard::GetType()
{
	ASSERT(m_nCard != NO_CARD);

	return (enumType)(m_nCard % 13);
}

enumColor CCard::GetColor()
{
	ASSERT(m_nCard != NO_CARD);

	return (enumColor)(m_nCard / 26);
}

int CCard::GetPegCard()
{
	ASSERT(m_nCard != NO_CARD);

	return m_CardLookup[m_nCard];
}

LPTSTR CCard::GetSuitSz()
{
	ASSERT(m_nCard != NO_CARD);
	return (m_szSuits[GetSuit()]);
}

LPTSTR CCard::GetTypeSz()
{
	ASSERT(m_nCard != NO_CARD);
	return (m_szTypes[GetType()]);
}

char CCard::Serialize()
{
	if (m_bPlaceHolder)
	{
		return (char) (10 + m_nCard);
	}
	else
	{
		return (char) 9;
	}
}

void CCard::Serialize(char chrCard)
{
	if (chrCard == (char) 9)
	{
		m_bPlaceHolder = true;
		m_nCard = 0;
	}
	else
	{
		m_nCard = (int) (chrCard - 10);
		m_bPlaceHolder = 0;
	}
	m_nOrder = 0;
}

CCard::CCard(char chrCard)
{
	Init();
	Serialize(chrCard);
}

