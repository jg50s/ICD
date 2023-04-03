#include "StdAfx.h"
#include "CObj__APC_POS_CONDUCT.h"

#include "CObj__APC_POS_CONDUCT__DEF.h"



// ...
void CObj__APC_POS_CONDUCT
::Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString pre__check_type;
	CString var_data;
	int i;

	bool active__chart_update = false;
	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)
		{
			loop_count = 1;
			active__chart_update = true;
		}


		// ...
		{
			int update_flag = -1;
			CString str__pre_type;

			if(dCH__CFG_CHECK_TYPE->Check__DATA(pre__check_type) < 0)
			{
				str__pre_type = pre__check_type;
				dCH__CFG_CHECK_TYPE->Get__DATA(pre__check_type);

				printf(" * Check Type - Change ... \n");

				update_flag = 1;
			}

			if(sCH__CHECK_TYPE_UPDATE_REQ->Check__DATA(STR__YES) > 0)
			{
				sCH__CHECK_TYPE_UPDATE_REQ->Set__DATA("");

				printf(" * Check Type - Update ... \n");

				update_flag = 1;
			}

			if(sCH__CHECK_TYPE_SAVE_REQ->Check__DATA(STR__YES) > 0)
			{
				sCH__CHECK_TYPE_SAVE_REQ->Set__DATA("");

				printf(" * Check Type - Save ... \n");

				Save__CHECK_TYPE(pre__check_type);	
			}

			if(sCH__CURRENT_REF_COPY_REQ->Check__DATA(STR__YES) > 0)
			{
				sCH__CURRENT_REF_COPY_REQ->Set__DATA("");

				printf(" * Copy (Current -> Ref.) ... \n");

				Copy__CURRENT_REF(pre__check_type);	
			}

			if(update_flag > 0)
			{
				if((pre__check_type.CompareNoCase(STR__Ar_80)       == 0)
				|| (pre__check_type.CompareNoCase(STR__N2_5PER)     == 0)
				|| (pre__check_type.CompareNoCase(STR__User_Define) == 0))
				{
					Update__CHECK_TYPE(pre__check_type, str__pre_type);	
					active__chart_update = false;
				}
			}
		}

		if(sCH__RESULT_SAVE_REQ->Check__DATA(STR__YES) > 0)
		{
			sCH__RESULT_SAVE_REQ->Set__DATA("");

			printf(" * Result_Save_Req : Start \n");

			for(i=0; i<CFG__TEST_LIST; i++)
			{					
				aCH_PARA__VLV_POS_LIST[i]->Get__DATA(var_data);
				sCH__CUR_VLV_POS_LIST[i]->Set__DATA(var_data);

				sCH_PARA__CONDUCT_RESULT[i]->Get__DATA(var_data);	
				sCH__CUR_CONDUCT_RESULT[i]->Set__DATA(var_data);
			}

			// ...
			{
				sCH_PARA__TEST_DATE->Get__DATA(var_data);
				sCH__CUR_TEST_DATE->Set__DATA(var_data);

				sCH_PARA__TEST_TIME->Get__DATA(var_data);
				sCH__CUR_TEST_TIME->Set__DATA(var_data);

				sCH__RESULT_STRING->Get__DATA(var_data);
				sCH__CUR_STRING->Set__DATA(var_data);
			}

			printf(" * Result_Save_Req : End \n");
		}

		if(sCH__RESULT_ERROR_RANGE_CHECK_REQ->Check__DATA(STR__YES) > 0)
		{
			sCH__RESULT_ERROR_RANGE_CHECK_REQ->Set__DATA("");

			// ...
			{
				CString err_msg;
				CString err_bff;

				double cur_value;
				double ref_value;

				int err_flag = -1;
				int i;

				// ...
				aCH__CFG_RESULT_ERROR_RANGE->Get__DATA(var_data);
				double cfg_err = atof(var_data);

				if(dCH__CFG_RESULT_ERROR_TYPE->Check__DATA(STR__NEW_REF) > 0)
				{
					err_msg = "New & Reference  -  Error Check \n";

					err_bff.Format("Result Error Range : (%.3f) \n", cfg_err);
					err_msg += err_bff;

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						sCH_PARA__CONDUCT_RESULT[i]->Get__DATA(var_data);
						cur_value = atof(var_data);

						aCH_PARA__VLV_REF_LIST[i]->Get__DATA(var_data);
						ref_value = atof(var_data);

						double diff_value = cur_value - ref_value;

						if((diff_value >  cfg_err)
							|| (diff_value < -cfg_err))
						{
							err_bff.Format("	%002d)   New(%.6f) : Ref.(%.6f) : Diff(%.6f) \n", i+1,cur_value,ref_value,diff_value);
							err_msg += err_bff;

							err_flag = 1;
						}
					}
				}
				else if(dCH__CFG_RESULT_ERROR_TYPE->Check__DATA(STR__NEW_CURRENT) > 0)
				{
					err_msg = "New & Current  -  Error Check \n";

					err_bff.Format("Result Error Range : (%.3f) \n", cfg_err);
					err_msg += err_bff;

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						sCH_PARA__CONDUCT_RESULT[i]->Get__DATA(var_data);
						cur_value = atof(var_data);

						sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
						ref_value = atof(var_data);

						double diff_value = cur_value - ref_value;

						if((diff_value >  cfg_err)
							|| (diff_value < -cfg_err))
						{
							err_bff.Format("	%002d)   New(%.6f) : Current.(%.6f) : Diff(%.6f) \n", i+1,cur_value,ref_value,diff_value);
							err_msg += err_bff;

							err_flag = 1;
						}
					}
				}
				else if(dCH__CFG_RESULT_ERROR_TYPE->Check__DATA(STR__CURRENT_REF) > 0)
				{
					err_msg = "Current & Reference -  Error Check \n";

					err_bff.Format("Result Error Range : (%.3f) \n", cfg_err);
					err_msg += err_bff;

					for(i=0;i<CFG__TEST_LIST;i++)
					{
						sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
						cur_value = atof(var_data);

						aCH_PARA__VLV_REF_LIST[i]->Get__DATA(var_data);
						ref_value = atof(var_data);

						double diff_value = cur_value - ref_value;

						if((diff_value >  cfg_err)
							|| (diff_value < -cfg_err))
						{
							err_bff.Format("	%002d)   New(%.6f) : Current.(%.6f) : Diff(%.6f) \n", i+1,cur_value,ref_value,diff_value);
							err_msg += err_bff;

							err_flag = 1;
						}
					}
				}

				if(err_flag > 0)
				{
					// ...
					{
						int alarm_id = ALID__VAC_CONDUCTANCE_CHECK_ERROR;
						CString r_act;

						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id,err_msg);
					}

					xCH__OBJ_ERROR_MSG->Set__DATA("Check : ERROR !");
				}
				else
				{
					xCH__OBJ_ERROR_MSG->Set__DATA("Check : OK !");
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
				sEXT_CH__MFCx_CFG_GAS_NAME[db_index]->Get__DATA(var_data);
				sCH__CUR_TEST_GAS_NAME->Set__DATA(var_data);

				double cfg_max = aEXT_CH__MFCx_CFG_GAS_MAX[db_index]->Get__VALUE();
				aCH_PARA__TEST_GAS_FLOW->Change__MIN_MAX_DEC(0, cfg_max, 0);
			}
			else
			{
				sCH__CUR_TEST_GAS_NAME->Set__DATA("");
			}
		}

		if(active__chart_update)
		{
			Update__REF_STRING();
		}
	}

	// ...
}

int  CObj__APC_POS_CONDUCT::
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


// ...
#define  POS_DATA__SET(P,D)			\
{									\
	var_data.Format("%1d", P);		\
	l_pos.Add(var_data);			\
	var_data.Format("%.6f", D);		\
	l_data.Add(var_data);			\
}

void CObj__APC_POS_CONDUCT::
Update__CHECK_TYPE(const CString& cur__check_type, const CString& pre__check_type)
{
	CStringArray l_pos;
	CStringArray l_data;

	CString var_data;

	if(cur__check_type.CompareNoCase(STR__Ar_80) == 0)
	{
		POS_DATA__SET(   0, 0.0      );		// 1
		POS_DATA__SET(  30, 0.785121 );		// 2
		POS_DATA__SET(  40, 0.877381 );		// 3
		POS_DATA__SET(  50, 1.08257  );		// 4
		POS_DATA__SET(  60, 1.49472  );		// 5
		POS_DATA__SET(  70, 2.20958  );		// 6
		POS_DATA__SET(  80, 3.26253  );		// 7
		POS_DATA__SET(  90, 4.48339  );		// 8
		POS_DATA__SET( 100, 5.9068   );		// 9
		POS_DATA__SET( 110, 7.56112  );		// 10

		POS_DATA__SET( 120,  9.14349 );		// 11
		POS_DATA__SET( 140, 12.5248  );		// 12
		POS_DATA__SET( 160, 15.6785  );		// 13
		POS_DATA__SET( 180, 18.154   );		// 14
		POS_DATA__SET( 200, 20.5603  );		// 15
		POS_DATA__SET( 250, 24.6145  );		// 16
		POS_DATA__SET( 300, 27.7989  );		// 17
		POS_DATA__SET( 400, 31.3195  );		// 18
		POS_DATA__SET( 600, 35.0929  );		// 19
		POS_DATA__SET(1000, 37.7186  );		// 19
	}
	else if(cur__check_type.CompareNoCase(STR__N2_5PER) == 0)
	{
		int limit = CFG__TEST_LIST;
		int i;

		for(i=0; i<limit; i++)
		{
			var_data.Format("%.0f", 50.0*(1+i));
			l_pos.Add(var_data);

			aCH_N2_5PER__VLV_REF_LIST[i]->Get__DATA(var_data);
			l_data.Add(var_data);
		}
	}
	else if(cur__check_type.CompareNoCase(STR__User_Define) == 0)
	{
		int limit = CFG__TEST_LIST;
		int i;

		for(i=0; i<limit; i++)
		{
			aCH_USER__VLV_POS_LIST[i]->Get__DATA(var_data);
			l_pos.Add(var_data);

			aCH_USER__VLV_REF_LIST[i]->Get__DATA(var_data);
			l_data.Add(var_data);
		}
	}

	// ...
	{
		int limit = l_pos.GetSize();
		if(limit > CFG__TEST_LIST)		limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			aCH_PARA__VLV_POS_LIST[i]->Set__DATA(l_pos[i]);
			aCH_PARA__VLV_REF_LIST[i]->Set__DATA(l_data[i]);
		}
	}

	if(pre__check_type.CompareNoCase(cur__check_type) == 0)
	{
		return;
	}

	// Pre_Type ...
	{
		int type_index = -1;

		if(pre__check_type.CompareNoCase(STR__Ar_80)   == 0)			type_index = _TEST_TYPE__INDEX_AR;
		if(pre__check_type.CompareNoCase(STR__N2_5PER) == 0)			type_index = _TEST_TYPE__INDEX_N2;
		if(pre__check_type.CompareNoCase(STR__User_Define) == 0)		type_index = _TEST_TYPE__INDEX_USER;

		// New & Current -> Type_DB
		if(type_index >= 0)
		{
			int limit = CFG__TEST_LIST;
			int i;

			// New -> Type_DB
			for(i=0; i<limit; i++)
			{
				sCH_PARA__CONDUCT_RESULT[i]->Get__DATA(var_data);
				sCH_PARA__CONDUCT_RESULT_OF_TYPE[type_index][i]->Set__DATA(var_data);
			}

			// Current -> Type_DB
			for(i=0; i<limit; i++)
			{
				sCH__CUR_VLV_POS_LIST[i]->Get__DATA(var_data);
				sCH__CUR_VLV_POS_LIST_OF_TYPE[type_index][i]->Set__DATA(var_data);

				sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
				sCH__CUR_CONDUCT_RESULT_OF_TYPE[type_index][i]->Set__DATA(var_data);
			}
		}
	}
	// Cur_Type ...
	{
		int type_index = -1;

		if(cur__check_type.CompareNoCase(STR__Ar_80)   == 0)			type_index = _TEST_TYPE__INDEX_AR;
		if(cur__check_type.CompareNoCase(STR__N2_5PER) == 0)			type_index = _TEST_TYPE__INDEX_N2;
		if(cur__check_type.CompareNoCase(STR__User_Define) == 0)		type_index = _TEST_TYPE__INDEX_USER;

		// Type_DB -> New & Current
		if(type_index >= 0)
		{
			int limit = CFG__TEST_LIST;
			int i;

			// Type_DB -> New
			for(int i=0; i<limit; i++)
			{
				sCH_PARA__CONDUCT_RESULT_OF_TYPE[type_index][i]->Get__DATA(var_data);
				sCH_PARA__CONDUCT_RESULT[i]->Set__DATA(var_data);
			}

			// Type_DB -> Current
			for(i=0; i<limit; i++)
			{
				sCH__CUR_VLV_POS_LIST_OF_TYPE[type_index][i]->Get__DATA(var_data);
				sCH__CUR_VLV_POS_LIST[i]->Set__DATA(var_data);

				sCH__CUR_CONDUCT_RESULT_OF_TYPE[type_index][i]->Get__DATA(var_data);
				sCH__CUR_CONDUCT_RESULT[i]->Set__DATA(var_data);
			}
		}
	}

	// Update.Chart ...
	{
		CString chart__new_data = "";
		CString chart__cur_data = "";

		// Now Result String ...
		{
			int i_limit = CFG__TEST_LIST;
			for(int i=0; i<i_limit; i++)
			{
				CString vlv_pos;
				CString vlv_data;

				aCH_PARA__VLV_POS_LIST[i]->Get__DATA(vlv_pos);
				sCH_PARA__CONDUCT_RESULT[i]->Get__DATA(vlv_data);

				CString add_data;
				add_data.Format("%.1f/%.1f,", atof(vlv_pos),atof(vlv_data));

				chart__new_data += add_data;
			}
		}
		// Now Current String ...
		{
			int i_limit = CFG__TEST_LIST;
			for(int i=0; i<i_limit; i++)
			{
				CString vlv_pos;
				CString vlv_data;

				sCH__CUR_VLV_POS_LIST[i]->Get__DATA(vlv_pos);
				sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(vlv_data);

				CString add_data;
				add_data.Format("%.1f/%.1f,", atof(vlv_pos),atof(vlv_data));

				chart__cur_data += add_data;
			}
		}

		sCH__RESULT_STRING->Set__DATA(chart__new_data);
		sCH__CUR_STRING->Set__DATA(chart__cur_data);

		Update__REF_STRING();
	}
}
void CObj__APC_POS_CONDUCT::
Update__REF_STRING()
{
	CString chart_data;
	CString add_data;

	for(int i=0; i<CFG__TEST_LIST; i++)	
	{
		double x_value = aCH_PARA__VLV_POS_LIST[i]->Get__VALUE();
		double y_value = aCH_PARA__VLV_REF_LIST[i]->Get__VALUE();

		add_data.Format("%.1f/%.1f,", x_value,y_value);
		chart_data += add_data;
	}

	sCH__REF_STRING->Set__DATA(chart_data);
}

void CObj__APC_POS_CONDUCT::
Save__CHECK_TYPE(const CString& str__check_type)
{
	CString var_data;

	if(str__check_type.CompareNoCase(STR__Ar_80) == 0)
	{
		return;
	}
	if(str__check_type.CompareNoCase(STR__N2_5PER) == 0)
	{
		int limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			aCH_PARA__VLV_REF_LIST[i]->Get__DATA(var_data);
			aCH_N2_5PER__VLV_REF_LIST[i]->Set__DATA(var_data);
		}
		return;
	}
	if(str__check_type.CompareNoCase(STR__User_Define) == 0)
	{
		int limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			aCH_PARA__VLV_POS_LIST[i]->Get__DATA(var_data);
			aCH_USER__VLV_POS_LIST[i]->Set__DATA(var_data);

			aCH_PARA__VLV_REF_LIST[i]->Get__DATA(var_data);
			aCH_USER__VLV_REF_LIST[i]->Set__DATA(var_data);
		}
		return;
	}
}
void CObj__APC_POS_CONDUCT::
Copy__CURRENT_REF(const CString& str__check_type)
{
	CString var_data;

	// ...
	int type_index = -1;

	if(str__check_type.CompareNoCase(STR__Ar_80)   == 0)			type_index = _TEST_TYPE__INDEX_AR;
	if(str__check_type.CompareNoCase(STR__N2_5PER) == 0)			type_index = _TEST_TYPE__INDEX_N2;
	if(str__check_type.CompareNoCase(STR__User_Define) == 0)		type_index = _TEST_TYPE__INDEX_USER;

	if(type_index >= 0)
	{
		int limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			sCH__CUR_VLV_POS_LIST[i]->Get__DATA(var_data);
			sCH__CUR_VLV_POS_LIST_OF_TYPE[type_index][i]->Set__DATA(var_data);

			sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
			sCH__CUR_CONDUCT_RESULT_OF_TYPE[type_index][i]->Set__DATA(var_data);

			aCH_PARA__VLV_REF_LIST[i]->Set__DATA(var_data);
		}
	}

	// ...
	if(str__check_type.CompareNoCase(STR__Ar_80) == 0)
	{
		return;
	}
	if(str__check_type.CompareNoCase(STR__N2_5PER) == 0)
	{
		int limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
			aCH_N2_5PER__VLV_REF_LIST[i]->Set__DATA(var_data);
		}
		return;
	}
	if(str__check_type.CompareNoCase(STR__User_Define) == 0)
	{
		int limit = CFG__TEST_LIST;

		for(int i=0; i<limit; i++)
		{
			sCH__CUR_VLV_POS_LIST[i]->Get__DATA(var_data);
			aCH_USER__VLV_POS_LIST[i]->Set__DATA(var_data);

			sCH__CUR_CONDUCT_RESULT[i]->Get__DATA(var_data);
			aCH_USER__VLV_REF_LIST[i]->Set__DATA(var_data);
		}
		return;
	}
}
