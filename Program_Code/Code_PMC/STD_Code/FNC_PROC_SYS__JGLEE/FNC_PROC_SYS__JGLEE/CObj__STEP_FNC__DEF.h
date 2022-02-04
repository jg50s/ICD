#pragma once


// ...
#define CFG_SIZE__MFC_OBJ				7
#define CFG_INTERLOCK__MFC_SIZE			5

#define CFG__IBx_SIZE					8
#define CFG__FNCx_SIZE					4

#define CFG__PROCESS_DECHUCK_SIZE		5


// ...
#define CFG__RF_PART_SIZE				2
#define RF_PART_INDEX__BIAS				0
#define RF_PART_INDEX__PLASMA			1

// ...
#define STR__CTCINUSE					"CTCINUSE"
#define STR__STANDBY					"STANDBY"
#define STR__MAINTMODE					"MAINTMODE"

#define STR__NONE						"NONE"

#define STR__YES						"YES"
#define STR__NO							"NO"

#define STR__LOCK						"LOCK"
#define STR__READY						"READY"
#define STR__PROC						"PROC"
#define STR__RUN						"RUN"
#define STR__START						"START"
#define STR__STOP						"STOP"

#define STR__CHECKING					"Checking"
#define STR__OK							"OK"
#define STR__ERROR						"ERROR"

#define STR__ENABLE						"ENABLE"
#define STR__DISABLE					"DISABLE"
#define STR__STEP_CTRL					"STEP_CTRL"

#define STR__WAP_POS                    "WAP_POS"
#define STR__VAT_POS                    "VAT_POS"

#define STR__ON							"ON"
#define STR__OFF						"OFF"

#define STR__OPEN						"Open"
#define STR__CLOSE						"Close"

#define STR__USE						"USE"

#define STR__INIT						"INIT"
#define STR__TEMP_AUTO_TUNE				"TEMP_AUTO_TUNE"

#define STR__PRESSURE					"Pressure"

#define STR__RETURN						"RETURN"
#define STR__RESET						"RESET"

#define STR__CTRL						"CTRL"
#define STR__AVAILABLE					"AVAILABLE"
#define STR__ABORTED					"ABORTED"

#define STR__ABORT						"ABORT"
#define STR__IGNORE						"IGNORE"

#define STR__HW							"HW"
#define STR__SW							"SW"
#define STR__RCP_CTRL					"RCP.CTRL"

#define STR__CLN						"CLN"
#define STR__PRC						"PRC"

#define STR__DECHUCKED					"DECHUCKED"

// IO Status ...
#define STR__Normal						"Normal"
#define STR__Warning					"Warning"
#define STR__Error						"Error"

#define STR__True						"True"

// FNC CHM ...
#define CMMD__BALLAST_END				"BALLAST_END"
#define CMMD__HIGH_VAC_PUMP				"HIGH_VAC_PUMP"

// APC ...
#define CMMD__APC_PRE_POS_POSITION		"PRE_POS.POSITION"
#define CMMD__APC_PRE_POS_PRESSURE		"PRE_POS.PRESSURE"
#define CMMD__APC_CLOSE					"CLOSE"
#define CMMD__APC_OPEN					"OPEN"

// CONTROL TYPE ...
#define CMMD__PRESSURE_CONTROL			"Pressure"
#define CMMD__POSITION_CONTROL			"Position"

// DGF ...
#define CMMD__DGF_ALL_CLOSE				"ALL_CLOSE"
#define CMMD__DGF_CONTROL				"CONTROL"
#define CMMD__DGF_PUMPING				"GASLINE_PUMP"

// MFC ...
#define CMMD__MFC_CONTROL				"CONTROL"
#define CMMD__MFC_CLOSE					"CLOSE"

// RF Match ...
#define CMMD__INIT						"INIT"
#define CMMD__RF_ON						"RF_ON"
#define CMMD__RF_OFF					"RF_OFF"
#define CMMD__RF_QUICK_OFF				"RF_QUICK_OFF"
#define CMMD__RF_SETPOWER				"SET_POWER"
#define CMMD__MATCH_AUTO				"AUTO"
#define CMMD__MATCH_MANUAL				"MANUAL"
#define CMMD__MATCH_PRESET				"PRESET"
#define CMMD__MATCH_MANUAL_AUTO			"MANUAL_AUTO"

// LIFT PIN
#define CMMD__LIFT_PIN__PROC_UP			"PROC.UP"
#define CMMD__LIFT_PIN__PROC_DOWN		"PROC.DOWN"
#define CMMD__LIFT_PIN__PROC_MIDDLE     "PROC.MIDDLE"

// ESC
#define CMMD__ESC_CHUCK					"CHUCK"
#define CMMD__ESC_DECHUCK				"DECHUCK"

// EPD
#define CMMD__EPD_DETECT				"EPD_DETECT"
#define CMMD__DC2EPD_DETECT				"DC2EPD_DETECT"

#define EPD_MODE__TRIGGER				"TRIGGER"
#define EPD_MODE__SLOPE					"SLOPE"
#define EPD_MODE__VALUE_CHANGE			"ValueChange"
#define EPD_MODE__PERCENT_CHANGE		"PercentChange"
#define EPD_MODE__VALUE_SLOPE			"ValueSlope"
#define EPD_MODE__PERCENT_SLOPE			"PercentSlope"

// FNC CHM ...
#define CMMD__PICK_READY				"PICK_READY"
#define CMMD__PICK_X_READY				"PICK_X_READY"
#define CMMD__PICK_COMPLETE				"PICK_COMPLETE"
#define CMMD__PICK_X_COMPLETE			"PICK_X_COMPLETE"

#define CMMD__PLACE_READY				"PLACE_READY"
#define CMMD__PLACE_X_READY				"PLACE_X_READY"
#define CMMD__PLACE_COMPLETE			"PLACE_COMPLETE"
#define CMMD__PLACE_X_COMPLETE			"PLACE_X_COMPLETE"


// STEP Control
#define CMMD__EXCEPTION_SKIP			-1
#define CMMD__EXCEPTION_PAUSE			 2
#define CMMD__EXCEPTION_RESUME			 3

