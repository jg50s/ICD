#include "StdAfx.h"
#include "CObj__iTIM_TYPE.h"

#include "math.h"



//------------------------------------------------------------------------------------
void CObj__iTIM_TYPE::
Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)
	{
		return;
	}

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__iTIM_TYPE::
Fnc__DRV_LOG(const CString& log_msg)
{
	if(dCH__DRV_LOG_PARAM_START_STOP->Check__DATA("STOP") > 0)
	{
		return;
	}

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__iTIM_TYPE::
Fnc__DATA_PARSING(const CString var_name, 
				  const CString str__read_req_data,
				  CString& str_final_data)
{
	CString str_log;
	int     fnc_name_id;
	double	converted_value;

	if((siCH__ELEC_SUPPLY_VOLT->Check__VARIABLE_NAME(var_name) > 0)			// Because of UNIT : 0.1 V
	|| (siCH__PHASE_CURRENT->Check__VARIABLE_NAME(var_name) > 0)			// Because of UNIT : 0.1 A
	|| (siCH__PUMP_POWER->Check__VARIABLE_NAME(var_name) > 0)				// Because of UNIT : 0.1 kW
	|| (siCH__VOLT_READ_THERMISTOR->Check__VARIABLE_NAME(var_name) > 0))	// Because of UNIT : 0.1 mV
	{
		converted_value = atof(str__read_req_data)*0.1;
		str_final_data.Format("%.1f", converted_value);
	}
	else if((siCH__TOTAL_RUN_TIME->Check__VARIABLE_NAME(var_name) > 0)		// Because of UNIT : hours
		 || (siCH__TIME_TO_STOP->Check__VARIABLE_NAME(var_name) > 0))		// Because of UNIT : seconds
	{
		str_final_data = str__read_req_data;
	}
	else if(siCH__N2_SUPPLY_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_final_data = str__read_req_data;
	}
	else if((siCH__MOTOR_TEMP->Check__VARIABLE_NAME(var_name) > 0)
		 || (siCH__BODY_TEMP->Check__VARIABLE_NAME(var_name) > 0))			// 0.1' K (K = 273)
	{
		converted_value = atof(str__read_req_data)*0.1;
		converted_value = converted_value - 274;		// 절대온도를 'C로...
		str_final_data.Format("%.1f", converted_value);
	}
	else if(siCH__WATER_FLOW_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(str__read_req_data.CompareNoCase("1") == 0)			str_final_data = "ON";
		else if(str__read_req_data.CompareNoCase("0") == 0)			str_final_data = "OFF";
		else														str_final_data  = "UNKNOWN";
	}
	else
	{
		str_final_data = "UNKNOWN";
		str_log.Format("%s Unknown...", var_name);

		Fnc__DRV_LOG(str_log);
	}
}

void CObj__iTIM_TYPE::
Fnc__DRV_CMD_ERR(const CString fnc_name, const CString str_get_err)
{
	CString str_err;
	CString str_log;
	int nErr_Num;
	char chErr;

	siCH__CMD_ERR->Set__DATA("0");			// 초기화..
	if(str_get_err.GetLength() >= 4)
	{
		chErr = str_get_err.GetAt(4);
	}
	else
	{
		siCH__CMD_ERR->Set__DATA("0");		// 초기화..
		return;
	}

	// ...
	nErr_Num = atoi(&chErr);

	switch(nErr_Num) 
	{
		case 0:				str_err = "0.NO ERROR";								break;
		case 1:				str_err =  "1.Invalid Message";						break;
		case 2:				str_err = "2.Number Not Found";						break;
		case 3:				str_err = "3.Number Invalid";						break;
		case 4:				str_err = "4.Parameter's value not received";		break;
		case 5:				str_err = "5.Command not possible";					break;

		default:
			str_err.Format("0.NO ERROR");
			Fnc__DRV_LOG("Unknown Error...");
			break;
	}

	siCH__CMD_ERR->Set__DATA(str_err);
	if(nErr_Num != 0)
	{
		str_log.Format("Fnc_Name:[%s], Error:[%s]", fnc_name, str_err);
		Fnc__DRV_LOG(str_log);
	}
}

int CObj__iTIM_TYPE::
Fnc__CMD_ERR_Check(CII_OBJECT__ALARM* p_alarm)
{
	CString str_err;
	CString str_log;
	int nErr_Num;
	int alarm_id;
	char chErr;

	siCH__CMD_ERR->Get__DATA(str_err);

	if(str_err.GetLength() >= 0)			chErr = str_err.GetAt(0);
	else									return 77;

	// ...
	nErr_Num = atoi(&chErr);
	if(nErr_Num == 0)
	{
		return 77;
	}

	switch(nErr_Num) 
	{
		case 0:
			str_err.Format("0.NO ERROR");
			break;
		case 1:
			str_err.Format("1.Invalid Message");
			alarm_id = ALID__PUMP_CMD_1_ERROR;
			break;
		case 2:
			str_err.Format("2.Number Not Found");
			alarm_id = ALID__PUMP_CMD_2_ERROR;
			break;
		case 3:
			str_err.Format("3.Number Invalid");
			alarm_id = ALID__PUMP_CMD_3_ERROR;
			break;
		case 4:
			str_err.Format("4.Parameter's value not received");
			alarm_id = ALID__PUMP_CMD_4_ERROR;
			break;
		case 5:
			str_err.Format("5.Command not possible");
			alarm_id = ALID__PUMP_CMD_5_ERROR;
			break;
		default:
			str_err.Format("0.NO ERROR");
			Fnc__DRV_LOG("Unknown Error...");
			break;
	}

	str_log.Format("Error:[%s]", str_err);
	Fnc__DRV_LOG(str_log);

	// ...
	{
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Popup__ALARM(alarm_id, r_act);

			 if(r_act.CompareNoCase("RETRY") == 0)		return OBJ_RETRY;
		else if(r_act.CompareNoCase("ABORT") == 0)		return OBJ_ABORT;
	}
	return 77;
}
