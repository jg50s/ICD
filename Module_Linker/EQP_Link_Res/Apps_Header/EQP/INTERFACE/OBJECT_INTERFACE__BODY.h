#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\EQP\Interface\Object_Interface.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Core_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__Core_Link_R.lib")
#endif


// ...
extern "C"
{
	CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC* New_CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC();
	void Del_CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC(CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC* p_cls);
}

// ...
class CX__COMMON_CODE__ERROR_FEEDBACK__USER_FNC
{											
private:									
	CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC *m_pT;								
	
public:	
	CX__COMMON_CODE__ERROR_FEEDBACK__USER_FNC()									
	{										
		m_pT = New_CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC();
	}										
	~CX__COMMON_CODE__ERROR_FEEDBACK__USER_FNC()									
	{										
		if(m_pT != NULL)					
		{									
			Del_CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC(m_pT);					
		}									
	}										
	
	CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC* operator->() const				
	{		
		return m_pT;						
	}										
	void Set__PTR(CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC* p_ptr)				
	{										
		m_pT = p_ptr;						
	}										
	CII__COMMON_CODE__ERROR_FEEDBACK__USER_FNC* Get__PTR()						
	{										
		return m_pT;						
	}										
};
