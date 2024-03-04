// Forward declares

enum enumHands;

class IGameWatcher;

class CGame;
class CCard;
class CardPlacement;
class CGameLayout;

#if defined(DEBUG) || defined(_DEBUG)
// Allright, this is a hack.  This enables the computer to play against
//  itself.  Somewhat useful for testing out AIs.
//#define COMPUTER_VS_COMPUTER
#endif

#ifndef GAME_H__INCLUDED_
#define GAME_H__INCLUDED_

#include "Player.h"
#include "Card.h"
#include "Registry.h"
#include "Rand.h"

#include "PlayComp1.h"
#include "PlayComp2.h"

#define PLACEMENT_COUNT 70 // Number of entires for hit testing

#ifdef COMPUTER_VS_COMPUTER
class CDummyWatcher : public IPlayerWatcher
{
public:
    void PlayedCard(CCard * pcCard) 
    {
        m_pcCard = pcCard;
    }

    CCard * m_pcCard;
};
#endif

// Our watcher
class IGameWatcher
{
public:
	// Something about the game probably changed, suggest a repaint
	virtual void GameHasChanged() = 0;

	// Need to ask the user how many cards to drop.  nMax is the number
	//  of cards that can be dropped (2 to 4)
	virtual int GetNumberToDrop(int nMax) = 0;

	// You should tell the user they won or lost the game
	virtual void GameIsOver(bool bWon) = 0;

	// Do you want to play more than one of the face up card you picked?
	virtual void PlaceMultiFaceUp(int * nToPlay, TCHAR * szType) = 0;

	// Do you want to also eat one of the cards?
	virtual void EatOneCard(int * nEatCard, TCHAR ** szType) = 0;
};

enum enumHands // Each player has three hands
{
	handHand, // The hand
	handUp, // Face up cards (may include placeholders)
	handDown, // Face down cards  (may include placeholders)
	handCount,
};

class CardPlacement
{
public:
	CCard * pcCard; // The card being referenced
	bool bPlaced; // Is this a valid entry?
	bool bFaceDown; // Is the card face down?
	bool bDraw; // Is this the empty draw pile?
	bool bDiscard; // Is this the empty discard pile?
	RECT rtPlace; // Rectangle of card
};

// The layout of all the cards
class CGameLayout
{
public:
    CCard * pcDeck; // The draw deck of cards
	CCard * pcDiscard; // The discard pile
	CCard * pcPlayer[handCount]; // The player's hands
	CCard * pcComputer[handCount]; // The computer's hands

	char *	Serialize();
	void	Serialize(char * szCards);
	void	SerializeToDeck(int * pnPos, char * szCards, CCard ** ppcCard);
};

class CGame : public IPlayerWatcher
{
public:
			CGame();
			~CGame();
			
	void	Init(IGameWatcher * watcher); //Pass in the watcher

	void	DealNewGame(); // Deals a new game, can start anytime
	void	DrawIt(HDC hdc, LPRECT rt); // Request to draw the current game

	void	Tapped(int x, int y); // Someone tapped on the game

    // Is the point in the deck?
    bool    IsInDraw(POINT pt);
    bool    IsInDiscard(POINT pt);

    // How many of these cards are there?
    int     NumberOfDraw();
    int     NumberOfDiscard();

	// Options
	void	SetOptEndGame(bool bEndGame); 
	void	SetOptCard(int nCardNum);
	void	SetOptGroupCards(bool bGroupCards);
	void	SetOptDiff(int nDiff);
	bool	GetOptEndGame();
	int		GetOptCard();
	bool	GetOptGroupCards();
	int		GetOptDiff();

	// Total number of wins and loses
	int		GetWins();
	int		GetLoses();
	void	ResetWinsLoses();

	// Draw the back of a card
	void	DrawBackCard(HDC hdc, int x, int y, int nCard);

	// Width and height of a card
	int		GetCardX();
	int		GetCardY();

    // Is a game currently being played?
    bool    GameInProgress();

    // IPlayerWatcher
    void    PlayedCard(CCard * pcCard);
private:
	// "Deals" a card from an array.  nCardPos is the current position in the array
	void	DealCard(int * nCardPos, CCard ** pcDeck, CCard ** pcDest);

	// Sorts a deck, putting aces at the end
	// (yes, the computer gets a different sorting, no, it's not cheating)
	void	SortDeck(CCard ** pcCard);
	static int __cdecl xSortDeck(const void *elem1, const void *elem2);

	// Draws a card onto the display, nPlacePos is the current index into m_place
	void	PlaceCard(HDC hdc, int x, int y, CCard * pcCard, bool bDown, int * nPlacePos);

	// Determines if a card is playable, and if it destructs the deck
	void	CanPlayCard(CCard * pcCard, bool * bCanPlay, bool * bDestructs);

	// Moves a card from one deck to another
	// (bLeavePlaceHolder leaves a place holder so the remaining cards are
	//  in the same position.  If only placeholders are left the deck is deleted)
	void	MoveCard(CCard ** ppcFrom, CCard ** ppcTo, CCard * pcCard, bool bLeavePlaceHolder);

	// Logic for playing a card
	void	PlayCard(bool bComputer, CCard * pcCard, bool * bCardPlayed, bool * bDestructed);

    // Loads the appropriate player object.  Can be called in the
    //  middle of a game.
    void    LoadPlayer();

	IGameWatcher * m_watcher; // Our watcher

	// Basic placement of cards, place holders, and the draw and discard
	//  piles (if visible).  Used for hit testing.  Created on paints.
	CardPlacement	m_place[PLACEMENT_COUNT];

    // The computer, or other, player
    CPlayer * m_player;

	// Width and height of cards
	int		m_nCardX;
	int		m_nCardY;

    // The current placement of all the cards
    CGameLayout m_gamelayout;

    // Total number of games won and lost
	int		m_nWins;
	int		m_nLoses;

	bool	m_bGameOver; // Is the game over?
    bool    m_bPlayerTurn; // Is it the player's turn?

	bool	m_bOptEndGame; // Don't start the game with a draw pile
	int		m_nOptCard; // The selected cards (1 .. 6)
	bool	m_bOptGroupCards; // Group similiar cards together in
	                          //  the player's hand
	int		m_nOptDiff; // The AI's difficulty

};

#endif