// TMC__Fnc_LBx.h : main header file for the TMC__Fnc_LBx DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Fnc_LBxApp
// See TMC__Fnc_LBx.cpp for the implementation of this class
//

class CTMC__Fnc_LBxApp : public CWinApp
{
public:
	CTMC__Fnc_LBxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
