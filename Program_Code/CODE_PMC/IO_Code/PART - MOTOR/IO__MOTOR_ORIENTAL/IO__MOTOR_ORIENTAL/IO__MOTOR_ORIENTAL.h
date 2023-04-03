// IO__MOTOR_ORIENTAL.h : main header file for the IO__MOTOR_ORIENTAL DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CIO__MOTOR_ORIENTALApp
// See IO__MOTOR_ORIENTAL.cpp for the implementation of this class
//

class CIO__MOTOR_ORIENTALApp : public CWinApp
{
public:
	CIO__MOTOR_ORIENTALApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
