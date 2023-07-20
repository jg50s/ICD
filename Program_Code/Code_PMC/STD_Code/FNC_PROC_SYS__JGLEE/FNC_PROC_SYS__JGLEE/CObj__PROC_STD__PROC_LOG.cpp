#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int  CObj__PROC_STD::Fnc__PRC_LOG__ENABLE(CII_OBJECT__VARIABLE *p_variable)
{
	bActive__PROC_LOG__STEP_START = false;

	// ...
	{
		CString ch_data;

		ch_data = sEXT_CH__SLOT01_LOTID->Get__STRING();
		sEXT_CH__PROC_LOG__LOTID->Set__DATA(ch_data);

		ch_data = sEXT_CH__SLOT01_PORTID->Get__STRING();
		sEXT_CH__PROC_LOG__PORTID->Set__DATA(ch_data);

		ch_data = sEXT_CH__SLOT01_SLOTID->Get__STRING();
		sEXT_CH__PROC_LOG__SLOTID->Set__DATA(ch_data);

		//
		ch_data.Format("DA_REPORT(%s)(%s mm & %s deg)", 
						dEXT_CH__TMC_LINK_DA_REPORT_RESULT_WAFER->Get__STRING(),
						sEXT_CH__TMC_LINK_DA_REPORT_R_OFFSET_WAFER->Get__STRING(),
						sEXT_CH__TMC_LINK_DA_REPORT_T_OFFSET_WAFER->Get__STRING());

		sEXT_CH__PROC_LOG_DA_REPORT_RESULT->Set__DATA(ch_data);
	}

	// ...
	CString para__rcp_name = sCH__CUR_RCP_FILE_NAME->Get__STRING();
	sEXT_CH__PROC_LOG__RECIPEID->Set__DATA(para__rcp_name);

	CStringArray l_para;
	l_para.Add(para__rcp_name);

	return pOBJ_CTRL__PROC_LOG->Call__OBJ_MODE(_LOG_CMD__ENABLE, l_para);
}
int  CObj__PROC_STD::Fnc__PRC_LOG__DISABLE(CII_OBJECT__VARIABLE *p_variable)
{
	bActive__PROC_LOG__STEP_START = false;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__DISABLE);
}

int  CObj__PROC_STD::Fnc__PRC_LOG__PAUSE(CII_OBJECT__VARIABLE *p_variable)
{
	bActive__PROC_LOG__STEP_START = false;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__PAUSE);
}
int  CObj__PROC_STD::Fnc__PRC_LOG__RESUME(CII_OBJECT__VARIABLE *p_variable)
{
	bActive__PROC_LOG__STEP_START = false;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__RESUME);
}

int  CObj__PROC_STD::Fnc__PRC_LOG__STEP_START()
{
	if(bActive__PROC_LOG__STEP_START)			return 11;
	bActive__PROC_LOG__STEP_START = true;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__STEP_START);
}
int  CObj__PROC_STD::Fnc__PRC_LOG__STEP_END()
{
	bActive__PROC_LOG__STEP_START = false;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__STEP_END);
}
int  CObj__PROC_STD::Fnc__PRC_LOG__STEP_END_START()
{
	bActive__PROC_LOG__STEP_START = true;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__STEP_END_START);
}
int  CObj__PROC_STD::Fnc__PRC_LOG__STEP_ABORT()
{
	bActive__PROC_LOG__STEP_START = false;

	return pOBJ_CTRL__PROC_LOG->Run__OBJECT(_LOG_CMD__STEP_ABORT);
}
