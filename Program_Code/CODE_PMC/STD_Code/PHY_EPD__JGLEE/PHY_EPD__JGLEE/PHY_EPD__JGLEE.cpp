// PHY_EPD__JGLEE.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "PHY_EPD__JGLEE.h"

#ifdef _DEBUG
#define new PHY_EPD__JGLEE
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CPHY_EPD__JGLEEApp

BEGIN_MESSAGE_MAP(CPHY_EPD__JGLEEApp, CWinApp)
END_MESSAGE_MAP()


// CPHY_EPD__JGLEEApp construction

CPHY_EPD__JGLEEApp::CPHY_EPD__JGLEEApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPHY_EPD__JGLEEApp object

CPHY_EPD__JGLEEApp theApp;


// CPHY_EPD__JGLEEApp initialization

BOOL CPHY_EPD__JGLEEApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
