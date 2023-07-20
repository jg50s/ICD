#include "StdAfx.h"
#include "CObj__WAP_POS_CONDUCT.h"
#include "CObj__WAP_POS_CONDUCT__DEF.h"



//-------------------------------------------------------------------------
void CObj__WAP_POS_CONDUCT::
Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	CString cur_gap_type;
	CString pre_gap_type;

	// ...
	CString pre__move_offset;
	aCH__SIM_MOVE_OFFSET->Get__DATA(pre__move_offset);

	CString pre__move_lookup;
	dCH__SIM_MOVE_LOOKUP->Get__DATA(pre__move_lookup);

	CString pre__data_type;
	dCH__SIM_MOVE_DATA_TYPE->Get__DATA(pre__data_type);

	// ...
	CString var_data;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.3);


		// ...
		{
			cur_gap_type = dCH_CFG__C_RING_GAP_TYPE->Get__STRING();

			if(cur_gap_type.CompareNoCase(pre_gap_type) != 0)
			{
				pre_gap_type = cur_gap_type;

				// ...
				CStringArray l_ref_pos;
				CStringArray l_ref_data;

				if(Get__REF_CONDUCTANCE(cur_gap_type, l_ref_pos,l_ref_data) > 0)
				{
					//
					l_ref_pos.SetSize(CFG__TEST_LIST);
					l_ref_data.SetSize(CFG__TEST_LIST);

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						aCH_PARA__VLV_POS_LIST[i]->Set__DATA(l_ref_pos[i]);
						aCH_PARA__VLV_REF_LIST[i]->Set__DATA(l_ref_data[i]);
					}

					//
					{
						CString str_data;
						CString add_data;

						double x_value = 0.0;
						double y_value = 0.0;

						for(i=0;i<CFG__TEST_LIST;i++)	
						{
							aCH_PARA__VLV_POS_LIST[i]->Get__DATA(var_data);
							x_value = atof(var_data);

							aCH_PARA__VLV_REF_LIST[i]->Get__DATA(var_data);
							y_value = atof(var_data);

							add_data.Format("%.3f/%.3f,", x_value,y_value);
							str_data += add_data;
						}

						sCH__REF_STRING->Set__DATA(str_data);
					}
				}
			}
		}

		// ...
		{
			dCH_PARA__TEST_GAS_TYPE->Get__DATA(var_data);
			int db_index = Get__Gas_Type_Index(var_data);

			if((db_index >= 0)
				&& (db_index <  iSIZE__OBJ_MFCx))
			{
				sEXT_CH__PARA_MFCx_GAS_NAME[db_index]->Get__DATA(var_data);
				sCH__CUR_TEST_GAS_NAME->Set__DATA(var_data);
			}
			else
			{
				sCH__CUR_TEST_GAS_NAME->Set__DATA("");
			}
		}

		// ...
		{
			if(sCH__RESULT_SAVE_FLAG->Check__DATA(STR__YES) > 0)
			{
				sCH__RESULT_SAVE_FLAG->Set__DATA("");

				// ...
				{
					sCH__RESULT_NEW_STRING->Get__DATA(var_data);
					sCH__RESULT_CUR_STRING->Set__DATA(var_data);

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						sCH_NEW__CONDUCT_RESULT[i]->Get__DATA(var_data);
						sCH_PARA__CONDUCT_RESULT[i]->Set__DATA(var_data);
					}
				}

				// ...
				{
					SCX__SEQ_INFO x_seq_info;

					var_data = x_seq_info->Get__DATE_TIME_STRING();
					sCH__RESULT_SAVE_DATE->Set__DATA(var_data);
				}
			}
		}

		// ...
		{
			int cal_flag = -1;

			if(sCH__SIM_MOVE_CHECK_FLAG->Check__DATA(STR__YES) > 0)
			{
				sCH__SIM_MOVE_CHECK_FLAG->Set__DATA("");

				cal_flag = 1;
			}
			if(aCH__SIM_MOVE_OFFSET->Check__DATA(pre__move_offset) < 0)
			{
				aCH__SIM_MOVE_OFFSET->Get__DATA(pre__move_offset);

				cal_flag = 1;
			}
			if(dCH__SIM_MOVE_LOOKUP->Check__DATA(pre__move_lookup) < 0)
			{
				dCH__SIM_MOVE_LOOKUP->Get__DATA(pre__move_lookup);

				cal_flag = 1;
			}
			if(dCH__SIM_MOVE_DATA_TYPE->Check__DATA(pre__data_type) < 0)
			{
				dCH__SIM_MOVE_DATA_TYPE->Get__DATA(pre__data_type);

				cal_flag = 1;
			}

			if(cal_flag > 0)
			{
				Fnc__SIM_MOVE_CAL(p_variable,p_alarm);
			}
		}

		// ...
		{
			int cal_flag = -1;

			if(sCH__SIM_MOVE_SCAN_FLAG->Check__DATA(STR__YES) > 0)
			{
				sCH__SIM_MOVE_SCAN_FLAG->Set__DATA("");

				cal_flag = 1;
			}

			if(cal_flag > 0)
			{
				Fnc__SIM_SCAN_CAL(p_variable,p_alarm);

				// ...
				{
					aCH__SIM_MOVE_OFFSET->Get__DATA(pre__move_offset);
					dCH__SIM_MOVE_LOOKUP->Get__DATA(pre__move_lookup);
					dCH__SIM_MOVE_DATA_TYPE->Get__DATA(pre__data_type);
				}
			}
		}
	}
}

int  CObj__WAP_POS_CONDUCT::
Get__Gas_Type_Index(const CString& str_gas_type)
{
	CString str_name;
	int i;

	for(i=0;i<CFG__MFC_SIZE;i++)
	{
		str_name.Format("GAS%002d", i+1);

		if(str_name.CompareNoCase(str_gas_type) == 0)
		{
			return (i);
		}
	}

	return -1;
}

int  CObj__WAP_POS_CONDUCT::
Get__REF_CONDUCTANCE(const CString& gap_type,
					 CStringArray& l_ref_pos,
					 CStringArray& l_ref_data)
{
	// ...
	{
		l_ref_pos.RemoveAll();
		l_ref_data.RemoveAll();
	}

	if(gap_type.CompareNoCase(GAP_TYPE__2_0) == 0)
	{
		// 1.
		l_ref_pos.Add("0");
		l_ref_data.Add("37.93");

		// 2.
		l_ref_pos.Add("300");
		l_ref_data.Add("28.53");

		// 3.
		l_ref_pos.Add("350");
		l_ref_data.Add("25.93");

		// 4.
		l_ref_pos.Add("400");
		l_ref_data.Add("22.99");

		// 5.
		l_ref_pos.Add("450");
		l_ref_data.Add("19.71");

		// 6.
		l_ref_pos.Add("500");
		l_ref_data.Add("16.24");

		// 7.
		l_ref_pos.Add("550");
		l_ref_data.Add("13.01");

		// 8.
		l_ref_pos.Add("600");
		l_ref_data.Add("10.98");

		// 9. 
		l_ref_pos.Add("650");
		l_ref_data.Add("9.25");

		// 10.
		l_ref_pos.Add("680");
		l_ref_data.Add("8.57");

		// 11.
		l_ref_pos.Add("710");
		l_ref_data.Add("7.56");

		// 12.
		l_ref_pos.Add("740");
		l_ref_data.Add("6.7");

		// 13.
		l_ref_pos.Add("760");
		l_ref_data.Add("6.1");

		// 14.
		l_ref_pos.Add("780");
		l_ref_data.Add("5.04");

		// 15.
		l_ref_pos.Add("800");
		l_ref_data.Add("3.8");

		// 16.
		l_ref_pos.Add("820");
		l_ref_data.Add("2.63");

		// 17.
		l_ref_pos.Add("840");
		l_ref_data.Add("2.284");

		// 18.
		l_ref_pos.Add("860");
		l_ref_data.Add("2.275");

		// 19.
		l_ref_pos.Add("900");
		l_ref_data.Add("2.267");

		// 20.
		l_ref_pos.Add("1000");
		l_ref_data.Add("2.261");

		return 1;
	}

	if(gap_type.CompareNoCase(GAP_TYPE__2_34) == 0)
	{
		// 0. 
		l_ref_pos.Add("0");
		l_ref_data.Add("41.91");

		// 1.
		l_ref_pos.Add("300");
		l_ref_data.Add("28.83");

		// 2.
		l_ref_pos.Add("350");
		l_ref_data.Add("25.55");

		// 3.
		l_ref_pos.Add("400");
		l_ref_data.Add("22.03");

		// 4.
		l_ref_pos.Add("450");
		l_ref_data.Add("18.44");

		// 5.
		l_ref_pos.Add("500");
		l_ref_data.Add("15.37");

		// 6.
		l_ref_pos.Add("550");
		l_ref_data.Add("13.53");

		// 7.
		l_ref_pos.Add("600");
		l_ref_data.Add("11.93");

		// 8.
		l_ref_pos.Add("650");
		l_ref_data.Add("10.58");

		// 9.
		l_ref_pos.Add("700");
		l_ref_data.Add("8.81");

		// 10.
		l_ref_pos.Add("740");
		l_ref_data.Add("7.77");

		// 11.
		l_ref_pos.Add("780");
		l_ref_data.Add("6.63");

		// 12.
		l_ref_pos.Add("800");
		l_ref_data.Add("5.61");

		// 13. 
		l_ref_pos.Add("820");
		l_ref_data.Add("4.44");

		// 14.
		l_ref_pos.Add("840");
		l_ref_data.Add("3.31");

		// 15.
		l_ref_pos.Add("860");
		l_ref_data.Add("2.73");

		// 16.
		l_ref_pos.Add("880");
		l_ref_data.Add("2.691");

		// 17.
		l_ref_pos.Add("900");
		l_ref_data.Add("2.69");

		// 18.
		l_ref_pos.Add("920");
		l_ref_data.Add("2.68");

		// 19.
		l_ref_pos.Add("1000");
		l_ref_data.Add("2.67");

		return 1;
	}

	if(gap_type.CompareNoCase(GAP_TYPE__2_5) == 0)
	{
		// 0. 
		l_ref_pos.Add("0");
		l_ref_data.Add("42.0375");

		// 1.
		l_ref_pos.Add("300");
		l_ref_data.Add("27.2197");

		// 2.
		l_ref_pos.Add("350");
		l_ref_data.Add("23.7769");

		// 3.
		l_ref_pos.Add("400");
		l_ref_data.Add("20.1657");

		// 4.
		l_ref_pos.Add("450");
		l_ref_data.Add("16.7156");

		// 5.
		l_ref_pos.Add("500");
		l_ref_data.Add("14.0639");

		// 6.
		l_ref_pos.Add("550");
		l_ref_data.Add("12.329");

		// 7.
		l_ref_pos.Add("600");
		l_ref_data.Add("10.8735");

		// 8.
		l_ref_pos.Add("650");
		l_ref_data.Add("9.34852");

		// 9.
		l_ref_pos.Add("700");
		l_ref_data.Add("7.84367");

		// 10.
		l_ref_pos.Add("740");
		l_ref_data.Add("6.81173");

		// 11.
		l_ref_pos.Add("780");
		l_ref_data.Add("5.56263");

		// 12.
		l_ref_pos.Add("800");
		l_ref_data.Add("4.67929");

		// 13. 
		l_ref_pos.Add("820");
		l_ref_data.Add("3.84009");

		// 14.
		l_ref_pos.Add("840");
		l_ref_data.Add("2.97303");

		// 15.
		l_ref_pos.Add("860");
		l_ref_data.Add("2.84623");

		// 16.
		l_ref_pos.Add("880");
		l_ref_data.Add("2.83621");

		// 17.
		l_ref_pos.Add("900");
		l_ref_data.Add("2.82623");

		// 18.
		l_ref_pos.Add("920");
		l_ref_data.Add("2.8121");

		// 19.
		l_ref_pos.Add("1000");
		l_ref_data.Add("2.812");

		return 1;
	}

	return -1;
}
