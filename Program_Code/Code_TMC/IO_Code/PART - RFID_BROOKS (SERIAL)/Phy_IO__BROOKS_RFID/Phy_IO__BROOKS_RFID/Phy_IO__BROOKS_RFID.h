// Phy_IO__BROOKS_RFID.h : main header file for the Phy_IO__BROOKS_RFID DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_IO__BROOKS_RFIDApp
// See Phy_IO__BROOKS_RFID.cpp for the implementation of this class
//

class CPhy_IO__BROOKS_RFIDApp : public CWinApp
{
public:
	CPhy_IO__BROOKS_RFIDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
