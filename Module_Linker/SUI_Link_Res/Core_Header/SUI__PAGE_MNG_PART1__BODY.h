#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__PAGE_MNG_PART1__HEADER.h"


//----------------------------------------------------
extern "C"
{
CGUI_DISTRIBUTOR__PART_I__CREATE_CTRL*	New_DISTRIBUTOR__PART_I__CREATE_CTRL();
CGUI_DISTRIBUTOR__PART_I__EVENT_CTRL*	New_DISTRIBUTOR__PART_I__EVENT_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class XGUI_DISTRIBUTOR__PART_I__CREATE_CTRL
{
private:
	CGUI_DISTRIBUTOR__PART_I__CREATE_CTRL *m_pT;

public:
	XGUI_DISTRIBUTOR__PART_I__CREATE_CTRL()
	{
		m_pT = New_DISTRIBUTOR__PART_I__CREATE_CTRL();
	}
	~XGUI_DISTRIBUTOR__PART_I__CREATE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGUI_DISTRIBUTOR__PART_I__CREATE_CTRL* operator->() const
	{
		return m_pT;
	}
};

class XGUI_DISTRIBUTOR__PART_I__EVENT_CTRL
{
private:
	CGUI_DISTRIBUTOR__PART_I__EVENT_CTRL *m_pT;

public:
	XGUI_DISTRIBUTOR__PART_I__EVENT_CTRL()
	{
		m_pT = New_DISTRIBUTOR__PART_I__EVENT_CTRL();
	}
	~XGUI_DISTRIBUTOR__PART_I__EVENT_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CGUI_DISTRIBUTOR__PART_I__EVENT_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
