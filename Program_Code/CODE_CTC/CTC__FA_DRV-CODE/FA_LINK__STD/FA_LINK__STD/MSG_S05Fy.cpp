#include "StdAFx.h"
#include "MSG_S05Fy.h"


CMsg_S05Fy mMSG_S05Fy;


//----------------------------------------------------------------------------
CMsg_S05Fy::CMsg_S05Fy()
{
	iSx = 5;
}

void CMsg_S05Fy::Send_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 1:		Send__F1(p_bridge_ctrl);		return;
	}
}

void CMsg_S05Fy::Recv_Msg(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	if(p_bridge_ctrl->iSx != iSx)					return;

	switch(p_bridge_ctrl->iFy)
	{
		case 3:		Recv__F3(p_bridge_ctrl);		return;
		case 5:		Recv__F5(p_bridge_ctrl);		return;
		case 7:		Recv__F7(p_bridge_ctrl);		return;
	}
}


//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
void CMsg_S05Fy::Send__F1(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	CI_FA_VARIABLE_CTRL   *p_variable_ctrl = p_bridge_ctrl->pRES_VARIABLE_CTRL;
	CI_FA_DB__ALARM_CTRL  *p_alarm_ctrl    = p_bridge_ctrl->pRES_DB_CTRL->Get_ALARM_CTRL();
	CI_FA_300mm__E30_CTRL *p_e30_ctrl      = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString	main_name;
	CString	sub_name;
	CString data;

	CString al_mode;
	CString al_module;
	int al_id;
	//--------------------------------------------	

	//--------------------------------------------
	main_name = "##S5F1";

	// ALARM_MODE
	sub_name = "ALARM_MODE";
	p_variable_ctrl->Get_Variable(main_name,sub_name,data);

	al_mode = data;

	// ALARM_MODULE
	sub_name = "ALARM_MODULE";
	p_variable_ctrl->Get_Variable(main_name,sub_name,data);

	al_module = data;

	// ALID
	sub_name = "ALID";
	p_variable_ctrl->Get_Variable(main_name,sub_name,data);

	al_id = atoi(data);
	//--------------------------------------------

	//--------------------------------------------
	int module_index;
	int id_offset = p_alarm_ctrl->Is_ID_OFFSET(al_module,module_index);
	if(id_offset < 0)		FA__ERROR;

	al_id += id_offset;
	//--------------------------------------------

	//--------------------------------------------
	int al_cd;
	int	alcd;
	CString al_tx;
	int al_sts;

	if(p_alarm_ctrl->Get_INFO(al_id,alcd,al_tx,al_sts) < 0)
	{
		if(p_e30_ctrl->Check__REPORT_ALL_ALARM() > 0)
		{
			// TITLE
			sub_name = "TITLE";
			p_variable_ctrl->Get_Variable(main_name,sub_name,al_tx);

			alcd = 0x05;
			al_sts = 1;
		}
		else
		{
			FA__ERROR;
		}
	}

	if(al_sts < 0)
	{
		FA__ERROR;
	}

	al_cd = 0x07f & alcd;

	if(al_mode.Compare("POST")  == 0)		al_cd += 0x80;
	else if(al_mode.Compare("CLEAR") != 0)		FA__ERROR;

	//.....
	{
		CString var_data;
		var_data.Format("%002X",al_cd);	

		p_e30_ctrl->Set__ALARM_CODE(var_data);
	}
	//--------------------------------------------

	//--------------------------------------------
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CString db_name;

	// ALCD
	db_name = "-1-1";
	p_send_ctrl->Add_Binary(db_name,al_cd);

	// ALID
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,al_id);

	// ALTX
	db_name = "-1-3";
	p_send_ctrl->Add_Ascii(db_name,al_tx);

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	//--------------------------------------------
	if(p_bridge_ctrl->iReply < 0)						FA__OK;
	if(p_bridge_ctrl->pFA_DRV_CTRL->Is_Recv() < 0)		FA__ERROR;

	//--------------------------------------------

	FA__OK;
}

//----------------------------------------------------------------------------
void CMsg_S05Fy::Recv__F3(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	//-------------------------------
	CString		 db_name;
	int			 fmt_type;
	CString		 data;
	CStringArray data_list;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_DB__ALARM_CTRL *p_alarm_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_ALARM_CTRL();

	CString aled;
	int status;
	int id;
	int limit;
	int i;

	int ackc5 = 0;

	//-------------------------------
	// ALED
	db_name = "-1-1";
	p_recv_ctrl->Get_Data(db_name,aled);

	// ALID
	db_name = "-1-2";
	p_recv_ctrl->Get_Data(db_name,fmt_type,data,data_list);

	if(atoi(aled) == 0)		status = -1;
	else					status =  1;

	limit = data_list.GetSize();

	if(limit < 1)
	{
		p_alarm_ctrl->SetALL(status);
	}
	else
	{
		for(i=0;i<limit;i++)
		{
			id = atoi(data_list[i]);

			if(p_alarm_ctrl->Set(id,status) < 0)
			{
				ackc5 = 1;
				break;
			}
		}
	}

	p_alarm_ctrl->Save();
	//--------------------------------------------

	//--------------------------------------------
	// ACKC5
	db_name = "-1";
	p_send_ctrl->Add_Binary(db_name,ackc5);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S05Fy::Recv__F5(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	//-------------------------------
	CString		 pp_name;
	CString		 db_name;
	int          fmt_type;
	CString		 data;
	CStringArray data_list;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_DB__ALARM_CTRL *p_alarm_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_ALARM_CTRL();

	int i;
	int limit;
	//-------------------------------

	//-------------------------------
	// ALID
	db_name = "-1";
	p_recv_ctrl->Get_Data(db_name,fmt_type,data,data_list);

	p_alarm_ctrl->Init_BFF();

	limit = data_list.GetSize();
	for(i=0;i<limit;i++)
	{
		p_alarm_ctrl->Load_BFF(atoi(data_list[i]));
	}
	//-------------------------------

	//-------------------------------
	int id;
	int cd;
	CString altx;
	int count = 0;

	if(limit > 0)
	{
		while(p_alarm_ctrl->Upload_BFF(id,cd,altx) > 0)
		{
			count++;
			pp_name.Format("-1-%1d",count);

			db_name  = pp_name;
			db_name += "-1";
			p_send_ctrl->Add_Binary(db_name,cd);

			db_name  = pp_name;
			db_name += "-2";
			p_send_ctrl->Add_U4(db_name,id);

			db_name  = pp_name;
			db_name += "-3";
			p_send_ctrl->Add_Ascii(db_name,altx);
		}
	}
	else if(limit == 0)
	{
		p_alarm_ctrl->Init_LIST();

		while(p_alarm_ctrl->Upload_LIST(id,cd,altx) > 0)
		{
			count++;
			pp_name.Format("-1-%1d",count);

			db_name  = pp_name;
			db_name += "-1";
			p_send_ctrl->Add_Binary(db_name,cd);

			db_name  = pp_name;
			db_name += "-2";
			p_send_ctrl->Add_U4(db_name,id);

			db_name  = pp_name;
			db_name += "-3";
			p_send_ctrl->Add_Ascii(db_name,altx);
		}
	}

	db_name = "-1";
	p_send_ctrl->Add_List(db_name,count);
	//-------------------------------


	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
void CMsg_S05Fy::Recv__F7(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl)
{
	//--------------------------------------------
	//-------------------------------
	CString		 pp_name;
	CString		 db_name;
	CStringArray data_list;

	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_BRIDGE__MSG_RECV_CTRL *p_recv_ctrl = p_bridge_ctrl->pMSG_RECV_CTRL;
	CI_FA_DB__ALARM_CTRL *p_alarm_ctrl = p_bridge_ctrl->pRES_DB_CTRL->Get_ALARM_CTRL();

	int id;
	int	cd;
	CString altx;
	CString data;
	int count = 0;
	//-------------------------------

	//-------------------------------
	p_alarm_ctrl->Init_LIST();

	while(p_alarm_ctrl->Upload_LIST(id,cd,altx) > 0)
	{
		count++;
		pp_name.Format("-1-%1d",count);

		// ALCD
		db_name  = pp_name;
		db_name += "-1";
		p_send_ctrl->Add_Binary(db_name,cd);

		// ALID
		db_name  = pp_name;
		db_name += "-2";
		p_send_ctrl->Add_U4(db_name,id);

		// ALTX
		db_name  = pp_name;
		db_name += "-3";
		p_send_ctrl->Add_Ascii(db_name,altx);
	}

	db_name = "-1";
	p_send_ctrl->Add_List(db_name,count);
	data.Format("%1d",count);
	//-------------------------------

	p_bridge_ctrl->pFA_DRV_CTRL->Send();
	//--------------------------------------------

	FA__OK;
}
