class CPlayer;
class IPlayerWatcher;

#ifndef PLAYCOMP2_H__INCLUDED__
#define PLAYCOMP2_H__INCLUDED__

#include "Card.h"
#include "Game.h"

class CPlayComp2 : public CPlayer
{
public:
            CPlayComp2();
            ~CPlayComp2();

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

    int m_nDiscardScore;
    int m_nDiscardCount;
    int m_nDrawCount;
    int m_nHandScore;
    int m_nHandCount;
    int m_nTypeCount[typeCount];

    int m_nScore[typeCount];
    int m_nOrder[typeCount];
};


#endif