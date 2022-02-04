#include "StdAfx.h"
#include "CObj__MFC_FLOW_CHECK.h"
#include "CObj__MFC_FLOW_CHECK__DEF.h"

#include "Macro_Function.h"


// ...
void CObj__MFC_FLOW_CHECK::
Mon__STATUS_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	int pre__view_index = -1;
	
	CString pre__mfc_set_mode;
	CString var_data;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iPRC_FLAG > 0)
		{
			sCH_INFO__LIST_SEL_REQ->Set__DATA("");
		}
		else
		{
			sCH_INFO__LIST_SEL_REQ->Get__DATA(var_data);
			sCH_INFO__LIST_SEL_REQ->Set__DATA("");

			if(var_data.CompareNoCase(STR__USER_REQ) == 0)
			{
				sCH_INFO__LIST_SEL_STS->Set__DATA(STR__USER);
			}
			else if(var_data.CompareNoCase(STR__ALL_REQ) == 0)
			{
				sCH_INFO__LIST_SEL_STS->Set__DATA(STR__ALL);

				for(i=0;i<CFG__MFC_SIZE;i++)
				{
					dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__YES);
				}
			}
			else if(var_data.CompareNoCase(STR__ODD_REQ) == 0)
			{
				sCH_INFO__LIST_SEL_STS->Set__DATA(STR__ODD);

				for(i=0;i<CFG__MFC_SIZE;i++)
				{
					if(i % 2 == 0)
					{
						dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__NO);
					}
					else
					{
						dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__YES);
					}
				}
			}
			else if(var_data.CompareNoCase(STR__EVEN_REQ) == 0)
			{
				sCH_INFO__LIST_SEL_STS->Set__DATA(STR__EVEN);

				for(i=0;i<CFG__MFC_SIZE;i++)
				{
					if(i % 2 == 0)
					{
						dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__YES);
					}
					else
					{
						dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__NO);
					}
				}
			}
			else if(var_data.CompareNoCase(STR__EMPTY_REQ) == 0)
			{
				sCH_INFO__LIST_SEL_STS->Set__DATA(STR__EMPTY);

				for(i=0;i<CFG__MFC_SIZE;i++)
				{
					dCH_APP__GAS_USE_FLAG[i]->Set__DATA(STR__NO);
				}
			}
		}

		if(iPRC_FLAG > 0)
		{
			for(i=0;i<CFG__MFC_SIZE;i++)
			{
				sCH_APP__GAS_VIEW_FLAG[i]->Set__DATA("");
			}
		}
		else
		{
			int check_index = -1;

			for(i=0;i<CFG__MFC_SIZE;i++)
			{
				if(sCH_APP__GAS_VIEW_FLAG[i]->Check__DATA(STR__YES_REQ) < 0)
				{
					continue;
				}

				sCH_APP__GAS_VIEW_FLAG[i]->Set__DATA(STR__YES);
				check_index = i;
				break;
			}

			if(pre__view_index != check_index)
			{
				pre__view_index = check_index;
				CString szRun_Mode_Data;

				if(check_index >= 0)
				{
					for(i=0;i<CFG__MFC_SIZE;i++)
					{
						if(check_index != i)
						{
							sCH_APP__GAS_VIEW_FLAG[i]->Set__DATA("");
						}
					}

					// RESULT .....
					{
						for(i=0;i<CFG__GAS_FLOW_LIST;i++)
						{
							sCH_APP__GAS_RUN_MODE[check_index]->Get__DATA(szRun_Mode_Data);
							sCH_PARA__RUN_MODE_CHECK->Set__DATA(szRun_Mode_Data);	

							sCH_RESULT__CURRENT_FLOW[check_index][i]->Get__DATA(var_data);
							sCH_PARA__GAS_CURRENT_FLOW[i]->Set__DATA(var_data);

							sCH_RESULT__CURRENT_PRESSURE[check_index][i]->Get__DATA(var_data);
							sCH_PARA__CURRENT_PRESSURE[i]->Set__DATA(var_data);

							sCH_RESULT__CAL_ERROR[check_index][i]->Get__DATA(var_data);
							sCH_PARA__CAL_ERROR_RESULT[i]->Set__DATA(var_data);
						}

						sCH_RESULT__CHECK_DATE[check_index]->Get__DATA(var_data);
						sCH_PARA__CHECK_DATE->Set__DATA(var_data);

						sCH_RESULT__CHECK_TIME[check_index]->Get__DATA(var_data);
						sCH_PARA__CHECK_TIME->Set__DATA(var_data);

						//
						var_data.Format("GAS%002d",check_index+1);
						sCH_INFO__CUR_GAS_ID->Set__DATA(var_data);

						if(check_index < iSIZE__OBJ_MFCx)
						{
							sEXT_CH__PARA_MFCx_GAS_NAME[check_index]->Get__DATA(var_data);
							sCH_INFO__CUR_GAS_NAME->Set__DATA(var_data);

							//
							CString str_min;
							CString str_max;

							aEXT_CH__PARA_MFCx_SET_FLOW[check_index]->Get__MIN_MAX_INFO(str_min,str_max);

							sCH_INFO__CUR_GAS_MIN->Set__DATA(str_min);
							sCH_INFO__CUR_GAS_MAX->Set__DATA(str_max);

							double min_value = atof(str_min);
							double max_value = atof(str_max);
							int k;

							for(k=0;k<CFG__GAS_FLOW_LIST;k++)
							{
								aCH_PARA__GAS_SET_USER_FLOW[k]->Change__MIN_MAX_DEC(min_value,max_value,-1);
							}
						}
						else
						{
							sCH_INFO__CUR_GAS_NAME->Set__DATA("");

							sCH_INFO__CUR_GAS_MIN->Set__DATA("");
							sCH_INFO__CUR_GAS_MAX->Set__DATA("");
						}
					}
				}
			}
		}

		// ...
		{
			dCH_PARA__MFC_SETTING_MODE->Get__DATA(var_data);

			if(pre__mfc_set_mode != var_data)
			{
				pre__mfc_set_mode = var_data;

				if(var_data.CompareNoCase(STR__1_PERCENT) == 0)
				{
					for(i=0;i<CFG__GAS_FLOW_LIST;i++)
					{
						var_data.Format("%.1f", 1.0*(i+1));	
						aCH_PARA__GAS_SET_AUTO_FLOW[i]->Set__DATA(var_data);
					}
				}
				else if(var_data.CompareNoCase(STR__5_PERCENT) == 0)
				{
					for(i=0;i<CFG__GAS_FLOW_LIST;i++)
					{
						var_data.Format("%.1f", 5.0*(i+1));	
						aCH_PARA__GAS_SET_AUTO_FLOW[i]->Set__DATA(var_data);
					}
				}
				else if(var_data.CompareNoCase(STR__10_PERCENT) == 0)
				{
					for(i=0;i<CFG__GAS_FLOW_LIST;i++)
					{
						var_data.Format("%.1f", 10.0*(i+1));	
						aCH_PARA__GAS_SET_AUTO_FLOW[i]->Set__DATA(var_data);
					}
				}
				else if(var_data.CompareNoCase(STR__YSK_PERCENT) == 0)
				{
					// SET VALUE 20 40 60 80 100
					for(i=0;i<CFG__GAS_FLOW_LIST;i++)
					{
						if (i<5)	var_data.Format("%.1f", 20.0*(i+1));
						else		var_data.Format("%.1f", 0*(i+1));

						aCH_PARA__GAS_SET_AUTO_FLOW[i]->Set__DATA(var_data);
					}
				}
				else
				{
					CString str_data = var_data;
					int check_percent; 

					if(Macro__Check_1Point(str_data,check_percent) > 0)
					{
						CString set_data;

						for(i=0;i<CFG__GAS_FLOW_LIST;i++)
						{
							if(i == 0)	set_data.Format("%.1f", 1.0*check_percent);
							else		set_data = "0.0";

							aCH_PARA__GAS_SET_AUTO_FLOW[i]->Set__DATA(set_data);
						}
					}
				}

				if(var_data.CompareNoCase(STR__USER_DEF) == 0)
				{
					sCH_INFO__SETPOINT_MODE->Set__DATA(var_data);
				}
				else
				{
					sCH_INFO__SETPOINT_MODE->Set__DATA(STR__PERCENT);
				}
			}
		}

		// ...
	}
}
