// Dlg__Wafer_MDx_Sel.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"
#include "Dlg__Wafer_MDx_Sel.h"

#include "Dlg__MDx_SEL.h"
#include "Dlg__Wafer_Proc_Chart.h"

#include "Interface_Header.h"
#include "Macro_Function.h"


// CDlg__Wafer_MDx_Sel dialog

IMPLEMENT_DYNAMIC(CDlg__Wafer_MDx_Sel, CDialog)

CDlg__Wafer_MDx_Sel::CDlg__Wafer_MDx_Sel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Wafer_MDx_Sel::IDD, pParent)
{

}

CDlg__Wafer_MDx_Sel::~CDlg__Wafer_MDx_Sel()
{
}

void CDlg__Wafer_MDx_Sel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM1, mBtn__Template_Ctrl_PM1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM2, mBtn__Template_Ctrl_PM2);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM3, mBtn__Template_Ctrl_PM3);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM4, mBtn__Template_Ctrl_PM4);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM5, mBtn__Template_Ctrl_PM5);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_PM6, mBtn__Template_Ctrl_PM6);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_LL1, mBtn__Template_Ctrl_LL1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_CTRL_LL2, mBtn__Template_Ctrl_LL2);

	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM1, mBtn__Template_Name_PM1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM2, mBtn__Template_Name_PM2);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM3, mBtn__Template_Name_PM3);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM4, mBtn__Template_Name_PM4);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM5, mBtn__Template_Name_PM5);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_PM6, mBtn__Template_Name_PM6);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_LL1, mBtn__Template_Name_LL1);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_NAME_LL2, mBtn__Template_Name_LL2);

	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM1, mCheck__Template_PM1);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM2, mCheck__Template_PM2);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM3, mCheck__Template_PM3);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM4, mCheck__Template_PM4);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM5, mCheck__Template_PM5);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_PM6, mCheck__Template_PM6);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_LL1, mCheck__Template_LL1);
	DDX_Control(pDX, IDC_CHECK__TEMPLATE_LL2, mCheck__Template_LL2);

	DDX_Control(pDX, IDC_BTN__TEMPLATE_SEL_MDx, mBtn__Template_Sel_MDx);
	DDX_Control(pDX, IDC_BTN__TEMPLATE_SEL_NAME, mBtn__Template_Sel_Name);
	DDX_Control(pDX, IDC_LIST__MDx_TEMPLATE, mList__MDx_Template);

	DDX_Control(pDX, IDC_LIST__MDx_SEL, mList__MDx_Sel);
	DDX_Control(pDX, IDC_CHECK__STEP_MIN, mCheck__STEP_MIN);
	DDX_Control(pDX, IDC_CHECK__STEP_MIN2, mCheck__STEP_MAX);
	DDX_Control(pDX, IDC_CHECK__STEP_MIN3, mCheck__STEP_AVG);
}


BEGIN_MESSAGE_MAP(CDlg__Wafer_MDx_Sel, CDialog)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM1, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM2, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM2)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM3, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM3)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM4, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM4)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM5, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM5)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_PM6, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM6)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_LL1, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_LL1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_CTRL_LL2, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_LL2)

	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM1, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM2, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM2)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM3, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM3)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM4, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM4)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM5, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM5)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_PM6, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM6)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_LL1, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_LL1)
	ON_BN_CLICKED(IDC_BTN__TEMPLATE_NAME_LL2, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_LL2)

	ON_BN_CLICKED(IDC_BTN__LOG_GRAPH, &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Log_Graph)
	ON_BN_CLICKED(IDC_BTN__LOG_TEXT,  &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Log_Text)
	ON_BN_CLICKED(IDC_BTN__SAVE_CSV,  &CDlg__Wafer_MDx_Sel::OnBnClickedBtn__SAVE_CSV)

	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlg__Wafer_MDx_Sel message handlers

BOOL CDlg__Wafer_MDx_Sel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		CImageList *p_img = &mImg_List;

		// ...
		{
			CBitmap cBit;
			cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

			p_img->Create(1,20, ILC_COLOR4,1,1);
			p_img->Add(&cBit, RGB(0,0,0));	
		}

		// Wafer Table ...
		{
			CListCtrl* p_table = &mList__MDx_Sel;
			p_table->SetImageList(p_img, LVSIL_SMALL);

			// ...
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);

			_Make__MDx_List(p_table);
			_Add__MDx_List(p_table);
		}

		// Template Table ...
		{
			CListCtrl* p_table = &mList__MDx_Template;
			p_table->SetImageList(p_img, LVSIL_SMALL);

			// ...
			int list_view_stype;

			list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
			list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
			list_view_stype += LVS_EX_INFOTIP;

			p_table->SetExtendedStyle(list_view_stype);

			_Make__Template_List(p_table);
		}
	}

	// ...
	{
		mBtn__Template_Name_PM1.SetWindowText(sPara__Template_Name_PM1);
		mBtn__Template_Name_PM2.SetWindowText(sPara__Template_Name_PM2);
		mBtn__Template_Name_PM3.SetWindowText(sPara__Template_Name_PM3);
		mBtn__Template_Name_PM4.SetWindowText(sPara__Template_Name_PM4);
		mBtn__Template_Name_PM5.SetWindowText(sPara__Template_Name_PM5);
		mBtn__Template_Name_PM6.SetWindowText(sPara__Template_Name_PM6);

		mBtn__Template_Name_LL1.SetWindowText(sPara__Template_Name_LL1);
		mBtn__Template_Name_LL2.SetWindowText(sPara__Template_Name_LL2);
	}

	// ...
	{
		mCheck__STEP_MIN.SetCheck(0);
		mCheck__STEP_MAX.SetCheck(0);
		mCheck__STEP_AVG.SetCheck(0);
	}

	UpdateData(FALSE);
	return TRUE; 
}


void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM1()
{
	_Fnc__Template_Sel_MDx(1, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM2()
{
	_Fnc__Template_Sel_MDx(2, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM3()
{
	_Fnc__Template_Sel_MDx(3, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM4()
{
	_Fnc__Template_Sel_MDx(4, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM5()
{
	_Fnc__Template_Sel_MDx(5, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_PM6()
{
	_Fnc__Template_Sel_MDx(6, -1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_LL1()
{
	_Fnc__Template_Sel_MDx(-1, 1);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Ctrl_LL2()
{
	_Fnc__Template_Sel_MDx(-1, 2);
}
void CDlg__Wafer_MDx_Sel::
_Fnc__Template_Sel_MDx(const int pm_id, const int ll_id)
{
	CButton *p_btn_check = NULL;
	CButton *p_btn_name  = NULL;

	if(pm_id > 0)				// PMx ...
	{
		mCheck__Template_PM1.SetCheck(0);
		mCheck__Template_PM2.SetCheck(0);
		mCheck__Template_PM3.SetCheck(0);
		mCheck__Template_PM4.SetCheck(0);
		mCheck__Template_PM5.SetCheck(0);
		mCheck__Template_PM6.SetCheck(0);

		if(pm_id == 1)
		{
			p_btn_name  = &mBtn__Template_Name_PM1;
			p_btn_check = &mCheck__Template_PM1;
		}
		if(pm_id == 2)
		{
			p_btn_name  = &mBtn__Template_Name_PM2;
			p_btn_check = &mCheck__Template_PM2;
		}
		if(pm_id == 3)
		{
			p_btn_name  = &mBtn__Template_Name_PM3;
			p_btn_check = &mCheck__Template_PM3;
		}
		if(pm_id == 4)
		{
			p_btn_name  = &mBtn__Template_Name_PM4;
			p_btn_check = &mCheck__Template_PM4;
		}
		if(pm_id == 5)
		{
			p_btn_name  = &mBtn__Template_Name_PM5;
			p_btn_check = &mCheck__Template_PM5;
		}
		if(pm_id == 6)
		{
			p_btn_name  = &mBtn__Template_Name_PM6;
			p_btn_check = &mCheck__Template_PM6;
		}
	}
	else if(ll_id > 0)			// LLx ...
	{
		mCheck__Template_LL1.SetCheck(0);
		mCheck__Template_LL2.SetCheck(0);

		if(ll_id == 1)
		{
			p_btn_name  = &mBtn__Template_Name_LL1;
			p_btn_check = &mCheck__Template_LL1;
		}
		if(ll_id == 2)
		{
			p_btn_name  = &mBtn__Template_Name_LL2;
			p_btn_check = &mCheck__Template_LL2;
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
			p_btn_check->SetCheck(1);

			_Change__Template_Table(str_mdx, str_template); 
		}
	}
}

void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM1()
{
	CString str_template;
	mBtn__Template_Name_PM1.GetWindowText(str_template);

	_Change__Template_Table("PM1", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM2()
{
	CString str_template;
	mBtn__Template_Name_PM2.GetWindowText(str_template);

	_Change__Template_Table("PM2", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM3()
{
	CString str_template;
	mBtn__Template_Name_PM3.GetWindowText(str_template);

	_Change__Template_Table("PM3", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM4()
{
	CString str_template;
	mBtn__Template_Name_PM4.GetWindowText(str_template);

	_Change__Template_Table("PM4", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM5()
{
	CString str_template;
	mBtn__Template_Name_PM5.GetWindowText(str_template);

	_Change__Template_Table("PM5", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_PM6()
{
	CString str_template;
	mBtn__Template_Name_PM6.GetWindowText(str_template);

	_Change__Template_Table("PM6", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_LL1()
{
	CString str_template;
	mBtn__Template_Name_LL1.GetWindowText(str_template);

	_Change__Template_Table("LL1", str_template); 	
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Template_Name_LL2()
{
	CString str_template;
	mBtn__Template_Name_LL2.GetWindowText(str_template);

	_Change__Template_Table("LL2", str_template); 	
}
void CDlg__Wafer_MDx_Sel::
_Change__Template_Table(const CString& str_mdx, 
					   const CString& str_template)
{
	mBtn__Template_Sel_MDx.SetWindowText(str_mdx);
	mBtn__Template_Sel_Name.SetWindowText(str_template);

	_Add__Template_List(str_mdx, str_template);
}


void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Log_Graph()
{
	CString md_name  = _Get__MDx_Name_Of_MDx_List();
	CString log_path = _Get__Log_Path_Of_MDx_List();

	_Upload__Log_Graph(md_name, log_path);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__Log_Text()
{
	CString md_name  = _Get__MDx_Name_Of_MDx_List();
	CString log_path = _Get__Log_Path_Of_MDx_List();

	_Upload__Log_Text(md_name, log_path);
}
void CDlg__Wafer_MDx_Sel::OnBnClickedBtn__SAVE_CSV()
{
	CString md_name  = _Get__MDx_Name_Of_MDx_List();
	CString log_path = _Get__Log_Path_Of_MDx_List();

	_Upload__Log_CSV(md_name, log_path);
}

void CDlg__Wafer_MDx_Sel::OnDestroy()
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

