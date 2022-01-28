#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__ALx_STD.h"
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
#define CLS__ALx_STD				"ALx.STD"
#define CLS__VIS_STD				"VIS.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ALx_STD);
ADD__OBJ_CLS(CLS__VIS_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ALx_STD)			return (new CObj__ALx_STD);
IF__OBJ_CLS(CLS__VIS_STD)			return (new CObj__VIS_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
