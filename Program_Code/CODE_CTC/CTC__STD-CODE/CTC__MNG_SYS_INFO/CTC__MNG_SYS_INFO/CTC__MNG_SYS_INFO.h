// CTC__MNG_SYS_INFO.h : main header file for the CTC__MNG_SYS_INFO DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCTC__MNG_SYS_INFOApp
// See CTC__MNG_SYS_INFO.cpp for the implementation of this class
//

class CCTC__MNG_SYS_INFOApp : public CWinApp
{
public:
	CCTC__MNG_SYS_INFOApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
