#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__MFC_IO.h"
#include "CObj__SYS_IO.h"



//----------------------------------------------------------
DECLARE_START__DLL_INTERLOCK_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_INTERLOCK_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__MFC_IO					"MFC.IO"
#define CLS__SYS_IO					"SYS.IO"


DECLARE_START__DLL_INTERLOCK_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__MFC_IO);
ADD__OBJ_CLS(CLS__SYS_IO);

DECLARE_END__DLL_INTERLOCK_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_INTERLOCK_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__MFC_IO)			return (new CObj__MFC_IO);
IF__OBJ_CLS(CLS__SYS_IO)			return (new CObj__SYS_IO);

DECLARE_END__DLL_INTERLOCK_OBJ__CREATE_LINK
