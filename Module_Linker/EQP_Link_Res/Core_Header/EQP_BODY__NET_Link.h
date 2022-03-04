#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__NET_Link.h"


//------------------------------------------------------
extern "C"
{
CI_SEQ_NET__CTRL* New_SEQ_NET__CTRL();
void Del_SEQ_NET__CTRL(CI_SEQ_NET__CTRL* p_cls);

CI_SEQ_NET__MODULE_CTRL* New_SEQ_NET__MODULE_CTRL();
void Del_SEQ_NET__MODULE_CTRL(CI_SEQ_NET__MODULE_CTRL* p_cls);

CI_SEQ_NET_CTRL__Memory_Check* New_SEQ_NET_CTRL__Memory_Check();
void Del_SEQ_NET_CTRL__Memory_Check(CI_SEQ_NET_CTRL__Memory_Check* p_cls);
};
//------------------------------------------------------


//------------------------------------------------------
class CX_SEQ_NET_CTRL__Memory_Check
{
private:
	CI_SEQ_NET_CTRL__Memory_Check *m_pT;
	
public:
	CX_SEQ_NET_CTRL__Memory_Check()
	{
		m_pT = New_SEQ_NET_CTRL__Memory_Check();
	}
	~CX_SEQ_NET_CTRL__Memory_Check()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_NET_CTRL__Memory_Check(m_pT);
		}
	}
	
	CI_SEQ_NET_CTRL__Memory_Check* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_NET__CTRL
{
private:
	CI_SEQ_NET__CTRL *m_pT;

public:
	CX_SEQ_NET__CTRL()
	{
		m_pT = New_SEQ_NET__CTRL();
	}
	~CX_SEQ_NET__CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_NET__CTRL(m_pT);
		}
	}

	CI_SEQ_NET__CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_SEQ_NET__MODULE_CTRL
{
private:
	CI_SEQ_NET__MODULE_CTRL *m_pT;

public:
	CX_SEQ_NET__MODULE_CTRL()
	{
		m_pT = New_SEQ_NET__MODULE_CTRL();
	}
	~CX_SEQ_NET__MODULE_CTRL()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_SEQ_NET__MODULE_CTRL(m_pT);
		}
	}

	CI_SEQ_NET__MODULE_CTRL* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
