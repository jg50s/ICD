#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__ARCTIC_SERIAL.h"
#include "CObj__RPS_SERIAL.h"



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
#define CLS__ARCTIC_SERIAL						"ARCTIC.SERIAL"
#define CLS__RPS_SERIAL							"RPS.SERIAL"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ARCTIC_SERIAL)
ADD__OBJ_CLS(CLS__RPS_SERIAL)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ARCTIC_SERIAL)					return (new CObj__ARCTIC_SERIAL);
IF__OBJ_CLS(CLS__RPS_SERIAL)					return (new CObj__RPS_SERIAL);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
