#include "StdAfx.h"
#include "MSG_S14Fy.h"


//----------------------------------------------------------------------------
void CMsg_S14Fy::
Fnc__MSG_S14F1__Make_Process_History(const CString& node_mode,
									 const CString& objtype,
									 const CString& objid,
									 CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl)
{
	//.....
	SCX__CTC__SCH_MATERIAL_CTRL x_sch_ctrl;
	x_sch_ctrl->Link__SERVICE_DB("");

	//.....
	CStringArray l_portid;
	CStringArray l_slotid;

	if(objtype.CompareNoCase("CarrierID") == 0)
	{
		x_sch_ctrl->CARRIERID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}
	else if(objtype.CompareNoCase("LotID") == 0)
	{
		x_sch_ctrl->LOTID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}
	else if(objtype.CompareNoCase("JobID") == 0)
	{
		x_sch_ctrl->JOBID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}

	//.....
	CString db_name;
	int list_count;
	CString var_data;

	int port_id;
	int slot_id;
	CStringArray l_proc_module_name;
	CStringArray l_proc_recipe_name;
	CStringArray l_proc_start_time;
	CStringArray l_proc_end_time;

	int limit = l_portid.GetSize();
	int i;

	p_send_ctrl->Add_List(node_mode,limit);

	for(i=0;i<limit;i++)
	{
		port_id = atoi(l_portid[i]);
		slot_id = atoi(l_slotid[i]);

		x_sch_ctrl->MATERIAL_INFO__Get_PROC_INFO(port_id,
			slot_id,
			l_proc_module_name,
			l_proc_recipe_name,
			l_proc_start_time,
			l_proc_end_time);

		//.....
		list_count = i + 1;

		// L3
		db_name.Format("%s-%1d",node_mode,list_count);
		p_send_ctrl->Add_List(db_name,3);

		// PORT ID
		db_name.Format("%s-%1d-1",node_mode,list_count);
		p_send_ctrl->Add_U1(db_name,port_id);

		// SLOT ID
		db_name.Format("%s-%1d-2",node_mode,list_count);
		p_send_ctrl->Add_U1(db_name,slot_id);

		// Ln : Process Info
		CString proc_module_name;
		CString proc_recipe_name;
		CString proc_start_time;
		CString proc_end_time;

		int kk_limit = l_proc_module_name.GetSize();
		int kk;

		db_name.Format("%s-%1d-3",node_mode,list_count);
		p_send_ctrl->Add_List(db_name,kk_limit);

		for(kk=0;kk<kk_limit;kk++)
		{
			proc_module_name = l_proc_module_name[kk];
			proc_recipe_name = l_proc_recipe_name[kk];
			proc_start_time  = l_proc_start_time[kk];
			proc_end_time    = l_proc_end_time[kk];

			// L4
			db_name.Format("%s-%1d-3-%1d",node_mode,list_count,kk+1);
			p_send_ctrl->Add_List(db_name,4);

			// Proc Module Name
			db_name.Format("%s-%1d-3-%1d-1",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,proc_module_name);

			// Proc Recipe Name
			db_name.Format("%s-%1d-3-%1d-2",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,proc_recipe_name);

			// Proc Start Time
			db_name.Format("%s-%1d-3-%1d-3",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,proc_start_time);

			// Proc End Time
			db_name.Format("%s-%1d-3-%1d-4",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,proc_end_time);
		}
	}
}

void CMsg_S14Fy::
Fnc__MSG_S14F1__Make_Module_History(const CString& node_mode,
									const CString& objtype,
									const CString& objid,
									CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl)
{
	//.....
	SCX__CTC__SCH_MATERIAL_CTRL x_sch_ctrl;
	x_sch_ctrl->Link__SERVICE_DB("");

	//.....
	CStringArray l_portid;
	CStringArray l_slotid;

	if(objtype.CompareNoCase("CarrierID") == 0)
	{
		x_sch_ctrl->CARRIERID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}
	else if(objtype.CompareNoCase("LotID") == 0)
	{
		x_sch_ctrl->LOTID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}
	else if(objtype.CompareNoCase("JobID") == 0)
	{
		x_sch_ctrl->JOBID__Get_ALL_MATERIAL(objid,l_portid,l_slotid);
	}

	//.....
	CString db_name;
	int list_count;
	CString var_data;

	int port_id;
	int slot_id;
	CStringArray l_module_name;
	CStringArray l_start_time;
	CStringArray l_end_time;
	CStringArray l_delay_time;

	int limit = l_portid.GetSize();
	int i;

	p_send_ctrl->Add_List(node_mode,limit);

	for(i=0;i<limit;i++)
	{
		port_id = atoi(l_portid[i]);
		slot_id = atoi(l_slotid[i]);

		x_sch_ctrl->MATERIAL_INFO__Get_MOVE_INFO_EX(port_id,
			slot_id,
			l_module_name,
			l_start_time,
			l_end_time,
			l_delay_time);

		//.....
		list_count = i + 1;

		// L3
		db_name.Format("%s-%1d",node_mode,list_count);
		p_send_ctrl->Add_List(db_name,3);

		// PORT ID
		db_name.Format("%s-%1d-1",node_mode,list_count);
		p_send_ctrl->Add_U1(db_name,port_id);

		// SLOT ID
		db_name.Format("%s-%1d-2",node_mode,list_count);
		p_send_ctrl->Add_U1(db_name,slot_id);

		// Ln : Module Info
		CString module_name;
		CString start_time;
		CString end_time;
		CString delay_time;

		int kk_limit = l_module_name.GetSize();
		int kk;

		db_name.Format("%s-%1d-3",node_mode,list_count);
		p_send_ctrl->Add_List(db_name,kk_limit);

		for(kk=0;kk<kk_limit;kk++)
		{
			module_name = l_module_name[kk];
			start_time  = l_start_time[kk];
			end_time    = l_end_time[kk];
			delay_time  = l_delay_time[kk];

			// L5
			db_name.Format("%s-%1d-3-%1d",node_mode,list_count,kk+1);
			p_send_ctrl->Add_List(db_name,5);

			// Module Name
			db_name.Format("%s-%1d-3-%1d-1",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,module_name);

			// Start Time
			db_name.Format("%s-%1d-3-%1d-2",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,start_time);

			// End Time
			db_name.Format("%s-%1d-3-%1d-3",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,end_time);

			// Delay Time
			db_name.Format("%s-%1d-3-%1d-4",node_mode,list_count,kk+1);
			p_send_ctrl->Add_Ascii(db_name,delay_time);

			//.....
			{
				CString act_name;
				CString act_start_time;
				CString act_end_time;

				CStringArray l_act_name;
				CStringArray l_act_start_time;
				CStringArray l_act_end_time;

				x_sch_ctrl->MATERIAL_INFO__Get_ACT_INFO(port_id,
					slot_id,
					kk,
					l_act_name,
					l_act_start_time,
					l_act_end_time);

				//.....
				int t_limit = l_act_name.GetSize();
				int tt;

				// Lm
				db_name.Format("%s-%1d-3-%1d-5",node_mode,list_count,kk+1);
				p_send_ctrl->Add_List(db_name,t_limit);

				for(tt=0;tt<t_limit;tt++)
				{
					act_name       = l_act_name[tt];
					act_start_time = l_act_start_time[tt];
					act_end_time   = l_act_end_time[tt];

					// L3
					db_name.Format("%s-%1d-3-%1d-5-%1d",node_mode,list_count,kk+1,tt+1);
					p_send_ctrl->Add_List(db_name,3);

					// Act Name
					db_name.Format("%s-%1d-3-%1d-5-%1d-1",node_mode,list_count,kk+1,tt+1);
					p_send_ctrl->Add_Ascii(db_name,act_name);

					// Act Start Time
					db_name.Format("%s-%1d-3-%1d-5-%1d-2",node_mode,list_count,kk+1,tt+1);
					p_send_ctrl->Add_Ascii(db_name,act_start_time);

					// Act End Time
					db_name.Format("%s-%1d-3-%1d-5-%1d-3",node_mode,list_count,kk+1,tt+1);
					p_send_ctrl->Add_Ascii(db_name,act_end_time);
				}
			}
		}
	}
}
