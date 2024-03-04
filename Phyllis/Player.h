// These objects used to create a fully fledged player object

class CPlayer;
class IPlayerWatcher;

#ifndef PLAYER_H__INCLUDED__
#define PLAYER_H__INCLUDED__

#include "Game.h"
#include "Card.h"

// Virtual base for a player
class CPlayer
{
public:
    virtual void InitPlayer(IPlayerWatcher * playerwatcher) = 0;
    virtual void NewDeck(CGameLayout * gamelayout) = 0;
    virtual void Played(CGameLayout * gamelayout) = 0;
    virtual void YourTurn() = 0;
	virtual void PlaceMultiFaceUp(int * nToPlay, enumType type) = 0;
	virtual void EatOneCard(int * nEatCard) = 0;
};

// This is how cards are actually played
//  (Allows for a disconnect between when YourTurn, and PlayedCard happens)
class IPlayerWatcher
{
public:
    virtual void PlayedCard(CCard * pcCard) = 0;
};

#endif