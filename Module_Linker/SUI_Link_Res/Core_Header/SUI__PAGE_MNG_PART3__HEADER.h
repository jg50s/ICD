#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


//-----------------------------------------------------------------------------------
class CGUI_DISTRIBUTOR__PART_III__CREATE_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_III__CREATE_CTRL(){};

	//--------------------------------------------------------------------
	virtual int System_Init(const CDS_SCREEN_INFO& scr_info,
						    const int moduel_id = 0) = 0;
	virtual int System_Optimize() = 0;
	
	//--------------------------------------------------------------------
	// MODEL_TYPE
	// 1 : FLASH

	// ds_model : CDS_MODEL_FILE_INFO
	
	virtual void* Create_Model(const HWND& hwnd,
							   const void* ds_model,
							   const int type,
							   const int file_type = 1,
							   const int module_id = 0,
							   const double version=3.0) = 0;

	//--------------------------------------------------------------------
	virtual int Set_Real_Mode() = 0;
};

class CGUI_DISTRIBUTOR__PART_III__EVENT_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_III__EVENT_CTRL(){};


	//--------------------------------------------------------------------
	// ds_resource : CDS_MODEL_RESOURCE
	
	virtual int Set_Resource(const void* ds_resource,
						     const double version=3.0) = 0;


	//--------------------------------------------------------------------
	// model_ptr : CDS_DISTRIBUTOR_INFO::pMODEL_PTR
	// ds_pos : CDS_MODEL_POSITION
	
	virtual int Get_Model_Position(const void* model_ptr,
								   const int type,
								   void* ds_pos,
								   const double version=3.0) = 0;

	//--------------------------------------------------------------------
	// model_ptr : CDS_DISTRIBUTOR_INFO::pMODEL_PTR
	// scr_event : CDS_SCREEN_EVENT

	virtual int Send_Event(const void* model_ptr,
						   const int type,
						   const void* scr_event,
						   const double version=3.0) = 0;
};
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
class GObj__Flash_Interface
{
private:

public:
	virtual ~GObj__Flash_Interface(){};

	//--------------------------------------------------------------
	virtual int  Create_Object(const CString& dll_path,const CString& sdl_name) = 0;
	
	//---------------------------------------------------------
	virtual int  Interface_Parameter(const int& module_id,
									 const POINT& st,
									 const POINT& et,
									 const HWND& hwnd) = 0;
	virtual int  Interface_Show(const HWND& hwnd) = 0;
	virtual int  Interface_Hide() = 0;

	//---------------------------------------------------------
	virtual int  WM_Paint(const HWND& hwnd) = 0;
	virtual int  WM_Timer(const HWND& hwnd) = 0;
	
	virtual int  WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd) = 0;
	virtual int  WM_LButtonUp(const HWND& hwnd) = 0;

	virtual int  WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd) = 0;
	virtual int  WM_RButtonUp(const HWND& hwnd) = 0;

	//---------------------------------------------------------
	virtual int  WM_Notify(UINT message,WPARAM wparam,LPARAM lparam) = 0;
};
//-----------------------------------------------------------------------------------
