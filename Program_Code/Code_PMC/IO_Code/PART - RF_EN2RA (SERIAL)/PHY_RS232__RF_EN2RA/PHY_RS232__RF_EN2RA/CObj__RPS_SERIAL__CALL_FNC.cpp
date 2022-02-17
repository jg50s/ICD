#include "StdAfx.h"
#include "CObj__RPS_SERIAL.h"

#include "CCommon_Utility.h"


// ...
int CObj__RPS_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__RPS_SERIAL
::Call__CTRL_MODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_remote)
{
	if(active_remote)		return 1;

	return -1;
}

int  CObj__RPS_SERIAL
::Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_set)
{
	CString ch_data;
	int	flag;

	if(active_set)
	{
		aCH__PARA_SET_POWER->Get__DATA(ch_data);
		aoCH__DIGITAL_POWER_SET->Set__DATA(ch_data);

		flag = doCH__DIGITAL_POWER_CTRL->Set__DATA(STR__ON);

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg = "\n";

			aCH__PARA_SET_POWER->Get__DATA(ch_data);
			log_bff.Format(" * %s <- %s \n",
				           aCH__PARA_SET_POWER->Get__VARIABLE_NAME(),
						   ch_data);
			log_msg += log_bff;

			aoCH__DIGITAL_POWER_SET->Get__DATA(ch_data);
			log_bff.Format(" * %s <- %s \n",
							aoCH__DIGITAL_POWER_SET->Get__VARIABLE_NAME(),
							ch_data);
			log_msg += log_bff;

			ch_data = doCH__DIGITAL_POWER_CTRL->Get__STRING();
			log_bff.Format(" * %s <- %s \n",
							doCH__DIGITAL_POWER_CTRL->Get__VARIABLE_NAME(),
							ch_data);
			log_msg += log_bff;

			Write__APP_LOG(log_msg);
		}
	}
	else
	{
		flag = doCH__DIGITAL_POWER_CTRL->Set__DATA(STR__OFF);

		aoCH__DIGITAL_POWER_SET->Set__DATA("0");
	}
	return flag;
}

int CObj__RPS_SERIAL
::Call__DRV_TEST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString s_cmmd = "CMD";
	CString s_op   = "";
	CString s_data = "";
	CString r_data;

	int r_len = _Send__Command(s_cmmd,s_op,s_data, &r_data);

	printf(" * r_len <- [%1d] \n", r_len);

	// ...
	{
		CCommon_Utility x_utility;
		CStringArray l_para;

		x_utility.Get__StringArrray_From_String(r_data, ",", l_para);

		int k_limit = l_para.GetSize();
		int k;

		printf(" * para_list <- %1d \n", k_limit);

		for(k=0; k<k_limit; k++)
		{
			printf(" * %1d) [%s] \n", k+1,l_para[k]);
		}
		printf("\n");
	}

	_Update__CMD_INFO(r_data);
	return 1;
}
