class CPlayer;
class IPlayerWatcher;

#ifndef PLAYCOMP1_H__INCLUDED__
#define PLAYCOMP1_H__INCLUDED__

#include "Card.h"
#include "Game.h"

class CPlayComp1 : public CPlayer
{
public:
            CPlayComp1();
            ~CPlayComp1();

// From CPlayer
    void InitPlayer(IPlayerWatcher * playerwatcher);
    void NewDeck(CGameLayout * gamelayout);
    void Played(CGameLayout * gamelayout);
    void YourTurn();
	void PlaceMultiFaceUp(int * nToPlay, enumType type);
	void EatOneCard(int * nEatCard);

private:
    void GetTopTwo();
    bool CanPlay(enumType type);
    bool CanPlayFromDeck(CCard * pcDeck, CCard ** pcCard);

    CCard * m_pcTop[2];

    IPlayerWatcher * m_playerwatcher;
    CGameLayout * m_gamelayout;
};


#endif