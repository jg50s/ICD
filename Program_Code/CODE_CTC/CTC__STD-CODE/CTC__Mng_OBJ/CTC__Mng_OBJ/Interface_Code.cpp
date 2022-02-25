#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_Mng__ALARM_CTRL_STD.h"
#include "CObj_Mng__SYSTEM_INFO_STD.h"

#include "CObj_Mng__SIGNAL_TOWER_EX.h"
#include "CObj_Mng__SIGNAL_TOWER_STD.h"


//----------------------------------------------------------
DECLARE_START__DLL_STD_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_STD_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__ALARM_CTRL_STD						"ALARM_CTRL.STD"
#define CLS__SYSTEM_INFO_STD					"SYSTEM_INFO.STD"

#define CLS__SIGNAL_TOWER_EX					"SIGNAL_TOWER.EX"
#define CLS__SIGNAL_TOWER_STD					"SIGNAL_TOWER.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ALARM_CTRL_STD);
ADD__OBJ_CLS(CLS__SYSTEM_INFO_STD);

ADD__OBJ_CLS(CLS__SIGNAL_TOWER_EX);
ADD__OBJ_CLS(CLS__SIGNAL_TOWER_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ALARM_CTRL_STD)				return (new CObj_Mng__ALARM_CTRL_STD);
IF__OBJ_CLS(CLS__SYSTEM_INFO_STD)				return (new CObj_Mng__SYSTEM_INFO_STD);

IF__OBJ_CLS(CLS__SIGNAL_TOWER_EX)				return (new CObj_Mng__SIGNAL_TOWER_EX);
IF__OBJ_CLS(CLS__SIGNAL_TOWER_STD)				return (new CObj_Mng__SIGNAL_TOWER_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
