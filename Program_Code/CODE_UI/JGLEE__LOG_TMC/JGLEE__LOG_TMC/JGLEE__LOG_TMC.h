// JGLEE__LOG_TMC.h : main header file for the JGLEE__LOG_TMC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__LOG_TMCApp
// See JGLEE__LOG_TMC.cpp for the implementation of this class
//

class CJGLEE__LOG_TMCApp : public CWinApp
{
public:
	CJGLEE__LOG_TMCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
