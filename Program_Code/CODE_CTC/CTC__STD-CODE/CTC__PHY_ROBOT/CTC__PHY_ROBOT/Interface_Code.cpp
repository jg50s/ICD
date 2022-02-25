#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_Phy__ROBOT_ATM.h"
#include "CObj_Phy__ROBOT_VAC.h"


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
#define CLS__ROBOT_ATM							"ROBOT.ATM"
#define CLS__ROBOT_VAC							"ROBOT.VAC"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ROBOT_ATM);
ADD__OBJ_CLS(CLS__ROBOT_VAC);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ROBOT_ATM)					return (new CObj_Phy__ROBOT_ATM);
IF__OBJ_CLS(CLS__ROBOT_VAC)					return (new CObj_Phy__ROBOT_VAC);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
