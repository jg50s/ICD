#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"
#include "CObj_Phy__LBx_STD__DEF.h"

#include "Macro_Function.h"


// ...
int CObj_Phy__LBx_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int r_flag = Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__INIT);

	if(r_flag > 0)
	{
		if(iActive__SIM_MODE > 0)
		{
			if(xEXT_CH_CFG__TRANSFER_MODE->Check__DATA(STR__VAC) > 0)
			{
				Call__PUMP(p_variable, p_alarm);
			}
			else
			{
				Call__VENT(p_variable, p_alarm);
			}
		}
	}
	return r_flag;
}
int CObj_Phy__LBx_STD
::Call__MAINT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__MAINT);
}

int CObj_Phy__LBx_STD
::Call__PUMP(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		int i;

		for(i=0;i<CFG_LBx__SLOT_MAX;i++)
		{
			if(xCH__SLOT_STATUS[i]->Check__DATA("NONE") > 0)
			{
				continue;
			}

			double preheat_time;
			double cooling_time;

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			xI_SCH_MATERIAL_CTRL->Get__SCH_LBx_INFO(sch_name, preheat_time,cooling_time);

			aCH__PARA_PREHEAT_TIME->Set__VALUE(preheat_time);
			aCH__PARA_COOLING_TIME->Set__VALUE(cooling_time);
			break;
		}
	}

	CStringArray l_sch_name;

	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		CString material_sts;
		int i;

		l_sch_name.RemoveAll();

		for(i=0; i<CFG_LBx__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(material_sts);
			if(Macro__Check_Material_Status(material_sts) < 0)
			{
				continue;
			}

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			l_sch_name.Add(sch_name);

			xI_SCH_MATERIAL_CTRL->Start__ACT_COMMAND(sch_name,"PUMPING");
		}
	}

	// ...
	int loop = -1;
	int flag;

	do
	{
		loop = -1;

		if(xEXT_CH_CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
		{
			flag = 1;
			break;
		}

		flag = Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__PUMP);

		if(flag > 0)
		{
			int retry_count = 5*5;

			//.....
			CString var_data;
			double ref_press;
			double cur_press;

			while(1)
			{
				aEXT_CH_CFG__REF_VAC_PRESSURE->Get__DATA(var_data);
				ref_press = atof(var_data);

				if(iActive__SIM_MODE > 0)
				{
					cur_press = ref_press * 0.9;

					var_data.Format("%.3f", cur_press);
					xCH__PRESSURE_VALUE->Set__DATA(var_data);
				}
				else
				{
					xCH__PRESSURE_VALUE->Get__DATA(var_data);
					cur_press = atof(var_data);
				}

				if(cur_press > ref_press)
				{
					if(retry_count > 0)
					{
						retry_count--;

						Sleep(190);
						continue;
					}

					// ...
					CString alarm_msg;
					CString r_act;

					alarm_msg.Format("LBx's pressure (%.3f torr) must be less than %.3f torr.",	cur_press,ref_press);

					p_alarm->Popup__ALARM_With_MESSAGE(ALID__PUMP_ERROR,alarm_msg,r_act);

					if(r_act.CompareNoCase("RETRY") == 0)
					{
						loop = 1;
					}
					else
					{
						flag = -1;
					}
				}
				break;
			}	
		}
	}
	while(loop > 0);

	if(sSCH_NAME.GetLength() > 0)
	{
		int limit = l_sch_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			xI_SCH_MATERIAL_CTRL->End__ACT_COMMAND(l_sch_name[i],"PUMPING");
		}
	}
	return flag;
}
int CObj_Phy__LBx_STD
::Call__VENT(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM *p_alarm)
{
	bool active__door_open = false;
	CString ch__door_name;
	CString ch__door_data;

	// Dummy_Test ...
	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		sCH__COUNT_VENT_COOLING_SEC->Set__DATA("__");
	}

	// ...
	{
		if(dCH__DOOR_STS_X->Check__DATA("OPEN") > 0)
		{
			active__door_open = true;

			ch__door_name = dCH__DOOR_STS_X->Get__CHANNEL_NAME();
			ch__door_data = dCH__DOOR_STS_X->Get__STRING();
		}

		if(!active__door_open)
		{
			for(int i=0; i<CFG_LBx__SLOT_MAX; i++)
			{
				if(dCH__DOOR_STS_SLOT[i]->Check__DATA("OPEN") < 0)		continue;
					
				active__door_open = true;

				ch__door_name = dCH__DOOR_STS_SLOT[i]->Get__CHANNEL_NAME();
				ch__door_data = dCH__DOOR_STS_SLOT[i]->Get__STRING();
				break;
			}
		}
	}

	if(active__door_open)
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Already, DV Open ... : Error_Check !!! \n";

		log_bff.Format("  * %s <- %s",
					   ch__door_name,
					   ch__door_data);
		log_msg += log_bff;
			           
		xI_LOG_CTRL->WRITE__LOG(log_msg);
		return 1;
	}

	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		int i;

		for(i=0; i<CFG_LBx__SLOT_MAX; i++)
		{
			if(xCH__SLOT_STATUS[i]->Check__DATA("NONE") > 0)
			{
				continue;
			}

			double preheat_time;
			double cooling_time;

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			xI_SCH_MATERIAL_CTRL->Get__SCH_LBx_INFO(sch_name, preheat_time,cooling_time);

			aCH__PARA_PREHEAT_TIME->Set__VALUE(preheat_time);
			aCH__PARA_COOLING_TIME->Set__VALUE(cooling_time);
			break;
		}
	}

	// ...
	CStringArray l_sch_name;

	if(sSCH_NAME.GetLength() > 0)
	{
		CString sch_name;
		CString material_sts;
		int i;

		l_sch_name.RemoveAll();

		for(i=0;i<CFG_LBx__SLOT_MAX;i++)
		{
			xCH__SLOT_STATUS[i]->Get__DATA(material_sts);
			if(Macro__Check_Material_Status(material_sts) < 0)
			{
				continue;
			}

			sch_name.Format("%s-%1d",sSCH_NAME,i+1);
			l_sch_name.Add(sch_name);

			xI_SCH_MATERIAL_CTRL->Start__ACT_COMMAND(sch_name,"VENTING");
		}
	}

	// ...
	int loop = -1;
	int flag;

	do
	{
		if(xCH__PRESSURE_STATUS->Check__DATA("ATM") > 0)
		{
			flag = 1;
			break;
		}

		loop = -1;
		flag = Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__VENT);

		if(flag > 0)
		{
			int retry_count = 5*5;

			CString var_data;
			double ref_press;
			double cur_press;

			while(1)
			{
				aEXT_CH_CFG__REF_ATM_PRESSURE->Get__DATA(var_data);
				ref_press = atof(var_data);

				if(iActive__SIM_MODE > 0)
				{
					cur_press = ref_press * 1.01;

					var_data.Format("%.1f", cur_press);
					xCH__PRESSURE_VALUE->Set__DATA(var_data);
				}
				else
				{
					xCH__PRESSURE_VALUE->Get__DATA(var_data);
					cur_press = atof(var_data);
				}

				if(cur_press < ref_press)
				{
					if(retry_count > 0)
					{
						retry_count--;

						Sleep(190);
						continue;
					}

					CString alarm_msg;
					CString r_act;

					alarm_msg.Format("LBx's pressure (%.3f torr) must be more than %.3f torr.",
						cur_press,ref_press);

					p_alarm->Popup__ALARM_With_MESSAGE(ALID__VENT_ERROR,alarm_msg,r_act);

					if(r_act.CompareNoCase("RETRY") == 0)
					{
						loop = 1;
					}
					else
					{
						flag = -1;
					}
				}
				break;
			}
		}
	}
	while(loop > 0);

	// Dummy_Test ...
	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		double para__cooloing_sec = aCH__PARA_VENT_COOLING_SEC->Get__VALUE();

		// COOLING ...
		if(para__cooloing_sec >= 1.0)
		{
			SCX__ASYNC_TIMER_CTRL x_timer_ctrl;

			x_timer_ctrl->REGISTER__COUNT_CHANNEL_NAME(sCH__COUNT_VENT_COOLING_SEC->Get__CHANNEL_NAME());
			x_timer_ctrl->START__COUNT_UP(99999);

			// Cooling.Start ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "Cooling Start \n";

				log_bff.Format("  * Cooling (sec) <- %.0f \n", para__cooloing_sec);
				log_msg += log_bff;

				xI_LOG_CTRL->WRITE__LOG(log_msg);
			}

			while(1)
			{
				Sleep(10);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					flag = -11;
					break;
				}

				if(x_timer_ctrl->Get__CURRENT_TIME() >=  para__cooloing_sec)			break;
			}

			// Cooling.End ...
			{
				CString log_msg;

				log_msg = "Cooling End \n";

				xI_LOG_CTRL->WRITE__LOG(log_msg);
			}
		}
	}

	if(sSCH_NAME.GetLength() > 0)
	{
		int limit = l_sch_name.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			xI_SCH_MATERIAL_CTRL->End__ACT_COMMAND(l_sch_name[i],"VENTING");
		}
	}
	return flag;
}

//
int CObj_Phy__LBx_STD
::Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__DOOR_OPEN);
}
int CObj_Phy__LBx_STD
::Call__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__DOOR_CLOSE);
}

int CObj_Phy__LBx_STD
::Call__SLOT_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__SLOT_OPEN);
}
int CObj_Phy__LBx_STD
::Call__SLOT_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__SLOT_CLOSE);
}

int CObj_Phy__LBx_STD
::Call__PIN_UP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__PIN_UP);
}
int CObj_Phy__LBx_STD
::Call__PIN_DOWN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__PIN_DOWN);
}

//
int CObj_Phy__LBx_STD
::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	Set__SLOT_PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__PREPMATER);
}
int CObj_Phy__LBx_STD
::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM *p_alarm,
				  const int ex_mode)
{
	Set__SLOT_PARAMETER(p_variable);

	if(ex_mode > 0)
	{
		return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__COMPMATER_EX);
	}
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__COMPMATER);
}

//
int CObj_Phy__LBx_STD::Call__MAP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__MAP);
}
int CObj_Phy__LBx_STD::Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM *p_alarm)
{
	return Fnc__MODULE_OBJ(p_variable,p_alarm, _CMMD__ISOLATE);
}

//
void CObj_Phy__LBx_STD::Set__SLOT_PARAMETER(CII_OBJECT__VARIABLE *p_variable)
{
	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		xCH__SLOT_NO->Set__DATA(l_para[0]);
	}
}
