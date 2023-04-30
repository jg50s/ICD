#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Trace.h"

#include "CObj__Wafer_Trace__KEY_DEF.h"


// ...
int CDlg__Wafer_Trace
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;

	CString para_data;
	CString dir_root;

	if(iREAL_MODE < 0)
	{
		CString log_msg;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_DIR_ROOT, dir_root);
		dir_root += "\\EQP_LOG\\Wafer_Data";
	}
	else
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = module_id;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_root);
		dir_root += "\\EQP_LOG\\Wafer_Data";
	}

	// ...
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_LPx_MAX, para_data);
		iLPx_SIZE = atoi(para_data);
		if(iLPx_SIZE > 5)		iLPx_SIZE = 5;
		if(iLPx_SIZE < 1)		iLPx_SIZE = 1;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_AXIS_MAX, para_data);
		double data__axis_full_range = atof(para_data);
		dRes__Axis_Range = data__axis_full_range / 5.0;
		if(dRes__Axis_Range < 0.1)			dRes__Axis_Range = 1.0;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_ERR_RANGE, para_data);
		dData__Error_Range = atof(para_data);
		double range_half = data__axis_full_range / 2.0;
		if(dData__Error_Range > range_half)			dData__Error_Range = range_half;
	}

	sDir_Root = dir_root;

	return 1;
}

int CDlg__Wafer_Trace
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	if(!bActive_Init)
	{
		bActive_Init = true;

		mReSize.Link_Dlg(this);

		mReSize.Link_ResID(IDC_TREE__WAFER);
		mReSize.Link_ResID(IDC_CHECK__SEARCH_MOVE);
		mReSize.Link_ResID(IDC_CHECK__SEARCH_PROC);
		mReSize.Link_ResID(IDC_CHECK__NODE_HISTORY);
		mReSize.Link_ResID(IDC_CHECK__NODE_OPEN);
		mReSize.Link_ResID(IDC_CHECK__NODE_CLOSE);
		mReSize.Link_ResID(IDC_BTN__EXPAND_HISTORY_OPEN);
		mReSize.Link_ResID(IDC_BTN__EXPAND_ALL_OPEN);
		mReSize.Link_ResID(IDC_BTN__EXPAND_ALL_CLOSE);
		mReSize.Link_ResID(IDC_BTN__WFR_REFRESH);
		mReSize.Link_ResID(IDC_BTN__DA_CHART);
		mReSize.Link_ResID(IDC_BTN__TACK_TIME);
		mReSize.Link_ResID(IDC_BTN__WAFER_SEL);
		mReSize.Link_ResID(IDC_EDIT__WAFER_PATH);
		mReSize.Link_ResID(IDC_EDIT__WAFERID);
		mReSize.Link_ResID(IDC_EDIT__LOTID);
		mReSize.Link_ResID(IDC_GROUP__ITEM);
		mReSize.Link_ResID(IDC_TEXT__WFRID);
		mReSize.Link_ResID(IDC_TEXT__LOTID);

		mReSize.Init_Position();
	}
	mReSize.Move_Position(p_st, p_et);

	// ...
	{
		int sx = p_st.x;
		int sy = p_st.y;
		int wx = p_et.x - p_st.x;
		int wy = p_et.y - p_st.y;

		MoveWindow(sx,sy,wx,wy,true);
		ShowWindow(SW_SHOW);
	}
	return 1;
}
int CDlg__Wafer_Trace
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}
