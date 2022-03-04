#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__FA_Link.h"


//------------------------------------------------------
extern "C"
{
	CI_STD_LIB_FA_300mm__CTRL* New_STD_LIB_FA_300mm__CTRL();
	CI_STD_LIB_FA_300mm__LINK* New_STD_LIB_FA_300mm__LINK();

	CI_STD_LIB_FA_300mm__DB_CTRL*		New_STD_LIB_FA_300mm__DB_CTRL();
	CI_STD_LIB_FA_300mm__VARIABLE_CTRL*	New_STD_LIB_FA_300mm__VARIABLE_CTRL();
	CI_STD_LIB_FA_300mm__SEQ_INFO*		New_STD_LIB_FA_300mm__SEQ_INFO();
};
//------------------------------------------------------


//------------------------------------------------------
class CX_STD_LIB_FA_300mm__CTRL
{
private:
	CI_STD_LIB_FA_300mm__CTRL *m_pT;

public:
	CX_STD_LIB_FA_300mm__CTRL()
	{
		m_pT = New_STD_LIB_FA_300mm__CTRL();
	}
	~CX_STD_LIB_FA_300mm__CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_STD_LIB_FA_300mm__CTRL* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
//------------------------------------------------------
class CX_STD_LIB_FA_300mm__LINK
{
private:
	CI_STD_LIB_FA_300mm__LINK *m_pT;

public:
	CX_STD_LIB_FA_300mm__LINK()
	{
		m_pT = New_STD_LIB_FA_300mm__LINK();
	}
	~CX_STD_LIB_FA_300mm__LINK()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_STD_LIB_FA_300mm__LINK* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------


//------------------------------------------------------
class CX_STD_LIB_FA_300mm__DB_CTRL
{
private:
	CI_STD_LIB_FA_300mm__DB_CTRL *m_pT;

public:
	CX_STD_LIB_FA_300mm__DB_CTRL()
	{
		m_pT = New_STD_LIB_FA_300mm__DB_CTRL();
	}
	~CX_STD_LIB_FA_300mm__DB_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_STD_LIB_FA_300mm__DB_CTRL* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
//------------------------------------------------------
class CX_STD_LIB_FA_300mm__VARIABLE_CTRL
{
private:
	CI_STD_LIB_FA_300mm__VARIABLE_CTRL *m_pT;

public:
	CX_STD_LIB_FA_300mm__VARIABLE_CTRL()
	{
		m_pT = New_STD_LIB_FA_300mm__VARIABLE_CTRL();
	}
	~CX_STD_LIB_FA_300mm__VARIABLE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_STD_LIB_FA_300mm__VARIABLE_CTRL* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
//------------------------------------------------------
class CX_STD_LIB_FA_300mm__SEQ_INFO
{
private:
	CI_STD_LIB_FA_300mm__SEQ_INFO *m_pT;

public:
	CX_STD_LIB_FA_300mm__SEQ_INFO()
	{
		m_pT = New_STD_LIB_FA_300mm__SEQ_INFO();
	}
	~CX_STD_LIB_FA_300mm__SEQ_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_STD_LIB_FA_300mm__SEQ_INFO* operator->() const
	{
		return m_pT;
	}
};
//------------------------------------------------------
