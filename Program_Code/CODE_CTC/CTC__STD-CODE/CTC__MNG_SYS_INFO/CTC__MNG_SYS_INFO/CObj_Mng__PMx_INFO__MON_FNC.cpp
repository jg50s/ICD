#include "StdAfx.h"
#include "CObj_Mng__PMx_INFO.h"


// ...
void CObj_Mng__PMx_INFO
::Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	SCX__TIMER_CTRL x_timer_ctrl;
	int timer_count = 0;
	int cur_id = -1;

	CString str_data;
	int i;

	while(1)
	{
		x_timer_ctrl->WAIT(0.1);

		// ...
		{
			timer_count++;

			if(timer_count >= 10)
			{
				timer_count = 0;
			}
		}

		// ...
		{
			for(i=0;i<iPMC_SIZE;i++)
			{
				if(xEXT_CH__PMx_USE_FLAG[i]->Check__DATA(STR__ENABLE) > 0)
				{
					sCH__PMx_CTRL__LOCK_FLAG[i]->Set__DATA("");

					if(cur_id < 0)
					{
						cur_id = i + 1;

						str_data.Format("%1d",cur_id);
						sCH__PMx_CTRL__SEL_ID->Set__DATA(str_data);
					}
				}
				else
				{
					sCH__PMx_CTRL__LOCK_FLAG[i]->Set__DATA(STR__YES);
				}
			}
		}

		if(timer_count % 5 == 0)
		{
			sCH__PMx_CTRL__SEL_ID->Get__DATA(str_data);
			cur_id = atoi(str_data);

			if((cur_id > 0) && (cur_id <= iPMC_SIZE))
			{
				int db_index = cur_id - 1;

				// PROCESS INFO : UPDATE ...
				{
					sEXT_CH__PMC_PROC_LOTID[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_LOTID->Set__DATA(str_data);

					sEXT_CH__PMC_PROC_RECIPEID[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_RECIPEID->Set__DATA(str_data);

					sEXT_CH__PMC_PROC_CUR_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_CUR_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_PROC_TOTAL_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_TOTAL_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_PROC_CUR_STEP[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_CUR_STEP->Set__DATA(str_data);

					sEXT_CH__PMC_PROC_TOTAL_STEP[db_index]->Get__DATA(str_data);
					sCH__PMC_PROC_TOTAL_STEP->Set__DATA(str_data);

					//
					sEXT_CH__PMC_STEP_CUR_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_CUR_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_TOTAL_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_TOTAL_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_CUR_NAME[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_CUR_NAME->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_CUR_TYPE[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_CUR_TYPE->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_EPD_DETECT_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_EPD_DETECT_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_EPD_OVERETCH_TIME[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_EPD_OVERETCH_TIME->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_EPD_OVERETCH_PERCENT[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_EPD_OVERETCH_PERCENT->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_OBJ_MAIN_MSG[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_OBJ_MAIN_MSG->Set__DATA(str_data);

					sEXT_CH__PMC_STEP_OBJ_SUB_MSG[db_index]->Get__DATA(str_data);
					sCH__PMC_STEP_OBJ_SUB_MSG->Set__DATA(str_data);
				}

				// SYSTEM INFO : UPDATE ...
				{
					sEXT_CH__PMC_SYS_OBJ_STATUS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_OBJ_STATUS->Set__DATA(str_data);

					//
					sEXT_CH__PMC_SYS_LIFT_PIN_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_LIFT_PIN_STS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_CHUCK_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_CHUCK_STS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SLIT_VLV_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SLIT_VLV_STS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_PRC_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_PRC_STS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SLOT01_STATUS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SLOT01_STATUS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_PRESSURE_STATUS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_PRESSURE_STATUS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_PRESSURE_VALUE[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_PRESSURE_VALUE->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_RF_ON_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_RF_ON_STS->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_WAP_CUR_POS_STS[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_WAP_CUR_POS_STS->Set__DATA(str_data);

					//
					sEXT_CH__PMC_SYS_SENSOR_CHM_BALLAST[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_CHM_BALLAST->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_PIN_UP[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_PIN_UP->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_PIN_MIDDLE[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_PIN_MIDDLE->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_PIN_DOWN[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_PIN_DOWN->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_ATM[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_ATM->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_VAC[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_VAC->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_500mTorr[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_500mTorr->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_SENSOR_100mTorr[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_SENSOR_100mTorr->Set__DATA(str_data);

					//
					sEXT_CH__PMC_SYS_APC_CUR_PRESSURE_mTORR[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_APC_CUR_PRESSURE_mTORR->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_APC_CUR_POSITION_GET[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_APC_CUR_POSITION_GET->Set__DATA(str_data);

					sEXT_CH__PMC_SYS_APC_CUR_POSITION_PER[db_index]->Get__DATA(str_data);
					sCH__PMC_SYS_APC_CUR_POSITION_PER->Set__DATA(str_data);
				}

				// PART ITEM ...
				{
					// MFC ITEM ...
					for(i=0;i<CFG__MFC_SIZE;i++)
					{
						sEXT_CH__PMC_PART_MFC_NAME[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MFC_NAME[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MFC_FLOW_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MFC_FLOW_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MFC_FLOW_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MFC_FLOW_GET[i]->Set__DATA(str_data);
					}

					// RF ITEM ...
					{
						sEXT_CH__PMC_PART_RF_AC_CONTACTOR_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_RF_AC_CONTACTOR_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RF_AC_CONTACTOR_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_RF_AC_CONTACTOR_GET->Set__DATA(str_data);
					}

					for(i=0;i<CFG__RF_SIZE;i++)
					{
						sEXT_CH__PMC_PART_RFx_ON_STATUS_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_ON_STATUS_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_ON_STATUS_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_ON_STATUS_GET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_POWER_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_POWER_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_RAMP_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_RAMP_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_FORWARD_POWER_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_FORWARD_POWER_GET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_REFLECT_POWER_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_REFLECT_POWER_GET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_MONITRING_STATUS[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_MONITRING_STATUS[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_FREQUENCY_START_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_FREQUENCY_START_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_FREQUENCY_POWER_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_RFx_FREQUENCY_POWER_GET[i]->Set__DATA(str_data);
					}

					// MATCHER ITEM ...
					for(i=0;i<CFG__RF_SIZE;i++)
					{
						sEXT_CH__PMC_PART_MATx_ON_STATUS[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MATx_ON_STATUS[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MATx_TUNE_STATUS[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MATx_TUNE_STATUS[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MATx_CONTROL_MODE[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MATx_CONTROL_MODE[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MATx_CUR_LOAD_POS[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MATx_CUR_LOAD_POS[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_MATx_CUR_TUNE_POS[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_MATx_CUR_TUNE_POS[i]->Set__DATA(str_data);
					}

					// WAP ITEM ...
					{
						sEXT_CH__PMC_PART_WAP_POSITION_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_WAP_POSITION_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_WAP_POSITION_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_WAP_POSITION_GET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_WAP_PRESSURE_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_WAP_PRESSURE_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_WAP_PRESSURE_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_WAP_PRESSURE_GET->Set__DATA(str_data);
					}

					// TEMPERATURE ITEM ...
					{
						sEXT_CH__PMC_PART_TOP_CHILLER_TEMP_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_TOP_CHILLER_TEMP_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_TOP_CHILLER_TEMP_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_TOP_CHILLER_TEMP_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_ESC_TEMP_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_TEMP_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ESC_TEMP_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_TEMP_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_TOP_PLATE_TEMP_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_TOP_PLATE_TEMP_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_TOP_PLATE_TEMP_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_TOP_PLATE_TEMP_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_ANAFAZER_TOP_TEMP_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ANAFAZER_TOP_TEMP_GET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ANAFAZER_TOP_BOTTOM_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ANAFAZER_TOP_BOTTOM_GET->Set__DATA(str_data);
					}

					// ESC ...
					{
						sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_TOTAL_VOLT_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_TOTAL_VOLT_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_ESC_BIAS_VOLT_SET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_BIAS_VOLT_SET->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ESC_BIAS_VOLT_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_BIAS_VOLT_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_ESC_COOLANT_GET[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_COOLANT_GET->Set__DATA(str_data);

						//
						sEXT_CH__PMC_PART_ESC_POWER_ON_STATUS[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_POWER_ON_STATUS->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ESC_REVERSE_POLARITY_STATUS[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_REVERSE_POLARITY_STATUS->Set__DATA(str_data);

						sEXT_CH__PMC_PART_ESC_COOLANT_FLOW_STATUS[db_index]->Get__DATA(str_data);
						sCH__PMC_PART_ESC_COOLANT_FLOW_STATUS->Set__DATA(str_data);
					}

					// He Inner / Outer - ITEM ...
					for(i=0;i<CFG__He_SIZE;i++)
					{
						sEXT_CH__PMC_PART_He_CTRL_PRESSURE_SET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_He_CTRL_PRESSURE_SET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_He_CTRL_PRESSURE_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_He_CTRL_PRESSURE_GET[i]->Set__DATA(str_data);

						sEXT_CH__PMC_PART_He_CTRL_FLOW_GET[db_index][i]->Get__DATA(str_data);
						sCH__PMC_PART_He_CTRL_FLOW_GET[i]->Set__DATA(str_data);	
					}
				}
			}
			else
			{
				// PROCESS INFO : INIT ...
				{
					sCH__PMC_PROC_LOTID->Set__DATA("");
					sCH__PMC_PROC_RECIPEID->Set__DATA("");
					sCH__PMC_PROC_CUR_TIME->Set__DATA("");
					sCH__PMC_PROC_TOTAL_TIME->Set__DATA("");
					sCH__PMC_PROC_CUR_STEP->Set__DATA("");
					sCH__PMC_PROC_TOTAL_STEP->Set__DATA("");

					//
					sCH__PMC_STEP_CUR_TIME->Set__DATA("");
					sCH__PMC_STEP_TOTAL_TIME->Set__DATA("");
					sCH__PMC_STEP_CUR_NAME->Set__DATA("");
					sCH__PMC_STEP_CUR_TYPE->Set__DATA("");
					sCH__PMC_STEP_EPD_DETECT_TIME->Set__DATA("");
					sCH__PMC_STEP_EPD_OVERETCH_TIME->Set__DATA("");
					sCH__PMC_STEP_EPD_OVERETCH_PERCENT->Set__DATA("");
					sCH__PMC_STEP_OBJ_MAIN_MSG->Set__DATA("");
					sCH__PMC_STEP_OBJ_SUB_MSG->Set__DATA("");
				}

				// SYSTEM INFO : INIT ...
				{
					sCH__PMC_SYS_OBJ_STATUS->Set__DATA("");

					sCH__PMC_SYS_LIFT_PIN_STS->Set__DATA("");
					sCH__PMC_SYS_CHUCK_STS->Set__DATA("");
					sCH__PMC_SYS_SLIT_VLV_STS->Set__DATA("");
					sCH__PMC_SYS_PRC_STS->Set__DATA("");
					sCH__PMC_SYS_SLOT01_STATUS->Set__DATA("");
					sCH__PMC_SYS_PRESSURE_STATUS->Set__DATA("");
					sCH__PMC_SYS_PRESSURE_VALUE->Set__DATA("");
					sCH__PMC_SYS_RF_ON_STS->Set__DATA("");
					sCH__PMC_SYS_WAP_CUR_POS_STS->Set__DATA("");

					sCH__PMC_SYS_SENSOR_CHM_BALLAST->Set__DATA("");
					sCH__PMC_SYS_SENSOR_PIN_UP->Set__DATA("");
					sCH__PMC_SYS_SENSOR_PIN_MIDDLE->Set__DATA("");
					sCH__PMC_SYS_SENSOR_PIN_DOWN->Set__DATA("");
					sCH__PMC_SYS_SENSOR_ATM->Set__DATA("");
					sCH__PMC_SYS_SENSOR_VAC->Set__DATA("");
					sCH__PMC_SYS_SENSOR_500mTorr->Set__DATA("");
					sCH__PMC_SYS_SENSOR_100mTorr->Set__DATA("");

					sCH__PMC_SYS_APC_CUR_PRESSURE_mTORR->Set__DATA("");
					sCH__PMC_SYS_APC_CUR_POSITION_GET->Set__DATA("");
					sCH__PMC_SYS_APC_CUR_POSITION_PER->Set__DATA("");
				}

				// PART ITEM ...
				{
					// MFC ITEM ...
					for(i=0;i<CFG__MFC_SIZE;i++)
					{
						sCH__PMC_PART_MFC_NAME[i]->Set__DATA("");
						sCH__PMC_PART_MFC_FLOW_SET[i]->Set__DATA("");
						sCH__PMC_PART_MFC_FLOW_GET[i]->Set__DATA("");
					}

					// RF ITEM ...
					{
						sCH__PMC_PART_RF_AC_CONTACTOR_SET->Set__DATA("");
						sCH__PMC_PART_RF_AC_CONTACTOR_GET->Set__DATA("");
					}

					for(i=0;i<CFG__RF_SIZE;i++)
					{
						sCH__PMC_PART_RFx_ON_STATUS_SET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_ON_STATUS_GET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_POWER_SET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_RAMP_SET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_FORWARD_POWER_GET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_REFLECT_POWER_GET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_MONITRING_STATUS[i]->Set__DATA("");
						sCH__PMC_PART_RFx_FREQUENCY_START_SET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_FREQUENCY_POWER_SET[i]->Set__DATA("");
						sCH__PMC_PART_RFx_FREQUENCY_POWER_GET[i]->Set__DATA("");
					}

					// MATCHER ITEM ...
					for(i=0;i<CFG__RF_SIZE;i++)
					{
						sCH__PMC_PART_MATx_ON_STATUS[i]->Set__DATA("");
						sCH__PMC_PART_MATx_TUNE_STATUS[i]->Set__DATA("");
						sCH__PMC_PART_MATx_CONTROL_MODE[i]->Set__DATA("");
						sCH__PMC_PART_MATx_CUR_LOAD_POS[i]->Set__DATA("");
						sCH__PMC_PART_MATx_CUR_TUNE_POS[i]->Set__DATA("");
					}

					// WAP ITEM ...
					{
						sCH__PMC_PART_WAP_POSITION_SET->Set__DATA("");
						sCH__PMC_PART_WAP_POSITION_GET->Set__DATA("");
						sCH__PMC_PART_WAP_PRESSURE_SET->Set__DATA("");
						sCH__PMC_PART_WAP_PRESSURE_GET->Set__DATA("");
					}

					// TEMPERATURE ITEM ...
					{
						sCH__PMC_PART_TOP_CHILLER_TEMP_SET->Set__DATA("");
						sCH__PMC_PART_TOP_CHILLER_TEMP_GET->Set__DATA("");

						sCH__PMC_PART_ESC_TEMP_SET->Set__DATA("");
						sCH__PMC_PART_ESC_TEMP_GET->Set__DATA("");

						sCH__PMC_PART_TOP_PLATE_TEMP_SET->Set__DATA("");
						sCH__PMC_PART_TOP_PLATE_TEMP_GET->Set__DATA("");

						sCH__PMC_PART_ANAFAZER_TOP_TEMP_GET->Set__DATA("");
						sCH__PMC_PART_ANAFAZER_TOP_BOTTOM_GET->Set__DATA("");
					}

					// ESC ...
					{
						sCH__PMC_PART_ESC_TOTAL_VOLT_SET->Set__DATA("");
						sCH__PMC_PART_ESC_TOTAL_VOLT_GET->Set__DATA("");

						sCH__PMC_PART_ESC_BIAS_VOLT_SET->Set__DATA("");
						sCH__PMC_PART_ESC_BIAS_VOLT_GET->Set__DATA("");

						sCH__PMC_PART_ESC_COOLANT_GET->Set__DATA("");

						sCH__PMC_PART_ESC_POWER_ON_STATUS->Set__DATA("");
						sCH__PMC_PART_ESC_REVERSE_POLARITY_STATUS->Set__DATA("");
						sCH__PMC_PART_ESC_COOLANT_FLOW_STATUS->Set__DATA("");
					}

					// He Inner / Outer - ITEM ...
					for(i=0;i<CFG__He_SIZE;i++)
					{
						sCH__PMC_PART_He_CTRL_PRESSURE_SET[i]->Set__DATA("");
						sCH__PMC_PART_He_CTRL_PRESSURE_GET[i]->Set__DATA("");
						sCH__PMC_PART_He_CTRL_FLOW_GET[i]->Set__DATA("");	
					}
				}
			}
		}

		// ...
	}
}
