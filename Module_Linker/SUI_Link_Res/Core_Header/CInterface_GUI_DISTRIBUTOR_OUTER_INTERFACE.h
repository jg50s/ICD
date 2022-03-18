#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


//----------------------------------------------------
// EDITOR & DISTRIBUTOR

class CI_DISTRIBUTOR_OUTER_INFO_CTRL
{
public:
	virtual ~CI_DISTRIBUTOR_OUTER_INFO_CTRL(){};

	//-----------------------------------------
	virtual int System_Init() = 0;		
	virtual int System_Optimize() = 0;

	// scr_info : CDS_SCREEN_INFO
	virtual int System_Get_Info(void* scr_info,const double version=3.0) = 0;

	//-----------------------------------------
	virtual int Change__Seq_Info(const int module_id,
								 const CString& dir_root,
								 const CString& dir_config,
								 const CString& dir_datalog,
								 const CString& dir_process) = 0;

	//-----------------------------------------
	virtual int Debugger_Init(const CString& dir_goi) = 0;
};

class CI_DISTRIBUTOR_OUTER_CTRL
{
public:
	virtual ~CI_DISTRIBUTOR_OUTER_CTRL(){};

	//-----------------------------------------
	virtual int Screen_Open(const CString& file,const int type,const POINT& size,const HWND hwnd) = 0;
	virtual int Screen_Close() = 0;

	
	// scr_event : CDS_SCREEN_EVENT
	//
	//	(GUI-EXE)	WM_LBUTTONDOWN
	//	(GUI-EXE)	WM_LBUTTONUP
	//	(GUI-EXE)	WM_TIMER
	//
	//  (GUI-EXE)	EVENT__DESTROY
	//	(GUI-EXE)	EVENT__DRAW
	//				EVENT__MOVE				(pVOID = CDS_MODEL_POSITION)
	//				EVENT__SAVE				(pVOID = CString)
	//				EVENT__COPY				(pVOID = CDS_MODEL_FILE_INFO)
	//
	//				EVENT__RENAME_GET		(pVOID = CDS_MODEL_RENAME)
	//				EVENT__DYNAMIC_GET		(pVOID = CDS_MODEL_DYNAMIC)
	//
	//				EVENT__RENAME_SET		(pVOID = CDS_MODEL_RENAME)
	//				EVENT__DYNAMIC_SET		(pVOID = CDS_MODEL_DYNAMIC)
	//
	//	(GUI-EXE)	EVENT__VARIABLE_GET		(pVOID = CDS_SCREEN_VARIABLE)
	//	(GUI-EXE)	EVENT__VARIABLE_SET		(pVOID = CDS_SCREEN_VARIABLE)
	//		
	//	(GUI-EXE)	EVENT__CHANNEL_INFO		(pVOID = CDS_MODEL_CHANNEL_INFO)
	//
	//				(STRING : pVOID = CDS_PROPERTY__STRING)
	//				(BITMAP : pVOID = CDS_PROPERTY__BITMAP)
	//				(PART   : pVOID = CDS_PROPERTY__PART)
	//				(PDLL   : pVOID = CDS_PROPERTY__PDLL)
	//				EVENT__PROPERTY_GET		
	//				EVENT__PROPERTY_SET

	virtual int Screen_Event(const CString& log_id, void* scr_event, const double version=3.0) = 0;
};
//----------------------------------------------------
