#pragma once


// ...
#define _CFG__ESC_CH_SIZE                   3

// ...
#define CFG__AXIS_SIZE						1

#define CFG_SIZE__PROC_POS					3
#define PROC_POS__DOWN						0
#define PROC_POS__MIDDLE					1
#define PROC_POS__UP						2

#define CFG_SIZE__TRANSFER_POS				4
#define TRANSFER_POS__DOWN					0
#define TRANSFER_POS__MIDDLE_DOWN			1
#define TRANSFER_POS__MIDDLE_UP				2
#define TRANSFER_POS__UP					3


// ...
#define STR__HMETHOD_DEC1_C					"HMETHOD_DEC1_C"			// 0
#define STR__HMETHOD_ZERO					"HMETHOD_ZERO"				// 1
#define STR__HMETHOD_DEC1_ZERO				"HMETHOD_DEC1_ZERO"			// 2
#define STR__HMETHOD_C						"HMETHOD_C"					// 3
#define STR__HMETHOD_DEC2_ZERO		        "HMETHOD_DEC2_ZERO"			// 4
#define STR__HMETHOD_DEC1_L_ZERO			"HMETHOD_DEC1_L_ZERO"		// 5
#define STR__HMETHOD_DEC2_C					"HMETHOD_DEC2_C"			// 6
#define STR__HMETHOD_DEC1_L_C				"HMETHOD_DEC1_L_C"			// 7

#define STR__HMETHOD_C_ONLY					"HMETHOD_C_ONLY"			// 11
#define STR__HMETHOD_POT_C					"HMETHOD_POT_C"				// 12
#define STR__HMETHOD_POT_ONLY				"HMETHOD_POT_ONLY"			// 13
#define STR__HMETHOD_HOMELS_C				"HMETHOD_HOMELS_C"			// 14
#define STR__HMETHOD_HOMELS_ONLY			"HMETHOD_HOMELS_ONLY"		// 15
#define STR__HMETHOD_NOT_C					"HMETHOD_NOT_C"				// 16
#define STR__HMETHOD_NOT_ONLY				"HMETHOD_NOT_ONLY"			// 17
#define STR__HMETHOD_INPUT_C				"HMETHOD_INPUT_C"			// 18
#define STR__HMETHOD_INPUT_ONLY				"HMETHOD_INPUT_ONLY"		// 19

// ...
#define STR__NEGATIVE						"NEGATIVE"
#define STR__POSITIVE						"POSITIVE"

#define STR__ON								"ON"
#define STR__OFF							"OFF"

#define STR__YES							"YES"
#define STR__NO								"NO"

#define STR__ONLINE							"ONLINE"
#define STR__OFFLINE						"OFFLINE"

#define STR__NONE							"NONE"

// ...
#define STR__MOVING							"MOVING"
#define STR__HOME							"HOME"

#define STR__DOWN							"DOWN"
#define STR__UP								"UP"
#define STR__MIDDLE							"MIDDLE"

#define STR__PROC_DOWN						"PROC.DOWN"
#define STR__PROC_MIDDLE					"PROC.MIDDLE"
#define STR__PROC_UP						"PROC.UP"

#define STR__MIDDLE_DOWN					"MIDDLE.DOWN"
#define STR__MIDDLE_UP						"MIDDLE.UP"

#define STR__DECHUCKED						"DECHUCKED"


// ...
#define _IO_Cmd__IDLE						"IDLE"

#define _IO_Cmd__HOME						"HOME"
#define _IO_Cmd__GOTO						"GOTO"

#define _IO_Cmd__JOG_UP						"JOG.UP"
#define _IO_Cmd__JOG_DOWN					"JOG.DOWN"

#define _IO_Cmd__STOP						"STOP"

#define _IO_Cmd__ALARM_RESET				"ALARM.RESET"

#define _IO_Cmd__SERVO_OFF					"SERVO.OFF"
#define _IO_Cmd__SERVO_ON					"SERVO.ON"

