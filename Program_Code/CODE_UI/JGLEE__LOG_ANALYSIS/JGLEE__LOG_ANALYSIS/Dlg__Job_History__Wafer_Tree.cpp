#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Job_History.h"

#include "Macro_Function.h"
#include "Macro__Wafer_Tree.h"


// ...
void CDlg__Job_History::
_Update__Wafer_Info(const CString& file_path)
{
	MACRO__Update__Wafer_Info(file_path, &mWfr_Info);
}

void CDlg__Job_History
::_Clear__Wafer_Tree()
{	
	CTreeCtrl *p_tree = &mTree__Wafer_Info;
	p_tree->DeleteAllItems();

	mWfr_Info.Clear__ALL();

	mBtn__DA_Chart_Wafer.EnableWindow(FALSE);
	mBtn__Tack_Time_Wafer.EnableWindow(FALSE);
	mBtn__Proc_Log_Wafer.EnableWindow(FALSE);
	mBtn__Rcp_Log_Wafer.EnableWindow(FALSE);
}
void CDlg__Job_History
::_Update__Wafer_Tree()
{	
	bool active_move = false;
	bool active_proc = false;

	if(mCheck__Search_Move.GetCheck() > 0)			active_move = true;
	if(mCheck__Search_Proc.GetCheck() > 0)			active_proc = true;

	// ...
	CTreeCtrl *p_tree = &mTree__Wafer_Info;

	MACRO__Update__Wafer_Tree(p_tree, &mWfr_Info, active_move,active_proc);

	_Expand__Node_History();

	mBtn__DA_Chart_Wafer.EnableWindow(TRUE);
	mBtn__Tack_Time_Wafer.EnableWindow(TRUE);
	mBtn__Proc_Log_Wafer.EnableWindow(TRUE);
	mBtn__Rcp_Log_Wafer.EnableWindow(TRUE);
}

