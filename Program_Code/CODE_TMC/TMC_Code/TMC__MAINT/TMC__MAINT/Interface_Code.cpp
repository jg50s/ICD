#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__LLx_PROC.h"


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
#define CLS__LLx_PROC					"LLx.PROC"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__LLx_PROC);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__LLx_PROC)				return (new CObj__LLx_PROC);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
