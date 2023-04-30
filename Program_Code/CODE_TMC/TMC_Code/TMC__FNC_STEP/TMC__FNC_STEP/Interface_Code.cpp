#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__STEP_LLx.h"


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
#define CLS__STEP_LLx				"STEP.LLx"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__STEP_LLx);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__STEP_LLx)			return (new CObj__STEP_LLx);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
