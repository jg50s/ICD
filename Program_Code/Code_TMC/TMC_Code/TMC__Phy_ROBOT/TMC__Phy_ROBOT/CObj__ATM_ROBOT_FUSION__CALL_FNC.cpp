#include "StdAfx.h"
#include "CObj__ATM_ROBOT_FUSION.h"
#include "CObj__ATM_ROBOT_FUSION__DEF.h"
#include "CObj__ATM_ROBOT_FUSION__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__ATM_ROBOT_FUSION
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	int flag = pROBOT__OBJ_CTRL->Call__OBJECT(CMMD__INIT);

	if(flag > 0)
	{
		Set_ANI__ROBOT_ALL_RETRACT();
	}
	return flag;
}

int  CObj__ATM_ROBOT_FUSION
::Interlock__AL1_SLOT_CHECK(CII_OBJECT__ALARM* p_alarm,
							const CString& stn_name,
							const CString& para_slot,
							CString& trg_slot)
{
LOOP_RETRY:

	if(stn_name.CompareNoCase(STR__AL1) != 0)
	{
		return 1;
	}

	// ...
	CString ch_data = dEXT_CH__CFG_AL1_SLOT_MAX->Get__STRING();
	int cfg_slot = atoi(ch_data);

	if(cfg_slot < 2)
	{
		trg_slot = "1";
		return 1;
	}

	// ...
	{
		int i_slot = atoi(para_slot);

		if(i_slot > cfg_slot)
		{
			CString log_msg;

			// ...
			{
				CString log_bff;

				log_msg = " * Error : Aligner Slot_MAX ... \n";
				log_bff.Format(" * para_slot : %1d \n", i_slot);
				log_msg += log_bff;
				log_bff.Format(" * cfg_slot : %1d \n", cfg_slot);
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			{
				int alm_id = ALID__ALx__SLOT_ID_ERROR;
				CString r_act;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, log_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
			}
			return -1;
		}
	}

	trg_slot = para_slot;
	return 1;
}
int  CObj__ATM_ROBOT_FUSION
::Interlock__LLx_SLOT_CHECK(CII_OBJECT__ALARM* p_alarm,
							const CString& stn_name,
							const CString& para_slot,
							CString& trg_slot)
{
LOOP_RETRY:

	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	if(ll_i <  0)				return  1;
	if(ll_i >= iSIZE_LLx)		return -1;

	// ...
	CString ch_data = dEXT_CH__CFG_LLx_SLOT_MAX[ll_i]->Get__STRING();
	int cfg__slot_max = atoi(ch_data);

	// Check ...
	{
		int i_slot = atoi(para_slot);

		// CFG.MAX ...
		if((i_slot > cfg__slot_max)
		|| (i_slot < 1))
		{
			CString log_msg;

			// ...
			{
				CString log_bff;

				log_msg.Format(" * Error : %s's Slot_MAX ... \n", stn_name);
				log_bff.Format(" * para_slot : %1d \n", i_slot);
				log_msg += log_bff;
				log_bff.Format(" * cfg_slot : %1d \n", cfg__slot_max);
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			{
				int alm_id = ALID__LLx__SLOT_ID_ERROR;
				CString r_act;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, log_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
			}
			return -1;
		}

		// CFG.USE ...
		int slot_index = i_slot - 1;

		if(dEXT_CH__CFG_LLx_SLOT_USE_X[ll_i][slot_index]->Check__DATA(STR__YES) < 0)
		{
			CString log_msg;

			// ...
			{
				CString log_bff;

				log_msg.Format(" * Error : %s's Slot_USE ... \n", stn_name);
				log_bff.Format(" * para_slot : %1d \n", i_slot);
				log_msg += log_bff;
				log_bff.Format(" * %s <- %s \n",
								dEXT_CH__CFG_LLx_SLOT_USE_X[ll_i][slot_index]->Get__CHANNEL_NAME(),
								dEXT_CH__CFG_LLx_SLOT_USE_X[ll_i][slot_index]->Get__STRING());
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			{
				int alm_id = ALID__LLx__SLOT_ID_ERROR;
				CString r_act;

				p_alarm->Popup__ALARM_With_MESSAGE(alm_id, log_msg, r_act);

				if(r_act.CompareNoCase(ACT__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}
			}
			return -2;
		}
	}

	trg_slot = para_slot;
	return 1;
}

int  CObj__ATM_ROBOT_FUSION
::Call__PICK(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const CString& arm_type,
			 const CString& stn_name,
			 const CString& para_slot,
			 const bool active__align_pick)
{
	CString act_name;
	CString stn_slot = para_slot;

	// Slot Check ...
	{
		if(Interlock__AL1_SLOT_CHECK(p_alarm, stn_name, para_slot, stn_slot) < 0)
		{
			return -11;
		}
		if(Interlock__LLx_SLOT_CHECK(p_alarm, stn_name, para_slot, stn_slot) < 0)
		{
			return -12;
		}
	}

	// ...
	{
		act_name.Format("pick from %s-%s to Arm-%s", stn_name,stn_slot,arm_type);
		Fnc__APP_LOG(act_name);

		// Door Check -----
		if(Interlock__CHECK_DOOR_OPEN(p_alarm, stn_name,stn_slot, act_name) < 0)
		{
			Fnc__APP_LOG("Interlock__CHECK_DOOR_OPEN.. ret:-1");
			return -1;
		}

		// Material Check -----
		if(dCH__CFG__WAFER_PRESENT_CHECK->Check__DATA("YES") > 0)	
		{
			if(Interlock__CHECK_MATERIAL(p_alarm,-1,arm_type,stn_name,stn_slot,act_name) < 0)
			{
				Fnc__APP_LOG("Interlock__CHECK_MATERIAL.. ret:-1");
				return -1;
			}
		}
	}

	Set_ANI__ROBOT_ROTATE(arm_type, stn_name,stn_slot);
	Set_ANI__ROBOT_EXTEND(arm_type, stn_name,stn_slot);

	// ...
	int r_flag;

	if(active__align_pick)		r_flag = Fnc__ACTION(arm_type,stn_name,stn_slot, CMMD__ALIGN_PICK);
	else						r_flag = Fnc__ACTION(arm_type,stn_name,stn_slot, CMMD__PICK);

	if(r_flag > 0)
	{
		if(arm_type.CompareNoCase(ARM_A) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		return -11;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		return -12;
		}

		Fnc__CHANGE_MATERIAL_INFO(-1,arm_type, stn_name,stn_slot);
		Set_ANI__ROBOT_RETRACT(arm_type, stn_name,stn_slot);
	}
	else
	{
		bool active__wfr_exchange = false;

		if(arm_type.CompareNoCase(ARM_A) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)		active__wfr_exchange = true;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)		active__wfr_exchange = true;
		}

		if(active__wfr_exchange)
		{
			Fnc__CHANGE_MATERIAL_INFO(-1,arm_type, stn_name,stn_slot);
		}
	}

	act_name.Format("End..Call__PICK.. ret:%d", r_flag);
	Fnc__APP_LOG(act_name);

	return r_flag;
}
int  CObj__ATM_ROBOT_FUSION
::Fnc__ACTION(const CString& arm_type,
			  const CString& stn_name,
			  const CString& stn_slot,
			  const CString& cmmd_act)
{
	// ...
	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->START__COUNT_UP(99999);

	// ...
	{
		CString log_msg;
	
		log_msg.Format("Fnc__ACTION(%s) :Arm(%s) Stn(%s) Slot(%s) \n",  cmmd_act,arm_type,stn_name,stn_slot);
		Fnc__APP_LOG(log_msg);
	}

	// ...
	CStringArray l_para;

	l_para.Add(arm_type);
	l_para.Add(stn_name);
	l_para.Add(stn_slot);

	int flag = pROBOT__OBJ_CTRL->Call__OBJ_MODE(cmmd_act, l_para);

	if(flag > 0)
	{
		CString str_cur;
		CString ch_data;

		int db_index = -1;

		if((cmmd_act.CompareNoCase(CMMD__PICK) == 0)
		|| (cmmd_act.CompareNoCase(CMMD__ALIGN_PICK) == 0))
		{
			db_index = _ACT_INDEX__PICK;
		}
		else if(cmmd_act.CompareNoCase(CMMD__PLACE)  == 0)			db_index = _ACT_INDEX__PLACE;
		else if(cmmd_act.CompareNoCase(CMMD__ROTATE) == 0)			db_index = _ACT_INDEX__ROTATE;

		if(db_index >= 0)
		{	
			CII__VAR_STRING_CTRL* p_ch_min;
			CII__VAR_STRING_CTRL* p_ch_max;
			CII__VAR_STRING_CTRL* p_ch_avg;
			CII__VAR_STRING_CTRL* p_ch_avg_f;
			CII__VAR_ANALOG_CTRL* p_ch_cnt;

			double cur_sec = x_timer_ctrl->Get__CURRENT_TIME();
			str_cur.Format("%.1f", cur_sec);

			// Robot ...
			{
				sCH__TAS_ACTION_TIME_NOW__RB[db_index]->Set__DATA(str_cur);

				//
				p_ch_min = sCH__TAS_ACTION_TIME_MIN__RB[db_index].Get__PTR();
				p_ch_max = sCH__TAS_ACTION_TIME_MAX__RB[db_index].Get__PTR();
				p_ch_avg = sCH__TAS_ACTION_TIME_AVG__RB[db_index].Get__PTR();
				p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__RB[db_index].Get__PTR();
				p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__RB[db_index].Get__PTR();

				_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
			}

			// LPx ...
			{
				int db_i = Macro__CHECK_LPx_INDEX(stn_name);
				if(db_i >= 0)
				{
					sCH__TAS_ACTION_TIME_NOW__LPx[db_index][db_i]->Set__DATA(str_cur);

					//
					p_ch_min = sCH__TAS_ACTION_TIME_MIN__LPx[db_index][db_i].Get__PTR();
					p_ch_max = sCH__TAS_ACTION_TIME_MAX__LPx[db_index][db_i].Get__PTR();
					p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LPx[db_index][db_i].Get__PTR();
					p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LPx[db_index][db_i].Get__PTR();
					p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LPx[db_index][db_i].Get__PTR();

					_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
				}
			}

			// AL1 ...
			if(stn_name.CollateNoCase(STR__AL1) == 0)
			{
				sCH__TAS_ACTION_TIME_NOW__AL1[db_index]->Set__DATA(str_cur);

				//
				p_ch_min = sCH__TAS_ACTION_TIME_MIN__AL1[db_index].Get__PTR();
				p_ch_max = sCH__TAS_ACTION_TIME_MAX__AL1[db_index].Get__PTR();
				p_ch_avg = sCH__TAS_ACTION_TIME_AVG__AL1[db_index].Get__PTR();
				p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__AL1[db_index].Get__PTR();
				p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__AL1[db_index].Get__PTR();

				_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
			}

			// LLx ...
			{
				int db_i = Macro__CHECK_LLx_INDEX(stn_name);
				if(db_i >= 0)
				{
					if(bActive__LLx_MULTI_DOOR_VALVE)
					{
						int s_index = atoi(stn_slot) - 1;

						if((s_index >= 0) && (s_index < CFG_LLx__SLOT_SIZE))
						{
							sCH__TAS_ACTION_TIME_NOW__LLx_SLOT[db_index][db_i][s_index]->Set__DATA(str_cur);

							//
							p_ch_min = sCH__TAS_ACTION_TIME_MIN__LLx_SLOT[db_index][db_i][s_index].Get__PTR();
							p_ch_max = sCH__TAS_ACTION_TIME_MAX__LLx_SLOT[db_index][db_i][s_index].Get__PTR();
							p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LLx_SLOT[db_index][db_i][s_index].Get__PTR();
							p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LLx_SLOT[db_index][db_i][s_index].Get__PTR();
							p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LLx_SLOT[db_index][db_i][s_index].Get__PTR();

							_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
						}
					}
					else
					{
						sCH__TAS_ACTION_TIME_NOW__LLx_X[db_index][db_i]->Set__DATA(str_cur);

						//
						p_ch_min = sCH__TAS_ACTION_TIME_MIN__LLx_X[db_index][db_i].Get__PTR();
						p_ch_max = sCH__TAS_ACTION_TIME_MAX__LLx_X[db_index][db_i].Get__PTR();
						p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LLx_X[db_index][db_i].Get__PTR();
						p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LLx_X[db_index][db_i].Get__PTR();
						p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LLx_X[db_index][db_i].Get__PTR();

						_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
					}
				}
			}

			// ST1 ...
			if((stn_name.CollateNoCase(STR__ST1)   == 0)
			|| (stn_name.CollateNoCase(STR__BUFF1) == 0))
			{
				sCH__TAS_ACTION_TIME_NOW__ST1[db_index]->Set__DATA(str_cur);

				//
				p_ch_min = sCH__TAS_ACTION_TIME_MIN__ST1[db_index].Get__PTR();
				p_ch_max = sCH__TAS_ACTION_TIME_MAX__ST1[db_index].Get__PTR();
				p_ch_avg = sCH__TAS_ACTION_TIME_AVG__ST1[db_index].Get__PTR();
				p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__ST1[db_index].Get__PTR();
				p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__ST1[db_index].Get__PTR();

				_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
			}
		}
	}

	return flag;
}
int  CObj__ATM_ROBOT_FUSION
::_Update__ACTION_MIN_MAX(CII__VAR_STRING_CTRL* p_ch_min,
						  CII__VAR_STRING_CTRL* p_ch_max,
						  CII__VAR_STRING_CTRL* p_ch_avg,
						  CII__VAR_STRING_CTRL* p_ch_avg_f,
						  CII__VAR_ANALOG_CTRL* p_ch_cnt,
						  const double cur_sec)
{
	CString ch_data;
	CString str_cur;

	str_cur.Format("%.1f", cur_sec);

	// Avg ...
	{
		ch_data = p_ch_avg_f->Get__STRING();
		double pre_avg = atof(ch_data);

		double n_count = p_ch_cnt->Get__VALUE();
		p_ch_cnt->Inc__VALUE();

		double cur_avg;
		if(n_count > 0)		cur_avg = (pre_avg * (n_count - 1) / n_count) + (cur_sec / n_count);
		else				cur_avg = cur_sec;

		ch_data.Format("%.5f", cur_avg);
		p_ch_avg_f->Set__DATA(ch_data);

		ch_data.Format("%.1f", cur_avg);
		p_ch_avg->Set__DATA(ch_data);
	}
	// Min ...
	{
		ch_data = p_ch_min->Get__STRING();

		if(ch_data.GetLength() < 1)
		{
			p_ch_min->Set__DATA(str_cur);
		}
		else
		{
			double cur_min = atof(ch_data);

			if(cur_sec < cur_min)		p_ch_min->Set__DATA(str_cur);
		}
	}
	// Max ...
	{
		ch_data = p_ch_max->Get__STRING();

		if(ch_data.GetLength() < 1)
		{
			p_ch_max->Set__DATA(str_cur);
		}
		else
		{
			double cur_max = atof(ch_data);

			if(cur_sec > cur_max)		p_ch_max->Set__DATA(str_cur);
		}
	}

	return 1;
}

int  CObj__ATM_ROBOT_FUSION
::Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const CString& arm_type,
			  const CString& stn_name,
			  const CString& para_slot)
{
	CString act_name;
	CString stn_slot = para_slot;

	// Slot Check ...
	{
		if(Interlock__AL1_SLOT_CHECK(p_alarm, stn_name, para_slot, stn_slot) < 0)
		{
			return -11;
		}
		if(Interlock__LLx_SLOT_CHECK(p_alarm, stn_name, para_slot, stn_slot) < 0)
		{
			return -12;
		}
	}

	// ...
	{
		act_name.Format("place from Arm-%s to %s-%s", arm_type,stn_name,stn_slot);
		Fnc__APP_LOG(act_name);

		// Door Check -----
		if(Interlock__CHECK_DOOR_OPEN(p_alarm, stn_name,stn_slot, act_name) < 0)
		{
			Fnc__APP_LOG("Interlock__CHECK_DOOR_OPEN.. ret:-1");
			return -21;
		}

		// Material Check -----
		if(Interlock__CHECK_MATERIAL(p_alarm,1,arm_type,stn_name,stn_slot,act_name) < 0)
		{
			Fnc__APP_LOG("Interlock__CHECK_MATERIAL.. ret:-1");
			return -22;
		}
	}

	Set_ANI__ROBOT_ROTATE(arm_type, stn_name,stn_slot);
	Set_ANI__ROBOT_EXTEND(arm_type, stn_name,stn_slot);

	// ...
	int r_flag = Fnc__ACTION(arm_type, stn_name,stn_slot, CMMD__PLACE);

	if(r_flag > 0)
	{
		if(arm_type.CompareNoCase(ARM_A) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)		return -11;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)		return -12;
		}

		Fnc__CHANGE_MATERIAL_INFO(1,arm_type, stn_name,stn_slot);
		Set_ANI__ROBOT_RETRACT(arm_type, stn_name,stn_slot);
	}
	else
	{
		bool active__wfr_exchange = false;

		if(arm_type.CompareNoCase(ARM_A) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		active__wfr_exchange = true;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)			
		{
			if(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		active__wfr_exchange = true;
		}

		if(active__wfr_exchange)
		{
			Fnc__CHANGE_MATERIAL_INFO(1,arm_type, stn_name,stn_slot);
		}
	}

	act_name.Format("End..Call__PLACE.. ret:%d", r_flag);
	Fnc__APP_LOG(act_name);
	return r_flag;
}
int  CObj__ATM_ROBOT_FUSION
::Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& arm_type,
			   const CString& stn_name,
			   const CString& stn_slot)
{
	Set_ANI__ROBOT_ROTATE(arm_type, stn_name,stn_slot);

	return Fnc__ACTION(arm_type, stn_name,stn_slot, CMMD__ROTATE);
}

int  CObj__ATM_ROBOT_FUSION::
Call__MAP(CII_OBJECT__VARIABLE* p_variable,
		  CII_OBJECT__ALARM* p_alarm)
{
	return pROBOT__OBJ_CTRL->Call__OBJECT(CMMD__MAP);
}
int  CObj__ATM_ROBOT_FUSION::
Call__HOME(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm,
		   const int req__vac_off)
{
	int flag = -1;

	if(req__vac_off > 0)
	{
		flag = pROBOT__OBJ_CTRL->Call__OBJECT("VAC_OFF.HOME");
	}
	else
	{
		flag = pROBOT__OBJ_CTRL->Call__OBJECT(CMMD__HOME);
	}

	if(flag > 0)
	{
		Set_ANI__ROBOT_ALL_RETRACT();
	}
	return flag;
}

int  CObj__ATM_ROBOT_FUSION::
Call__VACON(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm,
			const CString& arm_type)
{
	CStringArray l_para;

	l_para.Add(arm_type);

	return pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__VACON,l_para);
}
int  CObj__ATM_ROBOT_FUSION::
Call__VACOFF(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const CString& arm_type)
{
	CStringArray l_para;

	l_para.Add(arm_type);

	return pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__VACOFF,l_para);
}

int  CObj__ATM_ROBOT_FUSION::
Call__RETRACT(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const CString& arm_type,
			  const CString& stn_name,
			  const CString& stn_slot)
{
	CString act_name;

	act_name.Format("retract from Arm-%s to %s-%s", arm_type,stn_name,stn_slot);
	Fnc__APP_LOG(act_name);

	// ...
	CStringArray l_para;

	l_para.Add(arm_type);
	l_para.Add(stn_name);
	l_para.Add(stn_slot);

	int flag = pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__RETRACT,l_para);
	if(flag > 0)		Set_ANI__ROBOT_RETRACT(arm_type, stn_name, stn_slot);
	
	return flag;
}
int  CObj__ATM_ROBOT_FUSION
::Call__EXTEND(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& arm_type,
			   const CString& stn_name,
			   const CString& stn_slot)
{
	CString act_name;

	act_name.Format("extend from Arm-%s to %s-%s", arm_type,stn_name,stn_slot);
	Fnc__APP_LOG(act_name);

	// Door Check -----
	if(Interlock__CHECK_DOOR_OPEN(p_alarm, stn_name,stn_slot, act_name) < 0)
	{
		return -1;
	}

	// Material Check -----
	int place_flag = -1;

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		if(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)
		{
			place_flag = 1;
		}
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) < 0)
		{
			place_flag = 1;
		}
	}

	if(place_flag > 0)
	{
		if(Interlock__CHECK_MATERIAL(p_alarm,1,arm_type,stn_name,stn_slot,act_name) < 0)
		{
			return -1;
		}
	}

	Set_ANI__ROBOT_ROTATE(arm_type, stn_name,stn_slot);

	// ...
	CStringArray l_para;

	l_para.Add(arm_type);
	l_para.Add(stn_name);
	l_para.Add(stn_slot);

	int flag = pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__EXTEND,l_para);
	if(flag > 0)			Set_ANI__ROBOT_EXTEND(arm_type, stn_name, stn_slot);
	
	return flag;
}

int  CObj__ATM_ROBOT_FUSION
::Call__GOUP(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm,
			 const CString& arm_type,
			 const CString& stn_name,
			 const CString& stn_slot)
{
	CString act_name;

	act_name.Format("GoUp from Arm-%s to %s-%s", arm_type,stn_name,stn_slot);
	Fnc__APP_LOG(act_name);

	// ...
	CStringArray l_para;

	l_para.Add(arm_type);
	l_para.Add(stn_name);
	l_para.Add(stn_slot);

	return pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__GOUP,l_para);
}
int  CObj__ATM_ROBOT_FUSION
::Call__GODOWN(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& arm_type,
			   const CString& stn_name,
			   const CString& stn_slot)
{
	CString act_name;

	act_name.Format("GoDown from Arm-%s to %s-%s", arm_type,stn_name,stn_slot);
	Fnc__APP_LOG(act_name);

	// ...
	CStringArray l_para;

	l_para.Add(arm_type);
	l_para.Add(stn_name);
	l_para.Add(stn_slot);

	return pROBOT__OBJ_CTRL->Call__OBJ_MODE(CMMD__GODOWN,l_para);
}

int  CObj__ATM_ROBOT_FUSION
::Call__ALGN(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	return pAL1__OBJ_CTRL->Call__OBJECT(CMMD__ALIGN);
}

int  CObj__ATM_ROBOT_FUSION
::Call__LP_MAP(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm)
{
	int alm_id = ALID__ATM_RB_HAS_NO_MAPPING_SENSOR;
	CString r_act;

	p_alarm->Popup__ALARM(alm_id,r_act);
	return -1;
}

int  CObj__ATM_ROBOT_FUSION::
Call__TIME_TEST(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	int n_limit = 2000;
	int n;

	CString stn_name;
	int db_index;
	int i;
	int k;

	for(n=0; n<n_limit; n++)
	{
		stn_name.Format("LL1");

		double cur_sec = 5.0;
		if(n >= 1000)		cur_sec = 10.0;

		for(i=0; i<CFG_ACT__SIZE; i++)
		{
				 if(i == 0)			db_index = _ACT_INDEX__PICK;
			else if(i == 1)			db_index = _ACT_INDEX__PLACE;
			else if(i == 2)			db_index = _ACT_INDEX__ROTATE;
			else					continue;

			// ...
			{	
				CII__VAR_STRING_CTRL* p_ch_min;
				CII__VAR_STRING_CTRL* p_ch_max;
				CII__VAR_STRING_CTRL* p_ch_avg;
				CII__VAR_STRING_CTRL* p_ch_avg_f;
				CII__VAR_ANALOG_CTRL* p_ch_cnt;

				CString str_cur;
				str_cur.Format("%.1f", cur_sec);

				// Robot ...
				{
					sCH__TAS_ACTION_TIME_NOW__RB[db_index]->Set__DATA(str_cur);

					//
					p_ch_min = sCH__TAS_ACTION_TIME_MIN__RB[db_index].Get__PTR();
					p_ch_max = sCH__TAS_ACTION_TIME_MAX__RB[db_index].Get__PTR();
					p_ch_avg = sCH__TAS_ACTION_TIME_AVG__RB[db_index].Get__PTR();
					p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__RB[db_index].Get__PTR();
					p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__RB[db_index].Get__PTR();

					_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
				}

				// LPx ...
				{
					int db_i = Macro__CHECK_LPx_INDEX(stn_name);
					if(db_i >= 0)
					{
						sCH__TAS_ACTION_TIME_NOW__LPx[db_index][db_i]->Set__DATA(str_cur);

						//
						p_ch_min = sCH__TAS_ACTION_TIME_MIN__LPx[db_index][db_i].Get__PTR();
						p_ch_max = sCH__TAS_ACTION_TIME_MAX__LPx[db_index][db_i].Get__PTR();
						p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LPx[db_index][db_i].Get__PTR();
						p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LPx[db_index][db_i].Get__PTR();
						p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LPx[db_index][db_i].Get__PTR();

						_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
					}
				}

				// AL1 ...
				if(stn_name.CollateNoCase(STR__AL1) == 0)
				{
					sCH__TAS_ACTION_TIME_NOW__AL1[db_index]->Set__DATA(str_cur);

					//
					p_ch_min = sCH__TAS_ACTION_TIME_MIN__AL1[db_index].Get__PTR();
					p_ch_max = sCH__TAS_ACTION_TIME_MAX__AL1[db_index].Get__PTR();
					p_ch_avg = sCH__TAS_ACTION_TIME_AVG__AL1[db_index].Get__PTR();
					p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__AL1[db_index].Get__PTR();
					p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__AL1[db_index].Get__PTR();

					_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
				}

				// LLx ...
				{
					int db_i = Macro__CHECK_LLx_INDEX(stn_name);
					if(db_i >= 0)
					{
						if(bActive__LLx_MULTI_DOOR_VALVE)
						{
							for(int t=0; t<CFG_LLx__SLOT_SIZE; t++)
							{
								sCH__TAS_ACTION_TIME_NOW__LLx_SLOT[db_index][db_i][t]->Set__DATA(str_cur);

								//
								p_ch_min = sCH__TAS_ACTION_TIME_MIN__LLx_SLOT[db_index][db_i][t].Get__PTR();
								p_ch_max = sCH__TAS_ACTION_TIME_MAX__LLx_SLOT[db_index][db_i][t].Get__PTR();
								p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LLx_SLOT[db_index][db_i][t].Get__PTR();
								p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LLx_SLOT[db_index][db_i][t].Get__PTR();
								p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LLx_SLOT[db_index][db_i][t].Get__PTR();

								_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
							}
						}
						else
						{
							sCH__TAS_ACTION_TIME_NOW__LLx_X[db_index][db_i]->Set__DATA(str_cur);

							//
							p_ch_min = sCH__TAS_ACTION_TIME_MIN__LLx_X[db_index][db_i].Get__PTR();
							p_ch_max = sCH__TAS_ACTION_TIME_MAX__LLx_X[db_index][db_i].Get__PTR();
							p_ch_avg = sCH__TAS_ACTION_TIME_AVG__LLx_X[db_index][db_i].Get__PTR();
							p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__LLx_X[db_index][db_i].Get__PTR();
							p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__LLx_X[db_index][db_i].Get__PTR();

							_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
						}
					}
				}

				// ST1 ...
				if((stn_name.CollateNoCase(STR__ST1)   == 0)
				|| (stn_name.CollateNoCase(STR__BUFF1) == 0))
				{
					sCH__TAS_ACTION_TIME_NOW__ST1[db_index]->Set__DATA(str_cur);

					//
					p_ch_min = sCH__TAS_ACTION_TIME_MIN__ST1[db_index].Get__PTR();
					p_ch_max = sCH__TAS_ACTION_TIME_MAX__ST1[db_index].Get__PTR();
					p_ch_avg = sCH__TAS_ACTION_TIME_AVG__ST1[db_index].Get__PTR();
					p_ch_avg_f = sCH__TAS_ACTION_TIME_AVG_F__ST1[db_index].Get__PTR();
					p_ch_cnt = aCH__TAS_ACTION_TIME_CNT__ST1[db_index].Get__PTR();

					_Update__ACTION_MIN_MAX(p_ch_min,p_ch_max, p_ch_avg,p_ch_avg_f,p_ch_cnt, cur_sec);
				}
			}
		}

		// ...
	}

	return 1;
}
