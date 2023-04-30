// Dlg__Lot_Process.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Lot_Process.h"

#include "Interface_Header.h"

#include "CLS__Proc_Log.h"
#include "Macro__Wafer_Tree.h"
#include "Macro_Function.h"


// CDlg__Lot_Process dialog

IMPLEMENT_DYNAMIC(CDlg__Lot_Process, CDialog)

CDlg__Lot_Process::CDlg__Lot_Process(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Lot_Process::IDD, pParent)
{

}
CDlg__Lot_Process::~CDlg__Lot_Process()
{
	delete mChart_Viwer.getChart();
}

void CDlg__Lot_Process::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__SLOT_INFO,   mList__Slot_Info);
	DDX_Control(pDX, IDC_BTN__LOTID_DATA,   mBtn__LotID_Data);
	DDX_Control(pDX, IDC_BTN__PORTID_DATA2, mBtn__PortID_Data);

	DDX_Control(pDX, IDC_CHART__TACK_TIME, mChart_Viwer);

	DDX_Control(pDX, IDC_BTN__SINGLE_SLOT, mBtn__Single_Slot);
	DDX_Control(pDX, IDC_BTN__SEL_SLOT,    mBtn__Sel_Slot);
	DDX_Control(pDX, IDC_BTN__MULTI_SLOT,  mBtn__Multi_Slot);
	DDX_Control(pDX, IDC_BTN__SLOT_ALL,    mBtn__Slot_All);
	DDX_Control(pDX, IDC_BTN__SLOT_CLEAR,  mBtn__Slot_Clear);

	DDX_Control(pDX, IDC_CHECK__PM1, mCheck_PM1);
	DDX_Control(pDX, IDC_CHECK__PM2, mCheck_PM2);
	DDX_Control(pDX, IDC_CHECK__PM3, mCheck_PM3);
	DDX_Control(pDX, IDC_CHECK__PM4, mCheck_PM4);
	DDX_Control(pDX, IDC_CHECK__PM5, mCheck_PM5);
	DDX_Control(pDX, IDC_CHECK__PM6, mCheck_PM6);

	DDX_Control(pDX, IDC_CHECK__LL1, mCheck_LL1);
	DDX_Control(pDX, IDC_CHECK__LL2, mCheck_LL2);
}

BEGIN_MESSAGE_MAP(CDlg__Lot_Process, CDialog)

	ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART__TACK_TIME, OnMouseMovePlotArea)

	ON_BN_CLICKED(IDC_BTN__CHART_REFRESH, &CDlg__Lot_Process::OnBnClickedBtn__Chart_Refresh)

	ON_BN_CLICKED(IDC_BTN__MULTI_SLOT,  &CDlg__Lot_Process::OnBnClickedBtn__Multi_Slot)
	ON_BN_CLICKED(IDC_BTN__SINGLE_SLOT, &CDlg__Lot_Process::OnBnClickedBtn__Single_Slot)
	ON_BN_CLICKED(IDC_BTN__SLOT_ALL,    &CDlg__Lot_Process::OnBnClickedBtn__Slot_All)
	ON_BN_CLICKED(IDC_BTN__SLOT_CLEAR,  &CDlg__Lot_Process::OnBnClickedBtn__Slot_Clear)

	ON_NOTIFY(NM_CLICK, IDC_LIST__SLOT_INFO, &CDlg__Lot_Process::OnNMClickList__Slot_Info)

	ON_BN_CLICKED(IDC_CHECK__PM1, &CDlg__Lot_Process::OnBnClickedCheck__PM1)
	ON_BN_CLICKED(IDC_CHECK__PM2, &CDlg__Lot_Process::OnBnClickedCheck__PM2)
	ON_BN_CLICKED(IDC_CHECK__PM3, &CDlg__Lot_Process::OnBnClickedCheck__PM3)
	ON_BN_CLICKED(IDC_CHECK__PM4, &CDlg__Lot_Process::OnBnClickedCheck__PM4)
	ON_BN_CLICKED(IDC_CHECK__PM5, &CDlg__Lot_Process::OnBnClickedCheck__PM5)
	ON_BN_CLICKED(IDC_CHECK__PM6, &CDlg__Lot_Process::OnBnClickedCheck__PM6)

	ON_BN_CLICKED(IDC_CHECK__LL1, &CDlg__Lot_Process::OnBnClickedCheck__LL1)
	ON_BN_CLICKED(IDC_CHECK__LL2, &CDlg__Lot_Process::OnBnClickedCheck__LL2)
END_MESSAGE_MAP()


// CDlg__Lot_Process message handlers

BOOL CDlg__Lot_Process::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mBtn__LotID_Data.SetWindowText(sPara__LotID);
		mBtn__PortID_Data.SetWindowText(sPara__PortOD);

		_Btn_Click__PMx(1);
		_Btn_Click__LLx(-1);
	}

	// ...
	{
		_Btn_Click__Multi_Slot();
	}

	// ...
	{
		sPara__X_Axis_Title = "Step";
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
		_Update__Slot_Step_Cnt();
		_Make__Proc_Chart();
	}

	// ...
	{
		mCheck_PM1.EnableWindow(FALSE);
		mCheck_PM2.EnableWindow(FALSE);
		mCheck_PM3.EnableWindow(FALSE);
		mCheck_PM4.EnableWindow(FALSE);
		mCheck_PM5.EnableWindow(FALSE);
		mCheck_PM6.EnableWindow(FALSE);

		mCheck_LL1.EnableWindow(FALSE);
		mCheck_LL2.EnableWindow(FALSE);

		// 
		CStringArray l__md_name;
		mSlot_Step.Get__All_MDx_List(l__md_name);

		int i_limit = l__md_name.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			int pm_id = MACRO__Get_PMx_ID(l__md_name[i]);
			if(pm_id > 0)
			{
				if(pm_id == 1)			mCheck_PM1.EnableWindow(TRUE);
				if(pm_id == 2)			mCheck_PM2.EnableWindow(TRUE);
				if(pm_id == 3)			mCheck_PM3.EnableWindow(TRUE);
				if(pm_id == 4)			mCheck_PM4.EnableWindow(TRUE);
				if(pm_id == 5)			mCheck_PM5.EnableWindow(TRUE);
				if(pm_id == 6)			mCheck_PM6.EnableWindow(TRUE);
				continue;
			}

			int ll_id = MACRO__Get_LLx_ID(l__md_name[i]);
			if(ll_id > 0)
			{
				if(ll_id == 1)			mCheck_LL1.EnableWindow(TRUE);
				if(ll_id == 2)			mCheck_LL2.EnableWindow(TRUE);
				continue;
			}
		}
	}

	return TRUE;
}

void CDlg__Lot_Process::_Update__Slot_Info()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	// ...
	CString str_portid = sPara__PortOD;

	mSlot_Step.Clear();

	// ...
	int i_limit = p_slot_info->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_slotid = _Get__ID_Of_Slot_List(i);

		// ...
		CString wfr_path;
		wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,sDir_Sub,str_portid,str_slotid);

		CLS__Wafer_Info wfr_info;
		MACRO__Update__Wafer_Info(wfr_path, &wfr_info);

		// 
		CStringArray l_md_info;
		CStringArray l_tack;
		CStringArray l_rcp;
		CStringArray l_log_info;

		wfr_info.Get__PROCESS_LOG(l_md_info,l_tack,l_rcp,l_log_info);

		//
		int k_limit = l_md_info.GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString md_name = l_md_info[k];
			int eqp_id = -1;

			// PMx ...
			int pm_id = MACRO__Get_PMx_ID(md_name);
			if(pm_id > 0)
			{
				eqp_id = pm_id + 1;

				//if(!_Is__PMx_Check(pm_id))			continue;
			}
			// LLx ...
			int ll_id = MACRO__Get_LLx_ID(md_name);
			if(ll_id > 0)
			{
				eqp_id = 1;

				//if(!_Is__LLx_Check(ll_id))			continue;
			}

			if(eqp_id < 1)		continue;

			CString log_name = l_log_info[k];

			//
			CGX__SYSTEM_CTRL x_sys_ctrl;
			CString dir_log;

			x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
			dir_log += "\\EQP_LOG\\Datalog";

			CString log_path;
			log_path.Format("%s\\%s.step", dir_log,log_name);

			//
			CLS__Proc_Log x_log;
			if(x_log.Upload__Proc_Step_Of_Log_File(m_hWnd, log_path) < 0)		
			{
				printf(" Error : log_path <- [%s] \n", log_path);
				// continue;
			}

			//
			CLS__MDx_Step_Info md_step;

			md_step.sMDx_Name = md_name;
			md_step.sList__Step_Time.Copy(x_log.mProc_Step.sList__Step_Tack);

			mSlot_Step.Load__Slot_Info(str_slotid, &md_step);
		}
	}
}
bool CDlg__Lot_Process::_Is__PMx_Check(const int pm_id)
{
	switch(pm_id)
	{
		case 1:
			if(mCheck_PM1.GetCheck() > 0)			return true;
			return false;

		case 2:
			if(mCheck_PM2.GetCheck() > 0)			return true;
			return false;

		case 3:
			if(mCheck_PM3.GetCheck() > 0)			return true;
			return false;

		case 4:
			if(mCheck_PM4.GetCheck() > 0)			return true;
			return false;

		case 5:
			if(mCheck_PM5.GetCheck() > 0)			return true;
			return false;

		case 6:
			if(mCheck_PM6.GetCheck() > 0)			return true;
			return false;
	}

	return false;
}
bool CDlg__Lot_Process::_Is__LLx_Check(const int ll_id)
{
	switch(ll_id)
	{
		case 1:
			if(mCheck_LL1.GetCheck() > 0)			return true;
			return false;

		case 2:
			if(mCheck_LL2.GetCheck() > 0)			return true;
			return false;
	}

	return false;
}

void CDlg__Lot_Process::OnBnClickedBtn__Chart_Refresh()
{
	_Update__Slot_Info();
	_Update__Slot_Step_Cnt();

	_Make__Proc_Chart();
}

void CDlg__Lot_Process::OnBnClickedBtn__Slot_All()
{
	_Btn_Click__Slot_All();

	_Make__Proc_Chart();
}
void CDlg__Lot_Process::_Btn_Click__Slot_All()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	int i_limit = p_slot_info->GetItemCount();
	for(int i=0; i<i_limit; i++)		
		p_slot_info->SetCheck(i, 1);
}

void CDlg__Lot_Process::OnBnClickedBtn__Slot_Clear()
{
	_Btn_Click__Slot_Clear();

	_Make__Proc_Chart();
}
void CDlg__Lot_Process::_Btn_Click__Slot_Clear()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	int i_limit = p_slot_info->GetItemCount();
	for(int i=0; i<i_limit; i++)		
		p_slot_info->SetCheck(i, 0);
}

void CDlg__Lot_Process::OnNMClickList__Slot_Info(NMHDR *pNMHDR, LRESULT *pResult)
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

void CDlg__Lot_Process::OnBnClickedBtn__Multi_Slot()
{
	_Btn_Click__Multi_Slot();

	_Make__Proc_Chart();
}
void CDlg__Lot_Process::_Btn_Click__Multi_Slot()
{
	mBtn__Single_Slot.EnableWindow(TRUE);

	mBtn__Multi_Slot.EnableWindow(FALSE);
	mBtn__Slot_All.EnableWindow(TRUE);
	mBtn__Slot_Clear.EnableWindow(TRUE);	

	bActive__Chart_Single = false;
}

void CDlg__Lot_Process::OnBnClickedBtn__Single_Slot()
{
	_Btn_Click__Single_Slot();

	_Make__Proc_Chart();
}
void CDlg__Lot_Process::_Btn_Click__Single_Slot()
{
	mBtn__Single_Slot.EnableWindow(FALSE);

	mBtn__Multi_Slot.EnableWindow(TRUE);
	mBtn__Slot_All.EnableWindow(FALSE);
	mBtn__Slot_Clear.EnableWindow(FALSE);

	bActive__Chart_Single = true;
}


void CDlg__Lot_Process::OnBnClickedCheck__PM1()
{
	_Btn_Click__PMx(1);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__PM2()
{
	_Btn_Click__PMx(2);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__PM3()
{
	_Btn_Click__PMx(3);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__PM4()
{
	_Btn_Click__PMx(4);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__PM5()
{
	_Btn_Click__PMx(5);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__PM6()
{
	_Btn_Click__PMx(6);
	_Btn_Click__LLx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}

void CDlg__Lot_Process::OnBnClickedCheck__LL1()
{
	_Btn_Click__LLx(1);
	_Btn_Click__PMx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}
void CDlg__Lot_Process::OnBnClickedCheck__LL2()
{
	_Btn_Click__LLx(2);
	_Btn_Click__PMx(-1);

	_Update__Slot_Step_Cnt();
	_Make__Proc_Chart();
}

void CDlg__Lot_Process::_Btn_Click__PMx(const int pm_id)
{
	mCheck_PM1.SetCheck(0);
	mCheck_PM2.SetCheck(0);
	mCheck_PM3.SetCheck(0);
	mCheck_PM4.SetCheck(0);
	mCheck_PM5.SetCheck(0);
	mCheck_PM6.SetCheck(0);

	if(pm_id == 1)			mCheck_PM1.SetCheck(1);
	if(pm_id == 2)			mCheck_PM2.SetCheck(1);
	if(pm_id == 3)			mCheck_PM3.SetCheck(1);
	if(pm_id == 4)			mCheck_PM4.SetCheck(1);
	if(pm_id == 5)			mCheck_PM5.SetCheck(1);
	if(pm_id == 6)			mCheck_PM6.SetCheck(1);
}
void CDlg__Lot_Process::_Btn_Click__LLx(const int ll_id)
{
	mCheck_LL1.SetCheck(0);
	mCheck_LL2.SetCheck(0);

	if(ll_id == 1)			mCheck_LL1.SetCheck(1);
	if(ll_id == 2)			mCheck_LL2.SetCheck(1);
}

CString CDlg__Lot_Process::_Get__MDx_Name()
{
	if(mCheck_PM1.GetCheck() > 0)			return	"PM1";
	if(mCheck_PM2.GetCheck() > 0)			return	"PM2";
	if(mCheck_PM3.GetCheck() > 0)			return	"PM3";
	if(mCheck_PM4.GetCheck() > 0)			return	"PM4";
	if(mCheck_PM5.GetCheck() > 0)			return	"PM5";
	if(mCheck_PM6.GetCheck() > 0)			return	"PM6";

	if(mCheck_LL1.GetCheck() > 0)			return	"LL1";
	if(mCheck_LL2.GetCheck() > 0)			return	"LL2";

	return "???";
}
