#pragma once

#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__VARIABLE_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__300mm_CTRL.h"
#include "C:\Module_Linker\EQP_Link_Res\Apps_Header\FA\Service\FA_Interface__DB_SVID_TRACE_CTRL.h"


// ...
class CI_BRIDGE__MSG_BIN_INFO
{
public:
	virtual ~CI_BRIDGE__MSG_BIN_INFO(){};
	
	//---------------------------------------------------------
	virtual void Load(const int size,char* bin) = 0;
	virtual int  Get_Total_Size() = 0;
	virtual int  Get_BINARY(const int db_index,int& bin_size,char **pp_bin) = 0;
	
	virtual void Get_HEXA_MSG(CString& hexa_msg) = 0;

	// ...
	virtual void* Get__CDS_BRIDGE__MSG_BIN_INFO() = 0;	
};

class CI_BRIDGE__FA_DRV_CTRL
{
public:
	virtual ~CI_BRIDGE__FA_DRV_CTRL(){};

	//---------------------------------------------------------
	virtual int Send()    = 0;
	virtual int Is_Recv() = 0;

	//
	virtual int Send_Without_DB_Check() = 0;
};

class CI_BRIDGE__MSG_RECV_CTRL
{
public:
	virtual ~CI_BRIDGE__MSG_RECV_CTRL(){};

	//----------------------------------------------------
	virtual int Get_Data(const CString& db_name,
						 int& type,
						 CString& first_data,
						 CStringArray& data_list) = 0;
	virtual int Get_Data(const CString& db_name,CString& data) = 0;

	//
	virtual int Set_Node_Root() = 0;
	virtual	int Set_Node_Ref(const CString& db_name) = 0;

	// ...
	virtual CI_BRIDGE__MSG_BIN_INFO* New__CI_Bridge_Msg_Bin_Info() = 0;
	virtual int Get__CDS_BRIDGE__MSG_BIN_INFO(void *p_bin_data) = 0;

	virtual int Get__BIN_DATA(int& bin_len,CString& bin_data) = 0;
};

class CI_BRIDGE__MSG_SEND_CTRL
{
public:
	virtual ~CI_BRIDGE__MSG_SEND_CTRL(){};

	//---------------------------------------------------------
	virtual int Get_INFO_From_DB_NAME(const CString& db_name,int& fmt_type,int& fmt_byte) = 0;
	virtual int Get_INFO_From_VAR_NAME(const CString& var_name,CString &db_name,int& fmt_type,int& fmt_byte) = 0;

	//---------------------------------------------------------
	virtual int Add_List(const CString& db_name,const int list_size) = 0;
	
	virtual int Add_Binary(const CString& db_name,const int bin) = 0;
  	virtual int Add_Binary_Array(const CString& db_name,const int bin) = 0;

	virtual int Add_Boolean(const CString& db_name,const BOOL bool_value) = 0;
	virtual int Add_Boolean_Array(const CString& db_name,const BOOL bool_value) = 0;

	virtual int Add_Ascii(const CString& db_name,const CString& ascii) = 0; 

  	virtual int Add_I1(const CString& db_name,const int i_value) = 0;
  	virtual int Add_I1_Array(const CString& db_name,const int i_value) = 0;
  	virtual int Add_I2(const CString& db_name,const int i_value) = 0;
  	virtual	int Add_I2_Array(const CString& db_name,const int i_value) = 0;
	virtual int Add_I4(const CString& db_name,const long l_value) = 0;
	virtual int Add_I4_Array(const CString& db_name,const long l_value) = 0;
	virtual int Add_I8(const CString& db_name,const long l_value) = 0;
	virtual int Add_I8_Array(const CString& db_name,const long l_value) = 0;
  
	virtual int Add_F4(const CString& db_name,const double d_value) = 0;
	virtual int Add_F4_Array(const CString& db_name,const double d_value) = 0;
	virtual int Add_F8(const CString& db_name,const double d_value) = 0;
	virtual int Add_F8_Array(const CString& db_name,const double d_value) = 0;

	virtual int Add_U1(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U1_Array(const CString& db_name,const unsigned int u_value)  = 0;
	virtual int Add_U2(const CString& db_name,const unsigned int u_value) = 0;
	virtual int Add_U2_Array(const CString& db_name,const unsigned int u_value)  = 0;
	virtual int Add_U4(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U4_Array(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U8(const CString& db_name,const unsigned long u_value) = 0;
	virtual int Add_U8_Array(const CString& db_name,const unsigned long u_value) = 0;

	virtual int Add_Virtual(const CString& db_name,const CDS_SVID_DATA& svid_data) = 0;
	virtual int Add_Virtual(const CString& db_name,const CDS_ECID_DATA& ecid_data) = 0;
	virtual int Add_Virtual(const CString& db_name,
						    const CString& unit_type,
							const int      unit_size,
							const CString& data) = 0;
	virtual int Add_Virtual(const CString& db_name,const CDS_ATTR_DATA& attr_data) = 0;

	//
	virtual int Set_Node_Root() = 0;
	virtual	int Set_Node_Ref(const CString& db_name) = 0;

	// ...
	virtual int Add_List_Ex(const CString& db_name,const int list_size,const int db_search=1) = 0;
	virtual int Add_U4_Ex(const CString& db_name,const unsigned long u_value,const int db_search=1) = 0;	
	virtual int Add_F4_Ex(const CString& db_name,const double d_value,const int db_search=1) = 0;
	virtual int Add_Ascii_Ex(const CString& db_name,const CString& ascii,const int db_search=1) = 0;	
};


class CI_BRIDGE__INFO_CTRL
{
public:
	virtual ~CI_BRIDGE__INFO_CTRL(){};

	//---------------------------------------------------------
	CI_BRIDGE__FA_DRV_CTRL      *pFA_DRV_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL    *pMSG_RECV_CTRL;
	CI_BRIDGE__MSG_SEND_CTRL    *pMSG_SEND_CTRL;

	//---------------------------------------------------------
	CI_FA_VARIABLE_CTRL			*pRES_VARIABLE_CTRL;
	CI_FA_DB_CTRL				*pRES_DB_CTRL;
	CI_FA_300mm_CTRL			*pRES_300mm_CTRL;
	CI_SEQ_INFO					*pRES_SEQ_INFO;
	CI_FA_DB__SVID_TRACE_CTRL   *pRES_SVID_TRACE_CTRL;

	//---------------------------------------------------------
	int iSx;
	int iFy;
	int iType;
	int iReply;
};
