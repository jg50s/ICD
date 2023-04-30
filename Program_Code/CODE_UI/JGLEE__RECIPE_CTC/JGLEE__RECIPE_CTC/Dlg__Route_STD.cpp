// Dlg__Route_STD.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_STD.h"

#include "Macro_Function.h"
#include "CObj__Route_STD__KEY_DEF.h"

#include "Dlg__Route_Path_View.h"


// NEW CMMD ...
#define _NEW_CMMD__DESCRIPT						101
#define _NEW_CMMD__SCH_CFG						102

#define _NEW_CMMD__PROCESS_START    			1
#define _NEW_CMMD__PROCESS_END    				2
#define _NEW_CMMD__LLx_PROC_START    			3
#define _NEW_CMMD__LLx_PROC_END    				4
#define _NEW_CMMD__LOOPx_PROC_START    			5
#define _NEW_CMMD__LOOPx_PROC_END    			6
#define _NEW_CMMD__BMx_IN						11
#define _NEW_CMMD__BMx_OUT						12
#define _NEW_CMMD__ALx							13
#define _NEW_CMMD__STx							14

// OLD CMMD ...
#define _OLD_CMMD__DESCRIPT						101

#define _OLD_CMMD__MAIN_RCP						1
#define _OLD_CMMD__POST_RCP						2
#define _OLD_CMMD__PRE_RCP						3
#define _OLD_CMMD__BUFFER						11

// ...
#define _ROUTE_FILE_COL__NUMBER					0
#define _ROUTE_FILE_COL__FILE					1
#define _ROUTE_FILE_COL__DATE					2

// ...
#define _ROUTE_EDIT_COL__RCP_SIZE				3
#define _ROUTE_EDIT_COL__PRE_RCP				0
#define _ROUTE_EDIT_COL__MAIN_RCP				1
#define _ROUTE_EDIT_COL__POST_RCP				2

// ...
#define _ROUTE_EDIT__PMx_MAX					6
#define _ROUTE_EDIT__PATH_MAX					2

// ...
#define _PMx_RCP__NULL							"___"


// CDlg__Route_STD dialog

IMPLEMENT_DYNAMIC(CDlg__Route_STD, CDialog)

CDlg__Route_STD::CDlg__Route_STD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_STD::IDD, pParent)
{
	iShow_Count = 0;
}

CDlg__Route_STD::~CDlg__Route_STD()
{
}

void CDlg__Route_STD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST__ROUTE_FILE,  mCtrl__Route_List_Table);
	DDX_Control(pDX, IDC_BTN__FILE_NEW,     mCtrl_RouteFile_New);
	DDX_Control(pDX, IDC_BTN__FILE_UNDO,    mCtrl_RouteFile_Undo);
	DDX_Control(pDX, IDC_BTN__FILE_SAVE,    mCtrl_RouteFile_Save);
	DDX_Control(pDX, IDC_BTN__FILE_SAVEAS,  mCtrl_RouteFile_SaveAs);
	DDX_Control(pDX, IDC_BTN__FILE_DELETE,  mCtrl_RouteFile_Delete);

	DDX_Control(pDX, IDC_LIST__ROUTE_TABLE, mCtrl__Route_Edit_Table);
	DDX_Control(pDX, IDC_BTN__STx_USE, mCtrl_RouteEdit_STx_Use);

	DDX_Control(pDX, IDC_BTN__PM1_RCP, mCtrl_PM1_RCP);
	DDX_Control(pDX, IDC_BTN__PM2_RCP, mCtrl_PM2_RCP);
	DDX_Control(pDX, IDC_BTN__PM3_RCP, mCtrl_PM3_RCP);
	DDX_Control(pDX, IDC_BTN__PM4_RCP, mCtrl_PM4_RCP);
	DDX_Control(pDX, IDC_BTN__PM5_RCP, mCtrl_PM5_RCP);
	DDX_Control(pDX, IDC_BTN__PM6_RCP, mCtrl_PM6_RCP);

	DDX_Control(pDX, IDC_BTN__PMx_PRE,         mCtrl_PMx_PRE_RCP);
	DDX_Control(pDX, IDC_LIST__PMx_PRE_RCP,    mList_PMx_PRE_RCP);
	DDX_Control(pDX, IDC_BTN__PMx_MAIN,        mCtrl_PMx_MAIN_RCP);
	DDX_Control(pDX, IDC_LIST__PMx_MAIN_RCP,   mList_PMx_MAIN_RCP);
	DDX_Control(pDX, IDC_BTN__PMx_POST,        mCtrl_PMx_POST_RCP);
	DDX_Control(pDX, IDC_LIST__PMx_POST_RCP,   mList_PMx_POST_RCP);
	DDX_Control(pDX, IDC_BTN__UPDATE_ROUTE,    mCtrl_RouteFile_Update);
	DDX_Control(pDX, IDC_BTN__SEL_PMx,         mCtrl_SEL_PMx);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT_MODE, mCtrl_RouteEdit_Mode);
	DDX_Control(pDX, IDC_BTN__CUR_ROUTE, mCtrl__Current_Route_File_Name);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT_PATH_ID, mCtrl_RouteEdit_PathID);
	DDX_Control(pDX, IDC_BTN__ROUTE_FILE_SIZE, mCtrl_RouteFile_Size);
	DDX_Control(pDX, IDC_BTN__ROUTE_NAME, mCtrl_RouteEdit_FileName);
	DDX_Control(pDX, IDC_BTN__ROUTE_DATE, mCtrl_RouteEdit_FileDate);

	DDX_Text(pDX, IDC_EDIT__MAIN_MSG,  mStr_Edit__Main_Msg);
	DDX_Text(pDX, IDC_EDIT__ERROR_MSG, mStr_Edit__Error_Msg);
	DDX_Control(pDX, IDC_BTN__RCP_TYPE__DATA, mCtrl__Rcp_Type);
}


BEGIN_MESSAGE_MAP(CDlg__Route_STD, CDialog)
	ON_WM_TIMER()

	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlg__Route_STD::OnHdnItemclickList__File_List)

	ON_BN_CLICKED(IDC_BTN__UPDATE_ROUTE, &CDlg__Route_STD::OnBnClickedBtn_RouteFile_Update)
	ON_BN_CLICKED(IDC_BTN__FILE_NEW,     &CDlg__Route_STD::OnBnClickedBtn_RouteFile_New)
	ON_BN_CLICKED(IDC_BTN__FILE_UNDO,    &CDlg__Route_STD::OnBnClickedBtn_RouteFile_Undo)
	ON_BN_CLICKED(IDC_BTN__FILE_SAVE,    &CDlg__Route_STD::OnBnClickedBtn_RouteFile_Save)
	ON_BN_CLICKED(IDC_BTN__FILE_SAVEAS,  &CDlg__Route_STD::OnBnClickedBtn_RouteFile_SaveAs)
	ON_BN_CLICKED(IDC_BTN__FILE_DELETE,  &CDlg__Route_STD::OnBnClickedBtn_RouteFile_Delete)
	ON_BN_CLICKED(IDC_BTN__CUR_ROUTE,    &CDlg__Route_STD::OnBnClickedBtn_CurRoute_Update)
	
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__ROUTE_FILE, &CDlg__Route_STD::OnLvnColumnclickList_RouteTable)
	ON_NOTIFY(NM_CLICK,        IDC_LIST__ROUTE_FILE, &CDlg__Route_STD::OnNMClickList_RouteTable)
	ON_NOTIFY(NM_DBLCLK,       IDC_LIST__ROUTE_FILE, &CDlg__Route_STD::OnNMDblclkList_RouteTable)

	ON_BN_CLICKED(IDC_BTN__ROUTE_EDIT_MODE,   &CDlg__Route_STD::OnBnClickedBtn_RouteEdit_Mode)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST__ROUTE_TABLE, &CDlg__Route_STD::OnLvnColumnclickList_RouteEdit)
	ON_NOTIFY(NM_CLICK,        IDC_LIST__ROUTE_TABLE, &CDlg__Route_STD::OnNMClickList_RouteEdit)
	ON_NOTIFY(NM_DBLCLK,       IDC_LIST__ROUTE_TABLE, &CDlg__Route_STD::OnNMDblclkList_RouteEdit)	

	ON_BN_CLICKED(IDC_BTN__STx_USE,   &CDlg__Route_STD::OnBnClickedBtn_RouteEdit_STx_Use)
	ON_BN_CLICKED(IDC_BTN__PATH_VIEW, &CDlg__Route_STD::OnBnClickedBtn_PathView)

	ON_BN_CLICKED(IDC_BTN__PM1_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM1_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PM2_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM2_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PM3_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM3_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PM4_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM4_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PM5_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM5_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PM6_RCP,  &CDlg__Route_STD::OnBnClickedBtn_PM6_RCP_Update)
	ON_BN_CLICKED(IDC_BTN__PMx_PRE,  &CDlg__Route_STD::OnBnClickedBtn_PMx_PRE_Update)
	ON_BN_CLICKED(IDC_BTN__PMx_MAIN, &CDlg__Route_STD::OnBnClickedBtn_PMx_MAIN_Update)
	ON_BN_CLICKED(IDC_BTN__PMx_POST, &CDlg__Route_STD::OnBnClickedBtn_PMx_POST_Update)

	ON_LBN_SELCHANGE(IDC_LIST__PMx_PRE_RCP,  &CDlg__Route_STD::OnLbnSelchangeList_PreRCP )
	ON_LBN_SELCHANGE(IDC_LIST__PMx_MAIN_RCP, &CDlg__Route_STD::OnLbnSelchangeList_MainRCP)
	ON_LBN_SELCHANGE(IDC_LIST__PMx_POST_RCP, &CDlg__Route_STD::OnLbnSelchangeList_PostRCP)

END_MESSAGE_MAP()


// CDlg__Route_STD message handlers

BOOL CDlg__Route_STD::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ...
	{
		mCtrl__Current_Route_File_Name.SetWindowText("");
		mCtrl_RouteFile_Size.SetWindowText("");

		mCtrl_SEL_PMx.SetWindowText("");

		mCtrl_RouteEdit_FileName.SetWindowText("");
		mCtrl_RouteEdit_FileDate.SetWindowText("");
	}

	Msg_OnInitDialog();
	
	Update__RouteFile_List();
	Set__Route_Edit_Mode(FALSE);

	Fnc_OnInitDialog();

	m_bResultDirect = TRUE;

	SetTimer(1, 500, NULL);
	return TRUE;
}
BOOL CDlg__Route_STD::Msg_OnInitDialog()
{
	// iPMx_SIZE = 4;

	// Route List Table ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl *p_table = &mCtrl__Route_List_Table;
		CImageList *p_img  = &mImg__Route_List_Table;

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);

		Make__Route_List_Table();
	}
	// Route Edit Table ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl* p_table = &mCtrl__Route_Edit_Table;
		CImageList *p_img  = &mImg__Route_Edit_Table;

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		p_table->SetExtendedStyle(list_view_stype);

		Make__Route_Edit_Table();
		Init__Route_Edit_Table();
	}

	// ...
	{
		mCtrl_RouteFile_New.Init_Resource(this, NULL);
		mCtrl_RouteFile_Undo.Init_Resource(this, NULL);
		mCtrl_RouteFile_Save.Init_Resource(this, NULL);
		mCtrl_RouteFile_SaveAs.Init_Resource(this, NULL);
		mCtrl_RouteFile_Delete.Init_Resource(this, NULL);

		bActive__Recipe_Changed = FALSE;

		Set__Route_Edit_Mode(FALSE);
	}

	return TRUE;
}
BOOL CDlg__Route_STD::Fnc_OnInitDialog()
{
	Update__RouteFile_List();	
	Click__PMx_RCP(0);
	
	return TRUE;
}

void CDlg__Route_STD::OnTimer(UINT nIDEvent)
{
	static int pre_state = 0;

	if(bActive__Recipe_Changed)
	{
		if(pre_state <= 0)
		{
			pre_state = 1;

			mCtrl_RouteFile_New.Draw__Disable_State();
			mCtrl_RouteFile_Delete.Draw__Disable_State();

			mCtrl_RouteFile_Undo.Draw__Up_State();
			mCtrl_RouteFile_Save.Draw__Active_State();
			mCtrl_RouteFile_SaveAs.Draw__Active_State();
		}
	}
	else
	{
		if(pre_state >= 0)
		{
			pre_state = -1;

			mCtrl_RouteFile_New.Draw__Up_State();
			mCtrl_RouteFile_Undo.Draw__Up_State();
			mCtrl_RouteFile_SaveAs.Draw__Up_State();
			mCtrl_RouteFile_Delete.Draw__Up_State();

			mCtrl_RouteFile_Save.Draw__Disable_State();
		}
	}
}

// ...
int CDlg__Route_STD
::Set_Parameter(const int module_id)
{
	CString dir_sub;
	CString var_data;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_PMx_SIZE, var_data);
	iPMx_SIZE = atoi(var_data);
	if(iPMx_SIZE > _ROUTE_EDIT__PMx_MAX)
		iPMx_SIZE = _ROUTE_EDIT__PMx_MAX;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_DIR_PRE,  dir_sub);
	sRCP__DIR_PRE = dir_sub;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_DIR_MAIN, dir_sub);
	sRCP__DIR_MAIN = dir_sub;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_DIR_POST, dir_sub);
	sRCP__DIR_POST = dir_sub;

	//
	for(int i=0; i<_ROUTE_EDIT__PMx_MAX; i++)
	{
		sPMx_NAME[i].Format("PM%1d", i+1);
	}
	return 1;
}

// ...
int CDlg__Route_STD
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	// ...
	{
		mCtrl_RouteFile_New.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mCtrl_RouteFile_Undo.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mCtrl_RouteFile_Save.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mCtrl_RouteFile_SaveAs.Set_Position(&wndTop, SWP_SHOWWINDOW);
		mCtrl_RouteFile_Delete.Set_Position(&wndTop, SWP_SHOWWINDOW);
	}

	// ...
	{
		mCtrl_RouteFile_New.Draw__Buttn_State();
		mCtrl_RouteFile_Undo.Draw__Buttn_State();
		mCtrl_RouteFile_Save.Draw__Buttn_State();
		mCtrl_RouteFile_SaveAs.Draw__Buttn_State();
		mCtrl_RouteFile_Delete.Draw__Buttn_State();
	}

	// ...
	{
		bool active_check = true;

		while((iShow_Count < 2) || (active_check))
		{
			iShow_Count++;
			active_check = false;

			//
			CString key_name;
			CString str_data;

			for(int i=0; i<_ROUTE_EDIT__PMx_MAX; i++)
			{
				key_name.Format(pKEY__CH_CFG_NAME_PM_X, i+1);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, str_data);

				if(str_data.GetLength() > 0)		sPMx_NAME[i] = str_data;
				else								sPMx_NAME[i].Format("PM%1d", i+1);
			}
		}

		// ...
		{
			CListCtrl *p_table = &mCtrl__Route_Edit_Table;

			for(int i=1; i<=iPMx_SIZE; i++)
			{
				char ch_data[256];
				strcpy(ch_data, sPMx_NAME[i-1]);

				LV_COLUMN c;
				c.mask = LVCF_TEXT;
				c.pszText = ch_data;

				p_table->SetColumn(i, &c);
			}
		}
		// ...
		{
			CButton *p_ctrl;

			for(int i=0; i<iPMx_SIZE; i++)
			{
					 if(i == 0)			p_ctrl = &mCtrl_PM1_RCP;
				else if(i == 1)			p_ctrl = &mCtrl_PM2_RCP;
				else if(i == 2)			p_ctrl = &mCtrl_PM3_RCP;
				else if(i == 3)			p_ctrl = &mCtrl_PM4_RCP;
				else if(i == 4)			p_ctrl = &mCtrl_PM5_RCP;
				else if(i == 5)			p_ctrl = &mCtrl_PM6_RCP;
				else					continue;

				p_ctrl->SetWindowText(sPMx_NAME[i]);
			}
		}
	}

	MoveWindow(sx,sy,wx,wy,true);
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__Route_STD
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}

// ...
void CDlg__Route_STD
::Make__Route_List_Table()
{
	CListCtrl *p_table = &mCtrl__Route_List_Table;

	// ...
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
			if(i == _ROUTE_FILE_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(60);
			}
			else if(i == _ROUTE_FILE_COL__FILE)
			{
				l__col_name.Add("Route Recipe");
				l__col_width.Add(180);
			}
			else if(i == _ROUTE_FILE_COL__DATE)
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

void CDlg__Route_STD
::Make__Route_Edit_Table()
{
	CListCtrl *p_table = &mCtrl__Route_Edit_Table;

	// ...
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		CString str__col_name;

		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		CRect rc_win;
		p_table->GetWindowRect(&rc_win);
		int db_width = rc_win.Width();

		int width_path = 60;
		int width_step = 130;

		if(iPMx_SIZE < 5)
		{
			width_path = 100;
			width_step = 190;
		}

		int i_limit = iPMx_SIZE;
		int i;

		for(i=0; i<=i_limit; i++)
		{
			if(i == 0)
			{
				str__col_name = "PATH";

				l__col_name.Add(str__col_name);
				l__col_width.Add(width_path);
			}
			else 
			{
				// str__col_name.Format("PM%1d", i);
				str__col_name = sPMx_NAME[i-1];

				l__col_name.Add(str__col_name);
				l__col_width.Add(width_step);
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
void CDlg__Route_STD
::Init__Route_Edit_Table()
{
	CListCtrl *p_table = &mCtrl__Route_Edit_Table;
	p_table->DeleteAllItems();
	
	mCtrl_RouteEdit_PathID.SetWindowText("__");
	mCtrl_RouteEdit_STx_Use.SetWindowText("NO");

	// ...
	CString str_item;

	int i_limit = _ROUTE_EDIT__PMx_MAX;
	int i;

	int k_limit = _ROUTE_EDIT__PMx_MAX;
	int k;

	for(i=0;i<i_limit;i++)
	{
		for(k=0; k<=k_limit; k++)
		{
			if(k == 0)
			{
				int step_id = (i / _ROUTE_EDIT_COL__RCP_SIZE) + 1;
				int rcp_id  = (i % _ROUTE_EDIT_COL__RCP_SIZE);

				switch(rcp_id)
				{
					case _ROUTE_EDIT_COL__PRE_RCP:
						str_item.Format("%1d_Pre",  step_id);			
						break;
					case _ROUTE_EDIT_COL__MAIN_RCP:
						str_item.Format("%1d_Main", step_id);			
						break;
					case _ROUTE_EDIT_COL__POST_RCP:
						str_item.Format("%1d_Post", step_id);			
						break;

					default:		
						str_item.Format("%1d_%s", step_id,rcp_id);		
						break;
				}
			}
			else
			{
				str_item = _PMx_RCP__NULL;
			}

			if(k == 0)		p_table->InsertItem(i, str_item, 0);
			else			p_table->SetItem(i,k, LVIF_TEXT,str_item,0,0,0,0);
		}
	}
}
void CDlg__Route_STD
::Update__Route_Edit_Table(CListCtrl *p_table,
						   CStringArray* p_module_list[], 
						   CStringArray* p_recipe_list[],
						   const int step_count,
						   const int col_id)
{
	int i_limit = step_count;
	int i;

	for(i=0;i<i_limit;i++)
	{
		int k_limit = p_module_list[i]->GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString pmx_name = (*p_module_list)[i][k];
			CString rcp_name = (*p_recipe_list)[i][k];
			
			if(rcp_name == "")		
				rcp_name = _PMx_RCP__NULL;

			Change__Route_Edit_Table(p_table, pmx_name,rcp_name, i,col_id);
		}
	}
}
void CDlg__Route_STD
::Change__Route_Edit_Table(CListCtrl *p_table,
						   const CString& pmx_name,
						   const CString& rcp_name,
						   const int path_index,
						   const int col_id)
{
	int pmx_id = 0;

		 if(pmx_name.CompareNoCase("PM1") == 0)			pmx_id = 1;
	else if(pmx_name.CompareNoCase("PM2") == 0)			pmx_id = 2;
	else if(pmx_name.CompareNoCase("PM3") == 0)			pmx_id = 3;
	else if(pmx_name.CompareNoCase("PM4") == 0)			pmx_id = 4;
	else if(pmx_name.CompareNoCase("PM5") == 0)			pmx_id = 5;
	else if(pmx_name.CompareNoCase("PM6") == 0)			pmx_id = 6;
	else												return;

	int pos_x = (path_index * _ROUTE_EDIT_COL__RCP_SIZE) + col_id;
	int pos_y = pmx_id;

	p_table->SetItem(pos_x, pos_y, LVIF_TEXT, rcp_name, 0,0,0,0);
}

// Route Table ...
void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_Update()
{
	Update__RouteFile_List();	
}
void CDlg__Route_STD
::Update__RouteFile_List()
{
	CString s_date;

	Update__RouteFile_List("", s_date);
}
void CDlg__Route_STD
::Update__RouteFile_List(const CString& s_name,CString& s_date)
{
	CStringArray l_file;
	CStringArray l_date;

	CString dir_doot = "";
	CString dir_sub  = "ROUTE";
	CString file_ext = "rte";

	// ...
	{		
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = 0;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_doot);
	}
	
	// ...
	CString dir_proc;
	dir_proc.Format("%s\\%s", dir_doot,dir_sub);
	
	MACRO__Get_File_List(dir_proc,file_ext, l_file,l_date);

	sList__RouteFile_Name.Copy(l_file);
	sList__RouteFile_Date.Copy(l_date);

	m_bResultDirect = FALSE;
	Update__RouteFile_List(s_name,s_date, l_file,l_date);

}
void CDlg__Route_STD::
Update__RouteFile_List(const CString& s_name,
					   CString& s_date, 
					   const CStringArray& l_file,
					   const CStringArray& l_date)
{
	CListCtrl *p_table = &mCtrl__Route_List_Table;
	p_table->DeleteAllItems();

	int s_check = -1;
	CString str_count;
	CString file_name;
	CString file_date;

	int i_limit = l_file.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_count.Format("%1d", i+1);
		file_name = l_file[i];
		file_date = l_date[i];

		if(s_check < 0)
		{
			if(s_name.GetLength() > 0)
			{
				if(s_name.CompareNoCase(file_name) == 0)
				{
					s_date  = file_date;
					s_check = 1;
				}
			}
		}

		p_table->InsertItem(i, str_count, 0);
		p_table->SetItem(i, _ROUTE_FILE_COL__FILE, LVIF_TEXT, file_name, 0,0,0,0);
		p_table->SetItem(i, _ROUTE_FILE_COL__DATE, LVIF_TEXT, file_date, 0,0,0,0);
	}

	str_count.Format("%02d", i_limit);
	mCtrl_RouteFile_Size.SetWindowText(str_count);

	UpdateData(FALSE);
}

// ...
void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_New()
{
	if(mCtrl_RouteFile_New.Is_Disable() > 0)	
		return;

	// ...
	CString str_title;
	CString str_msg;

	if(bActive__Recipe_Changed)
	{
		str_title = "New File을 만들까요?";

		str_msg  = "변경된 내용이 있습니다.";
		str_msg += "\n";
		str_msg += "무시하고 진행할까요?";
	}
	else
	{
		str_title = "New File을 만들까요?";

		str_msg = "\"YES\"를 선택하면, 진행됩니다.";
	}

	int id_msg = MessageBox(str_msg, str_title, MB_YESNO);
	if(id_msg == IDYES)
	{
		mCtrl__Current_Route_File_Name.SetWindowText("");

		Undo__Route_File("", "");
	}
}
void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_Undo()
{
	CString str_title;
	CString str_msg;

	if(bActive__Recipe_Changed)
	{
		str_title = "Undo를 진행할까요?";

		str_msg  = "변경된 내용이 있습니다.";
		str_msg += "\n";
		str_msg += "무시하고 진행할까요?";
	}
	else
	{
		str_title = "Undo를 진행할까요?";

		str_msg = "\"YES\"를 선택하면, 진행됩니다.";
	}	

	int id_msg = MessageBox(str_msg, str_title, MB_YESNO);
	if(id_msg == IDYES)
	{
		CString file_name;
		mCtrl__Current_Route_File_Name.GetWindowText(file_name);

		Undo__Route_File(file_name, mStr__Current_Route_File_Date);
	}
}

void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_Save()
{
	UpdateData(TRUE);

	CString file_name;
	mCtrl_RouteEdit_FileName.GetWindowText(file_name);

	// ...
	{
		CString str_title;
		CString str_msg;

		str_title = "Save를 진행할까요?";

		str_msg.Format("File \"%s\"를 저장할까요?", file_name);
		str_msg += "\"YES\"를 선택하면, 진행됩니다.";

		int id_msg = MessageBox(str_msg, str_title, MB_YESNO);
		if(id_msg != IDYES)
		{
			return;
		}

		// ...
		mCtrl_RouteEdit_FileName.GetWindowText(file_name);	

		while(file_name.GetLength() < 1)
		{
			CString str_title = "File Name을 입력하세요.";

			UIX__STRING_PAD_CTRL x_pad_ctrl;
			if(x_pad_ctrl->Popup(str_title, file_name, file_name)  < 0)
			{
				return;
			}
		}							
	}

	if(Save_RouteFile(file_name) > 0)
	{
		Init_RouteFile(file_name);
	}
}
void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_SaveAs()
{
	CString file_name = "";

	while(file_name.GetLength() < 1)
	{
		CString str_title;

		str_title = "저장할 File 이름을 입력하세요.";

		mCtrl_RouteEdit_FileName.GetWindowText(file_name);	

		UIX__STRING_PAD_CTRL x_pad_ctrl;
		if(x_pad_ctrl->Popup(str_title, file_name, file_name)  < 0)
		{
			return;
		}
	}

	if(Save_RouteFile(file_name) > 0)
	{
		Init_RouteFile(file_name);
	}
}
int  CDlg__Route_STD
:: Save_RouteFile(const CString& file_name)
{
	CString file_path;
	CString dir_root;
	CString dir_sub  = "ROUTE";
	CString file_ext = "rte";

	// ...
	{	
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = 0;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	if(Check__RouteEdit_FileData() < 0)
	{
		return -1;
	}

	if(!bRCP_TYPE__NEW)
	{
		bRCP_TYPE__NEW = TRUE;
		bSCH_TYPE__CONFIG = TRUE;

		mCtrl__Rcp_Type.SetWindowText("CONFIG");
	}

	file_path.Format("%s\\%s\\%s.%s", dir_root,dir_sub,file_name,file_ext);
	printf("File_Path : [%s] \n", file_path);

	CString file_data = Get__RouteEdit_FileData();
	printf(" * RouteEdit_FileData() ... \n");
	printf(file_data);

	if(MACRO__Save_File_Data(file_path, file_data) < 0)
	{
		printf(" * File_Save Error : [%s] \n", file_path);
		return -1;
	}

	bActive__Recipe_Changed = FALSE;
	return 1;
}
void CDlg__Route_STD
::Init_RouteFile(const CString& file_name)
{
	CString s_date = "???";
	Update__RouteFile_List(file_name, s_date);

	mCtrl__Current_Route_File_Name.SetWindowText(file_name);
	mCtrl_RouteEdit_FileName.SetWindowText(file_name);	
	mCtrl_RouteEdit_FileDate.SetWindowText(s_date);

	// ...
	int c_index = _ROUTE_FILE_COL__FILE;

	int i_limit = mCtrl__Route_List_Table.GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString chk_name = mCtrl__Route_List_Table.GetItemText(i, c_index);

		printf(" * %1d) file_name : [%s] \n", i,chk_name);

		if(chk_name.CompareNoCase(file_name) != 0)
		{
			continue;
		}

		printf(" * Route_List_Table Index : [%1d] \n", i);

		mCtrl__Route_List_Table.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
		mCtrl__Route_List_Table.EnsureVisible(i, FALSE);
		mCtrl__Route_List_Table.SetFocus();
		break;
	}

	UpdateData(FALSE);
}

void CDlg__Route_STD
::OnBnClickedBtn_RouteFile_Delete()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_RouteFile_Delete() ... \n");

	// ...
	CString file_path;
	CString dir_root;
	CString dir_sub  = "ROUTE";
	CString file_ext = "rte";

	// ...
	{	
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = 0;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	// ...
	CString file_name;
	mCtrl__Current_Route_File_Name.GetWindowText(file_name);

	file_path.Format("%s\\%s\\%s.%s", dir_root,dir_sub,file_name,file_ext);
	printf(" * Delete File_Path : [%s] \n", file_path);

	// ...
	{
		CString str_title;
		CString str_msg;

		str_title = "선택된 파일을 삭제 하겠습니다.";

		str_msg.Format("File \"%s\"를 삭제할까요? ", file_name);

		int id_msg = MessageBox(str_msg, str_title, MB_YESNO);
		if(id_msg == IDYES)
		{
			MACRO__Delete_File(file_path);

			mCtrl__Current_Route_File_Name.SetWindowText("");
			Undo__Route_File("", "", FALSE);
			
			Update__RouteFile_List();	
		}							
	}
}

int CDlg__Route_STD::
Get__RouteEdit__Process_Path(CStringArray *pl__pmx_name,
							 CStringArray *pl__rcp_pre,
							 CStringArray *pl__rcp_main,
							 CStringArray *pl__rcp_post)
{
	int st_limit = _ROUTE_EDIT__PATH_MAX;
	int st;

	for(st=0; st<st_limit; st++)
	{
		int k_limit = _ROUTE_EDIT__PMx_MAX;
		int k;

		for(k=1; k<=k_limit; k++)
		{
			CString pmx_name = "";
			CString rcp_pre  = "";
			CString rcp_main = "";
			CString rcp_post = "";

			// ...
			int r_pre  = _ROUTE_EDIT_COL__PRE_RCP  + (st * _ROUTE_EDIT_COL__RCP_SIZE);
			int r_main = _ROUTE_EDIT_COL__MAIN_RCP + (st * _ROUTE_EDIT_COL__RCP_SIZE);
			int r_post = _ROUTE_EDIT_COL__POST_RCP + (st * _ROUTE_EDIT_COL__RCP_SIZE);

			int i_limit = mCtrl__Route_Edit_Table.GetItemCount();
			int i;

			for(i=0; i<i_limit; i++)
			{
					 if(i == r_pre)			;
				else if(i == r_main)		;
				else if(i == r_post)		;
				else					continue;

				CString rcp_name = mCtrl__Route_Edit_Table.GetItemText(i, k);

				if(rcp_name == "")					continue;
				if(rcp_name == _PMx_RCP__NULL)		continue;;

					 if(i == r_pre)			rcp_pre  = rcp_name;
				else if(i == r_main)		rcp_main = rcp_name;
				else if(i == r_post)		rcp_post = rcp_name;
			}

			if(rcp_main.GetLength() < 1)
			{
				continue;
			}

			//
			pmx_name.Format("PM%1d", k);
			pl__pmx_name[st].Add(pmx_name);

			pl__rcp_pre[st].Add(rcp_pre);
			pl__rcp_main[st].Add(rcp_main);
			pl__rcp_post[st].Add(rcp_post);
		}
	}

	return 1;
}
int CDlg__Route_STD::
Update__RouteEdit__STx_To_DB()
{
	if(bSCH_TYPE__CONFIG)
	{
		mDB__STx.Init_DB();

		// ...
		CString str_data;
		mCtrl_RouteEdit_STx_Use.GetWindowText(str_data);

		if(str_data.CompareNoCase("YES") == 0)
		{
			mDB__STx.sTitle = "STx";

			//
			_DB_Info__Module db_md;

			db_md.sTitle = "x";
			db_md.sList_Para.Add("CFG");
			db_md.sList_Para.Add("CFG");
			db_md.sList_Para.Add("CFG");

			mDB__STx.Load__Module_Info(db_md);
		}
	}

	return 1;
}

CString CDlg__Route_STD::Get__RouteEdit_FileData()
{
	UpdateData(TRUE);

	// ...
	CString str_data = "";
	CString str_bff;

	// ROUTE TYPE ...
	{
		str_data += "#ROUTE_EDIT#";
		str_data += "\n";
	}
	// SCHEDULER_MODE ...
	if(bSCH_TYPE__CONFIG)
	{
		str_data += "#SCH_CFG#";
		str_data += "\n";
	}
	// Description ...
	{
		str_data += "#DESCRIPT#,;";
		str_data += "\n";
	}

	// ALx ...
	{
		_DB_Info__Category *p_db = &mDB__ALx;

		int i_limit = p_db->Get__Module_Size();
		int i;

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

			// ...
			CString md_id = p_info->sTitle;
			CString para_1 = "";
			CString para_2 = "";

			for(int t=0; t<2; t++)
			{
				CString para_data = "";

				if(t < p_info->sList_Para.GetSize())
					para_data = p_info->sList_Para[t];

					 if(t == 0)		para_1 = para_data;
				else if(t == 1)		para_2 = para_data;
			}

			str_bff.Format("#ALx#,%s,%s,%s;\n", md_id,para_1,para_2);							
			str_data += str_bff;
		}
	}
	// LLx_IN ...
	{
		_DB_Info__Category *p_db = &mDB__LLx_IN;

		int i_limit = p_db->Get__Module_Size();
		int i;

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

			// ...
			CString md_id = p_info->sTitle;
			CString para_1 = "";
			CString para_2 = "";

			for(int t=0; t<2; t++)
			{
				CString para_data = "";

				if(t < p_info->sList_Para.GetSize())
					para_data = p_info->sList_Para[t];

					 if(t == 0)		para_1 = para_data;
				else if(t == 1)		para_2 = para_data;
			}

			str_bff.Format("#LLx_IN#,%s,%s,%s;\n", md_id,para_1,para_2);							
			str_data += str_bff;
		}
	}

	// PROCESS_PATH ...
	{
		CStringArray l__pmx_name[_ROUTE_EDIT__PATH_MAX];
		CStringArray l__rcp_pre[_ROUTE_EDIT__PATH_MAX];
		CStringArray l__rcp_main[_ROUTE_EDIT__PATH_MAX];
		CStringArray l__rcp_post[_ROUTE_EDIT__PATH_MAX];

		Get__RouteEdit__Process_Path(l__pmx_name,l__rcp_pre,l__rcp_main,l__rcp_post);

		// ...
		int st_limit = _ROUTE_EDIT__PATH_MAX;
		int st;

		for(st=0; st<st_limit; st++)
		{
			if(l__pmx_name[st].GetSize() < 1)
			{
				continue;
			}

			str_data += "#PROCESS_START#";
			str_data += "\n";

			// ...
			{
				int i_limit = l__pmx_name[st].GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					CString pmx_name = l__pmx_name[st].GetAt(i);
					CString rcp_pre  = l__rcp_pre[st].GetAt(i);
					CString rcp_main = l__rcp_main[st].GetAt(i);
					CString rcp_post = l__rcp_post[st].GetAt(i);

					if(rcp_main.GetLength() < 1)
					{
						continue;
					}

					str_bff.Format("%s,%s,%s,%s;\n", pmx_name,rcp_pre,rcp_main,rcp_post);
					str_data += str_bff;
				}
			}

			str_data += "#PROCESS_END#";
			str_data += "\n";
		}
	}
	// LLx_PRC ...
	{
		_DB_Info__Category *p_db = &mDB__LLx_PRC;

		int i_limit = p_db->Get__Module_Size();
		int i;

		if(i_limit > 0)
		{
			str_bff += "#LLx_PROC_START#";
			str_bff += "\n";
		}

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

			// ...
			CString md_id = p_info->sTitle;
			CString para_1 = "";
			CString para_2 = "";
			CString para_3 = "";

			for(int t=0; t<3; t++)
			{
				CString para_data = "";

				if(t < p_info->sList_Para.GetSize())
					para_data = p_info->sList_Para[t];

					 if(t == 0)		para_1 = para_data;
				else if(t == 1)		para_2 = para_data;
				else if(t == 2)		para_3 = para_data;
			}

			str_bff.Format("LL%s,%s,%s,%s;\n", md_id,para_1,para_2,para_3);
			str_data += str_bff;
		}

		if(i_limit > 0)
		{
			str_bff += "#LLx_PROC_END#";
			str_bff += "\n";
		}
	}
	// LOOPx_PRC ...
	{
		_DB_Info__Category *p_db = &mDB__LOOPx_PRC;

		int i_limit = p_db->Get__Module_Size();
		int i;

		if(i_limit > 0)
		{
			str_bff += "#LOOPx_PROC_START#";
			str_bff += "\n";
		}

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

			// ...
			CString md_id = p_info->sTitle;
			CString para_1 = "";

			for(int t=0; t<3; t++)
			{
				CString para_data = "";

				if(t < p_info->sList_Para.GetSize())
					para_data = p_info->sList_Para[t];

				if(t == 0)		para_1 = para_data;
			}

			// LOOP1,5;
			str_bff.Format("LOOP%s,%s;\n", md_id,para_1);
			str_data += str_bff;
		}

		if(i_limit > 0)
		{
			str_bff += "#LOOPx_PROC_END#";
			str_bff += "\n";
		}
	}

	// LLx_OUT ...
	{
		_DB_Info__Category *p_db = &mDB__LLx_OUT;

		int i_limit = p_db->Get__Module_Size();
		int i;

		for(i=0; i<i_limit; i++)
		{
			_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

			// ...
			CString md_id = p_info->sTitle;
			CString para_1 = "";
			CString para_2 = "";

			for(int t=0; t<2; t++)
			{
				CString para_data = "";

				if(t < p_info->sList_Para.GetSize())
					para_data = p_info->sList_Para[t];

					 if(t == 0)		para_1 = para_data;
				else if(t == 1)		para_2 = para_data;
			}

			str_bff.Format("#LLx_OUT#,%s,%s,%s;\n", md_id,para_1,para_2);							
			str_data += str_bff;
		}
	}
	// STx ...
	{
		Update__RouteEdit__STx_To_DB();

		// ...
		{
			_DB_Info__Category *p_db = &mDB__STx;

			int i_limit = p_db->Get__Module_Size();
			int i;

			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_info = p_db->Get__Module_Info(i);

				// ...
				CString md_id = p_info->sTitle;
				CString para_1 = "";
				CString para_2 = "";
				CString para_3 = "";

				for(int t=0; t<3; t++)
				{
					CString para_data = "";

					if(t < p_info->sList_Para.GetSize())
						para_data = p_info->sList_Para[t];

						 if(t == 0)		para_1 = para_data;
					else if(t == 1)		para_2 = para_data;
					else if(t == 2)		para_3 = para_data;
				}

				str_bff.Format("#STx#,%s,%s,%s,%s;\n", md_id,para_1,para_2,para_3);
				str_data += str_bff;
			}
		}
	}
	
	return str_data;
}
int CDlg__Route_STD::Check__RouteEdit_FileData()
{
	CStringArray l_main_pmx[_ROUTE_EDIT__PATH_MAX];
	CStringArray l_pre_pmx[_ROUTE_EDIT__PATH_MAX];
	CStringArray l_post_pmx[_ROUTE_EDIT__PATH_MAX];

	// ...
	CString pmx_name;

	int i_limit = mCtrl__Route_Edit_Table.GetItemCount();
	int i;

	// MAIN_RCP ...
	{
		int id_step1 = _ROUTE_EDIT_COL__MAIN_RCP;
		int id_step2 = id_step1 + _ROUTE_EDIT_COL__RCP_SIZE;

		for(i=0; i<i_limit; i++)
		{
			int path_i = -1;

				 if(i == id_step1)		path_i = 0;
			else if(i == id_step2)		path_i = 1;
			else						continue;
			
			// ...
			int k_limit = _ROUTE_EDIT__PMx_MAX;
			int k;

			for(k=1; k<=k_limit; k++)
			{
				CString rcp_name = mCtrl__Route_Edit_Table.GetItemText(i, k);

				if(rcp_name == "")					continue;
				if(rcp_name == _PMx_RCP__NULL)		continue;;

				pmx_name.Format("PM%1d", k);
				l_main_pmx[path_i].Add(pmx_name);
			}
		}
	}
	// POST_RCP ...
	{
		int id_step1 = _ROUTE_EDIT_COL__POST_RCP;
		int id_step2 = id_step1 + _ROUTE_EDIT_COL__RCP_SIZE;

		for(i=0; i<i_limit; i++)
		{
			int path_i = -1;

				 if(i == id_step1)		path_i = 0;
			else if(i == id_step2)		path_i = 1;
			else						continue;

			// ...
			int k_limit = _ROUTE_EDIT__PMx_MAX;
			int k;

			for(k=1; k<=k_limit; k++)
			{
				CString rcp_name = mCtrl__Route_Edit_Table.GetItemText(i, k);

				if(rcp_name == "")					continue;
				if(rcp_name == _PMx_RCP__NULL)		continue;;

				pmx_name.Format("PM%1d", k);
				l_post_pmx[path_i].Add(pmx_name);
			}
		}
	}
	// PRE_RCP ...
	{
		int id_step1 = _ROUTE_EDIT_COL__PRE_RCP;
		int id_step2 = id_step1 + _ROUTE_EDIT_COL__RCP_SIZE;

		for(i=0; i<i_limit; i++)
		{
			int path_i = -1;

				 if(i == id_step1)		path_i = 0;
			else if(i == id_step2)		path_i = 1;
			else						continue;

			// ...
			int k_limit = _ROUTE_EDIT__PMx_MAX;
			int k;

			for(k=1; k<=k_limit; k++)
			{
				CString rcp_name = mCtrl__Route_Edit_Table.GetItemText(i, k);

				if(rcp_name == "")					continue;
				if(rcp_name == _PMx_RCP__NULL)		continue;;

				pmx_name.Format("PM%1d", k);
				l_pre_pmx[path_i].Add(pmx_name);
			}
		}
	}

	// ...
	CString err_msg = "";

	// Check - Path1에 Main Module이 없음 ...
	{
		// Path_1
		if(l_main_pmx[0].GetSize() < 1)
		{
			// Error
			err_msg.Format("Error(1) : Path1에 등록된 Main Recipe가 없습니다.");
			printf(" * %s \n", err_msg);

			mStr_Edit__Error_Msg = err_msg;

			MessageBox(err_msg, "Route Recipe Error !", MB_ICONERROR);

			UpdateData(FALSE);
			return -1;
		}
	}
	// Check - Main Module 중복 ...
	{
		// Path_1
		i_limit = l_main_pmx[0].GetSize();

		for(i=0; i<i_limit; i++)
		{
			pmx_name = l_main_pmx[0].GetAt(i);

			// Path_2
			int k_limit = l_main_pmx[1].GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				CString chk_pmx = l_main_pmx[1].GetAt(k);

				if(pmx_name.CompareNoCase(chk_pmx) != 0)
				{
					continue;
				}

				// Error
				err_msg.Format("Error(2) : Path1 (%s) -> Path2 (%s) 중복 ...", pmx_name,chk_pmx);
				printf(" * %s \n", err_msg);

				mStr_Edit__Error_Msg = err_msg;

				MessageBox(err_msg, "Route Recipe Error !", MB_ICONERROR);

				UpdateData(FALSE);
				return -1;
			}
		}
	}
	// Check - Main Module 유무 검사 ...
	{
		i_limit = _ROUTE_EDIT__PATH_MAX;

		for(i=0; i<i_limit; i++)
		{
			int k_limit;
			int k;

			// Pre Check ...
			{
				k_limit = l_pre_pmx[i].GetSize();

				for(k=0; k<k_limit; k++)
				{
					CString pmx_check = l_pre_pmx[i].GetAt(k);

					if(Check__Module_Name(pmx_check, l_main_pmx[i]) < 0)
					{
						// Error
						err_msg.Format("Error(11) : Path%1d의 Post_PMx와 관련된 Main PMx(%s)의 등록된 Recipe가 없습니다. ", i+1,pmx_check);
						printf(" * %s \n", err_msg);

						mStr_Edit__Error_Msg = err_msg;
						
						MessageBox(err_msg, "Route Recipe Error !", MB_ICONERROR);

						UpdateData(FALSE);
						return -11;
					}
				}
			}
			// Post Check ...
			{
				k_limit = l_post_pmx[i].GetSize();

				for(k=0; k<k_limit; k++)
				{
					CString pmx_check = l_post_pmx[i].GetAt(k);

					if(Check__Module_Name(pmx_check, l_main_pmx[i]) < 0)
					{
						// Error
						err_msg.Format("Error(21) : Path%1d의 Post_PMx와 관련된 Main PMx(%s)의 등록된 Recipe가 없습니다. ", i+1,pmx_check);
						printf(" * %s \n", err_msg);

						mStr_Edit__Error_Msg = err_msg;

						MessageBox(err_msg, "Route Recipe Error !", MB_ICONERROR);

						UpdateData(FALSE);
						return -21;
					}
				}
			}

			// ...
		}
	}

	return 1;
}
int CDlg__Route_STD::Check__Module_Name(const CString& check_module, 
										const CStringArray& l_module)
{
	int i_limit = l_module.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(check_module.CompareNoCase(l_module[i]) == 0)
		{
			return 1;
		}
	}
	return -1;
}

// ...
void CDlg__Route_STD::OnBnClickedBtn_CurRoute_Update()
{
	UpdateData(TRUE);

	CString file_name;
	mCtrl__Current_Route_File_Name.GetWindowText(file_name);

	Undo__Route_File(file_name, mStr__Current_Route_File_Date);
}
void CDlg__Route_STD::OnLvnColumnclickList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("** CDlg__Route_STD::OnLvnColumnclickList_RouteTable() ... \n");

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// ...
	{
		int main_item = pNMLV->iItem;
		int sub_item  = pNMLV->iSubItem;

		printf("  main_item : %1d \n", main_item);
		printf("  sub_item  : %1d \n", sub_item );
	}

	*pResult = 0;
}
void CDlg__Route_STD::OnNMClickList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("** CDlg__Route_STD::OnNMClickList_RouteTable() ... \n");

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		CListCtrl *p_table = &mCtrl__Route_List_Table;

		int row = pNMItemActivate->iItem;
		int col = pNMItemActivate->iSubItem;

		p_table->SetHotItem(row);
		p_table->SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 

		if(row >= 0)
		{
			CString file_name = p_table->GetItemText(row, _ROUTE_FILE_COL__FILE);
			CString file_date = p_table->GetItemText(row, _ROUTE_FILE_COL__DATE);

			mCtrl__Current_Route_File_Name.SetWindowText(file_name);
			mStr__Current_Route_File_Date = file_date;

			Undo__Route_File(file_name,file_date);
		}
	}

	*pResult = 0;
}
void CDlg__Route_STD::OnNMDblclkList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("** CDlg__Route_STD::OnNMDblclkList_RouteTable() ... \n");

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	/*
	// ...
	{
		int row = pNMItemActivate->iItem;

		CListCtrl *p_table = &mCtrl__Route_List_Table;

		CString file_name = p_table->GetItemText(row, _ROUTE_FILE_COL__FILE);
		CString file_date = p_table->GetItemText(row, _ROUTE_FILE_COL__DATE);

		Undo__Route_File(file_name,file_date);
	}
	*/

	*pResult = 0;
}


// Route Edit ...
void CDlg__Route_STD::OnBnClickedBtn_RouteEdit_Mode()
{
	UpdateData(TRUE);

	CString str_mode;
	mCtrl_RouteEdit_Mode.GetWindowText(str_mode);

	if(str_mode.CompareNoCase("EDIT") == 0)
	{
		if(bActive__Recipe_Changed)
		{
			CString str_title;
			CString str_msg;

			str_title = "수정된 내용을 확인 바랍니다.";

			str_msg  = "변경된 내용이 있습니다.";
			str_msg += "\n";
			str_msg += "변경된 내용을 무시할려면, \"YES\"를 선택하기 바랍니다.";

			int box_id = MessageBox(str_msg, str_title, MB_YESNO);
			if(box_id != IDYES)
			{
				return;
			}

			// ...
			{
				CString file_name;
				mCtrl__Current_Route_File_Name.GetWindowText(file_name);

				Undo__Route_File(file_name, mStr__Current_Route_File_Date);
			}
		}

		mCtrl__Current_Route_File_Name.EnableWindow(TRUE);
		mCtrl__Route_List_Table.EnableWindow(TRUE);
		Set__Route_Edit_Mode(FALSE);
	}
	else
	{
		mCtrl__Current_Route_File_Name.EnableWindow(FALSE);
		mCtrl__Route_List_Table.EnableWindow(FALSE);
		Set__Route_Edit_Mode(TRUE);
	}
}
void CDlg__Route_STD::Set__Route_Edit_Mode(BOOL edit_mode)
{
	bRouteEdit__Edit_Mode = edit_mode;

	if(edit_mode)
	{
		mCtrl_RouteEdit_Mode.SetWindowText("EDIT");

		if(bSCH_TYPE__CONFIG)	
		{
			mCtrl_RouteEdit_STx_Use.EnableWindow(TRUE);
		}
		mCtrl__Route_Edit_Table.EnableWindow(TRUE);

		// ...
		{
			mCtrl_PM1_RCP.EnableWindow(TRUE);
			mCtrl_PM2_RCP.EnableWindow(TRUE);
			mCtrl_PM3_RCP.EnableWindow(TRUE);
			mCtrl_PM4_RCP.EnableWindow(TRUE);
			mCtrl_PM5_RCP.EnableWindow(TRUE);
			mCtrl_PM6_RCP.EnableWindow(TRUE);

			if(iPMx_SIZE < 2)		mCtrl_PM2_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 3)		mCtrl_PM3_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 4)		mCtrl_PM4_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 5)		mCtrl_PM5_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 6)		mCtrl_PM6_RCP.EnableWindow(FALSE);
		}

		// ...
		{
			int sel_size = 0;

			mList_PMx_PRE_RCP.EnableWindow(TRUE);
			sel_size = mList_PMx_PRE_RCP.GetCurSel();
			if(sel_size >= 0)		mCtrl_PMx_PRE_RCP.EnableWindow(TRUE);
			else					mCtrl_PMx_PRE_RCP.EnableWindow(FALSE);

			mList_PMx_MAIN_RCP.EnableWindow(TRUE);
			sel_size = mList_PMx_MAIN_RCP.GetCurSel();
			if(sel_size >= 0)		mCtrl_PMx_MAIN_RCP.EnableWindow(TRUE);
			else					mCtrl_PMx_MAIN_RCP.EnableWindow(FALSE);

			mList_PMx_POST_RCP.EnableWindow(TRUE);
			sel_size = mList_PMx_POST_RCP.GetCurSel();
			if(sel_size >= 0)		mCtrl_PMx_POST_RCP.EnableWindow(TRUE);
			else					mCtrl_PMx_POST_RCP.EnableWindow(FALSE);
		}
	}
	else
	{
		mCtrl_RouteEdit_Mode.SetWindowText("VIEW");

		mCtrl_RouteEdit_STx_Use.EnableWindow(FALSE);
		mCtrl__Route_Edit_Table.EnableWindow(FALSE);

		// ...
		{
			mCtrl_PM1_RCP.EnableWindow(TRUE);
			mCtrl_PM2_RCP.EnableWindow(TRUE);
			mCtrl_PM3_RCP.EnableWindow(TRUE);
			mCtrl_PM4_RCP.EnableWindow(TRUE);
			mCtrl_PM5_RCP.EnableWindow(TRUE);
			mCtrl_PM6_RCP.EnableWindow(TRUE);

			if(iPMx_SIZE < 2)		mCtrl_PM2_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 3)		mCtrl_PM3_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 4)		mCtrl_PM4_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 5)		mCtrl_PM5_RCP.EnableWindow(FALSE);
			if(iPMx_SIZE < 6)		mCtrl_PM6_RCP.EnableWindow(FALSE);
		}

		// ...
		{
			mList_PMx_PRE_RCP.EnableWindow(FALSE);
			mCtrl_PMx_PRE_RCP.EnableWindow(FALSE);
			
			mList_PMx_MAIN_RCP.EnableWindow(FALSE);
			mCtrl_PMx_MAIN_RCP.EnableWindow(FALSE);

			mList_PMx_POST_RCP.EnableWindow(FALSE);
			mCtrl_PMx_POST_RCP.EnableWindow(FALSE);
		}
	}

	UpdateData(FALSE);
}

void CDlg__Route_STD::OnLvnColumnclickList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// ...
	{
		int main_item = pNMLV->iItem;
		int sub_item  = pNMLV->iSubItem;

		printf("  main_item : %1d \n", main_item);
		printf("  sub_item  : %1d \n", sub_item );
	}

	*pResult = 0;
}
void CDlg__Route_STD::OnNMClickList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int main_item = pNMItemActivate->iItem;
		
		Select__RouteEdit_PathID(main_item);
	}

	*pResult = 0;
}
void CDlg__Route_STD::OnNMDblclkList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		int main_item = pNMItemActivate->iItem;

		Select__RouteEdit_PathID(main_item);
	}

	*pResult = 0;
}
void CDlg__Route_STD::Select__RouteEdit_PathID(const int row_index)
{
	CString str_item;

	if(row_index < 0)
	{
		str_item = "__";
	}
	else
	{
		int path_id = (row_index / _ROUTE_EDIT_COL__RCP_SIZE) + 1;
		str_item.Format("%02d", path_id);
	}

	mCtrl_RouteEdit_PathID.SetWindowText(str_item);
}

void CDlg__Route_STD::OnBnClickedBtn_RouteEdit_STx_Use()
{
	UpdateData(TRUE);

	// ...
	{
		CString str_data;
		mCtrl_RouteEdit_STx_Use.GetWindowText(str_data);
	
		if(str_data.CompareNoCase("YES") == 0)		str_data = "NO";
		else										str_data = "YES";

		mCtrl_RouteEdit_STx_Use.SetWindowText(str_data);

		bActive__Recipe_Changed = TRUE;
	}

	mStr_Edit__Error_Msg = "Recipe Changed !";

	UpdateData(FALSE);
}

void CDlg__Route_STD::OnBnClickedBtn_PathView()
{
	UpdateData(TRUE);

	// ...
	{
		CDlg__Route_Path_View dlg;

		int i_limit;
		int i;

		// ALx
		{
			_DB_Info__Category *p_db = &mDB__ALx;

			dlg.sALx__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_ALx__List_ID.Add(p_md->sTitle);

				for(int t=0; t<2; t++)
				{
					CString para_data = "";
					
					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

						 if(t == 0)		dlg.Para_ALx__List_ANGLE.Add(para_data);
					else if(t == 1)		dlg.Para_ALx__List_SLOT.Add(para_data);
				}
			}
		}
		// BMx_IN
		{
			_DB_Info__Category *p_db = &mDB__LLx_IN;

			dlg.sBMx_IN__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_BMx_IN__List_ID.Add(p_md->sTitle);

				for(int t=0; t<2; t++)
				{
					CString para_data = "";

					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

						 if(t == 0)		dlg.Para_BMx_IN__List_MODE.Add(para_data);
					else if(t == 1)		dlg.Para_BMx_IN__List_SLOT.Add(para_data);
				}
			}
		}

		// PROCESS_PATH
		{
			CStringArray l__pmx_name[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__rcp_pre[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__rcp_main[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__rcp_post[_ROUTE_EDIT__PATH_MAX];

			Get__RouteEdit__Process_Path(l__pmx_name,l__rcp_pre,l__rcp_main,l__rcp_post);

			// ...
			int k_limit = _ROUTE_EDIT__PATH_MAX;
			int k;

			dlg.iPara_PATH__SIZE = k_limit;

			for(k=0; k<k_limit; k++)
			{
				dlg.sPROCESS__Title = "PROCESSx";

				// ...
				int i_limit = l__pmx_name[k].GetSize();
				int i;

				for(i=0; i<i_limit; i++)
				{
					CString pmx_name = l__pmx_name[k].GetAt(i);
					CString rcp_pre  = l__rcp_pre[k].GetAt(i);
					CString rcp_main = l__rcp_main[k].GetAt(i);
					CString rcp_post = l__rcp_post[k].GetAt(i);

					dlg.Para_PATHx__List_PMx_ID[k].Add(pmx_name);
					dlg.Para_PATHx__List_RCP_PRE[k].Add(rcp_pre);
					dlg.Para_PATHx__List_RCP_MAIN[k].Add(rcp_main);
					dlg.Para_PATHx__List_RCP_POST[k].Add(rcp_post);
				}
			}
		}
		// LLx_PROC ...
		{
			_DB_Info__Category *p_db = &mDB__LLx_PRC;

			dlg.sLLx_PRC__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_LLx_PRC__List_ID.Add(p_md->sTitle);

				for(int t=0; t<3; t++)
				{
					CString para_data = "";

					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

						 if(t == 0)		dlg.Para_LLx_PRC__List_PRE.Add(para_data);
					else if(t == 1)		dlg.Para_LLx_PRC__List_MAIN.Add(para_data);
					else if(t == 2)		dlg.Para_LLx_PRC__List_POST.Add(para_data);
				}
			}
		}
		// LOOPx_PROC ...
		{
			_DB_Info__Category *p_db = &mDB__LOOPx_PRC;

			dlg.sLOOPx_PRC__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_LOOPx_PRC__List_ID.Add(p_md->sTitle);

				for(int t=0; t<1; t++)
				{
					CString para_data = "";

					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

					if(t == 0)		dlg.Para_LOOPx_PRC__List_REPEAT.Add(para_data);
				}
			}
		}

		// BMx_OUT
		{
			_DB_Info__Category *p_db = &mDB__LLx_OUT;

			dlg.sBMx_OUT__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_BMx_OUT__List_ID.Add(p_md->sTitle);

				for(int t=0; t<2; t++)
				{
					CString para_data = "";

					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

						 if(t == 0)		dlg.Para_BMx_OUT__List_MODE.Add(para_data);
					else if(t == 1)		dlg.Para_BMx_OUT__List_SLOT.Add(para_data);
				}
			}
		}
		// STx
		{
			Update__RouteEdit__STx_To_DB();

			// ...
			_DB_Info__Category *p_db = &mDB__STx;

			dlg.sSTx__Title = p_db->sTitle;

			i_limit = p_db->Get__Module_Size();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

				dlg.Para_STx__List_ID.Add(p_md->sTitle);

				for(int t=0; t<3; t++)
				{
					CString para_data = "";

					if(t < p_md->sList_Para.GetSize())
						para_data = p_md->sList_Para[t];

					     if(t == 0)		dlg.Para_STx__List_MODE.Add(para_data);
					else if(t == 1)		dlg.Para_STx__List_SLOT.Add(para_data);
					else if(t == 2)		dlg.Para_STx__List_SEC.Add(para_data);
					else if(t == 3)		dlg.Para_STx__List_N2_PURGE.Add(para_data);
				}
			}
		}

		dlg.DoModal();
	}

	UpdateData(FALSE);
}


// PMx Update ...
void CDlg__Route_STD::OnBnClickedBtn_PM1_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM1_RCP_Update() ... \n");

	Click__PMx_RCP(1);
}
void CDlg__Route_STD::OnBnClickedBtn_PM2_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM2_RCP_Update() ... \n");

	Click__PMx_RCP(2);
}
void CDlg__Route_STD::OnBnClickedBtn_PM3_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM3_RCP_Update() ... \n");

	Click__PMx_RCP(3);
}
void CDlg__Route_STD::OnBnClickedBtn_PM4_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM4_RCP_Update() ... \n");

	Click__PMx_RCP(4);
}
void CDlg__Route_STD::OnBnClickedBtn_PM5_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM5_RCP_Update() ... \n");

	Click__PMx_RCP(5);
}
void CDlg__Route_STD::OnBnClickedBtn_PM6_RCP_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PM6_RCP_Update() ... \n");

	Click__PMx_RCP(6);
}
void CDlg__Route_STD::Click__PMx_RCP(const int pmx_id)
{
	// ...
	{
		iPMx_SEL = -1;

		mCtrl_PMx_PRE_RCP.EnableWindow(FALSE);
		mCtrl_PMx_MAIN_RCP.EnableWindow(FALSE);
		mCtrl_PMx_POST_RCP.EnableWindow(FALSE);
	}

	// ...
	{
		CButton *p_ctrl;

		int i_limit = 10;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i >= iPMx_SIZE)
			{
				continue;
			}

				 if(i == 0)			p_ctrl = &mCtrl_PM1_RCP;
			else if(i == 1)			p_ctrl = &mCtrl_PM2_RCP;
			else if(i == 2)			p_ctrl = &mCtrl_PM3_RCP;
			else if(i == 3)			p_ctrl = &mCtrl_PM4_RCP;
			else if(i == 4)			p_ctrl = &mCtrl_PM5_RCP;
			else if(i == 5)			p_ctrl = &mCtrl_PM6_RCP;
			else					continue;

			if(pmx_id == (i+1))		p_ctrl->EnableWindow(FALSE);
			else					p_ctrl->EnableWindow(TRUE);

			p_ctrl->SetWindowText(sPMx_NAME[i]);
		}
	}

	if(pmx_id < 1)
	{
		printf("pmx_id : cleared ! \n");

		mCtrl_SEL_PMx.SetWindowText("");

		mList_PMx_PRE_RCP.ResetContent();
		mList_PMx_MAIN_RCP.ResetContent();
		mList_PMx_POST_RCP.ResetContent();

		UpdateData(FALSE);
		return;
	}
	else
	{
		CString sel_pmx;

		// sel_pmx.Format("PM%1d", pmx_id);
		sel_pmx = sPMx_NAME[pmx_id - 1];

		mCtrl_SEL_PMx.SetWindowText(sel_pmx);
	}

	// Process Recipe File ...
	CString dir_root = "";
	CString file_ext = "rcp";

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = pmx_id + 1;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	// ...
	{
		CGX_FILE__PM_CTRL x_file_ctrl;
		CStringArray l_file_name;
		CStringArray l_file_date;

		CString dir_proc;
		CString dir_pre  = sRCP__DIR_PRE;
		CString dir_main = sRCP__DIR_MAIN;
		CString dir_post = sRCP__DIR_POST;

		// Pre-Recipe ...
		{
			CListBox* p_list = &mList_PMx_PRE_RCP;
			
			p_list->ResetContent();
			p_list->AddString(_PMx_RCP__NULL);

			l_file_name.RemoveAll();
			l_file_date.RemoveAll();

			dir_proc.Format("%s\\%s", dir_root,dir_pre);
			MACRO__Get_File_List(dir_proc, file_ext, l_file_name, l_file_date);

			printf(" * pre-recipe : [%s] \n", dir_proc);

			int i_limit = l_file_name.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				p_list->AddString(l_file_name[i]);
			}
		}
		// Main-Recipe ...
		{
			CListBox* p_list = &mList_PMx_MAIN_RCP;

			p_list->ResetContent();
			p_list->AddString(_PMx_RCP__NULL);

			l_file_name.RemoveAll();
			l_file_date.RemoveAll();

			dir_proc.Format("%s\\%s", dir_root,dir_main);
			MACRO__Get_File_List(dir_proc, file_ext, l_file_name, l_file_date);

			printf(" * main-recipe : [%s] \n", dir_proc);

			int i_limit = l_file_name.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				p_list->AddString(l_file_name[i]);
			}
		}
		// Post-Recipe ...
		{
			CListBox* p_list = &mList_PMx_POST_RCP;

			p_list->ResetContent();
			p_list->AddString(_PMx_RCP__NULL);

			l_file_name.RemoveAll();
			l_file_date.RemoveAll();

			dir_proc.Format("%s\\%s", dir_root,dir_post);
			MACRO__Get_File_List(dir_proc, file_ext, l_file_name, l_file_date);

			printf(" * post-recipe : [%s] \n", dir_proc);

			int i_limit = l_file_name.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				p_list->AddString(l_file_name[i]);
			}
		}
	}

	iPMx_SEL = pmx_id;

	printf(" * CDlg__Route_STD::Click__PMx_RCP() \n");
	printf(" * iPMx_SEL : %1d \n", iPMx_SEL);
}

void CDlg__Route_STD::OnBnClickedBtn_PMx_PRE_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PMx_PRE_Update() ... \n");

	// ...
	CListBox *p_list = &mList_PMx_PRE_RCP;
	int col_id = _ROUTE_EDIT_COL__PRE_RCP;

	CString dir_sub = sRCP__DIR_PRE;

	Change__PMx_RCP_Of_Route_Edit(p_list,col_id, dir_sub);
}
void CDlg__Route_STD::OnBnClickedBtn_PMx_MAIN_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PMx_MAIN_Update() ... \n");

	// ...
	CListBox *p_list = &mList_PMx_MAIN_RCP;
	int col_id = _ROUTE_EDIT_COL__MAIN_RCP;

	CString dir_sub = sRCP__DIR_MAIN;

	Change__PMx_RCP_Of_Route_Edit(p_list,col_id, dir_sub);
}
void CDlg__Route_STD::OnBnClickedBtn_PMx_POST_Update()
{
	printf("** CDlg__Route_STD::OnBnClickedBtn_PMx_POST_Update() ... \n");

	// ...
	CListBox *p_list = &mList_PMx_POST_RCP;
	int col_id = _ROUTE_EDIT_COL__POST_RCP;
	
	CString dir_sub = sRCP__DIR_POST;

	Change__PMx_RCP_Of_Route_Edit(p_list,col_id, dir_sub);
}
void CDlg__Route_STD
::Change__PMx_RCP_Of_Route_Edit(CListBox  *p_rcp_list, 
							    const int col_id,
								const CString& dir_sub)
{
	printf(" * CDlg__Route_STD::Change__PMx_RCP_Of_Route_Edit() \n"); 
	printf(" * iPMx_SEL : %1d \n", iPMx_SEL);

	if(iPMx_SEL < 1)
	{
		printf(" ** PM_ID Not Selection : %1d \n", iPMx_SEL);

		mStr_Edit__Error_Msg = "Error : PM_ID Not Selected !";
		UpdateData(FALSE);
		return;
	}

	// ...
	CString str_data;		
		
	mCtrl_RouteEdit_PathID.GetWindowText(str_data);
	int path_index = atoi(str_data) - 1;

	if(path_index < 0)
	{
		printf(" ** Path_Index Not Selection : %1d \n", path_index);

		mStr_Edit__Error_Msg = "Error : Path_Index Not Selected !";
		UpdateData(FALSE);
		return;
	}

	// ...
	CString rcp_name;

	int i_sel = p_rcp_list->GetCurSel();
	if(i_sel < 0)		
	{
		printf(" ** No Selection : %1d \n", i_sel);

		mStr_Edit__Error_Msg = "Error : Recipe Not Selected !";
		UpdateData(FALSE);
		return;
	}

	p_rcp_list->GetText(i_sel, rcp_name);
	printf(" ** Selection [%1d] : %s \n", i_sel,rcp_name);

	// ...
	CListCtrl *p_route_edit = &mCtrl__Route_Edit_Table;

	CString pmx_name;
	pmx_name.Format("PM%1d", iPMx_SEL);

	CString pmx_rcp;
	if(rcp_name.CompareNoCase(_PMx_RCP__NULL) == 0)		pmx_rcp = rcp_name;
	else												pmx_rcp.Format("%s\\%s", dir_sub,rcp_name);

	Change__Route_Edit_Table(p_route_edit, pmx_name,pmx_rcp, path_index,col_id);

	// ...
	{
		bActive__Recipe_Changed = TRUE;

		printf(" #1 Recipe_Changed : TRUE \n");
	}

	mStr_Edit__Error_Msg = "Recipe Changed !";
	UpdateData(FALSE);
}

// ...
int CDlg__Route_STD
::Undo__Route_File(const CString& file_name,
				   const CString& file_date,
				   const BOOL edit_mode)
{
	// ...
	{
		bActive__Recipe_Changed = FALSE;

		printf(" #3 Recipe_Changed : FALSE \n");
	}

	if(file_name.GetLength() < 1)
	{
		mCtrl_RouteEdit_FileName.SetWindowText(file_name);
		mCtrl_RouteEdit_FileDate.SetWindowText(file_date);

		// Click__PMx_RCP(-1);
		Init__Route_Edit_Table();;

		if(edit_mode)
		{
			mCtrl__Route_List_Table.EnableWindow(FALSE);
			Set__Route_Edit_Mode(TRUE);
		}
		else
		{
			mCtrl__Route_List_Table.EnableWindow(TRUE);
			Set__Route_Edit_Mode(FALSE);
		}
		return 1;
	}

	// ...
	CString dir_root  = "";
	CString dir_sub   = "ROUTE";
	CString file_ext  = "rte";
	CString file_data = "";

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		int eqp_id = 0;

		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
	}

	// ...
	{
		CString file_path;
				
		file_path.Format("%s\\%s\\%s.%s", dir_root,dir_sub,file_name,file_ext);
		printf("  * file_path : [%s] \n", file_path);

		if(MACRO__Get_File_Data(file_path, file_data) < 0)
		{
			CString str_msg;

			str_msg.Format("File Error : \"%s\" ", file_path);
			mStr_Edit__Main_Msg = str_msg;

			printf(str_msg);
			printf("\n");

			UpdateData(FALSE);
			return -1;
		}
	}

	// ...
	{
		mCtrl_RouteEdit_FileName.SetWindowText(file_name);
		mCtrl_RouteEdit_FileDate.SetWindowText(file_date);

		// Click__PMx_RCP(-1);
	}

	// DB.Init ...
	{
		mDB__ALx.Init_DB();
		mDB__LLx_IN.Init_DB();
		mDB__LLx_OUT.Init_DB();
		mDB__STx.Init_DB();
		mDB__LLx_PRC.Init_DB();
		mDB__LOOPx_PRC.Init_DB();

		// PROCESS_X ...
		{
			int i_limit = _DB_INFO__PRCx_SIZE;

			for(int i=0; i<i_limit; i++)
			{
				mDB__PRCx[i].Init_DB();
			}
		}
	}

	if(MACRO__Check_Route_File_Edit_Type(file_data) > 0)
	{
		printf("** New_Type File Upload : %s \n", file_name);

		bRCP_TYPE__NEW = TRUE;
		bSCH_TYPE__CONFIG = FALSE;
		Upload__Route_File_Of_New_Type(file_data);
	}
	else
	{
		printf("** Old_Type File Upload : %s \n", file_name);

		bRCP_TYPE__NEW = FALSE;
		bSCH_TYPE__CONFIG = TRUE;
		Upload__Route_File_Of_Old_Type(file_data);
	}

	// ...
	{
		CString data__rcp_type = "???";

		if(bRCP_TYPE__NEW)
		{
			if(bSCH_TYPE__CONFIG)		data__rcp_type = "CONFIG";
			else						data__rcp_type = "ROUTE";
		}
		else
		{
			data__rcp_type = "OLD";
		}

		mCtrl__Rcp_Type.SetWindowText(data__rcp_type);
	}

	// ...
	{
		CString str_msg;

		str_msg.Format("File Upload : \"%s\" ...", file_name);
		mStr_Edit__Main_Msg = str_msg;

		printf(str_msg);
		printf("\n");
	}

	mStr_Edit__Error_Msg = "";
	UpdateData(FALSE);
	return 1;
}

int CDlg__Route_STD
::Upload__Route_File_Of_New_Type(const CString& file_data)
{
	// ...
	int max_count = _ROUTE_EDIT__PATH_MAX;
	int prc_count = 0;

	_DB_Info__Category db_prc[_ROUTE_EDIT__PATH_MAX];

	CStringArray l__al_id;
	CStringArray l__al_angle;
	CStringArray l__al_slot;

	CStringArray l__ll_in_id;
	CStringArray l__ll_in_mode;
	CStringArray l__ll_in_slot;

	CStringArray l__ll_prc_id;
	CStringArray l__ll_prc_pre;
	CStringArray l__ll_prc_main;
	CStringArray l__ll_prc_post;

	CStringArray l__loop_prc_id;
	CStringArray l__loop_prc_repeat;

	CStringArray l__ll_out_id;
	CStringArray l__ll_out_mode;
	CStringArray l__ll_out_slot;

	CStringArray l__st_id;
	CStringArray l__st_mode;
	CStringArray l__st_slot;
	CStringArray l__st_sec;

	CString rcp_item__descript = "";

	CString rcp_item__al_id    = "";
	CString rcp_item__al_angle = "";
	CString rcp_item__al_slot  = "";

	CString rcp_item__ll_id   = "";
	CString rcp_item__ll_mode = "";
	CString rcp_item__ll_slot = "";

	CString rcp_item__ll_prc_id   = "";
	CString rcp_item__ll_prc_pre  = "";
	CString rcp_item__ll_prc_main = "";
	CString rcp_item__ll_prc_post = "";

	CString rcp_item__loop_prc_id = "";
	CString rcp_item__loop_prc_repeat = "";

	CString rcp_item__st_id   = "";
	CString rcp_item__st_mode = "";
	CString rcp_item__st_slot = "";
	CString rcp_item__st_sec  = "";

	// ...
	CString	prc_module;
	CString	rcp_pre;
	CString	rcp_main;
	CString	rcp_post;

	CString	word;
	char ch;

	int command = 0;
	int para = 0;
	int check__ch_r = -1;

	int data_size = file_data.GetLength();
	int x;

	printf("** file_data : %1d ... \n", data_size);
	printf("================================================================== \n");
	printf("%s \n", file_data);
	printf("================================================================== \n");

	for(x=0; x<data_size; x++)
	{
		ch = file_data.GetAt(x);

		if((ch == '^')
		|| (ch == ',')
		|| (ch == ';')
		|| (ch == '(')
		|| (ch == ')')
		|| (ch == '\r')
		|| (ch == '\n')
		|| (ch == EOF))
		{
			if(ch == '\r')
			{
				check__ch_r = 1;
			}

			int new_cmmd = Get__Route_Cmmd_Of_New_Type(word);
			if(new_cmmd > 0)
			{
				if(command != new_cmmd)		
				{
					command = new_cmmd;

					// ...
					{
						word = "";
						para = 0;
					}

					if((command == _NEW_CMMD__BMx_IN)
					|| (command == _NEW_CMMD__BMx_OUT))
					{
						rcp_item__ll_id   = "";
						rcp_item__ll_mode = "";
						rcp_item__ll_slot = "";
					}
					else if(command == _NEW_CMMD__ALx)
					{
						rcp_item__al_id    = "";
						rcp_item__al_angle = "";
						rcp_item__al_slot  = "";
					}
					else if(command == _NEW_CMMD__STx)
					{
						rcp_item__st_id   = "";
						rcp_item__st_mode = "";
						rcp_item__st_slot = "";
						rcp_item__st_sec  = "";
					}
					else if(command == _NEW_CMMD__PROCESS_START)
					{
						prc_module = "";
						rcp_pre  = "";
						rcp_main = "";
						rcp_post = "";
					}
					else if(command == _NEW_CMMD__PROCESS_END)
					{
						prc_count++;
					}
					else if(command == _NEW_CMMD__LLx_PROC_START)
					{
						rcp_item__ll_prc_id   = "";
						rcp_item__ll_prc_pre  = "";
						rcp_item__ll_prc_main = "";
						rcp_item__ll_prc_post = "";
					}
					else if(command == _NEW_CMMD__LOOPx_PROC_START)
					{
						rcp_item__loop_prc_id = "";
						rcp_item__loop_prc_repeat = "";
					}

					continue;
				}
			}

			if(ch == '\n')
			{
				if(check__ch_r > 0)
				{
					check__ch_r = -1;

					if(word.GetLength() < 1)
					{
						word = "";
						continue;
					}
				}
			}

			if(command > 0)
			{
				if((ch == '^')||(ch == ',')||(ch == ';'))
				{
					para++;

					if(command == _NEW_CMMD__PROCESS_START)
					{
							 if(para == 1)		prc_module = word;
						else if(para == 2)		rcp_pre  = word;
						else if(para == 3)		rcp_main = word;
						else if(para == 4)		rcp_post = word;
					}
					else if(command == _NEW_CMMD__LLx_PROC_START)
					{
						     if(para == 1)		rcp_item__ll_prc_id   = word;
						else if(para == 2)		rcp_item__ll_prc_pre  = word;
						else if(para == 3)		rcp_item__ll_prc_main = word;
						else if(para == 4)		rcp_item__ll_prc_post = word;
					}
					else if(command == _NEW_CMMD__LOOPx_PROC_START)
					{
							 if(para == 1)		rcp_item__loop_prc_id     = word;
						else if(para == 2)		rcp_item__loop_prc_repeat = word;
					}
					else if((command == _NEW_CMMD__BMx_IN)
						 || (command == _NEW_CMMD__BMx_OUT))
					{
							 if(para == 1)		rcp_item__ll_id   = word;
						else if(para == 2)		rcp_item__ll_mode = word;
						else if(para == 3)		rcp_item__ll_slot = word;
					}
					else if(command == _NEW_CMMD__ALx)
					{
							 if(para == 1)		rcp_item__al_id    = word;
						else if(para == 2)		rcp_item__al_angle = word;
						else if(para == 3)		rcp_item__al_slot  = word;
					}
					else if(command == _NEW_CMMD__STx)
					{
							 if(para == 1)		rcp_item__st_id   = word;
						else if(para == 2)		rcp_item__st_mode = word;
						else if(para == 3)		rcp_item__st_slot = word;
						else if(para == 4)		rcp_item__st_sec  = word;
					}
					else if(command == _NEW_CMMD__DESCRIPT)
					{
						if(para == 1)
						{
							rcp_item__descript = word;
						} 
						else
						{
							rcp_item__descript += word;

							if(ch ==',')			rcp_item__descript += ",";
							else					rcp_item__descript += "\r\n";
						}
					}
					else if(command == _NEW_CMMD__SCH_CFG)
					{

					}
				}

				if(ch == ';')
				{
					para = 0;

					if(command == _NEW_CMMD__PROCESS_START)
					{
						if(prc_count < max_count)
						{
							_DB_Info__Module db_info;

							db_info.sTitle = prc_module;
							db_info.sList_Para.Add(rcp_pre);
							db_info.sList_Para.Add(rcp_main);
							db_info.sList_Para.Add(rcp_post);

							db_prc[prc_count].Load__Module_Info(db_info);
						}
					}
					else if(command == _NEW_CMMD__LLx_PROC_START)
					{
						l__ll_prc_id.Add(rcp_item__ll_prc_id);
						l__ll_prc_pre.Add(rcp_item__ll_prc_pre);
						l__ll_prc_main.Add(rcp_item__ll_prc_main);
						l__ll_prc_post.Add(rcp_item__ll_prc_post);
					}
					else if(command == _NEW_CMMD__LOOPx_PROC_START)
					{
						l__loop_prc_id.Add(rcp_item__loop_prc_id);
						l__loop_prc_repeat.Add(rcp_item__loop_prc_repeat);
					}
					else if(command == _NEW_CMMD__BMx_IN)
					{
						l__ll_in_id.Add(rcp_item__ll_id);
						l__ll_in_mode.Add(rcp_item__ll_mode);
						l__ll_in_slot.Add(rcp_item__ll_slot);
					}
					else if(command == _NEW_CMMD__BMx_OUT)
					{
						l__ll_out_id.Add(rcp_item__ll_id);
						l__ll_out_mode.Add(rcp_item__ll_mode);
						l__ll_out_slot.Add(rcp_item__ll_slot);
					}
					else if(command == _NEW_CMMD__ALx)
					{
						l__al_id.Add(rcp_item__al_id);
						l__al_angle.Add(rcp_item__al_angle);
						l__al_slot.Add(rcp_item__al_slot);
					}
					else if(command == _NEW_CMMD__STx)
					{
						l__st_id.Add(rcp_item__st_id);
						l__st_mode.Add(rcp_item__st_mode);
						l__st_slot.Add(rcp_item__st_slot);
						l__st_sec.Add(rcp_item__st_sec);
					}
				}
				else if((ch == '\n') || (ch == '\r'))
				{
					if(command == _NEW_CMMD__PROCESS_START)
					{
						prc_module = "";
						rcp_pre  = "";
						rcp_main = "";
						rcp_post = "";
					}
					else if(command == _NEW_CMMD__LLx_PROC_START)
					{
						rcp_item__ll_prc_id   = "";
						rcp_item__ll_prc_pre  = "";
						rcp_item__ll_prc_main = "";
						rcp_item__ll_prc_post = "";
					}
					else if(command == _NEW_CMMD__LOOPx_PROC_START)
					{
						rcp_item__loop_prc_id = "";
						rcp_item__loop_prc_repeat = "";
					}
					else
					{
						command = -1;
					}
				}
			}

			word = "";	
		}
		else
		{
			word += ch;
		}
	}

	// ...
	{
		Init__Route_Edit_Table();;

		CStringArray* p_module_list[_ROUTE_EDIT__PATH_MAX];
		CStringArray* p_recipe_list[_ROUTE_EDIT__PATH_MAX];
		CString str_data;

		CListCtrl *p_table = &mCtrl__Route_Edit_Table;

		// Sub_Parameter ...
		{
			// rcp_item__descript
		
			/*
			str_data = rcp_item__buffer;
			mCtrl_RouteEdit_SideBuffer.SetWindowText(str_data);
			*/
		}

		// PROCESS_PATH
		{
			CStringArray l__main_module[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__main_recipe[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__post_module[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__post_recipe[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__pre_module[_ROUTE_EDIT__PATH_MAX];
			CStringArray l__pre_recipe[_ROUTE_EDIT__PATH_MAX];

			int k_limit =  prc_count;
			int k;

			for(k=0; k<k_limit; k++)
			{
				_DB_Info__Category *p_db = &db_prc[k];;

				int i_limit = p_db->Get__Module_Size();
				for(int i=0; i<i_limit; i++)
				{
					_DB_Info__Module *p_md = p_db->Get__Module_Info(i);

					CString pmx_name = p_md->sTitle;
					CString rcp_pre  = "";
					CString rcp_main = "";
					CString rcp_post = "";

					for(int t=0; t<3; t++)
					{
						CString para_data = "";

						if(t < p_md->sList_Para.GetSize())
							para_data = p_md->sList_Para[t];

							 if(t == 0)		rcp_pre  = para_data;
						else if(t == 1)		rcp_main = para_data;
						else if(t == 2)		rcp_post = para_data;
					}

					//
					l__pre_module[k].Add(pmx_name);
					l__pre_recipe[k].Add(rcp_pre);

					l__main_module[k].Add(pmx_name);
					l__main_recipe[k].Add(rcp_main);

					l__post_module[k].Add(pmx_name);
					l__post_recipe[k].Add(rcp_post);
				}
			}

			// ...
			int step_count = prc_count;

			// Main Recipe ...
			{
				int col_id = _ROUTE_EDIT_COL__MAIN_RCP;

				for(int t=0; t<step_count; t++)
				{
					p_module_list[t] = &(l__main_module[t]);
					p_recipe_list[t] = &(l__main_recipe[t]);
				}
				Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
			}
			// Post Recipe ...
			{
				int col_id = _ROUTE_EDIT_COL__POST_RCP;

				for(int t=0; t<step_count; t++)
				{
					p_module_list[t] = &(l__post_module[t]);
					p_recipe_list[t] = &(l__post_recipe[t]);
				}
				Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
			}
			// Pre Recipe ...
			{
				int col_id = _ROUTE_EDIT_COL__PRE_RCP;

				for(int t=0; t<step_count; t++)
				{
					p_module_list[t] = &(l__pre_module[t]);
					p_recipe_list[t] = &(l__pre_recipe[t]);
				}
				Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
			}
		}
	}

	// DB.Update ...
	{
		int i_limit;
		int i;

		// ALx ...
		{
			mDB__ALx.Init_DB();
			mDB__ALx.sTitle = "ALx";

			i_limit = l__al_id.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__al_id[i];
				db_info.sList_Para.Add(l__al_angle[i]);
				db_info.sList_Para.Add(l__al_slot[i]);
			
				mDB__ALx.Load__Module_Info(db_info);
			}
		}
		// LLx_IN ...
		{
			mDB__LLx_IN.Init_DB();
			mDB__LLx_IN.sTitle = "LLx_IN";
			
			i_limit = l__ll_in_id.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__ll_in_id[i];
				db_info.sList_Para.Add(l__ll_in_mode[i]);
				db_info.sList_Para.Add(l__ll_in_slot[i]);

				mDB__LLx_IN.Load__Module_Info(db_info);
			}
		}
		// PROCESS_X ...
		{
			iSIZE__PRC_PATH = prc_count;
			i_limit = prc_count;

			for(i=0; i<i_limit; i++)
			{
				mDB__PRCx[i].Init_DB();
				mDB__PRCx[i].Copy_From(db_prc[i]);
			}
		}
		// LLx_PRC ...
		{
			mDB__LLx_PRC.Init_DB();
			mDB__LLx_PRC.sTitle = "LLx_PROC";

			i_limit = l__ll_prc_id.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__ll_prc_id[i];
				db_info.sList_Para.Add(l__ll_prc_pre[i]);
				db_info.sList_Para.Add(l__ll_prc_main[i]);
				db_info.sList_Para.Add(l__ll_prc_post[i]);

				mDB__LLx_PRC.Load__Module_Info(db_info);
			}
		}
		// LOOPx_PRC ...
		{
			mDB__LOOPx_PRC.Init_DB();
			mDB__LOOPx_PRC.sTitle = "LLx_LOOP";

			i_limit = l__loop_prc_id.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__loop_prc_id[i];
				db_info.sList_Para.Add(l__loop_prc_repeat[i]);

				mDB__LOOPx_PRC.Load__Module_Info(db_info);
			}
		}
		// LLx_OUT ...
		{
			mDB__LLx_OUT.Init_DB();
			mDB__LLx_OUT.sTitle = "LLx_OUT";

			i_limit = l__ll_out_slot.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__ll_out_id[i];
				db_info.sList_Para.Add(l__ll_out_mode[i]);
				db_info.sList_Para.Add(l__ll_out_slot[i]);

				mDB__LLx_OUT.Load__Module_Info(db_info);
			}
		}
		// STx ...
		{
			mDB__STx.Init_DB();
			mDB__STx.sTitle = "STx";

			i_limit = l__st_id.GetSize();
			for(i=0; i<i_limit; i++)
			{
				_DB_Info__Module db_info;

				db_info.sTitle = l__st_id[i];
				db_info.sList_Para.Add(l__st_mode[i]);
				db_info.sList_Para.Add(l__st_slot[i]);
				db_info.sList_Para.Add(l__st_sec[i]);

				mDB__STx.Load__Module_Info(db_info);
			}

			if(i_limit > 0)
			{
				mCtrl_RouteEdit_STx_Use.SetWindowText("YES");
			}
			else
			{
				mCtrl_RouteEdit_STx_Use.SetWindowText("NO");
			}
		}
	}

	return 1;
}
int CDlg__Route_STD
::Get__Route_Cmmd_Of_New_Type(const CString& cmmd)
{
	if(cmmd.CompareNoCase("#PROCESS_START#") == 0)
	{
		return _NEW_CMMD__PROCESS_START;
	}
	if(cmmd.CompareNoCase("#PROCESS_END#") == 0)
	{
		return _NEW_CMMD__PROCESS_END;
	}
	if(cmmd.CompareNoCase("#LLx_PROC_START#") == 0)
	{
		return _NEW_CMMD__LLx_PROC_START;
	}
	if(cmmd.CompareNoCase("#LLx_PROC_END#") == 0)
	{
		return _NEW_CMMD__LLx_PROC_END;
	}
	if(cmmd.CompareNoCase("#LOOPx_PROC_START#") == 0)
	{
		return _NEW_CMMD__LOOPx_PROC_START;
	}
	if(cmmd.CompareNoCase("#LOOPx_PROC_END#") == 0)
	{
		return _NEW_CMMD__LOOPx_PROC_END;
	}

	if(cmmd.CompareNoCase("#ALx#") == 0)
	{
		return _NEW_CMMD__ALx;
	}
	if(cmmd.CompareNoCase("#LLx_IN#") == 0)
	{
		return _NEW_CMMD__BMx_IN;
	}
	if(cmmd.CompareNoCase("#LLx_OUT#") == 0)
	{
		return _NEW_CMMD__BMx_OUT;
	}
	if(cmmd.CompareNoCase("#STx#") == 0)
	{
		return _NEW_CMMD__STx;
	}

	if(cmmd.CompareNoCase("#DESCRIPT#") == 0)
	{
		return _NEW_CMMD__DESCRIPT;
	}
	if(cmmd.CompareNoCase("#SCH_CFG#") == 0)
	{
		bSCH_TYPE__CONFIG = TRUE;

		return _NEW_CMMD__SCH_CFG;
	}

	return -1;
}

int CDlg__Route_STD
::Upload__Route_File_Of_Old_Type(const CString& file_data)
{
	// ...
	int max_count  = _ROUTE_EDIT__PATH_MAX;
	int main_count = 0;
	int post_count = 0;
	int pre_count  = 0;

	CStringArray l__main_module[_ROUTE_EDIT__PATH_MAX];
	CStringArray l__main_recipe[_ROUTE_EDIT__PATH_MAX];
	CStringArray l__post_module[_ROUTE_EDIT__PATH_MAX];
	CStringArray l__post_recipe[_ROUTE_EDIT__PATH_MAX];
	CStringArray l__pre_module[_ROUTE_EDIT__PATH_MAX];
	CStringArray l__pre_recipe[_ROUTE_EDIT__PATH_MAX];

	CString rcp_item__descript = "";
	CString rcp_item__buffer   = "";

	// ...
	CString	module_name;
	CString	module_recipe;

	CString	word;
	char ch;

	int command = 0;
	int para = 0;
	int check__ch_r = -1;

	int data_size = file_data.GetLength();
	int x;

	printf("** file_data : %1d ... \n", data_size);
	printf("================================================================== \n");
	printf("%s \n", file_data);
	printf("================================================================== \n");

	for(x=0; x<data_size; x++)
	{
		ch = file_data.GetAt(x);

		if((ch == '^')
		|| (ch == ',')
		|| (ch == ';')
		|| (ch == '(')
		|| (ch == ')')
		|| (ch == '\r')
		|| (ch == '\n')
		|| (ch == EOF))
		{
			if(ch == '\r')
			{
				check__ch_r = 1;
			}

			int new_cmmd = Get__Route_Cmmd_Of_Old_Type(word);
			if(new_cmmd > 0)
			{
				if(command != new_cmmd)		
				{
					command = new_cmmd;

					word = "";
					para = 0;

					continue;
				}
			}

			if(ch == '\n')
			{
				if(check__ch_r > 0)
				{
					check__ch_r = -1;

					if(word.GetLength() < 1)
					{
						word = "";
						continue;
					}
				}
			}

			if(command > 0)
			{
				if((ch == '^')||(ch == ',')||(ch == ';'))
				{
					para++;

					if((command == _OLD_CMMD__MAIN_RCP)
					|| (command == _OLD_CMMD__POST_RCP)
					|| (command == _OLD_CMMD__PRE_RCP ))
					{
							 if(para == 1)		module_name   = word;
						else if(para == 2)		module_recipe = word;
					}
					else if(command == _OLD_CMMD__BUFFER)
					{
						if(para == 1)
						{
							rcp_item__buffer = word;
						}
					}
					else if(command == _OLD_CMMD__DESCRIPT)
					{
						if(para == 1)
						{
							rcp_item__descript = word;
						} 
						else
						{
							rcp_item__descript += word;
							
							if(ch ==',')			rcp_item__descript += ",";
							else					rcp_item__descript += "\r\n";
						}
					}
				}

				if(ch == ';')
				{
					para = 0;
					
					if(command == _OLD_CMMD__MAIN_RCP)
					{
						if(main_count < max_count)
						{
							l__main_module[main_count].Add(module_name);
							l__main_recipe[main_count].Add(module_recipe);
						}
					}
					else if(command == _OLD_CMMD__POST_RCP)
					{
						if(post_count < max_count)
						{
							l__post_module[post_count].Add(module_name);
							l__post_recipe[post_count].Add(module_recipe);
						}
					}
					else if(command == _OLD_CMMD__PRE_RCP)
					{
						if(pre_count < max_count)
						{
							l__pre_module[pre_count].Add(module_name);
							l__pre_recipe[pre_count].Add(module_recipe);
						}
					}
				}
				else if((ch == '\n') || (ch == '\r'))
				{
					if(command == _OLD_CMMD__MAIN_RCP)
					{
						if(main_count < max_count)			main_count++;
					}
					else if(command == _OLD_CMMD__POST_RCP)
					{
						if(post_count < max_count)			post_count++;
					}
					else if(command == _OLD_CMMD__PRE_RCP)
					{
						if(pre_count < max_count)			pre_count++;
					}
					else
					{
						command = -1;
					}
				}
			}

			word = "";	
		}
		else
		{
			word += ch;
		}
	}

	// ...
	{
		printf("  Descript : [%s] \n", rcp_item__descript);
		printf("  Buffer   : [%s] \n", rcp_item__buffer);

		//
		printf("  Main_Recipe ... \n");

		int i_limit = main_count;

		for(int i=0; i<i_limit; i++)
		{
			printf("  Path_%1d : ", i+1);

			int k_limit = l__main_module[i].GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				printf("(%s, %s) ",
					   l__main_module[i][k],
					   l__main_recipe[i][k]);
			}
			printf("\n");
		}
	}

	// ...
	{
		Init__Route_Edit_Table();;

		CStringArray* p_module_list[_ROUTE_EDIT__PATH_MAX];
		CStringArray* p_recipe_list[_ROUTE_EDIT__PATH_MAX];
		CString str_data;

		CListCtrl *p_table = &mCtrl__Route_Edit_Table;
	
		// STx ...
		{
			BOOL active__stx_use = FALSE;

			if(rcp_item__buffer.CompareNoCase("YES") == 0)
			{
				active__stx_use = TRUE;
				str_data = "YES";
			}
			else
			{
				str_data = "NO";
			}

			mCtrl_RouteEdit_STx_Use.SetWindowText(str_data);

			// ...
			mDB__STx.Init_DB();

			if(active__stx_use)
			{
				mDB__STx.sTitle = "STx";

				//
				_DB_Info__Module db_md;

				db_md.sTitle = "x";
				db_md.sList_Para.Add("CFG");
				db_md.sList_Para.Add("CFG");
				db_md.sList_Para.Add("CFG");

				mDB__STx.Load__Module_Info(db_md);
			}
		}

		// Main Recipe ...
		{
			int step_count = main_count;
			int col_id = _ROUTE_EDIT_COL__MAIN_RCP;

			for(int t=0; t<step_count; t++)
			{
				p_module_list[t] = &(l__main_module[t]);
				p_recipe_list[t] = &(l__main_recipe[t]);
			}
			Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
		}
		// Post Recipe ...
		{
			int step_count = post_count;
			int col_id = _ROUTE_EDIT_COL__POST_RCP;

			for(int t=0; t<step_count; t++)
			{
				p_module_list[t] = &(l__post_module[t]);
				p_recipe_list[t] = &(l__post_recipe[t]);
			}
			Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
		}
		// Pre Recipe ...
		{
			int step_count = pre_count;
			int col_id = _ROUTE_EDIT_COL__PRE_RCP;

			for(int t=0; t<step_count; t++)
			{
				p_module_list[t] = &(l__pre_module[t]);
				p_recipe_list[t] = &(l__pre_recipe[t]);
			}
			Update__Route_Edit_Table(p_table, p_module_list, p_recipe_list, step_count, col_id);
		}
	}

	return 1;
}
int CDlg__Route_STD::Get__Route_Cmmd_Of_Old_Type(const CString& cmmd)
{
	if(cmmd.CompareNoCase("#ROUTE#") == 0)
	{
		return _OLD_CMMD__MAIN_RCP;
	}
	if(cmmd.CollateNoCase("#POST_CLN#") == 0)
	{
		return _OLD_CMMD__POST_RCP;
	}
	if(cmmd.CollateNoCase("#PRE_RCP#") == 0)
	{
		return _OLD_CMMD__PRE_RCP;
	}

	if(cmmd.CompareNoCase("#BUFFER1#") == 0)
	{
		return _OLD_CMMD__BUFFER;
	}

	if(cmmd.CompareNoCase("#DESCRIPT#") == 0)
	{
		return _OLD_CMMD__DESCRIPT;
	}

	return -1;
}

void CDlg__Route_STD::OnLbnSelchangeList_PreRCP()
{
	if(bRouteEdit__Edit_Mode)		
		mCtrl_PMx_PRE_RCP.EnableWindow(TRUE);
}
void CDlg__Route_STD::OnLbnSelchangeList_MainRCP()
{
	if(bRouteEdit__Edit_Mode)		
		mCtrl_PMx_MAIN_RCP.EnableWindow(TRUE);
}
void CDlg__Route_STD::OnLbnSelchangeList_PostRCP()
{
	if(bRouteEdit__Edit_Mode)		
		mCtrl_PMx_POST_RCP.EnableWindow(TRUE);
}

BOOL CDlg__Route_STD::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if((wParam == IDC_BTN__FILE_NEW)
	|| (wParam == IDC_BTN__FILE_UNDO)
	|| (wParam == IDC_BTN__FILE_SAVE)
	|| (wParam == IDC_BTN__FILE_SAVEAS)
	|| (wParam == IDC_BTN__FILE_DELETE))
	{
		CPart__Rcp_Common *p_rcp = NULL;

			 if(wParam == IDC_BTN__FILE_NEW)			p_rcp = &mCtrl_RouteFile_New;
		else if(wParam == IDC_BTN__FILE_UNDO)			p_rcp = &mCtrl_RouteFile_Undo;
		else if(wParam == IDC_BTN__FILE_SAVE)			p_rcp = &mCtrl_RouteFile_Save;
		else if(wParam == IDC_BTN__FILE_SAVEAS)			p_rcp = &mCtrl_RouteFile_SaveAs;
		else if(wParam == IDC_BTN__FILE_DELETE)			p_rcp = &mCtrl_RouteFile_Delete;

		if(p_rcp != NULL)
		{
			if(p_rcp->Is__Disable_State() < 0)
			{
				NMHDR* p_hdr = (NMHDR*) lParam;

				if(p_hdr->code == _BTN__LDOWN)
				{
					p_rcp->Draw__Down_State();
				}
				else if(p_hdr->code == _BTN__LUP)
				{
					p_rcp->Draw__Up_State();
				}
			}
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlg__Route_STD::OnHdnItemclickList__File_List(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	// ...
	{
		int col = phdr->iItem;

		Sort__Route_File(col);
	}

	*pResult = 0;
}
int  CDlg__Route_STD::Sort__Route_File(const int col)
{
	if(col < 1)			return -1;
	if(col > 2)			return -2;

	// ...
	int i_limit = sList__RouteFile_Name.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString cmp_name = sList__RouteFile_Name[i];
		CString cmp_date = sList__RouteFile_Date[i];

		for(int k=i+1; k<i_limit; k++)
		{
			CString cur_name = sList__RouteFile_Name[k];
			CString cur_date = sList__RouteFile_Date[k];

			// ...
			bool active_order = false;

			if(col == 1)
			{
				if(m_bResultDirect)		
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
				if(m_bResultDirect)		
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
				sList__RouteFile_Name[i] = cur_name;
				sList__RouteFile_Date[i] = cur_date;

				sList__RouteFile_Name[k] = cmp_name;
				sList__RouteFile_Date[k] = cmp_date;

				cmp_name = cur_name;
				cmp_date = cur_date;
			}
		}

		// ...
	}

	// ...
	{
		CString s_date;

		Update__RouteFile_List("",s_date, sList__RouteFile_Name,sList__RouteFile_Date);
	}

	m_bResultDirect = !m_bResultDirect;
	return 1;
}
