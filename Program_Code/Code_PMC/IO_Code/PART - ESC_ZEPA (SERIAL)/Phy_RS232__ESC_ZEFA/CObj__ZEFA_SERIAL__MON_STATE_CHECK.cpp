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

			alm_msg = "ESC Controller 통신 상태 NG";

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
				err_msg = "파라미터의 데이터 타입이 잘못 되었습니다.";
				l_err.Add(err_msg);
				break;

			case  -108:
				err_msg = "Parameter not allowed";
				l_err.Add(err_msg);
				err_msg = "명령어에 예상되는 파라미터 보다 많은 파라미터가 수신되었습니다.";
				l_err.Add(err_msg);
				err_msg = "파라미터가 필요 없는 명령에 여분의 파라미터나 추가 파라미터를 입력했습니다.";
				l_err.Add(err_msg);
				break;;

			case -109:
				err_msg = "Missing parameter";
				l_err.Add(err_msg);
				err_msg = "명령어에 예상되는 파라미터 보다 적은 파라미터가 수신되었습니다.";
				l_err.Add(err_msg);
				err_msg = "명령에 필요한 한 개 이상의 변수를 생략했습니다.";
				l_err.Add(err_msg);
				break;

			case -113:
				err_msg = "Undefined header";
				l_err.Add(err_msg);
				err_msg = "유효하지 않은 명령이 수신되었습니다.";
				l_err.Add(err_msg);
				err_msg = "명령을 잘못 입력했거나 유효하지 않은 명령입니다.";
				l_err.Add(err_msg);
				err_msg = "짧은 형식의 명령을 사용하는 경우, 축약형이 정확한지 확인 해야 합니다.";
				l_err.Add(err_msg);
				break;

			case -222:
				err_msg = "Data out of range";
				l_err.Add(err_msg);
				err_msg = "지정된 파라미터의 허용치를 초과합니다.";
				l_err.Add(err_msg);
				break;

			case -350:
				err_msg = "Too many errors";
				l_err.Add(err_msg);
				err_msg = "10개 이상의 오류가 발생하여 오류 대기열이 가득 찼습니다.";
				l_err.Add(err_msg);
				err_msg = "오류를 삭제하지 않으면 추가 저장되지 않습니다.";
				l_err.Add(err_msg);
				err_msg = "*CLS 명령 또는 전원을 리셋하면 오류가 모두 삭제됩니다.";
				l_err.Add(err_msg);
				break;

			case -410:
				err_msg = "Query INTERRUPED";
				l_err.Add(err_msg);
				err_msg = "명령이 수신되었지만 출력 버퍼에 이전 명령의 데이터가 들어 있습니다.";
				l_err.Add(err_msg);
				err_msg = "(이전 데이터 손실)";
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
