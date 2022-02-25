#include "StdAfx.h"
#include "CObj_Phy__LBx_STD.h"
#include "CObj_Phy__LBx_STD__DEF.h"

#include "Macro_Function.h"


// ...
int CObj_Phy__LBx_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__INIT);
}
int CObj_Phy__LBx_STD
::Call__MAINT(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__MAINT);
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

		flag = Fnc__MODULE_OBJ(p_variable, _CMMD__PUMP);

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

				xCH__PRESSURE_VALUE->Get__DATA(var_data);
				cur_press = atof(var_data);

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
		flag = Fnc__MODULE_OBJ(p_variable, _CMMD__VENT);

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

				xCH__PRESSURE_VALUE->Get__DATA(var_data);
				cur_press = atof(var_data);

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
::Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable)
{
	Set__SLOT_PARAMETER(p_variable);

	return Fnc__MODULE_OBJ(p_variable, _CMMD__PREPMATER);
}
int CObj_Phy__LBx_STD
::Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable, 
				  const int ex_mode)
{
	Set__SLOT_PARAMETER(p_variable);

	if(ex_mode > 0)
	{
		return Fnc__MODULE_OBJ(p_variable, _CMMD__COMPMATER_EX);
	}
	return Fnc__MODULE_OBJ(p_variable, _CMMD__COMPMATER);
}

//
int CObj_Phy__LBx_STD::Call__MAP(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__MAP);
}
int CObj_Phy__LBx_STD::Call__ISOLATE(CII_OBJECT__VARIABLE* p_variable)
{
	return Fnc__MODULE_OBJ(p_variable, _CMMD__ISOLATE);
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
