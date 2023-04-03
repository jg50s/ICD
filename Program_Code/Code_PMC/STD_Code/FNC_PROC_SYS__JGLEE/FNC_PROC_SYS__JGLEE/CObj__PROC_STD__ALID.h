#pragma once


// ...
#define ACT__CLEAR									"CLEAR"
#define ACT__CHECK									"CHECK"

#define ACT__ABORT									"ABORT"
#define ACT__RETRY									"RETRY"
#define ACT__IGNORE									"IGNORE"

#define ACT__RESTART								"RESTART"
#define ACT__END									"END"
#define ACT__SKIP									"SKIP"
#define ACT__CONTINUE								"CONTINUE"
#define ACT__JUMP									"JUMP"
#define ACT__PAUSE									"PAUSE"
#define ACT__RESUME									"RESUME"
#define ACT__END_WITH_PLASMA_DECHUCK				"PLASMA_DECHUCK"


// ...
#define ALID__PROCESS_RECIPE_NOT_EXIST						1

#define ALID__PROCESS_RECOVERY_CHECK_WITH_WAFER				2
#define ALID__PROCESS_RECOVERY_CHECK_NO_WAFER				3

#define ALID__PLSAMA_DECHUCK_RECIPE_NOT_EXIST				4
#define ALID__PLSAMA_DECHUCK_PROCESS_FAILED					5
#define ALID__PROCESS_RECIPE_FILE_CHANGING_NOW				6
#define ALID__WAFER_STATUS_CONVERT_TO_PROCESSED				7
#define ALID__WAFER_ALREADY_PROCESSED						8
#define ALID__RECIPE_STEP_SIZE_ERROR						9
#define ALID__PROCESS_NOT_READY								10

#define ALID__DI_SENSOR__HEAVY_ERRPR						11
#define ALID__PROCESS_INTERLOCK__DA_OFFSET_ERROR			12
