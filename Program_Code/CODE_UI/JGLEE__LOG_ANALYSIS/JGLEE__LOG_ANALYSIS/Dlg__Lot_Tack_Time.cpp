// Dlg__Lot_Tack_Time.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Lot_Tack_Time.h"

#include "resource.h"

#include "CLS__Wafer_Trace.h"
#include "Macro__Wafer_Tree.h"


// CDlg__Lot_Tack_Time dialog

IMPLEMENT_DYNAMIC(CDlg__Lot_Tack_Time, CDialog)

CDlg__Lot_Tack_Time::CDlg__Lot_Tack_Time(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Lot_Tack_Time::IDD, pParent)
{

}

CDlg__Lot_Tack_Time::~CDlg__Lot_Tack_Time()
{
	delete mChart_Viwer.getChart();
}

void CDlg__Lot_Tack_Time::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__SLOT_INFO,   mList__Slot_Info);
	DDX_Control(pDX, IDC_BTN__LOTID_DATA,   mBtn__LotID_Data);
	DDX_Control(pDX, IDC_BTN__PORTID_DATA2, mBtn__PortID_Data);

	DDX_Control(pDX, IDC_CHECK__MOVE, mCheck__Move);
	DDX_Control(pDX, IDC_CHECK__PROCESS, mCheck__Process);
	DDX_Control(pDX, IDC_CHART__TACK_TIME, mChart_Viwer);

	DDX_Control(pDX, IDC_BTN__SINGLE_SLOT, mBtn__Single_Slot);
	DDX_Control(pDX, IDC_BTN__MULTI_SLOT,  mBtn__Multi_Slot);
	DDX_Control(pDX, IDC_BTN__SLOT_ALL,    mBtn__Slot_All);
	DDX_Control(pDX, IDC_BTN__SLOT_CLEAR,  mBtn__Slot_Clear);
	DDX_Control(pDX, IDC_BTN__SEL_SLOT, mBtn__Sel_Slot);
}


BEGIN_MESSAGE_MAP(CDlg__Lot_Tack_Time, CDialog)

	ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART__TACK_TIME, OnMouseMovePlotArea)

	ON_BN_CLICKED(IDC_BTN__CHART_REFRESH, &CDlg__Lot_Tack_Time::OnBnClickedBtn__Chart_Refresh)

	ON_BN_CLICKED(IDC_BTN__MULTI_SLOT,  &CDlg__Lot_Tack_Time::OnBnClickedBtn__Multi_Slot)
	ON_BN_CLICKED(IDC_BTN__SINGLE_SLOT, &CDlg__Lot_Tack_Time::OnBnClickedBtn__Single_Slot)
	ON_BN_CLICKED(IDC_BTN__SLOT_ALL,    &CDlg__Lot_Tack_Time::OnBnClickedBtn__Slot_All)
	ON_BN_CLICKED(IDC_BTN__SLOT_CLEAR,  &CDlg__Lot_Tack_Time::OnBnClickedBtn__Slot_Clear)

	ON_NOTIFY(NM_CLICK, IDC_LIST__SLOT_INFO, &CDlg__Lot_Tack_Time::OnNMClickList__Slot_Info)

END_MESSAGE_MAP()


// CDlg__Lot_Tack_Time message handlers

BOOL CDlg__Lot_Tack_Time::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mBtn__LotID_Data.SetWindowText(sPara__LotID);
		mBtn__PortID_Data.SetWindowText(sPara__PortOD);
	}

	// ...
	{
		if(bPara__Active_Move)		mCheck__Move.SetCheck(1);
		else						mCheck__Move.SetCheck(0);

		if(bPara__Active_Proc)		mCheck__Process.SetCheck(1);
		else						mCheck__Process.SetCheck(0);

		_Btn_Click__Multi_Slot();
	}

	// ...
	{
		sPara__X_Axis_Title = "Action";
		sPara__Y_Axis_Title = "Time (sec)";

		_Init__Proc_Chart();
	}

	// ...
	{
		_Make__Slot_List();
		_Add__Slot_List(sList__Slot_ID);
	}

	// ...
	{
		_Btn_Click__Slot_All();
		
		_Update__Slot_Info();		
		_Update__Slot_Act_Cnt();
		_Make__Proc_Chart();
	}

	return TRUE;
}

void CDlg__Lot_Tack_Time::_Update__Slot_Info()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	// ...
	CString str_portid = sPara__PortOD;

	bool active_move = mCheck__Move.GetCheck();
	bool active_proc = mCheck__Process.GetCheck();

	mSlot_Tack.Clear();

	// ...
	int i_limit = p_slot_info->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_slotid = _Get__ID_Of_Slot_List(i);

		CString wfr_path;
		wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,sDir_Sub,str_portid,str_slotid);

		CLS__Wafer_Info wfr_info;
		MACRO__Update__Wafer_Info(wfr_path, &wfr_info);

		// 
		CStringArray l_module;
		CStringArray l_act;
		CStringArray l_result;
		CStringArray l_tack;
		CStringArray l_comment;

		wfr_info.Get__WAFER_TACK_INFO(active_move,
									  active_proc,
									  l_module,
									  l_act,
									  l_result,
									  l_tack,
									  l_comment);

		mSlot_Tack.Load__Slot_Info(str_slotid, l_module,l_act,l_result,l_tack,l_comment);
	}

	// ...
}

void CDlg__Lot_Tack_Time::OnBnClickedBtn__Chart_Refresh()
{
	_Update__Slot_Info();
	_Update__Slot_Act_Cnt();

	_Make__Proc_Chart();
}

void CDlg__Lot_Tack_Time::OnBnClickedBtn__Slot_All()
{
	_Btn_Click__Slot_All();

	_Make__Proc_Chart();
}
void CDlg__Lot_Tack_Time::_Btn_Click__Slot_All()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	int i_limit = p_slot_info->GetItemCount();
	for(int i=0; i<i_limit; i++)		
		p_slot_info->SetCheck(i, 1);
}

void CDlg__Lot_Tack_Time::OnBnClickedBtn__Slot_Clear()
{
	_Btn_Click__Slot_Clear();

	_Make__Proc_Chart();
}
void CDlg__Lot_Tack_Time::_Btn_Click__Slot_Clear()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	int i_limit = p_slot_info->GetItemCount();
	for(int i=0; i<i_limit; i++)		
		p_slot_info->SetCheck(i, 0);
}

void CDlg__Lot_Tack_Time::OnNMClickList__Slot_Info(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		if(bActive__Chart_Single)
		{

		}
		else
		{
			CListCtrl* p_slot_info = &mList__Slot_Info;

			if(p_slot_info->GetCheck(r_index) > 0)		p_slot_info->SetCheck(r_index, 0);
			else										p_slot_info->SetCheck(r_index, 1);
		}

		//
		CString str_data;
		str_data.Format("%1d", r_index+1);
		mBtn__Sel_Slot.SetWindowText(str_data);

		_Make__Proc_Chart();
	}

	*pResult = 0;
}

void CDlg__Lot_Tack_Time::OnBnClickedBtn__Multi_Slot()
{
	_Btn_Click__Multi_Slot();

	_Make__Proc_Chart();
}
void CDlg__Lot_Tack_Time::_Btn_Click__Multi_Slot()
{
	mBtn__Single_Slot.EnableWindow(TRUE);

	mBtn__Multi_Slot.EnableWindow(FALSE);
	mBtn__Slot_All.EnableWindow(TRUE);
	mBtn__Slot_Clear.EnableWindow(TRUE);	

	bActive__Chart_Single = false;
}

void CDlg__Lot_Tack_Time::OnBnClickedBtn__Single_Slot()
{
	_Btn_Click__Single_Slot();

	_Make__Proc_Chart();
}
void CDlg__Lot_Tack_Time::_Btn_Click__Single_Slot()
{
	mBtn__Single_Slot.EnableWindow(FALSE);

	mBtn__Multi_Slot.EnableWindow(TRUE);
	mBtn__Slot_All.EnableWindow(FALSE);
	mBtn__Slot_Clear.EnableWindow(FALSE);

	bActive__Chart_Single = true;
}
