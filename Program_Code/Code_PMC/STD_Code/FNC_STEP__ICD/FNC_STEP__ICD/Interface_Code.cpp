#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__STEP_BETA.h"
#include "CObj__STEP_STD.h"


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
#define CLS__STEP_BETA				"STEP.BETA"
#define CLS__STEP_STD				"STEP.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__STEP_BETA);
ADD__OBJ_CLS(CLS__STEP_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__STEP_BETA)			return (new CObj__STEP_BETA);
IF__OBJ_CLS(CLS__STEP_STD)			return (new CObj__STEP_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

