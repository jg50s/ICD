// IO_RS232__VAT_APC.h : main header file for the IO_RS232__VAT_APC DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO_RS232__VAT_APCApp
// See IO_RS232__VAT_APC.cpp for the implementation of this class
//

class CIO_RS232__VAT_APCApp : public CWinApp
{
public:
	CIO_RS232__VAT_APCApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
