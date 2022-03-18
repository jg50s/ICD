#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__MANUAL_PROC.h"

#include "CObj__PROC_STD.h"
#include "CObj__STEP_SAMPLE.h"


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
#define CLS__MANUAL_PROC				"MANUAL.PROC"

#define CLS__PROC_STD					"PROC.STD"
#define CLS__STEP_SAMPLE				"STEP.SAMPLE"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__MANUAL_PROC);

ADD__OBJ_CLS(CLS__PROC_STD);
ADD__OBJ_CLS(CLS__STEP_SAMPLE);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__MANUAL_PROC)			return (new CObj__MANUAL_PROC);

IF__OBJ_CLS(CLS__PROC_STD)				return (new CObj__PROC_STD);
IF__OBJ_CLS(CLS__STEP_SAMPLE)			return (new CObj__STEP_SAMPLE);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK

