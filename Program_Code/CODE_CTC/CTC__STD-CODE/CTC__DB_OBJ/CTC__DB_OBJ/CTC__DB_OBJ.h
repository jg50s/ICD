// CTC__DB_OBJ.h : main header file for the CTC__DB_OBJ DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__DB_OBJApp
// See CTC__DB_OBJ.cpp for the implementation of this class
//

class CCTC__DB_OBJApp : public CWinApp
{
public:
	CCTC__DB_OBJApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
