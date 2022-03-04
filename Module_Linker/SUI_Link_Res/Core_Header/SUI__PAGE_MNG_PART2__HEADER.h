#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"


//----------------------------------------------------
class CGUI_DISTRIBUTOR__PART_II__CREATE_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_II__CREATE_CTRL(){};

	virtual int System_Init(const CDS_SCREEN_INFO& scr_info,
						    const int moduel_id = 0) = 0;
	virtual int System_Optimize() = 0;

	//--------------------------------------------------------------------
	// 1 : STRING
	// 2 : BITMAP
	// 3 : PART
	// 4 : PDLL

	// ds_model : CDS_MODEL_FILE_INFO

	virtual void* Create_Model(const HWND hwnd,
							   const void* ds_model,
							   const int type,
							   const int file_type = 1,
							   const int module_id = 0,
							   const double version=3.0) = 0;

	//--------------------------------------------------------------------
	virtual int System_Optimize_Without_Log() = 0;
};

class CGUI_DISTRIBUTOR__PART_II__EVENT_CTRL
{
public:
	virtual ~CGUI_DISTRIBUTOR__PART_II__EVENT_CTRL(){};


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
						   int type,
						   const void* scr_event,
						   const double version=3.0) = 0;
};
//----------------------------------------------------
