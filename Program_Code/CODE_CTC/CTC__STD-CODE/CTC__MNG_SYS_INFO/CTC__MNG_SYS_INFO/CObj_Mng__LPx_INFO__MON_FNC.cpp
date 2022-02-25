#include "StdAfx.h"
#include "CObj_Mng__LPx_INFO.h"


// ...
void CObj_Mng__LPx_INFO
::Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	int pre_id = -1;
	int cur_id = -1;

	CString str_data;
	int i;

	while(1)
	{
		Sleep(90);

		// ...
		{
			for(i=0;i<iLPx_SIZE;i++)
			{
				if(xEXT_CH__LPx_USE_FLAG[i]->Check__DATA(STR__DISABLE) < 0)
				{
					sCH__LPx_CTRL__LOCK_FLAG[i]->Set__DATA("");

					if(cur_id < 0)
					{
						cur_id = i + 1;

						str_data.Format("%1d",cur_id);
						sCH__LPx_CTRL__SEL_ID->Set__DATA(str_data);
					}
				}
				else
				{
					sCH__LPx_CTRL__LOCK_FLAG[i]->Set__DATA(STR__YES);
				}
			}


			//.....
			sCH__LPx_CTRL__SEL_ID->Get__DATA(str_data);
			cur_id = atoi(str_data);

			if((cur_id > 0) && (cur_id <= iLPx_SIZE))
			{
				//
				{
					CString ctrl_msg;

					ctrl_msg.Format("LP%1d - Control", cur_id);
					sCH__LPx_INFO__CTRL_MSG->Set__DATA(ctrl_msg);
				}

				//
				CString var_name;
				CString var_data;

				int db_index = cur_id - 1;
				int limit = sLIST__LPx_VARIABLE[db_index].GetSize();

				for(i=0;i<limit;i++)
				{
					var_name = sLIST__LPx_VARIABLE[db_index].GetAt(i);	

					if(pOBJ_CTRL__LPx[db_index]->Get__VARIABLE_DATA(var_name,var_data) < 0)
					{
						var_data = "???";
					}

					switch(i)
					{
					case 0:			// 1. OBJ VIRTUAL STATUS
						sCH__LPx_INFO__OBJ_STATUS->Set__DATA(var_data);
						break;

					case 1:			// 2. JOBID
						sCH__LPx_INFO__JOBID->Set__DATA(var_data);
						break;

					case 2:			// 3. PORT STATUS
						sCH__LPx_INFO__PORT_STATUS->Set__DATA(var_data);
						break;

					case 3:			// 4. LOTID
						sCH__LPx_INFO__LOTID->Set__DATA(var_data);
						break;

					case 4:			// 5. CSTID
						sCH__LPx_INFO__CSTID->Set__DATA(var_data);
						break;

					case 5:			// 6. PPID
						sCH__LPx_INFO__PPID->Set__DATA(var_data);
						break;

					case 6:			// 7. TRANSFER PIO
						sCH__LPx_INFO__TRANSFER_PIO->Set__DATA(var_data);
						break;

					case 7:			// 8. PIO : COMM READY STS
						sCH__LPx_INFO__PIO_COMM_READY_STS->Set__DATA(var_data);
						break;

					case 8:			// 9. CST STATUS
						sCH__LPx_INFO__CST_STATUS->Set__DATA(var_data);
						break;
					}

					// SLOTx STATUS -----
					if(i >= 9)
					{
						int db_index = i - 9;

						if((db_index >= 0) && (db_index < CFG__SLOT_SIZE))
						{
							sCH__LPx_INFO__SLOTx_STATUS[db_index]->Set__DATA(var_data);
						}
					}
				}

				// LPx DB -----
				if(cur_id != pre_id)
				{
					if(pre_id < 0)
					{
						sCH__LPx_DB__LotID[db_index]->Get__DATA(var_data);
						sCH__LPx_INFO__DB_LotID->Set__DATA(var_data);

						sCH__LPx_DB__RouteID[db_index]->Get__DATA(var_data);
						sCH__LPx_INFO__DB_RouteID->Set__DATA(var_data);

						sCH__LPx_DB__StartSlot[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_StartSlot->Set__DATA(var_data);

						sCH__LPx_DB__EndSlot[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_EndSlot->Set__DATA(var_data);

						sCH__LPx_DB__CycleCount[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_CycleCount->Set__DATA(var_data);
					}

					int pre_index = pre_id - 1;
					pre_id = cur_id;

					if(pre_index >= 0)
					{
						sCH__LPx_INFO__DB_LotID->Get__DATA(var_data);
						sCH__LPx_DB__LotID[pre_index]->Set__DATA(var_data);

						sCH__LPx_INFO__DB_RouteID->Get__DATA(var_data);
						sCH__LPx_DB__RouteID[pre_index]->Set__DATA(var_data);

						aCH__LPx_INFO__DB_StartSlot->Get__DATA(var_data);
						sCH__LPx_DB__StartSlot[pre_index]->Set__DATA(var_data);

						aCH__LPx_INFO__DB_EndSlot->Get__DATA(var_data);
						sCH__LPx_DB__EndSlot[pre_index]->Set__DATA(var_data);

						aCH__LPx_INFO__DB_CycleCount->Get__DATA(var_data);
						sCH__LPx_DB__CycleCount[pre_index]->Set__DATA(var_data);
					}

					//
					{
						sCH__LPx_DB__LotID[db_index]->Get__DATA(var_data);
						sCH__LPx_INFO__DB_LotID->Set__DATA(var_data);

						sCH__LPx_DB__RouteID[db_index]->Get__DATA(var_data);
						sCH__LPx_INFO__DB_RouteID->Set__DATA(var_data);

						sCH__LPx_DB__StartSlot[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_StartSlot->Set__DATA(var_data);

						sCH__LPx_DB__EndSlot[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_EndSlot->Set__DATA(var_data);

						sCH__LPx_DB__CycleCount[db_index]->Get__DATA(var_data);
						aCH__LPx_INFO__DB_CycleCount->Set__DATA(var_data);
					}
				}

				//.....
				{
					CString obj_mode;
					CString obj_ctrl;

					sCH__LPx_INFO__OBJ_CTRL->Get__DATA(obj_ctrl);
					sCH__LPx_INFO__OBJ_MODE->Get__DATA(obj_mode);

					if(obj_ctrl.CompareNoCase(STR__RUN) == 0)
					{
						pOBJ_CTRL__LPx[db_index]->Run__OBJECT(obj_mode);

						Sleep(100);
						sCH__LPx_INFO__OBJ_CTRL->Set__DATA(STR__AVAILABLE);
					}
				}

				//.....
				{
					CString str_data;
					sCH__OBJ_CTRL__PORT_EXCEPTION->Get__DATA(str_data);

					if(str_data.GetLength() > 0)
					{
						xEXT_CH__LPx_PORT_EXCEPTION[db_index]->Set__DATA(str_data);

						Sleep(100);
						sCH__OBJ_CTRL__PORT_EXCEPTION->Set__DATA("");
					}
				}

				//.....
				{
					CString str_data;
					sCH__OBJ_CTRL__JOB_SELECT_REQ->Get__DATA(str_data);

					if(str_data.GetLength() > 0)
					{
						if(sCH__LPx_CTRL__LOCK_FLAG[db_index]->Check__DATA(STR__YES) > 0)
						{
							sCH__OBJ_CTRL__JOB_SELECT_REQ->Set__DATA("");
						}
						else
						{
							CString win_name = sDATA__WIN_NAME[db_index];
							xEXT_CH__LPx_CH_WIN[db_index]->Set__DATA(win_name);

							Sleep(100);
							sCH__OBJ_CTRL__JOB_SELECT_REQ->Set__DATA("");
						}
					}
				}

				// MANUAL START .....
				{
					sCH__LPx_INFO__MANUAL_START_STATUS->Set__DATA("");

					//
					CString str_data;
					sCH__OBJ_CTRL__MANUAL_START_REQ->Get__DATA(str_data);

					if(str_data.GetLength() > 0)
					{
						Sleep(100);
						sCH__OBJ_CTRL__MANUAL_START_REQ->Set__DATA("");
					}
				}

				// CYCLE START .....
				{
					sCH__LPx_INFO__CYCLE_START_STATUS->Set__DATA("");

					//
					CString str_data;
					sCH__OBJ_CTRL__CYCLE_START_REQ->Get__DATA(str_data);

					if(str_data.GetLength() > 0)
					{
						Sleep(100);
						sCH__OBJ_CTRL__CYCLE_START_REQ->Set__DATA("");
					}
				}
			}
			else
			{
				//.....
				// 1. OBJ STATUS
				sCH__LPx_INFO__OBJ_STATUS->Set__DATA("");

				// 2. JOBID
				sCH__LPx_INFO__JOBID->Set__DATA("");

				// 3. PORT STATUS
				sCH__LPx_INFO__PORT_STATUS->Set__DATA("");

				// 4. LOTID
				sCH__LPx_INFO__LOTID->Set__DATA("");

				// 5. CSTID
				sCH__LPx_INFO__CSTID->Set__DATA("");

				// 6. PPID
				sCH__LPx_INFO__PPID->Set__DATA("");

				// 7. TRANSFER PIO
				sCH__LPx_INFO__TRANSFER_PIO->Set__DATA("");

				// 8. CST STATUS
				sCH__LPx_INFO__CST_STATUS->Set__DATA("");

				// SLOTx STATUS -----
				for(i=0;i<CFG__SLOT_SIZE;i++)
				{
					sCH__LPx_INFO__SLOTx_STATUS[i]->Set__DATA("");
				}
			}
		}

		// ...
	}
}
