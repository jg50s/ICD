// Phy_IO__MKS_GAUGE.h : main header file for the Phy_IO__MKS_GAUGE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__MKS_GAUGEApp
// See Phy_IO__MKS_GAUGE.cpp for the implementation of this class
//

class CPhy_IO__MKS_GAUGEApp : public CWinApp
{
public:
	CPhy_IO__MKS_GAUGEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
