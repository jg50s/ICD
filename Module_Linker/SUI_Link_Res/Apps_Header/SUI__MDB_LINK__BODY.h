#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__MDB_LINK__HEADER.h"


//----------------------------------------------------
extern "C"
{
UII__GOI_EXE_MDB_LINK_CTRL* New__GOI_EXE_MDB_LINK_CTRL();
};
//----------------------------------------------------


//----------------------------------------------------
class UIX__GOI_EXE_MDB_LINK_CTRL
{
private:
	UII__GOI_EXE_MDB_LINK_CTRL *m_pT;

public:
	UIX__GOI_EXE_MDB_LINK_CTRL()
	{
		m_pT = New__GOI_EXE_MDB_LINK_CTRL();
	}
	~UIX__GOI_EXE_MDB_LINK_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__GOI_EXE_MDB_LINK_CTRL* operator->() const
	{
		return m_pT;
	}
	UII__GOI_EXE_MDB_LINK_CTRL* Get_PTR()
	{
		return m_pT;
	}
};
//----------------------------------------------------
