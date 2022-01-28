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
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}
int  CObj__LPx_STD::Call__LOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

//
int  CObj__LPx_STD::Call__RLSUNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__UNLOAD(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	if(flag > 0)
	{
		if(dCH__CFG_UNDOCK_POSITION_TAG_READ->Check__DATA("TRUE") > 0)
		{
			flag = pLPx__OBJ_CTRL->Call__OBJECT("CID_READ");
		}
	}
	return flag;
}
int  CObj__LPx_STD::Call__CLAMP(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__UNCLAMP(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__CID_READ(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__RF_PAGE_READ(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__RF_CID_WRITE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__RF_PAGE_WRITE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__MAP(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__EXTENDPADDLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__RETRACTPADDLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__PADDLE_DOWN(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__PADDLE_UP(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	return pLPx__OBJ_CTRL->Call__OBJECT(mode);
}

int  CObj__LPx_STD::Call__LATCH(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__UNLATCH(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__CLOSEDOOR(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__OPENDOOR(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__VACON(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__VACOFF(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__EXTENDSHUTTLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__RETRACTSHUTTLE(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}

int  CObj__LPx_STD::Call__HALT(const CString& mode,CII_OBJECT__VARIABLE* p_variable)
{
	int flag = pLPx__OBJ_CTRL->Call__OBJECT(mode);

	return flag;
}


//----------------------------------------------------------------------------------------------------
int  CObj__LPx_STD::Fnc__LOAD(const int empty_flag,
							  const int material_size)
{
	CString status;
	int i;

	if(empty_flag > 0)		status = "NONE";
	else					status = "EXIST";

	for(i=0;i<CFG_LP_MAX_SLOT;i++)
	{
		if(empty_flag == 0)
		{
			if(i<material_size)		status = "EXIST";
			else					status = "NONE";
		}

		dCH__SLOT_STATUS[i]->Set__DATA(status);
	}
	return 1;
}
int  CObj__LPx_STD::Fnc__UNLOAD()
{
	CString status;
	int i;

	status = "NONE";

	for(i=0;i<CFG_LP_MAX_SLOT;i++)
	{
		dCH__SLOT_STATUS[i]->Set__DATA(status);
	}
	return 1;
}
