#pragma once

#ifndef _GUI_DS_H_
#define _GUI_DS_H_

//------------------------------------------------------------------------
#define  FILE_TYPE__SCR						1
#define  FILE_TYPE__MON						2
#define  FILE_TYPE__GP						3

//------------------------------------------------------------------------
#define  MODEL_TYPE__STRING					1
#define  MODEL_TYPE__BITMAP					2
#define  MODEL_TYPE__GP						3
#define  MODEL_TYPE__GI						4
#define  MODEL_TYPE__BACKGROUND_BMP			5
#define  MODEL_TYPE__FLASH					6
#define  MODEL_TYPE__GOI					7
#define  MODEL_TYPE__PAGE_EXE				8

#define  MODEL_TYPE__LINE					10
#define  MODEL_TYPE__RECTANGLE				11		
#define  MODEL_TYPE__ELLIPSE				12
#define  MODEL_TYPE__POLYGON				13
#define  MODEL_TYPE__CURVE					14
#define  MODEL_TYPE__PRIMITIVE				15
#define  MODEL_TYPE__BITMAP_EX				20
#define  MODEL_TYPE__TEXT_EX				21
#define  MODEL_TYPE__ACTIVEX				22
#define  MODEL_TYPE__PRI_PART				23

//------------------------------------------------------------------------
#define  EVENT__DESTROY						10001
#define  EVENT__DRAW  						10002
#define  EVENT__MOVE						10003
#define  EVENT__SAVE						10004
#define  EVENT__COPY						10005
#define  EVENT__PAINT						10006
#define  EVENT__INIT_SCREEN					10007
#define  EVENT__INIT_GOI					10008

#define  EVENT__RENAME_GET   				10011
#define  EVENT__RENAME_SET   				10012
#define  EVENT__DYNAMIC_GET					10013
#define  EVENT__DYNAMIC_SET					10014
#define  EVENT__VARIABLE_GET				10015
#define  EVENT__VARIABLE_SET				10017

#define  EVENT__CHANNEL_INFO				10021

#define  EVENT__PROPERTY_GET				10031
#define  EVENT__PROPERTY_SET				10032

#define  EVENT__HIDE						10041
#define  EVENT__FLASH_HIDE					10042
#define  EVENT__FLASH_SHOW					10043

#define  EVENT__SET_POSITION				10051
#define  EVENT__DRAW_BACK					10052


#define  CHANNEL_PREFIX__NONE				0
#define  CHANNEL_PREFIX__GUI				1
#define  CHANNEL_PREFIX__SEQ				2
#define  CHANNEL_PREFIX__LOG_SIM			3

#define  CHANNEL_SUFFIX__NONE				0
#define  CHANNEL_SUFFIX__STRING				1
#define  CHANNEL_SUFFIX__SETTO				2
#define  CHANNEL_SUFFIX__FEEDBACK			3
#define  CHANNEL_SUFFIX__RCP				4
#define  CHANNEL_SUFFIX__RCP_MIN			5
#define  CHANNEL_SUFFIX__RCP_MAX			6
#define  CHANNEL_SUFFIX__RCP_DEC			7
#define  CHANNEL_SUFFIX__FUNCTION			8
#define  CHANNEL_SUFFIX__RCP_HISTORY		9


#define  RENAME_COMMAND__NONE				0
#define  RENAME_COMMAND__FONTBOX			1		// @FONTBOX
#define  RENAME_COMMAND__LISTBOX			2		// @LISTBOX
#define  RENAME_COMMAND__CHANNEL			3		// @CHANNEL
#define  RENAME_COMMAND__RECIPE				4		// @COMMAND_RECIPE
#define  RENAME_COMMAND__COLOR				5		// @COLOR
#define  RENAME_COMMAND__FONTBOX_EX			6		// @FONTBOX.EX


//----------------------------------------------------
// EDITOR & DISTRIBUTOR

class CDS_SCREEN_INFO
{
public:
	void Copy(const CDS_SCREEN_INFO& scr_info)
	{
		sEXE_ROOT   = scr_info.sEXE_ROOT;

		sGUI_ROOT__RESOURCE = scr_info.sGUI_ROOT__RESOURCE;
		sGUI_ROOT__PAGE     = scr_info.sGUI_ROOT__PAGE;
		sGUI_SCREEN = scr_info.sGUI_SCREEN;

		sSEQ_ROOT    = scr_info.sSEQ_ROOT;
		sSEQ_CONFIG  = scr_info.sSEQ_CONFIG;
		sSEQ_DATALOG = scr_info.sSEQ_DATALOG;
		sSEQ_PROCESS = scr_info.sSEQ_PROCESS;

		//---------------------------------
		int i;
		int limit = scr_info.sDEFINE_LIST.GetSize();
		
		sDEFINE_LIST.RemoveAll();
		sDATA_LIST.RemoveAll();

		for(i=0;i<limit;i++)
		{
			sDEFINE_LIST.Add(scr_info.sDEFINE_LIST[i]);
			sDATA_LIST.Add(scr_info.sDATA_LIST[i]);
		}
		//---------------------------------
	}

	CString  sEXE_ROOT;

	CString  sGUI_ROOT__RESOURCE;
	CString  sGUI_ROOT__PAGE;
	CString  sGUI_SCREEN;

	CString  sSEQ_ROOT;
	CString  sSEQ_CONFIG;
	CString  sSEQ_DATALOG;
	CString  sSEQ_PROCESS;

	CStringArray sDEFINE_LIST;
	CStringArray sDATA_LIST;
};

class CDS_SCREEN_EVENT
{
public:
	CDS_SCREEN_EVENT()
	{
		hWND = NULL;

		iMESSAGE = 0;
		iWPARAM  = 0;
		iLPARAM  = 0;

		iCTRL_MODE = -1;
		pVOID = NULL;
		dVERSION = 3.0;

		//.....
		iCLEAR_REQ = -1;
	}

	HWND    hWND;
	UINT	iMESSAGE;
	WPARAM  iWPARAM;
	LPARAM  iLPARAM;

	int     iCTRL_MODE;
	void    *pVOID;
	double  dVERSION;

	//.....
	int     iCLEAR_REQ;
};

class CDS_SCREEN_VARIABLE
{
public:
	// CHANNEL_PREFIX__NONE
	// CHANNEL_PREFIX__INPUT
	// CHANNEL_PREFIX__OUTPUT
	CUIntArray	  iPREFIX_LIST;		

	CStringArray  sCHANNEL_LIST;
	CStringArray  sDATA_LIST;
};
//----------------------------------------------------

//----------------------------------------------------
class CDS_MODEL_FILE_INFO
{
public:
	CStringArray sPROPERTY_LIST;
	CStringArray sCODE_LIST;
};
//----------------------------------------------------

//----------------------------------------------------
// DISTRIBUTOR & LIBRARY

class CDS_MODEL_RESOURCE
{
public:
	CDS_MODEL_RESOURCE()
	{
		hDC = NULL;
		hDC_BACK = NULL;
		hDC_MEM  = NULL;
	}

	HDC hDC;
	HDC	hDC_BACK;
	HDC hDC_MEM;
};

class CDS_MODEL_POSITION
{
public:
	CDS_MODEL_POSITION()
	{
		mST.x = 0;
		mST.y = 0;
		mET.x = 0;
		mET.y = 0;
	}

	POINT mST;
	POINT mET;
};

class CDS_MODEL_DYNAMIC
{
public:
	CStringArray sCODE_LIST;
};
class CDS_MODEL_RENAME
{
public:
	CStringArray sVARIABLE_LIST;
	CUIntArray   iCONTROL_LIST;		// RENAME_COMMAND__NONE
									// RENAME_COMMAND__FONTBOX   (font box popup)
									// RENAME_COMMAND__LISTBOX	 (list box popup)
									// RENAME_COMMAND__CHANNEL   
									// RENAME_COMMAND__RECIPE    (list box popup)
									// RENAME_COMMAND__COLOR	 (color box popup)
	CStringArray sITEM_LIST;

	CStringArray sRENAME_LIST;
};
class CDS_MODEL_CHANNEL_INFO
{
public:
	// CHANNEL_PREFIX__NONE
	// CHANNEL_PREFIX__INPUT
	// CHANNEL_PREFIX__OUTPUT
	CUIntArray   iPREFIX_LIST;
	
	CStringArray sNAME_LIST;

	// CHANNEL_SUFFIX__NONE
	// CHANNEL_SUFFIX__STRING
	// CHANNEL_SUFFIX__SETTO
	// CHANNEL_SUFFIX__FEEDBACK
	CUIntArray   iSUFFIX_LIST;

	CStringArray sCONSTANT_LIST;
	CStringArray sDATA_LIST;
};
//----------------------------------------------------

//----------------------------------------------------
class CDS_PROPERTY__BACKGROUND_BMP
{
public:
	CDS_PROPERTY__BACKGROUND_BMP()
	{
		sFILE = "";

		pSIZE.x = 100;
		pSIZE.y = 100;
	}

	CString sFILE;
	POINT   pSIZE;
};
class CDS_PROPERTY__STRING
{
public:
	CDS_PROPERTY__STRING()
	{
		sTITLE = "STRING";
		
		pST.x = 10;
		pST.y = 10;

		pET.x = pST.x + 100;
		pET.y = pST.y + 100;

		sFONT_NAME   = "Impact";
		iFONT_WIDTH  = 9;
		iFONT_HEIGHT = 21;
		iFONT_WEIGHT = 200;

		iFONT_COLOR_R = 0;
		iFONT_COLOR_G = 0;
		iFONT_COLOR_B = 0;
	}

	CString sTITLE;
	POINT   pST;
	POINT   pET;

	CString sFONT_NAME;
	int     iFONT_WIDTH;
	int     iFONT_HEIGHT;
	int     iFONT_WEIGHT;
	int     iFONT_COLOR_R;
	int     iFONT_COLOR_G;
	int     iFONT_COLOR_B;
};
class CDS_PROPERTY__BITMAP
{
public:
	CDS_PROPERTY__BITMAP()
	{
		sFILE = "";

		pST.x = 10;
		pST.y = 10;

		pET.x = pST.x + 100;
		pET.y = pST.y + 100;

		iMASK_FLAG = 0;
	}

	CString sFILE;

	POINT pST;
	POINT pET;

	int   iMASK_FLAG;		// >= 1 : Enable,  < 1 : Disable 
};
class CDS_PROPERTY__PART
{
public:
	CDS_PROPERTY__PART()
	{
		sFILE = "";

		pST.x = 10;
		pST.y = 10;

		pET.x = pST.x + 100;
		pET.y = pST.y + 100;
	}

	CString sFILE;

	POINT pST;
	POINT pET;
	
};
class CDS_PROPERTY__PDLL
{
public:
	CDS_PROPERTY__PDLL()
	{
		sFILE = "";

		pST.x = 10;
		pST.y = 10;

		pET.x = pST.x + 100;
		pET.y = pST.y + 100;
	}

	CString sFILE;

	POINT pST;
	POINT pET;
};
//----------------------------------------------------

#endif
