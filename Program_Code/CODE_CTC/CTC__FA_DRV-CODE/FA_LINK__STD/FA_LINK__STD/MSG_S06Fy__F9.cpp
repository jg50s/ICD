#include "StdAFx.h"
#include "Interface_Code.h"

#include "MSG_S06Fy.h"


void CMsg_S06Fy
::Make__F9__LPx_MHP_REPORT(CI_BRIDGE__INFO_CTRL *p_bridge_ctrl,
						   const int ceid,
						   const int lp_id)
{
	CI_BRIDGE__MSG_SEND_CTRL *p_send_ctrl = p_bridge_ctrl->pMSG_SEND_CTRL;
	CI_FA_VARIABLE_CTRL      *p_var_ctrl  = p_bridge_ctrl->pRES_VARIABLE_CTRL;
	CI_FA_300mm__E30_CTRL    *p_e30_ctrl  = p_bridge_ctrl->pRES_300mm_CTRL->Get_E30();

	CString str__portid;
	CString str__slotid;
	CString str__cjobid;
	CString str__pjobid;
	CString str__lotid;
	CString str__cstid;

	CString var_data;

	//
	str__portid.Format("%1d",lp_id);

	//
	p_e30_ctrl->Get__MPH_INFO(str__slotid,
							  str__cjobid,
							  str__pjobid,
							  str__lotid,
							  str__cstid);

	// ...
	CString db_name;

	// 1.<L,  3
	db_name = "-1";
	p_send_ctrl->Add_List(db_name,3);

	//		  1.<U4[1]  $DATAID
	db_name = "-1-1";
	p_send_ctrl->Add_Ascii(db_name,"1");

	//		  2.<U4[1]  $CEID
	db_name = "-1-2";
	p_send_ctrl->Add_U4(db_name,ceid);

	//		  3.<L,  7 
	db_name = "-1-3";
	p_send_ctrl->Add_List(db_name,7);

	//				 1.<U4[1]  $PORTID
	db_name = "-1-3-1";
	p_send_ctrl->Add_Ascii(db_name,str__portid);

	//				 2.<U4[1]  $SLOTID
	db_name = "-1-3-2";
	p_send_ctrl->Add_Ascii(db_name,str__slotid);

	//				 3.<A[16]  $CJOBID
	db_name = "-1-3-3";
	p_send_ctrl->Add_Ascii(db_name,str__cjobid);

	//				 4.<A[16]  $PJOBID
	db_name = "-1-3-4";
	p_send_ctrl->Add_Ascii(db_name,str__pjobid);

	//				 5.<A[16]  $LOTID
	db_name = "-1-3-5";
	p_send_ctrl->Add_Ascii(db_name,str__lotid);

	//				 6.<A[16]  $CSTID
	db_name = "-1-3-6";
	p_send_ctrl->Add_Ascii(db_name,str__cstid);

	// ...
	SCX__CTC__SCH_MATERIAL_CTRL x_sch_ctrl;
	x_sch_ctrl->Link__SERVICE_DB("");

	CStringArray l_module_name;
	CStringArray l_start_time;
	CStringArray l_end_time;
	CStringArray l_delay_time;

	int port_id = atoi(str__portid);
	int slot_id = atoi(str__slotid);

	x_sch_ctrl->MATERIAL_INFO__Get_MOVE_INFO_EX(port_id,
												slot_id,
												l_module_name,
												l_start_time,
												l_end_time,
												l_delay_time);

	int n_limit = l_module_name.GetSize();
	int nn;
	int n_count;

	//				 7.<L,  n
	db_name = "-1-3-7";
	p_send_ctrl->Add_List(db_name,n_limit);

	for(nn=0;nn<n_limit;nn++)
	{
		n_count = nn + 1;

		//  1.<L,  5
		db_name.Format("-1-3-7-%1d",n_count);
		p_send_ctrl->Add_List(db_name,5);

		// 1. Module Name
		db_name.Format("-1-3-7-%1d-1",n_count);
		p_send_ctrl->Add_Ascii(db_name,l_module_name[nn]);

		// 2. Start Time
		db_name.Format("-1-3-7-%1d-2",n_count);
		p_send_ctrl->Add_Ascii(db_name,l_start_time[nn]);

		// 3. End Time
		db_name.Format("-1-3-7-%1d-3",n_count);
		p_send_ctrl->Add_Ascii(db_name,l_end_time[nn]);

		// 4. Delay Time
		db_name.Format("-1-3-7-%1d-4",n_count);
		p_send_ctrl->Add_Ascii(db_name,l_delay_time[nn]);

		// ...
		{
			CString act_name;
			CString act_start_time;
			CString act_end_time;

			CStringArray l_act_name;
			CStringArray l_act_start_time;
			CStringArray l_act_end_time;

			x_sch_ctrl->MATERIAL_INFO__Get_ACT_INFO(port_id,
													slot_id,
													nn,
													l_act_name,
													l_act_start_time,
													l_act_end_time);

			// ...
			int t_limit = l_act_name.GetSize();
			int tt;

			// Lm
			db_name.Format("-1-3-7-%1d-5",n_count);
			p_send_ctrl->Add_List(db_name,t_limit);

			for(tt=0;tt<t_limit;tt++)
			{
				act_name       = l_act_name[tt];
				act_start_time = l_act_start_time[tt];
				act_end_time   = l_act_end_time[tt];

				// L3
				db_name.Format("-1-3-7-%1d-5-%1d",n_count,tt+1);
				p_send_ctrl->Add_List(db_name,3);

				// Act Name
				db_name.Format("-1-3-7-%1d-5-%1d-1",n_count,tt+1);
				p_send_ctrl->Add_Ascii(db_name,act_name);

				// Act Start Time
				db_name.Format("-1-3-7-%1d-5-%1d-2",n_count,tt+1);
				p_send_ctrl->Add_Ascii(db_name,act_start_time);

				// Act End Time
				db_name.Format("-1-3-7-%1d-5-%1d-3",n_count,tt+1);
				p_send_ctrl->Add_Ascii(db_name,act_end_time);
			}
		}
	}
}
