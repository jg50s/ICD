#include "StdAfx.h"
#include "CObj__ZEFA_SERIAL.h"


// ...
void CObj__ZEFA_SERIAL
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		sCH__COMM_STS->Set__DATA(STR__ONLINE);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(sCH__COMM_STS->Check__DATA(STR__ONLINE) < 0)
		{
			int alarm_id = ALID__OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg = "ESC Controller ��� ���� NG";

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}

		if(sCH__CUR_REMOTE_STATE->Check__DATA(STR__REMOTE) > 0)
		{
			Fnc__ERROR_CHECK(p_alarm);
		}

		// ...
	}
}

void CObj__ZEFA_SERIAL
::Fnc__ERROR_CHECK(CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = sCH__INFO_ERROR_ID->Get__STRING();

	int err_id = atoi(ch_data);
	if(err_id >= 0)		return;

	// ...
	CStringArray l_err;

	// ...
	{
		CString err_msg;

		switch(err_id)
		{
			case -104:
				err_msg = "Data type error";			
				l_err.Add(err_msg);
				err_msg = "�Ķ������ ������ Ÿ���� �߸� �Ǿ����ϴ�.";
				l_err.Add(err_msg);
				break;

			case  -108:
				err_msg = "Parameter not allowed";
				l_err.Add(err_msg);
				err_msg = "��ɾ ����Ǵ� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.";
				l_err.Add(err_msg);
				err_msg = "�Ķ���Ͱ� �ʿ� ���� ��ɿ� ������ �Ķ���ͳ� �߰� �Ķ���͸� �Է��߽��ϴ�.";
				l_err.Add(err_msg);
				break;;

			case -109:
				err_msg = "Missing parameter";
				l_err.Add(err_msg);
				err_msg = "��ɾ ����Ǵ� �Ķ���� ���� ���� �Ķ���Ͱ� ���ŵǾ����ϴ�.";
				l_err.Add(err_msg);
				err_msg = "��ɿ� �ʿ��� �� �� �̻��� ������ �����߽��ϴ�.";
				l_err.Add(err_msg);
				break;

			case -113:
				err_msg = "Undefined header";
				l_err.Add(err_msg);
				err_msg = "��ȿ���� ���� ����� ���ŵǾ����ϴ�.";
				l_err.Add(err_msg);
				err_msg = "����� �߸� �Է��߰ų� ��ȿ���� ���� ����Դϴ�.";
				l_err.Add(err_msg);
				err_msg = "ª�� ������ ����� ����ϴ� ���, ������� ��Ȯ���� Ȯ�� �ؾ� �մϴ�.";
				l_err.Add(err_msg);
				break;

			case -222:
				err_msg = "Data out of range";
				l_err.Add(err_msg);
				err_msg = "������ �Ķ������ ���ġ�� �ʰ��մϴ�.";
				l_err.Add(err_msg);
				break;

			case -350:
				err_msg = "Too many errors";
				l_err.Add(err_msg);
				err_msg = "10�� �̻��� ������ �߻��Ͽ� ���� ��⿭�� ���� á���ϴ�.";
				l_err.Add(err_msg);
				err_msg = "������ �������� ������ �߰� ������� �ʽ��ϴ�.";
				l_err.Add(err_msg);
				err_msg = "*CLS ��� �Ǵ� ������ �����ϸ� ������ ��� �����˴ϴ�.";
				l_err.Add(err_msg);
				break;

			case -410:
				err_msg = "Query INTERRUPED";
				l_err.Add(err_msg);
				err_msg = "����� ���ŵǾ����� ��� ���ۿ� ���� ����� �����Ͱ� ��� �ֽ��ϴ�.";
				l_err.Add(err_msg);
				err_msg = "(���� ������ �ս�)";
				l_err.Add(err_msg);
				break;

			default:
				err_msg  = "Unknown Error !";
				l_err.Add(err_msg);
				break;
		}
	}

	// ...
	{
		int alm_id = ALID__ERROR_ID;
		CString alm_msg;
		CString	r_act;

		alm_msg.Format(" * Error Code <- %1d \n", err_id);
		alm_msg += "\n";

		// ...
		{
			int k_limit = l_err.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				CString alm_add = l_err[k];
				sCH__INFO_ERROR_LINE_X[k]->Set__DATA(alm_add);

				alm_msg += alm_add;
				alm_msg += "\n";
			}

			for( ; k<_CFG__ERR_LINE_MAX; k++)
			{
				sCH__INFO_ERROR_LINE_X[k]->Set__DATA("");
			}
		}

		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}
}
