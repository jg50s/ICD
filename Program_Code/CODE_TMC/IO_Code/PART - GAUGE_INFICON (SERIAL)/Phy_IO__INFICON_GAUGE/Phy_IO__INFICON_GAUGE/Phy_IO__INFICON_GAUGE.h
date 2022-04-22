// Phy_IO__INFICON_GAUGE.h : main header file for the Phy_IO__INFICON_GAUGE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__INFICON_GAUGEApp
// See Phy_IO__INFICON_GAUGE.cpp for the implementation of this class
//

class CPhy_IO__INFICON_GAUGEApp : public CWinApp
{
public:
	CPhy_IO__INFICON_GAUGEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
