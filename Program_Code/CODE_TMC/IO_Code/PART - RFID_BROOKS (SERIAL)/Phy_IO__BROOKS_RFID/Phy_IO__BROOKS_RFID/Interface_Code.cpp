#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__HERMOS_SERIAL.h"
#include "CObj__LF80_SERIAL.h"
#include "CObj__VIRTUAL_TYPE.h"



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
#define CLS__HERMOS_SERIAL				"HERMOS.SERIAL"
#define CLS__LF80_SERIAL				"LF80.SERIAL"
#define CLS__VIRTUAL_TYPE				"VIRTUAL.TYPE"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

	ADD__OBJ_CLS(CLS__HERMOS_SERIAL);
	ADD__OBJ_CLS(CLS__LF80_SERIAL);
	ADD__OBJ_CLS(CLS__VIRTUAL_TYPE);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

	IF__OBJ_CLS(CLS__HERMOS_SERIAL)		return (new CObj__HERMOS_SERIAL);
	IF__OBJ_CLS(CLS__LF80_SERIAL)		return (new CObj__LF80_SERIAL);
	IF__OBJ_CLS(CLS__VIRTUAL_TYPE)		return (new CObj__VIRTUAL_TYPE);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
