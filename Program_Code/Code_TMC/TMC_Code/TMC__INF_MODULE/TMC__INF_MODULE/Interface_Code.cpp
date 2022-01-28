#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__UPPER_ATM_ROBOT.h"
#include "CObj__UPPER_VAC_ROBOT.h"

#include "CObj__ATM_ROBOT_STD.h"
#include "CObj__VAC_ROBOT_STD.h"

#include "CObj__TMC_CHM_STD.h"
#include "CObj__TMC_SYSTEM_STD.h"

#include "CObj__ALx_STD.h"
#include "CObj__LBx_STD.h"
#include "CObj__LPx_STD.h"
#include "CObj__VIS_STD.h"


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
#define CLS__UPPER_ATM_ROBOT		"UPPER.ATM_ROBOT"
#define CLS__UPPER_VAC_ROBOT		"UPPER.VAC_ROBOT"

#define CLS__ATM_ROBOT_STD			"ATM_ROBOT.STD"
#define CLS__VAC_ROBOT_STD			"VAC_ROBOT.STD"

#define CLS__TMC_CHM_STD			"TMC_CHM.STD"
#define CLS__TMC_SYS_STD			"TMC_SYS.STD"

#define CLS__ALx_STD				"ALx.STD"
#define CLS__LBx_STD				"LBx.STD"
#define CLS__LPx_STD				"LPx.STD"
#define CLS__VIS_STD				"VIS.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__UPPER_ATM_ROBOT);
ADD__OBJ_CLS(CLS__UPPER_VAC_ROBOT);

ADD__OBJ_CLS(CLS__ATM_ROBOT_STD);
ADD__OBJ_CLS(CLS__VAC_ROBOT_STD);

ADD__OBJ_CLS(CLS__TMC_CHM_STD);
ADD__OBJ_CLS(CLS__TMC_SYS_STD);

ADD__OBJ_CLS(CLS__ALx_STD);
ADD__OBJ_CLS(CLS__LBx_STD);
ADD__OBJ_CLS(CLS__LPx_STD);
ADD__OBJ_CLS(CLS__VIS_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__UPPER_ATM_ROBOT)		return (new CObj__UPPER_ATM_ROBOT);
IF__OBJ_CLS(CLS__UPPER_VAC_ROBOT)		return (new CObj__UPPER_VAC_ROBOT);

IF__OBJ_CLS(CLS__ATM_ROBOT_STD)			return (new CObj__ATM_ROBOT_STD);
IF__OBJ_CLS(CLS__VAC_ROBOT_STD)			return (new CObj__VAC_ROBOT_STD);

IF__OBJ_CLS(CLS__TMC_CHM_STD)			return (new CObj__TMC_CHM_STD);
IF__OBJ_CLS(CLS__TMC_SYS_STD)			return (new CObj__TMC_SYSTEM_STD);

IF__OBJ_CLS(CLS__ALx_STD)				return (new CObj__ALx_STD);
IF__OBJ_CLS(CLS__LBx_STD)				return (new CObj__LBx_STD);
IF__OBJ_CLS(CLS__LPx_STD)				return (new CObj__LPx_STD);
IF__OBJ_CLS(CLS__VIS_STD)				return (new CObj__VIS_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
