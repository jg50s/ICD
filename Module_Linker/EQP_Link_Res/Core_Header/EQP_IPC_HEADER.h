#pragma once


//---------------------------------------------------------------------------------------
class CISeq__IPC_Server
{
public:
	virtual ~CISeq__IPC_Server(){};

	//----------------------------------------------------------------
	//
	virtual int  Callback__ADD_PRC_NAME(const CString& prc_name) = 0;
	virtual int  Callback__DELETE_PRC_NAME(const CString& prc_name) = 0;

	//
	virtual int  Is__ACTIVE_PAGE() = 0;
	virtual int  Callback__SHOW_PAGE() = 0;

	//
	virtual int  Callback__SET_DATA(const CString& prc_name,
									const CUIntArray&   l_ch_index,
									const CStringArray& l_ch_name,
									const CStringArray& l_ch_data) = 0;

	virtual int  Callback__UPDATE_ALL_DATA(CUIntArray& l_ch_index,
										   CStringArray& l_ch_name,
										   CStringArray& l_ch_data) = 0;
	virtual int  Callback__UPDATE_DATA(CUIntArray& l_ch_index,
									   CStringArray& l_ch_name,
									   CStringArray& l_ch_data) = 0;
};


//---------------------------------------------------------------------------------------
#define	 IPC_MSG_CMMD__LINK_TEST				1

//
#define  IPC_MSG_CMMD__PRC_NAME__REQ			11
#define  IPC_MSG_CMMD__PRC_NAME__RSP			12

#define  IPC_MSG_CMMD__CHANNEL_LIST__REQ		21
#define  IPC_MSG_CMMD__CHANNEL_LIST__RSP		22

//
#define	 IPC_MSG_CMMD__STOP						100
#define	 IPC_MSG_CMMD__SHOW						101
#define	 IPC_MSG_CMMD__HIDE						102

//
#define  IPC_MSG_CMMD__SET_DATA					111
#define  IPC_MSG_CMMD__GET_DATA					112


//
class CMSG__Base
{
public:
	int iSIZE;
	int iCMMD;
};

class CMSG__Show_Page : public CMSG__Base
{
public:
	int iFRAME_FLAG;
	POINT pST;
	POINT pSIZE;
};

//
class CMSG__Prc_Name__Req : public CMSG__Base
{
public:
	char sPRC_NAME[255];
};
class CMSG__Prc_Name__Rsp : public CMSG__Base
{
public:
	int iACK;
};

//
#define DEFINE_MAX__CHANNEL_BYTE					1000

class CMSG__Channel_List__Req : public CMSG__Base
{
public:
	int  iCH_SIZE;
	char sCHANNEL_LIST[DEFINE_MAX__CHANNEL_BYTE+1];
	int  iNEXT_FLAG;
};
class CMSG__Channel_List__Rsp : public CMSG__Base
{
public:
	int iACK;
};

//
class CMSG__Set_Data : public CMSG__Base
{
public:
	int  iINDEX;
	char sNAME[255];
	char sDATA[255];
};
class CMSG__Get_Data : public CMSG__Base
{
public:
	char sNAME[255];
	char sDATA[255];
};

 
class CDB__Event_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

public:
	HANDLE hPIPE;

	//
	CDB__Event_Info()
	{
		InitializeCriticalSection(&mCS_LOCK);

		hPIPE = INVALID_HANDLE_VALUE;
	}
	~CDB__Event_Info()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	//
	int  Call__LINK_TEST()
	{
		return Load__CMMD(IPC_MSG_CMMD__LINK_TEST);
	}

	int  Call__PRC_NAME_REQ(const CString& prc_name)
	{
		return Load_Cmmd__Prc_Name_Req(prc_name);
	}
	int  Call__CHANNEL_LIST_REQ(const CStringArray& l_ch_name)
	{
		return Load_Cmmd__Channel_List_Req(l_ch_name);
	}

	int  Call__STOP()
	{
		return Load__CMMD(IPC_MSG_CMMD__STOP);
	}
	int  Call__SHOW(const int frame_flag,const POINT& s_pt,const POINT& size_pt)
	{
		return Load__SHOW_CMMD(frame_flag,s_pt,size_pt);
	}
	int  Call__HIDE()
	{
		return Load__CMMD(IPC_MSG_CMMD__HIDE);
	}

	int  Call__SET_DATA(const int ch_index,const CString& ch_name,const CString& ch_data)
	{
		return Load_Cmmd__Set_DATA(ch_index,ch_name,ch_data);
	}

	//
	int  Load__CMMD(const int cmmd)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Base *p_msg = new CMSG__Base;
		int msg_size = sizeof(CMSG__Base);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = cmmd;

		//
	 	int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}
	int  Load__SHOW_CMMD(const int frame_flag,const POINT& s_pt,const POINT& size_pt)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Show_Page *p_msg = new CMSG__Show_Page;
		int msg_size = sizeof(CMSG__Show_Page);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = IPC_MSG_CMMD__SHOW;
		
		//
		p_msg->iFRAME_FLAG = frame_flag;
		p_msg->pST.x = s_pt.x;
		p_msg->pST.y = s_pt.y;
		p_msg->pSIZE.x = size_pt.x;
		p_msg->pSIZE.y = size_pt.y;

		//
	 	int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	int  Load_Cmmd__Prc_Name_Req(const CString& prc_name)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Prc_Name__Req *p_msg = new CMSG__Prc_Name__Req;
		int msg_size = sizeof(CMSG__Prc_Name__Req);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = IPC_MSG_CMMD__PRC_NAME__REQ;
		
		strcpy(p_msg->sPRC_NAME,prc_name);

		//
		int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}
	int  Load_Cmmd__Channel_List_Req(const CStringArray& l_ch_name)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Channel_List__Req *p_msg = new CMSG__Channel_List__Req;
		int msg_size = sizeof(CMSG__Channel_List__Req);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = IPC_MSG_CMMD__CHANNEL_LIST__REQ;

		//
		CString str_list;
		CString ch_name;

		int total_len;
		int new_len;

		int limit = l_ch_name.GetSize();
		int i;

		p_msg->iCH_SIZE = 0;
		total_len = 0;

		for(i=0;i<limit;i++)
		{
			ch_name  = l_ch_name.GetAt(i);
			ch_name += "|";

			new_len = ch_name.GetLength();

			if(total_len + new_len < DEFINE_MAX__CHANNEL_BYTE)
			{
				p_msg->iCH_SIZE++;

				total_len += new_len;
				str_list  += ch_name;
			}
			else
			{
				//
				strcpy(p_msg->sCHANNEL_LIST,str_list);
				p_msg->iNEXT_FLAG = 1;
				
				if(Fnc__Send_MSG((char*) p_msg,msg_size) < 0)
				{
					LeaveCriticalSection(&mCS_LOCK);
					return -1;
				}

				//
				p_msg = new CMSG__Channel_List__Req;
				p_msg->iSIZE = msg_size - 4;
				p_msg->iCMMD = IPC_MSG_CMMD__CHANNEL_LIST__REQ;

				p_msg->iCH_SIZE = 1;

				total_len = new_len;
				str_list  = ch_name;
			}
		}

		//
		strcpy(p_msg->sCHANNEL_LIST,str_list);
		p_msg->iNEXT_FLAG = -1;

		int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}
	
	int  Load_Cmmd__Set_DATA(const int ch_index,const CString& ch_name,const CString& ch_data)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Set_Data *p_msg = new CMSG__Set_Data;
		int msg_size = sizeof(CMSG__Set_Data);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = IPC_MSG_CMMD__SET_DATA;
	
		p_msg->iINDEX = ch_index;
		strcpy(p_msg->sNAME,ch_name);
		strcpy(p_msg->sDATA,ch_data);

		//
		int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	int  Load_Cmmd__Get_DATA(const CString& ch_name,CString& ch_data)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)		return -1;

		EnterCriticalSection(&mCS_LOCK);

		CMSG__Get_Data *p_msg = new CMSG__Get_Data;
		int msg_size = sizeof(CMSG__Get_Data);

		p_msg->iSIZE = msg_size - 4;
		p_msg->iCMMD = IPC_MSG_CMMD__GET_DATA;

		strcpy(p_msg->sNAME,ch_name);
		strcpy(p_msg->sDATA,"");

		//
		int flag = Fnc__Send_MSG((char*) p_msg,msg_size);

		LeaveCriticalSection(&mCS_LOCK);
		return flag;
	}

	//
	int  Fnc__Send_MSG(char* p_data,const int msg_size)
	{
		if(hPIPE == INVALID_HANDLE_VALUE)
		{
			delete [] p_data;
			return -1;
		}

		//--------------------------------------------------------
		BOOL  b_suc;
		DWORD dw_write;
	
		b_suc = WriteFile(hPIPE,p_data,msg_size,&dw_write,NULL);

		delete [] p_data;

		//
		if((b_suc == FALSE)||(dw_write == 0))
		{
			hPIPE = INVALID_HANDLE_VALUE;
			return -1;
		}
		//--------------------------------------------------------

		return 1;
	}
};

