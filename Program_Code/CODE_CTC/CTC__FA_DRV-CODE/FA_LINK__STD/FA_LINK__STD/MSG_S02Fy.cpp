#include "StdAFx.h"

#include "MSG_S02Fy.h"
CMsg_S02Fy mMSG_S02Fy;

#include "CRes__DATAID_CEID.h"
extern CRes__DATAID_CEID mRes__DATAID_CEID;


// ...
#define MSG_TYPE__LIST					"L"

#define MSG_TYPE__BINARY                "B"
#define MSG_TYPE__BOOLEAN               "BOOL"
#define MSG_TYPE__ASCII					"A"
#define MSG_TYPE__U                     "U"
#define MSG_TYPE__I                     "I"
#define MSG_TYPE__F                     "F"


//----------------------------------------------------------------------------
CMsg_S02Fy::CMsg_S02Fy()
{
	iSx = 2;
}

void CMsg_S02Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;
	
	switch(p_bridge_ctrl->iFy)
	{
		case 17:	Send__F17(p_bridge_ctrl);		return;
		case 25:	Send__F25(p_bridge_ctrl);		return;
	}
}

void CMsg_S02Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 13:	Recv__F13(p_bridge_ctrl);		return;
		case 15:	Recv__F15(p_bridge_ctrl);		return;
		case 17:	Recv__F17(p_bridge_ctrl);		return;
		case 23:	Recv__F23(p_bridge_ctrl);		return;
		case 25:	Recv__F25(p_bridge_ctrl);		return;
		
		case 29:	Recv__F29(p_bridge_ctrl);		return;		
		case 31:	Recv__F31(p_bridge_ctrl);		return;
		case 33:	Recv__F33(p_bridge_ctrl);		return;
		case 35:	Recv__F35(p_bridge_ctrl);		return;
		case 37:	Recv__F37(p_bridge_ctrl);		return;
		case 39:	Recv__F39(p_bridge_ctrl);		return;
		case 41:	Recv__F41(p_bridge_ctrl);		return;
		case 43:	Recv__F43(p_bridge_ctrl);		return;
		case 45:	Recv__F45(p_bridge_ctrl);		return;
		case 47:	Recv__F47(p_bridge_ctrl);		return;
	}
}

//----------------------------------------------------------------------------
//  Date and Time Request
void CMsg_S02Fy::Send__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	//----------------------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//-----------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString time;
	
	// TIME
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,time);

	p_bridge_ctrl->pRES_SEQ_INFO->Set__Date_And_Time(time);
	//----------------------------------------------------------

	FA__OK;
}

//  Loopback Diagnostic
void CMsg_S02Fy::Send__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_VARIABLE_CTRL *p_variable_ctrl
		= p_bridge_ctrl->pRES_VARIABLE_CTRL;


	//----------------------------------------------------------
	CString	db_name;

	CString main_name;
	CString sub_name;
	CStringArray var_list;


	main_name = "##S2F25";
	sub_name  = "ABS";

	p_variable_ctrl->Get_Variable(main_name,sub_name,var_list);

	//-----------------------------
	int i;
	int limit = var_list.GetSize();

	db_name = "-1";
	
	for(i=0;i<limit;i++)
	{
		p_send_ctrl->Add_Binary_Array(db_name,atoi(var_list[i]));
	}
	//-----------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//----------------------------------------------------------

	//----------------------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//----------------------------------------------------------

	FA__OK;
}


//----------------------------------------------------------------------------
// 	Equipment Constant Request
void CMsg_S02Fy::Recv__F13(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString		 db_recv;
	CString		 db_send;
	CString		 first_data;
	int			 data_type;
	CStringArray data_list;

	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	
	int list_limit;

	db_recv = "-1";
	p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);

	list_limit = atoi(first_data);

	CI_FA_DB__ECID_CTRL *p_ecid_ctrl;
	int ecid;
	CDS_ECID_DATA ecid_data;

	if(list_limit > 0)
	{
		int i;

		db_send = "-1";
		p_send_ctrl->Add_List(db_send,list_limit);

		p_ecid_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

		for(i=0;i<list_limit;i++)
		{
			db_recv.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);

			ecid = atoi(first_data);
			p_ecid_ctrl->Get_DATA_WITH_ECID(ecid,ecid_data);

			db_send = db_recv;
			p_send_ctrl->Add_Virtual(db_send,ecid_data);
		}
	}
	else
	{
		p_ecid_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

		int db_index = 0;

		while(p_ecid_ctrl->Get_DATA_WITH_INDEX(db_index,ecid_data) > 0)
		{
			db_index++;

			db_send.Format("-1-%1d",db_index);
			p_send_ctrl->Add_Virtual(db_send,ecid_data);
		}

		db_send = "-1";
		p_send_ctrl->Add_List(db_send,db_index);
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	// p_bridge_ctrl->pFA_DRV_CTRL->Send_Without_DB_Check();
	//-----------------------------

	FA__OK
}

// 	New Equipment Constant
void CMsg_S02Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString		 db_recv;
	CString		 first_data;
	int			 data_type;
	CStringArray data_list;

	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	
	int list_limit;

	db_recv = "-1";
	p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);

	list_limit = atoi(first_data);

	CI_FA_DB__ECID_CTRL *p_ecid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

	int	   ecid;
	double ecid_value;

	int eac_bin = 0;

	if(list_limit > 0)
	{
		int i;

		p_ecid_ctrl->Init__SET_ECID_LIST();

		for(i=0;i<list_limit;i++)
		{
			// ECID
			db_recv.Format("-1-%1d-1",i+1);
			p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);
			ecid = atoi(first_data);

			// ECV
			db_recv.Format("-1-%1d-2",i+1);
			p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);
			ecid_value = atof(first_data);

			if(p_ecid_ctrl->Set_DATA(ecid,ecid_value) < 0)
			{
				eac_bin = 1;
			}
		}
	}

	if(eac_bin == 0)
	{
		p_ecid_ctrl->Save_FILE();
	}
	//-----------------------------

	//-----------------------------
	CString db_send;

	db_send = "-1";
	p_send_ctrl->Add_Binary(db_send,eac_bin);
	//-----------------------------
 
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------
	//----------------------------------------------------------

	FA__OK
}

//  Date and Time Request
void CMsg_S02Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	//-----------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__ECID_CTRL *p_ecid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

	//-----------------------------
	CString db_name;
	CString time;

	//-----------------------------
	// TIME
	if(p_ecid_ctrl->Get_ECID__TIME_FORMAT() == 0)
	{
		p_bridge_ctrl->pRES_SEQ_INFO->Get__Date_And_Time__With_2_Digit_Year(time);
	}
	else
	{
		p_bridge_ctrl->pRES_SEQ_INFO->Get__Date_And_Time(time);
	}

	db_name = "-1";
	p_send_ctrl->Add_Ascii(db_name,time);
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------
	//----------------------------------------------------------

	FA__OK
}

// 	Trace Initialize Send
void CMsg_S02Fy::Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString		 db_name;
	CString		 first_data;
	int			 data_type;
	CStringArray data_list;

	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	//-----------------------------
	CString s_hh, s_mm, s_ss;
	int list_limit;
	int i;
	int svid;
	int flag = 1;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	CI_FA_DB__SVID_TRACE_CTRL *p_svid_trace_ctrl
		= p_bridge_ctrl->pRES_SVID_TRACE_CTRL;

	CDS_SVID_TRACE_INFO trace_info;
	trace_info.Clear();
	//-----------------------------

	// TRID
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);
	
	trace_info.iTRID = atoi(first_data);

	// DSPER
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);
	
	s_hh = first_data;
	s_mm = first_data;
	s_ss = first_data;

	int len = s_hh.GetLength(); 
	if(len >= 2)
	{
		s_hh.Delete(2,len-2);
	}

	len = s_mm.GetLength(); 
	if(len >= 4)
	{
		s_mm.Delete(4,len-4);
		s_mm.Delete(0,2);
	}

	len = s_ss.GetLength(); 
	if(len >= 6)
	{
		s_ss.Delete(6,len-6);
		s_ss.Delete(0,4);
	}

	trace_info.iDSPER = (3600 * atoi(s_hh)) + (60 * atoi(s_mm)) + atoi(s_ss);
	if(trace_info.iDSPER < 1)	
	{
		flag = -3;
	}

	// TOTSMP
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);

	trace_info.iTOTSMP = atoi(first_data);

	// REPGSZ
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);

	trace_info.iREPGSZ = atoi(first_data);

	// LIST_LIMIT
	db_name = "-1-5";
	p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);
	
	list_limit = atoi(first_data);

	for(i=0;i<list_limit;i++)
	{
		// SVID
		db_name.Format("-1-5-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,data_type,first_data,data_list);
		svid = atoi(first_data);

		/*
		if(p_svid_ctrl->Is_SVID(svid) < 0)
		{
			flag = -2;
			break;
		}
		*/
		
		trace_info.iSVID_LIST.Add(svid);
	}

	if(flag > 0)
	{
		flag = p_svid_trace_ctrl->Add_TRACE(trace_info);
	}
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	int tiaack_bin;
	
	//-----------------------------
	if(flag < 0)
	{
		tiaack_bin = -flag;
	}
	else
	{
		tiaack_bin = 0;

		int trid = trace_info.iTRID;

		if(list_limit > 0)
		{
			p_svid_trace_ctrl->Start_TRACE(trid);
		}
		else
		{
			p_svid_trace_ctrl->Stop_TRACE(trid);
		}
	}

	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,tiaack_bin);
	//-----------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK;
}

//  Loopback Diagnostic
void CMsg_S02Fy::Recv__F25(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString		 db_name;
	CString		 first_data;
	int			 data_type;
	CStringArray data_list;

	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG

	// 1.<B[10]   $ABS

	//-----------------------------
	db_name = "-1";
	p_bridge_ctrl->pMSG_RECV_CTRL->Get_Data(db_name,data_type,first_data,data_list);
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	// 1.<B[10]   $ABS

	//-----------------------------
	int bin;
	int i;
	int limit = data_list.GetSize();

	db_name = "-1";

	for(i=0;i<limit;i++)
	{
		sscanf(data_list[i],"%x",&bin);

		p_bridge_ctrl->pMSG_SEND_CTRL->Add_Binary_Array(db_name,bin);
	}
	//-----------------------------
		
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

// 	Equipment Constant Namelist Request
void CMsg_S02Fy::Recv__F29(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString		 db_recv;
	CString		 db_send;
	CString		 first_data;
	int			 data_type;
	CStringArray data_list;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	
	CI_FA_DB__ECID_CTRL *p_ecid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

	//----------------------------------------------------------
	//-----------------------------
	int list_limit;
	int i;
	int ecid;
	CDS_ECID_INFO ecid_info;

	//-----------------------------
	db_recv = "-1";
	p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);
	list_limit = atoi(first_data);

	if(list_limit > 0)
	{
		db_send = "-1";
		p_send_ctrl->Add_List_Ex(db_send,list_limit, -1);

		for(i=0;i<list_limit;i++)
		{
			db_recv.Format("-1-%1d",i+1);
			p_recv_ctrl->Get_Data(db_recv,data_type,first_data,data_list);
			ecid = atoi(first_data);

			p_ecid_ctrl->Get_INFO_WITH_ECID(ecid,ecid_info);

			// ...
			{
				// List
				db_send.Format("-1-%1d",i+1);
				p_send_ctrl->Add_List_Ex(db_send,6, -1);

				// 1. ID
				db_send.Format("-1-%1d-1",i+1);
				p_send_ctrl->Add_U4_Ex(db_send,ecid_info.iECID, -1);

				// 2. Name
				db_send.Format("-1-%1d-2",i+1);
				p_send_ctrl->Add_Ascii_Ex(db_send,ecid_info.sName, -1);

				// 3. Min
				db_send.Format("-1-%1d-3",i+1);
				p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dMin, -1);

				// 4. Max
				db_send.Format("-1-%1d-4",i+1);
				p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dMax, -1);

				// 5. Default
				db_send.Format("-1-%1d-5",i+1);
				p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dDefault, -1);

				// 6. Unit
				db_send.Format("-1-%1d-6",i+1);
				p_send_ctrl->Add_Ascii_Ex(db_send,ecid_info.sUnit, -1);
			}
		}
	}
	else
	{
		// ...
		int     db_index = 0;
		CString db_data;
		int i;

		while(p_ecid_ctrl->Get_INFO_WITH_INDEX(db_index,ecid_info) > 0)
		{
			db_index++;

			for(i=0; i<=6; i++)
			{
				if(i == 0)				// List
				{
					db_send.Format("-1-%1d", db_index);
					p_send_ctrl->Add_List_Ex(db_send,6, -1);					
				}
				else if(i == 1)			// 1. ID
				{
					db_send.Format("-1-%1d-1", db_index);
					p_send_ctrl->Add_U4_Ex(db_send,ecid_info.iECID, -1);					
				}
				else if(i == 2)			// 2. Name
				{
					db_send.Format("-1-%1d-2", db_index);
					p_send_ctrl->Add_Ascii_Ex(db_send,ecid_info.sName, -1);
				}
				else if(i == 3)			// 3. Min
				{
					db_send.Format("-1-%1d-3", db_index);
					p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dMin, -1);
				}
				else if(i == 4)			// 4. Max
				{
					db_send.Format("-1-%1d-4", db_index);
					p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dMax, -1);					
				}
				else if(i == 5)			// 5. Default
				{
					db_send.Format("-1-%1d-5", db_index);
					p_send_ctrl->Add_F4_Ex(db_send,ecid_info.dDefault, -1);					
				}
				else if(i == 6)			// 6. Unit
				{
					db_send.Format("-1-%1d-6", db_index);
					p_send_ctrl->Add_Ascii_Ex(db_send,ecid_info.sUnit, -1);
				}
			}
		}

		// ...
		{
			db_send = "-1";
			p_send_ctrl->Add_List_Ex(db_send,db_index, -1);
		}
	}
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	// p_bridge_ctrl->pFA_DRV_CTRL->Send_Without_DB_Check();
	//-----------------------------

	FA__OK
}

//	Date and Time Set Request 
void CMsg_S02Fy::Recv__F31(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__ECID_CTRL *p_ecid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_ECID_CTRL();

	CString db_name;
	CString time;
	int tiack = 0;

	
	//-----------------------------
	// TIME

	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,time);
	//-----------------------------

	if(p_ecid_ctrl->Get_ECID__TIME_FORMAT() > 0)
	{
		if(time.GetLength() != 16)		tiack = 1;
	}
	else
	{
		if(time.GetLength() != 12)		tiack = 1;
	}

	if(tiack == 0)
	{
		p_bridge_ctrl->pRES_SEQ_INFO->Set__Date_And_Time(time);
	}
	//----------------------------------------------------------

	//----------------------------------------------------------
	//-----------------------------
	// TIACK

	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,tiack);
	//-----------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

//  Define Report
void CMsg_S02Fy::Recv__F33(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString	db_name;
	CString var_data;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;


	//----------------------------------------------------------
	// RECV-MSG
	
	int i;
	int list_limit;
	int k;
	int item_limit;
	int rptid;
	int svid;

	int err_flag = 0;

	//-----------------------------
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);
	list_limit = atoi(var_data);

	p_rptid_svid_ctrl->Init_RPTID();

	for(i=0;i<list_limit;i++)
	{
		// RPTID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		rptid = atoi(var_data);

		if(p_rptid_svid_ctrl->Load_RPTID(rptid) < 0)
		{
			err_flag = 3;

			printf(" * CMsg_S02Fy::Recv__F33() ... \n");
			printf("  * rptid <- %1d \n", rptid);
			printf("  * errid <- %1d \n", err_flag);
			break;
		}

		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		item_limit = atoi(var_data);

		for(k=0;k<item_limit;k++)
		{
			// SVID
			db_name.Format("-1-2-%1d-2-%1d",i+1,k+1);
			p_recv_ctrl->Get_Data(db_name,var_data);
			svid = atoi(var_data);

			if(p_svid_ctrl->Is_SVID(svid) < 0)
			{
				err_flag = 4;

				printf(" * CMsg_S02Fy::Recv__F33() ... \n");
				printf("  * rptid <- %1d \n", rptid);
				printf("  * svid  <- %1d \n", svid);
				printf("  * errid <- %1d \n", err_flag);
				break;
			}

			p_rptid_svid_ctrl->Load_SVID(svid);
		}

		if(err_flag > 0)
		{
			break;
		}
	}

	if(err_flag == 0)
	{
		if(list_limit > 0)
		{
			p_rptid_svid_ctrl->Change_Save();
		}
		else
		{
			p_rptid_svid_ctrl->Save();
		}
	}
	else
	{
		p_rptid_svid_ctrl->Init_RPTID();
	}
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG

	// DRACK
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,err_flag);	
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
//  Link Event Report
void CMsg_S02Fy::Recv__F35(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CString	db_name;
	CString var_data;

	CI_FA_DB__CEID_CTRL *p_ceid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_CTRL();

	CI_FA_DB__CEID_RPTID_CTRL *p_ceid_rptid_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_RPTID_CTRL();

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;
	
	//----------------------------------------------------------
	//-----------------------------
	// RECV-MSG
	
	int i_dataid;
	CUIntArray l_ceid;

	int i;
	int list_limit;
	int k;
	int item_limit;
	int ceid;
	int rptid;

	int err_flag = 0;

	//-----------------------------
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	i_dataid = atoi(var_data);

	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);
	list_limit = atoi(var_data);

	p_ceid_rptid_ctrl->Init_CEID();

	for(i=0;i<list_limit;i++)
	{
		// CEID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		ceid = atoi(var_data);
		l_ceid.Add(ceid);

		if(p_ceid_rptid_ctrl->Load_CEID(ceid) < 0)
		{
			err_flag = 3;

			printf(" * CMsg_S02Fy::Recv__F35() ... \n");
			printf("  * ceid  <- %1d \n", ceid);
			printf("  * errid <- %1d \n", err_flag);
			break;
		}
		if(p_ceid_ctrl->Check(ceid) < 0)
		{
			err_flag = 4;

			printf(" * CMsg_S02Fy::Recv__F35() ... \n");
			printf("  * ceid  <- %1d \n", ceid);
			printf("  * errid <- %1d \n", err_flag);
			break;
		}

		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		item_limit = atoi(var_data);

		for(k=0;k<item_limit;k++)
		{
			// RPTID
			db_name.Format("-1-2-%1d-2-%1d",i+1,k+1);
			p_recv_ctrl->Get_Data(db_name,var_data);
			rptid = atoi(var_data);

			if(p_rptid_svid_ctrl->Is_RPTID(rptid) < 0)
			{
				err_flag = 5;

				printf(" * CMsg_S02Fy::Recv__F35() ... \n");
				printf("  * ceid  <- %1d \n", ceid);
				printf("  * rptid <- %1d \n", rptid);
				printf("  * errid <- %1d \n", err_flag);
				break;
			}

			p_ceid_rptid_ctrl->Load_RPTID(rptid);
		}

		if(err_flag > 0)
		{
			break;
		}
	}

	if(err_flag == 0)
	{
		if(list_limit > 0)			p_ceid_rptid_ctrl->Change_Save();
		else						p_ceid_rptid_ctrl->Save();

		int t_limit = l_ceid.GetSize();
		int t;

		for(t=0;t<t_limit;t++)
		{
			mRes__DATAID_CEID.Load__INFO(l_ceid[t],i_dataid);
		}
	}
	else
	{
		p_ceid_rptid_ctrl->Init_CEID();
	}
	//-----------------------------

	//----------------------------------------------------------
	//-----------------------------
	// SEND-MSG
	
	// LRACK
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,err_flag);	
	//-----------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
// 	Enable/Disable Event Report 
void CMsg_S02Fy::Recv__F37(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__CEID_CTRL *p_ceid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_CTRL();

	CString db_name;
	CString db_data;

	int ceed;
	int i;
	int limit;
	int ceid;
	int err_flag = 0;

	//-----------------------------
	p_ceid_ctrl->ClearBUFFER();

	// CEED
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,db_data);

	if(db_data.CompareNoCase("FF") == 0)	ceed = 1;
	else									ceed = atoi(db_data);

	// LIST_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,db_data);
	
	limit = atoi(db_data);

	if(limit < 1)
	{
		p_ceid_ctrl->SetALLBUFFER(ceed);
	}
	else
	{
		CString log_msg;
		CString bff;

		log_msg = "CEID ERROR LIST\n";

		for(i=0;i<limit;i++)
		{
			// CEID
			db_name.Format("-1-2-%1d",i+1);
			p_recv_ctrl->Get_Data(db_name,db_data);

			ceid = atoi(db_data);

			if(p_ceid_ctrl->SetBUFFER(ceid,ceed) < 0)
			{
				bff.Format("     CEID : [%1d]\n",ceid);
				log_msg += bff;

				err_flag = 1;
				//break;
			}
		}

		if(err_flag > 0)
		{
			CI_SEQ_INFO *p_seq_info = p_bridge_ctrl->pRES_SEQ_INFO;

			p_seq_info->Write__Bridge_Log("S2F37_ERROR.log",log_msg);
		}
	}
		
	// if(err_flag == 0)
	{
		p_ceid_ctrl->ApplyBUFFER();
		p_ceid_ctrl->Save();
	}
	/*
	else
	{
		p_ceid_ctrl->ClearBUFFER();
	}
	*/
	//----------------------------------------------------------

	//----------------------------------------------------------
	//-----------------------------
	
	// ERACK
	db_name = "-1";
	// p_send_ctrl->Add_Binary(db_name,err_flag);
	p_send_ctrl->Add_Binary(db_name,0);
	//-----------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}
//  Multi-Block Inquire
void CMsg_S02Fy::Recv__F39(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//----------------------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CString db_name;

	//-----------------------------

	// GRANT
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,0);
	//-----------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//-----------------------------

	FA__OK
}

//  Host Command Send (HCS)
void CMsg_S02Fy::Recv__F41(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CString db_name;
	CString var_data;

	//-------------------------------
	CString rcmd;
	CString cpname;
	CString cpval;
	int i;
	int l_limit;
	CStringArray l_cpname;
	CStringArray l_cpval;

	//-------------------------------
	// RCMD
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,rcmd);

	// LIST_LIMIT
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	l_limit = atoi(var_data);

	for(i=0;i<l_limit;i++)
	{
		// CPNAME
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,cpname);
		
		// CPVAL
		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,cpval);

		l_cpname.Add(cpname);
		l_cpval.Add(cpval);
	}
	//-------------------------------

	//-------------------------------
	int hcack = 0;
	CStringArray l_err_cpname;
	CUIntArray   l_err_cpack;

	F41__Check_RCMD(p_bridge_ctrl->pRES_300mm_CTRL->Get_E30(),
				   rcmd,
				   l_cpname,
				   l_cpval,
				   hcack,
				   l_err_cpname,
				   l_err_cpack);

	// HCACK
	db_name = "-1-1";
	p_send_ctrl->Add_U1(db_name,hcack);

	l_limit = l_err_cpack.GetSize();

	if(l_limit > 0)
	{
		int i;

		l_err_cpname.SetSize(l_limit);

		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,l_limit);

		for(i=0;i<l_limit;i++)
		{
			cpname = l_err_cpname[i];

			// CPNAME
			db_name.Format("-1-2-%1d-1",i+1);
			p_send_ctrl->Add_Ascii(db_name,cpname);

			// CPACK
			db_name.Format("-1-2-%1d-2",i+1);
			p_send_ctrl->Add_U1(db_name,l_err_cpack[i]);
		}
	}
	else
	{
		// LIST_LIMIT
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK
}
int  CMsg_S02Fy::F41__Check_RCMD(CI_FA_300mm__E30_CTRL* p_e30_ctrl,
								const CString& rcmd,
								const CStringArray& l_cpname,
								const CStringArray& l_cpval,
								int& hcack,
								CStringArray& l_err_cpname,
								CUIntArray&   l_err_cpack)
{
/*
HCACK
	0 = Acknowledge, command has been performed.
	1 = Command does not exist.
	2 = Cannot perform now.
	3 = At least, one parameter is invalid.
CPACK
	0 = Parameter Name does not exist.
	1 = Illegal Value specified for CPVAL.
	2 = Illegal Format specified for CPVAL.
*/  

	//-------------------------------------------------------
	if((rcmd == "REMOTE" )
	|| (rcmd == "LOCAL"  )
    || (rcmd == "OFFLINE"))
	{
		
	}
	else
	{
		if(p_e30_ctrl->Is_REMOTE() < 0)
		{
			hcack = 2;
			return -1;
		}
	}

	//-------------------------------------------------------
	if(rcmd == "PAUSE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_PAUSE() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Can_SYSTEM__PAUSE() < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_SYSTEM__PAUSE();
		return 1;
	}
	if(rcmd == "RESUME")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_RESUME() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Can_SYSTEM__RESUME() < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_SYSTEM__RESUME();
		return 1;
	}
	if(rcmd == "END")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_END() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Can_SYSTEM__END() < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_SYSTEM__END();
		return 1;
	}
	if(rcmd == "STOP")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_STOP() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Can_SYSTEM__STOP() < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_SYSTEM__STOP();
		return 1;
	}
	if(rcmd == "ABORT")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_ABORT() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Can_SYSTEM__ABORT() < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_SYSTEM__ABORT();
		return 1;
	}

	//-------------------------------------------------------
	if(rcmd == "REMOTE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_REMOTE() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Set_REMOTE() < 0)
		{
			hcack = 2;
			return -1;
		}
		
		return 1;
	}
	if(rcmd == "LOCAL")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_LOCAL() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Set_LOCAL() < 0)
		{
			hcack = 2;
			return -1;
		}

		return 1;
	}
	if(rcmd == "OFFLINE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__SYSTEM_OFFLINE() < 0)
		{
			hcack = 1;
			return -1;
		}

		if(p_e30_ctrl->Set_OFFLINE() < 0)
		{
			hcack = 2;
			return -1;
		}

		return 1;
	}
	
	//-------------------------------------------------------
	//-------------------------------------------------------
	if(rcmd == "PTN_CANCEL")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PTN_CANCEL() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PTN")		err_flag = 1;

		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		int ptn = atoi(l_cpval[0]);

		if(p_e30_ctrl->Can_LP__CANCEL(ptn) < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_LP__CANCEL(ptn);
		return 1;
	}
	if(rcmd == "PTN_PAUSE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PTN_PAUSE() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PTN")		err_flag = 1;

		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		int ptn = atoi(l_cpval[0]);

		if(p_e30_ctrl->Can_LP__PAUSE(ptn) < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_LP__PAUSE(ptn);
		return 1;
	}
	if(rcmd == "PTN_RESUME")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PTN_RESUME() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PTN")		err_flag = 1;

		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		int ptn = atoi(l_cpval[0]);

		if(p_e30_ctrl->Can_LP__RESUME(ptn) < 0)
		{
			hcack = 2;
			return -1;
		}

		p_e30_ctrl->Set_LP__RESUME(ptn);
		return 1;
	}
	if(rcmd == "PTN_ABORT")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PTN_ABORT() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PTN")		err_flag = 1;
	
		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		int ptn = atoi(l_cpval[0]);

		if(p_e30_ctrl->Can_LP__ABORT(ptn) < 0)
		{
			hcack = 2;
			return -1;
		}

		// p_e30_ctrl->Set_LP__ABORT(ptn);
		p_e30_ctrl->Set_LP__RETURN(ptn);
		return 1;
	}

	//-------------------------------------------------------
	//-------------------------------------------------------
	if(rcmd == "PM_ENABLE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PM_ENABLE() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PM")			err_flag = 1;

		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		if(err_flag < 0)
		{
			int pm_id = atoi(l_cpval[0]);

			if(p_e30_ctrl->RCMD__Does_EXIST__PMC(pm_id) < 0)
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}

			p_e30_ctrl->RCMD__Set_PM__USE(pm_id,1);
		}
		return 1;
	}
	if(rcmd == "PM_DISABLE")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PM_DISABLE() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "PM")			err_flag = 1;

		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		if(err_flag < 0)
		{
			int pm_id = atoi(l_cpval[0]);

			if(p_e30_ctrl->RCMD__Does_EXIST__PMC(pm_id) < 0)
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}

			p_e30_ctrl->RCMD__Set_PM__USE(pm_id,-1);
		}
		return 1;
	}
	if(rcmd == "PM_CONTROL")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__PM_CONTROL() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 2)	
		{
			err_flag = 1;

			hcack = 3;
			
			if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);
			l_err_cpack.Add(0);
			return -1;
		}

		if(err_flag < 0)
		{
			CString cpname;
			CString cpval;

			int i;
			int l_limit = l_cpname.GetSize();

			for(i=0;i<l_limit;i++)
			{
				cpname = l_cpname[i];
				cpval  = l_cpval[i];

				cpname.MakeUpper();

				if(i == 0)
				{
					if(cpname == "PM")
					{
						if(p_e30_ctrl->RCMD__Does_EXIST__PMC(atoi(cpval)) < 0)
						{
							l_err_cpname.Add(cpname);
							l_err_cpack.Add(1);

							err_flag = 1;
						}
					}
					else
					{
						l_err_cpname.Add(cpname);
						l_err_cpack.Add(0);

						err_flag = 1;
					}
				}
				else if(i == 1)
				{
					if(cpname != "CONTROL")
					{
						l_err_cpname.Add(cpname);
						l_err_cpack.Add(0);
	
						err_flag = 1;
					}
				}
			}
		}

		if(err_flag > 0)
		{
			hcack = 3;
			return -1;
		}
		else
		{
			int pmc_id = -1;

			CString cpval;

			int i;
			int l_limit = l_cpname.GetSize();

			for(i=0;i<l_limit;i++)
			{
				cpval = l_cpval[i];

				switch(i)
				{
					case 0:		
						pmc_id = atoi(cpval);
						break;

					case 1:
						p_e30_ctrl->RCMD__Set_PM__USE(pmc_id,atoi(cpval));
						break;
				}
			}
		}
		return 1;
	}

	//-------------------------------------------------------
	//-------------------------------------------------------
	if(rcmd == "ALARM_BUZZER")
	{
		if(p_e30_ctrl->RCMD__Is_ENABLED__ALARM_BUZZER() < 0)
		{
			hcack = 1;
			return -1;
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "CONTROL")	err_flag = 1;
	
		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		CString ctrl_cmmd = l_cpval[0];
		ctrl_cmmd.MakeUpper();
		
		if(ctrl_cmmd == "ON")
		{
			p_e30_ctrl->RCMD__Set_ON__ALARM_BUZZER();
		}
		else if(ctrl_cmmd == "OFF")
		{
			p_e30_ctrl->RCMD__Set_OFF_ALARM_BUZZER();
		}
		else
		{
			hcack = 3;
			l_err_cpack.Add(1);
			return -1;
		}

		return 1;
	}	

	//-------------------------------------------------------
	//-------------------------------------------------------
	if((rcmd == "SIGNAL_TOWER_RED")
	|| (rcmd == "SIGNAL_TOWER_YELLOW")
	|| (rcmd == "SIGNAL_TOWER_GREEN")
	|| (rcmd == "SIGNAL_TOWER_BLUE"))
	{
		if(rcmd == "SIGNAL_TOWER_RED")
		{
			if(p_e30_ctrl->RCMD__Is_ENABLED__SIG_RED() < 0)
			{
				hcack = 1;
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_YELLOW")
		{
			if(p_e30_ctrl->RCMD__Is_ENABLED__SIG_YELLOW() < 0)
			{
				hcack = 1;
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_GREEN")
		{
			if(p_e30_ctrl->RCMD__Is_ENABLED__SIG_GREEN() < 0)
			{
				hcack = 1;
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_BLUE")
		{
			if(p_e30_ctrl->RCMD__Is_ENABLED__SIG_BLUE() < 0)
			{
				hcack = 1;
				return -1;
			}
		}

		int err_flag = -1;

		if(l_cpname.GetSize() != 1)		err_flag = 1;
		if(l_cpname[0] != "CONTROL")	err_flag = 1;
	
		if(l_cpname.GetSize() > 0)		l_err_cpname.Add(l_cpname[0]);

		if(err_flag > 0)
		{
			hcack = 3;
			l_err_cpack.Add(0);
			return -1;
		}

		CString ctrl_cmmd = l_cpval[0];
		ctrl_cmmd.MakeUpper();
		
		if(rcmd == "SIGNAL_TOWER_RED")
		{
			if(ctrl_cmmd == "ON")
			{
				p_e30_ctrl->RCMD__Set_ON__SIG_RED();
			}
			else if(ctrl_cmmd == "OFF")
			{
				p_e30_ctrl->RCMD__Set_OFF__SIG_RED();
			}
			else if(ctrl_cmmd == "BLINK")
			{
				p_e30_ctrl->RCMD__Set_BLINK__SIG_RED();
			}
			else
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_YELLOW")
		{
			if(ctrl_cmmd == "ON")
			{
				p_e30_ctrl->RCMD__Set_ON__SIG_YELLOW();
			}
			else if(ctrl_cmmd == "OFF")
			{
				p_e30_ctrl->RCMD__Set_OFF__SIG_YELLOW();
			}
			else if(ctrl_cmmd == "BLINK")
			{
				p_e30_ctrl->RCMD__Set_BLINK__SIG_YELLOW();
			}
			else
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_GREEN")
		{
			if(ctrl_cmmd == "ON")
			{
				p_e30_ctrl->RCMD__Set_ON__SIG_GREEN();
			}
			else if(ctrl_cmmd == "OFF")
			{
				p_e30_ctrl->RCMD__Set_OFF__SIG_GREEN();
			}
			else if(ctrl_cmmd == "BLINK")
			{
				p_e30_ctrl->RCMD__Set_BLINK__SIG_GREEN();
			}
			else
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}
		}
		else if(rcmd == "SIGNAL_TOWER_BLUE")
		{
			if(ctrl_cmmd == "ON")
			{
				p_e30_ctrl->RCMD__Set_ON__SIG_BLUE();
			}
			else if(ctrl_cmmd == "OFF")
			{
				p_e30_ctrl->RCMD__Set_OFF__SIG_BLUE();
			}
			else if(ctrl_cmmd == "BLINK")
			{
				p_e30_ctrl->RCMD__Set_BLINK__SIG_BLUE();
			}
			else
			{
				hcack = 3;
				l_err_cpack.Add(1);
				return -1;
			}
		}

		return 1;
	}	


	hcack = 1;
	return -1;
}


// 	Reset Spooling Streams and Functions  (RSSF) 	H -> E		
void CMsg_S02Fy::Recv__F43(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_300mm__E30_CTRL *p_e30_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString db_name;
	CString var_data;

	//-------------------------------
	int rspack = 0;
	int err_count = 0;

	int strid;
	int fncid;

	int i;
	int limit;
	int t;
	int t_limit;

	// STRID_LIST
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);

	if(limit < 1)
	{
		p_e30_ctrl->Spool__Clear_All_SxFy();
	}

	for(i=0;i<limit;i++)
	{
		// STRID
		db_name.Format("-1-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		
		strid = atoi(var_data);

	  	// FNCID_LIST
		db_name.Format("-1-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		t_limit = atoi(var_data);

		int err_code = p_e30_ctrl->Spool__Clear_SxFy(strid);

		if(err_code < 0)
		{
			err_count++;

			// STRID
			db_name.Format("-1-2-%1d-1",err_count);
			p_send_ctrl->Add_U1(db_name,strid);

			// STRACK
			db_name.Format("-1-2-%1d-2",err_count);
			p_send_ctrl->Add_Binary(db_name,-err_code);

			// FNCID_LIST
			db_name.Format("-1-2-%1d-3",err_count);
			p_send_ctrl->Add_List(db_name,0);

			continue;
		}

		int fncid_count = 0;

		for(t=0;t<t_limit;t++)
		{
			// FNCID
			db_name.Format("-1-%1d-2-%1d",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			fncid = atoi(var_data);

			if(p_e30_ctrl->Spool__Load_SxFy(strid,fncid) < 0)
			{
				fncid_count++;

				// STRID
				db_name.Format("-1-2-%1d-1",err_count+1);
				p_send_ctrl->Add_U1(db_name,strid);

				// STRACK
				db_name.Format("-1-2-%1d-2",err_count+1);
				p_send_ctrl->Add_Binary(db_name,3);

				// FNCID
				db_name.Format("-1-2-%1d-3-%1d",err_count+1,fncid_count);
				p_send_ctrl->Add_U1(db_name,fncid);
			}
		}

		// FNCID_LIST
		db_name.Format("-1-2-%1d-3",err_count+1);
		p_send_ctrl->Add_List(db_name,fncid_count);

		if(fncid_count > 0)		err_count++;
	}

	//-------------------------------
	if(err_count > 0)		rspack = 1;
	else					rspack = 0;
	
    // RSPACK
	db_name = "-1-1";
	p_send_ctrl->Add_Binary(db_name,rspack);

    // STRID_LIST
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_count);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK
}


// 	Variable Limit Attribute Request 
void CMsg_S02Fy::Recv__F45(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_DB__LIMIT_VID_CTRL *p_limit_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_LIMIT_VID_CTRL();

	CString db_name;
	CString var_data;

	//-------------------------------
	int vid;
	int i;
	int limit;
	int t;
	int t_limit;
	int vlaack = 0;
	int err_count = 0;

	p_limit_ctrl->Init_BFF();

	//-------------------------------
	// VID_LIST
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	limit = atoi(var_data);

	if(limit < 1)
	{
		p_limit_ctrl->Undefine_BFF__ALL_VID();
	}

	for(i=0;i<limit;i++)
	{
	  	// VID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		vid = atoi(var_data);

		if(p_limit_ctrl->Load_BFF__VID(vid) < 0)
		{
			vlaack = 1;

			err_count++;

			// VID
			db_name.Format("-1-2-%1d-1",err_count);
			p_send_ctrl->Add_U4(db_name,vid);

			// LVACK
			db_name.Format("-1-2-%1d-2",err_count);
			p_send_ctrl->Add_Binary(db_name,1);

			// INFO_LIST
			db_name.Format("-1-2-%1d-3",err_count);
			p_send_ctrl->Add_List(db_name,0);

			continue;
		}

		// INFO_LIST
		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		t_limit = atoi(var_data);

		if(t_limit < 1)
		{
			p_limit_ctrl->Undefine_BFF__VID(vid);
			continue;
		}

		int    limit_id;
		double upper_db;
		double lower_db;
		int    err_flag = 0;
		int    lvack = 0;

		for(t=0;t<t_limit;t++)
		{
			// LIMITID
			db_name.Format("-1-2-%1d-2-%1d-1",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			limit_id = atoi(var_data);

			if(p_limit_ctrl->Load_BFF__LIMITID(vid,limit_id) < 0)
			{
				err_flag = 1;

				lvack = 4;

				// LIMITID
				db_name.Format("-1-2-%1d-3-1",err_count+1);
				p_send_ctrl->Add_Binary(db_name,limit_id);

				// LIMITACK
				db_name.Format("-1-2-%1d-3-2",err_count+1);
				p_send_ctrl->Add_Binary(db_name,1);

				continue;
			}

			// DB_LIST
			db_name.Format("-1-2-%1d-2-%1d-2",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			switch(atoi(var_data))
			{
				case 0:
					p_limit_ctrl->Undefine_BFF__ALL_LIMITID(vid);
					break;

				case 2:
					{
						// UPPERDB
						db_name.Format("-1-2-%1d-2-%1d-2-1",i+1,t+1);
						p_recv_ctrl->Get_Data(db_name,var_data);

						upper_db = atof(var_data);

					    // LOWERDB
						db_name.Format("-1-2-%1d-2-%1d-2-2",i+1,t+1);
						p_recv_ctrl->Get_Data(db_name,var_data);

						lower_db = atof(var_data);

						int err_code = p_limit_ctrl->Load_BFF__LOWERDB_UPPERDB(vid,
																			   limit_id,
																			   lower_db,
																			   upper_db);

						if(err_code < 0)
						{
							err_flag = 1;

							lvack = 4;

							// LIMITID
							db_name.Format("-1-2-%1d-3-1",err_count+1);
							p_send_ctrl->Add_Binary(db_name,limit_id);

							// LIMITACK
							db_name.Format("-1-2-%1d-3-2",err_count+1);
							p_send_ctrl->Add_Binary(db_name,-err_code);
						}
					}
					break;

				default:
					{
						err_flag = 1;

						lvack = 4;

						// LIMITID
						db_name.Format("-1-2-%1d-3-1",err_count+1);
						p_send_ctrl->Add_Binary(db_name,limit_id);

						// LIMITACK
						db_name.Format("-1-2-%1d-3-2",err_count+1);
						p_send_ctrl->Add_Binary(db_name,8);
					}
					break;
			}
		}

		if(err_flag > 0)
		{
			vlaack = 1;

			// VID
			db_name.Format("-1-2-%1d-1",err_count+1);
			p_send_ctrl->Add_U4(db_name,vid);

			// LVACK
			db_name.Format("-1-2-%1d-2",err_count+1);
			p_send_ctrl->Add_Binary(db_name,lvack);

			// INFO_LIST
			db_name.Format("-1-2-%1d-3",err_count+1);
			p_send_ctrl->Add_List(db_name,2);

			err_count++;
		}
	}

    // VLAACK			
	db_name = "-1-1";
	p_send_ctrl->Add_Binary(db_name,vlaack);

    // VID_LIST
	db_name = "-1-2";
	p_send_ctrl->Add_List(db_name,err_count);

	if(err_count > 0)
	{
		p_limit_ctrl->Clear_BFF();
	}
	else
	{
		p_limit_ctrl->Save_BFF();
	}
	//-------------------------------

	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK
}


// 	Variable Limit Attribute Request 
void CMsg_S02Fy::Recv__F47(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_FA_DB__LIMIT_VID_CTRL *p_limit_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_LIMIT_VID_CTRL();

	CString db_name;
	CString var_data;

	//-------------------------------
	CUIntArray l_vid;
	int i;
	int limit;

	//-------------------------------
	// VID_LIST
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	limit = atoi(var_data);

	for(i=0;i<limit;i++)
	{
	  	// VID
		db_name.Format("-1-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_vid.Add(atoi(var_data));
	}
	//-------------------------------

	//-------------------------------
	CDS_LIMIT_VID_INFO ds_info;
	int vid;

	limit = l_vid.GetSize();

	if(limit > 0)
	{
		for(i=0;i<limit;i++)
		{
			vid = (int) l_vid[i];

			// VID
			db_name.Format("-1-%1d-1",i+1);
			p_send_ctrl->Add_U4(db_name,vid);

			if(p_limit_ctrl->Get_INFO(vid,ds_info) > 0)
			{
				// INFO_LIST
				db_name.Format("-1-%1d-2",i+1);
				p_send_ctrl->Add_List(db_name,4);

				// UNIT
				db_name.Format("-1-%1d-2-1",i+1);
				p_send_ctrl->Add_Ascii(db_name,ds_info.sUNIT);
				
				// LIMITMIN
				db_name.Format("-1-%1d-2-2",i+1);
				p_send_ctrl->Add_F4(db_name,ds_info.dLIMIT_MIN);

				// LIMITMAX
				db_name.Format("-1-%1d-2-3",i+1);
				p_send_ctrl->Add_F4(db_name,ds_info.dLIMIT_MAX);

				if((ds_info.iDEFINE_VID     < 0)
				|| (ds_info.iDEFINE_LIMITID < 0))
				{
  					// LIMITID_LIST
					db_name.Format("-1-%1d-2-4",i+1);
					p_send_ctrl->Add_List(db_name,0);
				}
				else
				{
  					// LIMITID_LIST
					db_name.Format("-1-%1d-2-4",i+1);
					p_send_ctrl->Add_List(db_name,1);

					// LIMITID
					db_name.Format("-1-%1d-2-4-1-1",i+1);
					p_send_ctrl->Add_Binary(db_name,ds_info.iLIMIT_ID);

					// UPPERDB
					db_name.Format("-1-%1d-2-4-1-2",i+1);
					p_send_ctrl->Add_F4(db_name,ds_info.dUPPER_DB);

					// LOWERDB
					db_name.Format("-1-%1d-2-4-1-3",i+1);
					p_send_ctrl->Add_F4(db_name,ds_info.dLOWER_DB);
				}
			}
			else
			{
		     	// INFO_LIST
				db_name.Format("-1-%1d-2",i+1);
				p_send_ctrl->Add_List(db_name,0);
			}
		}
	}
	else
	{
		limit = 0;

		while(p_limit_ctrl->Get_INFO(limit,vid,ds_info) > 0)
		{
			i = limit++;

			// VID
			db_name.Format("-1-%1d-1",i+1);
			p_send_ctrl->Add_U4(db_name,vid);

			if(p_limit_ctrl->Get_INFO(vid,ds_info) > 0)
			{
		     	// INFO_LIST
				db_name.Format("-1-%1d-2",i+1);
				p_send_ctrl->Add_List(db_name,4);

				// UNIT
				db_name.Format("-1-%1d-2-1",i+1);
				p_send_ctrl->Add_Ascii(db_name,ds_info.sUNIT);
				
				// LIMITMIN
				db_name.Format("-1-%1d-2-2",i+1);
				p_send_ctrl->Add_F4(db_name,ds_info.dLIMIT_MIN);

				// LIMITMAX
				db_name.Format("-1-%1d-2-3",i+1);
				p_send_ctrl->Add_F4(db_name,ds_info.dLIMIT_MAX);

				if((ds_info.iDEFINE_VID     < 0)
				|| (ds_info.iDEFINE_LIMITID < 0))
				{
  					// LIMITID_LIST
					db_name.Format("-1-%1d-2-4",i+1);
					p_send_ctrl->Add_List(db_name,0);
				}
				else
				{
					// LIMITID_LIST
					db_name.Format("-1-%1d-2-4",i+1);
					p_send_ctrl->Add_List(db_name,1);

					// LIMITID
					db_name.Format("-1-%1d-2-4-1-1",i+1);
					p_send_ctrl->Add_Binary(db_name,ds_info.iLIMIT_ID);

  					// UPPERDB
					db_name.Format("-1-%1d-2-4-1-2",i+1);
					p_send_ctrl->Add_F4(db_name,ds_info.dUPPER_DB);

					// LOWERDB
					db_name.Format("-1-%1d-2-4-1-3",i+1);
					p_send_ctrl->Add_F4(db_name,ds_info.dLOWER_DB);
				}
			}
			else
			{
		     	// INFO_LIST
				db_name.Format("-1-%1d-2",i+1);
				p_send_ctrl->Add_List(db_name,0);
			}
		}
	}

	// VID_LIST   
	db_name = "-1";
	p_send_ctrl->Add_List(db_name,limit);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK
}
