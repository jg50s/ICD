#include "StdAFx.h"

#include "MSG_S14Fy.h"
CMsg_S14Fy mMSG_S14Fy;


//----------------------------------------------------------------------------
CMsg_S14Fy::CMsg_S14Fy()
{
	iSx = 14;
}

void CMsg_S14Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	/*
	switch(p_bridge_ctrl->iFy)
	{
	}
	*/
}

void CMsg_S14Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Recv__F1(p_bridge_ctrl);		return;
		case 3:		Recv__F3(p_bridge_ctrl);		return;
		case 5:		Recv__F5(p_bridge_ctrl);		return;
		case 7:		Recv__F7(p_bridge_ctrl);		return;

		case 9:
			switch(p_bridge_ctrl->iType)
			{
				case 0:		Recv__F9_0(p_bridge_ctrl);		return;
				case 1:		Recv__F9_1(p_bridge_ctrl);		return;
			}
			return;

		case 11:	Recv__F11(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S14Fy::Recv__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E39_CTRL *p_e39_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E39();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CString objtype;
	int objid_list = 0;    
	int i;
	CStringArray l_objid;
	int attr_list = 0;
	CStringArray l_attrid;
	CStringArray l_attrdata;
	CUIntArray   l_attrreln;
	int attrid_list = 0;
	CStringArray  ll_attrid;
		
	//-------------------------------
	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// OBJTYPE
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objtype = var_data;

	// OBJID_LIST
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objid_list = atoi(var_data);
	for(i=0;i<objid_list;i++)
	{
		// OBJID
		db_name.Format("-1-3-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_objid.Add(var_data);
	}

	// ATTR_LIST
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	attr_list = atoi(var_data);
	
	for(i=0;i<attr_list;i++)
	{
		// ATTRID
		db_name.Format("-1-4-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrid.Add(var_data);

		// ATTRDATA
		db_name.Format("-1-4-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrdata.Add(var_data);

		// ATTRRELN
		db_name.Format("-1-4-%1d-3",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrreln.Add(atoi(var_data));
	}

	// ATTRID_LIST
	db_name = "-1-5";
	p_recv_ctrl->Get_Data(db_name,var_data);

	attrid_list = atoi(var_data);

	for(i=0;i<attrid_list;i++)
	{
		// ATTRID
		db_name.Format("-1-5-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		ll_attrid.Add(var_data);
	}
	//-------------------------------

	//-------------------------------
	int objid_limit;
	int objack = 0;
	int error_list = 0;
	CString objid_str;
	int t;
	CString attrid_str;
	
	objid_limit = l_objid.GetSize();
	attrid_list = ll_attrid.GetSize();

	if(objid_limit == 0)
	{
		p_e39_ctrl->GetAttr__ObjID(objspec,objtype,l_objid);

		objid_limit = l_objid.GetSize();
	}
	if(attrid_list == 0)
	{
		p_e39_ctrl->GetAttrName(objspec,objtype,ll_attrid);

		attrid_list = ll_attrid.GetSize();
	}

	// OBJID_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,objid_limit);

	for(i=0;i<objid_limit;i++)
	{
		// OBJID ------------------------------------------------------
		objid_str = l_objid[i];

		db_name.Format("-1-1-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,objid_str);

		if(p_e39_ctrl->Is__ObjID(objspec,
								 objtype,
								 objid_str) < 0)
		{
			//---------------------------------------------------------
			db_name.Format("-1-1-%1d-2",i+1);
			p_send_ctrl->Add_List(db_name,0);
			//---------------------------------------------------------
			//---------------------------------------------------------
			int err_code = 0;
			CString err_text = "";

			p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);

			error_list++;

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",error_list);
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",error_list);
			p_send_ctrl->Add_Ascii(db_name,err_text);
			//---------------------------------------------------------

			continue;
		}

		// ATTR_LIST --------------------------------------------------
		db_name.Format("-1-1-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,attrid_list);

		for(t=0;t<attrid_list;t++)
		{
			CDS_ATTR_DATA attr_data;
			int err_code = 0;
			CString err_text = "";

			// ATTRID
			attrid_str = ll_attrid[t];

			db_name.Format("-1-1-%1d-2-%1d-1",i+1,t+1);
			p_send_ctrl->Add_Ascii(db_name,attrid_str);
			
   	 		// ATTRDATA
			db_name.Format("-1-1-%1d-2-%1d-2",i+1,t+1);

			if(attrid_str.CompareNoCase("Process_History") == 0)
			{
				Fnc__MSG_S14F1__Make_Process_History(db_name,objtype,objid_str,p_send_ctrl);
			}
			else if(attrid_str.CompareNoCase("Module_History") == 0)
			{
				Fnc__MSG_S14F1__Make_Module_History(db_name,objtype,objid_str,p_send_ctrl);
			}
			else
			{
				if(p_e39_ctrl->GetAttr(objspec,
									   objtype,
									   objid_str,
									   attrid_str,
									   "",
									   "",
									   attr_data) < 0)
				{
					p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);
				}

				p_send_ctrl->Add_Virtual(db_name,attr_data);
			}

			if(err_code == 0)	continue;
			error_list++;

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",error_list);
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",error_list);
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}
	}

	if(error_list > 0)		objack = 1;

	// OBJACK
	db_name = "-1-2-1";
	p_send_ctrl->Add_U1(db_name,objack);

	// ERROR_LIST
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,error_list);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S14Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E39_CTRL *p_e39_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E39();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CString objtype;
	int objid_list = 0;    
	int i;
	CStringArray l_objid;
	int attr_list = 0;
	CStringArray l_attrid;
	CStringArray l_attrdata;
		
	//-------------------------------
	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// OBJTYPE
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objtype = var_data;

	// OBJID_LIST
	db_name = "-1-3";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objid_list = atoi(var_data);
	for(i=0;i<objid_list;i++)
	{
		// OBJID
		db_name.Format("-1-3-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_objid.Add(var_data);
	}

	// ATTR_LIST
	db_name = "-1-4";
	p_recv_ctrl->Get_Data(db_name,var_data);
	
	attr_list = atoi(var_data);
	
	for(i=0;i<attr_list;i++)
	{
		// ATTRID
		db_name.Format("-1-4-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrid.Add(var_data);

		// ATTRDATA
		db_name.Format("-1-4-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrdata.Add(var_data);
	}
	//-------------------------------

	//-------------------------------
	int objid_limit;
	int objack = 0;
	int error_list = 0;
	CString objid_str;
	int t;
	CString attrid_str;
	CString attrdata_str;
	
	objid_limit = l_objid.GetSize();

	// OBJID_LIMIT
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,objid_limit);

	for(i=0;i<objid_limit;i++)
	{
		// OBJID
		objid_str = l_objid[i];

		db_name.Format("-1-1-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,objid_str);

		// ATTR_LIST
		db_name.Format("-1-1-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,attr_list);

		for(t=0;t<attr_list;t++)
		{
			CString err_text = "No error";

			CDS_ATTR_DATA attr_data;
			int err_code = 0;

			// ATTRID
			attrid_str = l_attrid[t];

			db_name.Format("-1-1-%1d-2-%1d-1",i+1,t+1);
			p_send_ctrl->Add_Ascii(db_name,attrid_str);
			
   	 	 	// ATTRDATA
			if(p_e39_ctrl->SetAttr(objspec,
								   objtype,
								   objid_str,
								   attrid_str,
								   l_attrdata[t]) < 0)
			{
				p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);
			}

			db_name.Format("-1-1-%1d-2-%1d-2",i+1,t+1);
			p_send_ctrl->Add_Ascii(db_name,l_attrdata[t]);


			if(err_code == 0)	continue;
			error_list++;

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",error_list);
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",error_list);
			p_send_ctrl->Add_Ascii(db_name,err_text);
		}
	}

	if(error_list > 0)		objack = 1;

	// OBJACK
	db_name = "-1-2-1";
	p_send_ctrl->Add_U1(db_name,objack);

	// ERROR_LIST
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,error_list);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S14Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E39_CTRL *p_e39_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E39();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
		
	//-------------------------------
	// OBJSPEC
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;
	//-------------------------------

	//-------------------------------
	int objack = 0;
	int error_list = 0;
	CStringArray l_objtype;
	int objtype_limit;
	CString objtype;
	int i;

	if(p_e39_ctrl->GetType(objspec,l_objtype) < 0)
	{
		int     err_code;
		CString err_text;

		p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);
		error_list = 1;

		// ERRCODE
		db_name.Format("-1-2-2-%1d-1",error_list);
		p_send_ctrl->Add_U1(db_name,err_code);

		// ERRTEXT
		db_name.Format("-1-2-2-%1d-2",error_list);
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}

	objtype_limit = l_objtype.GetSize();

	// OBJTYPE LIST
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,objtype_limit);

	for(i=0;i<objtype_limit;i++)
	{
		// OBJTYPE
		objtype = l_objtype[i];

		db_name.Format("-1-1-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,objtype);
	}

	if(error_list > 0)		objack = 1;


	// OBJACK
	db_name = "-1-2-1";
	p_send_ctrl->Add_U1(db_name,objack);

	// ERROR_LIST
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,error_list);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S14Fy::Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E39_CTRL *p_e39_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E39();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CStringArray l_objtype;
	int objtype_limit;
	int i;
		
	//-------------------------------
	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// OBJTYPE LIST
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objtype_limit = atoi(var_data);

	for(i=0;i<objtype_limit;i++)
	{
		// OBJTYPE
		db_name.Format("-1-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_objtype.Add(var_data);
	}
	//-------------------------------

	//-------------------------------
	int objack = 0;
	int error_list = 0;
	CString objtype;
	CStringArray l_attrname;
	int limit_attrname;
	int t;

	objtype_limit = l_objtype.GetSize();

	// OBJTYPE LIST
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,objtype_limit);

	for(i=0;i<objtype_limit;i++)
	{
		objtype = l_objtype[i];
		
		// OBJTYPE
		db_name.Format("-1-1-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,objtype);

		// ATTRID LIST
		db_name.Format("-1-1-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,0);
		
		if(p_e39_ctrl->GetAttrName(objspec,objtype,l_attrname) < 0)
		{
			int     err_code;
			CString err_text;

			p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);

			if(err_code == 0)		continue;
			error_list++;

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",error_list);
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",error_list);
			p_send_ctrl->Add_Ascii(db_name,err_text);
			continue;
		}

		// ATTRID LIST
		limit_attrname = l_attrname.GetSize();
		db_name.Format("-1-1-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,limit_attrname);

		for(t=0;t<limit_attrname;t++)
		{
			// ATTRID
			db_name.Format("-1-1-%1d-2-%1d",i+1,t+1);
			p_send_ctrl->Add_Ascii(db_name,l_attrname[t]);
		}
	}

	if(error_list > 0)		objack = 1;

	// OBJACK
	db_name = "-1-2-1";
	p_send_ctrl->Add_U1(db_name,objack);

	// ERROR_LIST
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,error_list);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S14Fy::Recv__F9_0(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E94_CTRL *p_e94_ctrl
		 = p_bridge_ctrl->pRES_300mm_CTRL->Get_E94();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CString cjobid;
	int pr_order_mgmt;
	int start_method;
	int carrier_limit;
	int pjob_limit;
	int i;

	//-------------------------------
	p_e94_ctrl->Clear_CJob();

	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// CTRLJOBID
	db_name = "-1-3-1-2";
	p_recv_ctrl->Get_Data(db_name,cjobid);

	db_name = "-1-2-1-2";
	p_send_ctrl->Add_Ascii(db_name,cjobid);

	// PROCESSORDERMGMT
	db_name = "-1-3-2-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pr_order_mgmt = atoi(var_data);

	db_name = "-1-2-2-2";
	p_send_ctrl->Add_U1(db_name,pr_order_mgmt);

	p_e94_ctrl->Load_ProcessOrderMgmt(pr_order_mgmt);

	// START_METHOD
	db_name = "-1-3-3-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	var_data.MakeUpper();
	if(var_data == "FF")	start_method = 1;
	else					start_method = atoi(var_data);
	p_e94_ctrl->Load_StartMethod(start_method);

	db_name = "-1-2-3-2";
	if(start_method > 0)	p_send_ctrl->Add_Boolean(db_name,TRUE);
	else					p_send_ctrl->Add_Boolean(db_name,FALSE);

	// CARRIER_LIMIT
	db_name = "-1-3-4-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	carrier_limit = atoi(var_data);

	db_name = "-1-2-4-2";
	p_send_ctrl->Add_List(db_name,carrier_limit);

	for(i=0;i<carrier_limit;i++)
	{
		// CARRIERID
		db_name.Format("-1-3-4-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		
		p_e94_ctrl->Load_CarrierID(var_data);		

		db_name.Format("-1-2-4-2-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,var_data);
	}

	// MtrlOut - SPEC.
	CString    mtrl_lotid;
	CUIntArray mtrl_slot_list;
	int        mtrl_limit;

	// MTRL_LIMIT
	db_name = "-1-3-5-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	mtrl_limit = atoi(var_data);

	db_name = "-1-2-5-2";
	p_send_ctrl->Add_List(db_name,mtrl_limit);

	for(i=0;i<mtrl_limit;i++)
	{
		mtrl_lotid = "";
		mtrl_slot_list.RemoveAll();

		// SOURCE_LOTID
		db_name.Format("-1-3-5-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		mtrl_lotid = var_data;

		db_name.Format("-1-2-5-2-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,mtrl_lotid);

		// SOURCE_SLOT_LIST
		db_name.Format("-1-3-5-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		int slot_list = atoi(var_data);
		int t;
		int slot_no;

		db_name.Format("-1-2-5-2-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,slot_list);
		
		for(t=0;t<slot_list;t++)
		{
			// SOURCE_SLOT
			db_name.Format("-1-3-5-2-%1d-2-%1d",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			slot_no = atoi(var_data);
			mtrl_slot_list.Add(slot_no);

			db_name.Format("-1-2-5-2-%1d-2-%1d",i+1,t+1);
			p_send_ctrl->Add_U1(db_name,slot_no);
		}

		p_e94_ctrl->Load_MtrlOutSpec(mtrl_lotid,mtrl_slot_list);
	}

	// PJ_LIMIT
	db_name = "-1-3-6-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pjob_limit = atoi(var_data);

	db_name = "-1-2-6-2";
	p_send_ctrl->Add_List(db_name,pjob_limit);

	for(i=0;i<pjob_limit;i++)
	{
		// PRJOBID
		db_name.Format("-1-3-6-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		p_e94_ctrl->Load_PJobID(var_data);

		db_name.Format("-1-2-6-2-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,var_data);
	}
	//-------------------------------

	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();
	int remote_flag;

	if(p_e30_ctrl->Is_REMOTE() < 0)		remote_flag = -1;
	else								remote_flag =  1;

	//-------------------------------
	int flag = p_e94_ctrl->Create_CJob(cjobid);

	if((flag < 0)||(remote_flag < 0))
	{
		int err_code;
		CString err_text;

		if(remote_flag < 0)
		{
			err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
			err_text = "Command not valid for current state";
		}
		else
		{
			p_e94_ctrl->Get_CJob_Error(err_code,err_text);
		}

		// OBJSPEC
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,"");

		// ITEM LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,7);

		// ACKA
		db_name = "-1-3-1";
		p_send_ctrl->Add_U1(db_name,1);

		// ERROR_LIMIT
		db_name = "-1-3-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-3-2-1-1";
		p_send_ctrl->Add_U2(db_name,err_code);

		// ERRTEXT
		db_name = "-1-3-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	else
	{
		// OBJSPEC
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,cjobid);

		// ITEM LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);

		// ACKA
		db_name = "-1-3-1";
		p_send_ctrl->Add_U2(db_name,0);

		// ERROR_LIMIT
		db_name = "-1-3-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S14Fy::Recv__F9_1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E94_CTRL *p_e94_ctrl
		 = p_bridge_ctrl->pRES_300mm_CTRL->Get_E94();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CString cjobid;
	int pr_order_mgmt;
	int start_method;
	int carrier_limit;
	int pjob_limit;
	int i;

	//-------------------------------
	p_e94_ctrl->Clear_CJob();

	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// 1. CTRLJOBID
	db_name = "-1-3-1-2";
	p_recv_ctrl->Get_Data(db_name,cjobid);

	db_name = "-1-2-1-2";
	p_send_ctrl->Add_Ascii(db_name,cjobid);

	// 2. PJ_LIMIT
	db_name = "-1-3-2-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pjob_limit = atoi(var_data);

	db_name = "-1-2-2-2";
	p_send_ctrl->Add_List(db_name,pjob_limit);

	for(i=0;i<pjob_limit;i++)
	{
		// PRJOBID
		db_name.Format("-1-3-2-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		p_e94_ctrl->Load_PJobID(var_data);

		db_name.Format("-1-2-2-2-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,var_data);
	}

	// 3. CARRIER_LIMIT
	db_name = "-1-3-3-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	carrier_limit = atoi(var_data);

	db_name = "-1-2-3-2";
	p_send_ctrl->Add_List(db_name,carrier_limit);

	for(i=0;i<carrier_limit;i++)
	{
		// CARRIERID
		db_name.Format("-1-3-3-2-%1d",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);
		
		p_e94_ctrl->Load_CarrierID(var_data);		

		db_name.Format("-1-2-3-2-%1d",i+1);
		p_send_ctrl->Add_Ascii(db_name,var_data);
	}

	// 4. MtrlOut - SPEC
	CString    mtrl_lotid;
	CUIntArray mtrl_slot_list;
	int        mtrl_limit;

	// MTRL_LIMIT
	db_name = "-1-3-4-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	mtrl_limit = atoi(var_data);

	db_name = "-1-2-4-2";
	p_send_ctrl->Add_List(db_name,mtrl_limit);

	for(i=0;i<mtrl_limit;i++)
	{
		mtrl_lotid = "";
		mtrl_slot_list.RemoveAll();

		// SOURCE_LOTID
		db_name.Format("-1-3-4-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		mtrl_lotid = var_data;

		db_name.Format("-1-2-4-2-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,mtrl_lotid);

		// SOURCE_SLOT_LIST
		db_name.Format("-1-3-4-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		int slot_list = atoi(var_data);
		int t;
		int slot_no;

		db_name.Format("-1-2-4-2-%1d-2",i+1);
		p_send_ctrl->Add_List(db_name,slot_list);
		
		for(t=0;t<slot_list;t++)
		{
			// SOURCE_SLOT
			db_name.Format("-1-3-4-2-%1d-2-%1d",i+1,t+1);
			p_recv_ctrl->Get_Data(db_name,var_data);

			slot_no = atoi(var_data);
			mtrl_slot_list.Add(slot_no);

			db_name.Format("-1-2-4-2-%1d-2-%1d",i+1,t+1);
			p_send_ctrl->Add_U1(db_name,slot_no);
		}

		p_e94_ctrl->Load_MtrlOutSpec(mtrl_lotid,mtrl_slot_list);
	}
	
	// 5. PROCESSORDERMGMT
	db_name = "-1-3-5-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	pr_order_mgmt = atoi(var_data);

	db_name = "-1-2-5-2";
	p_send_ctrl->Add_U1(db_name,pr_order_mgmt);

	p_e94_ctrl->Load_ProcessOrderMgmt(pr_order_mgmt);

	// 6. START_METHOD
	db_name = "-1-3-6-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	var_data.MakeUpper();
	if(var_data == "FF")	start_method = 1;
	else					start_method = atoi(var_data);
	p_e94_ctrl->Load_StartMethod(start_method);

	db_name = "-1-2-6-2";
	if(start_method > 0)	p_send_ctrl->Add_Boolean(db_name,TRUE);
	else					p_send_ctrl->Add_Boolean(db_name,FALSE);


	//-------------------------------
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();
	int remote_flag;

	if(p_e30_ctrl->Is_REMOTE() < 0)		remote_flag = -1;
	else								remote_flag =  1;

	//-------------------------------
	int flag = p_e94_ctrl->Create_CJob(cjobid);

	if((flag < 0)||(remote_flag < 0))
	{
		int err_code;
		CString err_text;

		if(remote_flag < 0)
		{
			err_code = ERROR_CODE__COMMAND_NOT_VALID_FOR_CURRENT_STATE;
			err_text = "Command not valid for current state";
		}
		else
		{
			p_e94_ctrl->Get_CJob_Error(err_code,err_text);
		}

		// OBJSPEC
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,"");

		// ITEM LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,6);

		// ACKA
		db_name = "-1-3-1";
		p_send_ctrl->Add_U1(db_name,1);

		// ERROR_LIMIT
		db_name = "-1-3-2";
		p_send_ctrl->Add_List(db_name,1);

		// ERRCODE
		db_name = "-1-3-2-1-1";
		p_send_ctrl->Add_U2(db_name,err_code);

		// ERRTEXT
		db_name = "-1-3-2-1-2";
		p_send_ctrl->Add_Ascii(db_name,err_text);
	}
	else
	{
		// OBJSPEC
		db_name = "-1-1";
		p_send_ctrl->Add_Ascii(db_name,cjobid);

		// ITEM LIST
		db_name = "-1-2";
		p_send_ctrl->Add_List(db_name,0);

		// ACKA
		db_name = "-1-3-1";
		p_send_ctrl->Add_U2(db_name,0);

		// ERROR_LIMIT
		db_name = "-1-3-2";
		p_send_ctrl->Add_List(db_name,0);
	}
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}

void CMsg_S14Fy::Recv__F11(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl
		= p_bridge_ctrl->pMSG_RECV_CTRL;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl
		= p_bridge_ctrl->pMSG_SEND_CTRL;

	CI_FA_300mm__E39_CTRL *p_e39_ctrl
		= p_bridge_ctrl->pRES_300mm_CTRL->Get_E39();

	CString db_name;
	CString var_data;

	//-------------------------------
	CString objspec;
	CStringArray l_attrid;
	CStringArray l_attrdata;
	int attr_limit;
	int i;

	//-------------------------------
	// OBJSPEC
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,var_data);

	objspec = var_data;

	// ATTR LIST
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,var_data);

	attr_limit = atoi(var_data);

	for(i=0;i<attr_limit;i++)
	{
		// ATTRID
		db_name.Format("-1-2-%1d-1",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrid.Add(var_data);

		// ATTRDATA
		db_name.Format("-1-2-%1d-2",i+1);
		p_recv_ctrl->Get_Data(db_name,var_data);

		l_attrdata.Add(var_data);
	}
	//-------------------------------

	//-------------------------------
	int objack = 0;
	int error_list = 0;
	CString attrid;
	CString attrdata;

	// ATTR LIST
	db_name = "-1-1";
	p_send_ctrl->Add_List(db_name,attr_limit);

	for(i=0;i<attr_limit;i++)
	{
		attrid   = l_attrid[i];
		attrdata = l_attrdata[i];

		// ATTRID
		db_name.Format("-1-1-%1d-1",i+1);
		p_send_ctrl->Add_Ascii(db_name,attrid);

		// ATTRDATA
		db_name.Format("-1-1-%1d-2",i+1);
		p_send_ctrl->Add_Ascii(db_name,attrdata);

		
		if(p_e39_ctrl->Delete__Object(objspec,attrid,attrdata) < 0)
		{
			int     err_code;
			CString err_text;

			p_e39_ctrl->Get__ERROR_CODE(err_code,err_text);

			if(err_code == 0)		continue;
			error_list++;

			// ERRCODE
			db_name.Format("-1-2-2-%1d-1",error_list);
			p_send_ctrl->Add_U1(db_name,err_code);

			// ERRTEXT
			db_name.Format("-1-2-2-%1d-2",error_list);
			p_send_ctrl->Add_Ascii(db_name,err_text);
			continue;
		}
	}

	if(error_list > 0)		objack = 1;

	// OBJACK
	db_name = "-1-2-1";
	p_send_ctrl->Add_U1(db_name,objack);

	// ERROR_LIST
	db_name = "-1-2-2";
	p_send_ctrl->Add_List(db_name,error_list);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
