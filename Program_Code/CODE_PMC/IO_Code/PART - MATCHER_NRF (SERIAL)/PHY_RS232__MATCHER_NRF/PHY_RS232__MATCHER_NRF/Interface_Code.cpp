#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__MAT_SERIAL.h"
#include "CObj__NODA_SERIAL.h"


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
#define CLS__MAT_SERIAL						"MAT.SERIAL"
#define CLS__NODA_SERIAL					"NODA.SERIAL"



DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__MAT_SERIAL)
ADD__OBJ_CLS(CLS__NODA_SERIAL)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__MAT_SERIAL)				return (new CObj__MAT_SERIAL);
IF__OBJ_CLS(CLS__NODA_SERIAL)				return (new CObj__NODA_SERIAL);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK

