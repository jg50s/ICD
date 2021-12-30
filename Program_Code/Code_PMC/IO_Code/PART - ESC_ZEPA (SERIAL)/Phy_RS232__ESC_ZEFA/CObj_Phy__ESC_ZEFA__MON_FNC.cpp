#include "StdAfx.h"

#include "CObj_Phy__ESC_ZEFA.h"
//#include "CObj_Phy__ESC_ZEFA__DEF.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj_Phy__ESC_ZEFA::
Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	int offline__check_count = 0;

	CString var_data;
	CString	ch_data;
	int		cnt = 0;
	int		flag = 0;
	CString log_msg = "";

	dCH__COMM_STS->Set__DATA("ONLINE"); //test 삭제 하자.

	while(1)
	{
		cx_timer_ctrl->POLL(0.15);

		if(xI_SEQ->Is__SIMULATION_MODE() > 0)
		{
			dCH__COMM_STS->Set__DATA("ONLINE");
			continue;
		}
		
		if (mon_flag == 1)
		{
			flag = soCH__STATE_READ->Set__DATA("1");
			//sCH__STATE_READ->Get__DATA(var_data);

			if (flag < 0)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}

			if (cnt > 10)
			{
				// ...
				{
					int alarm_id = ALID__ESCCON_OFFLINE_ALARM;
					CString alm_msg;
					CString	r_act;

					alm_msg = "ESC Controller 통신 상태 NG";

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);

					dCH__COMM_STS->Set__DATA("OFFLINE");
					//sCH__COMM_STS->Set__DATA("OFFLINE");
				}
				cnt = 0;
				Write__DRV_LOG("ESC COMM Error");
			}
		}
	}
}

//------------------------------------------------------------------------------------
void CObj_Phy__ESC_ZEFA::
Mon__MONITOR_1(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	int offline__check_count = 0;

	CString var_data;
	CString ch_data;

	while(1)
	{
		cx_timer_ctrl->WAIT(0.5);

		if(xI_SEQ->Is__SIMULATION_MODE() > 0)
		{
			continue;
		}

		{
			// Check ...
			{
				CString ch_data_1;
				CString ch_data_2;
				CString var_data_1;
				CString var_data_2;
				double	check_data_1;
				double	check_data_2;
				double	cur_data_1;
				double	cur_data_2;
				
				CString	buf_msg1 = "";
				CString	buf_msg2 = "";
				CString alm_msg;
				CString	r_act;
				int		alarm_flag = 0;

				sCH__SETCURR_READ_CH1->Get__DATA(ch_data_1);
				aCH__CURR_READ_CH1->Get__DATA(var_data_1);
				check_data_1 = atof(ch_data_1);
				cur_data_1	 = atof(var_data_1);

				if (cur_data_1 > check_data_1)
				{
					alarm_flag = 1;
					buf_msg1.Format("ESC_CONTROLLER_CURRENT_RANGE_ABORT_CH1 \n Limit Current : %s \n Curr Current : %s \n", check_data_1, var_data_1);
				}

				sCH__SETCURR_READ_CH2->Get__DATA(ch_data_2);
				aCH__CURR_READ_CH2->Get__DATA(var_data_2);
				check_data_2 = atof(ch_data_2);
				cur_data_2	 = atof(var_data_2);

				if (cur_data_2 > check_data_2)
				{
					alarm_flag = 1;
					buf_msg2.Format("ESC_CONTROLLER_CURRENT_RANGE_ABORT_CH2 \n Limit Current : %s \n Curr Current : %s \n", check_data_2, var_data_2);
				}

				if (alarm_flag > 0)
				{
					int alarm_id = ALID__ESC_CURRENT_RANGE_ABORT;
					CString alm_msg;
					CString	r_act;

					alm_msg = buf_msg1 + buf_msg2;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
				}
			}
		}
	}
}


void CObj_Phy__ESC_ZEFA::
Mon__MONITOR_2(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	int offline__check_count = 0;

	CString var_data;
	CString ch_data;
	int		err_val;

	//...current setting cfg
	CString	rampup			= "";
	CString	rampdn			= "";
	CString	currlimit_ch1	= "";
	CString	currlimit_ch2	= "";
	CString	toggleuse		= "";	// Toggle
	CString	A_toggleuse		= "";	// Auto Toggle
	CString	A_toggle_cnt	= "";
	CString	A_toggle_volt	= "";

	//...last setting cfg
	CString rampup_last			= "";
	CString rampdn_last			= "";
	CString currlimit_last_ch1	= "";
	CString currlimit_last_ch2	= "";
	CString toggle_last			= "";
	CString A_toggle_last		= "";
	CString A_toggle_cnt_last	= "";
	CString A_toggle_volt_last	= "";

	while(1)
	{
		cx_timer_ctrl->WAIT(1.0);

		if(xI_SEQ->Is__SIMULATION_MODE() > 0)
		{
			
		}

		sCH__REMOTE_STATUS->Get__DATA(var_data);
		if (var_data == "REMOTE")
		{
			// CONFIG ...
			{

				aCH__CFG_RAMPUP_TIME->Get__DATA(rampup);
				if (rampup != rampup_last)
				{					
					aCH__RAMPUP_SET->Set__DATA(rampup);
					Write__DRV_LOG("rampup time config change");
				}

				aCH__CFG_RAMPDN_TIME->Get__DATA(rampdn);
				if (rampdn != rampdn_last)
				{
					aCH__RAMPDN_SET->Set__DATA(rampdn);
					Write__DRV_LOG("rampdn time config change");
				}

				aCH__CFG_CURRLIMIT_CH1->Get__DATA(currlimit_ch1);
				if (currlimit_ch1 != currlimit_last_ch1)
				{
					aCH__CURRLIMIT_SET_CH1->Set__DATA(currlimit_ch1);
					Write__DRV_LOG("currlimit ch1 config change");
				}

				aCH__CFG_CURRLIMIT_CH2->Get__DATA(currlimit_ch2);
				if (currlimit_ch2 != currlimit_last_ch2)
				{
					aCH__CURRLIMIT_SET_CH2->Set__DATA(currlimit_ch2);
					Write__DRV_LOG("currlimit ch2 config change");
				}

				aCH__CFG_AUTO_TOGGLE_CNT->Get__DATA(A_toggle_cnt);
				if (A_toggle_cnt != A_toggle_cnt_last)
				{
					aCH__AUTO_TOGGLE_CNT->Set__DATA(A_toggle_cnt);
					Write__DRV_LOG("A_toggle_cnt ch1 config change");
				}

				aCH__CFG_AUTO_TOGGLE_VOLT->Get__DATA(A_toggle_volt);
				if (A_toggle_volt != A_toggle_volt_last)
				{
					aCH__AUTO_TOGGLE_VOLT->Set__DATA(A_toggle_volt);
					Write__DRV_LOG("A_toggle_volt ch1 config change");
				}

				dCH__CFG_TOGGLE_USE->Get__DATA(toggleuse);
				if		(toggleuse == "USE")
				{
					dCH__TOGGLE->Set__DATA(MODE__ON);
				}
				else if (toggleuse == "NOTUSE")
				{
					dCH__TOGGLE->Set__DATA(MODE__OFF);
				}

				dCH__CFG_AUTO_TOGGLE_USE->Get__DATA(A_toggleuse);
				if		(A_toggleuse == "USE")
				{
					dCH__AUTO_TOGGLE->Set__DATA(MODE__ON);
				}
				else if (A_toggleuse == "NOTUSE")
				{
					dCH__AUTO_TOGGLE->Set__DATA(MODE__OFF);
				}

				rampup_last			= rampup;
				rampdn_last			= rampdn;
				currlimit_last_ch1	= currlimit_ch1;
				currlimit_last_ch2	= currlimit_ch2;
				toggle_last			= toggleuse;
				A_toggle_last		= A_toggleuse;
				A_toggle_cnt_last	= A_toggle_cnt;
				A_toggle_volt_last	= A_toggle_volt;
			}


			// Check ...
			{
				soCH__ERROR_READ->Set__DATA("1");
				sCH__ERROR_READ->Get__DATA(ch_data);
				err_val = atoi(ch_data);

				if (err_val < 0)
				{
					int alarm_id;
					CString alm_msg;

					switch (err_val)
					{
					case -104:
						alarm_id = ALID__ESC_DATA_TYPE_ERROR;
						alm_msg = "파라미터의 데이터 타입이 잘못 되었습니다.";
						break;

					case -108:
						alarm_id = ALID__ESC_PARAMETER_NOT_ALLOWED;
						alm_msg = "명령어에 필요한 파라미터 보다 많은 파라미터가 수신되었습니다.";
						break;

					case -109:
						alarm_id = ALID__ESC_MISSING_PARAMETER;
						alm_msg = "명령어에 필요한 파라미터 보다 적은 파라미터가 수신되었습니다.";
						break;

					case -113:
						alarm_id = ALID__ESC_UNDEFINED_HEADER;
						alm_msg = "유효하지 않은 명령이 수신되었습니다.";
						break;

					case -222:
						alarm_id = ALID__ESC_DATA_OUT_OF_RANGE;
						alm_msg = "지정된 파라미터의 허용치를 초과했습니다.";
						break;

					case -350:
						alarm_id = ALID__ESC_TOO_MANY_ERRORS;
						alm_msg = "10개 이상의 오류가 발생하여 Error Buffer가 가득찼습니다. Error Clear가 필요합니다.";
						break;

					case -410:
						alarm_id = ALID__ESC_QUERY_INTERRUPED;
						alm_msg = "명령이 수신되었지만 출력 버퍼에 이전 명령의 데이터가 들어 있습니다. - 이전 데이터는 손실 됩니다.";
						break;

					case -420:
						alarm_id = ALID__ESC_QUERY_UNTERMINATED;
						alm_msg = "데이터를 읽도록 지정되었지만, 출력버퍼에 데이터를 전송하는 명령이 수신되지 않았습니다.";
						break;

					case -430:
						alarm_id = ALID__ESC_QUERY_DEADLOCKED;
						alm_msg = "출력 버퍼에 비해 너무 많은 데이터를 작성하는 명령이 수신되었으며, 입력 버퍼 역시 가득 찼습니다. 명령은 실행되지만 모든 데이터가 손신됩니다.";
						break;

					case -440:
						alarm_id = ALID__ESC_QUERY_UNTERMINATED_AFTER_indefinite;
						alm_msg = "*IDN? 명령은 명령 문자열의 마지막 쿼리 명령으로 사용해야 합니다.";
						break;

					case -515:
						alarm_id = ALID__ESC_COMMAND_NOT_ALLOWED_IN_REMOTE;
						alm_msg = "Remote 상태에서만 실행 가능한 명령을 수신 했습니다.";
						break;

					case -522:
						alarm_id = ALID__ESC_OUTPUT_BUFFER_OVERFLOW;
						alm_msg = "출력 버퍼에 데이터가 가득 찼습니다.";
						break;

					case -561:
						alarm_id = ALID__ESC_OUTPUT_ENABLE;
						alm_msg = "출력 중에 명령을 수신 했습니다.";
						break;
					}

					{
						CString	r_act;

						p_alarm->Check__ALARM(alarm_id,r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
					}
				}
			}
		}
	}
}
