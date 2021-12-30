#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__VAT650_TYPE.h"



//----------------------------------------------------------
DECLARE_START__DLL_IO_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_IO_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__VAT650_TYPE					"VAT650.TYPE"			


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__VAT650_TYPE)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__VAT650_TYPE)				return (new CObj__VAT650_TYPE);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
