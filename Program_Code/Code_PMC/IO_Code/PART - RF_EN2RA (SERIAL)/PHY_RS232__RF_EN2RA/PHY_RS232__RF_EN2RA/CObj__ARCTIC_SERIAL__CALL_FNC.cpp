#include "StdAfx.h"
#include "CObj__ARCTIC_SERIAL.h"

#include "CCommon_Utility.h"


// ...
int CObj__ARCTIC_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__ARCTIC_SERIAL
::Call__CTRL_MODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_remote)
{
	if(active_remote)		return 1;

	return -1;
}

int  CObj__ARCTIC_SERIAL
::Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_set)
{
	CString ch_data;
	int	flag;

	if(active_set)
	{
		aCH__PARA_SET_POWER->Get__DATA(ch_data);
		aoCH__DIGITAL_POWER_SET->Set__DATA(ch_data);

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

			Write__APP_LOG(log_msg);
		}
	}
	else
	{
		doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH->Set__DATA(STR__OFF);
		doCH__PLASMA_ON_ENABLE_TURN_ON->Set__DATA(STR__OFF);

		//flag = doCH__DIGITAL_INITIAL_CTRL->Set__DATA(STR__OFF);
		flag = doCH__DIGITAL_POWER_CTRL->Set__DATA(STR__OFF);

		aCH__PARA_SET_POWER->Set__DATA("0");
		aoCH__DIGITAL_POWER_SET->Set__DATA("0");
	}
	return flag;
}

int  CObj__ARCTIC_SERIAL
::Call__POWER_ON(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;
	int	flag;

	flag = doCH__DIGITAL_POWER_CTRL->Set__DATA(STR__ON);

	if(flag > 0)
		flag = doCH__PLASMA_ON_ENABLE_TURN_ON->Set__DATA(STR__ON);

	if(flag > 0)
		flag = doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH->Set__DATA(STR__ON);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "\n";

		ch_data = doCH__DIGITAL_POWER_CTRL->Get__STRING();
		log_bff.Format(" * %s <- %s \n",
						doCH__DIGITAL_POWER_CTRL->Get__VARIABLE_NAME(),
						ch_data);
		log_msg += log_bff;

		ch_data = doCH__PLASMA_ON_ENABLE_TURN_ON->Get__STRING();
		log_bff.Format(" * %s <- %s \n",
						doCH__PLASMA_ON_ENABLE_TURN_ON->Get__VARIABLE_NAME(),
						ch_data);
		log_msg += log_bff;

		ch_data = doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH->Get__STRING();
		log_bff.Format(" * %s <- %s \n",
					   doCH__PLASMA_ON_ENABLE_OUTPUT_HIGH->Get__VARIABLE_NAME(),
					   ch_data);
		log_msg += log_bff;

		Write__APP_LOG(log_msg);
	}
	return flag;
}
