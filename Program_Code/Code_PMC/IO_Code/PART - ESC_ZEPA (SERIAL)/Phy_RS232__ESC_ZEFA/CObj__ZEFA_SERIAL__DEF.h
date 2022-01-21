#pragma once


// ...
#define _CFG__ERR_LINE_MAX			5


// ...
#define STR__OFFLINE				"OFFLINE"
#define STR__ONLINE					"ONLINE"

#define STR__REMOTE					"REMOTE"
#define STR__LOCAL					"LOCAL"

#define STR__1						"1"
#define STR__0						"0"

#define STR__YES					"YES"
#define STR__NO						"NO"

#define STR__OFF					"OFF"
#define STR__ON			    		"ON"
#define STR__SET		    		"SET"


// ...
#define CMD__LIAISE					";:"					// ���� ����� �׷����� �̾��ִ� ���� - Set) OUTP ON;:OUTP?<LF> -> ���� 1<LF> : Output On������ ���ÿ� Output ���¸� Read�� �� �ִ�.
#define CMD__OUTPUT					"OUTP "					// HV OUTPUT ON/OFF ���� - Set) OUTP ON<LF> -> HV On
#define CMD__TOGGLE					"TOGG "
#define CMD__OUTPUT_STATE_READ		"OUTP?"					// HV On/Off ���� Read
#define CMD__TOGGLE_STATE_READ		"TOGG?"					// Toggle On/Off ���� Read
#define CMD__LOCAL					"SYST:LOC"
#define CMD__REMOTE					"SYST:REM"
#define CMD__ONLY_VOLT_CHANGE		"VOLT "					// HV On�߿� Volt�� ������ ���, (�ؼ��� ������ �� ����) - Set) VOLT(space)2500,-2500<LF> -> Ch1 2500V, Ch2 -2500V
#define CMD__SETVOLT_READ			"VOLT? (@1,2)"			// ���� �����Ǿ� �ִ� Volt�� Read
#define CMD__VOLT_READ				"MEAS:VOLT? (@1,2)"		// ���� ��µǴ� Volt�� Read - ���� : V+0200;V-200<LF>   ->  Ch1 200V, Ch2 -200V
#define CMD__CURR_READ				"MEAS:CURR? (@1,2)"		// ���� ��µǴ� Curr�� Read - ���� : A+1000;A+1000<LF>  ->  Ch1 1mA,  Ch2 1mA
#define CMD__CFG_VOLT_SET			"CONF:VOLT "			// 
#define CMD__CFG_VOLT_READ			"CONF:VOLT? (@1,2)"		// 
#define CMD__CFG_CURRLIMIT_SET		"CONF:CURR "			// CurrentLimit ����  - Set) CONF:CURR(space)0.001,0.001<LF> -> Ch1 1mA. Ch2 1mA
#define CMD__CFG_CURRLIMIT_READ		"CONF:CURR? (@1,2)"		// ���� �����Ǿ� �ִ� Curr Limit�� Read  - ���� : A+1000;A+1000<LF> -> Ch1 1mA, Ch2 1mA
#define CMD__RAMPUP_SET				"CONF:RAMP UP,"			// RampUp Time ����   - Set) CONF:RAMP(space)UP,300<LF>   -> RampUp Time 0.3sec //Ch1, Ch2 ���� ����
#define CMD__RAMPDN_SET				"CONF:RAMP DOWN,"		// RampDown Time ���� - Set) CONF:RAMP(space)DOWN,500<LF> -> RampUp Time 0.5sec	//Ch1, Ch2 ���� ����
#define CMD__RAMPUP_READ			"CONF:RAMP? UP"			// ���� �����Ǿ� �ִ� RampUp Time Read   - ���� : 300<LF>	//Ch1, Ch2 ���� ����
#define CMD__RAMPDN_READ			"CONF:RAMP? DOWN"		// ���� �����Ǿ� �ִ� RampDown Time Read - ���� : 300<LF>	//Ch1, Ch2 ���� ����
#define CMD__STATE_READ				"STAT?"					// ���� : V+0000;V+0000;A+0000;A+0000;0;0;1<LF> -> Ch1����;Ch2����;Ch1����;Ch2����;OUTPUT����;TOGGLE����;REMOTE���� 
#define CMD__AUTO_TOGG				"AT "					// Auto Toggle ��� ���� ���� - AT(space)1<LF> -> 1 : ���, 0 : �̻��
#define CMD__AUTO_TOGG_READ			"AT?"					// ���� : 1<LF> �Ǵ� 0<LF> -> 1 : �����, 0 : �̻����
#define CMD__AUTO_TOGG_CNT			"AT:COUNT "				// Auto Toggle Count���� - Set) AT:COUNT(space)2<LF> -> Auto Toggle 2ȸ ����
#define CMD__AUTO_TOGG_CNT_READ		"AT:COUNT?"				// ���� �����Ǿ� �ִ� Auto Toggle Count Read - ���� : 2<LF> -> 2ȸ ����
#define CMD__AUTO_TOGG_VOLT			"AT:VOLT "				// Auto Toggle ���� Volt ���� - Set) AT:VOLT(space)2500<LF> -> 2.5kV�� ����
#define CMD__AUTO_TOGG_VOLT_READ	"AT:VOLT?"				// ���� �����Ǿ� �ִ� Auto Toggle Volt Read - ���� : 2500<LF>
#define CMD__ERROR_READ				"SYST:ERR?"				// ���� Error ���� Read
#define CMD__VERSION_READ			"SYST:VERS?"			// ���� System Ver. Read
#define CMD__BEEPER					"SYST:BEEP"				// Controller���� Boozer �︲
#define CMD__ERR_RESET				"*CLS"					// Error Reset
#define CMD__POWER_RESET			"*RST"					// Power Supply Reset
#define CMD__IDENTITY				"*IDN?"					// ���� : ������,�𵨸�,�ø����ȣ,�߿������<LF> ZEFATEK,DXM2.5K-DR,1808271001,5.1

