#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


//-----------------------------------------------------------------------
#define  FILE_TYPE__GOI					 9
#define  FILE_TYPE__GI					10
#define  FILE_TYPE__BITMAP				11
#define  FILE_TYPE__PRI					12

#define  MODEL_TYPE__UNKNOWN			0
#define  MODEL_TYPE__LINE				10

#define  MODEL_TYPE__RECTANGLE			11		
#define  MODEL_TYPE__ELLIPSE			12
#define  MODEL_TYPE__POLYGON			13
#define  MODEL_TYPE__CURVE				14
#define  MODEL_TYPE__PRIMITIVE			15

#define  MODEL_TYPE__BITMAP_EX			20
#define  MODEL_TYPE__TEXT_EX			21
#define  MODEL_TYPE__ACTIVEX			22
#define  MODEL_TYPE__BACKGROUND			100
#define  MODEL_TYPE__BACKGROUND_EX		101

//-----------------------------------------------------------------------
#define  EVENT__CREATE_BUFFER			20000
#define  EVENT__PASTE					20031		// WM_COMMAND, model type, &screen_size, EVENT__PASTE, CDS_MODEL_FILE_INFO*
#define  EVENT__PASTE_CONTINUE			20032		// UNDO / REDO를 위해 필요
#define  EVENT__PASTE_END				20033
#define  EVENT__PASTE_SAME_FRAME		20034
#define  EVENT__PASTE_DIFF_FRAME		20035		//
#define  EVENT__DELETE					20040		// 현재 선택된 아이템 모두 삭제
#define  EVENT__ALIGN					20050		
#define  EVENT__MODEL_COUNT				20060		// 현재 모델 갯수 얻어옴
#define  EVENT__SELECT_MODEL_COUNT		20061		// 현재 선택된 모델 갯수 얻어옴
#define  EVENT__GET_MODEL_TYPE			20062
#define  EVENT__LOAD_MODEL				20070
#define  EVENT__DRAW_ALL				20080
#define  EVENT__BLIT					20081
#define  EVENT__QUICK_MODE				20090		// Quick Mode  설정
#define  EVENT__CREATE					20100		// Model Create (WPARAM : pos, LPARAM : type)
#define  EVENT__SELECT					20110		// 마우스 클릭 select
#define  EVENT__INDEX_SELECT			20111		// 해당 index(WPARAM) select
#define  EVENT__DRAG_SELECT				20112
#define  EVENT__DESELECT				20113
#define  EVENT__GET_SELECT_AREA			20114		// 선택 영역을 얻는다.
#define  EVENT__GET_SELECT_INDEX		20115		// 마지막 선택된 모델의 index를 얻는다.
#define  EVENT__RSELECT					20116
#define  EVENT__SELECT_ALL				20117
#define  EVENT__SCALE					20120
#define  EVENT__SAVE_LIST				20130		// 현재 Frame의 Select List를 저장 한다.
#define  EVENT__REORDER					20200		// Order 변경
#define  EVENT__SET_BASIC_PROPERTY		20210
#define  EVENT__SET_PROPERTY_DATA		20211		// TOP BAR 변경 후 PROPERTY 적용
#define  EVENT__SET_EFFECT				20220
#define  EVENT__SET_BACKGROUND_FILE		20230
#define  EVENT__UNDO					20300
#define  EVENT__REDO					20301
#define  EVENT__MOVE_CENTER				20310
#define  EVENT__MOVE_LEFTTOP			20311
#define  EVENT__CONVERT_MODEL			20320
#define  EVENT__CONVERT_OLD_STR			20321
#define  EVENT__GET_MODEL_V2			20330
#define  EVENT__CHECK_LAST_MODEL		20340

#define  EVENT__GET_RECT				20341
#define  EVENT__GET_BACK_DC				20342
#define  EVENT__BACKUP					20343
#define  EVENT__DRAW_SELECT_RECT		20344
#define  EVENT__SELECT_SAME_MODEL		20345
#define  EVENT__INCREASE_PASTE_POS		20346

#define  EVENT__DRAW_ALL_GOBJ			20347
#define  EVENT__DRAW_RENAME_RECT        20348
#define  EVENT__DUPLICATE				20349

#define  EVENT__MOUSE_TEST				20351		// Mouse Test 설정
#define  EVENT__SELECT_CHECK			20352

//-----------------------------------------------------------------------
#define IS_PART_I(x)		((x > MODEL_TYPE__UNKNOWN) && (x < MODEL_TYPE__LINE))
#define IS_PRIMITIVE(x)		((x >= MODEL_TYPE__LINE) && (x <= MODEL_TYPE__PRIMITIVE))
#define IS_PART_II(x)		((IS_PRIMITIVE(x)) || x == MODEL_TYPE__BITMAP_EX || x == MODEL_TYPE__TEXT_EX || x == MODEL_TYPE__BACKGROUND_EX)

//-----------------------------------------------------------------------
enum UNDO_MODE
{
	UM_UNKNOWN = 0,
	UM_UNDO,
	UM_REDO,
};
enum UNDO_COMMAND
{
	UC_UNKNOWN = 0,
	UC_CREATE,
	UC_DELETE,
	UC_MOVE,
	UC_KEY_MOVE,
	UC_SCALE,
	UC_KEY_SCALE,
	UC_PASTE,
	UC_ALIGN,
};

class CDS_MODEL_INFO
{
public:
	CStringArray sCODE_LIST;
	CStringArray sVARIABLE_LIST;
	CStringArray sDATA_LIST;
	CUIntArray	 iTYPE_LIST;		// option (S-TYPE, V-TYPE)
};

class CDS_UNDO
{
public:
	void Copy(CDS_UNDO& undo)
	{
		CRect * newRect, *pRect;
		CDS_MODEL_FILE_INFO * pInfo, * dsInfo;
		int i, size;
		
		mCOMMAND = undo.mCOMMAND;
		mINDEX_LIST.Copy(undo.mINDEX_LIST);
		mMODEL_TYPE.Copy(undo.mMODEL_TYPE);
		
		size = undo.mMODEL_INFO.GetSize();
		for(i = 0; i < size; i++)
		{
			pInfo  = new CDS_MODEL_FILE_INFO;
			dsInfo = (CDS_MODEL_FILE_INFO *)undo.mMODEL_INFO.GetAt(i); 
			pInfo->sCODE_LIST.Copy(dsInfo->sCODE_LIST);
			pInfo->sPROPERTY_LIST.Copy(dsInfo->sPROPERTY_LIST);
			mMODEL_INFO.Add(pInfo);
		}
		size = undo.mBEFORE.GetSize();
		for(i = 0; i < size; i++)
		{
			newRect = new CRect;
			pRect   = (CRect *)undo.mBEFORE.GetAt(i); 
			newRect->CopyRect(pRect);
			mBEFORE.Add(newRect);
		}
		size = undo.mAFTER.GetSize();
		for(i = 0; i < size; i++)
		{
			newRect = new CRect;
			pRect   = (CRect *)undo.mAFTER.GetAt(i); 
			newRect->CopyRect(pRect);
			mAFTER.Add(newRect);
		}
	};

	int			mCOMMAND;
	CUIntArray	mINDEX_LIST;
	CUIntArray  mMODEL_TYPE;
	CPtrArray	mMODEL_INFO;		// DELETE시 CDS_MODEL_FILE_INFO ptr
	CPtrArray	mBEFORE;			// MOVE&SCALE / ALIGN
	CPtrArray	mAFTER;
};

class CFontInfo
{
public:
	void Copy(const CFontInfo& font_info)
	{
		mFONT	= font_info.mFONT;
		mCOLOR  = font_info.mCOLOR;
		iSIZE 	= font_info.iSIZE;
		iSTYLE	= font_info.iSTYLE;
	};
	CString		mFONT;
	COLORREF	mCOLOR;
	int			iSIZE;
	int			iSTYLE;
};

class CDS_CREATE_MODEL
{
public:
	CPoint	mPOINT;
	SIZE	mSCREEN_SIZE;
};

class CDS_PROPERTY__PRIMITIVE
{
public:
	void Copy(CDS_PROPERTY__PRIMITIVE& prop)
	{
		mCOLOR_PEN		= prop.mCOLOR_PEN;;
		mCOLOR_BRUSH	= prop.mCOLOR_BRUSH;
		iTYPE			= prop.iTYPE;	
		iWIDTH			= prop.iWIDTH;
		iALPHA			= prop.iALPHA;
		mST				= prop.mST;
		mET				= prop.mET;
		aX.RemoveAll();
		aX.Copy(prop.aX);
		aY.RemoveAll();
		aY.Copy(prop.aY);
	};
	COLORREF	mCOLOR_PEN;
	COLORREF	mCOLOR_BRUSH;
	int			iTYPE;
	int			iWIDTH;
	int			iALPHA;
	POINT		mST;
	POINT		mET;
	CUIntArray  aX;
	CUIntArray  aY;
};

class CDS_PROPERTY__PRI_PART
{
public:
	CString		mFILENAME;
	POINT		mST;
	POINT		mET;
};

class CDS_PROPERTY__TEXT_EX
{
public:
	void Copy(CDS_PROPERTY__TEXT_EX& prop)
	{
		mTEXT = prop.mTEXT;
		
		mFONT_INFO.Copy(prop.mFONT_INFO);
		mCOLOR_EFFECT = prop.mCOLOR_EFFECT;
		iEFFECT	= prop.iEFFECT;
		iALPHA	= prop.iALPHA;

		mST	= prop.mST;
		mET	= prop.mET;

		iFONT_WIDTH  = prop.iFONT_WIDTH;
		iFONT_HEIGHT = prop.iFONT_HEIGHT;
		iFONT_WEIGHT = prop.iFONT_WEIGHT;

		iFONT_COLOR_R = prop.iFONT_COLOR_R;
		iFONT_COLOR_G = prop.iFONT_COLOR_G;
		iFONT_COLOR_B = prop.iFONT_COLOR_B;
	};

	// ...
	CString	mTEXT;
	
	CFontInfo mFONT_INFO;
	COLORREF  mCOLOR_EFFECT;
	int	iEFFECT;
	int	iALPHA;

	POINT mST;
	POINT mET;

	int iFONT_WIDTH;
	int iFONT_HEIGHT;
	int iFONT_WEIGHT;

	int iFONT_COLOR_R;
	int iFONT_COLOR_G;
	int iFONT_COLOR_B;
};

class CDS_PROPERTY__BITMAP_EX
{
public:
	void Copy(CDS_PROPERTY__BITMAP_EX& prop)
	{
		mFILENAME		= prop.mFILENAME;
		mCOLOR_LOW		= prop.mCOLOR_LOW;
		mCOLOR_HIGH		= prop.mCOLOR_HIGH;
		mST				= prop.mST;
		mET				= prop.mET;
		iANGLE			= prop.iANGLE;
	};
	CString		mFILENAME;
	COLORREF	mCOLOR_LOW;
	COLORREF	mCOLOR_HIGH;
	POINT		mST;
	POINT		mET;
	int			iANGLE;
};

class CDS_PROPERTY
{
public:
	CDS_PROPERTY()
	{
		mFONT_INFO.mFONT = "Arial";
		mFONT_INFO.iSIZE = 9;
		mFONT_INFO.iSTYLE  = 0;
		mFONT_INFO.mCOLOR  = RGB(0,0,0);
		mCOLOR1 = RGB(0,0,0);
		mCOLOR2 = RGB(255,255,255);
		iDATA1  = 1;
		iDATA2  = 255;
	};
	void FromPrimitive(CDS_PROPERTY__PRIMITIVE * ptr)
	{
		mCOLOR1 = ptr->mCOLOR_PEN;
		mCOLOR2 = ptr->mCOLOR_BRUSH;
		iDATA1  = ptr->iWIDTH;
		iDATA2  = ptr->iALPHA;	
	};
	void FromText(CDS_PROPERTY__TEXT_EX * ptr)
	{
		mCOLOR1 = ptr->mFONT_INFO.mCOLOR;
		mCOLOR2 = ptr->mCOLOR_EFFECT;
		iDATA1  = 0;
		iDATA2  = ptr->iALPHA;

		mFONT_INFO.mFONT = ptr->mFONT_INFO.mFONT;
		mFONT_INFO.iSIZE = ptr->mFONT_INFO.iSIZE;
		mFONT_INFO.iSTYLE  = ptr->mFONT_INFO.iSTYLE;
		mFONT_INFO.mCOLOR  = ptr->mFONT_INFO.mCOLOR;
	};
	void FromBitmap(CDS_PROPERTY__BITMAP_EX * ptr)
	{
		mCOLOR1 = ptr->mCOLOR_LOW;
		mCOLOR2 = ptr->mCOLOR_HIGH;
		iDATA1  = ptr->iANGLE;
		iDATA2  = 0;
	};

	CFontInfo	mFONT_INFO;
	COLORREF	mCOLOR1;
	COLORREF	mCOLOR2;
	int			iDATA1;
	int			iDATA2;
};

class CDS_MODEL_V2
{
public:
	void Copy(CDS_MODEL_V2& dsMODEL)
	{
		iINDEX.Copy(dsMODEL.iINDEX);
		iTYPE.Copy(dsMODEL.iTYPE);
		sTITLE.Copy(dsMODEL.sTITLE);
	};
	CUIntArray	 iINDEX;
	CUIntArray	 iTYPE;
	CStringArray sTITLE;
};

enum ALIGN_MODE
{
	AM_UNKNOWN = 0,
	AM_LEFT,
	AM_TOP,
	AM_RIGHT,
	AM_BOTTOM,
	AM_WIDTH,
	AM_HEIGHT,
	AM_BOTH,
	AM_ACROSS,
	AM_DOWN
};			

enum EFFECT_MODE
{
	EFFECT_UNKNOWN = 0,
	EFFECT_BLOCK,
	EFFECT_SHADOW,
};
//-----------------------------------------------------------------------
