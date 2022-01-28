// TMC__INF_MODULE.h : main header file for the TMC__INF_MODULE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__INF_MODULEApp
// See TMC__INF_MODULE.cpp for the implementation of this class
//

class CTMC__INF_MODULEApp : public CWinApp
{
public:
	CTMC__INF_MODULEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
