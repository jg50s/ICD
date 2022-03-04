#pragma once

#include "C:\Module_Linker\SUI_Link_Res\Core_Header\SUI__PAD_CTRL__HEADER.h"


//----------------------------------------------------------------------------
extern "C"
{
	CI_Pad_Analog_CTRL* New_Pad_Analog_CTRL();
};
extern "C"
{
	CI_Pad_String_CTRL* New_Pad_String_CTRL();
};
extern "C"
{
	CI_Pad_Digital_CTRL* New_Pad_Digital_CTRL();
};

extern "C"
{
	CI_Pad__AnalogDigital_CTRL* New_Pad__AnalogDigital_CTRL();
};
extern "C"
{
	CI_Pad__DigitalAnalog_CTRL* New_Pad__DigitalAnalog_CTRL();
};
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//-----------------------------------------------
class CX_Pad_Analog_CTRL
{
private:
	CI_Pad_Analog_CTRL *m_pT;

public:
	CX_Pad_Analog_CTRL()
	{
		m_pT = New_Pad_Analog_CTRL();
	}
	~CX_Pad_Analog_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_Pad_Analog_CTRL* operator->() const
	{
		return m_pT;
	}
};
class CX_Pad_String_CTRL
{
private:
	CI_Pad_String_CTRL *m_pT;

public:
	CX_Pad_String_CTRL()
	{
		m_pT = New_Pad_String_CTRL();
	}
	~CX_Pad_String_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_Pad_String_CTRL* operator->() const
	{
		return m_pT;
	}
};
class CX_Pad_Digital_CTRL
{
private:
	CI_Pad_Digital_CTRL *m_pT;

public:
	CX_Pad_Digital_CTRL()
	{
		m_pT = New_Pad_Digital_CTRL();
	}
	~CX_Pad_Digital_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_Pad_Digital_CTRL* operator->() const
	{
		return m_pT;
	}
};

class CX_Pad__AnalogDigital_CTRL
{
private:
	CI_Pad__AnalogDigital_CTRL *m_pT;

public:
	CX_Pad__AnalogDigital_CTRL()
	{
		m_pT = New_Pad__AnalogDigital_CTRL();
	}
	~CX_Pad__AnalogDigital_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_Pad__AnalogDigital_CTRL* operator->() const
	{
		return m_pT;
	}
};
class CX_Pad__DigitalAnalog_CTRL
{
private:
	CI_Pad__DigitalAnalog_CTRL *m_pT;

public:
	CX_Pad__DigitalAnalog_CTRL()
	{
		m_pT = New_Pad__DigitalAnalog_CTRL();
	}
	~CX_Pad__DigitalAnalog_CTRL()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}

	CI_Pad__DigitalAnalog_CTRL* operator->() const
	{
		return m_pT;
	}
};
//----------------------------------------------------------------------------
