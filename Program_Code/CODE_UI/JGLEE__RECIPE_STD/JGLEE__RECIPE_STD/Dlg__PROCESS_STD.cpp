// Dlg__PROCESS_STD.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"

#include "Dlg__PROCESS_STD.h"


// CDlg__PROCESS_STD dialog

IMPLEMENT_DYNAMIC(CDlg__PROCESS_STD, CDialog)

CDlg__PROCESS_STD::CDlg__PROCESS_STD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PROCESS_STD::IDD, pParent)
{
	bActive__Interlock_Dll = false;
}

CDlg__PROCESS_STD::~CDlg__PROCESS_STD()
{
}

void CDlg__PROCESS_STD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_GridControl(pDX, IDC_GRID, m_Grid);

	DDX_Control(pDX, IDC_CHECK__RCP_TYPE_HEADER,    mCheck__Header_Type_Ctrl);
	DDX_Control(pDX, IDC_CHECK__RCP_TYPE_STEP,      mCheck__Step_Type_Ctrl);
	DDX_Control(pDX, IDC_CHECK__RCP_TYPE_TOLERANCE, mCheck__Tolerance_Type_Ctrl);

	DDX_Control(pDX, IDC_BTN__SEL_CUR_STEP_DATA,   mData__Sel_Step_Count);
	DDX_Control(pDX, IDC_BTN__SEL_CUR_PARA_DATA,   mData__Sel_Para_Count);
	DDX_Control(pDX, IDC_BTN__SEL_CUR_FILE_NAME,   mData__Sel_File_Name);
	DDX_Control(pDX, IDC_BTN__SEL_CUR_FOLDER_NAME, mData__Sel_Folder_Name);

	DDX_Control(pDX, IDC_LIST__RCP_FILE, mCtrl__File_Table);
	DDX_Control(pDX, IDC_CHECK__RCP_PRE_CTRL, mCheck__Rcp_Pre);
	DDX_Control(pDX, IDC_CHECK__RCP_MAIN_CTRL, mCheck__Rcp_Main);
	DDX_Control(pDX, IDC_CHECK__RCP_POST_CTRL, mCheck__Rcp_Post);
	DDX_Control(pDX, IDC_BTN__RCP_MAIN_COUNT, mData__Rcp_Main_Count);
	DDX_Control(pDX, IDC_BTN__RCP_PRE_COUNT, mData__Rcp_Pre_Count);
	DDX_Control(pDX, IDC_BTN__RCP_POST_COUNT, mData__Rcp_Post_Count);

	DDX_Control(pDX, IDC_BTN__FILE_NEW,    mCtrl__File_New);
	DDX_Control(pDX, IDC_BTN__FILE_SAVE,   mCtrl__File_Save);
	DDX_Control(pDX, IDC_BTN__FILE_SaveAs, mCtrl__File_SaveAs);
	DDX_Control(pDX, IDC_BTN__FILE_DELETE, mCtrl__File_Delete);
	DDX_Control(pDX, IDC_BTN__FILE_CSV,    mCtrl__File_CSV);
	DDX_Control(pDX, IDC_BTN__FILE_UNDO,   mCtrl__File_Undo);

	DDX_Control(pDX, IDC_BTN__SUMMARY_VIEW,   mCtrl__Summary_View);
	DDX_Control(pDX, IDC_CHECK__SUMMARY_SAVE, mCtrl__Summary_Save_Check);

	DDX_Control(pDX, IDC_BTN__STEP_APPEND, mCtrl__Step_Append);
	DDX_Control(pDX, IDC_BTN__STEP_COPY,   mCtrl__Step_Copy);
	DDX_Control(pDX, IDC_BTN__STEP_MOVE,   mCtrl__Step_Move);
	DDX_Control(pDX, IDC_BTN__STEP_DELETE, mCtrl__Step_Delete);
	DDX_Control(pDX, IDC_BTN__STEP_IID,    mCtrl__Sel_Step_ID);
	DDX_Control(pDX, IDC_BTN__ITEM_ID,     mCtrl__Sel_Item_ID);
	DDX_Control(pDX, IDC_BTN__SEND_FILE, mCtrl__Send_File);
}

BEGIN_MESSAGE_MAP(CDlg__PROCESS_STD, CDialog)
	ON_WM_MEASUREITEM()
	ON_WM_TIMER()

	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID, OnGridSelChanged) 

	ON_BN_CLICKED(IDC_CHECK__RCP_TYPE_HEADER,    &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Header)
	ON_BN_CLICKED(IDC_CHECK__RCP_TYPE_STEP,      &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Step)
	ON_BN_CLICKED(IDC_CHECK__RCP_TYPE_TOLERANCE, &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Tolerance)

	ON_BN_CLICKED(IDC_BTN__NODE_EXPAND,   &CDlg__PROCESS_STD::OnBnClickedBtn__Node_Expand)
	ON_BN_CLICKED(IDC_BTN__NODE_CONTRACT, &CDlg__PROCESS_STD::OnBnClickedBtn__Node_Contract)

	ON_NOTIFY(NM_CLICK, IDC_LIST__RCP_FILE, &CDlg__PROCESS_STD::OnNMClickList__File_Table)
	ON_BN_CLICKED(IDC_BTN__DIR_REFRESH,     &CDlg__PROCESS_STD::OnBnClickedBtn__File_Refresh)
	ON_BN_CLICKED(IDC_BTN__SEND_FILE,       &CDlg__PROCESS_STD::OnBnClickedBtn__Send_File)

	ON_BN_CLICKED(IDC_CHECK__RCP_PRE_CTRL,  &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Pre)
	ON_BN_CLICKED(IDC_CHECK__RCP_MAIN_CTRL, &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Main)
	ON_BN_CLICKED(IDC_CHECK__RCP_POST_CTRL, &CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Post)

	ON_BN_CLICKED(IDC_BTN__FILE_NEW,    &CDlg__PROCESS_STD::OnBnClickedBtn__File_New)
	ON_BN_CLICKED(IDC_BTN__FILE_SAVE,   &CDlg__PROCESS_STD::OnBnClickedBtn__File_Save)
	ON_BN_CLICKED(IDC_BTN__FILE_SaveAs, &CDlg__PROCESS_STD::OnBnClickedBtn__File_SaveAs)
	ON_BN_CLICKED(IDC_BTN__FILE_DELETE, &CDlg__PROCESS_STD::OnBnClickedBtn__File_Delete)
	ON_BN_CLICKED(IDC_BTN__FILE_CSV,    &CDlg__PROCESS_STD::OnBnClickedBtn__File_CSV)
	ON_BN_CLICKED(IDC_BTN__FILE_UNDO,   &CDlg__PROCESS_STD::OnBnClickedBtn__File_Undo)

	ON_BN_CLICKED(IDC_BTN__SUMMARY_VIEW,   &CDlg__PROCESS_STD::OnBnClickedBtn__Summary_View)
	ON_BN_CLICKED(IDC_CHECK__SUMMARY_SAVE, &CDlg__PROCESS_STD::OnBnClickedCheck__Summary_Save)

	ON_BN_CLICKED(IDC_BTN__STEP_APPEND, &CDlg__PROCESS_STD::OnBnClickedBtn__Step_Append)
	ON_BN_CLICKED(IDC_BTN__STEP_COPY,   &CDlg__PROCESS_STD::OnBnClickedBtn__Step_Copy)
	ON_BN_CLICKED(IDC_BTN__STEP_MOVE,   &CDlg__PROCESS_STD::OnBnClickedBtn__Step_Move)
	ON_BN_CLICKED(IDC_BTN__STEP_DELETE, &CDlg__PROCESS_STD::OnBnClickedBtn__Step_Delete)

END_MESSAGE_MAP()


// CDlg__PROCESS_STD message handlers

void CDlg__PROCESS_STD::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if(nIDCtl == IDC_LIST__RCP_FILE)
	{
		lpMeasureItemStruct->itemHeight = 21;
	}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

BOOL CDlg__PROCESS_STD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		iItem_Height = 27;
	}

	// ...
	{
		CString dir_log_root = sDir__ROOT_UI;

		dir_log_root += "\\_EVENT";
		xI_Log_Ctrl->Create__LOG_DIR(dir_log_root);

		dir_log_root += "\\RCP_HISTORY";
		xI_Log_Ctrl->Create__LOG_DIR(dir_log_root);

		//
		CString sub_dir;

		     if(iMODULE_ID == 0)		sub_dir = "\\CTC";
		else if(iMODULE_ID == 1)		sub_dir = "\\TMC";
		else							sub_dir.Format("\\PM%1d", iMODULE_ID-1);

		dir_log_root += sub_dir;
		xI_Log_Ctrl->Init__FILE(dir_log_root);

		xI_Log_Ctrl->SET__LOG_FILE_TIME(1);
		xI_Log_Ctrl->SET__LOG_BACKUP_DATE_SIZE(10);

		/*
		CString log_msg;

		log_msg = "LOG START ..... \n";
		log_msg += "\n";

		xI_Log_Ctrl->Write__LOG(log_msg);	
		*/
	}	

	// ...
	{
		COLORREF color__child_col  = RGB( 40, 108, 149);	

		m_Img_List.Create(16,16,ILC_COLOR24, 3, 3);
		m_Img_List.SetBkColor(color__child_col);

		m_Img_List.Add(AfxGetApp()->LoadIcon(IDI_PLUS));	// 0
		m_Img_List.Add(AfxGetApp()->LoadIcon(IDI_MINUS));	// 1
		m_Img_List.Add(AfxGetApp()->LoadIcon(IDI_CHILD));	// 2

		m_Grid.SetImageList(&m_Img_List);
	}

	// Recipe Header ...
	{
		CString dir_root  = sDir__ROOT_INF;
		CString file_name = sDef__Item_Header_File;

		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Header;
		p_rcp_item->iItem_Title__Width = iDef__Item_Header_Width;
		
		p_rcp_item->pGObj_Res = pGObj_Res;
		p_rcp_item->bActive__Header_Rcp = true;
		p_rcp_item->sRcp_Title = "Header";

		p_rcp_item->Upload__RCP_INFO(this->m_hWnd, dir_root,file_name);
	}
	// Recipe Step ...
	{
		CString dir_root  = sDir__ROOT_INF;
		CString file_name = sDef__Item_Step_File;

		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;
		p_rcp_item->iItem_Title__Width = iDef__Item_Step_Width;

		p_rcp_item->pGObj_Res = pGObj_Res;
		p_rcp_item->sRcp_Title = "Step";

		p_rcp_item->Upload__RCP_INFO(this->m_hWnd, dir_root,file_name);
	}
	// Recipe Tolerance ...
	{
		CString dir_root  = sDir__ROOT_INF;
		CString file_name = sDef__Item_Tolerance_File;

		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Tolerance;
		p_rcp_item->iItem_Title__Width = iDef__Item_Tolerance_Width;

		p_rcp_item->pGObj_Res = pGObj_Res;
		p_rcp_item->sRcp_Title = "Tolerance";

		p_rcp_item->Upload__RCP_INFO(this->m_hWnd, dir_root,file_name);
	}

	// List : File_Table ...
	{
		CReportCtrl *p_table = &mCtrl__File_Table;

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
		_Make__File_Table(p_table);
	}
	
	// Folder Upload ...
	{
		if(bActive__Rcp_Pre)		_Upload__Rcp_Folder(_RCP_FOLDER__PRE);
		if(bActive__Rcp_Post)		_Upload__Rcp_Folder(_RCP_FOLDER__POST);

		OnBnClickedCheck__Rcp_Folder_Main();
	}

	// ...
	{
		mCheck__Rcp_Pre.EnableWindow(bActive__Rcp_Pre);
		// mCheck__Rcp_Main.EnableWindow(bActive__Rcp_Main);
		mCheck__Rcp_Post.EnableWindow(bActive__Rcp_Post);

	}

	// ...
	{
		mCheck__Header_Type_Ctrl.EnableWindow(bActive__Item_Header);
		if(bShow__Item_Header)			mCheck__Header_Type_Ctrl.ShowWindow(SW_SHOW);
		else							mCheck__Header_Type_Ctrl.ShowWindow(SW_HIDE);
		
		mCheck__Tolerance_Type_Ctrl.EnableWindow(bActive__Item_Tolerance);
		if(bShow__Item_Tolerance)		mCheck__Tolerance_Type_Ctrl.ShowWindow(SW_SHOW);
		else							mCheck__Tolerance_Type_Ctrl.ShowWindow(SW_HIDE);

		//
		mCheck__Step_Type_Ctrl.EnableWindow(bActive__Item_Step);
		if(bShow__Item_Step)			mCheck__Step_Type_Ctrl.ShowWindow(SW_SHOW);
		else							mCheck__Step_Type_Ctrl.ShowWindow(SW_HIDE);
	
		//
		OnBnClickedBtn__File_New();
	}

	// ...
	{
		_Init__Step_Ctrl_Btn();
	}

	SetTimer(1, 500, NULL);
	return TRUE;
}

void CDlg__PROCESS_STD::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		if(m_Grid.iSel_Col > 0)
		{
			mCtrl__Step_Append.EnableWindow(TRUE);
			mCtrl__Step_Copy.EnableWindow(TRUE);
			mCtrl__Step_Move.EnableWindow(TRUE);
			mCtrl__Step_Delete.EnableWindow(TRUE);
		}
		else
		{
			mCtrl__Step_Append.EnableWindow(FALSE);
			mCtrl__Step_Copy.EnableWindow(FALSE);
			mCtrl__Step_Move.EnableWindow(FALSE);
			mCtrl__Step_Delete.EnableWindow(FALSE);
		}

		if(bActive__Rcp_item_Change)
		{
			mCtrl__File_Delete.EnableWindow(FALSE);
			mCtrl__File_New.EnableWindow(FALSE);

			mCtrl__File_Save.EnableWindow(TRUE);
			mCtrl__File_CSV.EnableWindow(FALSE);
			mCtrl__File_Undo.EnableWindow(TRUE);

			mCtrl__Send_File.EnableWindow(FALSE);
			// mCtrl__File_Table.EnableWindow(FALSE);
		}
		else
		{
			mCtrl__File_Delete.EnableWindow(TRUE);
			mCtrl__File_New.EnableWindow(TRUE);

			mCtrl__File_Save.EnableWindow(FALSE);
			mCtrl__File_CSV.EnableWindow(TRUE);
			mCtrl__File_Undo.EnableWindow(FALSE);

			mCtrl__Send_File.EnableWindow(TRUE);
			// mCtrl__File_Table.EnableWindow(TRUE);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

int CDlg__PROCESS_STD::_Init__Step_Ctrl_Btn()
{
	bActive__Rcp_item_Change = false;
	
	// ...
	{
		m_Grid.iSel_Row = -1;
		m_Grid.iSel_Col = -1;

		mCtrl__Sel_Step_ID.SetWindowText("__");
		mCtrl__Sel_Item_ID.SetWindowText("__");
	}

	if(bActive__Summary_Mode)
	{
		mCtrl__Summary_View.EnableWindow(TRUE);

		if(bActive__Summary_User)		mCtrl__Summary_Save_Check.EnableWindow(TRUE);
		else							mCtrl__Summary_Save_Check.EnableWindow(FALSE);
		mCtrl__Summary_Save_Check.SetCheck(1);
	}
	else
	{
		mCtrl__Summary_View.EnableWindow(FALSE);

		mCtrl__Summary_Save_Check.EnableWindow(FALSE);
		mCtrl__Summary_Save_Check.SetCheck(0);
	}

	// ...
	{
		mCtrl__Step_Append.EnableWindow(FALSE);
		mCtrl__Step_Copy.EnableWindow(FALSE);
		mCtrl__Step_Move.EnableWindow(FALSE);
		mCtrl__Step_Delete.EnableWindow(FALSE);
	}
	return 1;
}

void CDlg__PROCESS_STD::OnBnClickedBtn__Node_Expand()
{
	if(pCur_Rcp_Item == NULL)			return;

	CUIntArray l_row;
	pCur_Rcp_Item->Get__ITEM_CATEGORY_LIST(l_row);
	
	int i_limit = l_row.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int row = l_row[i];

		_Fnc__Grid_Expand(row,0, pCur_Rcp_Item);
	}
}
void CDlg__PROCESS_STD::OnBnClickedBtn__Node_Contract()
{
	if(pCur_Rcp_Item == NULL)			return;
	
	CUIntArray l_row;
	pCur_Rcp_Item->Get__ITEM_CATEGORY_LIST(l_row);

	int i_limit = l_row.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		int row = l_row[i];

		_Fnc__Grid_Contract(row,0, pCur_Rcp_Item);
	}
}

void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Header()
{
	pCur_Rcp_Item = &m_Rcp_Header;

	CInfo__Rcp_Item* p_rcp_item = pCur_Rcp_Item;
	_Draw__Grid_Table(p_rcp_item);

	_Change__Rcp_Type(_RCP_TYPE__HEADER);
}
void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Step()
{
	pCur_Rcp_Item = &m_Rcp_Step;

	CInfo__Rcp_Item* p_rcp_item = pCur_Rcp_Item;
	_Draw__Grid_Table(p_rcp_item);

	_Change__Rcp_Type(_RCP_TYPE__STEP);
}
void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Type_Tolerance()
{
	pCur_Rcp_Item = &m_Rcp_Tolerance;

	CInfo__Rcp_Item* p_rcp_item = pCur_Rcp_Item;
	_Draw__Grid_Table(p_rcp_item);

	_Change__Rcp_Type(_RCP_TYPE__TOLERANCE);
}

void CDlg__PROCESS_STD::_Change__Rcp_Type(const int rcp_type)
{
	mCheck__Header_Type_Ctrl.SetCheck(0);
	mCheck__Step_Type_Ctrl.SetCheck(0);
	mCheck__Tolerance_Type_Ctrl.SetCheck(0);

	if(rcp_type == _RCP_TYPE__HEADER)
	{
		pCur_Rcp_Item = &m_Rcp_Header;
		mCheck__Header_Type_Ctrl.SetCheck(1);
	}
	if(rcp_type == _RCP_TYPE__STEP)
	{
		pCur_Rcp_Item = &m_Rcp_Step;
		mCheck__Step_Type_Ctrl.SetCheck(1);
	}
	if(rcp_type == _RCP_TYPE__TOLERANCE)
	{
		pCur_Rcp_Item = &m_Rcp_Tolerance;
		mCheck__Tolerance_Type_Ctrl.SetCheck(1);
	}
}

void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Pre()
{
	int rcp_folder = _RCP_FOLDER__PRE;
	_Change__Rcp_Folder(rcp_folder);

	CString dir_sub = sDef__Rcp_Pre_Folder;
	int f_count = _Upload__File_List(dir_sub);

	CString str_data;
	str_data.Format("%1d", f_count);
	mData__Rcp_Pre_Count.SetWindowText(str_data);
}
void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Main()
{
	int rcp_folder = _RCP_FOLDER__MAIN;
	_Change__Rcp_Folder(rcp_folder);

	CString dir_sub = sDef__Rcp_Main_Folder;
	int f_count = _Upload__File_List(dir_sub);

	CString str_data;
	str_data.Format("%1d", f_count);
	mData__Rcp_Main_Count.SetWindowText(str_data);
}
void CDlg__PROCESS_STD::OnBnClickedCheck__Rcp_Folder_Post()
{
	int rcp_folder = _RCP_FOLDER__POST;
	_Change__Rcp_Folder(rcp_folder);

	CString dir_sub = sDef__Rcp_Post_Folder;
	int f_count = _Upload__File_List(dir_sub);

	CString str_data;
	str_data.Format("%1d", f_count);
	mData__Rcp_Post_Count.SetWindowText(str_data);
}
void CDlg__PROCESS_STD::_Upload__Rcp_Folder(const int rcp_folder)
{
	CString dir_sub;

	if(rcp_folder == _RCP_FOLDER__PRE)			dir_sub = sDef__Rcp_Pre_Folder;
	if(rcp_folder == _RCP_FOLDER__MAIN)			dir_sub = sDef__Rcp_Main_Folder;
	if(rcp_folder == _RCP_FOLDER__POST)			dir_sub = sDef__Rcp_Post_Folder;

	int f_count = _Upload__File_List(dir_sub);

	CString str_data;
	str_data.Format("%1d", f_count);

	if(rcp_folder == _RCP_FOLDER__PRE)			mData__Rcp_Pre_Count.SetWindowText(str_data);
	if(rcp_folder == _RCP_FOLDER__MAIN)			mData__Rcp_Main_Count.SetWindowText(str_data);
	if(rcp_folder == _RCP_FOLDER__POST)			mData__Rcp_Post_Count.SetWindowText(str_data);
}

void CDlg__PROCESS_STD::OnBnClickedBtn__File_Refresh()
{
	CString dir_sub = "";

	int rcp_folder = _Get__Rcp_Folder();
	
		 if(rcp_folder == _RCP_FOLDER__PRE)			dir_sub = sDef__Rcp_Pre_Folder;
	else if(rcp_folder == _RCP_FOLDER__MAIN)		dir_sub = sDef__Rcp_Main_Folder;
	else if(rcp_folder == _RCP_FOLDER__POST)		dir_sub = sDef__Rcp_Post_Folder;
	else											return;

	_Upload__File_List(dir_sub);
}

void CDlg__PROCESS_STD::OnNMClickList__File_Table(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int r_index = pNMItemActivate->iItem;
	if(r_index >= 0)
	{
		bool active_upload = true;

		if(bActive__Rcp_item_Change)
		{
			CString str_title;
			CString str_msg;

			str_title = "Do you want to change the file being edited ?";

			str_msg  = "There are changes.";
			str_msg += "\n";
			str_msg += "Do you want to change the file ?";
			str_msg += "\n";

			int r_flag = MessageBox(str_msg, str_title, MB_YESNO | MB_ICONINFORMATION);
			if(r_flag != IDYES)			active_upload = false;
		}

		if(active_upload)
		{
			CString str_name = _Get__Name_Of_File_Talbe(r_index);
			mData__Sel_File_Name.SetWindowText(str_name);
			mData__Sel_Folder_Name.SetWindowText(sCur__Rcp__Folder);

			CString rcp_path;
			rcp_path.Format("%s\\%s\\%s.rcp", sDir__ROOT_EQP,sCur__Rcp__Folder,str_name);
			m_Rcp_File.Upload__RCP_FILE(this->m_hWnd, rcp_path);

			_Draw__Grid_Table(pCur_Rcp_Item);
			_Init__Step_Ctrl_Btn();
		}
	}

	*pResult = 0;
}

