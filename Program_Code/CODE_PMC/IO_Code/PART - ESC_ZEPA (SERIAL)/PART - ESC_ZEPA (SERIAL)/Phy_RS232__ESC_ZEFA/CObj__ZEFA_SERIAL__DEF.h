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
#define CMD__LIAISE					";:"					// 여러 명령을 그룹으로 이어주는 설정 - Set) OUTP ON;:OUTP?<LF> -> 응답 1<LF> : Output On설정과 동시에 Output 상태를 Read할 수 있다.
#define CMD__OUTPUT					"OUTP "					// HV OUTPUT ON/OFF 설정 - Set) OUTP ON<LF> -> HV On
#define CMD__TOGGLE					"TOGG "
#define CMD__OUTPUT_STATE_READ		"OUTP?"					// HV On/Off 상태 Read
#define CMD__TOGGLE_STATE_READ		"TOGG?"					// Toggle On/Off 상태 Read
#define CMD__LOCAL					"SYST:LOC"
#define CMD__REMOTE					"SYST:REM"
#define CMD__ONLY_VOLT_CHANGE		"VOLT "					// HV On중에 Volt를 변경할 경우, (극성은 변경할 수 없다) - Set) VOLT(space)2500,-2500<LF> -> Ch1 2500V, Ch2 -2500V
#define CMD__SETVOLT_READ			"VOLT? (@1,2)"			// 현재 설정되어 있는 Volt값 Read
#define CMD__VOLT_READ				"MEAS:VOLT? (@1,2)"		// 현재 출력되는 Volt값 Read - 응답 : V+0200;V-200<LF>   ->  Ch1 200V, Ch2 -200V
#define CMD__CURR_READ				"MEAS:CURR? (@1,2)"		// 현재 출력되는 Curr값 Read - 응답 : A+1000;A+1000<LF>  ->  Ch1 1mA,  Ch2 1mA
#define CMD__CFG_VOLT_SET			"CONF:VOLT "			// 
#define CMD__CFG_VOLT_READ			"CONF:VOLT? (@1,2)"		// 
#define CMD__CFG_CURRLIMIT_SET		"CONF:CURR "			// CurrentLimit 설정  - Set) CONF:CURR(space)0.001,0.001<LF> -> Ch1 1mA. Ch2 1mA
#define CMD__CFG_CURRLIMIT_READ		"CONF:CURR? (@1,2)"		// 현재 설정되어 있는 Curr Limit값 Read  - 응답 : A+1000;A+1000<LF> -> Ch1 1mA, Ch2 1mA
#define CMD__RAMPUP_SET				"CONF:RAMP UP,"			// RampUp Time 설정   - Set) CONF:RAMP(space)UP,300<LF>   -> RampUp Time 0.3sec //Ch1, Ch2 구분 없음
#define CMD__RAMPDN_SET				"CONF:RAMP DOWN,"		// RampDown Time 설정 - Set) CONF:RAMP(space)DOWN,500<LF> -> RampUp Time 0.5sec	//Ch1, Ch2 구분 없음
#define CMD__RAMPUP_READ			"CONF:RAMP? UP"			// 현재 설정되어 있는 RampUp Time Read   - 응답 : 300<LF>	//Ch1, Ch2 구분 없음
#define CMD__RAMPDN_READ			"CONF:RAMP? DOWN"		// 현재 설정되어 있는 RampDown Time Read - 응답 : 300<LF>	//Ch1, Ch2 구분 없음
#define CMD__STATE_READ				"STAT?"					// 응답 : V+0000;V+0000;A+0000;A+0000;0;0;1<LF> -> Ch1전압;Ch2전압;Ch1전류;Ch2전류;OUTPUT상태;TOGGLE상태;REMOTE상태 
#define CMD__AUTO_TOGG				"AT "					// Auto Toggle 사용 여부 설정 - AT(space)1<LF> -> 1 : 사용, 0 : 미사용
#define CMD__AUTO_TOGG_READ			"AT?"					// 응답 : 1<LF> 또는 0<LF> -> 1 : 사용중, 0 : 미사용중
#define CMD__AUTO_TOGG_CNT			"AT:COUNT "				// Auto Toggle Count설정 - Set) AT:COUNT(space)2<LF> -> Auto Toggle 2회 설정
#define CMD__AUTO_TOGG_CNT_READ		"AT:COUNT?"				// 현재 설정되어 있는 Auto Toggle Count Read - 응답 : 2<LF> -> 2회 설정
#define CMD__AUTO_TOGG_VOLT			"AT:VOLT "				// Auto Toggle 시의 Volt 설정 - Set) AT:VOLT(space)2500<LF> -> 2.5kV로 설정
#define CMD__AUTO_TOGG_VOLT_READ	"AT:VOLT?"				// 현재 설정되어 있는 Auto Toggle Volt Read - 응답 : 2500<LF>
#define CMD__ERROR_READ				"SYST:ERR?"				// 현재 Error 상태 Read
#define CMD__VERSION_READ			"SYST:VERS?"			// 현재 System Ver. Read
#define CMD__BEEPER					"SYST:BEEP"				// Controller에서 Boozer 울림
#define CMD__ERR_RESET				"*CLS"					// Error Reset
#define CMD__POWER_RESET			"*RST"					// Power Supply Reset
#define CMD__IDENTITY				"*IDN?"					// 응답 : 제조사,모델명,시리얼번호,펌웨어버젼<LF> ZEFATEK,DXM2.5K-DR,1808271001,5.1

