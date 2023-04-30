// Dlg__Lot_Recipe_Log.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Lot_Recipe_Log.h"

#include "CLS__Wafer_Trace.h"
#include "Dlg__MDx_SEL.h"

#include "Interface_Header.h"
#include "Macro_Function.h"
#include "Macro__Wafer_Tree.h"

#include "CLS__Proc_Log.h"


// CDlg__Lot_Recipe_Log dialog

IMPLEMENT_DYNAMIC(CDlg__Lot_Recipe_Log, CDialog)

CDlg__Lot_Recipe_Log::CDlg__Lot_Recipe_Log(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Lot_Recipe_Log::IDD, pParent)
{

}

CDlg__Lot_Recipe_Log::~CDlg__Lot_Recipe_Log()
{
}

void CDlg__Lot_Recipe_Log::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__SLOT_INFO, mList__Slot_Info);
	DDX_Control(pDX, IDC_TREE__LOT_RECIPE, mTree__Lot_Recipe);
	DDX_Control(pDX, IDC_BTN__LOT_RECIPE, mBtn__Lot_Recipe);

	DDX_Control(pDX, IDC_CHECK_PM1, mCheck_PM1);
	DDX_Control(pDX, IDC_CHECK_PM2, mCheck_PM2);
	DDX_Control(pDX, IDC_CHECK_PM3, mCheck_PM3);
	DDX_Control(pDX, IDC_CHECK_PM4, mCheck_PM4);
	DDX_Control(pDX, IDC_CHECK_PM5, mCheck_PM5);
	DDX_Control(pDX, IDC_CHECK_PM6, mCheck_PM6);

	DDX_Control(pDX, IDC_CHECK_LL1, mCheck_LL1);
	DDX_Control(pDX, IDC_CHECK_LL2, mCheck_LL2);

	DDX_Control(pDX, IDC_BTN__LOTID_DATA, mBtn__LOTID_DATA);
	DDX_Control(pDX, IDC_BTN__PORTID_DATA, mBtn__PORTID_DATA);

	DDX_Control(pDX, IDC_BTN__SAVE_ALL_CSV, mBtn__SAVE_ALL_CSV);

	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM1, mBtn__Template_Name_PM1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM2, mBtn__Template_Name_PM2);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM3, mBtn__Template_Name_PM3);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM4, mBtn__Template_Name_PM4);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM5, mBtn__Template_Name_PM5);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_PM6, mBtn__Template_Name_PM6);

	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_LL1, mBtn__Template_Name_LL1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_DATA_LL2, mBtn__Template_Name_LL2);
}


BEGIN_MESSAGE_MAP(CDlg__Lot_Recipe_Log, CDialog)
	ON_WM_MEASUREITEM()

	ON_BN_CLICKED(IDC_BTN__SAVE_ALL_CSV, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Save_All_CSV)

	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM1, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM2, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM2)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM3, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM3)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM4, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM4)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM5, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM5)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM6, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM6)

	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_LL1, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_LL1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_LL2, &CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_LL2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlg__Lot_Recipe_Log message handlers

void CDlg__Lot_Recipe_Log::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__SLOT_INFO)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Lot_Recipe_Log::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mBtn__LOTID_DATA.SetWindowText(sPara__LotID);
		mBtn__PORTID_DATA.SetWindowText(sPara__PortOD);

		//
		mBtn__Template_Name_PM1.SetWindowText(sPara__Template_Name_PM1);
		mBtn__Template_Name_PM2.SetWindowText(sPara__Template_Name_PM2);
		mBtn__Template_Name_PM3.SetWindowText(sPara__Template_Name_PM3);
		mBtn__Template_Name_PM4.SetWindowText(sPara__Template_Name_PM4);
		mBtn__Template_Name_PM5.SetWindowText(sPara__Template_Name_PM5);
		mBtn__Template_Name_PM6.SetWindowText(sPara__Template_Name_PM6);

		mBtn__Template_Name_LL1.SetWindowText(sPara__Template_Name_LL1);
		mBtn__Template_Name_LL2.SetWindowText(sPara__Template_Name_LL2);
	}

	// Route_Recipe ...
	{
		CTreeCtrl* p_tree = &mTree__Lot_Recipe;

		// ...
		{
			CBitmap bmp;
			bmp.LoadBitmap(IDB_IMAGE_LIST);

			CImageList* p_img = &mImg_Tree;
			p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
			p_img->Add(&bmp, RGB(0, 0, 0)); 

			p_tree->SetImageList(p_img, TVSIL_NORMAL);
		}
	}

	// ...
	{
		CString dir_log;
		CString file_ext = "rte_log";

		dir_log.Format("%s\\%s", sDir_Root,sDir_Lot);

		CStringArray l_file;
		CStringArray l_date;
		MACRO__Get_File_List(dir_log,file_ext, l_file,l_date);

		if(l_file.GetSize() > 0)
		{
			CString rte_name = l_file[0];
			mBtn__Lot_Recipe.SetWindowText(rte_name);

			CString file_path;
			file_path.Format("%s\\%s.%s", dir_log,rte_name,file_ext);

			_Upload__Route_File(file_path);
		}
		else
		{
			printf(" route recipe - no exist ! \n");
		}
	}

	// ...
	{
		_Make__Slot_List();
		_Add__Slot_List(sList__Slot_ID);

		_Update__Slot_Info();
		_Update__MDx_Of_Slot_List();
	}

	return TRUE;
}

void CDlg__Lot_Recipe_Log::_Update__Slot_Info()
{
	CListCtrl* p_slot_info = &mList__Slot_Info;

	// ...
	CString str_portid = sPara__PortOD;

	mSlot_Proc.Clear();

	// ...
	int i_limit = p_slot_info->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_slotid = _Get__ID_Of_Slot_List(i);

		CString wfr_path;
		wfr_path.Format("%s\\%s\\P%s_%s.wfr", sDir_Root,sDir_Lot,str_portid,str_slotid);

		CLS__Wafer_Info wfr_info;
		MACRO__Update__Wafer_Info(wfr_path, &wfr_info);

		// 
		CStringArray l_module;
		CStringArray l_log_info;
		CStringArray l_result;

		wfr_info.Get__PROCESS_LOG(l_module, l_log_info, l_result);

		mSlot_Proc.Load__Slot_Process_Info(str_slotid, l_module,l_log_info,l_result);
	}
}

// ...
#include "Dlg__File_Save.h"

void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Save_All_CSV()
{
	CDlg__File_Save dlg;

	if(dlg.DoModal() != IDOK)		return;

	CString dir_output = dlg.sPara__SEL_DIR;

	bool active__aligh_left = true;
	if((dlg.bActive__ALIGN_RIGHT) && (!dlg.bActive__ALIGN_LEFT))
		active__aligh_left = false;

	// ...
	CString str_lotid;
	CString str_portid;

	mBtn__LOTID_DATA.GetWindowText(str_lotid);
	mBtn__PORTID_DATA.GetWindowText(str_portid);

	// ...
	int i_limit = 10;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int pm_id  = -1;
		int ll_id  = -1;
		CString md_name;

		if(i == 0)
		{
			if(mCheck_PM1.GetCheck() < 1)			continue;

			pm_id  = 1;
			md_name = "PM1";
		}
		else if(i == 1)
		{
			if(mCheck_PM2.GetCheck() < 1)			continue;

			pm_id  = 2;
			md_name = "PM2";
		}
		else if(i == 2)
		{
			if(mCheck_PM3.GetCheck() < 1)			continue;

			pm_id  = 3;
			md_name = "PM3";
		}
		else if(i == 3)
		{
			if(mCheck_PM4.GetCheck() < 1)			continue;

			pm_id  = 4;
			md_name = "PM4";
		}
		else if(i == 4)
		{
			if(mCheck_PM5.GetCheck() < 1)			continue;

			pm_id  = 5;
			md_name = "PM5";
		}
		else if(i == 5)
		{
			if(mCheck_PM6.GetCheck() < 1)			continue;

			pm_id  = 6;
			md_name = "PM6";
		}
		else if(i == 6)
		{
			if(mCheck_LL1.GetCheck() < 1)			continue;
	
			ll_id  = 1;
			md_name = "LL1";
		}
		else if(i == 7)
		{
			if(mCheck_LL2.GetCheck() < 1)			continue;

			ll_id  = 2;
			md_name = "LL2";
		}
		else
		{
			continue;
		}

		// ...
		int eqp_id = -1;
		CString temp_name;

		if(pm_id > 0)
		{
			eqp_id = pm_id + 1;
			temp_name = _Get__Template_Name_Of_PMx(pm_id);
		}
		else if(ll_id > 0)
		{
			eqp_id = 1;
			temp_name = _Get__Template_Name_Of_LLx(ll_id);
		}

		// ...
		CLS__Proc_Log x_log;

		x_log.bActive__CH_MIN = false;
		x_log.bActive__CH_MAX = false;
		x_log.bActive__CH_AVG = false;

		// ...
		{
			CGX__SYSTEM_CTRL x_sys_ctrl;
			CString dir_log;

			x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
			dir_log += "\\EQP_LOG\\Datalog";

			//
			CString temp_path;
			
			temp_path.Format("%s\\%s", dir_log,temp_name);
			
			if(x_log.Update__Template_File(m_hWnd, temp_path) < 0)
			{
				continue;;
			}

			// ...
			{
				CString dir_lot;

				dir_lot.Format("%s\\%s+%s", dir_output,str_lotid,str_portid);
				CreateDirectory(dir_lot, NULL);

				dir_output.Format("%s\\%s", dir_lot,md_name);
				CreateDirectory(dir_output, NULL);
			}

			// ...
			CStringArray l__slot_id;
			CStringArray l__log_info;

			mSlot_Proc.Get_Addr__Log_Info_Of_MDx(md_name, l__slot_id,l__log_info);

			int k_limit = l__slot_id.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				CString str__slot_id  = l__slot_id[k];
				CString str__log_info = l__log_info[k];

				// ...
				CString file_name = MACRO__Get_File_Name(str__log_info);

				CString path_input;
				if(ll_id > 0)		path_input.Format("%s\\%s.d%1d", dir_log,str__log_info,ll_id);
				else				path_input.Format("%s\\%s.d",    dir_log,str__log_info);

				CString path_output;
				path_output.Format("%s\\%s.csv", dir_output,file_name);

				if(x_log.Make__Log_Csv_File(m_hWnd, path_input,file_name,temp_name, path_output,active__aligh_left) < 0)
				{
					continue;
				}
			}
		}
	}
}

CString CDlg__Lot_Recipe_Log::
_Get__Template_Name_Of_PMx(const int pm_id)
{
	CString temp_name;

	if(pm_id == 1)		mBtn__Template_Name_PM1.GetWindowText(temp_name);
	if(pm_id == 2)		mBtn__Template_Name_PM2.GetWindowText(temp_name);
	if(pm_id == 3)		mBtn__Template_Name_PM3.GetWindowText(temp_name);
	if(pm_id == 4)		mBtn__Template_Name_PM4.GetWindowText(temp_name);
	if(pm_id == 5)		mBtn__Template_Name_PM5.GetWindowText(temp_name);
	if(pm_id == 6)		mBtn__Template_Name_PM6.GetWindowText(temp_name);

	return temp_name;
}
CString CDlg__Lot_Recipe_Log::
_Get__Template_Name_Of_LLx(const int ll_id)
{
	CString temp_name;

	if(ll_id == 1)		mBtn__Template_Name_LL1.GetWindowText(temp_name);
	if(ll_id == 2)		mBtn__Template_Name_LL2.GetWindowText(temp_name);

	return temp_name;
}

void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM1()
{
	_Fnc__Template_Sel_MDx(1, -1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM2()
{
	_Fnc__Template_Sel_MDx(2, -1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM3()
{
	_Fnc__Template_Sel_MDx(3, -1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM4()
{
	_Fnc__Template_Sel_MDx(4, -1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM5()
{
	_Fnc__Template_Sel_MDx(5, -1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_PM6()
{
	_Fnc__Template_Sel_MDx(6, -1);
}

void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_LL1()
{
	_Fnc__Template_Sel_MDx(-1, 1);
}
void CDlg__Lot_Recipe_Log::OnBnClickedBtn__Template_Ctrl_LL2()
{
	_Fnc__Template_Sel_MDx(-1, 2);
}

void CDlg__Lot_Recipe_Log::
_Fnc__Template_Sel_MDx(const int pm_id, const int ll_id)
{
	CButton *p_btn_name  = NULL;

	if(pm_id > 0)				// PMx ...
	{
		if(pm_id == 1)
		{
			p_btn_name  = &mBtn__Template_Name_PM1;
		}
		if(pm_id == 2)
		{
			p_btn_name  = &mBtn__Template_Name_PM2;
		}
		if(pm_id == 3)
		{
			p_btn_name  = &mBtn__Template_Name_PM3;
		}
		if(pm_id == 4)
		{
			p_btn_name  = &mBtn__Template_Name_PM4;
		}
		if(pm_id == 5)
		{
			p_btn_name  = &mBtn__Template_Name_PM5;
		}
		if(pm_id == 6)
		{
			p_btn_name  = &mBtn__Template_Name_PM6;
		}
	}
	else if(ll_id > 0)			// LLx ...
	{
		if(ll_id == 1)
		{
			p_btn_name  = &mBtn__Template_Name_LL1;
		}
		if(ll_id == 2)
		{
			p_btn_name  = &mBtn__Template_Name_LL2;
		}
	}

	// ...
	CString str_title;
	CString str_mdx;
	int eqp_id = -1;

	if(pm_id > 0)
	{
		eqp_id = pm_id + 1;

		str_title.Format("Select the template of PM%1d !", pm_id);
		str_mdx.Format("PM%1d", pm_id);
	}
	else if(ll_id > 0)
	{
		eqp_id = 1;

		str_title.Format("Select the template of LL%1d !", ll_id);
		str_mdx.Format("LL%1d", ll_id);
	}

	if(eqp_id > 0)
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_log;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(eqp_id, dir_log);
		dir_log += "\\EQP_LOG\\Datalog";

		// ...
		CStringArray l_file;
		CStringArray l_date;

		CString file_ext = "d_inf";
		if(ll_id > 0)		file_ext.Format("d%1d_inf", ll_id);
		
		MACRO__Get_File_List(dir_log, file_ext, l_file,l_date);

		// ...
		CDlg__MDx_SEL dlg;

		dlg.sPara__Dlg_Title = str_title;

		p_btn_name->GetWindowText(dlg.sCur__MDx_SEL);
		dlg.sList__MDx_SEL.Copy(l_file);

		if(dlg.DoModal() == IDOK)
		{
			CString str_template;
			str_template.Format("%s.%s", dlg.sCur__MDx_SEL,file_ext);

			p_btn_name->SetWindowText(str_template);
		}
	}
}

void CDlg__Lot_Recipe_Log::OnDestroy()
{
	CDialog::OnDestroy();

	// ...
	{
		mBtn__Template_Name_PM1.GetWindowText(sPara__Template_Name_PM1);
		mBtn__Template_Name_PM2.GetWindowText(sPara__Template_Name_PM2);
		mBtn__Template_Name_PM3.GetWindowText(sPara__Template_Name_PM3);
		mBtn__Template_Name_PM4.GetWindowText(sPara__Template_Name_PM4);
		mBtn__Template_Name_PM5.GetWindowText(sPara__Template_Name_PM5);
		mBtn__Template_Name_PM6.GetWindowText(sPara__Template_Name_PM6);

		mBtn__Template_Name_LL1.GetWindowText(sPara__Template_Name_LL1);
		mBtn__Template_Name_LL2.GetWindowText(sPara__Template_Name_LL2);
	}
}
