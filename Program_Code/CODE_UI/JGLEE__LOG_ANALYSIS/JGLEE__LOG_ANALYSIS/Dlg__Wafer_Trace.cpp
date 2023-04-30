// Dlg__Wafer_Trace.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Wafer_Trace.h"
#include "Dlg__Wafer_Trace_Sel.h"
#include "Dlg__Wafer_DA_Chart.h"
#include "Dlg__Wafer_Tack_Table.h"

#include "CObj__Wafer_Trace__KEY_DEF.h"

#include "Macro_Function.h"


// CDlg__Wafer_Trace dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_Trace, CDialog)

CDlg__Wafer_Trace::CDlg__Wafer_Trace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_Trace::IDD, pParent)
	, mStr__Sel_WaferID(_T(""))
	, mStr__Sel_LotID(_T(""))
	, mStr__Wafer_Path(_T(""))
{

}

CDlg__Wafer_Trace::~CDlg__Wafer_Trace()
{
}

void CDlg__Wafer_Trace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE__WAFER, mTree_Wafer);
	DDX_Control(pDX, IDC_CHECK__SEARCH_MOVE, mCheck__Search_Move);
	DDX_Control(pDX, IDC_CHECK__SEARCH_PROC, mCheck__Search_Proc);
	DDX_Control(pDX, IDC_CHECK__NODE_HISTORY, mCheck__Node_History);
	DDX_Control(pDX, IDC_CHECK__NODE_OPEN, mCheck__Node_Open);
	DDX_Control(pDX, IDC_CHECK__NODE_CLOSE, mCheck__Node_Close);

	DDX_Control(pDX, IDC_BTN__EXPAND_HISTORY_OPEN, mBtn__Node_History);
	DDX_Control(pDX, IDC_BTN__EXPAND_ALL_OPEN, mBtn__Node_All_Open);
	DDX_Control(pDX, IDC_BTN__EXPAND_ALL_CLOSE, mBtn__Node_All_Close);
	DDX_Control(pDX, IDC_BTN__WFR_REFRESH, mBtn__Wfr_Refresh);
	DDX_Control(pDX, IDC_BTN__DA_CHART, mBtn__DA_Chart);
	DDX_Control(pDX, IDC_BTN__TACK_TIME, mBtn__Tack_Time);
	DDX_Control(pDX, IDC_BTN__WAFER_SEL, mBtn__Wfr_Sel);

	DDX_Text(pDX, IDC_EDIT__WAFER_PATH, mStr__Wafer_Path);
	DDX_Control(pDX, IDC_EDIT__WAFER_PATH, mEdit__Wfr_Path);

	DDX_Text(pDX, IDC_EDIT__WAFERID, mStr__Sel_WaferID);
	DDX_Control(pDX, IDC_EDIT__WAFERID, mEdit__WfrID);

	DDX_Text(pDX, IDC_EDIT__LOTID, mStr__Sel_LotID);
	DDX_Control(pDX, IDC_EDIT__LOTID, mEdit__LotID);

	DDX_Control(pDX, IDC_GROUP__ITEM, mGroup__Item);
	DDX_Control(pDX, IDC_TEXT__WFRID, mText__WfrID);
	DDX_Control(pDX, IDC_TEXT__LOTID, mText__LotID);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_Trace, CDialog)
	ON_BN_CLICKED(IDC_BTN__WAFER_SEL,   &CDlg__Wafer_Trace::OnBnClickedBtn__Wafer_Sel)
	ON_BN_CLICKED(IDC_BTN__WFR_REFRESH, &CDlg__Wafer_Trace::OnBnClickedBtn__Wafer_Refresh)
	ON_BN_CLICKED(IDC_BTN__DA_CHART,    &CDlg__Wafer_Trace::OnBnClickedBtn__DA_Chart)
	ON_BN_CLICKED(IDC_BTN__TACK_TIME,   &CDlg__Wafer_Trace::OnBnClickedBtn__Tack_Time)

	ON_BN_CLICKED(IDC_BTN__EXPAND_HISTORY_OPEN, &CDlg__Wafer_Trace::OnBnClickedBtn__Expand_Node_History)
	ON_BN_CLICKED(IDC_BTN__EXPAND_ALL_OPEN,     &CDlg__Wafer_Trace::OnBnClickedBtn__Expand_All_Open)
	ON_BN_CLICKED(IDC_BTN__EXPAND_ALL_CLOSE,    &CDlg__Wafer_Trace::OnBnClickedBtn__Expand_All_Close)
END_MESSAGE_MAP()


// CDlg__Wafer_Trace message handlers

BOOL CDlg__Wafer_Trace::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
	// Wafer List ...
	{
		CListCtrl *p_table = &mList_Wafer;
		_Make__Table_List(p_table);
	}
	*/
	// Wafer Tree ...
	{
		bActive__Wafer_Tree = false;
		// _Init__Wafer_Tree();
	}

	// ..
	{
		mCheck__Node_History.SetCheck(1);
		mCheck__Node_Open.SetCheck(0);
		mCheck__Node_Close.SetCheck(0);

		mCheck__Search_Move.SetCheck(1);
		mCheck__Search_Proc.SetCheck(1);

		mStr__Sel_WaferID = "???";
		mStr__Sel_LotID   = "???";

		bActive_Init = false;
	}

	return TRUE; 
}

void CDlg__Wafer_Trace::OnBnClickedBtn__Expand_Node_History()
{
	_Expand__Node_History();
}
void CDlg__Wafer_Trace::_Expand__Node_History()
{
	// ..
	{
		mCheck__Node_History.SetCheck(1);
		mCheck__Node_Open.SetCheck(0);
		mCheck__Node_Close.SetCheck(0);
	}
	
	// ...
	CTreeCtrl *p_tree = &mTree_Wafer;
	HTREEITEM h_root = p_tree->GetRootItem();

	MACRO__Contract_All_Tree(p_tree);
	MACRO__Expand_Tree(p_tree, h_root, 2);
}

void CDlg__Wafer_Trace::OnBnClickedBtn__Expand_All_Open()
{
	// ..
	{
		mCheck__Node_History.SetCheck(0);
		mCheck__Node_Open.SetCheck(1);
		mCheck__Node_Close.SetCheck(0);
	}

	// ...
	CTreeCtrl *p_tree = &mTree_Wafer;

	MACRO__Expand_All_Tree(p_tree);
}
void CDlg__Wafer_Trace::OnBnClickedBtn__Expand_All_Close()
{
	// ..
	{
		mCheck__Node_History.SetCheck(0);
		mCheck__Node_Open.SetCheck(0);
		mCheck__Node_Close.SetCheck(1);
	}

	// ...
	CTreeCtrl *p_tree = &mTree_Wafer;

	MACRO__Contract_All_Tree(p_tree);
}

void CDlg__Wafer_Trace::OnBnClickedBtn__DA_Chart()
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
void CDlg__Wafer_Trace::OnBnClickedBtn__Tack_Time()
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

void CDlg__Wafer_Trace::OnBnClickedBtn__Wafer_Sel()
{
	CDlg__Wafer_Trace_Sel dlg;

	if(iREAL_MODE > 0)
	{
		CString key_word;
		CString ch_data;

		for(int i=0; i<iLPx_SIZE; i++)
		{
			key_word.Format("%s%1d", pKEY__CH_LPx_LOTID_X,i+1);
			ch_data = "";

			pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_word,ch_data);
			dlg.sPara__LOTID.Add(ch_data);
		}
	}
	else
	{
		CString ch_data;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_LPx_LOTID, ch_data);

		for(int i=0; i<iLPx_SIZE; i++)
		{
			dlg.sPara__LOTID.Add(ch_data);
		}
	}

	dlg.iREAL_MODE = iREAL_MODE;
	dlg.sPara__DIR_ROOT = sDir_Root;
	dlg.iPara__LPx_SIZE = iLPx_SIZE;

	if(dlg.DoModal() == IDOK)
	{
		int slot_id = dlg.iSel__SlotID;

		mStr__Sel_WaferID.Format("P%1d:%02d", dlg.iSel__PortID,slot_id);
		mStr__Sel_LotID  = dlg.sSel__LotID;
		mStr__Wafer_Path = dlg.sSel__Path;

		_Refresh__Wafer_Info(mStr__Wafer_Path);

		if(slot_id < 0)
		{
			CTreeCtrl *p_tree = &mTree_Wafer;
			p_tree->DeleteAllItems();
		}
		else
		{
			_Update__Wafer_Tree();
			_Expand__Node_History();
		}

		UpdateData(FALSE);
	}
}
void CDlg__Wafer_Trace::OnBnClickedBtn__Wafer_Refresh()
{
	UpdateData(TRUE);

	_Refresh__Wafer_Info(mStr__Wafer_Path);
	_Update__Wafer_Tree();
	_Expand__Node_History();
}
void CDlg__Wafer_Trace::_Refresh__Wafer_Info(const CString& wfr_file)
{
	CString wfr_path;
	wfr_path.Format("%s\\%s", sDir_Root,wfr_file);

	_Update__Wafer_Info(wfr_path);
}

