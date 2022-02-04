#include "StdAfx.h"
#include "CObj__RF_CONDUCT.h"


extern void Macro__Get_Date(CString& date, CString& time);


//-------------------------------------------------------------------------
int CObj__RF_CONDUCT::
Call__RF_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	if(dEXT_CH__VAC_IO_SENSOR->Check__DATA(STR__ON) < 0)
	{
		int alarm_id = ALID__CHAMBER_STATUS__NOT_VAC;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}

	// ...
	{
		sCH__DB_UPDATE_REQUEST->Set__DATA(STR__YES);		
		sCH__DB_UPDATE_REQUEST->When__DATA("", 2.0);
	}

	// ...
	CString str_title = "RF Linearity";

	CString str_msg;
	CString msg;
	int flag = 1;

	// RF CAL ...
	if(flag > 0)
	{
		flag = _Call__RF_CHECK(p_variable,p_alarm);
	}

	// ...
	{
		sCH__DB_UPDATE_REQUEST->Set__DATA(STR__YES);		
		sCH__DB_UPDATE_REQUEST->When__NOT_DATA("", 2.0);
	}

	return flag;
}
int CObj__RF_CONDUCT::
_Call__RF_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{	
	CString rf_type;
	dCH_PARA__RF_TYPE->Get__DATA(rf_type);

	// ...
	{
		CString var_data;
		int i;

		for(i=0;i<CFG__TEST_LIST;i++)
		{
			sCH_PARA__NEW_POWER_LIST[i]->Set__DATA("");
			sCH_PARA__NEW_METER_LIST[i]->Set__DATA("");
			sCH_PARA__NEW_OFFSET_LIST[i]->Set__DATA("");
		}

		// ...
		{
			var_data = "0.0/0.0,";

			sCH__RESULT_STRING->Set__DATA(var_data);
			sCH__REF_STRING->Set__DATA(var_data);
		}
	}

	// ...
	xCH__AUTO_START_CTRL->Set__DATA("START");

	int flag = 1;

	for(int x=0; x<iRF_SIZE; x++)
	{
		CString rf_title = sTITLE__RF_X[x];

		if(rf_type.CompareNoCase(rf_title) != 0)		continue;

		flag = Fnc__RF_CHECK(p_variable,p_alarm, x);
		break;
	}

	xCH__AUTO_START_CTRL->Set__DATA("STOP");

	// ...
	{
		CString str_msg;
		CString msg;

		str_msg = "All RF is off.";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("RF Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	// ...
	{
		int x;

		for(x=0; x<iRF_SIZE; x++)
		{
			pOBJ_CTRL__RF_X[x]->Dislink__UPPER_OBJECT();
		}

		for(x=0; x<iRF_SIZE; x++)
		{
			pOBJ_CTRL__RF_X[x]->Call__OBJECT(CMMD_MODE__RF__OFF);
		}

		for(x=0; x<iRF_SIZE; x++)
		{
			pOBJ_CTRL__RF_X[x]->Link__UPPER_OBJECT();
		}
	}

	xCH__OBJ_MSG->Set__DATA("");
	return flag;
}

int CObj__RF_CONDUCT
::Fnc__RF_CHECK(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const int rf_index)
{	
	CII_EXT_OBJECT__CTRL *p_rf_ctrl;
	CII__VAR_ANALOG_CTRL *p_rf_set;
	CII__VAR_ANALOG_CTRL *p_rf_get;

	// ...
	{
		sCH__OFFSET_CAL_ACTIVE_FLAG->Set__DATA(STR__LOCK);
	}

	// ...
	{
		p_rf_ctrl = pOBJ_CTRL__RF_X[rf_index];
		p_rf_set  = aEXT_CH__SET_POWER__RF_X[rf_index].Get__PTR();
		p_rf_get  = aEXT_CH__GET_POWER__RF_X[rf_index].Get__PTR();

		sEXT_CH__INTERLOCK_SKIP__RF_X[rf_index]->Set__DATA("SKIP");

		sCH__SAVE_ACTIVE_FLAG__RF_X[rf_index]->Set__DATA("LOCK");
		sCH__SAVE_REQ_FLAG__RF_X[rf_index]->Set__DATA("");
	}

	// ...
	CString set_pwr;
	int i;

	for(i=0; i<CFG__TEST_LIST; i++)
	{
		sCH_PARA__NEXT_TEST_REQ->Set__DATA("Testing ...");
		sCH_PARA__END_TEST_REQ->Set__DATA("");

		aCH_PARA__SET_PWR_LIST[i]->Get__DATA(set_pwr);
		sCH_PARA__NEW_POWER_LIST[i]->Set__DATA(set_pwr);

		if(atof(set_pwr) < 0.1)
		{
			break;
		}

		// ...
		int flag = Fnc__LOWER_RF_CHECK(p_variable,
										p_alarm, 
										p_rf_ctrl,
										p_rf_set,
										p_rf_get,
										set_pwr,
										i);

		if(flag < 0)
		{
			return flag;
		}

		if(dCH_PARA__TEST_MODE->Check__DATA(STR__AUTO) > 0)
		{
			sCH_PARA__ACT_ACTIVE_FLAG->Set__DATA("");

			sCH_PARA__NEXT_TEST_REQ->Set__DATA("");
			sCH_PARA__END_TEST_REQ->Set__DATA("");

			continue;
		}

		// ...
		{
			sCH_PARA__ACT_ACTIVE_FLAG->Set__DATA("YES");

			sCH_PARA__NEXT_TEST_REQ->Set__DATA("Next Test ?");
			sCH_PARA__END_TEST_REQ->Set__DATA("End Test ?");
		}

		if((i + 1) < CFG__TEST_LIST)
		{
			while(1)
			{
				Sleep(100);

				if(p_variable->Check__CTRL_ABORT() > 0)
				{
					return -1;
				}
				if(sCH_PARA__NEXT_TEST_REQ->Check__DATA("YES") > 0)
				{
					break;
				}
				if(sCH_PARA__END_TEST_REQ->Check__DATA("YES") > 0)
				{
					return 1;
				}
			}

			sCH_PARA__ACT_ACTIVE_FLAG->Set__DATA("");
		}
	}

	sCH__OFFSET_CAL_ACTIVE_FLAG->Set__DATA(STR__YES);
	return 1;
}
int CObj__RF_CONDUCT::
Fnc__LOWER_RF_CHECK(CII_OBJECT__VARIABLE *p_variable,
					CII_OBJECT__ALARM *p_alarm,
					CII_EXT_OBJECT__CTRL *p_rf_ctrl,
					CII__VAR_ANALOG_CTRL *p_rf_set,
					CII__VAR_ANALOG_CTRL *p_rf_get,
					const CString& str_set_pwr,
					const int db_index)
{
	CString var_data;
	CString str_msg;
	CString msg;


	// 1. RF Ctrl
	{
		str_msg = "RF Control - Started ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("RF Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);

		//
		p_rf_set->Set__DATA(str_set_pwr);

		if(p_rf_ctrl->Call__OBJECT(CMMD_MODE__RF__SET_POWER) < 0)
		{
			str_msg = "RF Control - Aborted ...";
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("RF Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -2;
		}

		//
		str_msg = "RF Control - Completed ...";
		xCH__OBJ_MSG->Set__DATA(str_msg);

		msg.Format("RF Check : %s",str_msg);
		sEXT_CH__FNC_MSG->Set__DATA(msg);
	}

	// 2. Stable Time
	{
		SCX__TIMER_CTRL x_timer_ctrl;

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(sCH_PARA__CHECK_TIME_COUNT->Get__CHANNEL_NAME());

		double cfg__delay_sec;
		aCH_CFG__STABLE_DELAY_SEC->Get__DATA(var_data);
		cfg__delay_sec = atof(var_data);

		//
		{
			str_msg.Format("Step[%1d] : Stable Time - (%s) sec", (db_index+1), var_data);
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("RF Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
		}

		if(x_timer_ctrl->WAIT(cfg__delay_sec) < 0)
		{
			str_msg.Format("Step[%1d] : Stable Time - Aborted ...", (db_index+1));
			xCH__OBJ_MSG->Set__DATA(str_msg);

			msg.Format("RF Check : %s",str_msg);
			sEXT_CH__FNC_MSG->Set__DATA(msg);
			return -3;
		}
	}

	// 3. Result Check
	{
		double x_value = atof(str_set_pwr);
		double y_value = x_value;

		// ...
		{
			CString str_data;
			CString add_data;

			str_data.Format("%.3f/%.3f,", x_value,y_value);

			sCH__REF_STRING->Get__DATA(add_data);
			add_data += str_data;
			sCH__REF_STRING->Set__DATA(add_data);
		}
	}

	return 1;
}

