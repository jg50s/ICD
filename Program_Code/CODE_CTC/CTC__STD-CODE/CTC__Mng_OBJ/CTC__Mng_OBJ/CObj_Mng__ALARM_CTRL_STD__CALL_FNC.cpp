#include "StdAfx.h"
#include "CObj_Mng__ALARM_CTRL_STD.h"



// ...
int CObj_Mng__ALARM_CTRL_STD
::Call__CHECK_CURRENT_ALARM(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	SCX__ALARM_CTRL cx_alarm_ctrl;

	int seq_id;
	int alm_type;
	int alm_id;
	CString alm_time;
	CString alm_title;
	CString alm_msg;
	CStringArray l_act;

	int i_size = cx_alarm_ctrl->Is__SIZE();
	int i;

	printf(" * alarm_size <- [%1d] \n", i_size);

	for(i=0; i<i_size; i++)
	{
		int r_data = cx_alarm_ctrl->Get__POSTED_ALARM_INFO(i, seq_id,alm_type,alm_id,alm_time,alm_title,alm_msg,l_act);
		if(r_data < 0)			continue;
	
		CString log_msg;
		CString log_bff;

		log_msg.Format("Index : %1d \n", i);

		log_bff.Format("SeqID : %1d \n", seq_id);
		log_msg += log_bff;

		log_bff.Format("alm_type : %1d \n", alm_type);
		log_msg += log_bff;

		log_bff.Format("alm_id : %1d \n", alm_id);
		log_msg += log_bff;

		log_bff.Format("alm_tile : %s \n", alm_title);
		log_msg += log_bff;

		log_bff.Format("alm_msg:\n%s \n", alm_msg);
		log_msg += log_bff;

		// ...
		log_msg += "l_act ...\n";

		int x_limit = l_act.GetSize();
		int x;

		for(x=0; x<x_limit; x++)
		{
			log_bff.Format("  * %s \n", l_act[x]);
			log_msg += log_bff;
		}

		MessageBox(NULL, log_msg, "Call__CHECK_CURRENT_ALARM() !!!", MB_OK);
	}
	return 1;
}
