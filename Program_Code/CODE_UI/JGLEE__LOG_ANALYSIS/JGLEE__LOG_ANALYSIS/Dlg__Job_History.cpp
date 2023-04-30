// Dlg__Job_History.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Job_History.h"

#include "CObj__Job_History__KEY_DEF.h"
#include "Macro_Function.h"


// CDlg__Job_History dialog

IMPLEMENT_DYNAMIC(CDlg__Job_History, CDialog)

CDlg__Job_History::CDlg__Job_History(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Job_History::IDD, pParent)
	, mData__Start_Date(COleDateTime::GetCurrentTime())
	, mData__End_Date(COleDateTime::GetCurrentTime())
	, mStr__Search_Start(_T(""))
	, mStr__Search_End(_T(""))
	, mStr_Option__LotID(_T(""))
	, mStr_Option__JobID(_T(""))
	, mStr_Option__CSTID(_T(""))
{

}

CDlg__Job_History::~CDlg__Job_History()
{
}

void CDlg__Job_History::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__RESULT_TABLE, mList__Result_Table);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER__START_DATE, mData__Start_Date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER__END_DATE,   mData__End_Date);

	DDX_Text(pDX, IDC_EDIT__SEARCH_START, mStr__Search_Start);
	DDX_Text(pDX, IDC_EDIT__SEARCH_END,   mStr__Search_End);

	DDX_Control(pDX, IDC_BTN__RESULT_SEL_PATH, mBtn__Result_Sel_Path);
	DDX_Control(pDX, IDC_BTN__RESULT_SEL_PORTID, mBtn__Result_Sel_PortID);

	DDX_Control(pDX, IDC_TREE__SLOT_INFO, mTree__Slot_Info);

	DDX_Control(pDX, IDC_TREE__WAFER, mTree__Wafer_Info);
	DDX_Control(pDX, IDC_CHECK__NODE_HISTORY, mCheck__Node_History);
	DDX_Control(pDX, IDC_CHECK__NODE_OPEN,    mCheck__Node_Open);
	DDX_Control(pDX, IDC_CHECK__NODE_CLOSE,   mCheck__Node_Close);
	DDX_Control(pDX, IDC_CHECK__SEARCH_MOVE,  mCheck__Search_Move);
	DDX_Control(pDX, IDC_CHECK__SEARCH_PROC,  mCheck__Search_Proc);
	DDX_Control(pDX, IDC_CHECK__LOG_WAFER_COMPARE, mCheck__Log_Wfr_Compare);
	DDX_Control(pDX, IDC_CHECK__REF_WAFER_COMPARE, mCheck__Ref_Wfr_Compare);

	DDX_Control(pDX, IDC_DATA__SEARCH_PORTID, mBtn_Option__PortID);
	DDX_Control(pDX, IDC_CHECK__ALL_PORTID,   mCheck_Option__PortID_All);

	DDX_Text(pDX, IDC_EDIT__SEARCH_JOBID,   mStr_Option__JobID);
	DDX_Control(pDX, IDC_CHECK__ALL_JOBID,  mCheck_Option__JobID_All);
	DDX_Control(pDX, IDC_CHECK__PART_JOBID, mCheck_Option__JobID_Part);

	DDX_Text(pDX, IDC_EDIT__SEARCH_LOTID,   mStr_Option__LotID);
	DDX_Control(pDX, IDC_CHECK__ALL_LOTID,  mCheck_Option__LotID_All);
	DDX_Control(pDX, IDC_CHECK__PART_LOTID, mCheck_Option__LotID_Part);

	DDX_Text(pDX, IDC_EDIT__SEARCH_CSTID,   mStr_Option__CSTID);
	DDX_Control(pDX, IDC_CHECK__ALL_CSTID,  mCheck_Option__CSTID_All);
	DDX_Control(pDX, IDC_CHECK__PART_CSTID, mCheck_Option__CSTID_Part);
	DDX_Control(pDX, IDC_BTN__DA_CHART_WAFER, mBtn__DA_Chart_Wafer);
	DDX_Control(pDX, IDC_BTN__TACK_TIME_WAFER, mBtn__Tack_Time_Wafer);
	DDX_Control(pDX, IDC_BTN__PROCESS_LOG_WAFER, mBtn__Proc_Log_Wafer);
	DDX_Control(pDX, IDC_BTN__RECIPE_LOG_WAFER, mBtn__Rcp_Log_Wafer);
	DDX_Control(pDX, IDC_BTN__REF_WAFER_INFO, mBtn__Ref_Wafer_Info);
	DDX_Control(pDX, IDC_BTN__REF_WAFER_SLOT, mBtn__Ref_Wafer_Slot);
	DDX_Control(pDX, IDC_BTN__REF_WAFER_MNG, mBtn__Ref_Wfr_Mng);
}


BEGIN_MESSAGE_MAP(CDlg__Job_History, CDialog)
	ON_BN_CLICKED(IDC_BTN__SEARCH_ALL, &CDlg__Job_History::OnBnClickedBtn__Search_All)
	ON_BN_CLICKED(IDC_BTN__SEARCH_REFEASH, &CDlg__Job_History::OnBnClickedBtn__Search_Option)
	ON_BN_CLICKED(IDC_BTN__SEARCH_PORTID, &CDlg__Job_History::OnBnClickedBtn__Option_PortID)
	ON_BN_CLICKED(IDC_BTN__SEARCH_JOBID,  &CDlg__Job_History::OnBnClickedBtn__Option_JobID)
	ON_BN_CLICKED(IDC_BTN__SEARCH_LOTID,  &CDlg__Job_History::OnBnClickedBtn__Option_LotID)
	ON_BN_CLICKED(IDC_BTN__SEARCH_CSTID,  &CDlg__Job_History::OnBnClickedBtn__Option_CSTID)

	ON_BN_CLICKED(IDC_BTN__SEARCH_PRE_1_DAY, &CDlg__Job_History::OnBnClickedBtn__Before_1Day)
	ON_BN_CLICKED(IDC_BTN__SEARCH_PRE_2_DAY, &CDlg__Job_History::OnBnClickedBtn__Before_2Day)
	ON_BN_CLICKED(IDC_BTN__SEARCH_PRE_3_DAY, &CDlg__Job_History::OnBnClickedBtn__Before_3Day)
	ON_BN_CLICKED(IDC_BTN__SEARCH_PRE_4_DAY, &CDlg__Job_History::OnBnClickedBtn__Before_4Day)
	ON_BN_CLICKED(IDC_BTN__SEARCH_PRE_5_DAY, &CDlg__Job_History::OnBnClickedBtn__Before_5Day)

	ON_NOTIFY(NM_CLICK, IDC_LIST__RESULT_TABLE, &CDlg__Job_History::OnNMClickList__Search_Table)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE__SLOT_INFO, &CDlg__Job_History::OnTvnSelchangedTree__Slot_Sel)
	ON_NOTIFY(NM_CLICK, IDC_TREE__SLOT_INFO, &CDlg__Job_History::OnNMClickTree__Slot_Sel)

	ON_BN_CLICKED(IDC_BTN__EXPAND_HISTORY_OPEN, &CDlg__Job_History::OnBnClickedBtn__Expand_Node_History)
	ON_BN_CLICKED(IDC_BTN__EXPAND_ALL_OPEN,     &CDlg__Job_History::OnBnClickedBtn__Expand_Node_All_Open)
	ON_BN_CLICKED(IDC_BTN__EXPAND_ALL_CLOSE,    &CDlg__Job_History::OnBnClickedBtn__Expand_Node_All_Close)

	ON_BN_CLICKED(IDC_CHECK__LOG_WAFER_COMPARE, &CDlg__Job_History::OnBnClickedCheck__Log_Wafer_Compare)
	ON_BN_CLICKED(IDC_CHECK__REF_WAFER_COMPARE, &CDlg__Job_History::OnBnClickedCheck__Ref_Wafer_Compare)

	ON_BN_CLICKED(IDC_CHECK__SEARCH_MOVE, &CDlg__Job_History::OnBnClickedCheck__Check_Move_Of_Wafer_Table)
	ON_BN_CLICKED(IDC_CHECK__SEARCH_PROC, &CDlg__Job_History::OnBnClickedCheck__Check_Proc_Of_Wafer_Table)

	ON_BN_CLICKED(IDC_BTN__DA_CHART_WAFER, &CDlg__Job_History::OnBnClickedBtn__DA_Chart_Wafer)
	ON_BN_CLICKED(IDC_BTN__DA_CHART_LOT,   &CDlg__Job_History::OnBnClickedBtn__DA_Chart_Lot)

	ON_BN_CLICKED(IDC_BTN__TACK_TIME_WAFER, &CDlg__Job_History::OnBnClickedBtn__Tack_Time_Wafer)
	ON_BN_CLICKED(IDC_BTN__TACK_TIME_LOT,   &CDlg__Job_History::OnBnClickedBtn__Tack_Time_Lot)

	ON_BN_CLICKED(IDC_BTN__PROCESS_LOG_WAFER, &CDlg__Job_History::OnBnClickedBtn__Proc_Log_Wafer)
	ON_BN_CLICKED(IDC_BTN__PROCESS_LOG_LOT,   &CDlg__Job_History::OnBnClickedBtn__Proc_Log_Lot)

	ON_BN_CLICKED(IDC_BTN__RECIPE_LOG_WAFER, &CDlg__Job_History::OnBnClickedBtn__Rcp_Log_Wafer)
	ON_BN_CLICKED(IDC_BTN__RECIPE_LOG_LOT,   &CDlg__Job_History::OnBnClickedBtn__Rcp_Log_Lot)

	ON_BN_CLICKED(IDC_BTN__REF_WAFER_SEL, &CDlg__Job_History::OnBnClickedBtn__Ref_Wafer_Sel)
	ON_BN_CLICKED(IDC_BTN__REF_WAFER_MNG, &CDlg__Job_History::OnBnClickedBtn__Ref_Wafer_Mng)

	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()


// CDlg__Job_History message handlers

void CDlg__Job_History::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__RESULT_TABLE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Job_History::OnInitDialog()
{
	CDialog::OnInitDialog();

	// List : Result_Table ...
	{
		CReportCtrl* p_table = &mList__Result_Table;

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;
			// list_view_stype += LVS_EX_DOUBLEBUFFER;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		p_table->SetNoSort(false);
		_Make__Result_Table(p_table);
	}

	// Tree ...
	{
		CImageList *p_img  = &mImg__Tree;

		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 

		// Slot_Info ...
		{
			CTreeCtrl *p_tree = &mTree__Slot_Info;
			p_tree->SetImageList(p_img, TVSIL_NORMAL);
		}

		// Wafer)Info ...
		{
			CTreeCtrl *p_tree = &mTree__Wafer_Info;
			p_tree->SetImageList(p_img, TVSIL_NORMAL);
		}
	}

	// ...
	{
		mCheck__Log_Wfr_Compare.SetCheck(1);
		//mCheck__Log_Wfr_Compare.EnableWindow(FALSE);

		mCheck__Ref_Wfr_Compare.SetCheck(0);
		// mCheck__Ref_Wfr_Compare.EnableWindow(FALSE);

		//
		mCheck__Search_Move.SetCheck(1);
		mCheck__Search_Proc.SetCheck(1);
	}

	bActive_Init = false;
	return TRUE;  
}

void CDlg__Job_History::OnBnClickedBtn__Search_All()
{
	UpdateData(TRUE);

	// ...
	{
		CString str_start;
		CString str_end;

		str_start.Format("%04d_%02d_%02d", 
						 mData__Start_Date.GetYear(),
						 mData__Start_Date.GetMonth(),
						 mData__Start_Date.GetDay());
		str_end.Format("%04d_%02d_%02d", 
					   mData__End_Date.GetYear(),
					   mData__End_Date.GetMonth(),
					   mData__End_Date.GetDay());

		_Update__Search_All(str_start, str_end);
	}

	// PortID Option ...
	{
		bActive_Option__PortID_All = false;
	}
	// LotID Option ...
	{
		bActive_Option__LotID_All  = false;
		bActive_Option__LotID_Part = false;
	}
	// JobID Option ...
	{
		bActive_Option__JobID_All  = false;
		bActive_Option__JobID_Part = false;
	}
	// CSTID Option ...
	{
		bActive_Option__CSTID_All  = false;
		bActive_Option__CSTID_Part = false;
	}

	// ...
	{
		CReportCtrl* p_table = &mList__Result_Table;

		_Add__Result_Table(p_table, &mLog_Ctrl);
	}

	// UpdateData(FALSE);
}
void CDlg__Job_History::OnBnClickedBtn__Search_Option()
{
	UpdateData(TRUE);

	// PortID Option ...
	{
		bActive_Option__PortID_All = false;

		if(mCheck_Option__PortID_All.GetCheck() > 0)			bActive_Option__PortID_All = true;
	}
	// JobID Option ...
	{
		bActive_Option__JobID_All  = false;
		bActive_Option__JobID_Part = false;

		if(mCheck_Option__JobID_All.GetCheck()  > 0)			bActive_Option__JobID_All  = true;
		if(mCheck_Option__JobID_Part.GetCheck() > 0)			bActive_Option__JobID_Part = true;
	}
	// LotID Option ...
	{
		bActive_Option__LotID_All  = false;
		bActive_Option__LotID_Part = false;

		if(mCheck_Option__LotID_All.GetCheck()  > 0)			bActive_Option__LotID_All  = true;
		if(mCheck_Option__LotID_Part.GetCheck() > 0)			bActive_Option__LotID_Part = true;
	}
	// CSTID Option ...
	{
		bActive_Option__CSTID_All  = false;
		bActive_Option__CSTID_Part = false;

		if(mCheck_Option__CSTID_All.GetCheck()  > 0)			bActive_Option__CSTID_All  = true;
		if(mCheck_Option__CSTID_Part.GetCheck() > 0)			bActive_Option__CSTID_Part = true;
	}

	// ...
	{
		CReportCtrl* p_table = &mList__Result_Table;

		_Add__Result_Table(p_table, &mLog_Ctrl);
	}

	// UpdateData(FALSE);
}
void CDlg__Job_History::OnBnClickedBtn__Option_PortID()
{
	UIX__DIGITAL_PAD_CTRL x_pad_ctrl;

	CString str_name;
	CString init_data;
	CStringArray l_data;
	CString r_data;

	str_name = "Select PortID !";
	mBtn_Option__PortID.GetWindowText(init_data);

	l_data.Add("1");
	l_data.Add("2");
	l_data.Add("3");

	if(x_pad_ctrl->Popup(str_name, init_data, l_data, r_data) > 0)
	{
		mBtn_Option__PortID.SetWindowText(r_data);
	}
}
void CDlg__Job_History::OnBnClickedBtn__Option_JobID()
{
	UIX__STRING_PAD_CTRL x_pad_ctrl;

	CString str_name;
	CString init_data;
	CString r_data;

	str_name  = "Input JobID !";
	init_data = mStr_Option__JobID;

	if(x_pad_ctrl->Popup(str_name, init_data, r_data) > 0)
	{
		mStr_Option__JobID = r_data;

		UpdateData(FALSE);
	}
}
void CDlg__Job_History::OnBnClickedBtn__Option_LotID()
{
	UIX__STRING_PAD_CTRL x_pad_ctrl;

	CString str_name;
	CString init_data;
	CString r_data;

	str_name  = "Input LotID !";
	init_data = mStr_Option__LotID;

	if(x_pad_ctrl->Popup(str_name, init_data, r_data) > 0)
	{
		mStr_Option__LotID = r_data;

		UpdateData(FALSE);
	}
}
void CDlg__Job_History::OnBnClickedBtn__Option_CSTID()
{
	UIX__STRING_PAD_CTRL x_pad_ctrl;

	CString str_name;
	CString init_data;
	CString r_data;

	str_name  = "Input CSTID !";
	init_data = mStr_Option__CSTID;

	if(x_pad_ctrl->Popup(str_name, init_data, r_data) > 0)
	{
		mStr_Option__CSTID = r_data;

		UpdateData(FALSE);
	}
}

void CDlg__Job_History::OnBnClickedBtn__Before_1Day()
{
	_Update__Before_X_Day(1);
}
void CDlg__Job_History::OnBnClickedBtn__Before_2Day()
{
	_Update__Before_X_Day(2);
}
void CDlg__Job_History::OnBnClickedBtn__Before_3Day()
{
	_Update__Before_X_Day(3);
}
void CDlg__Job_History::OnBnClickedBtn__Before_4Day()
{
	_Update__Before_X_Day(4);
}
void CDlg__Job_History::OnBnClickedBtn__Before_5Day()
{
	_Update__Before_X_Day(5);
}
void CDlg__Job_History::_Update__Before_X_Day(const int i_day)
{
	COleDateTimeSpan span(i_day, 0, 0, 0);    // 날 시 분 초
	COleDateTime edit_time = COleDateTime::GetCurrentTime();

	mData__End_Date = edit_time;

	edit_time = edit_time - span;
	mData__Start_Date.SetDate(edit_time.GetYear(), edit_time.GetMonth(), edit_time.GetDay());

	UpdateData(FALSE);
}

void CDlg__Job_History::OnNMClickList__Search_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		mBtn__Ref_Wfr_Mng.EnableWindow(FALSE);

		_Update__Search_Wafer(r_index);
		_Clear__Wafer_Tree();
	}

	*pResult = 0;
}

void CDlg__Job_History::OnTvnSelchangedTree__Slot_Sel(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*
	// ...
	{
		LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
		HTREEITEM h_node = pNMTreeView->itemNew.hItem;

		printf(" * CDlg__Job_History::OnNMClickTree__Slot_Sel() ... \n");
		printf(" ** h_node <- [%1d] \n", h_node);

		CString str_slot = mTree__Slot_Info.GetItemText(h_node);
		sBtn__Result_Sel_SlotID = str_slot;

		if(str_slot.GetLength() > 0)		mBtn__Ref_Wfr_Mng.EnableWindow(TRUE);
		else								mBtn__Ref_Wfr_Mng.EnableWindow(FALSE);

		CString str_portid;
		mBtn__Result_Sel_PortID.GetWindowText(str_portid);

		CString dir_sub;
		mBtn__Result_Sel_Path.GetWindowText(dir_sub);

		CString wfr_path;
		wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,dir_sub,str_portid,str_slot);

		_Update__Wafer_Info(wfr_path);
		_Update__Wafer_Tree();
	}
	*/

	*pResult = 0;
}
void CDlg__Job_History::OnNMClickTree__Slot_Sel(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint pt;
	UINT n_flag = 0;

	GetCursorPos(&pt);
	::ScreenToClient(mTree__Slot_Info.m_hWnd, &pt);

	HTREEITEM h_node = mTree__Slot_Info.HitTest(pt, &n_flag);
	if(h_node != NULL)
	{
		CString str_slot = mTree__Slot_Info.GetItemText(h_node);
		sBtn__Result_Sel_SlotID = str_slot;

		if(str_slot.GetLength() > 0)		mBtn__Ref_Wfr_Mng.EnableWindow(TRUE);
		else								mBtn__Ref_Wfr_Mng.EnableWindow(FALSE);

		CString str_portid;
		mBtn__Result_Sel_PortID.GetWindowText(str_portid);

		CString dir_sub;
		mBtn__Result_Sel_Path.GetWindowText(dir_sub);

		CString wfr_path;
		wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,dir_sub,str_portid,str_slot);

		_Update__Wafer_Info(wfr_path);
		_Update__Wafer_Tree();
	}

	*pResult = 0;
}

void CDlg__Job_History::OnBnClickedBtn__Expand_Node_History()
{
	_Expand__Node_History();
}
void CDlg__Job_History::_Expand__Node_History()
{
	// ..
	{
		mCheck__Node_History.SetCheck(1);
		mCheck__Node_Open.SetCheck(0);
		mCheck__Node_Close.SetCheck(0);
	}

	// ...
	CTreeCtrl *p_tree = &mTree__Wafer_Info;
	HTREEITEM h_root = p_tree->GetRootItem();

	MACRO__Contract_All_Tree(p_tree);
	MACRO__Expand_Tree(p_tree, h_root, 2);
}
void CDlg__Job_History::OnBnClickedBtn__Expand_Node_All_Open()
{
	// ..
	{
		mCheck__Node_History.SetCheck(0);
		mCheck__Node_Open.SetCheck(1);
		mCheck__Node_Close.SetCheck(0);
	}

	// ...
	CTreeCtrl *p_tree = &mTree__Wafer_Info;

	MACRO__Expand_All_Tree(p_tree);
}
void CDlg__Job_History::OnBnClickedBtn__Expand_Node_All_Close()
{
	// ..
	{
		mCheck__Node_History.SetCheck(0);
		mCheck__Node_Open.SetCheck(0);
		mCheck__Node_Close.SetCheck(1);
	}

	// ...
	CTreeCtrl *p_tree = &mTree__Wafer_Info;

	MACRO__Contract_All_Tree(p_tree);
}


// ...
#include "Dlg__Wafer_DA_Chart.h"

void CDlg__Job_History::OnBnClickedBtn__DA_Chart_Wafer()
{
	CDlg__Wafer_DA_Chart dlg;

	// ...
	{
		DS__Wafer_Info ds_wfr;
		mWfr_Info.Get__WFR_INFO(ds_wfr);

		dlg.sPara__LotID = ds_wfr.sLOTID;
		dlg.sPara__PortOD.Format("%1d", ds_wfr.iPORTID);
		dlg.sPara__SlotID.Format("%1d", ds_wfr.iSLOTID);

		mWfr_Info.Get__WAFER_DA_INFO(dlg.sList__MODULE, 
									 dlg.sList__R_OFFSET,
									 dlg.sList__T_OFFSET);
	}

	dlg.DoModal();
}
void CDlg__Job_History::OnBnClickedBtn__DA_Chart_Lot()
{
	CDlg__Wafer_DA_Chart dlg;

	// ...
	{
		dlg.bActive__Multi_Slot = true;
		dlg.sList__Slot_ID.Copy(sList__Tree_Slot_Info);

		dlg.sDir_Root = sDir_Root;
		mBtn__Result_Sel_Path.GetWindowText(dlg.sDir_Sub);

		dlg.sPara__LotID  = _Get_LotID__Result_Table();
		dlg.sPara__PortOD = _Get_PortID__Result_Table(); 
	}

	dlg.DoModal();
}


void CDlg__Job_History::OnBnClickedCheck__Log_Wafer_Compare()
{
	mCheck__Log_Wfr_Compare.SetCheck(1);
	mCheck__Ref_Wfr_Compare.SetCheck(0);

	UpdateData(FALSE);
}
void CDlg__Job_History::OnBnClickedCheck__Ref_Wafer_Compare()
{
	mCheck__Log_Wfr_Compare.SetCheck(0);
	mCheck__Ref_Wfr_Compare.SetCheck(1);

	UpdateData(FALSE);
}

void CDlg__Job_History::OnBnClickedCheck__Check_Move_Of_Wafer_Table()
{
	_Update__Wafer_Tree();	
}
void CDlg__Job_History::OnBnClickedCheck__Check_Proc_Of_Wafer_Table()
{
	_Update__Wafer_Tree();	
}


// ...
#include "Dlg__Wafer_Tack_Table.h"
#include "Dlg__Lot_Tack_Time.h"

void CDlg__Job_History::OnBnClickedBtn__Tack_Time_Wafer()
{
	CDlg__Wafer_Tack_Table dlg;

	// ...
	{
		bool active__search_move = false;
		bool active__search_proc = false;

		if(mCheck__Search_Move.GetCheck() > 0)		active__search_move = true;
		if(mCheck__Search_Proc.GetCheck() > 0)		active__search_proc = true;

		dlg.bPara__Active_Move = active__search_move;
		dlg.bPara__Active_Proc = active__search_proc;

		dlg.pWfr_Info = &mWfr_Info;
	}

	dlg.DoModal();
}
void CDlg__Job_History::OnBnClickedBtn__Tack_Time_Lot()
{
	CDlg__Lot_Tack_Time dlg;

	// ...
	{
		dlg.sList__Slot_ID.Copy(sList__Tree_Slot_Info);

		dlg.sDir_Root = sDir_Root;
		mBtn__Result_Sel_Path.GetWindowText(dlg.sDir_Sub);

		dlg.sPara__LotID  = _Get_LotID__Result_Table();
		dlg.sPara__PortOD = _Get_PortID__Result_Table(); 

		dlg.bPara__Active_Move = mCheck__Search_Move.GetCheck();
		dlg.bPara__Active_Proc = mCheck__Search_Proc.GetCheck();
	}

	dlg.DoModal();
}

// ...
#include "Dlg__Wafer_MDx_Sel.h"
#include "Dlg__Lot_Process.h"

void CDlg__Job_History::OnBnClickedBtn__Proc_Log_Wafer()
{
	CDlg__Wafer_MDx_Sel dlg;

	// ...
	{
		CString dir_sub;
		mBtn__Result_Sel_Path.GetWindowText(dir_sub);

		dlg.sDir_Root = sDir_Root;
		dlg.sDir_Lot  = dir_sub;

		dlg.pWfr_Info = &mWfr_Info;
	}

	// ...
	{
		CString key_name;
		CString ch_data;
		CString* p_dlg_str;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM1;
				ch_data  = sPara__Template_Name_PM1;

				p_dlg_str = &dlg.sPara__Template_Name_PM1;
			}
			else if(i == 1)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM2;
				ch_data  = sPara__Template_Name_PM2;

				p_dlg_str = &dlg.sPara__Template_Name_PM2;
			}
			else if(i == 2)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM3;
				ch_data  = sPara__Template_Name_PM3;

				p_dlg_str = &dlg.sPara__Template_Name_PM3;
			}
			else if(i == 3)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM4;
				ch_data  = sPara__Template_Name_PM4;

				p_dlg_str = &dlg.sPara__Template_Name_PM4;
			}
			else if(i == 4)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM5;
				ch_data  = sPara__Template_Name_PM5;

				p_dlg_str = &dlg.sPara__Template_Name_PM5;
			}
			else if(i == 5)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM6;
				ch_data  = sPara__Template_Name_PM6;

				p_dlg_str = &dlg.sPara__Template_Name_PM6;
			}
			else if(i == 6)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL1;
				ch_data  = sPara__Template_Name_LL1;

				p_dlg_str = &dlg.sPara__Template_Name_LL1;
			}
			else if(i == 7)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL2;
				ch_data  = sPara__Template_Name_LL2;

				p_dlg_str = &dlg.sPara__Template_Name_LL2;
			}
			else
			{
				continue;
			}

			if(ch_data == "")
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

			*p_dlg_str = ch_data;
		}
	}

	dlg.DoModal();

	// ...
	{
		sPara__Template_Name_PM1 = dlg.sPara__Template_Name_PM1;
		sPara__Template_Name_PM2 = dlg.sPara__Template_Name_PM2;
		sPara__Template_Name_PM3 = dlg.sPara__Template_Name_PM3;
		sPara__Template_Name_PM4 = dlg.sPara__Template_Name_PM4;
		sPara__Template_Name_PM5 = dlg.sPara__Template_Name_PM5;
		sPara__Template_Name_PM6 = dlg.sPara__Template_Name_PM6;

		sPara__Template_Name_LL1 = dlg.sPara__Template_Name_LL1;
		sPara__Template_Name_LL2 = dlg.sPara__Template_Name_LL2;
	}

	// ...
	{
		CString key_name;
		CString ch_data;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM1;
				ch_data  = sPara__Template_Name_PM1;
			}
			else if(i == 1)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM2;
				ch_data  = sPara__Template_Name_PM2;
			}
			else if(i == 2)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM3;
				ch_data  = sPara__Template_Name_PM3;
			}
			else if(i == 3)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM4;
				ch_data  = sPara__Template_Name_PM4;
			}
			else if(i == 4)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM5;
				ch_data  = sPara__Template_Name_PM5;
			}
			else if(i == 5)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM6;
				ch_data  = sPara__Template_Name_PM6;
			}
			else if(i == 6)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL1;
				ch_data  = sPara__Template_Name_LL1;
			}
			else if(i == 7)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL2;
				ch_data  = sPara__Template_Name_LL2;
			}
			else
			{
				continue;
			}

			pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, ch_data);
		}
	}
}
void CDlg__Job_History::OnBnClickedBtn__Proc_Log_Lot()
{
	CDlg__Lot_Process dlg;

	// ...
	{
		dlg.sList__Slot_ID.Copy(sList__Tree_Slot_Info);

		dlg.sDir_Root = sDir_Root;
		mBtn__Result_Sel_Path.GetWindowText(dlg.sDir_Sub);

		dlg.sPara__LotID  = _Get_LotID__Result_Table();
		dlg.sPara__PortOD = _Get_PortID__Result_Table(); 
	}

	dlg.DoModal();
}

// ...
#include "Dlg__Wafer_Rcp_Sel.h"
#include "Dlg__Lot_Recipe_Log.h"

void CDlg__Job_History::OnBnClickedBtn__Rcp_Log_Wafer()
{
	CDlg__Wafer_Rcp_Sel dlg;

	// ...
	{
		CString dir_sub;
		mBtn__Result_Sel_Path.GetWindowText(dir_sub);

		dlg.sDir_Root = sDir_Root;
		dlg.sDir_Lot  = dir_sub;

		dlg.pWfr_Info = &mWfr_Info;
	}

	// ...
	{
		dlg.sPara__Rcp_Inf_PM1 = sPara__Rcp_Inf_PM1;
		dlg.sPara__Rcp_Inf_PM2 = sPara__Rcp_Inf_PM2;
		dlg.sPara__Rcp_Inf_PM3 = sPara__Rcp_Inf_PM3;
		dlg.sPara__Rcp_Inf_PM4 = sPara__Rcp_Inf_PM4;
		dlg.sPara__Rcp_Inf_PM5 = sPara__Rcp_Inf_PM5;
		dlg.sPara__Rcp_Inf_PM6 = sPara__Rcp_Inf_PM6;

		dlg.sPara__Rcp_Inf_LL1 = sPara__Rcp_Inf_LL1;
		dlg.sPara__Rcp_Inf_LL2 = sPara__Rcp_Inf_LL2;
	}

	dlg.DoModal();
}
void CDlg__Job_History::OnBnClickedBtn__Rcp_Log_Lot()
{
	CDlg__Lot_Recipe_Log dlg;

	// ...
	{
		CString dir_sub;
		mBtn__Result_Sel_Path.GetWindowText(dir_sub);

		dlg.sDir_Root = sDir_Root;
		dlg.sDir_Lot  = dir_sub;

		dlg.sPara__LotID  = _Get_LotID__Result_Table();
		dlg.sPara__PortOD = _Get_PortID__Result_Table(); 

		dlg.sList__Slot_ID.Copy(sList__Tree_Slot_Info);
	}

	// ...
	{
		CString key_name;
		CString ch_data;
		CString* p_dlg_str;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM1;
				ch_data  = sPara__Template_Name_PM1;

				p_dlg_str = &dlg.sPara__Template_Name_PM1;
			}
			else if(i == 1)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM2;
				ch_data  = sPara__Template_Name_PM2;

				p_dlg_str = &dlg.sPara__Template_Name_PM2;
			}
			else if(i == 2)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM3;
				ch_data  = sPara__Template_Name_PM3;

				p_dlg_str = &dlg.sPara__Template_Name_PM3;
			}
			else if(i == 3)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM4;
				ch_data  = sPara__Template_Name_PM4;

				p_dlg_str = &dlg.sPara__Template_Name_PM4;
			}
			else if(i == 4)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM5;
				ch_data  = sPara__Template_Name_PM5;

				p_dlg_str = &dlg.sPara__Template_Name_PM5;
			}
			else if(i == 5)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM6;
				ch_data  = sPara__Template_Name_PM6;

				p_dlg_str = &dlg.sPara__Template_Name_PM6;
			}
			else if(i == 6)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL1;
				ch_data  = sPara__Template_Name_LL1;

				p_dlg_str = &dlg.sPara__Template_Name_LL1;
			}
			else if(i == 7)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL2;
				ch_data  = sPara__Template_Name_LL2;

				p_dlg_str = &dlg.sPara__Template_Name_LL2;
			}
			else
			{
				continue;
			}

			if(ch_data == "")
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

			*p_dlg_str = ch_data;
		}
	}

	dlg.DoModal();

	// ...
	{
		sPara__Template_Name_PM1 = dlg.sPara__Template_Name_PM1;
		sPara__Template_Name_PM2 = dlg.sPara__Template_Name_PM2;
		sPara__Template_Name_PM3 = dlg.sPara__Template_Name_PM3;
		sPara__Template_Name_PM4 = dlg.sPara__Template_Name_PM4;
		sPara__Template_Name_PM5 = dlg.sPara__Template_Name_PM5;
		sPara__Template_Name_PM6 = dlg.sPara__Template_Name_PM6;

		sPara__Template_Name_LL1 = dlg.sPara__Template_Name_LL1;
		sPara__Template_Name_LL2 = dlg.sPara__Template_Name_LL2;
	}

	// ...
	{
		CString key_name;
		CString ch_data;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == 0)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM1;
				ch_data  = sPara__Template_Name_PM1;
			}
			else if(i == 1)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM2;
				ch_data  = sPara__Template_Name_PM2;
			}
			else if(i == 2)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM3;
				ch_data  = sPara__Template_Name_PM3;
			}
			else if(i == 3)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM4;
				ch_data  = sPara__Template_Name_PM4;
			}
			else if(i == 4)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM5;
				ch_data  = sPara__Template_Name_PM5;
			}
			else if(i == 5)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_PM6;
				ch_data  = sPara__Template_Name_PM6;
			}
			else if(i == 6)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL1;
				ch_data  = sPara__Template_Name_LL1;
			}
			else if(i == 7)
			{
				key_name = pKEY__CH_TEMPLATE_FILE_LL2;
				ch_data  = sPara__Template_Name_LL2;
			}
			else
			{
				continue;
			}

			pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, ch_data);
		}
	}
}

// ...
#include "Dlg__Ref_Wafer_Sel.h"

void CDlg__Job_History::OnBnClickedBtn__Ref_Wafer_Sel()
{
	CString para__dir_log;
	CString para__wfr_port;
	CString para__wfr_slot;

	CDlg__Ref_Wafer_Sel dlg;
	dlg.sDir_Root = sDir_Ref_Wfr;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	//
	para__dir_log  = dlg.sPara__Dir_Log;
	para__wfr_port = dlg.sPara__Wfr_Port;
	para__wfr_slot = dlg.sPara__Wfr_Slot;

	CString wfr_path;
	wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Ref_Wfr,para__dir_log,para__wfr_port,para__wfr_slot);

	//
	mBtn__Ref_Wafer_Info.SetWindowText(para__dir_log);
	mBtn__Ref_Wafer_Slot.SetWindowText(para__wfr_slot);
}

// ...
#include "Dlg__Ref_Wafer_Mng.h"

void CDlg__Job_History::OnBnClickedBtn__Ref_Wafer_Mng()
{
	CString para__dir_sub;
	CString para__portid;
	CString para__slotid;
	CString para__jobid;
	CString para__lotid;
	CString para__cstid;
	CString para__start_date;

	mBtn__Result_Sel_Path.GetWindowText(para__dir_sub);

	mBtn__Result_Sel_PortID.GetWindowText(para__portid);
	para__slotid = sBtn__Result_Sel_SlotID;

	para__jobid = _Get_JobID__Result_Table();
	para__lotid = _Get_LotID__Result_Table();
	para__cstid = _Get_CSTID__Result_Table();
	para__start_date = _Get_StartDate__Result_Table();

	//
	CDlg__Ref_Wafer_Mng dlg;

	dlg.sPara__DIR_INFO_DATA = para__dir_sub;
	
	dlg.sPara__PORTID_DATA = para__portid;
	dlg.sPara__SLOTID_DATA = para__slotid;

	dlg.sPara__JOBID_DATA = para__jobid;
	dlg.sPara__LOTID_DATA = para__lotid;
	dlg.sPara__CSTID_DATA = para__cstid;
	dlg.sPara__START_TIME_DATA = para__start_date;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	// ...
	CString src_path;
	CString trg_path;

	src_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,    para__dir_sub,para__portid,para__slotid);
	trg_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Ref_Wfr, para__dir_sub,para__portid,para__slotid);

	// ...
	CString dir_backup;

	// Directory Create ...
	{
		CStringArray l_para;
		MACRO__Convert__LIST('\\', trg_path, l_para);

		int i_limit = l_para.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString str_para = l_para[i];
			if(str_para.Find(".wfr") > 0)		break;

			dir_backup += str_para;
			dir_backup += "\\";

			CreateDirectory(dir_backup, NULL);
		}
	}

	// Log Backup ...
	{
		CopyFile(src_path, trg_path, TRUE);
	}

	// ...
	{
		CStringArray l_md_info;
		CStringArray l_tack;
		CStringArray l_rcp;
		CStringArray l_log_info;

		mWfr_Info.Get__PROCESS_LOG(l_md_info,l_tack,l_rcp,l_log_info);

		int i_limit = l_md_info.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString str__md_info  = l_md_info[i];
			CString str__log_info = l_log_info[i];

			// ...
			CString log_file = MACRO__Get_File_Name(str__log_info);
			CString dir_log = "";

			// Log Directory  ...
			{
				bool check_dir = true;

				// PMx Check ...
				if(check_dir)
				{
					int md_id = MACRO__Get_PMx_ID(str__md_info);		
					if(md_id > 0)
					{
						check_dir = false;
						dir_log.Format("%s\\PM%1d\\", dir_backup,md_id);
					}
				}
				// LLx Check ...
				if(check_dir)
				{
					int md_id = MACRO__Get_LLx_ID(str__md_info);
					if(md_id > 0)
					{
						check_dir = false;
						dir_log.Format("%s\\LL%1d\\", dir_backup,md_id);
					}
				}

				if(check_dir)
				{
					continue;
				}
			}

			CreateDirectory(dir_log, NULL);

			// ...
			CString name__log_d;
			CString name__log_rcp_inf;
			CString name__log_rcp_log;
			CString name__log_step;

			name__log_d.Format("%s.d",             log_file);
			name__log_rcp_inf.Format("%s.rcp_inf", log_file);
			name__log_rcp_log.Format("%s.rcp_log", log_file);
			name__log_step.Format("%s.step",       log_file);

			// ...
			CString path__log_d;
			CString path__log_rcp_inf;
			CString path__log_rcp_log;
			CString path__log_step;

			path__log_d.Format("%s\\%s",       dir_log,name__log_d);
			path__log_rcp_inf.Format("%s\\%s", dir_log,name__log_rcp_inf);
			path__log_rcp_log.Format("%s\\%s", dir_log,name__log_rcp_log);
			path__log_step.Format("%s\\%s",    dir_log,name__log_step);

			CString file_data;

			MACRO__Make_File_Data(path__log_d,       file_data, false);
			MACRO__Make_File_Data(path__log_rcp_inf, file_data, false);
			MACRO__Make_File_Data(path__log_rcp_log, file_data, false);
			MACRO__Make_File_Data(path__log_step,    file_data, false);
		}
	}
}

