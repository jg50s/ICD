// PHY_IO_CTRL__JGLEE.h : main header file for the PHY_IO_CTRL__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPMC__PHY_IOALPHAApp
// See PHY_IO_CTRL__JGLEE.cpp for the implementation of this class
//

class CPMC__PHY_IOALPHAApp : public CWinApp
{
public:
	CPMC__PHY_IOALPHAApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
