// JGLEE__RECIPE_STD.h : main header file for the JGLEE__RECIPE_STD DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__RECIPE_STDApp
// See JGLEE__RECIPE_STD.cpp for the implementation of this class
//

class CJGLEE__RECIPE_STDApp : public CWinApp
{
public:
	CJGLEE__RECIPE_STDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
