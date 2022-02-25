#include "StdAfx.h"
#include "CObj_Mng__SYSTEM_INFO_STD.h"


#define DEF__SYS_STS__PROCESS					1
#define DEF__SYS_STS__IDLE						2
#define DEF__SYS_STS__DOWN						3


// ...
int  CObj_Mng__SYSTEM_INFO_STD
::Mon__SYSTEM_INFO(CII_OBJECT__VARIABLE *p_variable)
{
	xSCH_MATERIAL_CTRL->Link__SERVICE_DB("");

	// ...
	SCX__ASYNC_TIMER_CTRL async__eqp_proc_time;
	SCX__ASYNC_TIMER_CTRL async__eqp_idle_time;
	SCX__ASYNC_TIMER_CTRL async__eqp_down_time;

	double max_up_sec = 24 * 60 * 60;
	double init_sec = 0;

	CString var_data;
	int cur_day;
	int cur_hour;
	int i_sts;
	int cur_system_sts = -1;

	// ...
	{
		sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC->Get__DATA(var_data);
		init_sec = atof(var_data);
		async__eqp_proc_time->Set__START_TIME(init_sec);

		sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC->Get__DATA(var_data);
		init_sec = atof(var_data);
		async__eqp_idle_time->Set__START_TIME(init_sec);

		sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC->Get__DATA(var_data);
		init_sec = atof(var_data);
		async__eqp_down_time->Set__START_TIME(init_sec);

		//
		async__eqp_proc_time->REGISTER__COUNT_CHANNEL_NAME(sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC->Get__CHANNEL_NAME());
		async__eqp_idle_time->REGISTER__COUNT_CHANNEL_NAME(sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC->Get__CHANNEL_NAME());
		async__eqp_down_time->REGISTER__COUNT_CHANNEL_NAME(sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC->Get__CHANNEL_NAME());

		//
		async__eqp_proc_time->START__COUNT_UP(max_up_sec);
		async__eqp_idle_time->START__COUNT_UP(max_up_sec);
		async__eqp_down_time->START__COUNT_UP(max_up_sec);

		async__eqp_proc_time->PAUSE();
		async__eqp_idle_time->PAUSE();
		async__eqp_down_time->PAUSE();
	}

	// ...
	{
		sCH__CUR_DAY->Get__DATA(var_data);
		cur_day = atoi(var_data);

		// ...
		CTime cur_time = CTime::GetCurrentTime();

		if(cur_day == cur_time.GetDay())
		{
			int db_index = DB__1th_INDEX;

			sCH__DAYx__TOTAL_LOT_COUNT[db_index]->Get__DATA(var_data);
			if(atoi(var_data) < 1)
			{
				sCH__DAYx__TOTAL_LOT_COUNT[db_index]->Set__DATA("0");
			}

			sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[db_index]->Get__DATA(var_data);
			if(atoi(var_data) < 1)
			{
				sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[db_index]->Set__DATA("0");
			}
		}
	}

	// ...
	{
		int db_index = DB__1th_INDEX;

		sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[db_index]->Set__DATA("00:00:00");
		sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[db_index]->Set__DATA("00:00:00");
		sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[db_index]->Set__DATA("00:00:00");
	}

	while(1)
	{
		MONITORING_TIMER_RETURN_INT(500,1);

		// ...
		CTime cur_time = CTime::GetCurrentTime();
		cur_hour = cur_time.GetHour();

		// ...
		{
			int db_index = DB__1th_INDEX;

			int port_id;
			int slot_id;
			CString lot_id;
			int cur_count;

			// PICK
			if(xSCH_MATERIAL_CTRL->Check__EVENT__PICK_From_LPx(port_id,slot_id,lot_id) > 0)
			{
				if(mRes__SYSTEM_LOTID.Check__LOTID_COUNT(lot_id) < 0)
				{
					sCH__DAYx__TOTAL_LOT_COUNT[db_index]->Get__DATA(var_data);

					cur_count = atoi(var_data) + 1;
					var_data.Format("%1d",cur_count);

					sCH__DAYx__TOTAL_LOT_COUNT[db_index]->Set__DATA(var_data);
				}
			}

			// PLACE
			if(xSCH_MATERIAL_CTRL->Check__EVENT__PLACE_To_LPx(port_id,slot_id,lot_id) > 0)
			{
				sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[db_index]->Get__DATA(var_data);

				cur_count = atoi(var_data) + 1;
				var_data.Format("%1d",cur_count);

				sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[db_index]->Set__DATA(var_data);

				// ...
				{
					if((cur_hour >= 0) && (cur_hour < CFG__HOUR_SIZE))
					{
						sCH__DAYx__HOURx_UPEH_RESULT[db_index][cur_hour]->Get__DATA(var_data);

						cur_count = atoi(var_data) + 1;
						var_data.Format("%1d", cur_count);

						sCH__DAYx__HOURx_UPEH_RESULT[db_index][cur_hour]->Set__DATA(var_data);
					}
				}
			}
		}

		// Alarm & Maint ...
		{
			i_sts = Check__ALARM_Or_MAINT();

			if((i_sts == 2)			// ALARM
			|| (i_sts == 1))		// MAINT
			{
				if(cur_system_sts != DEF__SYS_STS__DOWN)
				{
					cur_system_sts = DEF__SYS_STS__DOWN;

					async__eqp_down_time->RESUME();
					async__eqp_proc_time->PAUSE();
					async__eqp_idle_time->PAUSE();
				}
			}
			else
			{
				// Process & Idle ...
				i_sts = Check__PROCESS_Or_IDLE();

				switch(i_sts)
				{
					case 2:		// IDLE
						if(cur_system_sts != DEF__SYS_STS__IDLE)
						{
							cur_system_sts = DEF__SYS_STS__IDLE;

							async__eqp_idle_time->RESUME();
							async__eqp_proc_time->PAUSE();
							async__eqp_down_time->PAUSE();
						}
						break;

					case 1:		// PROCESS
						if(cur_system_sts != DEF__SYS_STS__PROCESS)
						{
							cur_system_sts = DEF__SYS_STS__PROCESS;

							async__eqp_proc_time->RESUME();	
							async__eqp_idle_time->PAUSE();
							async__eqp_down_time->PAUSE();
						}
						break;

					default:
						break;
				}
			}
		}

		// SEC -> FMT ...
		{
			int db_index = DB__1th_INDEX;

			int total_min;
			int total_sec;
			int i_hour;
			int i_min;
			int i_sec;

			//
			{
				sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC->Get__DATA(var_data);
				total_sec = atoi(var_data);

				total_min = total_sec / 60;
				i_sec  = total_sec % 60;
				i_min  = total_min % 60;
				i_hour = total_min / 60;

				var_data.Format("%002d:%002d:%002d", i_hour,i_min,i_sec);
				sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[db_index]->Set__DATA(var_data);
			}

			//
			{
				sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC->Get__DATA(var_data);
				total_sec = atoi(var_data);

				total_min = total_sec / 60;
				i_sec  = total_sec % 60;
				i_min  = total_min % 60;
				i_hour = total_min / 60;

				var_data.Format("%002d:%002d:%002d", i_hour,i_min,i_sec);
				sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[db_index]->Set__DATA(var_data);
			}

			//
			{
				sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC->Get__DATA(var_data);
				total_sec = atoi(var_data);

				total_min = total_sec / 60;
				i_sec  = total_sec % 60;
				i_min  = total_min % 60;
				i_hour = total_min / 60;

				var_data.Format("%002d:%002d:%002d", i_hour,i_min,i_sec);
				sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[db_index]->Set__DATA(var_data);
			}
		}

		// Data Backup ...
		{	
			// ...
			{
				var_data.Format("%002d", cur_hour);
				sCH__CUR_HOUR->Set__DATA(var_data);
			}

			if(cur_day != cur_time.GetDay())
			{
				// 2th -> 3th
				{
					// ...
					{
						sCH__DAYx__TOTAL_LOT_COUNT[DB__2th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_LOT_COUNT[DB__3th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[DB__2th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[DB__3th_INDEX]->Set__DATA(var_data);

						//
						sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[DB__2th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[DB__3th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[DB__2th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[DB__3th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[DB__2th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[DB__3th_INDEX]->Set__DATA(var_data);
					}

					// ...
					{
						int k;

						for(k=0; k<CFG__HOUR_SIZE; k++)
						{
							sCH__DAYx__HOURx_UPEH_RESULT[DB__2th_INDEX][k]->Get__DATA(var_data);
							sCH__DAYx__HOURx_UPEH_RESULT[DB__3th_INDEX][k]->Set__DATA(var_data);
						}
					}
				}

				// 1th -> 2th
				{
					// ...
					{
						sCH__DAYx__TOTAL_LOT_COUNT[DB__1th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_LOT_COUNT[DB__2th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[DB__1th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[DB__2th_INDEX]->Set__DATA(var_data);

						//
						sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[DB__1th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[DB__2th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[DB__1th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[DB__2th_INDEX]->Set__DATA(var_data);

						sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[DB__1th_INDEX]->Get__DATA(var_data);
						sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[DB__2th_INDEX]->Set__DATA(var_data);
					}

					// ...
					{
						int k;

						for(k=0; k<CFG__HOUR_SIZE; k++)
						{
							sCH__DAYx__HOURx_UPEH_RESULT[DB__1th_INDEX][k]->Get__DATA(var_data);
							sCH__DAYx__HOURx_UPEH_RESULT[DB__2th_INDEX][k]->Set__DATA(var_data);
						}
					}
				}

				// 1th : Clear
				{
					// ...
					{
						sCH__DAYx__TOTAL_LOT_COUNT[DB__1th_INDEX]->Set__DATA("0");
						sCH__DAYx__TOTAL_PROCESSED_WAFER_COUNT[DB__1th_INDEX]->Set__DATA("0");

						//
						sCH__1th_DAY__TOTAL_EQUIPMENT_PROCESS_TIME_SEC->Set__DATA("0");
						sCH__DAYx__TOTAL_EQUIPMENT_PROCESS_TIME_FMT[DB__1th_INDEX]->Set__DATA("00:00:00");

						//
						sCH__1th_DAY__TOTAL_EQUIPMENT_IDLE_TIME_SEC->Set__DATA("0");
						sCH__DAYx__TOTAL_EQUIPMENT_IDLE_TIME_FMT[DB__1th_INDEX]->Set__DATA("00:00:00");

						//
						sCH__1th_DAY__TOTAL_EQUIPMENT_DOWN_TIME_SEC->Set__DATA("0");
						sCH__DAYx__TOTAL_EQUIPMENT_DOWN_TIME_FMT[DB__1th_INDEX]->Set__DATA("00:00:00");
					}

					for(int k=0; k<CFG__HOUR_SIZE; k++)
					{
						sCH__DAYx__HOURx_UPEH_RESULT[DB__1th_INDEX][k]->Set__DATA("");
					}
				}

				// ...
				{
					cur_day = cur_time.GetDay();
					var_data.Format("%1d",cur_day);
					sCH__CUR_DAY->Set__DATA(var_data);

					//
					async__eqp_proc_time->STOP();
					async__eqp_idle_time->STOP();
					async__eqp_down_time->STOP();

					async__eqp_proc_time->Set__START_TIME(0.0);
					async__eqp_idle_time->Set__START_TIME(0.0);
					async__eqp_down_time->Set__START_TIME(0.0);

					async__eqp_proc_time->START__COUNT_UP(max_up_sec);
					async__eqp_idle_time->START__COUNT_UP(max_up_sec);
					async__eqp_down_time->START__COUNT_UP(max_up_sec);

					async__eqp_proc_time->PAUSE();
					async__eqp_idle_time->PAUSE();
					async__eqp_down_time->PAUSE();
				}

				// ...
				{
					cur_system_sts = -1;
					mRes__SYSTEM_LOTID.Init__LOTID_COUNT();
				}
			}
		}

		// ...
	}
	return 1;
}

// Alarm & Maint
int  CObj_Mng__SYSTEM_INFO_STD::Check__ALARM_Or_MAINT()
{
	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__ALARM() > 0)
	{
		sCH__MON_SYS_ALARM_STATE->Set__DATA("YES");
		return 2;
	}
	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__MAINT() > 0)
	{
		sCH__MON_SYS_MAINT_STATE->Set__DATA("YES");
		return 1;
	}

	// ...
	{
		sCH__MON_SYS_ALARM_STATE->Set__DATA("");
		sCH__MON_SYS_MAINT_STATE->Set__DATA("");
	}
	return -1;
}

// Process & Idle 
int  CObj_Mng__SYSTEM_INFO_STD::Check__PROCESS_Or_IDLE()
{
	if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STATUS__PROCESS() > 0)
	{
		return 1;
	}

	return 2;
}
