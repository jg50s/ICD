#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_Fnc__TMC_SYS_STD.h"
#include "CObj_Fnc__PMC_SYS_STD.h"



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
#define CLS__TMC_SYS_STD				"TMC_SYS.STD"
#define CLS__PMC_SYS_STD				"PMC_SYS.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__TMC_SYS_STD);
ADD__OBJ_CLS(CLS__PMC_SYS_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__TMC_SYS_STD)			return new CObj_Fnc__TMC_SYS_STD;
IF__OBJ_CLS(CLS__PMC_SYS_STD)			return new CObj_Fnc__PMC_SYS_STD;

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
