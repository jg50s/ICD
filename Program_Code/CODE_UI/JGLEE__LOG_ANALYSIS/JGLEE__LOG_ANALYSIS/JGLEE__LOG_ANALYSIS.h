// JGLEE__LOG_ANALYSIS.h : main header file for the JGLEE__LOG_ANALYSIS DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__LOG_ANALYSISApp
// See JGLEE__LOG_ANALYSIS.cpp for the implementation of this class
//

class CJGLEE__LOG_ANALYSISApp : public CWinApp
{
public:
	CJGLEE__LOG_ANALYSISApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
