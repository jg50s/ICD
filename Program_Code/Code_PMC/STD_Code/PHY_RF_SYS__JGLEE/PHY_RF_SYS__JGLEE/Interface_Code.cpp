#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__ESC_IO.h"
#include "CObj__RF_STD.h"



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
#define CLS__ESC_IO								"ESC.IO"
#define CLS__RF_STD								"RF.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ESC_IO)
ADD__OBJ_CLS(CLS__RF_STD)

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ESC_IO)						return (new CObj__ESC_IO);
IF__OBJ_CLS(CLS__RF_STD)						return (new CObj__RF_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
