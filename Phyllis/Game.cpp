#include "stdafx.h"
#ifndef UNDER_CE
#include <search.h>
#endif
#include "Game.h"

#include "DrawCards.h"


#if defined(DEBUG) || defined(_DEBUG)
#define TRACE(s) OutputDebugString(s)
#else
#define TRACE(s) (void())
#endif

#define MY_REGKEY _T("Software\\Seligman\\Phyllis")

BOOL cdtAnimate(HDC hdc, int cd, int x, int y, int ispr);
BOOL cdtDraw(HDC hdc, int x, int y, int dx, int dy, int cd, int mode );
BOOL cdtInit(int FAR *pcardSizeX, int FAR *pcardSizeY );

void CGame::DrawBackCard(HDC hdc, int x, int y, int nCard)
{
	//Draw the backing of cards, used by the options dialog

	int nCard2 = 0;

	switch (nCard)
	{
	case 1:
		nCard2 = IDFACEDOWN1;
		break;
	case 2:
		nCard2 = IDFACEDOWN2;
		break;
	case 3:
		nCard2 = IDFACEDOWN3;
		break;
	case 4:
		nCard2 = IDFACEDOWN4;
		break;
	case 5:
		nCard2 = IDFACEDOWN5;
		break;
	default:
		nCard2 = IDFACEDOWN6;
		break;
	}

	cdtDraw(hdc, x, y, m_nCardX, m_nCardY, 
		nCard2, 
		FACEDOWN);
}


void CGame::SetOptEndGame(bool bEndGame)
{
	m_bOptEndGame = bEndGame;
}

void CGame::SetOptCard(int nCardNum)
{
	ASSERT(nCardNum >= 1);
	ASSERT(nCardNum <= 6);

	m_nOptCard = nCardNum;
}

bool CGame::GetOptEndGame()
{
	return m_bOptEndGame;
}

int CGame::GetOptCard()
{
	return m_nOptCard;
}


void CGame::PlayCard(bool bComputer, CCard * pcCard, bool * pbCardPlayed, bool * pbDestructed)
{
	// Play a selected card.

	if (m_bGameOver)
	{
		(*pbCardPlayed) = false;
		(*pbDestructed) = false;
		return;
	}

	// Hack to let us play from either the player or computers hands
	CCard ** ppcPlayerHand;
	CCard ** ppcPlayerUp;
	CCard ** ppcPlayerDown;
	if (bComputer)
	{
		ppcPlayerHand = &m_gamelayout.pcComputer[handHand];
		ppcPlayerUp = &m_gamelayout.pcComputer[handUp];
		ppcPlayerDown = &m_gamelayout.pcComputer[handDown];
	}
	else
	{
		ppcPlayerHand = &m_gamelayout.pcPlayer[handHand];
		ppcPlayerUp = &m_gamelayout.pcPlayer[handUp];
		ppcPlayerDown = &m_gamelayout.pcPlayer[handDown];
	}
	

	CCard * pcTemp;
	CCard * pcNext;
	CCard ** ppcDeck;
	enumType type;
	bool bFound = false;
	bool bCanPlay = false;
	bool bDestructs = false;
	bool bEatTheDeck = false;
	bool bTemp1;
	bool bTemp2;
	int i = 0;

	// Figure out where the card came from

	// Was a card in the hand selected?
	pcTemp = *ppcPlayerHand;
	ppcDeck = ppcPlayerHand;
	while (pcTemp)
	{
		if (pcTemp == pcCard)
		{
			bFound = true;
			pcNext = pcCard->GetNext();
			type = pcCard->GetType();
			CanPlayCard(pcCard, &bCanPlay, &bDestructs);

			if (bFound && bCanPlay)
			{
				MoveCard(ppcDeck, &m_gamelayout.pcDiscard, pcCard, false);
			}

			while ((pcNext != NULL) && 
				   (type == pcNext->GetType()))
			{
				pcCard = pcNext;
				pcNext = pcCard->GetNext();
				bTemp1 = false;
				bTemp2 = false;
				CanPlayCard(pcCard, &bTemp1, &bTemp2);
				if (bTemp1)
				{
					MoveCard(ppcDeck, &m_gamelayout.pcDiscard, pcCard, false);
					if (bTemp2)
					{
						bDestructs = true;
					}
				}
			}
		}
		if (!bFound)
		{
			pcTemp = pcTemp->GetNext();
		}
		else
		{
			pcTemp = NULL;
		}
	}

	if (!bFound)
	{
		//Not in the hand, if the hand is empty, check the faceup pile
		if ((*ppcPlayerHand) == NULL)
		{
			pcTemp = *ppcPlayerUp;
			ppcDeck = ppcPlayerUp;
			while (pcTemp)
			{
				if (pcTemp == pcCard)
				{
					CanPlayCard(pcCard, &bCanPlay, &bDestructs);
					bFound = true;
				}
				pcTemp = pcTemp->GetNext();
			}
		}
		if (bFound && bCanPlay)
		{
			pcTemp = *ppcPlayerUp;
			int nCount = 0;
			while (pcTemp)
			{
				if (pcTemp->GetPlaceHolder() == false)
				{
					if (pcTemp->GetType() == pcCard->GetType())
					{
						nCount ++;
					}
				}
				pcTemp = pcTemp->GetNext();
			}

			if (nCount > 1)
			{
				//Need to see if we want to play more than one of this card.
				#ifndef COMPUTER_VS_COMPUTER
				if (bComputer)
				{
				#endif
					//ask the computer
					m_player->PlaceMultiFaceUp(&nCount, pcCard->GetType());
				#ifndef COMPUTER_VS_COMPUTER
				}
				else
				{
					// ask the player
					m_watcher->PlaceMultiFaceUp(&nCount, pcCard->GetTypeSz());
				}
				#endif
			}

			//we found something that's playable
			enumType type = pcCard->GetType();
			MoveCard(ppcDeck, &m_gamelayout.pcDiscard, pcCard, true);

			while (nCount > 1)
			{
				pcTemp = *ppcPlayerUp;
				while (pcTemp)
				{
					if (pcTemp->GetPlaceHolder() == false)
					{
						if (pcTemp->GetType() == type)
						{
							nCount --;
							CanPlayCard(pcTemp, &bCanPlay, &bDestructs);
							ASSERT(bCanPlay);
							MoveCard(ppcDeck, &m_gamelayout.pcDiscard, pcTemp, true);
							pcTemp = NULL;
						}
					}
					if (pcTemp)
					{
						pcTemp = pcTemp->GetNext();
					}
				}
			}

		}
	}


	if (!bFound)
	{
		//Not in the hand or faceup, if the hand and faceup are 
		// empty, check the facedown pile
		if ((*ppcPlayerHand) == NULL && (*ppcPlayerUp) == NULL)
		{
			pcTemp = *ppcPlayerDown;
			ppcDeck = ppcPlayerDown;
			while (pcTemp)
			{
				if (pcTemp == pcCard)
				{
					CanPlayCard(pcCard, &bCanPlay, &bDestructs);
					bFound = true;
					pcTemp = NULL;
					MoveCard(ppcPlayerDown, &m_gamelayout.pcDiscard, pcCard, true);
					if (!bCanPlay)
					{
						bEatTheDeck = true;
						bCanPlay = true;
					}
				}
				if (pcTemp)
				{
					pcTemp = pcTemp->GetNext();
				}
			}
		}
	}

	if (!bFound)
	{
		//see if they're trying to hand of god
		// (play a card from the draw pile)
		pcTemp = m_gamelayout.pcDeck;
		if (pcTemp != NULL)
		{
			while (pcTemp->GetNext() && pcTemp != pcCard)
			{
				pcTemp = pcTemp->GetNext();
			}
			if (pcTemp == pcCard)
			{
				//yes, they are trying to, can they?
				bFound = true;
				CanPlayCard(pcCard, &bCanPlay, &bDestructs);
				MoveCard(&m_gamelayout.pcDeck, &m_gamelayout.pcDiscard, pcCard, false);
				if (!bCanPlay)
				{
					bEatTheDeck = true;
					bCanPlay = true;
				}
			}
		}
	}


	if (!bFound)
	{
		bFound = true;
		//see if they just want to eat the deck
		pcTemp = m_gamelayout.pcDiscard;
		while (pcTemp != NULL)
		{
			if (pcTemp == pcCard)
			{
				bFound = true;
				bCanPlay = true;
				bEatTheDeck = true;
				pcTemp = NULL;
			}
			else
			{
				pcTemp = pcTemp->GetNext();
			}
		}
	}

	if (bEatTheDeck)
	{
		// if this is an empty hand, they can also eat a face up card
		if ((*ppcPlayerHand) == NULL && (*ppcPlayerUp) != NULL)
		{
			int nEatCard = 0;

			#ifndef COMPUTER_VS_COMPUTER
			if (bComputer)
			{
			#endif
				//ask the computer
				m_player->EatOneCard(&nEatCard);
			#ifndef COMPUTER_VS_COMPUTER
			}
			else
			{
				// ask the player
				TCHAR * szTypes[3];
				for (i = 0; i < 3; i ++)
				{
					szTypes[i] = NULL;
				}
				i = 0;

				pcTemp = (*ppcPlayerUp);
				while (pcTemp)
				{
					if (pcTemp->GetPlaceHolder() == false)
					{
						szTypes[i] = pcTemp->GetTypeSz();
					}
					i++;
					pcTemp = pcTemp->GetNext();
				}

				m_watcher->EatOneCard(&nEatCard, szTypes);
			}
			#endif

			pcTemp = (*ppcPlayerUp);
			while (nEatCard > 0)
			{
				ASSERT(pcTemp);
				nEatCard --;
				if (nEatCard == 0)
				{
					MoveCard(ppcPlayerUp, ppcPlayerHand, pcTemp, true);
				}
				pcTemp = pcTemp->GetNext();
			}
		}


		// They get to eat the deck, lucky them
		while (m_gamelayout.pcDiscard)
		{
			MoveCard(&m_gamelayout.pcDiscard, ppcPlayerHand, m_gamelayout.pcDiscard, false);
		}
		SortDeck(ppcPlayerHand);
	}

	if (bDestructs)
	{
		// They desctructed the discard pile, first off triger
		//  a refresh so they can see it happen
		m_watcher->GameHasChanged();
        m_player->Played(&m_gamelayout);
#ifndef COMPUTER_VS_COMPUTER
		Sleep(500);
#endif

		// Go ahead and delete the discard pile
		xuntrack(m_gamelayout.pcDiscard);
		delete m_gamelayout.pcDiscard;
		m_gamelayout.pcDiscard = NULL;
	}


	if (m_gamelayout.pcDeck)
	{
		// There's still a draw deck, so give them cards
		//  until they have three
		int c = 0;
		pcTemp = *ppcPlayerHand;
		while (pcTemp)
		{
			c++;
			pcTemp = pcTemp->GetNext();
		}
		while (c < 3 && m_gamelayout.pcDeck)
		{
			c++;
			MoveCard(&m_gamelayout.pcDeck, ppcPlayerHand, m_gamelayout.pcDeck, false);
		}
		SortDeck(ppcPlayerHand);
	}

	if (bCanPlay)
	{
		// Something happened, so refresh the screen
		m_watcher->GameHasChanged();
        m_player->Played(&m_gamelayout);
	}

	if (*ppcPlayerHand == NULL &&
		*ppcPlayerUp == NULL &&
		*ppcPlayerDown == NULL)
	{
		// All of their hands are empty, guess it's the
		//  end of the game
		m_bGameOver = true;
		if (bComputer)
		{
			m_nLoses ++;
#ifndef COMPUTER_VS_COMPUTER
			m_watcher->GameIsOver(false);
#endif
		}
		else
		{
			m_nWins ++;
#ifndef COMPUTER_VS_COMPUTER
			m_watcher->GameIsOver(true);
#endif
		}
	}

	// Let the caller know what happened
	(*pbCardPlayed) = bCanPlay;
	(*pbDestructed) = bDestructs;
}


void CGame::DrawIt(HDC hdc, LPRECT lprt)
{
	CCard * pcCard = NULL;

	int x;
	int y;
	int nPlacePos = 0;

	int i;
	int c;
	bool bDown;

#define DIX(x) ((int)(((((double)x)/240.0)*((double)lprt->right))))
#define DIY(x) ((int)(((((double)x)/268.0)*((double)lprt->bottom))))
//#define DIX(x) (x)
//#define DIY(x) (x)

	y = DIY(110);
	x = DIX(30);

	// Reset the placement info
	for (i = 0; i < PLACEMENT_COUNT; i ++)
	{
		m_place[i].bPlaced = false;
		m_place[i].bDraw = false;
		m_place[i].bDiscard = false;
	}

	// How many cards are there in the deck?
	c = 0;
	pcCard = m_gamelayout.pcDeck;
	while (pcCard)
	{
		c++;
		pcCard = pcCard->GetNext();
	}

	// Draw the deck
	pcCard = m_gamelayout.pcDeck;
	if (c > 0)
	{
		while (pcCard)
		{
			PlaceCard(hdc, x, y, pcCard, true, &nPlacePos);
			if (c % 10 == 0)
			{
				// This just gives some illusion of depth to the deck
				x += 2;
				y += 1;
			}
			c--;
			pcCard = pcCard->GetNext();
		}
	}
	else
	{
		// Nothing here, just draw a "ghost" card
		m_place[nPlacePos].bPlaced = true;
		m_place[nPlacePos].pcCard = NULL;
		m_place[nPlacePos].bDraw = true;
		m_place[nPlacePos].rtPlace.left = x;
		m_place[nPlacePos].rtPlace.top = y;
		m_place[nPlacePos].rtPlace.bottom = y + m_nCardY;
		m_place[nPlacePos].rtPlace.right = x + m_nCardX;
		nPlacePos ++;

		cdtDraw(hdc, x, y, m_nCardX, m_nCardY, 
			0, GHOST);
	}

	y = DIY(110);
	x += DIX(50);

	// Draw the discard pile
	c = 0;
	pcCard = m_gamelayout.pcDiscard;
	while (pcCard)
	{
		c++;
		pcCard = pcCard->GetNext();
	}
	if (c > 0)
	{
		pcCard = m_gamelayout.pcDiscard;
		while (pcCard)
		{
			PlaceCard(hdc, x, y, pcCard, false, &nPlacePos);
			if (c < 5)
			{
				// Make sure you can see the top few cards
				x += DIX(10);
			}
			else
			{
				// Just give a hint of how many are left
				x += 1;
			}
			pcCard = pcCard->GetNext();
			c--;
		}
	}
	else
	{
		// No discard pile, just draw the ghost card
		cdtDraw(hdc, x, y, m_nCardX, m_nCardY, 
			0, GHOST);
		m_place[nPlacePos].bPlaced = true;
		m_place[nPlacePos].pcCard = NULL;
		m_place[nPlacePos].bDiscard = true;
		m_place[nPlacePos].rtPlace.left = x;
		m_place[nPlacePos].rtPlace.top = y;
		m_place[nPlacePos].rtPlace.bottom = y + m_nCardY;
		m_place[nPlacePos].rtPlace.right = x + m_nCardX;
		nPlacePos ++;
	}


	bool bComputer;
	for (i = 0; i < 2; i ++)
	{
		// Draw each player's hands
		int yStart;
		int xStart;
		int xDir;
		CCard ** pcPerson;
		if (i == 0)
		{
			bComputer = false;
			xDir = 1;
			yStart = DIY(5);
			xStart = DIX(5);
			pcPerson = m_gamelayout.pcPlayer;
		}
		else
		{
			bComputer = true;
			xDir = -1;
			xStart = DIX(200);
			yStart = DIY(170);
			pcPerson = m_gamelayout.pcComputer;
		}

		// Draw the face down cards
		pcCard = pcPerson[handDown];
		y = yStart;
		x = xStart;
		while (pcCard != NULL)
		{
			if (m_bGameOver)
			{
				bDown = false;
			}
			else
			{
				bDown = true;
			}
			if (pcCard->GetPlaceHolder() == false)
			{
				PlaceCard(hdc, x, y, pcCard, bDown, &nPlacePos);
			}
			x += DIX(35) * xDir;
			pcCard = pcCard->GetNext();
		}

		// Now the face up cards
		pcCard = pcPerson[handUp];
		if (m_bGameOver)
		{
			y = yStart + DIY(10);
			x = xStart + DIX(10);
		}
		else
		{
			y = yStart + DIY(2);
			x = xStart + DIX(2);
		}
		while (pcCard != NULL)
		{
			bDown = false;
			if (pcCard->GetPlaceHolder() == false)
			{
				PlaceCard(hdc, x, y, pcCard, bDown, &nPlacePos);
			}
			x += DIX(35) * xDir;
			pcCard = pcCard->GetNext();
		}

		// Draw the actual hand
		int xOver = DIX(25);
		pcCard = pcPerson[handHand];
		c=0;
		int nRealCount = 0;
		int nLastType = -1;
		bool bGroupCards = m_bOptGroupCards;
		while (pcCard != NULL)
		{
			nRealCount++;
			if (m_bOptGroupCards)
			{
				// For the player's hand, only need room for
				//  the first card in a series
				if (bComputer)
				{
					c++;
				}
				else
				{
					if (pcCard->GetType() != nLastType)
					{
						c++;
						nLastType = pcCard->GetType();
					}
				}
			}
			else
			{
				c++;
			}
			pcCard = pcCard->GetNext();
		}

		if (bGroupCards)
		{
			if (c != nRealCount)
			{
				if (xOver * nRealCount <= DIX(200))
				{
					c = nRealCount;
					bGroupCards = false;
				}
			}
		}
		// small hack to make it fit on the screen.  There's barely
		// enough room if they eat the entire deck
		if (xOver * c > DIX(200))
		{
			xOver = DIX(200 / c);
		}

		// Now draw the hand
		y = yStart + DIY(45);
		x = xStart;
		x += DIX(10) * xDir;
		pcCard = pcPerson[handHand];
		nLastType = -1;
		int yHand = y;
		while (pcCard != NULL)
		{
			if (bComputer)
			{
                if (m_bGameOver)
                {
                    bDown = false;
                }
                else
                {
				    bDown = true;
                }
			}
			else
			{
				bDown = false;
			}

			if (m_bOptGroupCards)
			{
				// Simple hack to group similiar cards together
                if (bGroupCards)
                {
				    if (!bComputer)
				    {
					    if (nLastType == pcCard->GetType())
					    {
						    y += DIY(5);
						    x -= xOver * xDir;
					    }
					    else
					    {
						    nLastType = pcCard->GetType();
						    y = yHand;
						    int nSameCard = 0;
						    CCard * pcTemp = pcCard;
						    while (pcTemp && pcTemp->GetType() == pcCard->GetType())
						    {
							    nSameCard ++;
							    pcTemp = pcTemp->GetNext();
						    }
						    y += DIY((4 - nSameCard) * 5);
					    }
				    }
                }
                else
                {
                    y = yHand;
                    y += DIY((4 - 1) * 5);
                }
			}

			PlaceCard(hdc, x, y, pcCard, bDown, &nPlacePos);
			x += xOver * xDir;
			pcCard = pcCard->GetNext();
		}

	}

}

void CGame::CanPlayCard(CCard * pcCard, bool * pbCanPlay, bool * pbDestructs)
{
	// See what would happen if a card is played.

	(*pbCanPlay) = false;
	(*pbDestructs) = false;

	// A ten always destructs
	if (pcCard->GetType() == typeTen)
	{
		(*pbCanPlay) = true;
		(*pbDestructs) = true;
		return;
	}

	CCard * pcTop[2];

	// Need to keep track of what the top two cards on the discard pile are
	pcTop[0] = NULL;
	pcTop[1] = NULL;

	CCard * pcTemp = m_gamelayout.pcDiscard;

	while (pcTemp)
	{
		pcTop[0] = pcTop[1];
		pcTop[1] = pcTemp;
		pcTemp = pcTemp->GetNext();
	}

	// If it's a two or ace, they can always play it
	if (pcCard->GetType() == typeTwo ||
		pcCard->GetType() == typeAce)
	{
		(*pbCanPlay) = true;
	}
	else
	{
		if (pcTop[1])
		{
			// Some logic because you can't put anything on top
			// of an ace (and it has the lowest numerical value)
			if (pcTop[1]->GetType() == typeAce)
			{
				if (pcTop[1]->GetType() == pcCard->GetType())
				{
					(*pbCanPlay) = true;
				}
			}
			else
			{
				// Just a normal card, so just compare the numeric value
				if (pcCard->GetType() >= pcTop[1]->GetType())
				{
					(*pbCanPlay) = true;
				}
			}
		}
		else
		{
			// There's no discard pile, you can play anything
			(*pbCanPlay) = true;
		}
	}

	if (*pbCanPlay)
	{
		// They can play the card, see if it makes three of a kind on the discard
		//  pile and destructs it
		if (pcTop[1] != NULL &&
			pcTop[0] != NULL)
		{
			if (pcTop[1]->GetType() == pcCard->GetType() &&
				pcTop[0]->GetType() == pcCard->GetType())
			{
				(*pbDestructs) = true;
			}
		}
	}

}

void CGame::MoveCard(CCard ** ppcFrom, CCard ** ppcTo, CCard * pcCard, bool bLeavePlaceHolder)
{
	// Moves a card from one deck to another,
	//  bLeavePlaceHolder causes a place holder card to be placed
	//  where the card came from.

	CCard * pcPlace;
	if (bLeavePlaceHolder)
	{
		pcPlace = new CCard;
		xtrack(pcPlace);
		pcPlace->SetPlaceHolder(true);
	}

	CCard * pcLast;
	CCard * pcTemp;

	// Find the card in the from deck
	if ((*ppcFrom) == pcCard)
	{
		// It's the first card, this is easy
		if (bLeavePlaceHolder)
		{
			(*ppcFrom) = pcPlace;
			pcPlace->SetNext(pcCard->GetNext());
		}
		else
		{
			(*ppcFrom) = (*ppcFrom)->GetNext();
		}
		pcCard->SetNext(NULL);
	}
	else
	{
		// it's somewhere else, find it and take it out
		//  of the linked list
		pcLast = NULL;
		pcTemp = (*ppcFrom);
		{
			while (pcTemp != pcCard)
			{
				pcLast = pcTemp;
				pcTemp = pcTemp->GetNext();
			}
			if (bLeavePlaceHolder)
			{
				pcLast->SetNext(pcPlace);
				pcPlace->SetNext(pcCard->GetNext());
			}
			else
			{
				pcLast->SetNext(pcCard->GetNext());
			}
			pcCard->SetNext(NULL);
		}
	}

	// Now we get to put it in the new deck, at the end
	// of the linked list
	pcTemp = (*ppcTo);
	if (pcTemp == NULL)
	{
		(*ppcTo) = pcCard;
	}
	else
	{
		while (pcTemp->GetNext())
		{
			pcTemp = pcTemp->GetNext();
		}
		pcTemp->SetNext(pcCard);
	}


	// Check to see if all we left behind was a deck
	//  of placeholders
	if (bLeavePlaceHolder)
	{
		bool bAllPlace = true;
		pcTemp = (*ppcFrom);
		while (pcTemp)
		{
			if (pcTemp->GetPlaceHolder() == false)
			{
				bAllPlace = false;
			}
			pcTemp = pcTemp->GetNext();
		}
		if (bAllPlace)
		{
			xuntrack((*ppcFrom));
			delete (*ppcFrom);
			(*ppcFrom) = NULL;
		}
	}

}

void CGame::Tapped(int x, int y)
{
	// someone tapped on the game, figure out what card they tapped on

    if (!m_bPlayerTurn)
    {
        // it's not their turn!
        return;
    }

	POINT pt;
	pt.x = x;
	pt.y = y;
	CCard * pcCard = NULL;
	int i = 0;

	while (m_place[i].bPlaced)
	{
		if (PtInRect(&m_place[i].rtPlace, pt))
		{
			pcCard = m_place[i].pcCard;
		}
		i++;
	}

	if (pcCard == NULL)
	{
		// They didn't tap on anything
		return;
	}

	if (pcCard->GetPlaceHolder())
	{
		// They tapped on a place holder, we don't care
		return;
	}

	// Let's see if they tapped on a card in their hand.
	CCard * pcTemp = m_gamelayout.pcPlayer[handHand];
	bool bInHand = false;
	int cCards = 0;
	CCard * pcTypes[4];

	while (pcTemp)
	{
		if (pcTemp == pcCard)
		{
			bInHand = true;
		}
		if (pcTemp->GetType() == pcCard->GetType())
		{
			ASSERT(cCards < 4);
			pcTypes[cCards] = pcTemp;
			cCards ++;
		}
		pcTemp = pcTemp->GetNext();
	}
	if (bInHand && cCards > 1)
	{
        bool bCanPlay = false;
        bool bDestructs = false;
        CanPlayCard(pcTypes[0], &bCanPlay, &bDestructs);
        if (bCanPlay)
        {
		    // They picked something that they can play and they have 
            // more than one of the same type in their hand. Let them 
            // pick how many of these cards to drop
		    int nToDrop = m_watcher->GetNumberToDrop(cCards);
		    ASSERT(nToDrop >= 1);
		    ASSERT(nToDrop <= 4);
		    ASSERT(nToDrop <= cCards);

		    // PlayCard() only looks after pcCard for similiar 
		    // cards, so use that to our advantage
		    pcCard = pcTypes[cCards - nToDrop];
        }
	}


	// Play the card they tapped on
	bool bPlayed = false;
	bool bDestructed = false;

	PlayCard(false, pcCard, &bPlayed, &bDestructed);

	if (bPlayed && !bDestructed)
	{
		//Looks like they were able to play the card, and it didn't
		// destruct the deck, time for the computer to make a move:
#ifndef COMPUTER_VS_COMPUTER
        Sleep(500);
#endif
        m_bPlayerTurn = false;
        m_player->YourTurn();
	}

}

void CGame::PlayedCard(CCard * pcCard)
{
    // Allright, the computer like object played something, let's do it.
    bool bPlayed;
    bool bDestructed;

    PlayCard(true, pcCard, &bPlayed, &bDestructed);
    if (bDestructed)
    {
        //They get to play again
        m_player->YourTurn();
    }
    else
    {
        // Computer's turn is over
        m_bPlayerTurn = true;
    }

}

void CGame::PlaceCard(HDC hdc, int x, int y, CCard * pcCard, bool bDown, int * nPlacePos)
{
	//Takes care of drawing the card and adding the information for later hit testing

	int nFaceDown;
	switch (m_nOptCard)
	{
	case 1:
		nFaceDown = IDFACEDOWN1;
		break;
	case 2:
		nFaceDown = IDFACEDOWN2;
		break;
	case 3:
		nFaceDown = IDFACEDOWN3;
		break;
	case 4:
		nFaceDown = IDFACEDOWN4;
		break;
	case 5:
		nFaceDown = IDFACEDOWN5;
		break;
	default:
		nFaceDown = IDFACEDOWN6;
		break;
	}


	cdtDraw(hdc, x, y, m_nCardX, m_nCardY, 
		bDown?nFaceDown:pcCard->GetPegCard(), 
		bDown?FACEDOWN:FACEUP);

	m_place[*nPlacePos].pcCard = pcCard;
	m_place[*nPlacePos].bPlaced = true;
	m_place[*nPlacePos].bFaceDown = bDown;
	m_place[*nPlacePos].rtPlace.left = x;
	m_place[*nPlacePos].rtPlace.top = y;
	m_place[*nPlacePos].rtPlace.right = x + m_nCardX;
	m_place[*nPlacePos].rtPlace.bottom = y + m_nCardY;

	(*nPlacePos) ++;
}

CGame::CGame()
{
    m_bGameOver = true;
    m_player = NULL;

	DWORD dwSetting;
	CRegistryKey * reg;

	reg = new CRegistryKey(HKEY_LOCAL_MACHINE, MY_REGKEY);
	xtrack(reg);

	if (reg->GetRegValueDW(_T("EndGame"),dwSetting)) {
		m_bOptEndGame = (dwSetting==1?true:false);
	} else {
		m_bOptEndGame = false;
	}

	if (reg->GetRegValueDW(_T("Diff"),dwSetting)) {
		m_nOptDiff = dwSetting;
	} else {
		m_nOptDiff = 1;
	}

	if (reg->GetRegValueDW(_T("GroupCards"),dwSetting)) {
		m_bOptGroupCards = (dwSetting==1?true:false);
	} else {
		m_bOptGroupCards = false;
	}

	if (reg->GetRegValueDW(_T("Card"),dwSetting)) {
		m_nOptCard = dwSetting;
	} else {
		m_nOptCard = 3;
	}

	if (reg->GetRegValueDW(_T("Wins"),dwSetting)) {
		m_nWins = dwSetting;
	} else {
		m_nWins = 0;
	}

	if (reg->GetRegValueDW(_T("Loses"),dwSetting)) {
		m_nLoses = dwSetting;
	} else {
		m_nLoses = 0;
	}

	xuntrack(reg);
	delete reg;

	m_watcher = NULL;
	cdtInit(&m_nCardX, &m_nCardY);

	m_gamelayout.pcDeck = NULL;
	m_gamelayout.pcDiscard = NULL;
	int i;
	for (i = 0; i < handCount; i ++)
	{
		m_gamelayout.pcPlayer[i] = NULL;
		m_gamelayout.pcComputer[i] = NULL;
	}

	sgenrand(GetTickCount());

#ifdef COMPUTER_VS_COMPUTER
    m_nLoses = 0;
    m_nWins = 0;
#endif
}

CGame::~CGame()
{
    if (!m_bGameOver)
    {
        m_nLoses ++;
    }

    if (m_player)
    {
        xuntrack(m_player);
        delete m_player;
        m_player = NULL;
    }

	DWORD dwSetting;
	CRegistryKey * reg;

	reg = new CRegistryKey(HKEY_LOCAL_MACHINE, MY_REGKEY);
	xtrack(reg);

	dwSetting = m_nOptDiff;
	reg->SetRegValueDW(_T("Diff"), dwSetting);

	dwSetting = m_bOptEndGame?1:0;
	reg->SetRegValueDW(_T("EndGame"), dwSetting);

	dwSetting = m_bOptGroupCards?1:0;
	reg->SetRegValueDW(_T("GroupCards"), dwSetting);

	dwSetting = m_nOptCard;
	reg->SetRegValueDW(_T("Card"), dwSetting);

	dwSetting = m_nWins;
	reg->SetRegValueDW(_T("Wins"), dwSetting);

	dwSetting = m_nLoses;
	reg->SetRegValueDW(_T("Loses"), dwSetting);

	xuntrack(reg);
	delete reg;
	
	if (m_gamelayout.pcDeck)
	{
		xuntrack(m_gamelayout.pcDeck);
		delete m_gamelayout.pcDeck;
		m_gamelayout.pcDeck = NULL;
	}
	if (m_gamelayout.pcDiscard)
	{
		xuntrack(m_gamelayout.pcDiscard);
		delete m_gamelayout.pcDiscard;
		m_gamelayout.pcDiscard = NULL;
	}
	int i;
	for (i = 0; i < handCount; i ++)
	{
		if (m_gamelayout.pcPlayer[i])
		{
			xuntrack(m_gamelayout.pcPlayer[i]);
			delete m_gamelayout.pcPlayer[i];
			m_gamelayout.pcPlayer[i] = NULL;
		}
		if (m_gamelayout.pcComputer[i])
		{
			xuntrack(m_gamelayout.pcComputer[i]);
			delete m_gamelayout.pcComputer[i];
			m_gamelayout.pcComputer[i] = NULL;
		}
	}
}

void CGame::Init(IGameWatcher * watcher)
{
	m_watcher = watcher;
}

void CGame::DealNewGame()
{
    if (!m_bGameOver)
    {
        m_nLoses ++;
    }

	m_bGameOver = false;
    m_bPlayerTurn = true;

	if (m_gamelayout.pcDeck)
	{
		xuntrack(m_gamelayout.pcDeck);
		delete m_gamelayout.pcDeck;
		m_gamelayout.pcDeck = NULL;
	}
	if (m_gamelayout.pcDiscard)
	{
		xuntrack(m_gamelayout.pcDiscard);
		delete m_gamelayout.pcDiscard;
		m_gamelayout.pcDiscard = NULL;
	}
	int i;
	for (i = 0; i < handCount; i ++)
	{
		if (m_gamelayout.pcPlayer[i])
		{
			xuntrack(m_gamelayout.pcPlayer[i]);
			delete m_gamelayout.pcPlayer[i];
			m_gamelayout.pcPlayer[i] = NULL;
		}
		if (m_gamelayout.pcComputer[i])
		{
			xuntrack(m_gamelayout.pcComputer[i]);
			delete m_gamelayout.pcComputer[i];
			m_gamelayout.pcComputer[i] = NULL;
		}
	}

	// A reall cheap way to shuffle the deck, just
	//  randomly sort it
	CCard * pcDeck[52];
	for(i = 0; i < 52; i ++)
	{
		pcDeck[i] = new CCard(i, (int) genrand());
		xtrack(pcDeck[i]);
	}

	qsort(pcDeck, 52, sizeof(pcDeck[0]), xSortDeck);

	int nCardPos = 0;

	int j;
	for (i = 0; i < 3; i ++)
	{
		for (j = 0; j < handCount; j ++)
		{
			DealCard(&nCardPos, pcDeck, &m_gamelayout.pcPlayer[j]);
			DealCard(&nCardPos, pcDeck, &m_gamelayout.pcComputer[j]);

			if (j == handHand)
			{
				SortDeck(&m_gamelayout.pcPlayer[j]);
				SortDeck(&m_gamelayout.pcComputer[j]);
			}
		}
	}

	if (m_bOptEndGame)
    {
        // No starting deck, delete the remaining cards
        for (i = nCardPos; i < 52; i++)
        {
            xuntrack(pcDeck[i]);
            delete pcDeck[i];
        }
    }
    else
	{
        // Deal the remaining cards into the starting deck
		while (nCardPos < 52)
		{
			DealCard(&nCardPos, pcDeck, &m_gamelayout.pcDeck);
		}
	}

	m_watcher->GameHasChanged();
    LoadPlayer();

#ifdef COMPUTER_VS_COMPUTER

    CPlayComp2 me;
	CPlayer * playerTemp;
    CDummyWatcher dw;
    me.InitPlayer(&dw);
    me.NewDeck(&m_gamelayout);

    bool bPlayed;
    bool bDestructed;
    int nTurns = 0;

    while (!m_bGameOver)
    {
        if (m_bPlayerTurn)
        {
            do
            {
                CCard * pcTemp;
                int i;

                for (i = 0; i < handCount; i++)
                {
                    pcTemp = m_gamelayout.pcPlayer[i];
                    m_gamelayout.pcPlayer[i] = m_gamelayout.pcComputer[i];
                    m_gamelayout.pcComputer[i] = pcTemp;
                }
				playerTemp = m_player;
				m_player = &me;
                me.YourTurn();
                for (i = 0; i < handCount; i++)
                {
                    pcTemp = m_gamelayout.pcPlayer[i];
                    m_gamelayout.pcPlayer[i] = m_gamelayout.pcComputer[i];
                    m_gamelayout.pcComputer[i] = pcTemp;
                }
                PlayCard(false, dw.m_pcCard, &bPlayed, &bDestructed);
				m_player = playerTemp;
            } while (bDestructed);
            m_bPlayerTurn = false;
        }
        else
        {
            // The interface takes care of all game logic
            m_player->YourTurn();
        }
        nTurns ++;
        if (nTurns > 1000)
        {
            break;
        }
    }
        

#endif

}

void CGame::DealCard(int * nCardPos, CCard ** pcDeck, CCard ** pcDest)
{
	CCard * pcNewCard = pcDeck[*nCardPos];
	CCard * pcOldCard = *pcDest;
	pcNewCard->SetNext(pcOldCard);
	(*pcDest) = pcNewCard;
	(*nCardPos) ++;
}

void CGame::SortDeck(CCard ** pcCard)
{

	if (*pcCard == NULL)
	{
		return;
	}

	// Put the deck into an normal array
	int nCount = 0;
	CCard * pcDeck[52];
	while (*pcCard)
	{
		pcDeck[nCount] = *pcCard;

		// The Suit is added in to provide a constant sorting
		//  otherwise the hand might change a bit from one
		//  sort to the next
		if (pcDeck[nCount]->GetType() == typeAce)
		{
			// Put the aces at the end, it looks more correct
			pcDeck[nCount]->SetOrder(pcDeck[nCount]->GetSuit() + (14 * 4));
		}
		else
		{
			pcDeck[nCount]->SetOrder(
				(pcDeck[nCount]->GetType())*4 + 
				pcDeck[nCount]->GetSuit());
		}

		(*pcCard) = (*pcCard)->GetNext();
		nCount ++;
	}

	// Sort it
	qsort(pcDeck, nCount, sizeof(pcDeck[0]), xSortDeck);

	// Now put the array back to a linked list
	int i;
	for (i = 0; i < nCount; i ++)
	{
		CCard * pcOld = (*pcCard);
		*pcCard = pcDeck[i];
		(*pcCard)->SetNext(pcOld);
	}

}

int __cdecl CGame::xSortDeck(const void *elem1, const void *elem2)
{
	CCard * pc1 = *((CCard**)elem1);
	CCard * pc2 = *((CCard**)elem2);

	if (pc1->GetOrder() > pc2->GetOrder())
	{
		return -1;
	}
	else if (pc1->GetOrder() < pc2->GetOrder())
	{
		return 1;
	}

	return 0;
}

int CGame::GetWins()
{
	return m_nWins;
}

int CGame::GetLoses()
{
	return m_nLoses;
}

void CGame::ResetWinsLoses()
{
	m_nWins = 0;
	m_nLoses = 0;
}

int CGame::GetCardX()
{
	return m_nCardX;
}

int CGame::GetCardY()
{
	return m_nCardY;
}

void CGame::SetOptGroupCards(bool bGroupCards)
{
	m_bOptGroupCards = bGroupCards;
}

bool CGame::GetOptGroupCards()
{
	return m_bOptGroupCards;
}

bool CGame::GameInProgress()
{
    return !m_bGameOver;
}

void CGame::SetOptDiff(int nDiff)
{
	m_nOptDiff = nDiff;
    if (m_player)
    {
        LoadPlayer();
    }
}

int CGame::GetOptDiff()
{
	return m_nOptDiff;
}


void CGame::LoadPlayer()
{
    if (m_player)
    {
        xuntrack(m_player);
        delete m_player;
        m_player = NULL;
    }

	if (m_nOptDiff == 1)
	{
		m_player = new CPlayComp1();
		xtrack(m_player);
	}
	else
	{
		m_player = new CPlayComp2();
		xtrack(m_player);
	}

    m_player->InitPlayer(this);
    m_player->NewDeck(&m_gamelayout);

}


bool CGame::IsInDraw(POINT pt)
{
	CCard * pcCard = NULL;
    CCard * pcTemp = NULL;
	int i = 0;

	while (m_place[i].bPlaced)
	{
		if (PtInRect(&m_place[i].rtPlace, pt))
		{
			pcCard = m_place[i].pcCard;
		}
		i++;
	}

	if (pcCard == NULL)
	{
		// They didn't tap on anything
		return false;
	}

    pcTemp = m_gamelayout.pcDeck;
    while (pcTemp)
    {
        if (pcTemp == pcCard)
        {
            return true;
        }
        pcTemp = pcTemp->GetNext();
    }

    return false;

}

bool CGame::IsInDiscard(POINT pt)
{
	CCard * pcCard = NULL;
    CCard * pcTemp = NULL;
	int i = 0;

	while (m_place[i].bPlaced)
	{
		if (PtInRect(&m_place[i].rtPlace, pt))
		{
			pcCard = m_place[i].pcCard;
		}
		i++;
	}

	if (pcCard == NULL)
	{
		// They didn't tap on anything
		return false;
	}

    pcTemp = m_gamelayout.pcDiscard;
    while (pcTemp)
    {
        if (pcTemp == pcCard)
        {
            return true;
        }
        pcTemp = pcTemp->GetNext();
    }

    return false;

}

int CGame::NumberOfDraw()
{
    CCard * pcTemp = m_gamelayout.pcDeck;
    int nRet = 0;
    while (pcTemp)
    {
        nRet ++;
        pcTemp = pcTemp->GetNext();
    }
    return nRet;
}

int CGame::NumberOfDiscard()
{
    CCard * pcTemp = m_gamelayout.pcDiscard;
    int nRet = 0;
    while (pcTemp)
    {
        nRet ++;
        pcTemp = pcTemp->GetNext();
    }
    return nRet;
}

char * CGameLayout::Serialize()
{
	char * szCards = (char *) LocalAlloc(LPTR, 70);
	xtrack(szCards);

	int nPos = 0;
	CCard * pcCard;

	pcCard = pcDeck;
	while (pcCard)
	{
		szCards[nPos] = pcCard->Serialize();
		nPos ++;
		pcCard = pcCard->GetNext();
	}
	szCards[nPos] = (char) 2;
	nPos++;

	pcCard = pcDiscard;
	while (pcCard)
	{
		szCards[nPos] = pcCard->Serialize();
		nPos ++;
		pcCard = pcCard->GetNext();
	}
	szCards[nPos] = (char) 2;
	nPos++;

	int i;
	for (i = 0; i < handCount; i ++)
	{
		pcCard = pcPlayer[i];
		while (pcCard)
		{
			szCards[nPos] = pcCard->Serialize();
			nPos ++;
			pcCard = pcCard->GetNext();
		}
		szCards[nPos] = (char) 2;
		nPos++;
	}

	for (i = 0; i < handCount; i ++)
	{
		pcCard = pcComputer[i];
		while (pcCard)
		{
			szCards[nPos] = pcCard->Serialize();
			nPos ++;
			pcCard = pcCard->GetNext();
		}
		szCards[nPos] = (char) 2;
		nPos++;
	}


	szCards[nPos] = 0;

	return szCards;
}

void CGameLayout::Serialize(char * szCards)
{

	int nPos = 0;
	int i;
	SerializeToDeck(&nPos, szCards, &pcDeck);
	SerializeToDeck(&nPos, szCards, &pcDiscard);
	for (i = 0; i < handCount; i ++)
	{
		SerializeToDeck(&nPos, szCards, &pcPlayer[i]);
	}
	for (i = 0; i < handCount; i ++)
	{
		SerializeToDeck(&nPos, szCards, &pcComputer[i]);
	}
}

void CGameLayout::SerializeToDeck(int * pnPos, char * szCards, CCard ** ppcCard)
{
	if (*ppcCard)
	{
		xuntrack((*ppcCard));
		delete(*ppcCard);
		(*ppcCard) = NULL;
	}
	CCard * pcLast = NULL;
	CCard * pcTemp;

	while (szCards[*pnPos] != (char) 2)
	{
		pcTemp = new CCard(szCards[*pnPos]);
		xtrack(pcTemp);
		if (pcLast == NULL)
		{
			(*ppcCard) = pcTemp;
		}
		else
		{
			pcLast->SetNext(pcTemp);
		}
		pcLast = pcTemp;
		(*pnPos) ++;
	}
	(*pnPos) ++;
}