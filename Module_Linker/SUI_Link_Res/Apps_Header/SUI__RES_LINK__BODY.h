#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Apps_Header\SUI__RES_LINK__HEADER.h"


//----------------------------------------------------
extern "C"
{
UII__FILE_LOG_CTRL*  New__FILE_LOG_CTRL();

UII__RCP_INTERLOCK_CTRL*     New__RCP_INTERLOCK_CTRL();
UII__RCP_INTERLOCK_FEEDBACK* New__RCP_INTERLOCK_FEEDBACK(); 

UII__ALARM_DB_INFO*  New__ALARM_DB_INFO(); 
UII__FILE_CTRL*      New__GUI_FILE_CTRL(); 
UII__PAGE_INFO*      New__PAGE_INFO();  

UII__FILE_ANALYSIS_CTRL* New__FILE_ANALYSIS_CTRL();
UII__SYSTEM_INFO*        New__SYSTEM_INFO();
};
//----------------------------------------------------


//----------------------------------------------------
// ...
class UIX__FILE_LOG_CTRL
{
private:
	UII__FILE_LOG_CTRL *m_pT;
	
public:
	UIX__FILE_LOG_CTRL()
	{
		m_pT = New__FILE_LOG_CTRL();
	}
	~UIX__FILE_LOG_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	UII__FILE_LOG_CTRL* operator->() const
	{
		return m_pT;
	}
	UII__FILE_LOG_CTRL* Get_PTR()
	{
		return m_pT;
	}
};

// ...
class UIX__RCP_INTERLOCK_CTRL
{
private:
	UII__RCP_INTERLOCK_CTRL *m_pT;

public:
	UIX__RCP_INTERLOCK_CTRL()
	{
		m_pT = New__RCP_INTERLOCK_CTRL();
	}
	~UIX__RCP_INTERLOCK_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__RCP_INTERLOCK_CTRL* operator->() const
	{
		return m_pT;
	}
	UII__RCP_INTERLOCK_CTRL* Get_PTR()
	{
		return m_pT;
	}
};
class UIX__RCP_INTERLOCK_FEEDBACK
{
private:
	UII__RCP_INTERLOCK_FEEDBACK *m_pT;

public:
	UIX__RCP_INTERLOCK_FEEDBACK()
	{
		m_pT = New__RCP_INTERLOCK_FEEDBACK();
	}
	~UIX__RCP_INTERLOCK_FEEDBACK()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__RCP_INTERLOCK_FEEDBACK* operator->() const
	{
		return m_pT;
	}
	UII__RCP_INTERLOCK_FEEDBACK* Get_PTR()
	{
		return m_pT;
	}
};

// ...
class UIX__ALARM_DB_INFO
{
private:
	UII__ALARM_DB_INFO *m_pT;

public:
	UIX__ALARM_DB_INFO()
	{
		m_pT = New__ALARM_DB_INFO();
	}
	~UIX__ALARM_DB_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__ALARM_DB_INFO* operator->() const
	{
		return m_pT;
	}
};

// ...
class UIX__FILE_CTRL
{
private:
	UII__FILE_CTRL *m_pT;

public:
	UIX__FILE_CTRL()
	{
		m_pT = New__GUI_FILE_CTRL();
	}
	~UIX__FILE_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__FILE_CTRL* operator->() const
	{
		return m_pT;
	}
};

// ...
class UIX__PAGE_INFO
{
private:
	UII__PAGE_INFO *m_pT;

public:
	UIX__PAGE_INFO()
	{
		m_pT = New__PAGE_INFO();
	}
	~UIX__PAGE_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__PAGE_INFO* operator->() const
	{
		return m_pT;
	}
};

// ...
class UIX__FILE_ANALYSIS_CTRL
{
private:
	UII__FILE_ANALYSIS_CTRL *m_pT;

public:
	UIX__FILE_ANALYSIS_CTRL()
	{
		m_pT = New__FILE_ANALYSIS_CTRL();
	}
	~UIX__FILE_ANALYSIS_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__FILE_ANALYSIS_CTRL* operator->() const
	{
		return m_pT;
	}
};

// ...
class UIX__SYSTEM_INFO
{
private:
	UII__SYSTEM_INFO *m_pT;

public:
	UIX__SYSTEM_INFO()
	{
		m_pT = New__SYSTEM_INFO();
	}
	~UIX__SYSTEM_INFO()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	UII__SYSTEM_INFO* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------
