#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__SERVICE_LINK_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__SERVICE_LINK_R.lib")
#endif


//----------------------------------------------------
class CGui__Service_Ctrl
{
public:
	virtual ~CGui__Service_Ctrl(){};

	//--------------------------------------------------------------------
	virtual int Start_Service(const CString& service_name) = 0;

};
//----------------------------------------------------
