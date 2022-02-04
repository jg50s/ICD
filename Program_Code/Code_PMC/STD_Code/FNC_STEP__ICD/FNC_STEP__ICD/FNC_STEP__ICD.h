// FNC_STEP__ICD.h : main header file for the FNC_STEP__ICD DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFNC_STEP__ICDApp
// See FNC_STEP__ICD.cpp for the implementation of this class
//

class CFNC_STEP__ICDApp : public CWinApp
{
public:
	CFNC_STEP__ICDApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
