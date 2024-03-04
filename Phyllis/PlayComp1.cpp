//#define SHOW_HAND

#include "stdafx.h"
#include "PlayComp1.h"
#if defined(DEBUG) || defined(_DEBUG)
#include <stdio.h>
#endif

CPlayComp1::CPlayComp1()
{
    m_gamelayout = NULL;
    m_playerwatcher = NULL;
}

CPlayComp1::~CPlayComp1()
{
    // nothing yet
}

void CPlayComp1::InitPlayer(IPlayerWatcher * playerwatcher)
{
    m_playerwatcher = playerwatcher;
}

void CPlayComp1::NewDeck(CGameLayout * gamelayout)
{
    // Just need to take note of the game layout
    m_gamelayout = gamelayout;
}

void CPlayComp1::Played(CGameLayout * gamelayout)
{
    // Just need to take note of the game layout
    m_gamelayout = gamelayout;
}

// Just keeps track of the top two cards
void CPlayComp1::GetTopTwo()
{

    m_pcTop[1] = NULL;
    m_pcTop[0] = NULL;

    CCard * pcCard = m_gamelayout->pcDiscard;
    while (pcCard)
    {
        m_pcTop[0] = m_pcTop[1];
        m_pcTop[1] = pcCard;
        pcCard = pcCard->GetNext();
    }

}

bool CPlayComp1::CanPlay(enumType type)
{
    switch (type)
    {
    case typeAce:
    case typeTwo:
    case typeTen:
        return true;
    }

    if (!m_pcTop[1])
    {
        return true;
    }

    switch (m_pcTop[1]->GetType())
    {
    case typeAce:
        if (type == typeAce)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    default:
        if (type >= m_pcTop[1]->GetType())
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }

 }

// Find out the optimal card to play from the deck
bool CPlayComp1::CanPlayFromDeck(CCard * pcDeck, CCard ** pcCard)
{
#if defined(DEBUG) || defined(_DEBUG)
#ifdef SHOW_HAND
    TCHAR sz[100];
    OutputDebugString(_T("---\n"));
    CCard * pcTemp = pcDeck;
    while (pcTemp)
    {
        if (pcTemp->GetPlaceHolder())
        {
            OutputDebugString(_T("[   ]\n"));
        }
        else
        {
            _stprintf(sz, _T("%s of %s\n"), pcTemp->GetTypeSz(), pcTemp->GetSuitSz());
            OutputDebugString(sz);
        }
        pcTemp = pcTemp->GetNext();
    }
#endif
#endif
    if (!pcDeck)
    {
        return false;
    }

    bool bRet = false;
    int i;
    enumType type;

    // Simple, just search for the cards in this order,
    //  And play the first one we run into
    for (i = 0; i < 13; i ++)
    {
        switch (i)
        {
        case 0:
            type = typeThree;
            break;
        case 1:
            type = typeFour;
            break;
        case 2:
            type = typeFive;
            break;
        case 3:
            type = typeSix;
            break;
        case 4:
            type = typeSeven;
            break;
        case 5:
            type = typeEight;
            break;
        case 6:
            type = typeNine;
            break;
        case 7:
            type = typeJack;
            break;
        case 8:
            type = typeQueen;
            break;
        case 9:
            type = typeKing;
            break;
        case 10:
            type = typeAce;
            break;
        case 11:
            type = typeTwo;
            break;
        case 12:
            type = typeTen;
            break;
        }
    
        if (CanPlay(type))
        {
            (*pcCard) = pcDeck;
            while (*pcCard && !bRet)
            {
                if ( (*pcCard)->GetPlaceHolder() == false && 
                     (*pcCard)->GetType() == type )
                {
                    bRet = true;
                }
                else
                {
                    (*pcCard) = (*pcCard)->GetNext();
                }
            }
        }
        if (bRet)
        {
            break;
        }
    }

    //Small hack to only drop one ten at a time
    if (bRet)
    {
        if ((*pcCard)->GetType() == typeTen)
        {
            CCard * pcTemp;
            CCard * pcLast;
            pcTemp = (*pcCard);
            pcLast = pcTemp;
            while(pcTemp && pcTemp->GetType() == typeTen)
            {
                pcLast = pcTemp;
                pcTemp = pcTemp->GetNext();
            }
            (*pcCard) = pcLast;
        }
    }

    return bRet;

}

void CPlayComp1::YourTurn()
{
	bool bDestructed = false;
	CCard * pcCard;
    bool bPlay = false;

    GetTopTwo();

    if (m_gamelayout->pcComputer[handHand])
    {
        if (CanPlayFromDeck(m_gamelayout->pcComputer[handHand], &pcCard))
        {
            bPlay = true;
        }
    }
    else if (m_gamelayout->pcComputer[handUp])
    {
        if (CanPlayFromDeck(m_gamelayout->pcComputer[handUp], &pcCard))
        {
            bPlay = true;
        }
    }
    else if (m_gamelayout->pcComputer[handDown])
    {
        pcCard = m_gamelayout->pcComputer[handDown];
        while (pcCard && pcCard->GetPlaceHolder())
        {
            pcCard = pcCard->GetNext();
        }
        if (pcCard)
        {
            bPlay = true;
        }
    }

    // Nothing we can play, try hand-of-god, then just eat the deck
    if (!bPlay)
    {
        if (m_gamelayout->pcDeck)
        {
            pcCard = m_gamelayout->pcDeck;
        }
        else
        {
            pcCard = m_gamelayout->pcDiscard;
        }
    }

    m_playerwatcher->PlayedCard(pcCard);
}

void CPlayComp1::PlaceMultiFaceUp(int * nToPlay, enumType type)
{
	(*nToPlay) = 1;
}

void CPlayComp1::EatOneCard(int * nEatCard)
{
	(*nEatCard) = 0;
}

