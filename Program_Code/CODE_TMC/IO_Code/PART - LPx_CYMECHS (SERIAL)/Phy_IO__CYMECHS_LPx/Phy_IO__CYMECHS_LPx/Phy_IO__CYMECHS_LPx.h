// Phy_IO__CYMECHS_LPx.h : main header file for the Phy_IO__CYMECHS_LPx DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__CYMECHS_LPxApp
// See Phy_IO__CYMECHS_LPx.cpp for the implementation of this class
//

class CPhy_IO__CYMECHS_LPxApp : public CWinApp
{
public:
	CPhy_IO__CYMECHS_LPxApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
