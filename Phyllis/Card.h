class CCard;
enum enumSuit;
enum enumColor;
enum enumType;

// CCard - A card
//  CCard is also a poor man's linked list, so it's often
//  refered to as a deck.

#ifndef CARD_H__INCLUDED_
#define CARD_H__INCLUDED_

enum enumSuit
{
	suitDiamond,
	suitHeart,
	suitSpade,
	suitClub,
};

enum enumColor
{
	colorRed,
	colorBlack,
};

enum enumType
{
	typeAce,
	typeTwo,
	typeThree,
	typeFour,
	typeFive,
	typeSix,
	typeSeven,
	typeEight,
	typeNine,
	typeTen,
	typeJack,
	typeQueen,
	typeKing,
    typeCount,
};

class CCard
{
public:
				CCard();
				CCard(int nNewCard, int nNewOrder);
				CCard(char chrCard);
				~CCard();

	char		Serialize();
	void		Serialize(char chrCard);

	// Set the card number, 0 .. 51
	int			GetCard();
	void		SetCard(int nNewCard);

	// Retreive the card number for drawing the card
	int			GetPegCard();

	// Set the order number (this is just a number used by
	//  the sorting function in CGame)
	int			GetOrder();
	void		SetOrder(int nNewOrder);

	// Is this card really a place holder?
	bool		GetPlaceHolder();
	void		SetPlaceHolder(bool bNewPlaceHolder);

	// Poor man's linked list.  Just a reference to the next card
	//  in the deck.  This is delete with the card.
	CCard *		GetNext();
	void		SetNext(CCard * pcNewNext);

	enumSuit	GetSuit(); // Suit of card
	enumColor	GetColor(); // Color of card
	enumType	GetType(); // Type (one, two, three, ace, king, etc)

	LPTSTR		GetSuitSz(); // Human readable suit
	LPTSTR		GetTypeSz(); // Human readable card name

private:
	void		Init();

	int		m_nCard;
	int		m_nOrder;
	bool	m_bPlaceHolder;

	CCard *	m_pcNext;

	static const int	m_CardLookup[];
	static const LPTSTR	m_szSuits[];
	static const LPTSTR	m_szTypes[]; 
};

#endif
