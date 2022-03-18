// JGLEE__IMG_MNG.h : main header file for the JGLEE__IMG_MNG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CJGLEE__IMG_MNGApp
// See JGLEE__IMG_MNG.cpp for the implementation of this class
//

class CJGLEE__IMG_MNGApp : public CWinApp
{
public:
	CJGLEE__IMG_MNGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
