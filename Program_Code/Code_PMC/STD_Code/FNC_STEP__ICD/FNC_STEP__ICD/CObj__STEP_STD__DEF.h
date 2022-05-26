#pragma once


// ...
#define  _CFG__MFC_SIZE					20
#define  _CFG__PT_SIZE					20

#define  _CFG__SH_SIZE					1
#define  _CFG__WALL_SIZE				1


// ...
#define  _ACT_CMD__IDLE					"IDLE"
#define  _ACT_CMD__START				"START"
#define  _ACT_CMD__ABORT				"ABORT"
#define  _ACT_CMD__END					"END"
#define  _ACT_CMD__SKIP					"SKIP"
#define  _ACT_CMD__PAUSE				"PAUSE"
#define  _ACT_CMD__RESUME				"RESUME"
#define  _ACT_CMD__JUMP					"JUMP"
#define  _ACT_CMD__ALARM				"ALARM"

#define  _CMD_ID__ABORT					-1
#define  _CMD_ID__START					 1
#define  _CMD_ID__PAUSE					 2
#define  _CMD_ID__END					 3
#define  _CMD_ID__SKIP					 4
#define  _CMD_ID__JUMP					 5


// ...
#define  _APC_CMD__POSITION				"POSITION"
#define  _APC_CMD__PRESSURE				"PRESSURE"
#define  _APC_CMD__CLOSE				"CLOSE"
#define  _APC_CMD__OPEN					"OPEN"

#define  _MFC_CMD__CONTROL				"CONTROL"
#define  _MFC_CMD__RAMP_CTRL			"RAMP.CTRL"
#define  _MFC_CMD__CLOSE				"CLOSE"

#define  _RF_CMD__SET_POWER				"SET_POWER"
#define  _RF_CMD__OFF					"OFF"

#define  _PULSE_CMD__PARA_RCP_ON		"PARA_RCP.ON"
#define  _PULSE_CMD__PARA_RCP_OFF		"PARA_RCP.OFF"

#define  _MAT_CMD__PROC_CTRL			"PROC.CTRL"

#define  _ESC_CMD__CHUCK_PROC			"CHUCK.PROC"
#define  _ESC_CMD__CHUCK1_PROC			"CHUCK1.PROC"
#define  _ESC_CMD__CHUCK2_PROC			"CHUCK2.PROC"
#define  _ESC_CMD__DECHUCK				"DECHUCK"
#define  _ESC_CMD__DECHUCK1				"DECHUCK1"
#define  _ESC_CMD__DECHUCK2				"DECHUCK2"
#define  _ESC_CMD__HE_SET_PROC			"HE_SET.PROC"
#define  _ESC_CMD__HE_CLOSE				"HE.CLOSE"

#define  _PIN_CMD__DOWN					"DOWN"
#define  _PIN_CMD__MIDDLE				"MIDDLE"
#define  _PIN_CMD__UP					"UP"

#define  _EPD_CMD__INIT					"INIT"
#define  _EPD_CMD__IDLE					"IDLE"
#define  _EPD_CMD__DETECT				"EPD.DETECT"
#define  _EPD_CMD__ERROR_CHECK			"ERROR.CHECK"


// ...
#define  STR__Stable					"Stable"
#define  STR__Time						"Time"
#define  STR__High_Vac					"High.Vac"
#define  STR__OverEtch					"OverEtch"
#define  STR__EndPT						"EndPT"
#define  STR__End						"End"

#define  STR__Position					"Position"
#define  STR__Pressure					"Pressure"
#define  STR__Close						"Close"
#define  STR__Open						"Open"

#define  STR__NoChange					"NoChange"
#define  STR__Chuck						"Chuck"
#define  STR__Chuck1					"Chuck1"
#define  STR__Chuck2					"Chuck2"
#define  STR__He_Set					"He.Set"
#define  STR__Dechuck					"Dechuck"
#define  STR__Dechuck1					"Dechuck1"
#define  STR__Dechuck2					"Dechuck2"

#define  STR__Down						"Down"
#define  STR__Middle					"Middle"
#define  STR__Up						"Up"

// ...
#define  STR__ON						"ON"
#define  STR__ENABLE					"ENABLE"

#define  STR__YES						"YES"
#define  STR__NO						"NO"
