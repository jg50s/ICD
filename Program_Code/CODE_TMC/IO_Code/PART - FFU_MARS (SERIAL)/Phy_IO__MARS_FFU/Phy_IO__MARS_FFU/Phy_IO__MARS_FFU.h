// Phy_IO__MARS_FFU.h : main header file for the Phy_IO__MARS_FFU DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__MARS_FFUApp
// See Phy_IO__MARS_FFU.cpp for the implementation of this class
//

class CPhy_IO__MARS_FFUApp : public CWinApp
{
public:
	CPhy_IO__MARS_FFUApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
