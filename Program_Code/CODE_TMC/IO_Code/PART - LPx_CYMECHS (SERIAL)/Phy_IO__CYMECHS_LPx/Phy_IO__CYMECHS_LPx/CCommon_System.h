#pragma once


// ...
#define PT__UNKNOWN				0
#define PT__CMD					1
#define PT__EVT					2
#define PT__DEFAULT				3

#define STR__CMD				"cmd"
#define STR__EVT				"event"


#define STR_UNKNOWN				"UNKNOWN"
#define STR_INITIALIZED			"INITIALIZED"
#define STR_HOMED				"HOMED"
#define STR_CLAMPED				"CLAMPED"
#define STR_UNCLAMPED			"UNCLAMPED"
#define STR_DOCKED				"DOCKED"
#define STR_UNDOCKED			"UNDOCKED"
#define STR_OPENED				"OPENED"
#define STR_CLOSED				"CLOSED"
#define STR_LOADED				"LOADED"
#define STR_UNLOADED			"UNLOADED"
#define STR_EXIST				"EXIST"

#define STR_INPROGRESS			"INPROGRESS"
#define STR_SUCCEEDED			"SUCCEEDED"
#define STR_FAILED				"FAILED"

#define STR_LAST_COMMAND		"stat_op"

#define CMD_TYPE__STAT_FXL		1


#define BIT__PLACED				0
#define BIT__DOCKED				1
#define BIT__LOWERED			2
#define BIT__UNDOCKED			3
#define BIT__CLAMPED			4
#define BIT__RELEASED			5
#define BIT__PRESENT			6


/*
Bit0 1 FOUP placed
		0 FOUP not placed
Bit1 1 FOUP docked
		0 FOUP not docked
Bit2 1 pdo lowered
		0 pdo not lowered
Bit3 1 FOUP undocked
		0 FOUP not undocked
Bit4 1 FOUP clamped
		0 FOUP not clamped
Bit5 1 FOUP released
		0 FOUP not released
Bit6 1 FOUP present
		0 FOUP not present
*/
