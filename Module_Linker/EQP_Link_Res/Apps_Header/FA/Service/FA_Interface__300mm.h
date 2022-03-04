#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__300mm_Link.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__l5_Samsung__FA_Lib.h"


#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__FA_Link_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\EQP_Link_Res\\EQP_Lib\\EQP__FA_Link_R.lib")
#endif


//----------------------------------------------------
#define FA_LINK__SERVER_INIT(fnc_name,server_id)											\
extern "C" __declspec(dllexport) int FA_SERVER_INIT_##fnc_name(const int server_id)

#define FA_LINK__SERVER_SEND(fnc_name,server_id,p_bridge_info)								\
extern "C" __declspec(dllexport) int FA_SERVER_SEND_##fnc_name(const int server_id,CI_BRIDGE__INFO_CTRL* p_bridge_info)

#define FA_LINK__SERVER_RECV(fnc_name,server_id,p_bridge_info)								\
extern "C" __declspec(dllexport) int FA_SERVER_RECV_##fnc_name(const int server_id,CI_BRIDGE__INFO_CTRL* p_bridge_info)
//----------------------------------------------------

//----------------------------------------------------
#define FA_LINK_TYPE__ONLY_SEND								0      // Default
#define FA_LINK_TYPE__ONLY_SEND_EX							1
#define FA_LINK_TYPE__ALL_SEND    							2

#define FA_LINK__GET_TYPE(fnc_name)															\
extern "C" __declspec(dllexport) int FA_GET_TYPE_##fnc_name()

#define FA_LINK__INIT(fnc_name,service_name)												\
extern "C" __declspec(dllexport) int FA_INIT_##fnc_name(const CString& service_name)

#define FA_LINK__SEND_EX(fnc_name,p_bridge_info,event_id)									\
extern "C" __declspec(dllexport) int FA_SEND_EX_##fnc_name(CI_BRIDGE__INFO_CTRL* p_bridge_info,const int event_id)

#define FA_LINK__SEND(fnc_name,p_bridge_info)												\
extern "C" __declspec(dllexport) int FA_SEND_##fnc_name(CI_BRIDGE__INFO_CTRL* p_bridge_info)

#define FA_LINK__RECV(fnc_name,p_bridge_info)												\
extern "C" __declspec(dllexport) int FA_RECV_##fnc_name(CI_BRIDGE__INFO_CTRL* p_bridge_info)

#define FA_LINK__MSG_DELETE(fnc_name,user_msg_id,p_void)									\
extern "C" __declspec(dllexport) int FA_USER_MSG_DELETE_##fnc_name(const int user_msg_id,void* p_void)
//----------------------------------------------------

//----------------------------------------------------
#define SVID_GET(fnc_name,svid,svid_data,p_300mm_ctrl,p_db_ctrl)							\
extern "C" __declspec(dllexport) int SVID_GET_##fnc_name(const int svid,CDS_SVID_DATA& svid_data,CI_FA_300mm_CTRL* p_300mm_ctrl,CI_FA_VARIABLE_CTRL* p_variable_ctrl)
//----------------------------------------------------

//----------------------------------------------------
#define ECID_GET(fnc_name,ecid,ecid_value)													\
extern "C" __declspec(dllexport) int ECID_GET_##fnc_name(const int ecid,double& ecid_value)

#define ECID_SET(fnc_name,ecid,ecid_value)													\
extern "C" __declspec(dllexport) int ECID_SET_##fnc_name(const int ecid,const double ecid_value)
//----------------------------------------------------

//----------------------------------------------------
#define FA__START							\
	try										\
	{

#define FA__END								\
	}										\
	catch(int result)						\
	{										\
		return result;						\
	}										\
	return 0;
//----------------------------------------------------

//----------------------------------------------------
#define FA__OK				throw  1;
#define FA__ERROR			throw -1; 
//----------------------------------------------------



//----------------------------------------------------
extern "C"
{
CI_FA_300mm_LINK* New_FA_300mm_LINK();
void Del_FA_300mm_LINK(CI_FA_300mm_LINK* pt);

SCI__Memory_Check__FA_Interface__300mm* New__Memory_Check__FA_Interface__300mm();

SCI__L5_Samsung__FA_Lib* New__SCI__L5_Samsung__FA_Lib();
};
//----------------------------------------------------


//----------------------------------------------------
class CX_FA_300mm_LINK
{
private:
	CI_FA_300mm_LINK *m_pT;

public:
	CX_FA_300mm_LINK()
	{
		m_pT = New_FA_300mm_LINK();
	}
	~CX_FA_300mm_LINK()
	{
		if(m_pT != NULL)
		{
			// delete m_pT;
			Del_FA_300mm_LINK(m_pT);
		}
	}

	CI_FA_300mm_LINK* operator->() const
	{
		return m_pT;
	}
};

class SCX__Memory_Check__FA_Interface__300mm
{
private:
	SCI__Memory_Check__FA_Interface__300mm *m_pT;
	
public:
	SCX__Memory_Check__FA_Interface__300mm()
	{
		m_pT = New__Memory_Check__FA_Interface__300mm();
	}
	~SCX__Memory_Check__FA_Interface__300mm()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	SCI__Memory_Check__FA_Interface__300mm* operator->() const
	{
		return m_pT;
	}
};

class SCX__L5_Samsung__FA_Lib
{
private:
	SCI__L5_Samsung__FA_Lib *m_pT;
	
public:
	SCX__L5_Samsung__FA_Lib()
	{
		m_pT = New__SCI__L5_Samsung__FA_Lib();
	}
	~SCX__L5_Samsung__FA_Lib()
	{
		if(m_pT != NULL)
		{
			delete m_pT;
		}
	}
	
	SCI__L5_Samsung__FA_Lib* operator->() const
	{
		return m_pT;
	}
};
