#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"


// ...
int CObj__NXA_PULSE
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__NXA_PULSE
::Call__CLK_A_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "CLK.A Info ... \n";

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_A_FREQ->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_A_FREQ->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_A_DUTY->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_A_DUTY->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_A_ON_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_A_ON_TIME->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_A_OFF_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_A_OFF_TIME->Get__VALUE());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);		
	}

	doCH__PARAM_A1->Set__DATA(STR__ON);
	doCH__PARAM_A2->Set__DATA(STR__ON);
	return 1;
}
int  CObj__NXA_PULSE
::Call__CLK_B_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "CLK.B Info ... \n";

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_B_ON_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_B_ON_SHIFT_TIME->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_B_OFF_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_B_OFF_SHIFT_TIME->Get__VALUE());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);		
	}

	doCH__PARAM_B->Set__DATA(STR__ON);
	return 1;
}
int  CObj__NXA_PULSE
::Call__CLK_C_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "CLK.C Info ... \n";

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_C_ON_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_C_ON_SHIFT_TIME->Get__VALUE());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %.2f \n", 
						aCH__PARA_PARAM_C_OFF_SHIFT_TIME->Get__CHANNEL_NAME(),
						aCH__PARA_PARAM_C_OFF_SHIFT_TIME->Get__VALUE());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);		
	}

	doCH__PARAM_C->Set__DATA(STR__ON);
	return 1;
}

int  CObj__NXA_PULSE
::Call__CLK_EXEC_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__clk_on)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "CLK.EXE Info ... \n";

		log_bff.Format(" * %s <- %s \n", 
						dCH__PARA_CLK_A_CTRL->Get__CHANNEL_NAME(),
						dCH__PARA_CLK_A_CTRL->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__PARA_CLK_B_CTRL->Get__CHANNEL_NAME(),
						dCH__PARA_CLK_B_CTRL->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__PARA_CLK_C_CTRL->Get__CHANNEL_NAME(),
						dCH__PARA_CLK_C_CTRL->Get__STRING());
		log_msg += log_bff;

		Write__APP_LOG(log_msg);		
	}

	if(active__clk_on)			doCH__SET_EXEC->Set__DATA(STR__ON);
	else						doCH__SET_EXEC->Set__DATA(STR__OFF);

	return 1;
}

// ...
int  CObj__NXA_PULSE
::Call__TEST_DRV(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CDS_IO__CHANNEL_INFO io_info;

	// do.CH ...
	{
		CString var_name = doCH__PARAM_A1->Get__VARIABLE_NAME();
		CString set_data = doCH__PARAM_A1->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	// do.CH ...
	{
		CString var_name = doCH__SET_EXEC->Get__VARIABLE_NAME();
		CString set_data = doCH__SET_EXEC->Get__STRING();

		__Write__DIGITAL(var_name, io_info, set_data, 0);
	}

	return 1;
}
