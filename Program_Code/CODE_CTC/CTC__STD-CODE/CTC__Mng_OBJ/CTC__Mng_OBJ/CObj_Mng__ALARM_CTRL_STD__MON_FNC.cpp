#include "StdAfx.h"

#include "CObj_Mng__ALARM_CTRL_STD.h"
#include "CObj_Mng__ALARM_CTRL_STD__DEF.h"
#include "Macro_Function.h"


#include "CRes__ALARM_INFO.h"
extern CRes__ALARM_REPORT mRes__ALARM_IREPORT;


//-------------------------------------------------------------------------
void CObj_Mng__ALARM_CTRL_STD::Mon__ALARM_CTRL(CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");
		xSCH_MATERIAL_CTRL->Register__SYSTEM_NAME(sObject_Name);
	}

	// ...
	SCX__ALARM_CTRL cx_alarm_ctrl;

	CString var_data;

	CString ref_toolid;
	CString ref_unitid;
	int i_host_report;
	int i_alarm_level;

	CString str_seq_id;
	CString alarm_type;
	CString alarm_id;
	CString time;
	CString title;
	CString message;
	CStringArray l_option;
	CString act_result;
	
	int count;
	int alarm_flag = -1;
	
	CStringArray l__new_alarm_type;
	CUIntArray   l__new_alarm_seqid;
	CUIntArray   l__new_alarm_id;
	CUIntArray   l__new_alarm_level;

	int alarm_count = 0;
	int cur_day;

	// ...
	{
		xCH__ALARM_FILE_UPLOAD_REQ->Set__DATA(STR__YES);

		var_data = sCH__CUR_DAY->Get__STRING();
		cur_day = atoi(var_data);
	}

	while(1)
	{
		MONITORING_TIMER_RETURN(100);

		// ...
		_Report__ALARM_TO_FA();
		_Change__DAY_REPORT(cur_day);
		_Reload__ALARM_FILE();

		// ...
		alarm_count = cx_alarm_ctrl->Is__SIZE();
		alarm_flag  = 0;

		// ...
		{
			var_data.Format("%1d", alarm_count);
			xCH__POST_ALARM_COUNT->Set__DATA(var_data);
		}

		l__new_alarm_type.RemoveAll();
		l__new_alarm_seqid.RemoveAll();
		l__new_alarm_id.RemoveAll();
		l__new_alarm_level.RemoveAll();

		// ...
		int db_index = 0;

		int r_flag = cx_alarm_ctrl->Get__POST_ALARM_EX(db_index,
													   ref_toolid,
													   ref_unitid,
													   i_host_report,
													   i_alarm_level,
													   &str_seq_id,
													   &alarm_type,
													   &time,  
													   &alarm_id,
													   &title, 
													   &message,
													   &l_option);

		while(r_flag > 0)
		{
			title.Replace('[', '(');
			title.Replace(']', ')');
			// title = Macro__Get_String_Without_KeyChar(title,l_keyword,l_keydata);

			int i_seq_id = Macro__Get_SeqID_From_String(str_seq_id);
			int i_alarm_id = atoi(alarm_id); 

			alarm_flag = 1;
			l__new_alarm_type.Add(alarm_type);
			l__new_alarm_seqid.Add(i_seq_id);
			l__new_alarm_id.Add(i_alarm_id);
			l__new_alarm_level.Add(i_alarm_level);

			// ...
			bool active_check = true;

			if(alarm_type.CompareNoCase(STR__MSG_BOX) == 0)
			{
				active_check = false;
			}

			if(active_check)
			{
				if((i_seq_id >= 0) && (i_seq_id < MODULE_SIZE))
				{
					int i_count;
					CString var_data;

					xCH__1th_SYSTEM_ALARM_COUNT->Get__DATA(var_data);
					i_count = atoi(var_data) + 1;
					var_data.Format("%1d", i_count);
					xCH__1th_SYSTEM_ALARM_COUNT->Set__DATA(var_data);

					xCH__1th_MODULE_ALARM_COUNT[i_seq_id]->Get__DATA(var_data);
					i_count = atoi(var_data) + 1;
					var_data.Format("%1d", i_count);
					xCH__1th_MODULE_ALARM_COUNT[i_seq_id]->Set__DATA(var_data);
				}

				if(!mRes__ALARM_IREPORT.Check__EXT_ID_Of_REPORT_NO(i_seq_id, i_alarm_id))
				{
					mRes__POST_ALARM.Load__INFO(str_seq_id,
												i_alarm_id,
												alarm_type,
												i_alarm_level,
												title);
				}

				cx_alarm_ctrl->ALARM_LOG_DB__Load_POST_EX(i_seq_id,
														  i_alarm_id,
														  i_alarm_level,
														  time,
														  title,
														  message,
														  l_option);

				// ...
				{
					xCH__POST_ALARM_ID->Set__DATA(alarm_id);
					xCH__POST_ALARM_TEXT->Set__DATA(title);
				}
			}

			db_index++;
			r_flag = cx_alarm_ctrl->Get__POST_ALARM_EX(db_index,
													   ref_toolid,
													   ref_unitid,
														  i_host_report,
														  i_alarm_level,
														  &str_seq_id,
														  &alarm_type,
														  &time,  
														  &alarm_id,
														  &title, 
														  &message,
														  &l_option);
		}

		while(cx_alarm_ctrl->Get__CLEAR_ALARM_EX(ref_toolid,
												 ref_unitid,
												 i_host_report,
												 i_alarm_level,
												 &str_seq_id,
												 &alarm_type,
												 &time,  
												 &alarm_id,
												 &title, 
												 &act_result) >= 0)
		{
			title.Replace('[', '(');
			title.Replace(']', ')');
			// title = Macro__Get_String_Without_KeyChar(title,l_keyword,l_keydata);
	
			if(alarm_type.CompareNoCase(STR__MSG_BOX) == 0)
			{
				continue;
			}

			// ...
			int i_seq_id   = Macro__Get_SeqID_From_String(str_seq_id);
			int i_alarm_id = atoi(alarm_id); 

			if(!mRes__ALARM_IREPORT.Check__EXT_ID_Of_REPORT_NO(i_seq_id, i_alarm_id))
			{
				mRes__CLEAR_ALARM.Load__INFO(str_seq_id,
											 i_alarm_id,
											 alarm_type,
											 i_alarm_level,
											 title);
			}

			cx_alarm_ctrl->ALARM_LOG_DB__Load_CLEAR_EX(i_seq_id,
													   i_alarm_id,
													   i_alarm_level,
													   time,
													   title,
													   "",
													   act_result);
		}

		// Module Alarm Flag
		{
			CUIntArray l__eqp_id;			
			int eqp_index;

			cx_alarm_ctrl->Get__ALARM_MODULE_LIST(l__eqp_id);

			int i_limit = l__eqp_id.GetSize();
			int i;

			for(i=0; i<MODULE_SIZE; i++)
			{
				xCH__MODULE_ALARM_FLAG[i]->Set__DATA("");
			}

			for(i=0; i<i_limit; i++)
			{
				eqp_index = (int) l__eqp_id[i];

				if(eqp_index <  0)					continue;
				if(eqp_index >= MODULE_SIZE)		continue;

				xCH__MODULE_ALARM_FLAG[eqp_index]->Set__DATA("YES");
			}
		}

		if(alarm_count > 0)
		{
			xCH__ALARM_FLAG->Set__DATA("YES");

			// ...
			int err_count = 0;

			err_count += cx_alarm_ctrl->Is__HEAVY_ALARM_SIZE();
			err_count += cx_alarm_ctrl->Is__LIGHT_ALARM_SIZE();

			if(xCH__CFG_ALM_WARNING_LIGHT_RED_APPLY_MODE->Check__DATA(STR__ENABLE) > 0)
				err_count += cx_alarm_ctrl->Is__WARNING_ALARM_SIZE();

			if(xCH__CFG_MSG_BOX_BUZZER_MODE->Check__DATA(STR__ENABLE) > 0)
				err_count += 1;

			if(err_count > 0)
			{
				xSCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__ALARM(sObject_Name);

				if(alarm_flag > 0)
					xCH__ALARM_BUZZER->Set__DATA("ON");
			}
			else
			{
				xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__ALARM(sObject_Name);
			}
		}
		else if(alarm_count <= 0)
		{
			xSCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__ALARM(sObject_Name);

			xCH__ALARM_FLAG->Set__DATA("NO");
			xCH__ALARM_BUZZER->Set__DATA("OFF");
		}

		// ...
		{
			CString obj_msg;
			obj_msg.Format("Alarm Count [%1d]", alarm_count);

			xCH__OBJ_MSG->Set__DATA(obj_msg);
		}

		_Update__LAST_ALARM(cx_alarm_ctrl.Get__SCI_PTR());
		_Update__ALARM_LOG(cx_alarm_ctrl.Get__SCI_PTR());
	}	
}

void CObj_Mng__ALARM_CTRL_STD::
_Change__DAY_REPORT(int& cur_day)
{
	CTime cur_time = CTime::GetCurrentTime();

	if(cur_day == cur_time.GetDay())
	{
		return;
	}

	// ...
	CString var_data;

	cur_day = cur_time.GetDay();
	var_data.Format("%1d",cur_day);
	sCH__CUR_DAY->Set__DATA(var_data);

	// 2th -> 3th
	{
		xCH__2th_SYSTEM_ALARM_COUNT->Get__DATA(var_data);
		xCH__3th_SYSTEM_ALARM_COUNT->Set__DATA(var_data);

		for(int i=0; i<MODULE_SIZE; i++)
		{
			xCH__2th_MODULE_ALARM_COUNT[i]->Get__DATA(var_data);
			xCH__3th_MODULE_ALARM_COUNT[i]->Set__DATA(var_data);
		}
	}
	// 1th -> 2th
	{
		xCH__1th_SYSTEM_ALARM_COUNT->Get__DATA(var_data);
		xCH__2th_SYSTEM_ALARM_COUNT->Set__DATA(var_data);

		for(int i=0; i<MODULE_SIZE; i++)
		{
			xCH__1th_MODULE_ALARM_COUNT[i]->Get__DATA(var_data);
			xCH__2th_MODULE_ALARM_COUNT[i]->Set__DATA(var_data);
		}
	}
	// 1th : Init
	{
		xCH__1th_SYSTEM_ALARM_COUNT->Set__DATA("0");

		for(int i=0; i<MODULE_SIZE; i++)
		{
			xCH__1th_MODULE_ALARM_COUNT[i]->Set__DATA("0");
		}
	}
}

void CObj_Mng__ALARM_CTRL_STD::
_Reload__ALARM_FILE()
{
	if(xCH__ALARM_FILE_UPLOAD_REQ->Check__DATA(STR__YES) < 0)
	{
		return;
	}
	xCH__ALARM_FILE_UPLOAD_REQ->Set__DATA("");

	// ...
	{
		printf(" * CObj_Mng__ALARM_CTRL_STD::_Reload__ALARM_FILE() \n");
		printf(" ** [%s] <- [%s] \n",
			   xCH__ALARM_FILE_UPLOAD_REQ->Get__CHANNEL_NAME(),
			   xCH__ALARM_FILE_UPLOAD_REQ->Get__STRING());
	}

	mRes__ALARM_IREPORT.Upload__Report_File();
	// mRes__ALARM_IREPORT.Report__ALL_Of_REPORT_NO();
}

void CObj_Mng__ALARM_CTRL_STD::
_Report__ALARM_TO_FA()
{
	int seq_id;
	int alarm_id;
	int alarm_level;
	CString alarm_type;
	CString alarm_title;

	// ...
	bool active__level_heavy = true;
	bool active__level_light = true;
	bool active__level_warning = true;

	if(dCH__CFG_FA_REPORT_WITH_LEVEL_HEAVY->Check__DATA(STR__ENABLE) < 0)
		active__level_heavy = false;

	if(dCH__CFG_FA_REPORT_WITH_LEVEL_LIGHT->Check__DATA(STR__ENABLE) < 0)
		active__level_light = false;

	if(dCH__CFG_FA_REPORT_WITH_LEVEL_WARNING->Check__DATA(STR__ENABLE) < 0)
		active__level_warning = false;

	// CLEAR ...
	while(mRes__CLEAR_ALARM.Get__INFO(seq_id,
									  alarm_id,
									  alarm_type,
									  alarm_level,
									  alarm_title) > 0)
	{

		if(alarm_type.CompareNoCase(STR__MSG_BOX) == 0)
		{
			continue;
		}

		if(alarm_level == ALARM_LEVEL__LIGHT)
		{
			if(!active__level_light)			continue;
		}
		else if(alarm_level == ALARM_LEVEL__WARNING)
		{
			if(!active__level_warning)			continue;
		}
		else 
		{
			if(!active__level_heavy)			continue;
		}

		// ...
		{
			printf(" * CObj_Mng__ALARM_CTRL_STD::_Report__ALARM_TO_FA() ... \n");
			printf(" ** Alarm - CLEAR !!! \n");
			printf(" ** eqp_id    <- [%1d] \n", seq_id);
			printf(" ** alarm_id  <- [%1d] \n", alarm_id);
			printf(" ** alm_level <- [%s] [%1d]  \n", MACRO__Get_Alarm_Level(alarm_level), alarm_level);
			printf(" ** alm_title <- [%s]  \n", alarm_title);
		}

		xFA_300mm_Link->Send__ALARM_CLEAR_EX(seq_id,alarm_id,alarm_title);
	}

	// POST ...
	while(mRes__POST_ALARM.Get__INFO(seq_id,
									 alarm_id,
									 alarm_type,
									 alarm_level,
									 alarm_title) > 0)		
	{

		if(alarm_type.CompareNoCase(STR__MSG_BOX) == 0)
		{
			continue;
		}

		if(alarm_level == ALARM_LEVEL__LIGHT)
		{
			if(!active__level_light)			continue;
		}
		else if(alarm_level == ALARM_LEVEL__WARNING)
		{
			if(!active__level_warning)			continue;
		}
		else 
		{
			if(!active__level_heavy)			continue;
		}

		// ...
		{
			printf(" * CObj_Mng__ALARM_CTRL_STD::_Report__ALARM_TO_FA() ... \n");
			printf(" ** Alarm - POST !!! \n");
			printf(" ** eqp_id    <- [%1d] \n", seq_id);
			printf(" ** alarm_id  <- [%1d] \n", alarm_id);
			printf(" ** alm_level <- [%s] [%1d]  \n", MACRO__Get_Alarm_Level(alarm_level), alarm_level);
			printf(" ** alm_title <- [%s]  \n", alarm_title);
		}

		xFA_300mm_Link->Send__ALARM_POST_EX(seq_id,alarm_id,alarm_title);
	}
}

void CObj_Mng__ALARM_CTRL_STD::
_Update__LAST_ALARM(SCI__ALARM_CTRL* p_alarm_ctrl)
{
	int flag = -1;

	int count = p_alarm_ctrl->Is__SIZE();
	if(count > 0)
	{
		int eqp_id;
		int alarm_type;
		int alarm_id;
		CString time;
		CString title;
		CString message;
		CStringArray l_act;

		flag = p_alarm_ctrl->Get__LAST_POSTED_ALARM_INFO(eqp_id,
														 alarm_type,
														 alarm_id,
														 time,
														 title,
														 message,
														 l_act);

		if(flag > 0)
		{
			CString str_time = time;

			if(str_time.GetLength() >= 4)		str_time.Insert( 4,'.');	// year
			if(str_time.GetLength() >= 7)		str_time.Insert( 7,'.');	// month
			if(str_time.GetLength() >= 10)		str_time.Insert(10,' ');	// date
			if(str_time.GetLength() >= 13)		str_time.Insert(13,':');	// hour
			if(str_time.GetLength() >= 16)		str_time.Insert(16,':');	// minute
			if(str_time.GetLength() >= 19)		str_time.Insert(19,'.');	// sec

			CString str_data;
			str_data.Format("[EQP%1d][%1d][%s][%s]", eqp_id,alarm_id,str_time,title);

			xCH__LAST_ALARM_MSG->Set__DATA(str_data);
		}
	}

	if((count < 1) || (flag < 0))
	{
		xCH__LAST_ALARM_MSG->Set__DATA("");
	}
}

void CObj_Mng__ALARM_CTRL_STD::
_Update__ALARM_LOG(SCI__ALARM_CTRL* p_alarm_ctrl)
{
	if(xCH__CFG_ALARM_POSTED_DB_CHECK->Check__DATA(STR__ENABLE) < 0)
	{
		return;
	}

	// ...
	CUIntArray l_ext_id;
	p_alarm_ctrl->Get__Posted_All_Alarm(l_ext_id);

	int i_limit = l_ext_id.GetSize();
	int i;

	printf(" * All Alarm ... [%1d] \n", i_limit);

	for(i=0; i<i_limit; i++)
	{
		int ext_id = l_ext_id[i];

		int eqp_id;
		CString obj_name;
		int internal_id;
		CString alm_level;
		CString alm_title;

		if(p_alarm_ctrl->Get__Posted_Alarm_Level(ext_id, eqp_id,obj_name,internal_id, alm_level, alm_title) < 0)
		{
			continue;
		}

		printf(" * %1d)  [%1d] [Eqp:%1d] [Obj:%s] [%1d] [%s] [%s] \n", 
				i+1,
				ext_id,
				eqp_id,
				obj_name,
				internal_id,
				alm_level,
				alm_title);
	}
	printf("\n");
}
