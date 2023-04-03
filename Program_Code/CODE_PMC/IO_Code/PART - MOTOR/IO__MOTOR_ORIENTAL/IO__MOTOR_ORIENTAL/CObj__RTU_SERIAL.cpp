#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"

#include "CCommon_Utility.h"


//--------------------------------------------------------------------------------
CObj__RTU_SERIAL::CObj__RTU_SERIAL()
{

}
CObj__RTU_SERIAL::~CObj__RTU_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__RTU_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__HOME, "HOME");

		// TRANSFER ...
		ADD__CTRL_VAR(sMODE__DOWN, "DOWN");
		ADD__CTRL_VAR(sMODE__UP,   "UP");

		ADD__CTRL_VAR(sMODE__MIDDLE_DOWN, "MIDDLE.DOWN");
		ADD__CTRL_VAR(sMODE__MIODLE_UP,   "MIDDLE.UP");

		ADD__CTRL_VAR(sMODE__RETURN, "RETURN");

		// PROCESS ...
		ADD__CTRL_VAR(sMODE__PROC_DOWN,   "PROC.DOWN");
		ADD__CTRL_VAR(sMODE__PROC_MIDDLE, "PROC.MIDDLE");
		ADD__CTRL_VAR(sMODE__PROC_UP,     "PROC.UP");

		// CYCLE ...
		ADD__CTRL_VAR(sMODE__CYCLE_DOWN_UP,      "CYCLE.DOWN_UP");
		ADD__CTRL_VAR(sMODE__CYCLE_PROC_DOWN_UP, "CYCLE_PROC.DOWN_UP");

		// TEACH ...
		ADD__CTRL_VAR(sMODE__TEACH_ABS_UP,    "TEACH.ABS_UP");
		ADD__CTRL_VAR(sMODE__TEACH_ABS_DOWN,  "TEACH.ABS_DOWN");
		
		ADD__CTRL_VAR(sMODE__TEACH_JOG_PLUS,  "TEACH.JOG_PLUS");
		ADD__CTRL_VAR(sMODE__TEACH_JOG_MINUS, "TEACH.JOG_MINUS");

		//
		ADD__CTRL_VAR(sMODE__MOVE_STOP, "MOVE.STOP");

		ADD__CTRL_VAR(sMODE__CHECK_ALARM, "CHECK.ALARM");
		ADD__CTRL_VAR(sMODE__CLEAR_ALARM, "CLEAR.ALARM");
		ADD__CTRL_VAR(sMODE__CLEAR_SERVO_ALARM, "CLEAR.SERVO_ALARM");

		ADD__CTRL_VAR(sMODE__SERVO_ON,    "SERVO.ON");
		ADD__CTRL_VAR(sMODE__SERVO_OFF,   "SERVO.OFF");
	}
	return 1;
}
int CObj__RTU_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1
#define  MON_ID__VIEW_REQ				2

#define  APP_DSP__MON_MODE				"IDLE  RUN"
#define  APP_DSP__OFF_ON				"OFF   ON"


int CObj__RTU_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString str_list;
	int i;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, str_name);

		//
		str_name = "OBJ.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIME_COUNT, str_name);
	}

	// MON.PART ... 
	{
		str_name = "MON.PIN.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PIN_ERROR_ACTIVE, str_name);
	}

	// Simulation ...
	{
		str_name = "SIM.HOME.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_HOME_TIME, str_name);
		
		str_name = "SIM.MOVE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_MOVE_TIME, str_name);
	}

	// Parameter ...
	{
		str_name = "PARA.GOTO_POS.DATA_PULSE";
		STD__ADD_ANALOG(str_name, "pulse", 0, -10000, 1000000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_GOTO_POS_DATA_PULSE, str_name);

		str_name = "PARA.GOTO_POS.SPEED";
		STD__ADD_ANALOG(str_name, "mm/sec",  3, 0, 1000000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_GOTO_POS_SPEED, str_name);

		str_name = "PARA.GOTO_POS.ACCEL";
		STD__ADD_ANALOG(str_name, "mm/sec2", 3, 0, 1000000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_GOTO_POS_ACCEL, str_name);

		str_name = "PARA.GOTO_POS.DECEL";
		STD__ADD_ANALOG(str_name, "mm/sec2", 3, 0, 1000000000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_GOTO_POS_DECEL, str_name);
	}

	// Monitoring Channel ...
	{
		// ...
		{
			str_name = "MON.COMM.STS";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_COMM_STS, str_name);
		}

		// ...
		{
			str_name = "MON.LIFT_PIN.STATE";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_LIFT_PIN_STATE, str_name);

			str_name = "MON.LIFT_PIN.INFO";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_LIFT_PIN_INFO, str_name);

			//
			str_name = "MON.IO.WARNING.DATA_HEXA";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_WARNING_DATA_HEXA, str_name);

			str_name = "MON.IO.WARNING.VIEW_REQ";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_WARNING_VIEW_REQ, str_name);

			//
			str_name = "MON.IO.ALARM.DATA_HEXA";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_ALARM_DATA_HEXA, str_name);

			str_name = "MON.IO.ALARM.VIEW_REQ";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_ALARM_VIEW_REQ, str_name);

			//
			str_name = "MON.IO.LAST_ERROR.VIEW_REQ";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_IO_LAST_ERROR_VIEW_REQ, str_name);
		}
	}

	// Command Request ...
	{
		str_name = "CMMD_REQ.SAVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CMMD_REQ_SAVE, str_name);
	}

	// Config Channel ...
	{
		// ESC.VOLTAGE ...
		{
			str_name = "CFG.ESC.VOLTAGE.PIN.UP.THRESHOLD";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "V", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_ESC_VOLTAGE_PIN_UP_THRESHOLD, str_name);
		}

		// ...
		{
			str_name = "CFG.RANGE.POSITION.MIN";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 3, 0, 1, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_POSITION_MIN, str_name);

			str_name = "CFG.RANGE.POSITION.MAX";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 3, 1, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_POSITION_MAX, str_name);

			str_name = "CFG.RANGE.POSITION.DEC";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "dec", 0, 0, 6, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_POSITION_DEC, str_name);

			//
			str_name = "CFG.CONVERSION.UNIT.PULSE_TO_MM";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/pulse", 3, 0.001, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM, str_name);

			//
			str_name = "CFG.HOME.TIMEOUT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_TIMEOUT, str_name);
			
			str_name = "CFG.MOVING.TIMEOUT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 600, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MOVING_TIMEOUT, str_name);

			// ...
			str_name = "CFG.HOME.METHOD";

			str_list  = STR__HMETHOD_DEC1_C;
			str_list += " ";
			str_list += STR__HMETHOD_ZERO;
			str_list += " ";
			str_list += STR__HMETHOD_DEC1_ZERO;
			str_list += " ";
			str_list += STR__HMETHOD_C;
			str_list += " ";
			str_list += STR__HMETHOD_DEC2_ZERO;
			str_list += " ";
			str_list += STR__HMETHOD_DEC1_L_ZERO;
			str_list += " ";
			str_list += STR__HMETHOD_DEC2_C;
			str_list += " ";
			str_list += STR__HMETHOD_DEC1_L_C;
			str_list += " ";
			str_list += STR__HMETHOD_C_ONLY;
			str_list += " ";
			str_list += STR__HMETHOD_POT_C;
			str_list += " ";
			str_list += STR__HMETHOD_POT_ONLY;
			str_list += " ";
			str_list += STR__HMETHOD_HOMELS_C;
			str_list += " ";
			str_list += STR__HMETHOD_HOMELS_ONLY;
			str_list += " ";
			str_list += STR__HMETHOD_NOT_C;
			str_list += " ";
			str_list += STR__HMETHOD_NOT_ONLY;
			str_list += " ";
			str_list += STR__HMETHOD_INPUT_C;
			str_list += " ";
			str_list += STR__HMETHOD_INPUT_ONLY;

			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, str_list, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_HOME_METHOD, str_name);

			//
			str_name = "CFG.HOME.OFFSET_POS";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_OFFSET_POS, str_name);

			str_name = "CFG.HOME.SPEED";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_SPEED, str_name);

			str_name = "CFG.HOME.APPROACH";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_APPROACH, str_name);

			str_name = "CFG.HOME.CREEP";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_CREEP, str_name);

			str_name = "CFG.HOME.ACCEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_ACCEL, str_name);

			str_name = "CFG.HOME.DECEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2",  0, 1, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_DECEL, str_name);

			//
			str_name = "CFG.HOME.DIRECTION";
			
			str_list  = STR__NEGATIVE;
			str_list += " ";
			str_list += STR__POSITIVE;

			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, str_list, "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_HOME_DIRECTION, str_name);

			str_name = "CFG.HOME.OBxx05B";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "OFF ON", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_HOME_OBxx05B, str_name);

			//
			str_name = "CFG.HOME.ZERO.BASE.OFFSET";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 3, -10, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_HOME_ZERO_BASE_OFFSET, str_name);
		}

		// Teaching Config ...
		{
			str_name = "ACTIVE.MOVE.DOWN_UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__ACTIVE_MOVE_DOWN_UP, str_name);

			str_name = "ACTIVE.PROC.DOWN_UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__ACTIVE_PROC_DOWN_UP, str_name);

			//
			str_name = "TEACH.ACTIVE.JOG.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TEACH_ACTIVE_JOG_UP, str_name);
			
			str_name = "TEACH.ACTIVE.JOG.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TEACH_ACTIVE_JOG_DOWN, str_name);

			//
			str_name = "TEACH.ACTIVE.ABS.UP";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TEACH_ACTIVE_ABS_UP, str_name);

			str_name = "TEACH.ACTIVE.ABS.DOWN";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__TEACH_ACTIVE_ABS_DOWN, str_name);

			//
			str_name = "CFG.GOTO_POS.UP.ABS_POS";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm",  3, 0, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_GOTO_POS_UP_ABS_POS, str_name);

			str_name = "CFG.GOTO_POS.DOWN.ABS_POS";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm",  3, 0, 10, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_GOTO_POS_DOWN_ABS_POS, str_name);

			//
			str_name = "CFG.TEACH.JOG.SPEED";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec",  1, 0.1, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_JOG_SPEED, str_name);
			
			str_name = "CFG.TEACH.JOG.ACCEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_JOG_ACCEL, str_name);
			
			str_name = "CFG.TEACH.JOG.DECEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_JOG_DECEL, str_name);

			//
			str_name = "CFG.TEACH.ABS.SPEED";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec",  1, 0.1, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_ABS_SPEED, str_name);
			
			str_name = "CFG.TEACH.ABS.ACCEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_ABS_ACCEL, str_name);
			
			str_name = "CFG.TEACH.ABS.DECEL";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TEACH_ABS_DECEL, str_name);
		}

		// PROCESS.POS ...
		for(i=0; i<CFG_SIZE__PROC_POS; i++)
		{
			CString name_sns;
			CString name_data;
			CString name_speed;
			CString name_accel;
			CString name_decel;

			if(i == PROC_POS__DOWN)
			{
				name_sns   = "APP.PROC_POS.DOWN.SNS";
				name_data  = "CFG.PROC_POS.DOWN.DATA_POS";
				name_speed = "CFG.PROC_POS.DOWN.SPEED";
				name_accel = "CFG.PROC_POS.DOWN.ACCEL";
				name_decel = "CFG.PROC_POS.DOWN.DECEL";
			}
			else if(i == PROC_POS__MIDDLE)
			{
				name_sns   = "APP.PROC_POS.MIDDLE.SNS";
				name_data  = "CFG.PROC_POS.MIDDLE.DATA_POS";
				name_speed = "CFG.PROC_POS.MIDDLE.SPEED";
				name_accel = "CFG.PROC_POS.MIDDLE.ACCEL";
				name_decel = "CFG.PROC_POS.MIDDLE.DECEL";
			}
			else if(i == PROC_POS__UP)
			{
				name_sns   = "APP.PROC_POS.UP.SNS";
				name_data  = "CFG.PROC_POS.UP.DATA_POS";
				name_speed = "CFG.PROC_POS.UP.SPEED";
				name_accel = "CFG.PROC_POS.UP.ACCEL";
				name_decel = "CFG.PROC_POS.UP.DECEL";
			}
			else
			{
				continue;
			}

			STD__ADD_STRING(name_sns);
			LINK__VAR_STRING_CTRL(sCH__APP_PROC_POS_X_SNS[i], name_sns);

			STD__ADD_ANALOG_WITH_X_OPTION(name_data,  "mm",      3, -1000, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_POS_X_DATA_POS[i], name_data);

			STD__ADD_ANALOG_WITH_X_OPTION(name_speed, "mm/sec",  1, 0.1, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_POS_X_SPEED[i], name_speed);

			STD__ADD_ANALOG_WITH_X_OPTION(name_accel, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_POS_X_ACCEL[i], name_accel);

			STD__ADD_ANALOG_WITH_X_OPTION(name_decel, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_POS_X_DECEL[i], name_decel);
		}

		// TRNASFER.POS ...
		for(i=0; i<CFG_SIZE__TRANSFER_POS; i++)
		{
			CString name_sns;
			CString name_data;
			CString name_speed;
			CString name_accel;
			CString name_decel;

			if(i == TRANSFER_POS__DOWN)
			{
				name_sns   = "APP.TRANSFER_POS.DOWN.SNS";
				name_data  = "CFG.TRANSFER_POS.DOWN.DATA_POS";
				name_speed = "CFG.TRANSFER_POS.DOWN.SPEED";
				name_accel = "CFG.TRANSFER_POS.DOWN.ACCEL";
				name_decel = "CFG.TRANSFER_POS.DOWN.DECEL";
			}
			else if((i == TRANSFER_POS__MIDDLE_DOWN)
			     || (i == TRANSFER_POS__MIDDLE_UP  ))
			{
				if(i == TRANSFER_POS__MIDDLE_DOWN)
				{
					name_sns  = "APP.TRANSFER_POS.MIDDLE_DOWN.SNS";
					name_data = "CFG.TRANSFER_POS.MIDDLE_DOWN.DATA_POS";
				}
				else if(i == TRANSFER_POS__MIDDLE_UP)
				{
					name_sns  = "APP.TRANSFER_POS.MIDDLE_UP.SNS";
					name_data = "CFG.TRANSFER_POS.MIDDLE_UP.DATA_POS";
				}
				
				name_speed = "CFG.TRANSFER_POS.MIDDLE.SPEED";
				name_accel = "CFG.TRANSFER_POS.MIDDLE.ACCEL";
				name_decel = "CFG.TRANSFER_POS.MIDDLE.DECEL";
			}
			else if(i == TRANSFER_POS__UP)
			{
				name_sns   = "APP.TRANSFER_POS.UP.SNS";
				name_data  = "CFG.TRANSFER_POS.UP.DATA_POS";
				name_speed = "CFG.TRANSFER_POS.UP.SPEED";
				name_accel = "CFG.TRANSFER_POS.UP.ACCEL";
				name_decel = "CFG.TRANSFER_POS.UP.DECEL";
			}
			else
			{
				continue;
			}

			STD__ADD_STRING(name_sns);
			LINK__VAR_STRING_CTRL(sCH__APP_TRANSFER_POS_X_SNS[i], name_sns);

			STD__ADD_ANALOG_WITH_X_OPTION(name_data,  "mm",      0, -100, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_POS_X_DATA_POS[i], name_data);

			STD__ADD_ANALOG_WITH_X_OPTION(name_speed, "mm/sec",  1, 0.1, 1000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_POS_X_SPEED[i], name_speed);

			STD__ADD_ANALOG_WITH_X_OPTION(name_accel, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_POS_X_ACCEL[i], name_accel);

			STD__ADD_ANALOG_WITH_X_OPTION(name_decel, "mm/sec2", 1, 0.1, 1000000, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TRANSFER_POS_X_DECEL[i], name_decel);
		}

		// CYCLE TEST : TRANSFER POS ...
		{
			str_name = "CFG.MOVE.DOWN_UP.CYCLE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 9999, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_MOVE_DOWN_UP_CYCLE, str_name);
		
			str_name = "RESULT.MOVE.DOWN_UP.CYCLE";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_CYCLE, str_name);
		
			//
			str_name = "RESULT.MOVE.DOWN_UP.AVG.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_AVG_UP, str_name);
			
			str_name = "RESULT.MOVE.DOWN_UP.MIN.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MIN_UP, str_name);
			
			str_name = "RESULT.MOVE.DOWN_UP.MAX.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MAX_UP, str_name);

			//
			str_name = "RESULT.MOVE.DOWN_UP.AVG.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_AVG_DOWN, str_name);
			
			str_name = "RESULT.MOVE.DOWN_UP.MIN.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MIN_DOWN, str_name);
			
			str_name = "RESULT.MOVE.DOWN_UP.MAX.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_MOVE_DOWN_UP_MAX_DOWN, str_name);
		}
		// CYCLE TEST : PROCESS POS ...
		{
			str_name = "CFG.PROC.DOWN_UP.CYCLE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 9999, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_PROC_DOWN_UP_CYCLE, str_name);

			str_name = "RESULT.PROC.DOWN_UP.CYCLE";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_CYCLE, str_name);

			//
			str_name = "RESULT.PROC.DOWN_UP.AVG.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_AVG_UP, str_name);

			str_name = "RESULT.PROC.DOWN_UP.MIN.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_MIN_UP, str_name);

			str_name = "RESULT.PROC.DOWN_UP.MAX.UP";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_MAX_UP, str_name);

			//
			str_name = "RESULT.PROC.DOWN_UP.AVG.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_AVG_DOWN, str_name);

			str_name = "RESULT.PROC.DOWN_UP.MIN.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_MIN_DOWN, str_name);

			str_name = "RESULT.PROC.DOWN_UP.MAX.DOWN";
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__RESULT_PROC_DOWN_UP_MAX_DOWN, str_name);
		}
	}

	// Stable Channel ...
	{
		// ...
		{
			str_name = "CFG.WARNING.LIMIT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_WARNING_LIMIT, str_name);

			str_name = "CFG.FAULT.LIMIT";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_FAULT_LIMIT, str_name);

			//
			str_name = "CFG.CHECKING_TIME.FOR.STABLE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_CHECKING_TIME_FOR_STABLE, str_name);

			str_name = "CFG.CHECK_TIMEOUT.FOR.ERROR";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_CHECK_TIMEOUT_FOR_ERROR, str_name);

			str_name = "CFG.STABLE_TIME.FOR.SETPINT_CHANGE";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_STABLE_TIME_FOR_SETPINT_CHANGE, str_name);
		}

		for(i=0; i<CFG__AXIS_SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("MON.AXIS%1d.STABLE.STATE", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_STABLE_STATE[i], str_name);

			str_name.Format("MON.AXIS%1d.STABLE.TIME", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_STABLE_TIME[i], str_name);

			str_name.Format("MON.AXIS%1d.FAULT.STATE", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_FAULT_STATE[i], str_name);

			str_name.Format("MON.AXIS%1d.FAULT.TIME", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_FAULT_TIME[i], str_name);

			str_name.Format("MON.AXIS%1d.CHANGE.STATE", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_CHANGE_STATE[i], str_name);

			str_name.Format("MON.AXIS%1d.CHANGE.TIME", id);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_AXIS_CHANGE_TIME[i], str_name);
		}

		// ...
		{
			str_name = "MON.STABLE.FLAG";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_STABLE_FLAG, str_name);

			str_name = "MON.FAULT.FLAG";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__MON_FAULT_FLAG, str_name);
		}
	}


	//-------------------------------------------------------------------------
	// DRIVER.INFO ...

	// CFG.DRV ...
	{
		str_name = "CFG.DRV.DATA_BIT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "8  7","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DRV_DATA_BIT, str_name);

		str_name = "CFG.DRV.PARITY_BIT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0  1  2  3  4","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_DRV_PARITY_BIT, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.MOTOR_IDLE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MOTOR_IDLE, str_name);

		//
		str_name = "INFO.SET.POS.MM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SET_POS_MM, str_name);

		str_name = "INFO.CUR.POS.MM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_POS_MM, str_name);

		//
		str_name = "INFO.SET.POS.STEP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SET_POS_STEP, str_name);

		str_name = "INFO.CUR.POS.STEP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_POS_STEP, str_name);

		//
		str_name = "INFO.SET.VEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SET_VEL, str_name);

		str_name = "INFO.CUR.VEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_VEL, str_name);

		//
		str_name = "INFO.SET.ACCEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SET_ACCEL, str_name);

		str_name = "INFO.SET.DECEL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SET_DECEL, str_name);
	}

	// INFO.MON ...
	{
		str_name = "INFO.MON.DATA.NO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_DATA_NO, str_name);

		str_name = "INFO.MON.POS.STEP.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_POS_STEP_SET, str_name);

		str_name = "INFO.MON.VEL.RPM.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_VEL_RPM_SET, str_name);

		str_name = "INFO.MON.VEL.HZ.SET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_VEL_HZ_SET, str_name);

		str_name = "INFO.MON.POS.STEP.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_POS_STEP_CUR, str_name);

		str_name = "INFO.MON.VEL.RPM.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_VEL_RPM_CUR, str_name);

		str_name = "INFO.MON.VEL.HZ.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_VEL_HZ_CUR, str_name);

		str_name = "INFO.MON.DWELL.MSEC.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_DWELL_MSEC_CUR, str_name);

		str_name = "INFO.MON.DIRECT.IO.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_DIRECT_IO_CUR, str_name);

		str_name = "INFO.MON.TORQUE.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_TORQUE_CUR, str_name);

		str_name = "INFO.MON.MOTOR_LOAD.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MON_MOTOR_LOAD_CUR, str_name);
	}

	// INFO.DRV ...
	{
		str_name = "INFO.DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.PARAMETER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_PARAMETER, str_name);

		//
		str_name = "INFO.DRV.BYTE_0.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BYTE_0_HEXA, str_name);

		str_name = "INFO.DRV.BIT00.M0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT00_M0, str_name);

		str_name = "INFO.DRV.BIT01.M1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT01_M1, str_name);

		str_name = "INFO.DRV.BIT02.M2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT02_M2, str_name);

		str_name = "INFO.DRV.BIT03.START";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT03_START, str_name);

		str_name = "INFO.DRV.BIT04.HOME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT04_HOME, str_name);

		str_name = "INFO.DRV.BIT05.READY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT05_READY, str_name);

		str_name = "INFO.DRV.BIT06.INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT06_INFO, str_name);

		str_name = "INFO.DRV.BIT07.ALARM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT07_ALARM, str_name);

		//
		str_name = "INFO.DRV.BYTE_1.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BYTE_1_HEXA, str_name);

		str_name = "INFO.DRV.BIT08.BUSY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT08_BUSY, str_name);

		str_name = "INFO.DRV.BIT09.AREA0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT09_AREA0, str_name);

		str_name = "INFO.DRV.BIT10.AREA1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT10_AREA1, str_name);

		str_name = "INFO.DRV.BIT11.AREA2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT11_AREA2, str_name);

		str_name = "INFO.DRV.BIT12.TIM";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT12_TIM, str_name);

		str_name = "INFO.DRV.BIT13.MOVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT13_MOVE, str_name);

		str_name = "INFO.DRV.BIT14.IN_POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT14_IN_POS, str_name);

		str_name = "INFO.DRV.BIT15.TLC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_BIT15_TLC, str_name);
	}

	// SET.DRV ...
	{
		str_name = "SET.DRV.BYTE_0.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BYTE_0_HEXA, str_name);

		str_name = "SET.DRV.BIT00.M0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT00_M0, str_name);

		str_name = "SET.DRV.BIT01.M1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT01_M1, str_name);

		str_name = "SET.DRV.BIT02.M2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT02_M2, str_name);

		str_name = "SET.DRV.BIT03.START";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT03_START, str_name);

		str_name = "SET.DRV.BIT04.HOME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT04_HOME, str_name);

		str_name = "SET.DRV.BIT05.STOP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT05_STOP, str_name);

		str_name = "SET.DRV.BIT06.FREE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT06_FREE, str_name);

		str_name = "SET.DRV.BIT07.ALARM_RESET";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT07_ALARM_RESET, str_name);

		//
		str_name = "SET.DRV.BYTE_1.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BYTE_1_HEXA, str_name);

		str_name = "SET.DRV.BIT08.D_SEL0";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT08_D_SEL0, str_name);

		str_name = "SET.DRV.BIT09.D_SEL1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT09_D_SEL1, str_name);

		str_name = "SET.DRV.BIT10.D_SEL2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT10_D_SEL2, str_name);

		str_name = "SET.DRV.BIT11.SSTART";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT11_SSTART, str_name);

		str_name = "SET.DRV.BIT12.FW_JOG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT12_FW_JOG, str_name);

		str_name = "SET.DRV.BIT13.RV_JOG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT13_RV_JOG, str_name);

		str_name = "SET.DRV.BIT14.FW_POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT14_FW_POS, str_name);

		str_name = "SET.DRV.BIT15.RV_POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__SET_DRV_BIT15_RV_POS, str_name);
	}


	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__MONITOR);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__VIEW_REQ);
	}
	return 1;
}
int CObj__RTU_SERIAL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	CString str_bff;

	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__PIN.RemoveAll();

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Offline !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(STR__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__HOME_TIMEOUT;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Home Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(STR__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__MOVING_TIMEOUT;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Moving Timeout !";

		alarm_msg = "";

		l_act.RemoveAll();
		l_act.Add(STR__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__STATE_ERROR;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Motor state error !";

		alarm_msg = "Please, check the state of motor !";

		l_act.RemoveAll();
		l_act.Add(STR__CLEAR);

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__CHUCKING_STATUS_ALARM__MON;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - Chuck Status ALARM (MON) !";

		alarm_msg = "Pin Lifter can not operate.\n";
		alarm_msg = "Please, Check the Chucking Status.";

		l_act.RemoveAll();
		l_act.Add(STR__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__CHUCKING_STATUS_ALARM__ACT;
		iLIST_ALID__PIN.Add(alarm_id);

		alarm_title  = title;
		alarm_title += " PIN LIFTER - Chuck Status ALARM (ACT) !";

		alarm_msg = "Pin Lifter can not operate.\n";
		alarm_msg = "Please, Check the Chucking Status.";

		l_act.RemoveAll();
		l_act.Add(STR__RETRY);
		l_act.Add(STR__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define APP_DSP__COMM_STATUS            "OFFLINE  ONLINE"
#define APP_DSP__HEATER_ID              "1 2 3 4 5"


int CObj__RTU_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	//-------------------------------------------------------
	CString str_name;

	// Digital ...
	{
		// DO ...
		{
			str_name = "do.CTRL.SET";
			IO__ADD_DIGITAL_WRITE(str_name, "IDLE  HOME  GOTO  JOG.UP JOG.DOWN  STOP  ALARM.RESET  SERVO.OFF SERVO.ON");	
			LINK__IO_VAR_DIGITAL_CTRL(doCH__CTRL_SET, str_name);

			//
			str_name = "do.PARA.GOTO.SET";
			IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");	
			LINK__IO_VAR_DIGITAL_CTRL(doCH__PARA_GOTO_SET, str_name);
		}
	}

	// String ...
	{
		// SI ...
		{
			str_name = "si.DRIVER_STS.AUTO";
			IO__ADD_STRING_READ(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__DRIVER_STS__AUTO, str_name);

			str_name = "si.DRIVER_STS.MANUAL";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__DRIVER_STS__MANUAL, str_name);

			//
			str_name = "si.MONITOR.ALL";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "", "", "", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__MONITOR_ALL, str_name);			
		}
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__RTU_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// LINK : IO_Chammel
	{
		// PIN.STATE ...
		{
			def_name = "CH__LIFT_PIN_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LIFT_PIN_STATE, obj_name,var_name);
		}

		// ESC.CHUCK_STATE ...
		{
			def_name = "CH__ESC_CHUCK_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__ESC_CHUCK_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ESC_CHUCK_STATE, obj_name,var_name);
			}
		}
		// ESC.AI_VOLTAGE ...
		{
			def_name = "DATA__ESC_CH_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			iDATA__ESC_CH_SIZE = atoi(def_data);
			if(iDATA__ESC_CH_SIZE > _CFG__ESC_CH_SIZE)			iDATA__ESC_CH_SIZE = _CFG__ESC_CH_SIZE;

			for(i=0; i<iDATA__ESC_CH_SIZE; i++)
			{
				def_name.Format("CH__ESC_AI_VOLTAGE.%1d", i+1);
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__ESC_AI_VOLTAGE_X[i], obj_name,var_name);
			}
		}
	}

	// ...
	{
		iPARA__SLAVE_ID = 1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	if(iActive__SIM_MODE > 0)
	{
		// INFO.DRV ...
		{
			sCH__INFO_DRV_BYTE_0_HEXA->Set__DATA("0x01");
			sCH__INFO_DRV_BIT00_M0->Set__DATA("01");
			sCH__INFO_DRV_BIT01_M1->Set__DATA("02");
			sCH__INFO_DRV_BIT02_M2->Set__DATA("03");
			sCH__INFO_DRV_BIT03_START->Set__DATA("04");
			sCH__INFO_DRV_BIT04_HOME->Set__DATA("05");
			sCH__INFO_DRV_BIT05_READY->Set__DATA("06");
			sCH__INFO_DRV_BIT06_INFO->Set__DATA("07");
			sCH__INFO_DRV_BIT07_ALARM->Set__DATA("08");

			sCH__INFO_DRV_BYTE_1_HEXA->Set__DATA("0x02");
			sCH__INFO_DRV_BIT08_BUSY->Set__DATA("09");
			sCH__INFO_DRV_BIT09_AREA0->Set__DATA("10");
			sCH__INFO_DRV_BIT10_AREA1->Set__DATA("11");
			sCH__INFO_DRV_BIT11_AREA2->Set__DATA("12");
			sCH__INFO_DRV_BIT12_TIM->Set__DATA("13");
			sCH__INFO_DRV_BIT13_MOVE->Set__DATA("14");
			sCH__INFO_DRV_BIT14_IN_POS->Set__DATA("15");
			sCH__INFO_DRV_BIT15_TLC->Set__DATA("16");
		}

		// SET.DRV ...
		{
			sCH__SET_DRV_BYTE_0_HEXA->Set__DATA("0x21");
			sCH__SET_DRV_BIT00_M0->Set__DATA("21");
			sCH__SET_DRV_BIT01_M1->Set__DATA("22");
			sCH__SET_DRV_BIT02_M2->Set__DATA("23");
			sCH__SET_DRV_BIT03_START->Set__DATA("24");
			sCH__SET_DRV_BIT04_HOME->Set__DATA("25");
			sCH__SET_DRV_BIT05_STOP->Set__DATA("26");
			sCH__SET_DRV_BIT06_FREE->Set__DATA("27");
			sCH__SET_DRV_BIT07_ALARM_RESET->Set__DATA("28");

			sCH__SET_DRV_BYTE_1_HEXA->Set__DATA("0x22");
			sCH__SET_DRV_BIT08_D_SEL0->Set__DATA("31");
			sCH__SET_DRV_BIT09_D_SEL1->Set__DATA("32");
			sCH__SET_DRV_BIT10_D_SEL2->Set__DATA("33");
			sCH__SET_DRV_BIT11_SSTART->Set__DATA("34");
			sCH__SET_DRV_BIT12_FW_JOG->Set__DATA("35");
			sCH__SET_DRV_BIT13_RV_JOG->Set__DATA("36");
			sCH__SET_DRV_BIT14_FW_POS->Set__DATA("37");
			sCH__SET_DRV_BIT15_RV_POS->Set__DATA("38");
		}

		// INFO.MON ...
		{
			sCH__INFO_CUR_POS_MM->Set__DATA("Pos (mm)");

			sCH__INFO_MON_DATA_NO->Set__DATA("101");
			sCH__INFO_MON_POS_STEP_SET->Set__DATA("102");
			sCH__INFO_MON_VEL_RPM_SET->Set__DATA("103");
			sCH__INFO_MON_VEL_HZ_SET->Set__DATA("104");

			sCH__INFO_MON_POS_STEP_CUR->Set__DATA("201");
			sCH__INFO_MON_VEL_RPM_CUR->Set__DATA("202");
			sCH__INFO_MON_VEL_HZ_CUR->Set__DATA("203");
			sCH__INFO_MON_DWELL_MSEC_CUR->Set__DATA("204");
			sCH__INFO_MON_DIRECT_IO_CUR->Set__DATA("205");
			sCH__INFO_MON_TORQUE_CUR->Set__DATA("206");
			sCH__INFO_MON_MOTOR_LOAD_CUR->Set__DATA("207");
		}
	}

	return 1;
}
int CObj__RTU_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 115200;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 2;			// 0 ~ 4 : None, Odd, Even, Mark, Space

	// ...
	{
		CString str_cmmd;
		CString str_data;

		// 1.
		{
			str_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(str_cmmd, str_data) > 0)
			{
				com_port = atoi(str_data);
			}
		}

		// ...
		CString str_info;

		str_info.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(str_info);
	}

	// ...
	{
		CString ch_data;

		ch_data = dCH__CFG_DRV_DATA_BIT->Get__STRING();
		nByte = atoi(ch_data);

		ch_data = dCH__CFG_DRV_PARITY_BIT->Get__STRING();
		nParity = atoi(ch_data);
	}

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "Connect to Serial \n";

		log_bff.Format("Com Port: %1d \n", com_port);
		log_msg += log_bff;

		log_bff.Format("Baud Rate: %1d \n", nRate);
		log_msg += log_bff;

		log_bff.Format("Data Bit: %1d \n", nByte);
		log_msg += log_bff;

		log_bff.Format("Parity Bit: %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("Stop Bit: %1d \n", nStop);
		log_msg += log_bff;

		//
		log_msg += "Terminal String : Byte Count \n";							  
	}

	// ...
	{
		CString str_info;

		str_info.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d]",
						nRate, 
						nByte, 
						nStop, 
						nParity);

		sCH__INFO_DRV_PARAMETER->Set__DATA(str_info);
	}

	if(iActive__SIM_MODE > 0)
	{
		log_msg += "Initialize RS-232 Complete \n";
		log_msg += "Simulation Mode !!! \n";

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
		return -1;
	}

	if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
	{
		log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
		log_msg += log_bff;

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
		return -1;
	}
	else
	{
		log_msg += "Initialize RS-232 Complete \n";

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__RTU_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	CString msg;
	int flag = 1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");

		Write__APP_LOG(msg);
	}

	if(bActive__ESC_CHUCK_STATE)
	{
		if(sEXT_CH__ESC_CHUCK_STATE->Check__DATA(STR__DECHUCKED) < 0)
		{
			if((mode.CompareNoCase(sMODE__CYCLE_DOWN_UP) == 0)
			|| (mode.CompareNoCase(sMODE__CYCLE_PROC_DOWN_UP) == 0)
			|| (mode.CompareNoCase(sMODE__TEACH_ABS_UP) == 0)
			|| (mode.CompareNoCase(sMODE__TEACH_JOG_PLUS) == 0)
			|| (mode.CompareNoCase(sMODE__UP) == 0)
			|| (mode.CompareNoCase(sMODE__PROC_UP) == 0))
			{
				int alm_id = ALID__CHUCKING_STATUS_ALARM__ACT;
				CString alm_msg;
				CString r_act;

				alm_msg.Format("명령[%s]을 실행 할 수 없습니다. \n", mode);
	
				p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg, r_act);

				if(r_act.CompareNoCase(STR__RETRY) == 0)
				{
					goto LOOP_RETRY;
				}

				flag = -1;
			}
		}
	}

	if(flag > 0)
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HOME)					flag = Call__HOME(p_variable,p_alarm);

		// TRANSFER ...
		ELSE_IF__CTRL_MODE(sMODE__DOWN)					flag = Call__DOWN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UP)					flag = Call__UP(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MIDDLE_DOWN)			flag = Call__MIDDLE_DOWN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MIODLE_UP)			flag = Call__MIDDLE_UP(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RETURN)				flag = 1;

		// PROCESS ...
		ELSE_IF__CTRL_MODE(sMODE__PROC_DOWN)			flag = Call__PROC_DOWN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_MIDDLE)			flag = Call__PROC_MIDDLE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PROC_UP)				flag = Call__PROC_UP(p_variable,p_alarm);

		// CYCLE ...
		ELSE_IF__CTRL_MODE(sMODE__CYCLE_DOWN_UP)
		{
			sCH__ACTIVE_MOVE_DOWN_UP->Set__DATA(STR__YES);

			flag = Call__CYCLE_DOWN_UP(p_variable,p_alarm);

			sCH__ACTIVE_MOVE_DOWN_UP->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE(sMODE__CYCLE_PROC_DOWN_UP)
		{
			sCH__ACTIVE_PROC_DOWN_UP->Set__DATA(STR__YES);

			flag = Call__CYCLE_PROC_DOWN_UP(p_variable,p_alarm);

			sCH__ACTIVE_PROC_DOWN_UP->Set__DATA("");
		}

		// TEACH ...
		ELSE_IF__CTRL_MODE(sMODE__TEACH_ABS_UP)			flag = Call__TEACH_ABS_START(p_variable,p_alarm,  1);
		ELSE_IF__CTRL_MODE(sMODE__TEACH_ABS_DOWN)		flag = Call__TEACH_ABS_START(p_variable,p_alarm, -1);

		ELSE_IF__CTRL_MODE(sMODE__TEACH_JOG_PLUS)		flag = Call__TEACH_JOG_START(p_variable,p_alarm,  1);
		ELSE_IF__CTRL_MODE(sMODE__TEACH_JOG_MINUS)		flag = Call__TEACH_JOG_START(p_variable,p_alarm, -1);

		//
		ELSE_IF__CTRL_MODE(sMODE__MOVE_STOP)			flag = Call__MOVE_STOP(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CHECK_ALARM)			flag = Call__CHECK_ALARM(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLEAR_ALARM)			flag = Call__CLEAR_ALARM(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CLEAR_SERVO_ALARM)	flag = Call__CLEAR_SERVO_ALARM(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SERVO_ON)				flag = Call__SERVO_ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SERVO_OFF)			flag = Call__SERVO_OFF(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");

		Write__APP_LOG(msg);
	}
	return flag;
}

int CObj__RTU_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)			return Mon__MONITOR(p_variable,p_alarm);
	if(id == MON_ID__VIEW_REQ)			return Mon__VIEW_REQ(p_variable,p_alarm);

	return 1;
}
