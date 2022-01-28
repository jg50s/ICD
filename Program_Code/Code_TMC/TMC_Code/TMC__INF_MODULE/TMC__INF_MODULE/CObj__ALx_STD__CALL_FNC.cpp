#include "StdAfx.h"
#include "CObj__ALx_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__ALx_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pAL__OBJ_CTRL->Call__OBJECT("INIT");
}

int  CObj__ALx_STD::Call__ALIGN(CII_OBJECT__VARIABLE* p_variable)
{
	return pAL__OBJ_CTRL->Call__OBJECT("ALIGN");
}

int  CObj__ALx_STD::Call__OCR(CII_OBJECT__VARIABLE* p_variable)
{
	return pAL__OBJ_CTRL->Call__OBJECT("OCR");
}
