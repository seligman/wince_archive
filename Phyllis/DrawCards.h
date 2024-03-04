HINSTANCE ourCardLibrary = 0;
extern HINSTANCE g_hInstance;
#define WPC
typedef long X;
typedef long Y;
typedef long DX;
typedef long DY;
typedef long RA;
typedef long SU;
typedef long CD;
typedef long SCO;
typedef long SMD;
#define IDACLUBS        1
#define ID2CLUBS        2
#define ID3CLUBS        3
#define ID4CLUBS        4
#define ID5CLUBS        5
#define ID6CLUBS        6
#define ID7CLUBS        7
#define ID8CLUBS        8
#define ID9CLUBS        9
#define IDTCLUBS        10
#define IDJCLUBS        11
#define IDQCLUBS        12
#define IDKCLUBS        13
#define IDADIAMONDS     14
#define ID2DIAMONDS     15
#define ID3DIAMONDS     16
#define ID4DIAMONDS     17
#define ID5DIAMONDS     18
#define ID6DIAMONDS     19
#define ID7DIAMONDS     20
#define ID8DIAMONDS     21
#define ID9DIAMONDS     22
#define IDTDIAMONDS     23
#define IDJDIAMONDS     24
#define IDQDIAMONDS     25
#define IDKDIAMONDS     26
#define IDAHEARTS       27
#define ID2HEARTS       28
#define ID3HEARTS       29
#define ID4HEARTS       30
#define ID5HEARTS       31
#define ID6HEARTS       32
#define ID7HEARTS       33
#define ID8HEARTS       34
#define ID9HEARTS       35
#define IDTHEARTS       36
#define IDJHEARTS       37
#define IDQHEARTS       38
#define IDKHEARTS       39
#define IDASPADES       40
#define ID2SPADES       41
#define ID3SPADES       42
#define ID4SPADES       43
#define ID5SPADES       44
#define ID6SPADES       45
#define ID7SPADES       46
#define ID8SPADES       47
#define ID9SPADES       48
#define IDTSPADES       49
#define IDJSPADES       50
#define IDQSPADES       51
#define IDKSPADES       52
#define IDFACEDOWNFIRST 61
#define IDFACEDOWN1     61
#define IDFACEDOWN2     62
#define IDFACEDOWN3     63
#define IDFACEDOWN4     64
#define IDFACEDOWN5     65
#define IDFACEDOWN6     66
#define IDFACEDOWNLAST  66
#define IDANNFACE1_1    69
#define IDANNFACE1_2    70
#define IDANNFACE1_1W   10
#define IDANNFACE1_1H   10
#define IDANNFACE1_1X   14
#define IDANNFACE1_1Y    7

#define IDANNFACE2_1    71
#define IDANNFACE2_1W   19
#define IDANNFACE2_1H   17
#define IDANNFACE2_1X   9
#define IDANNFACE2_1Y   1
#define IDANNFACE2_2    72
#define IDANNFACE2_2W   19
#define IDANNFACE2_2H   17
#define IDANNFACE2_2X   9
#define IDANNFACE2_2Y   1

#define IDANNFACE3_1    73
#define IDANNFACE3_1W   27
#define IDANNFACE3_1H   7
#define IDANNFACE3_1X   1
#define IDANNFACE3_1Y   18
#define IDANNFACE3_2    74
#define IDANNFACE3_2W   27
#define IDANNFACE3_2H   7
#define IDANNFACE3_2X   1
#define IDANNFACE3_2Y   18

#define IDANNFACE4_1    75
#define IDANNFACE4_1W   12
#define IDANNFACE4_1H   10
#define IDANNFACE4_1X   14
#define IDANNFACE4_1Y   16
#define IDANNFACE4_2    76
#define IDANNFACE4_2W   12
#define IDANNFACE4_2H   10
#define IDANNFACE4_2X   14
#define IDANNFACE4_2Y   16

#define IDANNFACE6_1    77
#define IDANNFACE6_1W   9
#define IDANNFACE6_1H   5
#define IDANNFACE6_1X   2
#define IDANNFACE6_1Y   2

#define IDCARDO         78
#define IDCARDX         79

#define IDCARDGHOST     80

#define ColorRGB(r,g,b)    RGB(r,g,b)

#define ColorRGBBlack      RGB(  0,   0,   0)
#define ColorRGBDarkGray   RGB(128, 128, 128)
#define ColorRGBLightSilver   RGB(192, 192, 192)
#define ColorRGBWhite      RGB(255, 255, 255)
#define ColorRGBRed        RGB(255,   0,   0)
#define ColorRGBGreen      RGB(  0, 255,   0)
#define ColorRGBBlue    RGB(  0,   0, 255)
#define ColorRGBCyan    RGB(  0, 255, 255)
#define ColorRGBMagenta    RGB(255,   0, 255)
#define ColorRGBYellow     RGB(255, 255,   0)
#define ColorRGBDarkRed    RGB(128,   0,   0)
#define ColorRGBDarkGreen  RGB(  0, 128,   0)
#define ColorRGBDarkBlue   RGB(  0,   0, 128)
#define ColorRGBDarkCyan   RGB(  0, 128, 128)
#define ColorRGBDarkMagenta   RGB(128,   0, 128)
#define ColorRGBDarkYellow RGB(128, 128,   0)

#define cdNil           0x3c
#define cIDFACEDOWN     (IDFACEDOWNLAST-IDFACEDOWNFIRST+1)
#define icolNil         -1
#define icrdNil         0x1fff
#define icrdEmpty       0x1ffe
#define icrdToEnd       0x1ffd
#define ccrdToEnd       -2
#define icrdEnd         0x1ffc
#define bitFZip         0x2000
#define icrdMask        0x1fff
#define CLOADMAX        1
#define FACEUP          0
#define FACEDOWN        1
#define HILITE          2
#define GHOST           3
#define REMOVE          4
#define INVISIBLEGHOST  5
#define DECKX           6
#define DECKO           7
#define icrdUndoMax     52
#define drwInit         1
#define drwDrawCard     2
#define drwClose        3
#define BFT_BITMAP      0x4d42
#define icrdDeckMax     52
#define icrdDiscardMax  (icrdDeckMax-(1+2+3+4+5+6+7))
#define icrdFoundMax    13
#define icrdTabMax      19
#define YCARD_MARGIN 6

#define ABS(x) (((x) < 0) ? -(x) : (x))
#define EOS    '\0'
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define TSIZE sizeof(TCHAR)
#define BUFSIZE 80

#define suClub              0
#define suDiamond           1
#define suHeart             2
#define suSpade             3
#define suMax               4
#define suFirst             suClub
#define raAce               0
#define raDeuce             1
#define raTres              2
#define raFour              3
#define raFive              4
#define raSix               5
#define raSeven             6
#define raEight             7
#define raNine              8
#define raTen               9
#define raJack              10
#define raQueen             11
#define raKing              12
#define raMax               13
#define raNil               15
#define raFirst             raAce

#define msgcNil             0
#define msgcInit            1
#define msgcEnd             2
#define msgcClearCol        3
#define msgcNumCards        4
#define msgcHit             5
#define msgcSel             6
#define msgcEndSel          7
#define msgcFlip            8
#define msgcInvert          9
#define msgcMouseUp         10
#define msgcDblClk          11
#define msgcRemove          12
#define msgcInsert          13
#define msgcMove            14
#define msgcCopy            15
#define msgcValidMove       16
#define msgcValidMovePt     17
#define msgcRender          18
#define msgcPaint           19
#define msgcDrawOutline     20
#define msgcComputeCrdPos   21
#define msgcDragInvert      22
#define msgcGetPtInCrd      23
#define msgcShuffle         26
#define msgcAnimate         27
#define msgcZip             28
#define msggInit            0
#define msggEnd             1
#define msggKeyHit          2
#define msggMouseDown       3
#define msggMouseUp         4
#define msggMouseMove       5
#define msggMouseDblClk     6
#define msggPaint           7
#define msggDeal            8
#define msggUndo            9
#define msggSaveUndo        10
#define msggKillUndo        11
#define msggIsWinner        12
#define msggWinner          13
#define msggScore           14
#define msggChangeScore     15
#define msggDrawStatus      16
#define msggTimer           17

#define SuFromCd(cd) ((cd) & 0x03)
#define RaFromCd(cd) ((cd) >> 2)

typedef struct _del
{
    DX dx;
    DY dy;
} DEL;

typedef struct _rc
{
    X xLeft;
    Y yTop;
    X xRight;
    Y yBot;
} RC;

typedef struct _crd
{
    unsigned cd  : 15;
    unsigned fUp : 1;
    POINT pt;
} CRD;

typedef struct _colcls
{
    int tcls;
    int (FAR *lpfnColProc)();
    int ccolDep;
    DX dxUp;
    DY dyUp;
    DX dxDn;
    DY dyDn;
    int dcrdUp;
    int dcrdDn;
} COLCLS;

typedef struct _move
{
    int icrdSel;
    int ccrdSel;
    DEL delHit;
    BOOL fHdc;
    DY dyCol;
    HDC hdcScreen;
    HDC hdcCol;
    HBITMAP hbmColOld;
    HDC hdcScreenSave;
    HBITMAP hbmScreenSaveOld;
    HDC hdcT;
    HBITMAP hbmT;
    int izip;
} MOVE;

typedef struct _col
{
    COLCLS *pcolcls;
    int (FAR *lpfnColProc)();
    RC rc;
    MOVE *pmove;
    int icrdMac;
    int icrdMax;
    CRD rgcrd[1];
} COL;

typedef struct _udr
{
    BOOL fAvail;
    int sco;
    int irep;
    int icol1;
    int icol2;
    COL *rgpcol[2];
} UDR;

typedef struct _gm
{
    int (FAR *lpfnGmProc)();
    UDR udr;
    BOOL fDealt;
    BOOL fInput;
    BOOL fWon;
    int sco;
    UINT iqsecScore;
    UINT dqsecScore;
    int ccrdDeal;
    int irep;
    POINT ptMousePrev;
    BOOL fButtonDown;
    int icolSel;
    int icolHilight;
    DY   dyDragMax;
    int icolMac;
    int icolMax;
    COL *rgpcol[1];
} GM;

typedef struct _cddr
{
    HDC hdc;
    int x;
    int y;
    int cd;
    int mode;
    DWORD rgbBgnd;
} CDDR;



void MyDeleteHbm(HBITMAP hbm);
typedef struct {
	int id;
	DX dx;
	DY dy;
} SPR;
#define isprMax 4

typedef struct {
	int cdBase;
	DX dxspr;
	DY dyspr;
	int isprMac;
	SPR rgspr[isprMax];
} ANI;

#ifndef WPC
#define ianiMax 4
static const ANI rgani[ianiMax] = {
	IDFACEDOWN2, IDANNFACE2_1W, IDANNFACE2_1H, 2,
	{IDANNFACE2_1, IDANNFACE2_1X, IDANNFACE2_1Y,
	IDFACEDOWN2, IDANNFACE2_1X, IDANNFACE2_1Y,
	0, 0, 0,
	0, 0, 0},
	IDFACEDOWN3, IDANNFACE3_1W, IDANNFACE3_1H, 3,
	{IDANNFACE3_1, IDANNFACE3_1X, IDANNFACE3_1Y,
	IDANNFACE3_2, IDANNFACE3_1X, IDANNFACE3_1Y,
	IDFACEDOWN3, IDANNFACE3_1X, IDANNFACE3_1Y,
	0, 0, 0},
	IDFACEDOWN4, IDANNFACE4_1W, IDANNFACE4_1H, 4,
	{IDANNFACE4_1, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDANNFACE4_2, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDANNFACE4_1, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDFACEDOWN4, IDANNFACE4_1X, IDANNFACE4_1Y},
	IDFACEDOWN5, IDANNFACE5_1W, IDANNFACE5_1H, 4,
	{IDANNFACE5_1, IDANNFACE5_1X, IDANNFACE5_1Y,
	IDANNFACE5_2, IDANNFACE5_1X, IDANNFACE5_1Y,
	IDANNFACE5_1, IDANNFACE5_1X, IDANNFACE5_1Y,
	IDFACEDOWN5, IDANNFACE5_1X, IDANNFACE5_1Y}
};
#else
#define ianiMax 5
static const ANI rgani[ianiMax] = {
    IDFACEDOWN1, IDANNFACE1_1W, IDANNFACE1_1H, 3,
	{IDANNFACE1_1, IDANNFACE1_1X, IDANNFACE1_1Y,
	IDANNFACE1_2, IDANNFACE1_1X, IDANNFACE1_1Y,
	IDFACEDOWN1, IDANNFACE1_1X, IDANNFACE1_1Y,
	0, 0, 0,
	},
	IDFACEDOWN2, IDANNFACE2_1W, IDANNFACE2_1H, 4,
	{IDANNFACE2_1, IDANNFACE2_1X, IDANNFACE2_1Y,
	IDANNFACE2_2, IDANNFACE2_1X, IDANNFACE2_1Y,
	IDANNFACE2_1, IDANNFACE2_1X, IDANNFACE2_1Y,
	IDFACEDOWN2,  IDANNFACE2_1X, IDANNFACE2_1Y},
	IDFACEDOWN3, IDANNFACE3_1W, IDANNFACE3_1H, 4,
	{IDANNFACE3_1, IDANNFACE3_1X, IDANNFACE3_1Y,
	IDANNFACE3_2, IDANNFACE3_1X, IDANNFACE3_1Y,
	IDANNFACE3_1, IDANNFACE3_1X, IDANNFACE3_1Y,
	IDFACEDOWN3,  IDANNFACE3_1X, IDANNFACE3_1Y},
	IDFACEDOWN4, IDANNFACE4_1W, IDANNFACE4_1H, 4,
	{IDANNFACE4_1, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDANNFACE4_2, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDANNFACE4_1, IDANNFACE4_1X, IDANNFACE4_1Y,
	IDFACEDOWN4, IDANNFACE4_1X, IDANNFACE4_1Y},
	IDFACEDOWN6, IDANNFACE6_1W, IDANNFACE6_1H, 2,
	{IDANNFACE6_1, IDANNFACE6_1X, IDANNFACE6_1Y,
	IDFACEDOWN6, IDANNFACE6_1X, IDANNFACE6_1Y,
	0, 0, 0,
	0, 0, 0},
};
#endif

int cardSizeX, cardSizeY;
static int cInits;
#define CARDS_DLL TEXT("PegCards.DLL")

BOOL cdtAnimate
// ************************************************************************************************
// Animate the backs of selected playing cards
// ************************************************************************************************
(HDC hdc,
 int cd,
 int x,
 int y,
 int ispr)
{
	int iani;
	const ANI *pani;
	const SPR *pspr;
	HBITMAP hbm, oldHbm;
	HDC hdcMem;
	X xSrc;
	Y ySrc;
	
	if (ispr < 0) return FALSE;
	for (iani = 0; iani < ianiMax; iani++) {
		if (cd == rgani[iani].cdBase) {
			pani = &rgani[iani];
			if (ispr < pani->isprMac) {
				pspr = &pani->rgspr[ispr];
				ASSERT(pspr->id != 0);
				if (pspr->id == cd) {xSrc = pspr->dx; ySrc = pspr->dy;}
				else xSrc = ySrc = 0;
				if (!(hbm = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(pspr->id)))) goto NoMemory;
				hdcMem = CreateCompatibleDC(hdc);
				if (hdcMem == NULL) {DeleteObject(hbm); goto NoMemory;}
				if ((oldHbm = (HBITMAP) SelectObject(hdcMem, hbm)) != NULL) {
					BitBlt(hdc, x+pspr->dx, y+pspr->dy, pani->dxspr, pani->dyspr, hdcMem, xSrc, ySrc,
						SRCCOPY);
					SelectObject(hdcMem, oldHbm);
				}
				DeleteDC(hdcMem);
				DeleteObject(hbm);
				return TRUE;
			}
		}
	}
	return FALSE;
	
NoMemory:
	return FALSE;
}


BOOL cdtDraw
// ************************************************************************************************
// Parameters:
//    hdc      HDC to window to draw cards on.
//    x, y     where you'd like them.
//    dx,dy    card extents
//    cd       card to be drawn
//    mode     way you want it drawn (face up or face down)
//
// Returns:
//    True if card successfully drawn, False otherwise
// ************************************************************************************************
(
 HDC hdc,
 int x,
 int y,
 int dx,
 int dy,
 int cd,
 int mode
 )
{
	HBITMAP hbmCard, oldHbm;
	HDC hdcMemory;
	DWORD dwRop;
	RECT rect;
	
	switch (mode) {
	default:
		ASSERT(FALSE);
		break;
	case FACEUP:
		hbmCard = LoadBitmap(ourCardLibrary,
			MAKEINTRESOURCE((RaFromCd(cd) % 13 + SuFromCd(cd) * 13) + 1));
		dwRop = SRCCOPY;
		break;
	case FACEDOWN:
		hbmCard = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(cd));
		dwRop = SRCCOPY;
		break;
	case REMOVE:
	case GHOST:
		SetRect(&rect, x, y, x + dx, y + dy);
		FillRect(hdc, &rect, (HBRUSH) GetStockObject(LTGRAY_BRUSH));
		if (mode == REMOVE) return TRUE;
		ASSERT(mode == GHOST);
	case INVISIBLEGHOST:
		hbmCard = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(IDCARDGHOST));
		dwRop = SRCAND;
		break;
	case DECKX:
		hbmCard = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(IDCARDX));
		dwRop = SRCCOPY;
		break;
	case DECKO:
		hbmCard = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(IDCARDO));
		dwRop = SRCCOPY;
		break;
    }
	if (!hbmCard) goto NoMemory;
	else {
		hdcMemory = CreateCompatibleDC( hdc);
		if (hdcMemory == NULL) goto NoMemory;
		if ((oldHbm = (HBITMAP) SelectObject(hdcMemory, hbmCard)) != NULL) {
			BitBlt(hdc, x, y, cardSizeX, cardSizeY, hdcMemory, 0, 0, dwRop);
			SelectObject(hdcMemory, oldHbm);
		}
		DeleteDC(hdcMemory);
		DeleteObject(hbmCard);
	}
	return TRUE;
	
NoMemory:
	if (hbmCard) DeleteObject(hbmCard);
	return FALSE;
}


BOOL cdtInit
// ************************************************************************************************
// cdtInit
//    Parameters:
//       pcardSizeX, pcardSizeY:  far pointers to ints where card size will be placed.
//    Returns:
//       True when successful, False when it can't find one of the standard bitmaps.
// ************************************************************************************************
(
 int FAR *pcardSizeX,
 int FAR *pcardSizeY
 )
{
	BITMAP bmCard;
	HBITMAP bitmap;

#ifdef UNDER_CE
	if (!ourCardLibrary) if (!(ourCardLibrary = LoadLibrary(CARDS_DLL))) return FALSE;
#else
	ourCardLibrary = g_hInstance;
#endif
	if (!(bitmap = LoadBitmap(ourCardLibrary, MAKEINTRESOURCE(IDCARDGHOST)))) return FALSE;
	GetObject(bitmap, sizeof(BITMAP), (LPSTR)&bmCard);
	cardSizeX = *pcardSizeX = bmCard.bmWidth;
	cardSizeY = *pcardSizeY = bmCard.bmHeight;
	DeleteObject(bitmap);
	return TRUE;
}

