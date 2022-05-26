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

	dCH__COMM_STS->Set__DATA("ONLINE"); //test ���� ����.

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

					alm_msg = "ESC Controller ��� ���� NG";

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
						alm_msg = "�Ķ������ ������ Ÿ���� �߸� �Ǿ����ϴ�.";
						break;

					case -108:
						alarm_id = ALID__ESC_PARAMETER_NOT_ALLOWED;
						alm_msg = "��ɾ �ʿ��� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.";
						break;

					case -109:
						alarm_id = ALID__ESC_MISSING_PARAMETER;
						alm_msg = "��ɾ �ʿ��� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.";
						break;

					case -113:
						alarm_id = ALID__ESC_UNDEFINED_HEADER;
						alm_msg = "��ȿ���� ���� ����� ���ŵǾ����ϴ�.";
						break;

					case -222:
						alarm_id = ALID__ESC_DATA_OUT_OF_RANGE;
						alm_msg = "������ �Ķ������ ���ġ�� �ʰ��߽��ϴ�.";
						break;

					case -350:
						alarm_id = ALID__ESC_TOO_MANY_ERRORS;
						alm_msg = "10�� �̻��� ������ �߻��Ͽ� Error Buffer�� ����á���ϴ�. Error Clear�� �ʿ��մϴ�.";
						break;

					case -410:
						alarm_id = ALID__ESC_QUERY_INTERRUPED;
						alm_msg = "����� ���ŵǾ����� ��� ���ۿ� ���� ����� �����Ͱ� ��� �ֽ��ϴ�. - ���� �����ʹ� �ս� �˴ϴ�.";
						break;

					case -420:
						alarm_id = ALID__ESC_QUERY_UNTERMINATED;
						alm_msg = "�����͸� �е��� �����Ǿ�����, ��¹��ۿ� �����͸� �����ϴ� ����� ���ŵ��� �ʾҽ��ϴ�.";
						break;

					case -430:
						alarm_id = ALID__ESC_QUERY_DEADLOCKED;
						alm_msg = "��� ���ۿ� ���� �ʹ� ���� �����͸� �ۼ��ϴ� ����� ���ŵǾ�����, �Է� ���� ���� ���� á���ϴ�. ����� ��������� ��� �����Ͱ� �սŵ˴ϴ�.";
						break;

					case -440:
						alarm_id = ALID__ESC_QUERY_UNTERMINATED_AFTER_indefinite;
						alm_msg = "*IDN? ����� ��� ���ڿ��� ������ ���� ������� ����ؾ� �մϴ�.";
						break;

					case -515:
						alarm_id = ALID__ESC_COMMAND_NOT_ALLOWED_IN_REMOTE;
						alm_msg = "Remote ���¿����� ���� ������ ����� ���� �߽��ϴ�.";
						break;

					case -522:
						alarm_id = ALID__ESC_OUTPUT_BUFFER_OVERFLOW;
						alm_msg = "��� ���ۿ� �����Ͱ� ���� á���ϴ�.";
						break;

					case -561:
						alarm_id = ALID__ESC_OUTPUT_ENABLE;
						alm_msg = "��� �߿� ����� ���� �߽��ϴ�.";
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
