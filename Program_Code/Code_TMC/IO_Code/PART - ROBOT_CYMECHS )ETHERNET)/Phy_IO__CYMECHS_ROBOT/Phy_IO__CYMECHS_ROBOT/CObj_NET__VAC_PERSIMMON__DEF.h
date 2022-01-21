#pragma once

#include "CCommon_SYSTEM.h"


// ...
enum {NORMAL, ACTIVE_HAND_OFF};

// ...
#define  STR__ENABLE				"ENABLE"
#define  STR__DISABLE				"DISABLE"

#define  STR__ONLINE				"ONLINE"
#define  STR__OFFLINE				"OFFLINE"

#define  STR__HOME					"HOME"

#define  STR__ROTATE				"ROTATE"
#define  STR__EXTEND				"EXTEND"
#define  STR__RETRACT				"RETRACT"

#define  STR__NONE					"NONE"
#define  STR__EXIST					"EXIST"
#define  STR__UNKNOWN				"UNKNOWN"

#define  STR__OPEN					"OPEN"
#define  STR__CLOSE					"CLOSE"

#define  STR__YES					"YES"
#define  STR__NO					"NO"

#define  STR__CLAMP					"CLAMP"
#define  STR__UNCLAMP				"UNCLAMP"

#define  STR__LOAD					"LOAD"
#define  STR__UNLOAD				"UNLOAD"

// ...
#define  STR__Unknown				"Unknown"
#define  STR__Idle					"Idle"
#define  STR__Busy					"Busy"

// ...
#define  ARM_A						"A"
#define  ARM_B						"B"

// ...
#define  _RDY						"_RDY"
#define  _ERR						"_ERR"

// ...
#define _TO__QUERY					1.0				// 1.0  sec
#define _TO__ACT					50.0			// 50.0 sec


// ...
#define _Cmmd__AGoto				"AGoto"
#define _Cmmd__AGoto_Offset			"AGoto_Offset"
#define _Cmmd__BGoto				"BGoto"
#define _Cmmd__BGoto_Offset			"BGoto_Offset"

#define _Cmmd__APick_Act			"APick_Act"
#define _Cmmd__APick_Extend			"APick_Extend"
#define _Cmmd__APick_Retract		"APick_Retract"

#define _Cmmd__BPick_Act			"BPick_Act"
#define _Cmmd__BPick_Extend			"BPick_Extend"
#define _Cmmd__BPick_Retract		"BPick_Retract"

#define _Cmmd__APlace_Act			"APlace_Act"
#define _Cmmd__APlace_Extend		"APlace_Extend"
#define _Cmmd__APlace_Retract		"APlace_Retract"

#define _Cmmd__BPlace_Act			"BPlace_Act"
#define _Cmmd__BPlace_Extend		"BPlace_Extend"
#define _Cmmd__BPlace_Retract		"BPlace_Retract"

#define _Cmmd__APlace_Offset		"APlace_Offset"
#define _Cmmd__BPlace_Offset		"BPlace_Offset"
#define _Cmmd__HomeAll				"HomeAll"
#define _Cmmd__HomeR				"HomeR"
#define _Cmmd__Reset				"Reset"
#define _Cmmd__LoadA				"LoadA"
#define _Cmmd__LoadB				"LoadB"
#define _Cmmd__UnloadA				"UnloadA"
#define _Cmmd__UnloadB				"UnloadB"
#define _Cmmd__ChkLoad				"ChkLoad"
#define _Cmmd__ChkLoadA				"ChkLoadA"
#define _Cmmd__ChkLoadB				"ChkLoadB"
#define _Cmmd__ASet_Cptr_On			"ASet_Cptr_On"
#define _Cmmd__ASet_Cptr_Off		"ASet_Cptr_Off"
#define _Cmmd__BSet_Cptr_On			"BSet_Cptr_On"
#define _Cmmd__BSet_Cptr_Off		"BSet_Cptr_Off"
#define _Cmmd__AGet_Cptr			"AGet_Cptr"
#define _Cmmd__BGet_Cptr			"BGet_Cptr"
#define _Cmmd__Wfr_Cen_Data			"Wfr_Cen_Data"
#define _Cmmd__AGet_Current_Stn		"AGet_Current_Stn"
#define _Cmmd__BGet_Current_Stn		"BGet_Current_Stn"
#define _Cmmd__ASet_Stn				"ASet_Stn"
#define _Cmmd__BSet_Stn				"BSet_Stn"
