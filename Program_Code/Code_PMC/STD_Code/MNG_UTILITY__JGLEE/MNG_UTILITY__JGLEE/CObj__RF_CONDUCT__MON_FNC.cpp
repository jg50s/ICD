#include "StdAfx.h"
#include "CObj__RF_CONDUCT.h"



//-------------------------------------------------------------------------
void CObj__RF_CONDUCT
::Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	sCH__DB_UPDATE_REQUEST->Set__DATA(STR__YES);

	// ...
	int update_flag = -1;
	CString pre__rf_type;

	CString var_data;
	int x;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ...
		{
			update_flag = -1;

			if(sCH__DB_UPDATE_REQUEST->Check__DATA(STR__YES) > 0)
			{
				sCH__DB_UPDATE_REQUEST->Set__DATA(STR__CHECKING);

				update_flag = 1;
			}
			else if(sCH__DB_UPDATE_REQUEST->Check__DATA(STR__CHECKING) > 0)
			{
				sCH__DB_UPDATE_REQUEST->Set__DATA("");
			}
		}

		// ...
		dCH_PARA__RF_TYPE->Get__DATA(var_data);

		if(var_data.CompareNoCase(pre__rf_type) != 0)
		{
			if(iFLAG__RF_CHECK > 0)
			{
				if(pre__rf_type.GetLength() > 0)
				{
					// ...
					{
						int alarm_id = ALID__RF_TYPE__CAN_NOT_CHANGED;
						CString alm_msg;
						CString r_act;

						alm_msg.Format("The current RF(%s) type can be changed to the requested RF(%s) type. \n",
							pre__rf_type,var_data);

						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
					}

					var_data = pre__rf_type;
					dCH_PARA__RF_TYPE->Set__DATA(var_data);	
				}
			}
		}

		if((var_data.CompareNoCase(pre__rf_type) != 0)
		|| (update_flag > 0))	
		{
			CString cur__rf_type = var_data;		

			CII__VAR_ANALOG_CTRL*  p__set_power  = NULL;

			CII__VAR_STRING_CTRL*  p__new_power  = NULL;
			CII__VAR_STRING_CTRL*  p__new_meter  = NULL;
			CII__VAR_STRING_CTRL*  p__new_offset = NULL;

			CII__VAR_STRING_CTRL*  p__now_power  = NULL;
			CII__VAR_STRING_CTRL*  p__now_meter  = NULL;
			CII__VAR_STRING_CTRL*  p__now_offset = NULL;

			for(x=0; x<iRF_SIZE; x++)
			{
				CString rf_title = sTITLE__RF_X[x];

				if(pre__rf_type.CompareNoCase(rf_title) != 0)
				{
					continue;
				}

				// View -> RFx
				for(i=0; i<CFG__TEST_LIST; i++)
				{
					p__set_power  = aEXT_CH__CAL_CFG_SET_POWER__RF_X[x][i].Get__PTR();

					p__new_power  = sEXT_CH__CAL_CFG_NEW_POWER__RF_X[x][i].Get__PTR();
					p__new_meter  = sEXT_CH__CAL_CFG_NEW_METER__RF_X[x][i].Get__PTR();
					p__new_offset = sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[x][i].Get__PTR();

					p__now_power  = sEXT_CH__CAL_CFG_NOW_POWER__RF_X[x][i].Get__PTR();
					p__now_meter  = sEXT_CH__CAL_CFG_NOW_METER__RF_X[x][i].Get__PTR();
					p__now_offset = sEXT_CH__CAL_CFG_NOW_OFFSET__RF_X[x][i].Get__PTR();

					// ...
					aCH_PARA__SET_PWR_LIST[i]->Get__DATA(var_data);
					p__set_power->Set__DATA(var_data);

					//
					sCH_PARA__NEW_POWER_LIST[i]->Get__DATA(var_data);
					p__new_power->Set__DATA(var_data);

					sCH_PARA__NEW_METER_LIST[i]->Get__DATA(var_data);
					p__new_meter->Set__DATA(var_data);

					sCH_PARA__NEW_OFFSET_LIST[i]->Get__DATA(var_data);								
					p__new_offset->Set__DATA(var_data);

					//
					sCH_PARA__NOW_POWER_LIST[i]->Get__DATA(var_data);
					p__now_power->Set__DATA(var_data);

					sCH_PARA__NOW_METER_LIST[i]->Get__DATA(var_data);
					p__now_meter->Set__DATA(var_data);

					sCH_PARA__NOW_OFFSET_LIST[i]->Get__DATA(var_data);								
					p__now_offset->Set__DATA(var_data);
				}

				// RFx -> View ...
				for(i=0; i<CFG__TEST_LIST; i++)
				{
					p__set_power  = aEXT_CH__CAL_CFG_SET_POWER__RF_X[x][i].Get__PTR();

					p__new_power  = sEXT_CH__CAL_CFG_NEW_POWER__RF_X[x][i].Get__PTR();
					p__new_meter  = sEXT_CH__CAL_CFG_NEW_METER__RF_X[x][i].Get__PTR();
					p__new_offset = sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[x][i].Get__PTR();

					p__now_power  = sEXT_CH__CAL_CFG_NOW_POWER__RF_X[x][i].Get__PTR();
					p__now_meter  = sEXT_CH__CAL_CFG_NOW_METER__RF_X[x][i].Get__PTR();
					p__now_offset = sEXT_CH__CAL_CFG_NOW_OFFSET__RF_X[x][i].Get__PTR();
	
					// ...
					p__set_power->Get__DATA(var_data);
					aCH_PARA__SET_PWR_LIST[i]->Set__DATA(var_data);

					//
					p__new_power->Get__DATA(var_data);
					sCH_PARA__NEW_POWER_LIST[i]->Set__DATA(var_data);

					p__new_meter->Get__DATA(var_data);
					sCH_PARA__NEW_METER_LIST[i]->Set__DATA(var_data);

					p__new_offset->Get__DATA(var_data);
					sCH_PARA__NEW_OFFSET_LIST[i]->Set__DATA(var_data);

					//
					p__now_power->Get__DATA(var_data);
					sCH_PARA__NOW_POWER_LIST[i]->Set__DATA(var_data);

					p__now_meter->Get__DATA(var_data);
					sCH_PARA__NOW_METER_LIST[i]->Set__DATA(var_data);

					p__now_offset->Get__DATA(var_data);
					sCH_PARA__NOW_OFFSET_LIST[i]->Set__DATA(var_data);
				}

				// ...
				{
					CString str__new_off = sEXT_CH__CAL_CFG_NEW_AVG_OFFSET__RF_X[x]->Get__STRING();
					CString str__now_off = sEXT_CH__CAL_CFG_NOW_AVG_OFFSET__RF_X[x]->Get__STRING();

					sCH__CFG_AVERAGE_NEW_OFFSET->Set__DATA(str__new_off);
					sCH__CFG_AVERAGE_NOW_OFFSET->Set__DATA(str__now_off);
				}

				// ...
				{
					CString str_data;

					double x_value;
					double y_value;

					str_data = "0.0/0.0,";

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						sCH_PARA__NEW_POWER_LIST[i]->Get__DATA(var_data);
						x_value = atof(var_data);
						if(x_value < 1)			break;

						sCH_PARA__NEW_METER_LIST[i]->Get__DATA(var_data);
						y_value = atof(var_data);

						// ...
						{
							var_data.Format("%.3f/%.3f,", x_value,y_value);
							str_data += var_data;
						}
					}

					sCH__RESULT_STRING->Set__DATA(str_data);
				}

				pre__rf_type = cur__rf_type;

				// ...
				{
					CString str_data;
					CString add_data;

					double x_value = 0.0;
					double y_value = 0.0;

					str_data.Format("%.3f/%.3f,", x_value,y_value);

					for(i=0; i<CFG__TEST_LIST; i++)	
					{
						sCH_PARA__NEW_POWER_LIST[i]->Get__DATA(var_data);
						x_value = atof(var_data);
						if(x_value < 1)			break;

						y_value = x_value;

						add_data.Format("%.3f/%.3f,", x_value,y_value);
						str_data += add_data;
					}

					sCH__REF_STRING->Set__DATA(str_data);
				}

				break;
			}
		}

		//
		for(x=0; x<iRF_SIZE; x++)
		{
			if(sCH__SAVE_REQ_FLAG__RF_X[x]->Check__DATA(STR__YES) > 0)
			{
				sCH__SAVE_REQ_FLAG__RF_X[x]->Set__DATA("");

				Fnc__RFx_SAVE(x);
			}			
		}

		//
		if(sCH__OFFSET_CAL_REQ_FLAG->Check__DATA(STR__YES) > 0)
		{
			sCH__OFFSET_CAL_REQ_FLAG->Set__DATA("");
			sCH__OFFSET_CAL_ACTIVE_FLAG->Set__DATA("OK");

			//
			CString rf_type = dCH_PARA__RF_TYPE->Get__STRING();

			for(x=0; x<iRF_SIZE; x++)
			{
				CString rf_title = sTITLE__RF_X[x];

				if(rf_type.CompareNoCase(rf_title) != 0)		continue;

				sCH__SAVE_ACTIVE_FLAG__RF_X[x]->Set__DATA("YES");
				
				Fnc__RFx_CAL(x);
				break;
			}
		}

		// ...
	}
}

void CObj__RF_CONDUCT::Fnc__RFx_CAL(const int rf_index)
{
	CII__VAR_ANALOG_CTRL* p__set_power = NULL;

	CII__VAR_STRING_CTRL* p__new_power  = NULL;
	CII__VAR_STRING_CTRL* p__new_meter  = NULL;
	CII__VAR_STRING_CTRL* p__new_offset = NULL;

	CII__VAR_STRING_CTRL* p__rf_new_meter  = NULL;
	CII__VAR_STRING_CTRL* p__rf_new_offset = NULL;

	CStringArray l_offset;
	CString var_data;
	int i;

	for(i=0; i<CFG__TEST_LIST; i++)
	{
		p__set_power  = aCH_PARA__SET_PWR_LIST[i].Get__PTR();

		p__new_power  = sCH_PARA__NEW_POWER_LIST[i].Get__PTR();
		p__new_meter  = sCH_PARA__NEW_METER_LIST[i].Get__PTR();
		p__new_offset = sCH_PARA__NEW_OFFSET_LIST[i].Get__PTR();

		p__rf_new_meter  = sEXT_CH__CAL_CFG_NEW_METER__RF_X[rf_index][i].Get__PTR();
		p__rf_new_offset = sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[rf_index][i].Get__PTR();

		// ...
		double value__set_power;
		double value__new_meter;

		// POWER ...
		{
			p__new_power->Get__DATA(var_data);
			value__set_power = atof(var_data);

			if(value__set_power < 0.1)
			{
				break;
			}
		}

		// METER ...
		{
			p__new_meter->Get__DATA(var_data);
			p__rf_new_meter->Set__DATA(var_data);
			value__new_meter = atof(var_data);
		}

		// OFFET ...
		{
			double err_per = 0.0;

			if(value__set_power >= 0.01)
			{
				err_per = ((value__set_power - value__new_meter) / value__set_power) * 100.0;
			}
			else
			{
				err_per = (value__set_power - value__new_meter);
			}

			var_data.Format("%.1f", err_per);
			p__new_offset->Set__DATA(var_data);
			p__rf_new_offset->Set__DATA(var_data);

			l_offset.Add(var_data);
		}
	}

	// ...
	{
		double value__avg_err = 0;
		double value__cur_err = 0;

		int limit = l_offset.GetSize();

		for(i=0; i<limit; i++)
		{
			value__cur_err = atof(l_offset[i]);
			value__avg_err += (value__cur_err / limit);
		}

		var_data.Format("%.1f", value__avg_err);
		sCH__CFG_AVERAGE_NEW_OFFSET->Set__DATA(var_data);

		sEXT_CH__CAL_CFG_NEW_AVG_OFFSET__RF_X[rf_index]->Set__DATA(var_data);
	}

	// ...
	{
		CString str_data;
		CString add_data;

		double x_value = 0.0;
		double y_value = 0.0;

		str_data.Format("%.3f/%.3f,", x_value,y_value);

		for(i=0; i<CFG__TEST_LIST; i++)	
		{
			sCH_PARA__NEW_POWER_LIST[i]->Get__DATA(var_data);
			x_value = atof(var_data);
			if(x_value < 1)			break;

			sCH_PARA__NEW_METER_LIST[i]->Get__DATA(var_data);
			y_value = atof(var_data);

			add_data.Format("%.3f/%.3f,", x_value,y_value);
			str_data += add_data;
		}

		sCH__RESULT_STRING->Set__DATA(str_data);
	}
}
void CObj__RF_CONDUCT::Fnc__RFx_SAVE(const int rf_index)
{
	SCX__SEQ_INFO x_seq_info;
	CString str_date = x_seq_info->Get__DATE_TIME_STRING();

	sCH__SAVE_ACTIVE_FLAG__RF_X[rf_index]->Set__DATA(STR__OK);
	sEXT_CH__CAL_OFFSET_SAVE_DATE__RF_X[rf_index]->Set__DATA(str_date);

	// ...
	CII__VAR_STRING_CTRL*  p__new_power  = NULL;
	CII__VAR_STRING_CTRL*  p__new_meter  = NULL;
	CII__VAR_STRING_CTRL*  p__new_offset = NULL;

	CII__VAR_STRING_CTRL*  p__now_power  = NULL;
	CII__VAR_STRING_CTRL*  p__now_meter  = NULL;
	CII__VAR_STRING_CTRL*  p__now_offset = NULL;

	CString var_data;
	int i;

	for(i=0; i<CFG__TEST_LIST; i++)
	{
		p__new_power  = sEXT_CH__CAL_CFG_NEW_POWER__RF_X[rf_index][i].Get__PTR();
		p__new_meter  = sEXT_CH__CAL_CFG_NEW_METER__RF_X[rf_index][i].Get__PTR();
		p__new_offset = sEXT_CH__CAL_CFG_NEW_OFFSET__RF_X[rf_index][i].Get__PTR();

		p__now_power  = sEXT_CH__CAL_CFG_NOW_POWER__RF_X[rf_index][i].Get__PTR();
		p__now_meter  = sEXT_CH__CAL_CFG_NOW_METER__RF_X[rf_index][i].Get__PTR();
		p__now_offset = sEXT_CH__CAL_CFG_NOW_OFFSET__RF_X[rf_index][i].Get__PTR();

		// POWER ...
		{
			p__new_power->Get__DATA(var_data);

			p__now_power->Set__DATA(var_data);
			sCH_PARA__NOW_POWER_LIST[i]->Set__DATA(var_data);
		}
		// METER ...
		{
			p__new_meter->Get__DATA(var_data);

			p__now_meter->Set__DATA(var_data);
			sCH_PARA__NOW_METER_LIST[i]->Set__DATA(var_data);
		}
		// OFFET ...
		{
			p__new_offset->Get__DATA(var_data);		

			p__now_offset->Set__DATA(var_data);
			sCH_PARA__NOW_OFFSET_LIST[i]->Set__DATA(var_data);
		}
	}

	// AVERAGE OFFSET ...
	{
		sCH__CFG_AVERAGE_NEW_OFFSET->Get__DATA(var_data);
		sCH__CFG_AVERAGE_NOW_OFFSET->Set__DATA(var_data);

		sEXT_CH__CAL_CFG_NOW_AVG_OFFSET__RF_X[rf_index]->Set__DATA(var_data);
	}
}
