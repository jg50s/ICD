#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"
#include "C:\Module_Linker\SUI_Link_Res\Core_Header\UI_Library__WINDOW_HEADER.h"


//----------------------------------------------------
class CGUI_DISTRIBUTOR__PART_I__CREATE_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_I__CREATE_CTRL(){};

	//--------------------------------------------------------------------
	virtual int System_Init(const CDS_SCREEN_INFO& scr_info,
						    const int moduel_id = 0) = 0;
	virtual int System_Optimize() = 0;
	
	//--------------------------------------------------------------------
	virtual int Check_Layered_Window(const int type,
									 const void* ds_model,
									 const int module_id) = 0;

	virtual void* Create_Model_Ex(CInterface_Lib__WINDOW* p_win_interface,
								  const CString& page_name,
							      int& win_layered_flag,
							      const HWND hwnd,
							      const void* ds_model,
							      const int type,
							      const int file_type = 1,
							      const int module_id = 0,
							      const double version=3.0) = 0;

	//--------------------------------------------------------------------
	virtual int Set_Real_Mode() = 0;

	virtual int Change__Seq_Info(const int module_id,
								 const CString& dir_root,
								 const CString& dir_config,
								 const CString& dir_datalog,
								 const CString& dir_process) = 0;

	//--------------------------------------------------------------------
	virtual int System_Optimize_Without_Log() = 0;

	//--------------------------------------------------------------------
	virtual int Debug_Init(const CDS_SCREEN_INFO& scr_info, const int moduel_id = 0) = 0;
};

class CGUI_DISTRIBUTOR__PART_I__EVENT_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_I__EVENT_CTRL(){};


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

	//--------------------------------------------------------------------
	virtual int  Get_PDLL__FEEDBACK_LBUTTON_INFO(const void* model_ptr,
												 const int type,
												 CString& feedback_command,
												 CStringArray& channel_list,
												 CStringArray& data_list) = 0;

	virtual int  Get_PDLL__FEEDBACK_TIMER_INFO(const void* model_ptr,
											   const int type,
											   CString& feedback_command,
											   CStringArray& channel_list,
											   CStringArray& data_list) = 0;

	// ...
	virtual int Link__Win_Interface(CInterface_Lib__WINDOW* p_win_interface) = 0;
};
//----------------------------------------------------
