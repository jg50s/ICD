// PHY_IO__EDWARDS_TMP.h : main header file for the PHY_IO__EDWARDS_TMP DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPHY_IO__EDWARDS_TMPApp
// See PHY_IO__EDWARDS_TMP.cpp for the implementation of this class
//

class CPHY_IO__EDWARDS_TMPApp : public CWinApp
{
public:
	CPHY_IO__EDWARDS_TMPApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
