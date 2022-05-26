// IO_USB__SPECTROMETER.h : main header file for the IO_USB__SPECTROMETER DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO_USB__SPECTROMETERApp
// See IO_USB__SPECTROMETER.cpp for the implementation of this class
//

class CIO_USB__SPECTROMETERApp : public CWinApp
{
public:
	CIO_USB__SPECTROMETERApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
