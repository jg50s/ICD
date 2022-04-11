// PHY_RS485__MFC_UNIT.h : main header file for the PHY_RS485__MFC_UNIT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_RS485__MFC_UNITApp
// See PHY_RS485__MFC_UNIT.cpp for the implementation of this class
//

class CPHY_RS485__MFC_UNITApp : public CWinApp
{
public:
	CPHY_RS485__MFC_UNITApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
