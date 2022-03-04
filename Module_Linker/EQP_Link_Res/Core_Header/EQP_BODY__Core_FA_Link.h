#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Core_Header\EQP_HEADER__Core_FA_Link.h"


//-----------------------------------------------------------------------
extern "C"
{
CI_SEQ_DB__FA_CTRL*			 New_SEQ_DB__FA_CTRL();
CI_SEQ_DB__FA__CHANNEL_CTRL* New_SEQ_DB__FA__CHANNEL_CTRL();
CI_SEQ_DB__FA__ALARM_CTRL*   New_SEQ_DB__FA__ALARM_CTRL();
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CX_SEQ_DB__FA_CTRL
{
private:
	CI_SEQ_DB__FA_CTRL *m_pT;

public:
	CX_SEQ_DB__FA_CTRL()
	{
		m_pT = New_SEQ_DB__FA_CTRL();
	}
	~CX_SEQ_DB__FA_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_SEQ_DB__FA_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CX_SEQ_DB__FA__CHANNEL_CTRL
{
private:
	CI_SEQ_DB__FA__CHANNEL_CTRL *m_pT;

public:
	CX_SEQ_DB__FA__CHANNEL_CTRL()
	{
		m_pT = New_SEQ_DB__FA__CHANNEL_CTRL();
	}
	~CX_SEQ_DB__FA__CHANNEL_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_SEQ_DB__FA__CHANNEL_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
class CX_SEQ_DB__FA__ALARM_CTRL
{
private:
	CI_SEQ_DB__FA__ALARM_CTRL *m_pT;

public:
	CX_SEQ_DB__FA__ALARM_CTRL()
	{
		m_pT = New_SEQ_DB__FA__ALARM_CTRL();
	}
	~CX_SEQ_DB__FA__ALARM_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_SEQ_DB__FA__ALARM_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------

