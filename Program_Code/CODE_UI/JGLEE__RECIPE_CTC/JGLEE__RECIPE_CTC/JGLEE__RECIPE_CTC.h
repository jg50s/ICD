// JGLEE__RECIPE_CTC.h : main header file for the JGLEE__RECIPE_CTC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__RECIPE_CTCApp
// See JGLEE__RECIPE_CTC.cpp for the implementation of this class
//

class CJGLEE__RECIPE_CTCApp : public CWinApp
{
public:
	CJGLEE__RECIPE_CTCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
