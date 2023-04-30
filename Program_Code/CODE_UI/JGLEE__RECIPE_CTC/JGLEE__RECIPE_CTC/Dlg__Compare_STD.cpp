// Dlg__Compare_STD.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Compare_STD.h"

#include "CObj__Compare_STD__KEY_DEF.h"
#include "Macro_Function.h"


// CDlg__Compare_STD dialog

IMPLEMENT_DYNAMIC(CDlg__Compare_STD, CDialog)

CDlg__Compare_STD::CDlg__Compare_STD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Compare_STD::IDD, pParent)
	, mStr_Save_File_Path(_T(""))
{
	iPM_SIZE = 0;
}
CDlg__Compare_STD::~CDlg__Compare_STD()
{
}

void CDlg__Compare_STD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE__RESULT_REPORT, mTree__Result_Report);

	DDX_Control(pDX, IDC_LIST__REF_FILE,     mCtrl__Ref_File_List);
	DDX_Control(pDX, IDC_LIST__CHECK_FILE,   mCtrl__Check_File_List);

	DDX_Control(pDX, IDC_BTN__REF_PM_DATA,   mCtrl__Ref_PM_Data);
	DDX_Control(pDX, IDC_BTN__CHECK_PM_DATA, mCtrl__Check_PM_Data);

	DDX_Control(pDX, IDC_BTN__REF_RCP_TYPE_DATA,   mCtrl__Ref_Rcp_Type_Data);
	DDX_Control(pDX, IDC_BTN__CHECK_RCP_TYPE_DATA, mCtrl__Check_Rcp_Type_Data);

	DDX_Control(pDX, IDC_BTN__REF_PM_ID_UPDATE,    mCtrl__Ref_PM_ID_Update);
	DDX_Control(pDX, IDC_BTN__REF_RCP_TYPE_UPDATE, mCtrl__Ref_Rcp_Type_Update);

	DDX_Control(pDX, IDC_BTN__CHECK_PM_ID_UPDATE,    mCtrl__Check_PM_ID_Update);
	DDX_Control(pDX, IDC_BTN__CHECK_RCP_TYPE_UPDATE, mCtrl__Check_Rcp_Type_Update);

	DDX_Control(pDX, IDC_BTN__REF_RECIPE_NAME,   mCtrl__Ref_Recipe_Name);
	DDX_Control(pDX, IDC_BTN__CHECK_RECIPE_NAME, mCtrl__Check_Recipe_Name);

	DDX_Control(pDX, IDC_BTN__RESULT__REF_PM,       mCtrl__Result_Ref_PM);
	DDX_Control(pDX, IDC_BTN__RESULT__REF_RCP_NAME, mCtrl__Result_Ref_Rcp);

	DDX_Control(pDX, IDC_BTN__RESULT__CHECK_PM,       mCtrl__Result_Check_PM);
	DDX_Control(pDX, IDC_BTN__RESULT__CHECK_RCP_NAME, mCtrl__Result_Check_Rcp);
	DDX_Control(pDX, IDC_BTN__RESULT_SAVE, mCtrl__Result_Save);

	DDX_Text(pDX, IDC_EDIT__SAVE_FILE_PATH, mStr_Save_File_Path);
}


BEGIN_MESSAGE_MAP(CDlg__Compare_STD, CDialog)
	ON_BN_CLICKED(IDC_BTN__REF_PM_CTRL,   &CDlg__Compare_STD::OnBnClickedBtn__Ref_PM_Ctrl)
	ON_BN_CLICKED(IDC_BTN__CHECK_PM_CTRL, &CDlg__Compare_STD::OnBnClickedBtn__Check_PM_Ctrl)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_TYPE_CTRL,   &CDlg__Compare_STD::OnBnClickedBtn__Ref_Rcp_Type_Ctrl)
	ON_BN_CLICKED(IDC_BTN__CHECK_RCP_TYPE_CTRL, &CDlg__Compare_STD::OnBnClickedBtn__Check_Rcp_Type_Ctrl)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_UPDATE,   &CDlg__Compare_STD::OnBnClickedBtn__Ref_PM_Update)
	ON_BN_CLICKED(IDC_BTN__CHECK_RCP_UPDATE, &CDlg__Compare_STD::OnBnClickedBtn__Check_PM_Update)

	ON_NOTIFY(NM_CLICK, IDC_LIST__REF_FILE,   &CDlg__Compare_STD::OnNMClickList__Ref_File_Table)
	ON_NOTIFY(NM_CLICK, IDC_LIST__CHECK_FILE, &CDlg__Compare_STD::OnNMClickList__Check_File_Table)

	ON_BN_CLICKED(IDC_BTN__RESULT_CHECK,  &CDlg__Compare_STD::OnBnClickedBtn__Compare_Check)
	ON_BN_CLICKED(IDC_BTN__RESULT_SAVE,   &CDlg__Compare_STD::OnBnClickedBtn__Result_Save)
	ON_BN_CLICKED(IDC_BTN__RESULT_REPORT, &CDlg__Compare_STD::OnBnClickedBtn__Parameter_View)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_COPY_TO_CHK_RCP, &CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Chk_RCP)
	ON_BN_CLICKED(IDC_BTN__CHK_RCP_COPY_TO_REF_RCP, &CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Ref_RCP)
	ON_BN_CLICKED(IDC_BTN__REF_RCP_COPY_TO_OTHER_PMx, &CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Other_PMx)

	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__REF_FILE,   &CDlg__Compare_STD::OnLvnColumnclickList__Ref_File_Table)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__CHECK_FILE, &CDlg__Compare_STD::OnLvnColumnclickList__Check_File_Table)

END_MESSAGE_MAP()


// CDlg__Compare_STD message handlers

BOOL CDlg__Compare_STD::OnInitDialog()
{
	CDialog::OnInitDialog();

	Fnc_OnInitDialog();

	bSortDirect_RefFile   = false;
	bSortDirect_CheckFile = false;
	return TRUE; 
}
BOOL CDlg__Compare_STD::Fnc_OnInitDialog()
{
	// Ref_File List ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl *p_table = &mCtrl__Ref_File_List;
		CImageList *p_img  = &mImg__Ref_File_List;
		
		p_img->Create(1,20, ILC_COLOR4,1,1);	
		p_img->Add(&cBit, RGB(0,0,0));	
		
		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);

		Make__File_List(p_table);
	}
	// Check_File List ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl *p_table = &mCtrl__Check_File_List;
		CImageList *p_img  = &mImg__Check_File_List;

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);

		Make__File_List(p_table);
	}

	// Result ReportMoudle_List ...
	{
		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		CTreeCtrl  *p_tree = &mTree__Result_Report;
		CImageList *p_img  = &mImageList__Result_Report;

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 

		p_tree->SetImageList(p_img, TVSIL_NORMAL);
	}

	// Data Init ...
	{
		mCtrl__Result_Save.EnableWindow(FALSE);

		//
		mCtrl__Ref_PM_Data.SetWindowText("");
		mCtrl__Check_PM_Data.SetWindowText("");

		mCtrl__Ref_Rcp_Type_Data.SetWindowText("");
		mCtrl__Check_Rcp_Type_Data.SetWindowText("");

		mCtrl__Ref_PM_ID_Update.SetWindowText("");
		mCtrl__Ref_Rcp_Type_Update.SetWindowText("");

		mCtrl__Check_PM_ID_Update.SetWindowText("");
		mCtrl__Check_Rcp_Type_Update.SetWindowText("");

		mCtrl__Ref_Recipe_Name.SetWindowText("");
		mCtrl__Check_Recipe_Name.SetWindowText("");

		mCtrl__Result_Ref_PM.SetWindowText("");
		mCtrl__Result_Ref_Rcp.SetWindowText("");

		mCtrl__Result_Check_PM.SetWindowText("");
		mCtrl__Result_Check_Rcp.SetWindowText("");
	}

	return TRUE; 
}


// ...
#define _FILE_COL__NUMBER					0
#define _FILE_COL__FILE						1
#define _FILE_COL__DATE						2

void CDlg__Compare_STD
::Make__File_List(CListCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _FILE_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _FILE_COL__FILE)
			{
				l__col_name.Add("Route Recipe");
				l__col_width.Add(180);
			}
			else if(i == _FILE_COL__DATE)
			{
				l__col_name.Add("Date");
				l__col_width.Add(120);
			}
			else
			{
				break;
			}
		}
	}

	// ...
	{
		int i;

		p_table->DeleteAllItems();

		for(i=0; i<10; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

	// ...
	{
		CString col_name;
		int col_cx;

		int limit = l__col_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			col_name = l__col_name[i];
			col_cx   = (int) l__col_width[i];

			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}
void CDlg__Compare_STD
::Add__File_List(CListCtrl *p_table, 
				 const CStringArray& l_file_name,
				 const CStringArray& l_file_date)
{
	p_table->DeleteAllItems();

	// ...
	CString str_item;

	int i_limit = l_file_name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int k_limit = 5;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _FILE_COL__NUMBER)		str_item.Format("%1d", i+1);
			else if(k == _FILE_COL__FILE)		str_item = l_file_name[i];
			else if(k == _FILE_COL__DATE)		str_item = l_file_date[i];
			else								break;

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}
}

// ...
int CDlg__Compare_STD
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;
	CString str_data;

	// 
	{
		p_para->Get_Constant_Data(pKEY__DATA_PMx_SIZE, str_data);
		iPM_SIZE = atoi(str_data);
		if(iPM_SIZE > DEF_PMx__SIZE)		iPM_SIZE = DEF_PMx__SIZE;
	}

	// ...
	CString dir_root;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		
		x_sys_ctrl->Get__GUI_DIR_EXE(dir_root);
		dir_root += "\\INCLUDE_FILE\\";
	}

	// ...
	{
		CString dir_sub;
		CString file_name;
		CString file_path;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_SUB_DIR, dir_sub);
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_RCP_PARA_FILE_MAME, file_name);

		file_path.Format("%s\\%s\\%s", dir_root,dir_sub,file_name);

		// ...
		CPara_Info* p_para_info = &mPara_Info;
		Upload__Para_Info(file_path, p_para_info);
	}

	return 1;
}

// ...
int CDlg__Compare_STD
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	MoveWindow(sx,sy,wx,wy,true);
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__Compare_STD
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}

// ...
void CDlg__Compare_STD::OnBnClickedBtn__Ref_PM_Ctrl()
{
	CDlg__PMx_Selection dlg;
	Get__Para_Of_PMx_Selection(&dlg);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data;

		if(dlg.sPara__PMx_SEL.GetLength() > 0)
			str_data.Format("PM%1d  (%s)", dlg.iPara__PMx_SEL,dlg.sPara__PMx_SEL);
		else
			str_data.Format("PM%1d", dlg.iPara__PMx_SEL);
		
		mCtrl__Ref_PM_Data.SetWindowText(str_data);

		OnBnClickedBtn__Ref_PM_Update();
	}
}
void CDlg__Compare_STD::OnBnClickedBtn__Check_PM_Ctrl()
{
	CDlg__PMx_Selection dlg;
	Get__Para_Of_PMx_Selection(&dlg);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data;
		
		if(dlg.sPara__PMx_SEL.GetLength() > 0)
			str_data.Format("PM%1d  (%s)", dlg.iPara__PMx_SEL,dlg.sPara__PMx_SEL);
		else
			str_data.Format("PM%1d", dlg.iPara__PMx_SEL);

		mCtrl__Check_PM_Data.SetWindowText(str_data);

		OnBnClickedBtn__Check_PM_Update();
	}
}
void CDlg__Compare_STD
::Get__Para_Of_PMx_Selection(CDlg__PMx_Selection* p_dlg)
{
	p_dlg->iPara__PMx_Size = iPM_SIZE;

	// ...
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;

	CString key_name;
	CString ch_data;

	int i_limit = iPM_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		key_name.Format(pKEY__CH_CFG_NAME_PM_X, i+1);
		ch_data = "";

		p_para->Get_Channel_Data(key_name, ch_data);
		p_dlg->sPara__PMx_Name[i] = ch_data;
	}
}

void CDlg__Compare_STD::OnBnClickedBtn__Ref_Rcp_Type_Ctrl()
{
	CDlg__Rcp_Type_Selection dlg;
	Get__Para_Of_Rcp_Type_Selection(&dlg);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data = dlg.sPara__Type_SEL;
		mCtrl__Ref_Rcp_Type_Data.SetWindowText(str_data);

		OnBnClickedBtn__Ref_PM_Update();
	}
}
void CDlg__Compare_STD::OnBnClickedBtn__Check_Rcp_Type_Ctrl()
{
	CDlg__Rcp_Type_Selection dlg;
	Get__Para_Of_Rcp_Type_Selection(&dlg);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data = dlg.sPara__Type_SEL;
		mCtrl__Check_Rcp_Type_Data.SetWindowText(str_data);

		OnBnClickedBtn__Check_PM_Update();
	}
}
void CDlg__Compare_STD
::Get__Para_Of_Rcp_Type_Selection(CDlg__Rcp_Type_Selection* p_dlg)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;
	CString str_data;

	p_para->Get_Constant_Data(pKEY__DATA_PRE_SUB_DIR,  str_data);
	p_dlg->sPara__Pre_Sub_Dir = str_data;

	p_para->Get_Constant_Data(pKEY__DATA_MAIN_SUB_DIR, str_data);
	p_dlg->sPara__Main_Sub_Dir = str_data;

	p_para->Get_Constant_Data(pKEY__DATA_POST_SUB_DIR, str_data);
	p_dlg->sPara__Post_Sub_Dir = str_data;
}

void CDlg__Compare_STD::OnBnClickedBtn__Ref_PM_Update()
{
	UpdateData(TRUE);
	
	CString str_pmx;
	int pmx_id = 0;
	CString str_type;
	CString str_data;

	// ...
	{
		mCtrl__Ref_PM_Data.GetWindowText(str_pmx);
		pmx_id = MACRO__Get__PMC_ID(str_pmx);

		mCtrl__Ref_Rcp_Type_Data.GetWindowText(str_type);
	}

	// ...
	{
		mCtrl__Ref_PM_Data.GetWindowText(str_data);
		mCtrl__Ref_PM_ID_Update.SetWindowText(str_data);

		mCtrl__Ref_Rcp_Type_Data.GetWindowText(str_data);
		mCtrl__Ref_Rcp_Type_Update.SetWindowText(str_data);
	}

	// ...
	CString dir_sub  = str_type;
	CString file_ext = "rcp";

	CStringArray l_file_name;
	CStringArray l_file_date;

	// ...
	{
		int eqp_id = pmx_id + 1;

		CString dir_proc;	
		CString dir_log;

		CGX__SYSTEM_CTRL x_sys_ctrl;			
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_proc);

		dir_log.Format("%s\\%s", dir_proc,str_type);
		
		MACRO__Get_File_List(dir_log, file_ext, l_file_name,l_file_date);
	}

	// ...
	{
		CListCtrl* p_table  = &mCtrl__Ref_File_List;
		bSortDirect_RefFile = false;

		Sort__Route_File(p_table, 2, bSortDirect_RefFile, l_file_name,l_file_date);

		sList__Ref_File_List__File.Copy(l_file_name);
		sList__Ref_File_List__Date.Copy(l_file_date);
	}
}
void CDlg__Compare_STD::OnBnClickedBtn__Check_PM_Update()
{
	UpdateData(TRUE);

	CString str_pmx;
	int pmx_id = 0;
	CString str_type;
	CString str_data;

	// ...
	{
		mCtrl__Check_PM_Data.GetWindowText(str_pmx);
		pmx_id = MACRO__Get__PMC_ID(str_pmx);

		mCtrl__Check_Rcp_Type_Data.GetWindowText(str_type);
	}

	// ...
	{
		mCtrl__Check_PM_Data.GetWindowText(str_data);
		mCtrl__Check_PM_ID_Update.SetWindowText(str_data);

		mCtrl__Check_Rcp_Type_Data.GetWindowText(str_data);
		mCtrl__Check_Rcp_Type_Update.SetWindowText(str_data);
	}

	// ...
	CString file_ext = "rcp";

	CStringArray l_file_name;
	CStringArray l_file_date;

	// ...
	{
		int eqp_id = pmx_id + 1;
		
		CString dir_sub = str_type;
		CString dir_proc;	
		CString dir_log;

		CGX__SYSTEM_CTRL x_sys_ctrl;			
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_proc);

		dir_log.Format("%s\\%s", dir_proc,str_type);
		MACRO__Get_File_List(dir_log, file_ext, l_file_name,l_file_date);
	}

	// ...
	{
		CListCtrl* p_table = &mCtrl__Check_File_List;
		bSortDirect_CheckFile = false;

		Sort__Route_File(p_table, 2, bSortDirect_CheckFile, l_file_name,l_file_date);

		sList__Check_File_List__File.Copy(l_file_name);
		sList__Check_File_List__Date.Copy(l_file_date);
	}
}

void CDlg__Compare_STD::OnNMClickList__Ref_File_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int r_index = pNMItemActivate->iItem;
		int c_index = _FILE_COL__FILE;

		CString file_name = mCtrl__Ref_File_List.GetItemText(r_index,c_index);
		
		CString str_type;
		mCtrl__Ref_Rcp_Type_Data.GetWindowText(str_type);

		CString file_path;
		file_path.Format("%s\\%s", str_type,file_name);
		mCtrl__Ref_Recipe_Name.SetWindowText(file_path);

		printf(" * ref_recipe_name : [%s] \n", file_path);
	}

	*pResult = 0;
}
void CDlg__Compare_STD::OnNMClickList__Check_File_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int r_index = pNMItemActivate->iItem;
		int c_index = _FILE_COL__FILE;

		CString file_name = mCtrl__Check_File_List.GetItemText(r_index,c_index);

		CString str_type;
		mCtrl__Check_Rcp_Type_Data.GetWindowText(str_type);

		CString file_path;
		file_path.Format("%s\\%s", str_type,file_name);

		mCtrl__Check_Recipe_Name.SetWindowText(file_path);

		printf(" * check_recipe_name : [%s] \n", file_path);
	}

	*pResult = 0;
}

void CDlg__Compare_STD::OnBnClickedBtn__Compare_Check()
{
	UpdateData(TRUE);

	// ...
	CString str_pmx;
	CString ref_rcp;
	CString check_rcp;

	// Ref ...
	{
		mCtrl__Ref_PM_Data.GetWindowText(str_pmx);
		mCtrl__Ref_Recipe_Name.GetWindowText(ref_rcp);

		mCtrl__Result_Ref_PM.SetWindowText(str_pmx);
		mCtrl__Result_Ref_Rcp.SetWindowText(ref_rcp);
	}
	// Check ...
	{
		mCtrl__Check_PM_Data.GetWindowText(str_pmx);
		mCtrl__Check_Recipe_Name.GetWindowText(check_rcp);

		mCtrl__Result_Check_PM.SetWindowText(str_pmx);
		mCtrl__Result_Check_Rcp.SetWindowText(check_rcp);
	}

	// Rcp Compare ...
	{
		printf(" * ref_rcp   : [%s] \n", ref_rcp);
		printf(" * check_rcp : [%s] \n", check_rcp);
	}

	// ...
	{
		CString file_path;
		CString dir_root__ref;
		CString dir_root__check;

		// ...
		{
			CGX__SYSTEM_CTRL x_sys_ctrl;			
			CString dir_root;
			int eqp_id;

			// Ref.
			{
				mCtrl__Result_Ref_PM.GetWindowText(str_pmx);
				eqp_id = MACRO__Get__PMC_ID(str_pmx) + 1;
				
				x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
				dir_root__ref = dir_root;
			}
			// Check.
			{
				mCtrl__Result_Check_PM.GetWindowText(str_pmx);
				eqp_id = MACRO__Get__PMC_ID(str_pmx) + 1;
			
				x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
				dir_root__check = dir_root;
			}
		}

		// ...
		CRcp_Info *p_rcp_ref   = &mRcp_Info__Ref;
		CRcp_Info *p_rcp_check = &mRcp_Info__Check;

		// Upload Ref.Rcp ...
		{
			file_path.Format("%s\\%s.rcp", dir_root__ref,ref_rcp);
			printf(" * ref file_path : [%s] \n", file_path);

			Upload__Rcp_Info(file_path, p_rcp_ref);
		}
		// Upload Check.Rcp ...
		{
			file_path.Format("%s\\%s.rcp", dir_root__check,check_rcp);
			printf(" * check file_path : [%s] \n", file_path);

			Upload__Rcp_Info(file_path, p_rcp_check);
		}

		// Compare : Ref Rcp & Check Rcp ...
		{
			CTreeCtrl *p_tree = &mTree__Result_Report;
			p_tree->DeleteAllItems();

			HTREEITEM h_result_report = p_tree->InsertItem("RESULT_REPORT", 1,1, TVI_ROOT, TVI_LAST);
			HTREEITEM h_result_state  = p_tree->InsertItem("State : ???", 2,2, h_result_report, TVI_LAST);
			HTREEITEM h_result_error  = p_tree->InsertItem("Error : ???", 2,2, h_result_report, TVI_LAST);

			HTREEITEM h_error  = p_tree->InsertItem("ERROR_REPORT",  1,1, TVI_ROOT, TVI_LAST);

			// ...
			CString str_info;

			int ref__step_limit = p_rcp_ref->Get__Step_Size();
			int chk__step_limit = p_rcp_check->Get__Step_Size();

			int total__err_count = 0;
			int step__err_count = 0;
			int i_limit;
			int i;

			if(ref__step_limit > chk__step_limit)		i_limit = ref__step_limit;
			else										i_limit = chk__step_limit;

			printf(" * i_limit : [%1d] \n", i_limit);
			printf(" * ref__Step_limit : [%1d] \n", ref__step_limit);
			printf(" * chk__Step_limit : [%1d] \n", chk__step_limit);

			str_info.Format("Step_Size (%1d)", i_limit);
			HTREEITEM h_rcp = p_tree->InsertItem(str_info, 2,2, h_error, TVI_LAST);

			for(i=0; i<i_limit; i++)
			{
				CStep_Info* p_step_ref = p_rcp_ref->Get__Step_Info(i);
				CStep_Info* p_step_chk = p_rcp_check->Get__Step_Info(i);

				CStep_Info* p_step_inf = NULL;

				if(p_step_ref != NULL)		p_step_inf = p_step_ref;
				else						p_step_inf = p_step_chk;

				if(p_step_inf == NULL)
				{
					continue;
				}

				// ...
				str_info.Format("Step (%1d)", p_step_inf->iStep_ID);
				HTREEITEM h_step = p_tree->InsertItem(str_info, 2,2, h_rcp, TVI_LAST);

				if((p_step_ref == NULL)
				|| (p_step_chk == NULL))
				{
					CString err_type = "???";

						 if(p_step_ref == NULL)			err_type = "Ref_Step No Exist";
					else if(p_step_chk == NULL)			err_type = "Check_Step No Exist";

					// Error Type 		
					str_info.Format("Error_Type [%s]", err_type);
					HTREEITEM h_err_type = p_tree->InsertItem(str_info, 3,3, h_step, TVI_LAST);

					total__err_count++;
					step__err_count++;
					continue;
				}

				// ...
				int para__err_count = 0;

				int ref__para_limit = p_step_ref->sList__Channe_Type.GetSize();
				int chk__para_limit = p_step_chk->sList__Channe_Type.GetSize();

				int k_limit;
				int k;

				if(ref__para_limit > chk__para_limit)		k_limit = ref__para_limit;
				else										k_limit = chk__para_limit;

				for(k=0; k<k_limit; k++)
				{
					CString err_type = "???";

					CString ch_name = "";
					CString ref__ch_data = "";
					CString chk__ch_data = "";

					if(k < ref__para_limit)		ch_name = p_step_ref->sList__Channe_Name[k];
					else						ch_name = p_step_chk->sList__Channe_Name[k];

					if(k < ref__para_limit)		ref__ch_data = p_step_ref->sList__Channe_Data[k];
					if(k < chk__para_limit)		chk__ch_data = p_step_chk->sList__Channe_Data[k];

					// Error Check ...
					if(ref__ch_data.CompareNoCase(chk__ch_data) == 0)
					{
						continue;
					}
					else
					{
						para__err_count++;

						err_type = "Not Equal";
					}

					// Parameter Title
					CString str_category;
					CString str_title = mPara_Info.Get__Para_Title(ch_name, str_category);

					int img_id = 3;

						 if(str_category.GetLength() > 0)		str_info.Format("%s - %s", str_category,str_title);
					else if(str_title.GetLength()    > 0)		str_info = str_title;
					else
					{
						str_info = "* Unknown Parameter";
						img_id = 4;
					}
					HTREEITEM h_para = p_tree->InsertItem(str_info, img_id,img_id, h_step, TVI_LAST);

					// Error Type 		
					str_info.Format("Error_Type [%s]", err_type);
					HTREEITEM h_err_type = p_tree->InsertItem(str_info, 3,3, h_para, TVI_LAST);

					/*
					// Channel Type
					str_info.Format("Type [%s]", p_step_ref->sList__Channe_Type[k]);
					HTREEITEM h_ch_type = p_tree->InsertItem(str_info, 3,3, h_para, TVI_LAST);
					*/

					// Channel Name
					str_info.Format("Name [%s]", ch_name);
					HTREEITEM h_ch_name = p_tree->InsertItem(str_info, 3,3, h_para, TVI_LAST);

					// Ref. & Chk. Channel Data
					{
						str_info.Format("Ref_Data [%s]", ref__ch_data);
						p_tree->InsertItem(str_info, 3,3, h_para, TVI_LAST);

						str_info.Format("Chk_Data [%s]", chk__ch_data);
						p_tree->InsertItem(str_info, 3,3, h_para, TVI_LAST);
					}
				}

				total__err_count += para__err_count;

				if(para__err_count < 1)			p_tree->DeleteItem(h_step);
				else							step__err_count++;
			}

			// ...
			{
				if(total__err_count < 1)		str_info = "State : OK";
				else							str_info = "State : ERROR";
				p_tree->SetItemText(h_result_state, str_info);

				str_info.Format("Error : %1d", total__err_count);
				p_tree->SetItemText(h_result_error, str_info);

				//
				str_info.Format("Error_Step Size : [%1d]", step__err_count);
				p_tree->SetItemText(h_rcp, str_info);
			}

			p_tree->Expand(h_result_report, TVE_EXPAND);
			p_tree->Expand(h_error, TVE_EXPAND);
		}
	}

	mCtrl__Result_Save.EnableWindow(TRUE);
}

int  CDlg__Compare_STD
::Get__File_Info(const CString& file_path, CStringArray& l_line)
{
	l_line.RemoveAll();

	FILE *f_in = fopen(file_path, "r");
	if(f_in == NULL)			return -1;

	// ...
	char str_line[1000];
	int  line_count = 0;

	while(fgets(str_line,1000,f_in) != NULL)
	{
		line_count++;
		if(line_count > 5000)		break;

		l_line.Add(str_line);
	}

	fclose(f_in);	
	return 1;
}
int  CDlg__Compare_STD
::Upload__Rcp_Info(const CString& file_path, CRcp_Info* p_rcp_info)
{
	p_rcp_info->Clear__All();

	/*
	printf(" * Upload__Rcp_Info() ... \n");
	printf(" * file_path : [%s] \n", file_path);
	*/

	// ...
	CStringArray l_line;

	if(Get__File_Info(file_path, l_line) < 0)
	{
		return -1;
	}

	// ...
	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// printf(" # %1d) [%s] \n", i,str_line);

		CString word = "";
		char ch;

		int para_count = 0;
		CString para__ch_type;
		CString para__ch_name;
		CString para__ch_data;

		int active_step = -1;
		int active_para = -1;

		int k_len = str_line.GetLength();
		int k;

		for(k=0; k<k_len; k++)
		{
			ch = str_line[k];

			if((ch == ',') || (ch == ';'))
			{
				if(word.CompareNoCase("@") == 0)
				{
					if(para_count == 0)
					{
						active_step = 1;
					}
				}
				else if(word.CompareNoCase("&") == 0)
				{
					if(para_count == 0)
					{
						active_para = 1;
					}
				}
				else
				{
					if(active_step > 0)
					{
						if(para_count == 1)
						{
							int step_id = atoi(word);
							p_rcp_info->Add__Step_ID(step_id);

							// printf(" ** step_id : [%s] \n", word);
						}
					}
					else if(active_para > 0)
					{
							 if(para_count == 1)			para__ch_type = word;
						else if(para_count == 2)			para__ch_name = word;
						else if(para_count == 3)			para__ch_data = word;
					}
				}

				if(ch == ';')
				{
					if(active_para > 0)
					{
						p_rcp_info->Add__Step_Info(para__ch_type,para__ch_name,para__ch_data);
					}

					active_step = -1;
					active_para = -1;
					para_count = 0;
				}
				else
				{
					para_count++;
				}

				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}

	return 1;
}


// ...
#define _CMMD__RCP_PARA__ITEM_XXX					1
#define _CMMD__RCP_PARA__ITEM_YES					2

#define _CMMD__RCP_PARA__CATEGORY_XXX				11
#define _CMMD__RCP_PARA__CATEGORY_TITLE				12
#define _CMMD__RCP_PARA__CATEGORY_CHILD				13

#define _CMMD__RCP_PARA__CHANNEL					21

#define _CMMD__RCP_PARA__TITLE						31


int  CDlg__Compare_STD
::Upload__Para_Info(const CString& file_path, CPara_Info* p_para_info)
{
	p_para_info->Clear__All();

	// ...
	CStringArray l_line;

	if(Get__File_Info(file_path, l_line) < 0)
	{
		printf("  ** Get__File_Info - Error : [%s] \n", file_path);
		return -1;
	}

	// ...
	int active__para_item = -1;
	int active__category  = -1;
	CString para_category = "";
	CString para_title    = "";

	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// ...
		int active__para_cmmd = -1;
		int para_count = 0;		

		CString word = "";
		char ch;

		int k_len = str_line.GetLength();
		int k;

		for(k=0; k<k_len; k++)
		{
			ch = str_line[k];

			if((ch == ' ')		// space
			|| (ch == '	')		// tap 
			|| (ch == '\r') 
			|| (ch == '\n'))
			{
				if(word.GetLength() < 1)
				{
					continue;
				}

				if(para_count == 0)
				{
					if(word.CompareNoCase("##ITEM") == 0)
					{
						active__para_item = _CMMD__RCP_PARA__ITEM_XXX;
						active__category  = -1;
						
						para_title = "";
					}
					else if(active__para_item == _CMMD__RCP_PARA__ITEM_YES)
					{
							 if(word.CompareNoCase("#CATEGORY") == 0)			active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_XXX;
						else if(word.CompareNoCase("#CHANNEL")  == 0)			active__para_cmmd = _CMMD__RCP_PARA__CHANNEL;
						else if(word.CompareNoCase("#TITLE")    == 0)			active__para_cmmd = _CMMD__RCP_PARA__TITLE;
					}
				}
				else if(active__para_item == _CMMD__RCP_PARA__ITEM_XXX)
				{
					if(para_count == 1)
					{
						if(word.CompareNoCase("YES") == 0)
						{
							active__para_item = _CMMD__RCP_PARA__ITEM_YES;

							p_para_info->Add__New_Parameter();
						}
						else
						{
							active__para_item = -1;
						}
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__CATEGORY_XXX)
				{
					if(para_count == 1)
					{
						if(word.CompareNoCase("YES") == 0)
						{
							active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_TITLE;
							active__category  = 1;

							para_category = para_title;
						}
						else if(word.CompareNoCase("CHILD") == 0)
						{
							active__para_cmmd = _CMMD__RCP_PARA__CATEGORY_CHILD;
							active__category  = -1;

							p_para_info->Load__Para_Category(para_category);
						}
						else
						{
							active__para_cmmd = -1;
							active__category  = -1;
						}
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__CHANNEL)
				{
					if(para_count == 1)
					{
						p_para_info->Load__Para_Channel(word);
					}
				}
				else if(active__para_cmmd == _CMMD__RCP_PARA__TITLE)
				{
					if(para_count == 1)
					{
						p_para_info->Load__Para_Titlel(word);
						
						para_title = word;						
						if(active__category > 0)		para_category = word;
					}
				}

				para_count++;
				word = "";
			}
			else
			{
				word += ch;
			}
		}
	}

	return 1;
}

// ...
void CDlg__Compare_STD::OnBnClickedBtn__Result_Save()
{
	printf(" * CDlg__Compare_STD::OnBnClickedBtn__Result_Save() ... \n");

	// ...
	CString log_inf = "";

	// ...
	{
		CString log_bff;

		CString str_pmx;
		CString str_rcp;

		mCtrl__Result_Ref_PM.GetWindowText(str_pmx);
		mCtrl__Result_Ref_Rcp.GetWindowText(str_rcp);

		log_bff.Format(" Ref_Recipe   : [%s] [%s] \n", str_pmx,str_rcp);
		log_inf += log_bff;

		printf(log_bff);

		//
		mCtrl__Result_Check_PM.GetWindowText(str_pmx);
		mCtrl__Result_Check_Rcp.GetWindowText(str_rcp);
	
		log_bff.Format(" Check_Recipe : [%s] [%s] \n", str_pmx,str_rcp);
		log_bff += "\n";
		log_inf += log_bff;

		printf(log_bff);
	}

	// ...
	CTreeCtrl *p_tree = &mTree__Result_Report;
	HTREEITEM h_node = p_tree->GetRootItem();
	
	CString str_info;

	while(h_node)
	{			
		str_info.Format(" * %s \n", p_tree->GetItemText(h_node));
		printf(str_info);

		log_inf += str_info;
		log_inf += Get__Child_Node_List(p_tree, h_node, "");

		h_node = p_tree->GetNextItem(h_node, TVGN_NEXT);
		if(h_node == NULL)			break;
	}

	// ...
	{
		CString dir_root;

		// ...
		{
			pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_SAVE_DIR_ROOT, dir_root);

			CreateDirectory(dir_root, NULL);
		}

		CString file_path;
		file_path.Format("%s\\Recipe_Result-%s.log", dir_root,MACRO__Get_Date_Time());

		if(MACRO__Save_File_Data(file_path, log_inf) > 0)
		{
			mStr_Save_File_Path.Format(" File_Save Path  : \"%s\"", file_path);
		}
		else
		{
			mStr_Save_File_Path.Format(" File_Save Error : \"%s\"", file_path);
		}

		UpdateData(FALSE);
	}
}
CString CDlg__Compare_STD
::Get__Child_Node_List(CTreeCtrl *p_tree, HTREEITEM h_parent, const CString& str_upper_tap)
{
	CString log_msg = "";
	CString log_bff;

	HTREEITEM h_child = p_tree->GetNextItem(h_parent, TVGN_CHILD);
	CString str_child_tap = str_upper_tap + "  ";

	while(h_child)
	{	
		CString str_info = p_tree->GetItemText(h_child);		
		log_bff.Format(" %s %s \n", str_child_tap,str_info);
		
		printf(log_bff);

		log_msg += log_bff;
		log_msg += Get__Child_Node_List(p_tree, h_child, str_child_tap);

		h_child = p_tree->GetNextItem(h_child, TVGN_NEXT);
	}
	return log_msg;
}

void CDlg__Compare_STD
::OnBnClickedBtn__Parameter_View()
{
	mCtrl__Result_Save.EnableWindow(FALSE);

	// ...
	CPara_Info *p_para = &mPara_Info;
	CString str_info;

	CTreeCtrl *p_tree = &mTree__Result_Report;
	p_tree->DeleteAllItems();

	int i_limit = p_para->sList__Para_Channel.GetSize();
	int i;

	str_info.Format("RECIPE_PARAMETER [%1d]", i_limit);
	HTREEITEM h_root = p_tree->InsertItem(str_info, 1,1, TVI_ROOT, TVI_LAST);

	for(i=0; i<i_limit; i++)
	{
		CString str_title    = p_para->sList__Para_Title[i];
		CString str_category = p_para->sList__Para_Category[i];
		CString ch_name      = p_para->sList__Para_Channel[i];

		// ...		
		int img_id = 2;
		if(ch_name.GetLength() > 0)		img_id = 3;

		if(str_category.GetLength() > 0)		str_info.Format("%s - %s", str_category,str_title);
		else									str_info = str_title;

		HTREEITEM h_para = p_tree->InsertItem(str_info, img_id,img_id, h_root, TVI_LAST);

		p_tree->InsertItem(ch_name, 4,4, h_para, TVI_LAST);
	}

	p_tree->Expand(h_root, TVE_EXPAND);
}

void CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Chk_RCP()
{
	printf(" * CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Chk_RCP() ... \n");

	Copy__Source_File_To_Target_File(1);
}
void CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Ref_RCP()
{
	printf(" * CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Ref_RCP() ... \n");

	Copy__Source_File_To_Target_File(-1);
}
void CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Other_PMx()
{
	printf(" * CDlg__Compare_STD::OnBnClickedBtn__Copy_To_Other_PMx() ... \n");

	Copy__Source_File_To_Other_PMx();
}

int  CDlg__Compare_STD
::Copy__Source_File_To_Other_PMx()
{
	UpdateData(TRUE);

	if(iREAL_MODE < 0)
	{
		return 1;
	}

	// ...
	CString ref__pmx_id;
	CString ref__rcp_type;

	mCtrl__Ref_PM_ID_Update.GetWindowText(ref__pmx_id);
	mCtrl__Ref_Rcp_Type_Update.GetWindowText(ref__rcp_type);

	printf(" * Ref_Info ... \n");
	printf("  ** pm_id    : [%s] \n", ref__pmx_id);
	printf("  ** rcp_type : [%s] \n", ref__rcp_type);

	// ...
	CString src__pmx_id;
	CString src__rcp_type;

	CString src__file_name;
	CString err_mdule = "";

	CListCtrl *p_table__src;

	// ...
	{
		err_mdule = "Ref-File";

		p_table__src = &mCtrl__Ref_File_List;

		src__pmx_id   = ref__pmx_id;
		src__rcp_type = ref__rcp_type;
	}

	printf(" * Src_Info ... \n");
	printf("  ** pm_id    : [%s] \n", src__pmx_id);
	printf("  ** rcp_type : [%s] \n", src__rcp_type);

	// ...
	{
		int row = p_table__src->GetSelectionMark();
		if(row < 0)
		{
			printf(" * %s Row_Index  :  [%1d] \n", err_mdule,row);			

			CString err_title;
			CString err_msg;

			err_title = "복사할 File 파일을 선택해야 합니다.";
			err_msg   = "복사할 파일을 선택하시기 바랍니다.";

			MessageBox(err_msg,err_title, MB_ICONERROR);
			return -11;
		}

		src__file_name = p_table__src->GetItemText(row, _FILE_COL__FILE);
		printf(" * %s Name  :  [%s] \n", err_mdule,src__file_name);
	}

	// Copy ...
	CString src__copy_file;
	CString file_ext = "rcp";

	CStringArray l__copy_file;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;			

		int src__eqp_id = MACRO__Get__PMC_ID(src__pmx_id) + 1;
		CString src__file_data = "";

		// ...
		{
			CString src__dir_proc;	
			x_sys_ctrl->Get__SEQ_DIR_PROCESS(src__eqp_id, src__dir_proc);

			src__copy_file.Format("%s\\%s\\%s.%s", src__dir_proc,src__rcp_type,src__file_name,file_ext);

			if(MACRO__Get_File_Data(src__copy_file, src__file_data) < 0)
			{
				CString err_title;
				CString err_msg;
				CString err_bff;

				err_title = "File이 존재하지 않습니다.";

				err_msg = "File Path를 확인바랍니다. \n";
				err_bff.Format(" * File_Path [%s] \n", src__copy_file);
				err_msg += err_bff;

				MessageBox(err_msg,err_title, MB_ICONERROR);
				return -31;
			}
		}

		// ...
		int i_limit = iPM_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			int trg__eqp_id = 2 + i;

			if(src__eqp_id == trg__eqp_id)
			{
				continue;
			}

			CString trg__dir_proc;	
			x_sys_ctrl->Get__SEQ_DIR_PROCESS(trg__eqp_id, trg__dir_proc);

			CString trg__copy_file;
			trg__copy_file.Format("%s\\%s\\%s.%s", trg__dir_proc,src__rcp_type,src__file_name,file_ext);

			if(MACRO__Save_File_Data(trg__copy_file, src__file_data) < 0)
			{
				CString err_title;
				CString err_msg;
				CString err_bff;

				err_title = "Copy하지 못 했습니다.";

				err_msg = "Copy 할 File Path가 정확한지? 확인바랍니다. \n";
				err_bff.Format(" * File_Path [%s] \n", trg__copy_file);
				err_msg += err_bff;

				MessageBox(err_msg,err_title, MB_ICONERROR);
				return -41;
			}

			l__copy_file.Add(trg__copy_file);
		}
	}

	OnBnClickedBtn__Check_PM_Update();

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg.Format("Source File \"%s\"를 \n", src__copy_file);
		log_msg += "아래의 경로에 복사 했습니다. \n";

		int i_limit = l__copy_file.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			log_bff.Format(" %1d) \"%s\" \n", i+1,l__copy_file[i]);						
			log_msg += log_bff;
		}

		MessageBox(log_msg, "Copy Result ...", MB_OK);
	}
	return 1;
}
int  CDlg__Compare_STD
::Copy__Source_File_To_Target_File(const int ref_to_chk_copy)
{
	UpdateData(TRUE);

	// ...
	CString ref__pmx_id;
	CString ref__rcp_type;

	mCtrl__Ref_PM_ID_Update.GetWindowText(ref__pmx_id);
	mCtrl__Ref_Rcp_Type_Update.GetWindowText(ref__rcp_type);

	printf(" * Ref_Info ... \n");
	printf("  ** pm_id    : [%s] \n", ref__pmx_id);
	printf("  ** rcp_type : [%s] \n", ref__rcp_type);

	// ...
	CString chk__pmx_id;
	CString chk__rcp_type;

	mCtrl__Check_PM_ID_Update.GetWindowText(chk__pmx_id);
	mCtrl__Check_Rcp_Type_Update.GetWindowText(chk__rcp_type);

	printf(" * check_Info ... \n");
	printf("  ** pm_id    : [%s] \n", chk__pmx_id);
	printf("  ** rcp_type : [%s] \n", chk__rcp_type);

	if(ref__pmx_id == chk__pmx_id)
	{
		printf(" * Error(1) : PM_ID Same ... \n");

		CString err_title;
		CString err_msg;

		err_title = "PM_ID가 달라야 합니다.";
		err_msg   = "Ref와 Check의 PM_ID가 일치 합니다.";

		MessageBox(err_msg,err_title, MB_ICONERROR);
		return -1;
	}
	if(ref__rcp_type != chk__rcp_type)
	{
		printf(" * Error(2) : RCP_Type not Same ... \n");

		CString err_title;
		CString err_msg;

		err_title = "Process Type이 같아야 합니다.";
		err_msg   = "Ref와 Check의 Process Type이 일치해야 합니다.";

		MessageBox(err_msg,err_title, MB_ICONERROR);
		return -2;
	}

	// ...
	CString src__pmx_id;
	CString src__rcp_type;

	CString trg__pmx_id;
	CString trg__rcp_type;

	CString src__file_name;
	CString trg__file_name;
	CString err_mdule = "";

	CListCtrl *p_table__src;
	CListCtrl *p_table__trg;

	if(ref_to_chk_copy > 0)
	{
		err_mdule = "Ref-File";

		p_table__src = &mCtrl__Ref_File_List;
		p_table__trg = &mCtrl__Check_File_List;

		src__pmx_id   = ref__pmx_id;
		src__rcp_type = ref__rcp_type;

		trg__pmx_id   = chk__pmx_id;
		trg__rcp_type = chk__rcp_type;
	}
	else
	{
		err_mdule = "Check-File";

		p_table__src = &mCtrl__Check_File_List;
		p_table__trg = &mCtrl__Ref_File_List;

		src__pmx_id   = chk__pmx_id;
		src__rcp_type = chk__rcp_type;

		trg__pmx_id   = ref__pmx_id;
		trg__rcp_type = ref__rcp_type;
	}

	printf(" * Src_Info ... \n");
	printf("  ** pm_id    : [%s] \n", src__pmx_id);
	printf("  ** rcp_type : [%s] \n", src__rcp_type);

	printf(" * Trg_Info ... \n");
	printf("  ** pm_id    : [%s] \n", trg__pmx_id);
	printf("  ** rcp_type : [%s] \n", trg__rcp_type);

	// ...
	{
		int row = p_table__src->GetSelectionMark();
		if(row < 0)
		{
			printf(" * %s Row_Index  :  [%1d] \n", err_mdule,row);			

			CString err_title;
			CString err_msg;

			err_title = "복사할 File 파일을 선택해야 합니다.";
			err_msg   = "복사할 파일을 선택하시기 바랍니다.";

			MessageBox(err_msg,err_title, MB_ICONERROR);
			return -11;
		}

		src__file_name = p_table__src->GetItemText(row, _FILE_COL__FILE);
		printf(" * %s Name  :  [%s] \n", err_mdule,src__file_name);
	}

	// ...
	{
		int i_limit = p_table__trg->GetItemCount();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString trg_data = p_table__trg->GetItemText(i, _FILE_COL__FILE);

			if(src__file_name.CompareNoCase(trg_data) != 0)
			{
				continue;
			}

			if(iREAL_MODE > 0)
			{
				CString err_title;
				CString err_msg;

				err_title = "File이 이미 존재합니다.";
				err_msg.Format("%s의 File(%s)를 확인 바랍니다.", trg__pmx_id,src__file_name);

				MessageBox(err_msg,err_title, MB_ICONERROR);
				return -21;
			}
			break;
		}
	}

	// Copy ...
	CString src__copy_file;
	CString trg__copy_file;
	CString file_ext = "rcp";

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;			

		int src__eqp_id = MACRO__Get__PMC_ID(src__pmx_id) + 1;
		int trg__eqp_id = MACRO__Get__PMC_ID(trg__pmx_id) + 1;

		CString src__dir_proc;	
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(src__eqp_id, src__dir_proc);
		
		CString trg__dir_proc;	
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(trg__eqp_id, trg__dir_proc);

		trg__file_name = src__file_name;

		src__copy_file.Format("%s\\%s\\%s.%s", src__dir_proc,src__rcp_type,src__file_name,file_ext);
		trg__copy_file.Format("%s\\%s\\%s.%s", trg__dir_proc,trg__rcp_type,trg__file_name,file_ext);
	}

	// ...
	{
		printf(" * src__copy_file : [%s] \n", src__copy_file);
		printf(" * trg__copy_file : [%s] \n", trg__copy_file);
	}

	// ...
	CString file_data;

	if(MACRO__Get_File_Data(src__copy_file, file_data) < 0)
	{
		CString err_title;
		CString err_msg;
		CString err_bff;

		err_title = "File이 존재하지 않습니다.";

		err_msg = "File Path를 확인바랍니다. \n";
		err_bff.Format(" * File_Path [%s] \n", src__copy_file);
		err_msg += err_bff;

		MessageBox(err_msg,err_title, MB_ICONERROR);
		return -31;
	}

	if(MACRO__Save_File_Data(trg__copy_file, file_data) < 0)
	{
		CString err_title;
		CString err_msg;
		CString err_bff;

		err_title = "Copy하지 못 했습니다.";

		err_msg = "Copy 할 File Path가 정확한지? 확인바랍니다. \n";
		err_bff.Format(" * File_Path [%s] \n", trg__copy_file);
		err_msg += err_bff;

		MessageBox(err_msg,err_title, MB_ICONERROR);
		return -41;
	}

	// ...
	CString trg__rcp_name;
	CButton *p_btn_rcp;

	trg__rcp_name.Format("%s\\%s", trg__rcp_type,trg__file_name);

	if(ref_to_chk_copy > 0)
	{
		OnBnClickedBtn__Check_PM_Update();
		Search__File_Name_Of_File_Table(&mCtrl__Check_File_List, trg__file_name);

		p_btn_rcp = &mCtrl__Check_Recipe_Name;
	}
	else
	{
		OnBnClickedBtn__Ref_PM_Update();
		Search__File_Name_Of_File_Table(&mCtrl__Ref_File_List, trg__file_name);

		p_btn_rcp = &mCtrl__Ref_Recipe_Name;
	}

	p_btn_rcp->SetWindowText(trg__rcp_name);
	return 1;
}
int  CDlg__Compare_STD
::Search__File_Name_Of_File_Table(CListCtrl* p_table,
								  const CString& file_name)
{
	CString str_data;
	int s_index = -1;

	int i_limit = p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_data = p_table->GetItemText(i, _FILE_COL__FILE);

		if(file_name.CompareNoCase(str_data) != 0)
		{
			continue;
		}

		s_index = i;
		break;
	}

	if(s_index < 0)
	{
		printf(" * No Search : File_Name [%s] \n", file_name);
		return -1;
	}

	// ...
	{
		printf(" * Search_Index [%1d] : File_Name [%s] \n", s_index,file_name);

		p_table->SetItemState(s_index, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
		p_table->EnsureVisible(s_index, FALSE);
		p_table->SetFocus();
	}
	return 1;
}

void CDlg__Compare_STD::OnLvnColumnclickList__Ref_File_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(pNMLV->iItem == -1)
	{
		CListCtrl* p_table = &mCtrl__Ref_File_List;
		int col = pNMLV->iSubItem;

		Sort__Route_File(p_table, col, bSortDirect_RefFile, sList__Ref_File_List__File,sList__Ref_File_List__Date);
	}

	*pResult = 0;
}
void CDlg__Compare_STD::OnLvnColumnclickList__Check_File_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if(pNMLV->iItem == -1)
	{
		CListCtrl* p_table = &mCtrl__Check_File_List;
		int col = pNMLV->iSubItem;

		Sort__Route_File(p_table, col, bSortDirect_CheckFile, sList__Check_File_List__File,sList__Check_File_List__Date);
	}

	*pResult = 0;
}

int  CDlg__Compare_STD::
Sort__Route_File(CListCtrl* p_table,
				 const int col, 
				 bool& sort_order,
				 CStringArray& l_file,
				 CStringArray& l_date)
{
	if(col < 1)			return -1;
	if(col > 2)			return -2;

	// ...
	int i_limit = l_file.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString cmp_name = l_file[i];
		CString cmp_date = l_date[i];

		for(int k=i+1; k<i_limit; k++)
		{
			CString cur_name = l_file[k];
			CString cur_date = l_date[k];

			// ...
			bool active_order = false;

			if(col == 1)
			{
				if(sort_order)		
				{
					if(cmp_name.CompareNoCase(cur_name) > 0)		active_order = true;
				}
				else
				{
					if(cmp_name.CompareNoCase(cur_name) < 0)		active_order = true;
				}
			}
			else if(col == 2)
			{
				if(sort_order)		
				{
					if(cmp_date.CompareNoCase(cur_date) > 0)		active_order = true;
				}
				else
				{
					if(cmp_date.CompareNoCase(cur_date) < 0)		active_order = true;
				}
			}

			if(active_order)
			{
				l_file[i] = cur_name;
				l_date[i] = cur_date;

				l_file[k] = cmp_name;
				l_date[k] = cmp_date;

				cmp_name = cur_name;
				cmp_date = cur_date;
			}
		}

		// ...
	}

	Add__File_List(p_table, l_file,l_date);

	sort_order = !sort_order;
	return 1;
}
