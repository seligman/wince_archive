//#define SHOW_HAND

#include "stdafx.h"
#include "PlayComp2.h"
#if defined(DEBUG) || defined(_DEBUG)
#include <stdio.h>
#endif

#ifdef COMPUTER_VS_COMPUTER
extern int g_nCurrentNum;
#endif

CPlayComp2::CPlayComp2()
{
    m_gamelayout = NULL;
    m_playerwatcher = NULL;

    m_nScore[typeThree] = -10;
    m_nScore[typeFour] = -10;
    m_nScore[typeFive] = -8;
    m_nScore[typeSix] = -8;
    m_nScore[typeSeven] = -6;
    m_nScore[typeEight] = -6;
    m_nScore[typeNine] = -1;
    m_nScore[typeTwo] = 0;
    m_nScore[typeJack] = 1;
    m_nScore[typeQueen] = 2;
    m_nScore[typeKing] = 3;
    m_nScore[typeAce] = 5;
    m_nScore[typeTen] = 7;

    m_nOrder[typeTen] = 0;
    m_nOrder[typeTwo] = 1;
    m_nOrder[typeThree] = 2;
    m_nOrder[typeFour] = 3;
    m_nOrder[typeFive] = 4;
    m_nOrder[typeSix] = 5;
    m_nOrder[typeSeven] = 6;
    m_nOrder[typeEight] = 7;
    m_nOrder[typeNine] = 8;
    m_nOrder[typeJack] = 9;
    m_nOrder[typeQueen] = 10;
    m_nOrder[typeKing] = 11;
    m_nOrder[typeAce] = 12;
}

CPlayComp2::~CPlayComp2()
{
    // nothing yet
}

void CPlayComp2::InitPlayer(IPlayerWatcher * playerwatcher)
{
    m_playerwatcher = playerwatcher;
}

void CPlayComp2::NewDeck(CGameLayout * gamelayout)
{
    // Just need to take note of the game layout
    m_gamelayout = gamelayout;
}

void CPlayComp2::Played(CGameLayout * gamelayout)
{
    // Just need to take note of the game layout
    m_gamelayout = gamelayout;
}

// Keeps track of the top two cards, and scores
//  the decks
void CPlayComp2::GetTopTwo()
{

    m_pcTop[1] = NULL;
    m_pcTop[0] = NULL;

    m_nHandCount = 0;
    m_nDiscardScore = 0;
    m_nDiscardCount = 0;
    m_nDrawCount = 0;
    m_nHandScore = 0;

    CCard * pcCard;
    pcCard = m_gamelayout->pcDeck;
    while (pcCard)
    {
        m_nDrawCount ++;
        pcCard = pcCard->GetNext();
    }

    int i = 0;
    for (i = 0; i < typeCount; i ++)
    {
        m_nTypeCount[i] = 0;
    }

    pcCard = m_gamelayout->pcComputer[handHand];
    while (pcCard)
    {
        m_nHandCount ++;
        m_nHandScore += m_nScore[pcCard->GetType()];
        m_nTypeCount[pcCard->GetType()] ++;
        pcCard = pcCard->GetNext();
    }

    pcCard = m_gamelayout->pcDiscard;
    while (pcCard)
    {
        int nType = pcCard->GetType();
        int nScore = m_nScore[pcCard->GetType()];

        m_nDiscardCount ++;

        if (m_nTypeCount[nType] == 2)
        {
            m_nDiscardScore += nScore<0?0:nScore;
        }
        else
        {
            m_nDiscardScore += nScore;
        }

        m_pcTop[0] = m_pcTop[1];
        m_pcTop[1] = pcCard;
        pcCard = pcCard->GetNext();
    }

}

// Can the type of card be played?
bool CPlayComp2::CanPlay(enumType type)
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
bool CPlayComp2::CanPlayFromDeck(CCard * pcDeck, CCard ** pcCard)
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
    int j;
    bool bTriplicate;
    enumType type;

    // See if there are any triplicates to play first
    // Otherwise, just try any card
    for (j = 0; j < 2; j ++)
    {
        if (j == 0)
        {
            bTriplicate = true;
        }
        else
        {
            bTriplicate = false;
        }

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
    
            bool bSkip = false;
            if (bTriplicate && type == typeTen)
            {
                bSkip = true;
            }
            else
            {
                if (m_gamelayout->pcDiscard == NULL && bTriplicate)
                {
                    bSkip = true;
                }
            }
            if (!bSkip)
            {
                if (bTriplicate)
                {
                    if (m_nTypeCount[type] <= 2)
                    {
                        bSkip = true;
                    }
                }
            }

            if (!bSkip)
            {
                if (CanPlay((enumType) type))
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
            }
            if (bRet)
            {
                break;
            }
        }

        if (bRet)
        {
            break;
        }
    }


    //Small hack to only drop one ten at a time
    // Also, only drop one card if we only have two
    if (bRet)
    {
        bool bOneCard = false;
        type = (*pcCard)->GetType();
        if (type == typeTen)
        {
            bOneCard = true;
        }
        else if (m_nTypeCount[type] == 2)
        {
            if (m_nScore[type] > 0)
            {
                bOneCard = true;
            }
        }
        if (bOneCard)
        {
            CCard * pcTemp;
            CCard * pcLast;
            pcTemp = (*pcCard);
            pcLast = pcTemp;
            while(pcTemp && pcTemp->GetType() == type)
            {
                pcLast = pcTemp;
                pcTemp = pcTemp->GetNext();
            }
            (*pcCard) = pcLast;
        }
    }

    return bRet;

}

void CPlayComp2::YourTurn()
{
	bool bDestructed = false;
	CCard * pcCard;
    bool bPlay = false;

    GetTopTwo();

    if (m_gamelayout->pcComputer[handHand])
    {
        if (CanPlayFromDeck(m_gamelayout->pcComputer[handHand], &pcCard))
        {

            // These numbers have been tweaked
            if (m_gamelayout->pcPlayer[handHand] == NULL &&
                m_gamelayout->pcPlayer[handUp] != NULL &&
                m_nDiscardCount >= 3 &&
                m_nDiscardScore < 8)
            {
                CCard * pcTemp = m_gamelayout->pcPlayer[handUp];
                int typePlayerHighest = -1;

                while (pcTemp)
                {
                    if (!pcTemp->GetPlaceHolder())
                    {
                        if (typePlayerHighest == -1)
                        {
                            typePlayerHighest = pcTemp->GetType();
                        }
                        else if (m_nOrder[typePlayerHighest] < m_nOrder[pcTemp->GetType()])
                        {
                            typePlayerHighest = pcTemp->GetType();
                        }
                    }
                    pcTemp = pcTemp->GetNext();
                }
                // We know what the player's highest card is, can we beat it?
                CCard * pcTemp2 = NULL;
                pcTemp = m_gamelayout->pcComputer[handHand];
                while (pcTemp && !pcTemp2)
                {
                    if (m_nOrder[pcTemp->GetType()] > m_nOrder[typePlayerHighest])
                    {
                        if (CanPlay(pcTemp->GetType()))
                        {
                            pcTemp2 = pcTemp;
                        }
                    }
                    pcTemp = pcTemp->GetNext();
                }
                if (pcTemp2)
                {
                    //we can beat it, go ahead and place the last one
                    while (pcTemp2->GetNext() && pcTemp2->GetNext()->GetType() == pcTemp2->GetType())
                    {
                        pcTemp2 = pcTemp2->GetNext();
                    }
                    pcCard = pcTemp2;
                }
            }

            bPlay = true;
            if (pcCard->GetType() == typeTen)
            {
                // we only have one ten left, only play it if there's no draw pile
                if (m_nTypeCount[typeTen] == 1 && m_nDrawCount > 0)
                {
                    bPlay = false;
                }
            }

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

    bool bEatDeck = false;

    // These numbers have been tweaked
    if (m_nDiscardScore > 6 && 
        m_nDiscardCount >= 3 && m_nDiscardCount <= 10 &&
        m_nHandCount <= 20 && 
		m_nDrawCount > 0)
    {
        // This is a good deck, eat it!
        bPlay = false;
        bEatDeck = true;
    }

    // These numbers have been tweaked
    if (m_nHandScore > 0 && m_nDiscardScore > 5 && m_nDrawCount > 0)
    {
        bPlay = false;
        bEatDeck = true;
    }

	//These numbers have been tweaked
    if (m_nHandScore > 25 && m_nDiscardCount == 0 && m_nDrawCount > 0)
    {
        bPlay = false;
    }
    
    // Nothing we can play, then just eat the deck
    if (!bPlay)
    {
        // See if we should try hand of god
        bool bHandOfGod = true;
        if (bEatDeck)
        {
            bHandOfGod = false;
        }
        if (!m_gamelayout->pcDeck)
        {
            // Oops, no cards to try it with
            bHandOfGod = false;
        }
        if (bHandOfGod)
        {
            // Not a good idea to try a hand of god with a high card on the deck
            if (m_pcTop[1])
            {
                // These numbers have been tweaked
                switch (m_pcTop[1]->GetType())
                {
                case typeAce:
                case typeKing:
                    bHandOfGod = false;
                }
            }
        }
        if (bHandOfGod)
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

void CPlayComp2::PlaceMultiFaceUp(int * nToPlay, enumType type)
{
	// There might be something better taking into account
	//  the other player, but number wise, it's always best to
	//  play more than one if you can.

	// Do nothing, nToPlay is the number I want to play.
    // These numbers have been tweaked
}

void CPlayComp2::EatOneCard(int * nEatCard)
{
	// Eat a card if it'll give us a triplicate, otherwise
	//  don't bother, it won't do any good.
	CCard * pcTemp = m_gamelayout->pcComputer[handUp];
	int nFound = 0;
	int nScore = 0;
	int nCur = 0;
	while (pcTemp)
	{
		nCur ++;
		if (pcTemp->GetPlaceHolder() == false)
		{
			int nCount = 0;
			nCount = 0;
			enumType typeDest = pcTemp->GetType();
			CCard * pcTemp2 = m_gamelayout->pcDiscard;
			while (pcTemp2)
			{
				if (pcTemp2->GetType() == typeDest)
				{
					nCount ++;
				}
				pcTemp2 = pcTemp2->GetNext();
			}
			if (nCount > 2)
			{
				if (nScore == 0 || m_nScore[typeDest] > nScore)
				{
					nFound = nCur;
					nScore = m_nScore[typeDest];
				}
			}
		}

		pcTemp = pcTemp->GetNext();
	}

	(*nEatCard) = nFound;
}

