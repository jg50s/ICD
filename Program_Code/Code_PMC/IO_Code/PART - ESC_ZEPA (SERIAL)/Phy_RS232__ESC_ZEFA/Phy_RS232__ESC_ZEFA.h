// Phy_RS232__ESC_ZEFA.h : main header file for the Phy_RS232__ESC_ZEFA DLL
//

#if !defined(AFX_Phy_RS232__ESC_ZEFA_H__280941B1_B365_4272_BEAF_DC5D3B5050E1__INCLUDED_)
#define AFX_Phy_RS232__ESC_ZEFA_H__280941B1_B365_4272_BEAF_DC5D3B5050E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPhy_RS232__ESC_ZEFAApp
// See Phy_RS232__ESC_ZEFA.cpp for the implementation of this class
//

class CPhy_RS232__ESC_ZEFAApp : public CWinApp
{
public:
	CPhy_RS232__ESC_ZEFAApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#endif