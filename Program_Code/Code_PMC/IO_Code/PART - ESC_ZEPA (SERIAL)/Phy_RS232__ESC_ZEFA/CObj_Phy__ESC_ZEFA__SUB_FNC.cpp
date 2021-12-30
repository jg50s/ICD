#include "StdAfx.h"

#include "CObj_Phy__ESC_ZEFA.h"
//#include "CObj_Phy__ESC_ZEFA__DEF.h"

#include "CCommon_DEF.h"

//----------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
FNC__INITIAL(CII_OBJECT__VARIABLE*	p_variable,
			 CII_OBJECT__ALARM*		p_alarm)
{
	Write__DRV_LOG("FNC__INITIAL_Start");

	int sim_flag;
	
	sim_flag = xI_SEQ->Is__SIMULATION_MODE();
	if (sim_flag > 0)
	{
		sCH__REMOTE_STATUS->Set__DATA("Remote");
		aCH__VOLT_SET_CH1->Set__DATA("0");
		aCH__VOLT_SET_CH2->Set__DATA("0");

		return 1;
	}

	mon_flag = 0;
	if (Call__REMOTE(p_variable, p_alarm) < 0)			{return -1;}
	Sleep(200);
	//if (Call__OFF(p_variable, p_alarm) < 0)				{return -2;}
	if (doCH__OUTPUT->Set__DATA(MODE__OFF) < 0)			{return -2;}
	Sleep(200);
	if (aCH__VOLT_SET_CH1->Set__DATA("0") < 0)			{return -3;}
	Sleep(200);
	if (aCH__VOLT_SET_CH2->Set__DATA("0") < 0)			{return -4;}
	Sleep(200);
	if (aoCH__VOLT_SET_CH1->Set__DATA("0") < 0)			{return -9;}
	Sleep(200);
	if (aoCH__VOLT_SET_CH2->Set__DATA("0") < 0)			{return -10;}
	Sleep(200);
	if (Call__VOLT_SET(p_variable, p_alarm) < 0)		{return -5;}
	Sleep(200);
	if (Call__RAMPUP_SET(p_variable, p_alarm) < 0)		{return -6;}
	Sleep(200);
	if (Call__RAMPDN_SET(p_variable, p_alarm) < 0)		{return -7;}
	Sleep(200);
	if (Call__CURRLIMIT_SET(p_variable, p_alarm) < 0)	{return -8;}

	Write__DRV_LOG("FNC__INITIAL_End");
	mon_flag = 1;
	return 1;
}

//----------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
FNC__PROC_READY(CII_OBJECT__VARIABLE*	p_variable,
			 CII_OBJECT__ALARM*		p_alarm)
{
	Write__DRV_LOG("FNC__PROC_READY_Start");

	int sim_flag;

	sim_flag = xI_SEQ->Is__SIMULATION_MODE();
	if (sim_flag > 0)
	{
		sCH__REMOTE_STATUS->Set__DATA("Remote");
		aCH__VOLT_SET_CH1->Set__DATA("0");
		aCH__VOLT_SET_CH2->Set__DATA("0");
		aCH__RAMPUP_SET->Set__DATA("0.3");
		aCH__RAMPDN_SET->Set__DATA("0.3");

		return 1;
	}

	mon_flag = 0;
	if (Call__REMOTE(p_variable, p_alarm) < 0)			{return -1;}
	Sleep(200);
	if (Call__OFF(p_variable, p_alarm) < 0)				{return -2;}
	Sleep(200);
	if (aCH__VOLT_SET_CH1->Set__DATA("0") < 0)			{return -3;}
	Sleep(200);
	if (aCH__VOLT_SET_CH2->Set__DATA("0") < 0)			{return -4;}
	Sleep(200);
	if (Call__RAMPUP_SET(p_variable, p_alarm) < 0)		{return -5;}
	Sleep(200);
	if (Call__RAMPDN_SET(p_variable, p_alarm) < 0)		{return -6;}
	Sleep(200);
	if (Call__CURRLIMIT_SET(p_variable, p_alarm) < 0)	{return -7;}

	Write__DRV_LOG("FNC__PROC_READY_End");
	mon_flag = 1;
	return 1;
}

//----------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
FNC__ON_SEQ(CII_OBJECT__VARIABLE*	p_variable,
			CII_OBJECT__ALARM*	p_alarm)
{
	Write__DRV_LOG("FNC__ON_SEQ_Start");

	int sim_flag;

	sim_flag = xI_SEQ->Is__SIMULATION_MODE();
	if (sim_flag > 0)
	{
		CString ch_data;
		
		sCH__REMOTE_STATUS->Set__DATA("Remote");
		aCH__RAMPUP_SET->Get__DATA(ch_data);
		aCH__RAMPUP_READ->Set__DATA(ch_data);
		aCH__RAMPDN_SET->Get__DATA(ch_data);
		aCH__RAMPDN_READ->Set__DATA(ch_data);
		aCH__VOLT_SET_CH1->Get__DATA(ch_data);
		aCH__VOLT_READ_CH1->Set__DATA(ch_data);
		aCH__VOLT_SET_CH2->Get__DATA(ch_data);
		aCH__VOLT_READ_CH2->Set__DATA(ch_data);

		return 1;
	}

	CString ch1_data;
	CString ch2_data;
	CString	trg_volt;
	CString local_remote;
	CString log_msg;
	CString buf_msg;
	CString toggle;
	int		flag = 1;

	sCH__REMOTE_STATUS->Get__DATA(local_remote);
	dCH__CFG_TOGGLE_USE->Get__DATA(toggle);
	
	aCH__VOLT_SET_CH1->Get__DATA(ch1_data);
	aCH__VOLT_SET_CH2->Get__DATA(ch2_data);
	trg_volt.Format("%s,%s", ch1_data, ch2_data);

	{ // Remote Mode가 아닐 경우, Remote Mode 전환 후, On Seq 진행
		if (local_remote == STS__OFF)
		{
			doCH__LOCAL_REMOTE->Set__DATA(MODE__REMOTE);
		}
	}
	
	// Volt Set은 "doCH__OUTPUT" DRV function에서 수행한다.
	{ // Volt Set
		if (sCH__VOLT_SET_ALL->Set__DATA(MODE__ON) < 0)
		{
			flag = -11;
			Write__DRV_LOG("FNC__ON_SEQ - VOLT_SET NG");
			return flag;
		}
	}

	{ // Output On
		if (doCH__OUTPUT->Set__DATA(MODE__ON) < 0)
		{
			flag = -12;
			Write__DRV_LOG("FNC__ON_SEQ - OUTPUT_ON NG");

			return flag;
		}
	}

	{ // Toggle On
		if (toggle.CompareNoCase("USE") == 0)
		{
			Sleep(100);
			if (doCH__TOGGLE->Set__DATA(MODE__ON) < 0)
			{
				flag = -13;
				Write__DRV_LOG("FNC__ON_SEQ - TOGGLE_ON NG");

				return flag;
			}
		}
	}
	
	Write__DRV_LOG("FNC__ON_SEQ_End");
	return flag;
}

//----------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
FNC__PROC_SEQ(CII_OBJECT__VARIABLE*	p_variable,
			 CII_OBJECT__ALARM*		p_alarm)
{
	Write__DRV_LOG("FNC__PROC_SEQ_Start");

	int sim_flag;

	sim_flag = xI_SEQ->Is__SIMULATION_MODE();
	if (sim_flag > 0)
	{
		CString ch_data;

		sCH__REMOTE_STATUS->Set__DATA("Remote");
		aCH__RAMPUP_SET->Get__DATA(ch_data);
		aCH__RAMPUP_READ->Set__DATA(ch_data);
		aCH__RAMPDN_SET->Get__DATA(ch_data);
		aCH__RAMPDN_READ->Set__DATA(ch_data);
		aCH__VOLT_SET_CH1->Get__DATA(ch_data);
		aCH__VOLT_READ_CH1->Set__DATA(ch_data);
		aCH__VOLT_SET_CH2->Get__DATA(ch_data);
		aCH__VOLT_READ_CH2->Set__DATA(ch_data);

		return 1;
	}

	CString trg_value;
	CString trg_mode;
	CString trg_rampup;
	CString local_remote;
	CString log_msg;
	CString buf_msg;
	int		flag = 1;

	sCH__REMOTE_STATUS->Get__DATA(local_remote);

	/* // 20181010 Process Sequence 간략화 및 Process Ready 추가
	if (local_remote == STS__OFF)	// Remote Mode 아니면 Remote Mode
	{
		Call__REMOTE(p_variable, p_alarm);
		log_msg ="SUB_FNC : Call_REMOTE_OK\n";
		Write__DRV_LOG(log_msg);
	}

	if (Call__RAMPUP_SET(p_variable,p_alarm) < 0) // RampUp Set
	{
		log_msg = "SUB_FNC : Call__RAMPUP_SET_NG\n";
		flag = -1;
	}	
	else
	{
		log_msg = "SUB_FNC : Call__RAMPUP_SET\n";
	}
	Write__DRV_LOG(log_msg);

	if (Call__RAMPDN_SET(p_variable,p_alarm) < 0) // RampDown Set
	{
		log_msg = "SUB_FNC : Call__RAMPDN_SET_NG\n";
		flag = -1;
	}	
	else
	{
		log_msg = "SUB_FNC : Call__RAMPDN_SET\n";
	}
	Write__DRV_LOG(log_msg);

	if (flag < 0) // ESC ON 명령 이전에 통신에 Error가 발생할 경우, ON시키지 않고 Return 시키기 위해
	{
		log_msg = "PROC_SEQ_NG - Before ESC On";
		Write__DRV_LOG(log_msg);

		return -1;
	}
	*/

	if (Call__VOLT_SET(p_variable,p_alarm) < 0) // Voltage Set
	{
		log_msg = "SUB_FNC : Call__VOLTAGE_SET_NG\n";
		flag = -1;
	}
	else
	{
		log_msg = "SUB_FNC : Call__VOLTAGE_SET_OK\n";
	}
	Write__DRV_LOG(log_msg);

	if (Call__ON(p_variable, p_alarm) < 0) // ESC ON
	{
		log_msg = "SUB_FNC : Call__ON_NG\n";
		flag = -1;
		if (flag < 0)
		{
			buf_msg = "PROC_SEQ_NG - After ESC On";
			log_msg += buf_msg;
			Write__DRV_LOG(log_msg);

			return -1;
		}
	}
	else
	{
		log_msg = "SUB_FNC : Call__ON_OK\n";
	}
	Write__DRV_LOG(log_msg);
	
	Write__DRV_LOG("FNC__PROC_SEQ_End");

	return 1;
}

//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
Recv_Data_Multi(const CString& real_data, CStringArray& value, const char Sepa_Str, int total_len)
{
	// ...
	{
		value.RemoveAll();
	}

	CString data = "";
	int		posi = 0;
	int		lastposi = 0;
	int		i;
	int		len;

	len = real_data.GetLength();

	for (i=0; i<total_len; i++)
	{
		if (posi == 0)
		{
			posi = real_data.Find(Sepa_Str, 0);
			lastposi = posi;
			data = real_data.Left(posi);
		}
		else
		{
			posi = real_data.Find(Sepa_Str, lastposi + 1);
			if (posi == -1)	// 더 이상 Separate문자가 없을 경우
			{	
				//data = real_data.Mid(lastposi + 1, (total_len - 2));
				data = real_data.Mid(lastposi + 1, (len - 1));
				value.Add(data);
				lastposi = posi;

				break;
			}
			else
			{
				data = real_data.Mid(lastposi + 1, (posi - lastposi - 1));
			}
			lastposi = posi;
		}
		value.Add(data);
	}

	return 1;
}

//------------------------------------------------------------------------------------
int CObj_Phy__ESC_ZEFA::
Recv_Data_Single(const CString& real_data, CString *value)
{
	CString data;
	CString cmd;
	CString buf;
	CString log_msg;
	int		len;

	len = real_data.GetLength();
	data = real_data.Left(len);

	*value = data;

	return 1;
}

//------------------------------------------------------------------------------------
void  CObj_Phy__ESC_ZEFA::
Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm)
{
	// Set Zero
	sCH__VOLT_SET_ALL->Set__DATA(MODE__OFF);

	// Set Off
	doCH__OUTPUT->Set__DATA(MODE__OFF);	
}

//------------------------------------------------------------------------------------
int  CObj_Phy__ESC_ZEFA::
Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm)
{
	//dCH__COMM_STS->Set__DATA("ONLINE");
	if(dCH__COMM_STS->Check__DATA("ONLINE") < 0)
	{
		CString r_act;
		p_alarm->Popup__ALARM(ALID__ESCCON_OFFLINE_ALARM, r_act);

		return -1;
	}
	return 1;
}

//------------------------------------------------------------------------------------
int  CObj_Phy__ESC_ZEFA::
Seq__Ramp_Up_Down(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm,
				  const int zero_ctrl)
{
	//SCX__TIMER_CTRL cx_timer_ctrl;
	//cx_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	//// ...
	//CString obj_msg;
	//int	    ramp_flag;

	//CString var_data;
	//double  trg__set_value;
	//double  trg__set_rate;
	//double  cur__set_value; 
	//double  unit_set;

	//// ...
	//{
	//	aCH__VOLT_SET->Get__DATA(var_data);
	//	trg__set_value = atof(var_data);

	//	aCH__RAMPUP_SET->Get__DATA(var_data);
	//	trg__set_rate = atof(var_data);

	//	if(zero_ctrl > 0)
	//	{
	//		cur__set_value = 0.0;
	//	}
	//	else
	//	{
	//		sCH__SETVOLT_READ->Get__DATA(var_data);
	//		cur__set_value = atof(var_data);
	//	}

	//	//unit_set = trg__set_rate / 60.0;
	//	unit_set = trg__set_rate;
	//}

	//if(trg__set_rate < 1.0)
	//{
	//	trg__set_rate = 1.0;
	//}

	//int n_sec = (int) (((trg__set_value - cur__set_value) / trg__set_rate) * 60.0);

	//if(trg__set_value > cur__set_value)
	//{
	//	obj_msg.Format("RAMP UP COUNT START...");		
	//	ramp_flag = 1;
	//}
	//else 
	//{
	//	obj_msg.Format("RAMP DOWN COUNT START...");
	//	ramp_flag = -1;

	//}
	//sCH__OBJ_MSG->Set__DATA(obj_msg);

	//// ...
	//{
	//	CString log_msg;
	//	CString log_bff;

	//	log_msg = "Ramp_Up_Down Parameter ... \n";

	//	log_bff.Format("ramp_flag <- %1d \n", ramp_flag);
	//	log_msg += "\n";

	//	log_bff.Format("trg__set_value <- %.3f \n", trg__set_value);
	//	log_msg += "\n";

	//	log_bff.Format("trg__set_rate  <- %.3f \n", trg__set_rate);
	//	log_msg += "\n";

	//	log_bff.Format("cur__set_value <- %.3f \n", cur__set_value);
	//	log_msg += "\n";

	//	log_bff.Format("unit_set <- %.3f \n", unit_set);
	//	log_msg += "\n";

	//	Write__APP_LOG(log_msg);
	//}

	//while(n_sec > 0)
	//{
	//	aoCH__VOLTAGE_SET->Set__VALUE(cur__set_value);

	//	if(cx_timer_ctrl->WAIT(1.0) < 0)
	//	{
	//		Fnc__Do_Abort(p_alarm);
	//		return -1;
	//	}

	//	if(ramp_flag == 1)
	//	{
	//		cur__set_value += unit_set;

	//		if(cur__set_value >= trg__set_value)	
	//		{
	//			cur__set_value = trg__set_value;
	//			n_sec = 0;
	//		}
	//	}
	//	else
	//	{
	//		cur__set_value -= unit_set;

	//		if(cur__set_value <= trg__set_value)	
	//		{
	//			cur__set_value = trg__set_value;
	//			n_sec = 0;
	//		}
	//	}

	//	n_sec--;
	//	aoCH__VOLTAGE_SET->Set__VALUE(cur__set_value);

	//	// ...
	//	{
	//		CString bff_msg;
	//		bff_msg.Format("%s  %1d sec [%.1f]", obj_msg,n_sec,cur__set_value);

	//		sCH__OBJ_MSG->Set__DATA(bff_msg);

	//		Write__APP_LOG(bff_msg);
	//	}
	//}

	//if(ramp_flag ==	1)		obj_msg.Format("RAMP UP END...");
	//else					obj_msg.Format("RAMP DOWN END...");

	//sCH__OBJ_MSG->Set__DATA(obj_msg);
	//aoCH__VOLTAGE_SET->Set__VALUE(trg__set_value);

	return 1;
}

