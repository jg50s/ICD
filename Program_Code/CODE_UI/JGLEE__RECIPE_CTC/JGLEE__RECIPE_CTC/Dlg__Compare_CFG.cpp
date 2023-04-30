// Dlg_Compare_CFG.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Compare_CFG.h"

#include "CObj__Compare_CFG__KEY_DEF.h"
#include "Macro_Function.h"


// CDlg__Compare_CFG dialog

IMPLEMENT_DYNAMIC(CDlg__Compare_CFG, CDialog)

CDlg__Compare_CFG::CDlg__Compare_CFG(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Compare_CFG::IDD, pParent)
	, mStr_Save_File_Path(_T(""))
{

}

CDlg__Compare_CFG::~CDlg__Compare_CFG()
{
}

void CDlg__Compare_CFG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BTN__REF_PM_ID_UPDATE, mBtn__Ref_PM_ID_Data);
	DDX_Control(pDX, IDC_BTN__REF_RCP_TYPE_DATA, mBtn__Ref_Cfg_Type_Data);
	DDX_Control(pDX, IDC_BTN__REF_RECIPE_NAME, mBtn__Ref_Cfg_Page);
	DDX_Control(pDX, IDC_LIST__REF_FILE, mCtrl__Ref_List);
	DDX_Control(pDX, IDC_BTN__REF_PM_DATA, mBtn__Ref_PM_Data_Sel);
	DDX_Control(pDX, IDC_BTN__REF_RCP_TYPE_UPDATE, mBtn__Ref_Cfg_Type_Sel);
	DDX_Control(pDX, IDC_BTN__REF_RCP_COPY_TO_CHK_RCP, mBtn__Copy_Ref_To_Chk);

	DDX_Control(pDX, IDC_BTN__CHECK_PM_DATA, mBtn__Chk_PM_ID_Data);
	DDX_Control(pDX, IDC_BTN__CHECK_RECIPE_NAME, mBtn__Chk_Cfg_Page);
	DDX_Control(pDX, IDC_LIST__CHECK_FILE, mCtrl__Chk_List);
	DDX_Control(pDX, IDC_BTN__CHECK_PM_ID_UPDATE, mBtn__Chk_PM_Data_Sel);
	DDX_Control(pDX, IDC_BTN__CHK_RCP_COPY_TO_REF_RCP, mBtn__Copy_Chk_To_Ref);
	DDX_Control(pDX, IDC_TREE__RESULT_REPORT, mCtrl__Result_Tree);
	DDX_Text(pDX, IDC_EDIT__SAVE_FILE_PATH, mStr_Save_File_Path);
	DDX_Control(pDX, IDC_BTN__RESULT_SAVE, mBtn__Result_Save);
	DDX_Control(pDX, IDC_BTN__RESULT_CHECK, mBtn__Config_Compare);
}


BEGIN_MESSAGE_MAP(CDlg__Compare_CFG, CDialog)
	ON_WM_MEASUREITEM()

	ON_BN_CLICKED(IDC_BTN__REF_PM_CTRL, &CDlg__Compare_CFG::OnBnClickedBtn__Ref_PM_ID)
	ON_BN_CLICKED(IDC_BTN__CHECK_PM_CTRL, &CDlg__Compare_CFG::OnBnClickedBtn__Chk_PM_ID)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_TYPE_CTRL, &CDlg__Compare_CFG::OnBnClickedBtn__Ref_CFG_TYPE)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_UPDATE, &CDlg__Compare_CFG::OnBnClickedBtn__Ref_Update)
	ON_BN_CLICKED(IDC_BTN__CHECK_RCP_UPDATE, &CDlg__Compare_CFG::OnBnClickedBtn__Chk_Update)

	ON_NOTIFY(NM_CLICK, IDC_LIST__REF_FILE, &CDlg__Compare_CFG::OnNMClickList__Ref_Table)

	ON_BN_CLICKED(IDC_BTN__PATH_VIEW, &CDlg__Compare_CFG::OnBnClickedBtn__Path_View)
	ON_BN_CLICKED(IDC_BTN__RESULT_CHECK, &CDlg__Compare_CFG::OnBnClickedBtn__Config_Compare)
	ON_BN_CLICKED(IDC_BTN__RESULT_SAVE, &CDlg__Compare_CFG::OnBnClickedBtn__Result_Save)

	ON_BN_CLICKED(IDC_BTN__REF_RCP_COPY_TO_CHK_RCP, &CDlg__Compare_CFG::OnBnClickedBtn__Copy_Ref_To_Chk)
	ON_BN_CLICKED(IDC_BTN__CHK_RCP_COPY_TO_REF_RCP, &CDlg__Compare_CFG::OnBnClickedBtn__Copy_Chk_To_Ref)
END_MESSAGE_MAP()


// CDlg__Compare_CFG message handlers

void CDlg__Compare_CFG::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__REF_FILE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}
	else if(nIDCtl == IDC_LIST__CHECK_FILE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__Compare_CFG::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ref. Table ...
	{
		CListCtrl* p_table = &mCtrl__Ref_List;

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

		Make__File_List(p_table);
	}
	// Check Table ...
	{
		CListCtrl* p_table = &mCtrl__Chk_List;

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

		Make__File_List(p_table);
	}

	// Result ReportMoudle_List ...
	{
		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		CTreeCtrl  *p_tree = &mCtrl__Result_Tree;
		CImageList *p_img  = &mImg__Result_Tree;

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 

		p_tree->SetImageList(p_img, TVSIL_NORMAL);
	}

	// ...
	{
		mBtn__Ref_Cfg_Type_Data.SetWindowText("CFG");
		mBtn__Ref_Cfg_Type_Sel.SetWindowText("CFG");

		mBtn__Copy_Ref_To_Chk.EnableWindow(FALSE);
		mBtn__Copy_Chk_To_Ref.EnableWindow(FALSE);

		mBtn__Config_Compare.EnableWindow(FALSE);
		mBtn__Result_Save.EnableWindow(FALSE);
	}
	return TRUE; 
}


// ...
#include "Dlg__PMx_SEL.h"

void CDlg__Compare_CFG::OnBnClickedBtn__Ref_PM_ID()
{
	CDlg__PMx_SEL dlg;

	dlg.sPara__Win_Title = "PMx Selection";
	dlg.bActive__PMx_SEL = true;

	_Get__PMx_Title_List(dlg.sList__PMx_TITLE);
	mCls__Page_Info.Get__PM_ID(dlg.sList__PMx_ID);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data;

		int pm_id = dlg.iPara__PMx_SEL;
		CString pm_title = dlg.sPara__PMx_TITLE;
		
		if(pm_title.GetLength() > 0)
			str_data.Format("PM%1d  (%s)", pm_id,pm_title);
		else	
			str_data.Format("PM%1d", pm_id);

		mBtn__Ref_PM_Data_Sel.SetWindowText(str_data);
		mBtn__Ref_PM_ID_Data.SetWindowText(str_data);

		// ...
		CListCtrl* p_table = &mCtrl__Ref_List;

		_Click_Btn__Cfg_Update(true, pm_id, p_table);
	}
}
void CDlg__Compare_CFG::OnBnClickedBtn__Chk_PM_ID()
{
	CDlg__PMx_SEL dlg;

	dlg.sPara__Win_Title = "PMx Selection";
	dlg.bActive__PMx_SEL = true;

	_Get__PMx_Title_List(dlg.sList__PMx_TITLE);
	mCls__Page_Info.Get__PM_ID(dlg.sList__PMx_ID);

	if(dlg.DoModal() == IDOK)
	{
		CString str_data;

		int pm_id = dlg.iPara__PMx_SEL;
		CString pm_title = dlg.sPara__PMx_TITLE;

		if(pm_title.GetLength() > 0)
			str_data.Format("PM%1d  (%s)", pm_id,pm_title);
		else	
			str_data.Format("PM%1d", pm_id);

		mBtn__Chk_PM_Data_Sel.SetWindowText(str_data);
		mBtn__Chk_PM_ID_Data.SetWindowText(str_data);

		// ...
		CListCtrl* p_table = &mCtrl__Chk_List;

		_Click_Btn__Cfg_Update(false, pm_id, p_table);
	}
}

void CDlg__Compare_CFG::_Get__PMx_Title_List(CStringArray& l_pm_title)
{
	l_pm_title.RemoveAll();

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
		l_pm_title.Add(ch_data);
	}		
}

void CDlg__Compare_CFG::OnBnClickedBtn__Ref_CFG_TYPE()
{
	CDlg__PMx_SEL dlg;

	dlg.sPara__Win_Title = "Config-Type Selection";
	dlg.bActive__CFG_TYPE = true;

	dlg.sList__CFG_TYPE.RemoveAll();
	dlg.sList__CFG_TYPE.Add("CFG");
	// dlg.sList__CFG_TYPE.Add("PARA");

	if(dlg.DoModal() == IDOK)
	{
		CString str_data = dlg.sPara__CFG_TYPE_SEL;

		mBtn__Ref_Cfg_Type_Data.SetWindowText(str_data);
		mBtn__Ref_Cfg_Type_Sel.SetWindowText(str_data);
	}
}

void CDlg__Compare_CFG::OnBnClickedBtn__Ref_Update()
{
	CString str_data;
	mBtn__Ref_PM_ID_Data.GetWindowText(str_data);

	int pm_id = MACRO__Get__PMC_ID(str_data);
	if(pm_id < 1)		return;

	// ...
	CListCtrl* p_table = &mCtrl__Ref_List;

	_Click_Btn__Cfg_Update(true, pm_id, p_table);
}
void CDlg__Compare_CFG::OnBnClickedBtn__Chk_Update()
{
	CString str_data;
	mBtn__Chk_PM_ID_Data.GetWindowText(str_data);

	int pm_id = MACRO__Get__PMC_ID(str_data);
	if(pm_id < 1)		return;

	// ...
	CListCtrl* p_table = &mCtrl__Chk_List;

	_Click_Btn__Cfg_Update(false, pm_id, p_table);
}
void CDlg__Compare_CFG::_Click_Btn__Cfg_Update(const bool active_ref,
											   const int pm_id, 
											   CListCtrl* p_table)
{
	mBtn__Config_Compare.EnableWindow(FALSE);

	mBtn__Copy_Ref_To_Chk.EnableWindow(FALSE);
	mBtn__Copy_Chk_To_Ref.EnableWindow(FALSE);

	// ...
	CStringArray l_cfg_name;
	_Upload__Inf_Cfg_File(active_ref, pm_id, l_cfg_name);

	MACRO__Change_Order(l_cfg_name, false, false);

	Add__File_List(p_table, l_cfg_name);
}

void CDlg__Compare_CFG::OnNMClickList__Ref_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		int c_index = 1;

		CString file_name = mCtrl__Ref_List.GetItemText(r_index,c_index);
		mBtn__Ref_Cfg_Page.SetWindowText(file_name);

		mBtn__Config_Compare.EnableWindow(TRUE);

		mBtn__Copy_Ref_To_Chk.EnableWindow(FALSE);
		mBtn__Copy_Chk_To_Ref.EnableWindow(FALSE);
	}

	*pResult = 0;
}


// ...
#include "Dlg__MDx_Info.h"

void CDlg__Compare_CFG::OnBnClickedBtn__Path_View()
{
	CDlg__MDx_Info dlg;

	// ...
	CGX__SYSTEM_CTRL x_sys_ctrl;

	CStringArray l__pm_id;
	mCls__Page_Info.Get__PM_ID(l__pm_id);

	int i_limit = l__pm_id.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str__pm_id = l__pm_id[i];
		int eqp_id = atoi(str__pm_id) + 1;

		// ...
		CString dir_cfg;
		x_sys_ctrl->Get__SEQ_DIR_CONFIG(eqp_id, dir_cfg);

		CString str_info;
		str_info.Format("[PM%s]  %s", str__pm_id,dir_cfg);
		dlg.sList__MDx_Info.Add(str_info);
	}

	dlg.DoModal();
}

void CDlg__Compare_CFG::OnBnClickedBtn__Config_Compare()
{
	CUIntArray   l__err_type;
	CStringArray l__err_ref_ch;
	CStringArray l__err_ref_data;
	CStringArray l__err_chk_ch;
	CStringArray l__err_chk_data;

	_Fnc__Error_Check(l__err_type,
		              l__err_ref_ch,
					  l__err_ref_data,
					  l__err_chk_ch,
					  l__err_chk_data);

	_Fnc__Error_Report(l__err_type,
					   l__err_ref_ch,
					   l__err_ref_data,
					   l__err_chk_ch,
					   l__err_chk_data);

	mBtn__Result_Save.EnableWindow(TRUE);
}

void CDlg__Compare_CFG::OnBnClickedBtn__Result_Save()
{
	CTreeCtrl *p_tree = &mCtrl__Result_Tree;
	HTREEITEM h_node = p_tree->GetRootItem();

	CString log_info;
	CString str_info;

	while(h_node)
	{			
		str_info.Format(" * %s \n", p_tree->GetItemText(h_node));
		printf(str_info);

		log_info += str_info;
		log_info += _Get__Child_Node_List(p_tree, h_node, "");

		h_node = p_tree->GetNextItem(h_node, TVGN_NEXT);
		if(h_node == NULL)			break;
	}

	// ...
	CString dir_root;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_SAVE_DIR_ROOT, dir_root);
	CreateDirectory(dir_root, NULL);

	CString file_path;
	file_path.Format("%s\\Config_Result-%s.log", dir_root,MACRO__Get_Date_Time());

	if(MACRO__Save_File_Data(file_path, log_info) > 0)
	{
		mStr_Save_File_Path.Format(" File_Save Path  : \"%s\"", file_path);
	}
	else
	{
		mStr_Save_File_Path.Format(" File_Save Error : \"%s\"", file_path);
	}

	UpdateData(FALSE);
}
CString CDlg__Compare_CFG
::_Get__Child_Node_List(CTreeCtrl *p_tree, HTREEITEM h_parent, const CString& str_upper_tap)
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
		log_msg += _Get__Child_Node_List(p_tree, h_child, str_child_tap);

		h_child = p_tree->GetNextItem(h_child, TVGN_NEXT);
	}
	return log_msg;
}

void CDlg__Compare_CFG::OnBnClickedBtn__Copy_Ref_To_Chk()
{
	CString ref_pm_sel;
	CString ref_page_name;

	mBtn__Ref_PM_Data_Sel.GetWindowText(ref_pm_sel);
	mBtn__Ref_Cfg_Page.GetWindowText(ref_page_name);

	CString chk_pm_sel;
	CString chk_page_name;

	mBtn__Chk_PM_Data_Sel.GetWindowText(chk_pm_sel);
	mBtn__Chk_Cfg_Page.GetWindowText(chk_page_name);

	_Copy__Source_File_To_Other_PMx(ref_pm_sel,ref_page_name, chk_pm_sel,chk_page_name);
}
void CDlg__Compare_CFG::OnBnClickedBtn__Copy_Chk_To_Ref()
{
	CString ref_pm_sel;
	CString ref_page_name;

	mBtn__Ref_PM_Data_Sel.GetWindowText(ref_pm_sel);
	mBtn__Ref_Cfg_Page.GetWindowText(ref_page_name);

	CString chk_pm_sel;
	CString chk_page_name;

	mBtn__Chk_PM_Data_Sel.GetWindowText(chk_pm_sel);
	mBtn__Chk_Cfg_Page.GetWindowText(chk_page_name);

	_Copy__Source_File_To_Other_PMx(chk_pm_sel,chk_page_name, ref_pm_sel,ref_page_name);
}
int  CDlg__Compare_CFG
::_Copy__Source_File_To_Other_PMx(const CString& src_pm_id,
								  const CString& src_file,
								  const CString& trg_pm_id,
								  const CString& trg_file)
{
	if(src_file.CompareNoCase(trg_file) != 0)
	{
		CString err_title;
		CString err_msg;

		err_title = "Config File 파일 이름이 동일하지 않습니다.";
		err_msg.Format("Source File (%s) \n, Target File (%s) \n", src_file,trg_file);

		MessageBox(err_msg,err_title, MB_ICONERROR);
		return -11;
	}

	// ...
	CString src_path;
	CString trg_path;

	int src_eqp = MACRO__Get__PMC_ID(src_pm_id) + 1;
	int trg_eqp = MACRO__Get__PMC_ID(trg_pm_id) + 1;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;

		CString src_dir;
		x_sys_ctrl->Get__SEQ_DIR_CONFIG(src_eqp, src_dir);
		src_path.Format("%s\\%s.cfg", src_dir,src_file);

		CString trg_dir;
		x_sys_ctrl->Get__SEQ_DIR_CONFIG(trg_eqp, trg_dir);
		trg_path.Format("%s\\%s.cfg", trg_dir,trg_file);
	}

	// Copy ...
	{
		CopyFile(src_path, trg_path, FALSE);
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg.Format("Source File \"%s\"를 \n", src_file);
		log_msg += "아래의 경로에 복사 했습니다. \n";

		log_bff.Format(" \"%s\" \n", trg_path);						
		log_msg += log_bff;

		MessageBox(log_msg, "Copy Result ...", MB_OK);
	}

	// ...
	{
		CStringArray l_channel;
		CStringArray l_data;

		pGObj_Res->pGOBJ_PARA_CTRL->Undo__Config_Ex(trg_file, trg_eqp, trg_path, l_channel,l_data);
	}
	return 1;
}
