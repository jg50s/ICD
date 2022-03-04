#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\GUI_DS.h"
#include "C:\Module_Linker\SUI_Link_Res\Core_Header\UI__DIALOG_UTILITY_DS.h"


//----------------------------------------------------
class CI_DIALOG_UTILITY_CTRL
{
public:
	virtual ~CI_DIALOG_UTILITY_CTRL(){};	

	virtual int PopupFileOpen(void* open_info, const void* screen_info, double version=3.0) = 0;
	virtual int PopupFileSave(void* save_info, const void* screen_info, double version=3.0) = 0;
	
	//////////////////////////////////////////////////////////////////////////
	// DYNAMIC
	virtual int PopupDynamic(/*DynamicCallBack CBFunc*/) = 0;
	virtual int SetDynamic(CDS_MODEL_DYNAMIC& dynamic) = 0;
	virtual int GetDynamic(CDS_MODEL_DYNAMIC& dynamic) = 0;

	//////////////////////////////////////////////////////////////////////////
	// RENAME
	virtual int PopupRename() = 0;
	virtual int SetRename(CDS_PROPERTY__PART& prop, CDS_MODEL_RENAME& info) = 0;
	virtual int GetRename(CDS_MODEL_RENAME& info) = 0;
};
//----------------------------------------------------


//----------------------------------------------------
extern "C"
{
CI_DIALOG_UTILITY_CTRL*	 New_DIALOG_UTILITY_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_DIALOG_UTILITY_CTRL
{
private:
	CI_DIALOG_UTILITY_CTRL *m_pT;

public:
	CX_DIALOG_UTILITY_CTRL()
	{
		m_pT = New_DIALOG_UTILITY_CTRL();
	}
	~CX_DIALOG_UTILITY_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_DIALOG_UTILITY_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
