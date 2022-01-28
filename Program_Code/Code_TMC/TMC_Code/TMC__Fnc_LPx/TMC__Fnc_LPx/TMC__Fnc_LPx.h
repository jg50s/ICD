// TMC__Fnc_LPx.h : main header file for the TMC__Fnc_LPx DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Fnc_LPxApp
// See TMC__Fnc_LPx.cpp for the implementation of this class
//

class CTMC__Fnc_LPxApp : public CWinApp
{
public:
	CTMC__Fnc_LPxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
