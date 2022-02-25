#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_Opr__TIMER_CLIENT.h"
#include "CObj_Opr__TIMER_SERVER.h"



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
#define CLS__TIMER_CLIENT				"TIMER.CLIENT"
#define CLS__TIMER_SERVER				"TIMER.SERVER"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__TIMER_CLIENT);
ADD__OBJ_CLS(CLS__TIMER_SERVER);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__TIMER_CLIENT)		return (new CObj_Opr__TIMER_CLIENT);
IF__OBJ_CLS(CLS__TIMER_SERVER)		return (new CObj_Opr__TIMER_SERVER);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
