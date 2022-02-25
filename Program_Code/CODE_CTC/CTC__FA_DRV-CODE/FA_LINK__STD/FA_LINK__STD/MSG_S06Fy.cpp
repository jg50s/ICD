#include "StdAFx.h"

#include "MSG_S06Fy.h"
CMsg_S06Fy mMSG_S06Fy;

#include "CRes__DATAID_CEID.h"
extern CRes__DATAID_CEID mRes__DATAID_CEID;


//----------------------------------------------------------------------------
CMsg_S06Fy::CMsg_S06Fy()
{
	iSx = 6;
}

void CMsg_S06Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;
	
	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Send__F1(p_bridge_ctrl);		return;
		case 9:		Send__F9(p_bridge_ctrl);		return;
		case 11:	Send__F11(p_bridge_ctrl);		return;
	}
}

void CMsg_S06Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 15:	Recv__F15(p_bridge_ctrl);		return;
		case 17:	Recv__F17(p_bridge_ctrl);		return;
		case 19:	Recv__F19(p_bridge_ctrl);		return;
		case 21:	Recv__F21(p_bridge_ctrl);		return;
		case 23:	Recv__F23(p_bridge_ctrl);		return;
	}
}

//----------------------------------------------------------------------------
/*
void CMsg_S06Fy::Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	main_name;
	CString	sub_name;
	CString var_data;
	int     trid = 0;

	main_name = "##S6F1";
	sub_name  = "TRID";
	
	p_bridge_ctrl->pRES_VARIABLE_CTRL->Get_Variable(main_name,sub_name,var_data);

	trid = atoi(var_data);
	//--------------------------------------------

	//--------------------------------------------
	CString db_name;
	int i;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__SVID_TRACE_CTRL *p_trace_ctrl
		= p_bridge_ctrl->pRES_SVID_TRACE_CTRL;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();


	int           smpln;
	CString       stime;
	CUIntArray    svid_list;
	int			  svid_limit;
	CDS_SVID_DATA svid_data;
	int			  svid;
	

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Date_And_Time(stime);
	p_trace_ctrl->Get_TRACE_INFO(trid,smpln,svid_list);


	// TRID
	db_name = "-1-1";
	p_send_ctrl->Add_U4(db_name,trid);

	// SMPLN
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,smpln);

	// STIME
	db_name = "-1-3";
	p_send_ctrl->Add_Ascii(db_name,stime);

	// LIST_LIMIT
	svid_limit = svid_list.GetSize();

	db_name = "-1-4";
	p_send_ctrl->Add_List(db_name,svid_limit);

	for(i=0;i<svid_limit;i++)
	{
		svid = svid_list[i];
		svid_data.sData = "";

		p_svid_ctrl->Get_DATA(svid,
							  svid_data,
							  p_bridge_ctrl->pRES_300mm_CTRL,
							  p_bridge_ctrl->pRES_VARIABLE_CTRL);
	
		// V
		db_name.Format("-1-4-%1d",i+1);
		p_send_ctrl->Add_Virtual(db_name,svid_data);
	}

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//--------------------------------------------

	FA__OK;
}
*/
void CMsg_S06Fy::Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	main_name;
	CString	sub_name;
	CString var_data;
	int     trid = 0;

	main_name = "##S6F1";
	sub_name  = "TRID";
	
	p_bridge_ctrl->pRES_VARIABLE_CTRL->Get_Variable(main_name,sub_name,var_data);

	trid = atoi(var_data);
	//--------------------------------------------

	//--------------------------------------------
	CString db_name;
	int i;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__SVID_TRACE_CTRL *p_trace_ctrl
		= p_bridge_ctrl->pRES_SVID_TRACE_CTRL;

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();


	int           smpln;
	CString       stime;
	int			  svid_limit;
	CPtrArray     l_svid_data;
	CDS_SVID_DATA *p_svid_data;
	int			  svid;
	

	p_bridge_ctrl->pRES_SEQ_INFO->Get__Date_And_Time(stime);
	p_trace_ctrl->Get_TRACE_INFO_EX(trid,smpln,l_svid_data);


	// TRID
	db_name = "-1-1";
	p_send_ctrl->Add_U4(db_name,trid);

	// SMPLN
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,smpln);

	// STIME
	db_name = "-1-3";
	p_send_ctrl->Add_Ascii(db_name,stime);

	// LIST_LIMIT
	svid_limit = l_svid_data.GetSize();

	db_name = "-1-4";
	p_send_ctrl->Add_List(db_name,svid_limit);

	for(i=0;i<svid_limit;i++)
	{
		p_svid_data = (CDS_SVID_DATA*) l_svid_data[i];
	
		// V
		db_name.Format("-1-4-%1d",i+1);
		p_send_ctrl->Add_Virtual(db_name,*p_svid_data);
	}

	p_trace_ctrl->Delete_TRACE_INFO(l_svid_data);
	l_svid_data.RemoveAll();

	//
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//--------------------------------------------

	FA__OK;
}
/*
void CMsg_S06Fy::Send__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	main_name;
	CString	sub_name;
	CString var_data;
	int ceid = -1;

	main_name = "##S6F9";
	sub_name = "CEID";

	p_bridge_ctrl->pRES_VARIABLE_CTRL->Get_Variable(main_name,sub_name,var_data);
	ceid = atoi(var_data);

	if(ceid < 1)		FA__ERROR;
	//--------------------------------------------	

	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__FVS_CTRL *p_fvs_ctrl 
		= p_bridge_ctrl->pRES_DB_CTRL->Get_FVS_CTRL();

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();


	CString pp_name;
	CString db_name;
	CString db_data;

	//-------------------------------
	CDS_SVID_DATA svid_data;
	int	ceid_index;

	CString fmt_type;
	int dsid_index = 0;
	int pfcd;
	int dataid;
	int dsid_size;
	int dsid;

	ceid_index = p_fvs_ctrl->Get_Index_From_CEID(ceid);
		
	p_fvs_ctrl->Get_PFCD_From_Index(ceid_index,pfcd);
	p_fvs_ctrl->Get_DATAID_From_Index(ceid_index,dataid);

	//-----------------------------
	// PFCD
	db_name = "-1-1";
	p_send_ctrl->Add_U4(db_name,pfcd);

	// DATAID
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,dataid);

	// CEID
	db_name = "-1-3";
	p_send_ctrl->Add_U4(db_name,ceid);
	//-----------------------------

	dsid_size = p_fvs_ctrl->Get_DSID_SIZE(ceid_index);

	//-----------------------------
	// DSID_LIST
	db_name = "-1-4";
	p_send_ctrl->Add_List(db_name,dsid_size);
	//-----------------------------

	while(p_fvs_ctrl->Get_DSID_From_Index(ceid_index,dsid_index,dsid,fmt_type) > 0)
	{
		int vid_index = 0;
		int vid_size;
		int vid;
		int size;

		pp_name.Format("-1-4-%1d",(dsid_index+1));

		//-----------------------------
		// DSID
		db_data.Format("%1d",dsid);
			
		db_name  = pp_name;
		db_name += "-1";
		p_send_ctrl->Add_Virtual(db_name,fmt_type,1,db_data);

		// VID_LIST
		vid_size = p_fvs_ctrl->Get_VID_SIZE(ceid_index,dsid_index);

		db_name  = pp_name;
		db_name += "-2";
		p_send_ctrl->Add_List(db_name,vid_size);
		//-----------------------------

		pp_name = db_name;

		while(p_fvs_ctrl->Get_VID_INF_From_Index(ceid_index,dsid_index,vid_index,vid,fmt_type,size) > 0)
		{
			vid_index++;

			p_svid_ctrl->Get_DATA(vid,
								  svid_data,
								  p_bridge_ctrl->pRES_300mm_CTRL,
								  p_bridge_ctrl->pRES_VARIABLE_CTRL);

			if(size == 0)
			{
				fmt_type = svid_data.sFmt_Type;
				size     = svid_data.iFmt_Byte;
			}

			//-----------------------------
			// VID

			db_name.Format("%s-%1d",pp_name,vid_index);
			p_send_ctrl->Add_Virtual(db_name,fmt_type,size,svid_data.sData);	
			//-----------------------------				
		}

		dsid_index++;
	}
	//-------------------------------
	
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//--------------------------------------------

	FA__OK;
}
*/
void CMsg_S06Fy::Send__F9(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	main_name;
	CString	sub_name;
	CString var_data;
	int ceid = -1;

	main_name = "##S6F9";
	sub_name = "CEID";

	p_bridge_ctrl->pRES_VARIABLE_CTRL->Get_Variable(main_name,sub_name,var_data);
	ceid = atoi(var_data);

	if(ceid < 1)		FA__ERROR;
	//--------------------------------------------	

	//--------------------------------------------
	CI_FA_300mm__E30_CTRL *p_e30 = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();
	int lp_mhp = 0;

	if(p_e30->Check_CEID__LPx_WAFER_MHP_REPORT(ceid,lp_mhp) > 0)
	{
		Make__F9__LPx_MHP_REPORT(p_bridge_ctrl,ceid,lp_mhp);
	}
	else
	{

	}
	//-------------------------------
	
	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//--------------------------------------------

	FA__OK;
}
void CMsg_S06Fy::Send__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	main_name;
	CString	sub_name;
	CString var_data;
	int ceid = -1;

	main_name = "##S6F11";
	sub_name = "CEID";
	p_bridge_ctrl->pRES_VARIABLE_CTRL->Get_Variable(main_name,sub_name,var_data);
	ceid = atoi(var_data);

	if(ceid < 1)		FA__ERROR;
	//--------------------------------------------	
	
	//--------------------------------------------
	CString db_name;
	CUIntArray rptid_list;
	CUIntArray vid_list;
	int rptid_limit;
	int vid_limit;
	int rptid;
	int vid;
	int i;
	int k;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__CEID_RPTID_CTRL *p_ceid_rptid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_RPTID_CTRL();

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	// DATAID 
	{
		int i_dataid = 0;
		mRes__DATAID_CEID.Get__DATAID(ceid,i_dataid);
		var_data.Format("%1d",i_dataid);

		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,var_data);
	}

	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,ceid);

	p_ceid_rptid_ctrl->Get_RPTID(ceid,rptid_list);

	rptid_limit = rptid_list.GetSize();

	db_name = "-1-3";
	p_send_ctrl->Add_List(db_name,rptid_limit);

	for(i=0;i<rptid_limit;i++)
	{
		rptid = rptid_list[i];
		
		db_name.Format("-1-3-%1d-1",i+1);
		p_send_ctrl->Add_U4(db_name,rptid);

		vid_list.RemoveAll();
		p_rptid_svid_ctrl->Get_SVID(rptid,vid_list);

		vid_limit = vid_list.GetSize();

		db_name.Format("-1-3-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,vid_limit);

		for(k=0;k<vid_limit;k++)
		{
			vid = vid_list[k];
			
			CDS_SVID_DATA svid_data;

			p_svid_ctrl->Get_DATA(vid,
								  svid_data,
								  p_bridge_ctrl->pRES_300mm_CTRL,
								  p_bridge_ctrl->pRES_VARIABLE_CTRL);

			db_name.Format("-1-3-%1d-2-%1d",i+1,k+1);
			p_send_ctrl->Add_Virtual(db_name,svid_data);
		}		
	}

	if(p_bridge_ctrl->pFA_DRV_CTRL->Send() < 0)
	{
		FA__ERROR;
	}
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;
	//--------------------------------------------

	FA__OK;
}


//----------------------------------------------------------------------------
void CMsg_S06Fy::Recv__F15(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	db_name;
	CString var_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__CEID_RPTID_CTRL *p_ceid_rptid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_RPTID_CTRL();

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();
	
	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	//--------------------------------------------
	int			  ceid;
	CUIntArray    rptid_list;
	CUIntArray    svid_list;
	CDS_SVID_DATA svid_data;

	int rptid;
	int svid;
	int i;
	int limit;

	// CEID
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	ceid = atoi(var_data);

	p_ceid_rptid_ctrl->Get_RPTID(ceid,rptid_list);

	limit = rptid_list.GetSize();
	
	// CEID
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,ceid);

	// LIST_LIMIT
	db_name = "-1-3";
	p_send_ctrl->Add_List(db_name,limit);

	for(i=0;i<limit;i++)
	{
		rptid = rptid_list[i];

		// RPTID
		db_name.Format("-1-3-%1d-1",i+1);
		p_send_ctrl->Add_U4(db_name,rptid);

		if(p_rptid_svid_ctrl->Get_SVID(rptid,svid_list) > 0)
		{
			int k;
			int k_limit = svid_list.GetSize();

			// SVID_LIMIT
			db_name.Format("-1-3-%1d-2",i+1);
			p_send_ctrl->Add_List(db_name,k_limit);

			for(k=0;k<k_limit;k++)
			{
				svid = svid_list[k];
				p_svid_ctrl->Get_DATA(svid,
									  svid_data,
									  p_bridge_ctrl->pRES_300mm_CTRL,
									  p_bridge_ctrl->pRES_VARIABLE_CTRL);

				// V
				db_name.Format("-1-3-%1d-2-%1d",i+1,k+1);
				p_send_ctrl->Add_Virtual(db_name,svid_data);
			}
		}
	}
	//--------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S06Fy::Recv__F17(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	db_name;
	CString var_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__CEID_RPTID_CTRL *p_ceid_rptid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_CEID_RPTID_CTRL();

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();
	
	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	//--------------------------------------------
	int			  ceid;
	CUIntArray    rptid_list;
	CUIntArray    svid_list;
	CDS_SVID_DATA svid_data;

	int rptid;
	int svid;
	int i;
	int limit;

	// CEID
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);
	ceid = atoi(var_data);

	p_ceid_rptid_ctrl->Get_RPTID(ceid,rptid_list);

	limit = rptid_list.GetSize();

	// CEID
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,ceid);

	// LIST_LIMIT
	db_name = "-1-3";
	p_send_ctrl->Add_List(db_name,limit);

	for(i=0;i<limit;i++)
	{
		rptid = rptid_list[i];

		// RPTID
		db_name.Format("-1-3-%1d-1",i+1);
		p_send_ctrl->Add_U4(db_name,rptid);

		if(p_rptid_svid_ctrl->Get_SVID(rptid,svid_list) > 0)
		{
			int k;
			int k_limit = svid_list.GetSize();

			// SVID_LIMIT
			db_name.Format("-1-3-%1d-2",i+1);
			p_send_ctrl->Add_List(db_name,k_limit);

			for(k=0;k<k_limit;k++)
			{
				svid = svid_list[k];
				p_svid_ctrl->Get_DATA(svid,
									  svid_data,
									  p_bridge_ctrl->pRES_300mm_CTRL,
									  p_bridge_ctrl->pRES_VARIABLE_CTRL);
				
				// VID
				db_name.Format("-1-3-%1d-2-%1d-1",i+1,k+1);
				p_send_ctrl->Add_U4(db_name,svid);

				// V
				db_name.Format("-1-3-%1d-2-%1d-2",i+1,k+1);
				p_send_ctrl->Add_Virtual(db_name,svid_data);
			}
		}
	}
	//--------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S06Fy::Recv__F19(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	db_name;
	CString var_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	//--------------------------------------------
	int			  rptid;
	CUIntArray    svid_list;
	CDS_SVID_DATA svid_data;

	int svid;
	int i;
	int limit;

	// RPTID
	db_name = "-1";
	p_bridge_ctrl->pMSG_RECV_CTRL->Get_Data(db_name,var_data);

	rptid = atoi(var_data);

	p_rptid_svid_ctrl->Get_SVID(rptid,svid_list);

	limit = svid_list.GetSize();

	// LIST_LIMIT
	db_name = "-1";
	p_send_ctrl->Add_List(db_name,limit);

	for(i=0;i<limit;i++)
	{
		svid = svid_list[i];
		p_svid_ctrl->Get_DATA(svid,
							  svid_data,
							  p_bridge_ctrl->pRES_300mm_CTRL,
							  p_bridge_ctrl->pRES_VARIABLE_CTRL);

		// V
		db_name.Format("-1-%1d",i+1);
		p_send_ctrl->Add_Virtual(db_name,svid_data);		
	}
	//--------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S06Fy::Recv__F21(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	db_name;
	CString var_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_DB__RPTID_SVID_CTRL *p_rptid_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_RPTID_SVID_CTRL();

	CI_FA_DB__SVID_CTRL *p_svid_ctrl
		= p_bridge_ctrl->pRES_DB_CTRL->Get_SVID_CTRL();

	//--------------------------------------------
	int			  rptid;
	CUIntArray    svid_list;
	CDS_SVID_DATA svid_data;

	int svid;
	int i;
	int limit;

	// RPTID
	db_name = "-1";
	p_bridge_ctrl->pMSG_RECV_CTRL->Get_Data(db_name,var_data);

	rptid = atoi(var_data);

	p_rptid_svid_ctrl->Get_SVID(rptid,svid_list);

	limit = svid_list.GetSize();

	// LIST_LIMIT
	db_name = "-1";
	p_send_ctrl->Add_List(db_name,limit);

	for(i=0;i<limit;i++)
	{
		svid = svid_list[i];
		p_svid_ctrl->Get_DATA(svid,
							  svid_data,
							  p_bridge_ctrl->pRES_300mm_CTRL,
							  p_bridge_ctrl->pRES_VARIABLE_CTRL);

		// VID
		db_name.Format("-1-%1d-1",i+1);
		p_send_ctrl->Add_U4(db_name,svid);		

		// V
		db_name.Format("-1-%1d-2",i+1);
		p_send_ctrl->Add_Virtual(db_name,svid_data);
	}
	//--------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S06Fy::Recv__F23(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CString	db_name;
	CString var_data;

	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl 
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E30_CTRL *p_e30_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CI_FA_VARIABLE_CTRL *p_var_ctrl 
		= p_bridge_ctrl->pRES_VARIABLE_CTRL;
	
	//--------------------------------------------
	int trans_flag = -1;
	int rsdc;
	int rsda = 0;

	// RSDC
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	rsdc = atoi(var_data);
	
	//--------------------------------------------
	switch(rsdc)
	{
		case 0:			// Transmit
			{
				if(p_e30_ctrl->Get__SPOOLING_COUNT_ACTUAL() > 0)
				{
					trans_flag = 1;
				}
				else
				{
					rsda = 2;
				}
			}
			break;

		case 1:			// Purge
			{
				if(p_e30_ctrl->Get__SPOOLING_COUNT_ACTUAL() > 0)
				{
					p_e30_ctrl->Spool__Purge();
				}
				else
				{
					rsda = 2;
				}
			}
			break;

		default:		
			rsda = 3;
			break;
	}

	// RSDA
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,rsda);
	//--------------------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	if(trans_flag > 0)
	{
		CString main_name = "#RCV_MSG-S6F23";
		CString sub_name  = "RSDC";
		CString var_data  = "OK";

		p_var_ctrl->Set_Variable(main_name,sub_name,var_data);
	}

	FA__OK;
}
