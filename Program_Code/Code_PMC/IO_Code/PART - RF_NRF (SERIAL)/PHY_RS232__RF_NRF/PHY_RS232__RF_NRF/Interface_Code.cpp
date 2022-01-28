#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__NXA_PULSE.h"
#include "CObj__RFG_SERIAL.h"


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
#define CLS__NXA_PULSE						"NXA.PULSE"
#define CLS__RFG_SERIAL						"RFG.SERIAL"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__NXA_PULSE)
ADD__OBJ_CLS(CLS__RFG_SERIAL)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__NXA_PULSE)					return (new CObj__NXA_PULSE);
IF__OBJ_CLS(CLS__RFG_SERIAL)				return (new CObj__RFG_SERIAL);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
