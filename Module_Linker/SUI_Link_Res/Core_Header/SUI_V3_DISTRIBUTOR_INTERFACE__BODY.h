#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI_V3_DISTRIBUTOR_INTERFACE__HEADER.h"


//----------------------------------------------------
extern "C"
{
CI_V3_DISTRIBUTOR_FACTORY_CTRL*	New_DISTRIBUTOR_FACTORY_CTRL();
CI_V3_DISTRIBUTOR_INFO_CTRL*	New_DISTRIBUTOR_INFO_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_V3_DISTRIBUTOR_FACTORY_CTRL
{
private:
	CI_V3_DISTRIBUTOR_FACTORY_CTRL *m_pT;

public:
	CX_V3_DISTRIBUTOR_FACTORY_CTRL()
	{
		m_pT = New_DISTRIBUTOR_FACTORY_CTRL();
	}
	~CX_V3_DISTRIBUTOR_FACTORY_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_V3_DISTRIBUTOR_FACTORY_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_V3_DISTRIBUTOR_INFO_CTRL
{
private:
	CI_V3_DISTRIBUTOR_INFO_CTRL *m_pT;

public:
	CX_V3_DISTRIBUTOR_INFO_CTRL()
	{
		m_pT = New_DISTRIBUTOR_INFO_CTRL();
	}
	~CX_V3_DISTRIBUTOR_INFO_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_V3_DISTRIBUTOR_INFO_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
