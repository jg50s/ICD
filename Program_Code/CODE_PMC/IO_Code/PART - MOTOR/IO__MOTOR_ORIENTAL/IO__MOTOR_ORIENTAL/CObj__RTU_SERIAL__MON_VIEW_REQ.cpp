#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"
#include "CObj__RTU_SERIAL__DEF.h"


// ...
int CObj__RTU_SERIAL
::Mon__VIEW_REQ(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(sCH__MON_IO_WARNING_VIEW_REQ->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				CString str_code = sCH__MON_IO_WARNING_DATA_HEXA->Get__STRING();
				DWORD err_code = atoi(str_code);

				CString str_msg;
				CString r_act;

				str_msg.Format("Warning [%s] \n", str_code);
				str_msg += Get__WARNING_OF_MONITORING_PARAMETER(err_code);

				CStringArray l_act;
				l_act.Add("CHECK");

				p_alarm->Popup__MESSAGE_BOX("Register Warning Check",str_msg,l_act,r_act);
			}

			sCH__MON_IO_WARNING_VIEW_REQ->Set__DATA("");
		}
		if(sCH__MON_IO_ALARM_VIEW_REQ->Check__DATA(STR__YES) > 0)
		{
			// ...
			{
				CString str_code = sCH__MON_IO_ALARM_DATA_HEXA->Get__STRING();

				DWORD err_code = atoi(str_code);

				CString str_msg;
				CString r_act;

				str_msg.Format("Alarm [%s] \n", str_code);
				str_msg += Get__ALARM_OF_MONITORING_PARAMETER(err_code);

				CStringArray l_act;
				l_act.Add("CHECK");

				p_alarm->Popup__MESSAGE_BOX("Register Alarm Check",str_msg,l_act,r_act);
			}

			sCH__MON_IO_ALARM_VIEW_REQ->Set__DATA("");
		}
		if(sCH__MON_IO_LAST_ERROR_VIEW_REQ->Check__DATA(STR__YES) > 0)
		{

			sCH__MON_IO_LAST_ERROR_VIEW_REQ->Set__DATA("");
		}

		if(sCH__CMMD_REQ_SAVE->Check__DATA("") < 0)
		{
			CString str_cmmd = sCH__CMMD_REQ_SAVE->Get__STRING();
			CString str_pos  = sCH__INFO_CUR_POS_MM->Get__STRING();

			int save_ok = -1;

			// ...
			{
				CString str_msg;
				CString str_bff;
				CString r_act;

				str_msg.Format("���� ��ġ %s(mm)�� \n", str_pos);
				str_bff.Format(" %s�� ���� �ұ��?", str_cmmd);
				str_msg += str_bff;

				CStringArray l_act;
				l_act.Add(STR__YES);
				l_act.Add(STR__NO);

				p_alarm->Popup__MESSAGE_BOX("Register Alarm Check",str_msg,l_act,r_act);

				if(r_act.CompareNoCase(STR__YES) == 0)
				{
					save_ok = 1;
				}
			}

			if(save_ok > 0)
			{
				if(str_cmmd.CompareNoCase("MOVE.UP") == 0)
				{
					int i = TRANSFER_POS__UP;
					aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("MOVE.MIDDLE_UP") == 0)
				{
					int i = TRANSFER_POS__MIDDLE_UP;
					aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("MOVE.MIDDLE_DOWN") == 0)
				{
					int i = TRANSFER_POS__MIDDLE_DOWN;
					aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("MOVE.DOWN") == 0)
				{
					int i = TRANSFER_POS__DOWN;
					aCH__CFG_TRANSFER_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("PROC.UP") == 0)
				{
					int i = PROC_POS__UP;
					aCH__CFG_PROC_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("PROC.MIDDLE") == 0)
				{
					int i = PROC_POS__MIDDLE;
					aCH__CFG_PROC_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
				else if(str_cmmd.CompareNoCase("PROC.DOWN") == 0)
				{
					int i = PROC_POS__DOWN;
					aCH__CFG_PROC_POS_X_DATA_POS[i]->Set__DATA(str_pos);
				}
			}

			sCH__CMMD_REQ_SAVE->Set__DATA("");
		}
	}

	return 1;
}

CString CObj__RTU_SERIAL
::Get__WARNING_OF_MONITORING_PARAMETER(DWORD code_value)
{
	if(code_value == 0x00)
	{
		return "No Warning";
	}

	// ...
	CString str_msg;
	int i;

	for(i=0; i < 32; i++)
	{	
		DWORD check_bit = (code_value >> i) & 0x01;
		if(check_bit == 0x00)
		{
			continue;
		}

		if(i == 0)
		{
			str_msg += "Excessively Following Error";
			str_msg += "\n";
			str_msg += "���� �Ķ��Ÿ�� [Deviation Abnormal Detection Error Level]���� ������ �����ϰ�,";
			str_msg += "\n";
			str_msg += "���� �Ķ��Ÿ [Deviation Abnormal Detection]�� ���� ���.";
		}
		if(i == 1)
		{
			str_msg += "Setting Parameter Error";
			str_msg += "\n";
			str_msg += "�Ķ��Ÿ�� ���� ������ ����� ���.";
			str_msg += "\n";
		}
		if(i == 2)
		{
			str_msg += "Fixed Parameter Error";
			str_msg += "\n";
			str_msg += "�Ķ��Ÿ�� ���� ������ ����� ���.";
			str_msg += "\n";
		}
		if(i == 3)
		{
			str_msg += "Servo Driver Error";
			str_msg += "\n";
			str_msg += "�������� ������ ���� ��� �߻��� ���.";
			str_msg += "\n";
		}
		if(i == 4)
		{
			str_msg += "Motion Command Setting Error";
			str_msg += "\n";
			str_msg += "����� �� ���� ��� �ڸǵ带 �����߽��ϴ�.";
			str_msg += "\n";
		}
		if(i == 5)
		{
			str_msg += "Reserved";
			str_msg += "\n";
		}
		if(i == 6)
		{
			str_msg += "Positive Overtravel";
			str_msg += "\n";
			str_msg += "�Ķ��Ÿ�� ������ ����, ������ ����Ʈ������ ��ȿ�� �Ǿ��ִ� ���¿��� ������ ����Ʈ���� ��ȣ�� �Էµ� ���.";
			str_msg += "\n";
		}
		if(i == 7)
		{
			str_msg += "Negative Overtravel";
			str_msg += "\n";
			str_msg += "�Ķ��Ÿ�� ������ ����, ������ ����Ʈ������ ��ȿ�� �Ǿ��ִ� ���¿��� ������ ����Ʈ���� ��ȣ�� �Էµ� ���.";
			str_msg += "\n";
		}
		if(i == 8)
		{
			str_msg += "Servo Not On";
			str_msg += "\n";
			str_msg += "�Ķ��Ÿ���� Servo On�� �����Ǿ�����, �����δ� Servo On�� ���� ���� ���.";
			str_msg += "\n";
		}
		if(i == 9)
		{
			str_msg += "Servo Driver Communication Warining";	
			str_msg += "\n";
			str_msg += "Mechatrolin ����̻��� 1ȸ ������ ���.";
			str_msg += "\n";
		}

		return str_msg;
	}

	return "Unknown Warning";
}

CString CObj__RTU_SERIAL
::Get__ALARM_OF_MONITORING_PARAMETER(DWORD code_value)
{
	if(code_value == 0x00)
	{
		return "No Alarm";
	}

	// ...
	CString str_msg;
	int i;

	for(i=0; i < 32; i++)
	{	
		DWORD check_bit = (code_value >> i) & 0x01;
		if(check_bit == 0x00)
		{
			continue;
		}

		if(i == 0)
		{
			str_msg += "Servo Driver Error";
			str_msg += "�������� ������ ���� �˶��� �߻��� ���.";
		}
		if(i == 1)
		{
			str_msg += "Positive Overtravel";
			str_msg += "����Ʈ���� ��ȣ�� �Էµ� ���¿��� ���������� �̵������� ���߽��ϴ�.";
		}
		if(i == 2)
		{
			str_msg += "Negative Overtravel";
			str_msg += "������ ����Ʈ���� ��ȣ�� �Էµ� ���¿��� ���������� �̵������� ���߽��ϴ�.";
		}
		if(i == 3)
		{
			str_msg += "Positive Soft Limit";
			str_msg += "�� ������ ���� ���� �࿡�� ������ ����Ʈ ������ ��ȿ,";
			str_msg += "���ÿ� ���� ���� �Ϸ���¿� �ִ� ��쿡 ������ ����Ʈ ���԰��� �Ѵ� �̵������� �̷�������ϴ�.";
		}
		if(i == 4)
		{
			str_msg += "Negative Soft Limit";
			str_msg += "�� ������ ���� ���� �࿡�� ������ ����Ʈ ������ ��ȿ,";
			str_msg += "���ÿ� ���� ���� �Ϸ���¿� �ִ� ��쿡 ������ ����Ʈ ���԰��� �Ѵ� �̵������� �̷�������ϴ�.";
		}
		if(i == 5)
		{
			str_msg += "Servo Off";
			str_msg += "Servo Off���¿��� �̵����� ��� �ڸǵ带 ������ ���.";
		}
		if(i == 6)
		{
			str_msg += "Positioning Time Over";
			str_msg += "�й� �Ϸᰡ �ǰ� ���� ���� �Ķ��Ÿ [Position Complete Timeout]�� �ʰ��Ͽ��� ��ġ���� �Ϸ���°� ���� �ʴ� ���.";
		}
		if(i == 7)
		{
			str_msg += "Excessive Positioning Moveing Amount";
			str_msg += "��ġ���� �̵����� ���������� �ʰ��� �̵����� ���ɵ� ���.";
		}
		if(i == 8)
		{
			str_msg += "Excessive Speed";
			str_msg += "���������� �ʰ��� �ӵ� ������ �̷���� ���.";
		}
		if(i == 9)
		{
			str_msg += "Excessively Following Error";
			str_msg += "���� �Ķ��Ÿ�� [Deviation Abnormal Detection Error Level]���� �˶��� �����ϰ�,";
			str_msg += "��ġ������ ���� �Ķ��Ÿ [Deviation Abnormal Detection]�� ���� ���.";
		}
		if(i == 10)
		{
			str_msg += "Filter Type Change Error";
			str_msg += "�й� �̿Ϸ� ���¿��� ���� Ÿ���� ������ �̷���� ���.";
		}
		if(i == 11)
		{
			str_msg += "FilterTime Constant Change Error";
			str_msg += "�й� �̿Ϸ� ���¿��� ���� �������� ������ �̷���� ���.";
		}
		if(i == 12)
		{
			str_msg += "Zero Point Not Set";
			str_msg += "���� ���� ���� ������ ����ϴ� ��쿡 ���� ������ �̷������ ���� ���¿��� �̵������� ������ ���.";
		}
		if((i >= 13) && (i <= 14))
		{
			str_msg += "Reserved";
			str_msg += "�ý��ۿ�";
		}
		if(i == 15)
		{
			str_msg += "Servo Driver Synchronization Communication Error";
			str_msg += "Mechatrolink �������� ��������̻��� ������ ���.";
		}
		if(i == 16)
		{
			str_msg += "Servo Driver Communication Error";
			str_msg += "Mechatrolink �������� ����̻��� 2ȸ �����Ͽ� ������ ���.";
		}
		if(i == 17)
		{
			str_msg += "Servo Driver Command Timeout Error";
			str_msg += "Mechatrolink ������ ������ ����� �����ð� ���� �Ϸ����� ���� ���.";
		}
		if(i == 18)
		{
			str_msg += "ABS Encoder Count Exceeded";
			str_msg += "����ġ ���ڴ��� ȸ������ ����� �� �ִ� ������ ������ ���.";
		}
		if((i >= 19) && (i <= 29))
		{
			str_msg += "Reserved";
		}
		if(i == 30)
		{
			str_msg += "Servopack Motor Type Mismatch";
		}
		if(i == 31)
		{
			str_msg += "Servopack Encoder Type Mismatch";
		}

		return str_msg;
	}

	return "Unknown Alarm";
}
