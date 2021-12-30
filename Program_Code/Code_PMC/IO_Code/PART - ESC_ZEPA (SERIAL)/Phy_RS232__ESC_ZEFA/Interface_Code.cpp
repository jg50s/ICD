#include "StdAfx.h"
#include "Interface_Header.h"

#include "CObj_Phy__ESC_ZEFA.h"



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
#define CLS__ESC_ZEFA					"RS232"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__ESC_ZEFA);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__ESC_ZEFA)		    return (new CObj_Phy__ESC_ZEFA);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK

