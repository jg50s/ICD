// TMC__FNC_PROC.h : main header file for the TMC__FNC_PROC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__FNC_PROCApp
// See TMC__FNC_PROC.cpp for the implementation of this class
//

class CTMC__FNC_PROCApp : public CWinApp
{
public:
	CTMC__FNC_PROCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
