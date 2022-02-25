// CTC__Mng_OBJ.h : main header file for the CTC__Mng_OBJ DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__Mng_OBJApp
// See CTC__Mng_OBJ.cpp for the implementation of this class
//

class CCTC__Mng_OBJApp : public CWinApp
{
public:
	CCTC__Mng_OBJApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
