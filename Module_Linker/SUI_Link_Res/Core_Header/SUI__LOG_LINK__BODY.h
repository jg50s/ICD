#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__LOG_LINK__HEADER.h"


//-----------------------------------------------------------------------
extern "C"
{
  CCI__UTILITY_LOG_CTRL__LOG_CREATE* New__UTILITY_LOG_CTRL__LOG_CREATE();
  void Del__UTILITY_LOG_CTRL__LOG_CREATE(CCI__UTILITY_LOG_CTRL__LOG_CREATE* p_cls);

  CCI__UTILITY_LOG_CTRL__LOG_LINK* New__UTILITY_LOG_CTRL__LOG_LINK();
  void Del__UTILITY_LOG_CTRL__LOG_LINK(CCI__UTILITY_LOG_CTRL__LOG_LINK* p_cls);

  CCI__UI_PROPERTY_CTRL* New__UI_PROPERTY_CTRL();
  void Del__UI_PROPERTY_CTRL(CCI__UI_PROPERTY_CTRL* p_cls);
};
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
class CCX__UTILITY_LOG_CTRL__LOG_CREATE
{
private:
	CCI__UTILITY_LOG_CTRL__LOG_CREATE *m_pT;

public:
	CCX__UTILITY_LOG_CTRL__LOG_CREATE()
	{
		m_pT = New__UTILITY_LOG_CTRL__LOG_CREATE();
	}
	~CCX__UTILITY_LOG_CTRL__LOG_CREATE()
	{
		Del__UTILITY_LOG_CTRL__LOG_CREATE(m_pT);
	}

	CCI__UTILITY_LOG_CTRL__LOG_CREATE* operator->() const
	{
		return m_pT;
	}
};

class CCX__UTILITY_LOG_CTRL__LOG_LINK
{
private:
	CCI__UTILITY_LOG_CTRL__LOG_LINK *m_pT;

public:
	CCX__UTILITY_LOG_CTRL__LOG_LINK()
	{
		m_pT = New__UTILITY_LOG_CTRL__LOG_LINK();
	}
	~CCX__UTILITY_LOG_CTRL__LOG_LINK()
	{
		Del__UTILITY_LOG_CTRL__LOG_LINK(m_pT);
	}

	CCI__UTILITY_LOG_CTRL__LOG_LINK* operator->() const
	{
		return m_pT;
	}
};

class CCX__UI_PROPERTY_CTRL
{
private:
	CCI__UI_PROPERTY_CTRL *m_pT;
	
public:
	CCX__UI_PROPERTY_CTRL()
	{
		m_pT = New__UI_PROPERTY_CTRL();
	}
	~CCX__UI_PROPERTY_CTRL()
	{
		Del__UI_PROPERTY_CTRL(m_pT);
	}
	
	CCI__UI_PROPERTY_CTRL* operator->() const
	{
		return m_pT;
	}
};
//-----------------------------------------------------------------------
