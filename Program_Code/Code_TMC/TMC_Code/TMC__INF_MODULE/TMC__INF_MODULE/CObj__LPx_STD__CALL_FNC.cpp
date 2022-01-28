#include "StdAfx.h"
#include "CObj__LPx_STD.h"


//----------------------------------------------------------------------------------------------------
int  CObj__LPx_STD::Call__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("INIT");
}

//
int  CObj__LPx_STD::Call__PREPLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("PREPLOAD");
}
int  CObj__LPx_STD::Call__LOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("LOAD");
}

//
int  CObj__LPx_STD::Call__RLSUNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("RLSUNLOAD");
}
int  CObj__LPx_STD::Call__UNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("UNLOAD");
}

//
int  CObj__LPx_STD::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("CID_READ");
}

int  CObj__LPx_STD::Call__RF_CID_READ(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("RF_CID_READ");
}
int  CObj__LPx_STD::Call__RF_PAGE_READ(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("RF_PAGE_READ");
}
int  CObj__LPx_STD::Call__RF_CID_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("RF_CID_WRITE");
}
int  CObj__LPx_STD::Call__RF_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT("RF_PAGE_WRITE");
}
