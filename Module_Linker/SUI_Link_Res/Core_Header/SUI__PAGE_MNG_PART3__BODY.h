#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__PAGE_MNG_PART3__HEADER.h"


//----------------------------------------------------
extern "C"
{
CGUI_DISTRIBUTOR__PART_III__CREATE_CTRL*  New_DISTRIBUTOR__PART_III__CREATE_CTRL();
CGUI_DISTRIBUTOR__PART_III__EVENT_CTRL*   New_DISTRIBUTOR__PART_III__EVENT_CTRL();

GObj__Flash_Interface* New__FLASH_INTERFACE();
};
//----------------------------------------------------


//----------------------------------------------------
class XGUI_DISTRIBUTOR__PART_III__CREATE_CTRL
{
private:
	CGUI_DISTRIBUTOR__PART_III__CREATE_CTRL *m_pT;

public:
	XGUI_DISTRIBUTOR__PART_III__CREATE_CTRL()
	{
		m_pT = New_DISTRIBUTOR__PART_III__CREATE_CTRL();
	}
	~XGUI_DISTRIBUTOR__PART_III__CREATE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGUI_DISTRIBUTOR__PART_III__CREATE_CTRL* operator->() const
	{
		return m_pT;
	}
};

class XGUI_DISTRIBUTOR__PART_III__EVENT_CTRL
{
private:
	CGUI_DISTRIBUTOR__PART_III__EVENT_CTRL *m_pT;

public:
	XGUI_DISTRIBUTOR__PART_III__EVENT_CTRL()
	{
		m_pT = New_DISTRIBUTOR__PART_III__EVENT_CTRL();
	}
	~XGUI_DISTRIBUTOR__PART_III__EVENT_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGUI_DISTRIBUTOR__PART_III__EVENT_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------

//------------------------------------------------------
class XGObj__Flash_Interface
{
private:
	GObj__Flash_Interface *m_pT;

public:
	XGObj__Flash_Interface()
	{
		m_pT = New__FLASH_INTERFACE();
	}
	~XGObj__Flash_Interface()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	GObj__Flash_Interface* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
