// Dlg__Wafer_Rcp_Sel.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_Rcp_Sel.h"

#include "Interface_Header.h"
#include "Macro_Function.h"


// CDlg__Wafer_Rcp_Sel dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_Rcp_Sel, CDialog)

CDlg__Wafer_Rcp_Sel::CDlg__Wafer_Rcp_Sel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_Rcp_Sel::IDD, pParent)
{

}

CDlg__Wafer_Rcp_Sel::~CDlg__Wafer_Rcp_Sel()
{
}

void CDlg__Wafer_Rcp_Sel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST__RCP_SEL,  mList__RCP_SEL);
	DDX_Control(pDX, IDC_LIST__RCP_INFO, mList__RCP_INFO);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_Rcp_Sel, CDialog)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDC_BTN__LOG_VIEW, &CDlg__Wafer_Rcp_Sel::OnBnClickedBtn__Rcp_View)
END_MESSAGE_MAP()


// CDlg__Wafer_Rcp_Sel message handlers

void CDlg__Wafer_Rcp_Sel::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if((nIDCtl == IDC_LIST__RCP_SEL )
	|| (nIDCtl == IDC_LIST__RCP_INFO))
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Wafer_Rcp_Sel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Rcp Sel - Table ...
	{
		CReportCtrl* p_table = &mList__RCP_SEL;
		p_table->SetNoSort(false);

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		_Make__RCP_List(p_table);
		_Add__RCP_List();
	}

	// Rcp Info - Table ...
	{
		CListCtrl* p_table = &mList__RCP_INFO;

		// ...
		{
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);
			p_table->ModifyStyle(LVS_OWNERDRAWFIXED, 0, 0);
		}

		iRCP_INFO__Column_Size = 0;
		_Make__INFO_List();
	}

	return TRUE; 
}

void CDlg__Wafer_Rcp_Sel::OnBnClickedBtn__Rcp_View()
{
	CString md_name  = _Get__MDx_Name_Of_RCP_List();
	CString log_path = _Get__Log_Path_Of_RCP_List();
	
	// ...
	int eqp_id = -1;

	CString dir_md;
	CString temp_name;

	int pm_id = MACRO__Get_PMx_ID(md_name);
	if(pm_id > 0)
	{
		eqp_id = pm_id + 1;
		dir_md.Format("PM%1d", pm_id);
	}

	int ll_id = MACRO__Get_LLx_ID(md_name);
	if(ll_id > 0)
	{
		eqp_id = 1;
		dir_md.Format("LL%1d", ll_id);
	}

	if(eqp_id > 0)
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_log;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
		dir_log += "\\EQP_LOG\\Datalog";

		// ...
		CString rcp_path;
		rcp_path.Format("%s\\%s.rcp_log", dir_log,log_path);

		// ...
		/*
		CString file_name = MACRO__Get_File_Name(log_path);

		CString bck_rcp__path;
		CString dir_path;

		// Backup ...
		{
			dir_path.Format("%s\\%s\\%s", sDir_Root,sDir_Lot,dir_md);
			CreateDirectory(dir_path, NULL);

		}

		// Recipe Log ...
		{
			bck_rcp__path.Format("%s\\%s.rcp_log", dir_path,file_name);

			printf(" * rcp_log_path \n");
			printf("  <- [%s] \n", bck_rcp__path);

			CopyFile(rcp_path, bck_rcp__path, TRUE);
		}
		*/

		if(Upload__Rcp_Info(rcp_path, &mRcp_Info) < 0)
		{
			_Clear__INFO_List();
			return;
		}
	}

	// ...
	{
		int st_limit = mRcp_Info.Get__Step_Size();
		int st_i;

		printf("Step Size <- [%1d] \n", st_limit);

		for(st_i=0; st_i<st_limit; st_i++)
		{
			CStep_Info* p_step = mRcp_Info.Get__Step_Info(st_i);

			printf(" * Step_[%02d] ... \n", st_i+1);

			//
			int i_limit = p_step->sList__Channe_Name.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				printf("  ** %02d)  [%s] <- [%s] \n",
					   i+1,
					   p_step->sList__Channe_Name[i],
					   p_step->sList__Channe_Data[i]);
			}
		}
	}

	// ...
	CString para_path;

	if(ll_id > 0)
	{
		if(ll_id == 1)			para_path = sPara__Rcp_Inf_LL1;
		if(ll_id == 2)			para_path = sPara__Rcp_Inf_LL2;

		printf(" ## LL%1d Rcp_Inf <- [%s] \n", ll_id,para_path);
	}
	if(pm_id > 0)
	{
		if(pm_id == 1)			para_path = sPara__Rcp_Inf_PM1;
		if(pm_id == 2)			para_path = sPara__Rcp_Inf_PM2;
		if(pm_id == 3)			para_path = sPara__Rcp_Inf_PM3;
		if(pm_id == 4)			para_path = sPara__Rcp_Inf_PM4;
		if(pm_id == 5)			para_path = sPara__Rcp_Inf_PM5;
		if(pm_id == 6)			para_path = sPara__Rcp_Inf_PM6;

		printf(" ## PM%1d Rcp_Inf <- [%s] \n", pm_id,para_path);
	}

	if(Upload__Para_Info(para_path, &mPara_Info) < 0)
	{
		_Clear__INFO_List();
		return;
	}

	_Make__INFO_List();
	_Add__INFO_List();
}
