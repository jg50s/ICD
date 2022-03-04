#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\UI__DISTRIBUTOR_INTERFACE_HEADER.h"


//----------------------------------------------------
extern "C"
{
CI_DISTRIBUTOR_FACTORY_CTRL*  New_SUI__DISTRIBUTOR_FACTORY_CTRL();
CI_DISTRIBUTOR_INFO_CTRL*	  New_SUI__DISTRIBUTOR_INFO_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_DISTRIBUTOR_FACTORY_CTRL
{
private:
	CI_DISTRIBUTOR_FACTORY_CTRL *m_pT;

public:
	CX_DISTRIBUTOR_FACTORY_CTRL()
	{
		m_pT = New_SUI__DISTRIBUTOR_FACTORY_CTRL();
	}
	~CX_DISTRIBUTOR_FACTORY_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_DISTRIBUTOR_FACTORY_CTRL* operator->() const
	{
		return m_pT;
	}
	CI_DISTRIBUTOR_FACTORY_CTRL* Get_PTR()
	{
		return m_pT;
	}
};

class CX_DISTRIBUTOR_INFO_CTRL
{
private:
	CI_DISTRIBUTOR_INFO_CTRL *m_pT;

public:
	CX_DISTRIBUTOR_INFO_CTRL()
	{
		m_pT = New_SUI__DISTRIBUTOR_INFO_CTRL();
	}
	~CX_DISTRIBUTOR_INFO_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_DISTRIBUTOR_INFO_CTRL* operator->() const
	{
		return m_pT;
	}
	CI_DISTRIBUTOR_INFO_CTRL* Get_PTR()
	{
		return m_pT;
	}
};
//----------------------------------------------------
