#pragma once


// ...
#define  _ACT__TRANSFER_SIZE                    10
#define  _ACT_ID__MOVE_TO_LPx                   0
#define  _ACT_ID__MOVE_TO_LLx_IN_ATM            1
#define  _ACT_ID__LLx_DOOR_VLV_OP_CL            2
#define  _ACT_ID__LLx_PUMP_VENT                 3
#define  _ACT_ID__LLx_COOLING                   4
#define  _ACT_ID__LLx_SLOT_VLV_OP_CL            5
#define  _ACT_ID__MOVE_TO_LLx_IN_VAC            6
#define  _ACT_ID__MOVE_TO_AL1                   7
#define  _ACT_ID__MOVE_TO_ST1                   8
#define  _ACT_ID__MOVE_TO_ST2                   9

#define  _ACT_MOVE__MOVE_TO_LPx                 "MOVE_TO_FOUP"
#define  _ACT_MOVE__MOVE_TO_LLx_IN_ATM          "MOVE_TO_LLx_IN_ATM"
#define  _ACT_MOVE__LLx_DOOR_VLV_OP_CL          "LLx_DOOR_VLV_OP_CL"
#define  _ACT_MOVE__LLx_PUMP_VENT               "LLx_PUMP_VENT"
#define  _ACT_MOVE__LLx_COOLING                 "LLx_COOLING"
#define  _ACT_MOVE__LLx_SLOT_VLV_OP_CL          "LLx_SLOT_VLV_OP_CL"
#define  _ACT_MOVE__MOVE_TO_LLx_IN_VAC          "MOVE_TO_LLx_IN_VAC"
#define  _ACT_MOVE__MOVE_TO_AL1                 "MOVE_TO_AL1"
#define  _ACT_MOVE__MOVE_TO_ST1                 "MOVE_TO_ST1"
#define  _ACT_MOVE__MOVE_TO_ST2                 "MOVE_TO_ST2"

// ...
#define  _ACT__PROCESS_SIZE                     4
#define  _ACT_ID__MOVE_TO_PMx                   0
#define  _ACT_ID__PMx_SLOT_VLV_OP_CL            1
#define  _ACT_ID__PMx_PIN_UP_TO_DOWN            2
#define  _ACT_ID__PMx_PROCESS                   3

#define  _ACT_PROC__MOVE_TO_PMx                 "MOVE_TO_PMx."
#define  _ACT_PROC__PMx_SLOT_VLV_OP_CL          "PMx_SLOT_VLV_OP_CL."
#define  _ACT_PROC__PMx_PIN_UP_TO_DOWN          "PMx_PIN_UP_TO_DOWN."
#define  _ACT_PROC__PMx_PROCESS                 "PMx_PROCESS."


// STATE COLOR ...
#define  pKEY__DATA_T_COLOR_IDLE				"DATA.T_COLOR.IDLE"
#define  pKEY__DATA_B_COLOR_IDLE				"DATA.B_COLOR.IDLE"

#define  pKEY__DATA_T_COLOR_DISABLE				"DATA.T_COLOR.DISABLE"
#define  pKEY__DATA_B_COLOR_DISABLE				"DATA.B_COLOR.DISABLE"

#define  pKEY__DATA_T_COLOR_RESERVE				"DATA.T_COLOR.RESERVE"
#define  pKEY__DATA_B_COLOR_RESERVE				"DATA.B_COLOR.RESERVE"

#define  pKEY__DATA_T_COLOR_RUN					"DATA.T_COLOR.RUN"
#define  pKEY__DATA_B_COLOR_RUN					"DATA.B_COLOR.RUN"

#define  pKEY__DATA_T_COLOR_END					"DATA.T_COLOR.END"
#define  pKEY__DATA_B_COLOR_END					"DATA.B_COLOR.END"

#define  pKEY__DATA_T_COLOR_ABORT				"DATA.T_COLOR.ABORT"
#define  pKEY__DATA_B_COLOR_ABORT				"DATA.B_COLOR.ABORT"


// CFG ...
#define  pKEY__DATA_LLx_SLOT_SIZE				"DATA.LLx_SLOT_SIZE"
#define  pKEY__DATA_LLx_PIN_USE					"DATA.LLx.PIN_USE"

#define  pKEY__DATA_STx_SIZE					"DATA.STx_MD_SIZE"
#define  pKEY__DATA_PMx_SIZE					"DATA.PMx_MD_SIZE"


// TRANSFER.PART ...
#define  pKEY__CH_MOVE_CTRL_STATE_X             "CH.MOVE.CTRL_STATE."

#define  pKEY__CH_MOVE_STN_SRC_X                "CH.MOVE.STN_SRC."
#define  pKEY__CH_MOVE_STN_TRG_X                "CH.MOVE.STN_TRG."
#define  pKEY__CH_MOVE_CFG_COUNT_X              "CH.MOVE.CFG_COUNT."
#define  pKEY__CH_MOVE_CUR_COUNT_X              "CH.MOVE.CUR_COUNT."

#define  pKEY__CH_MOVE_ACT_CHECK_X				"CH.MOVE.ACT_CHECK."


// PROCESS.PART ...
#define  pKEY__CH_PROC_CTRL_STATE_X             "CH.PROC.CTRL_STATE."

#define  pKEY__CH_PROC_STN_SRC_X                "CH.PROC.STN_SRC."
#define  pKEY__CH_PROC_STN_TRG_X                "CH.PROC.STN_TRG."
#define  pKEY__CH_PROC_CFG_COUNT_X              "CH.PROC.CFG_COUNT."
#define  pKEY__CH_PROC_CUR_COUNT_X              "CH.PROC.CUR_COUNT."

#define  pKEY__CH_PROC_ACT_CHECK_X				"CH.PROC.ACT_CHECK."

#define  pKEY__CH_PROC_RECIPE_NAME_X            "CH.PROC.RECIPE_NAME."

