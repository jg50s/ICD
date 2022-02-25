// FA_LINK__S7Fy.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FA_LINK__S7Fy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
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

// CFA_LINK__S7FyApp

BEGIN_MESSAGE_MAP(CFA_LINK__S7FyApp, CWinApp)
END_MESSAGE_MAP()


// CFA_LINK__S7FyApp construction

CFA_LINK__S7FyApp::CFA_LINK__S7FyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CFA_LINK__S7FyApp object

CFA_LINK__S7FyApp theApp;


// CFA_LINK__S7FyApp initialization

BOOL CFA_LINK__S7FyApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
