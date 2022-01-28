// TMC__Fnc_VLV.h : main header file for the TMC__Fnc_VLV DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTMC__Fnc_VLVApp
// See TMC__Fnc_VLV.cpp for the implementation of this class
//

class CTMC__Fnc_VLVApp : public CWinApp
{
public:
	CTMC__Fnc_VLVApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
