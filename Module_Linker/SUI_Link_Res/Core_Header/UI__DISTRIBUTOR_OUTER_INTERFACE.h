#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\CInterface_GUI_DISTRIBUTOR_OUTER_INTERFACE.h"


//----------------------------------------------------
extern "C"
{
CI_DISTRIBUTOR_OUTER_INFO_CTRL*	New_DISTRIBUTOR_OUTER_INFO_CTRL();
CI_DISTRIBUTOR_OUTER_CTRL*		New_DISTRIBUTOR_OUTER_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_DISTRIBUTOR_OUTER_INFO_CTRL
{
private:
	CI_DISTRIBUTOR_OUTER_INFO_CTRL *m_pT;

public:
	CX_DISTRIBUTOR_OUTER_INFO_CTRL()
	{
		m_pT = New_DISTRIBUTOR_OUTER_INFO_CTRL();
	}
	~CX_DISTRIBUTOR_OUTER_INFO_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_DISTRIBUTOR_OUTER_INFO_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_DISTRIBUTOR_OUTER_CTRL
{
private:
	CI_DISTRIBUTOR_OUTER_CTRL *m_pT;

public:
	CX_DISTRIBUTOR_OUTER_CTRL()
	{
		m_pT = New_DISTRIBUTOR_OUTER_CTRL();
	}
	~CX_DISTRIBUTOR_OUTER_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_DISTRIBUTOR_OUTER_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
