// FNC_CHM_SYS__JGLEE.h : main header file for the FNC_CHM_SYS__JGLEE DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFNC_CHM_SYS__JGLEEApp
// See FNC_CHM_SYS__JGLEE.cpp for the implementation of this class
//

class CFNC_CHM_SYS__JGLEEApp : public CWinApp
{
public:
	CFNC_CHM_SYS__JGLEEApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
