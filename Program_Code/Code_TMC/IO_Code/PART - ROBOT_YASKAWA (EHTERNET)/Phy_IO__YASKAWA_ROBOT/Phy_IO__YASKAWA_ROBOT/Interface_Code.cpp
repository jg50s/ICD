#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ALx_SR100.h"



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
#define CLS__SR100_RBx				"SR100.RBx"
#define CLS__SR100_ALx				"SR100.ALx"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

	ADD__OBJ_CLS(CLS__SR100_RBx);
	ADD__OBJ_CLS(CLS__SR100_ALx);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

	IF__OBJ_CLS(CLS__SR100_RBx)		return (new CObj_NET__ATM_SR100);
	IF__OBJ_CLS(CLS__SR100_ALx)		return (new CObj_NET__ALx_SR100);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK

