// Dlg__Route_EDIT.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__Route_EDIT.h"
#include "Dlg__Route_EDIT__Def.h"

#include "Macro_Function.h"
#include "CObj__Route_EDIT__KEY_DEF.h"
#include "Dlg__Process_Recipe_Select.h"

#include "Dlg__Route_ALx.h"
#include "Dlg__Route_LLx.h"
#include "Dlg__Route_STx.h"
#include "Dlg__Route_LOOPx.h"


#define  STR__MODE					"MODE"

#define  STR__PRE__RCP				"PRE_.RCP"
#define  STR__MAIN_RCP				"MAIN.RCP"
#define  STR__POST_RCP				"POST.RCP"


// CDlg__Route_EDIT dialog

IMPLEMENT_DYNAMIC(CDlg__Route_EDIT, CDialog)

CDlg__Route_EDIT::CDlg__Route_EDIT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Route_EDIT::IDD, pParent)
{
	bActive__LLx_PROC   = false;
	bActive__LOOPx_PROC = false;

	iShow_Count = 0;
}

CDlg__Route_EDIT::~CDlg__Route_EDIT()
{
}

void CDlg__Route_EDIT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE__MODULE_LIST, mTree__Module_List);
	DDX_Control(pDX, IDC_TREE__ROUTE_EDIT,  mTree__Route_Edit);
	DDX_Control(pDX, IDC_LIST__ROUTE_FILE, mCtrl__RouteFile_List);
	DDX_Control(pDX, IDC_BTN__ROUTE_FILE__LIST, mCtrl__Current_Route_File);
	DDX_Control(pDX, IDC_BTN__ROUTE_FILE__SIZE, mCtrl__Route_File_Size);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT__FILE_NAME, mCtrl__RouteEdit_FileName);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT__FILE_DATE, mCtrl__RouteEdit_FileDate);
	DDX_Control(pDX, IDC_CHECK__DEFUALT_ROUTE, mCheck__Default_Route);
	DDX_Text(pDX, IDC_EDIT__SYS_MSG, mStr__Sys_Msg);
	DDX_Text(pDX, IDC_EDIT__ERROR_MSG, mStr_Edit__Error_Msg);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT_MODE, mCtrl__RouteEdit_Mode);

	DDX_Control(pDX, IDC_BTN__ROUTE_NEW,  mBtn__Route_New);
	DDX_Control(pDX, IDC_BTN__ROUTE_UNDO, mBtn__Route_Undo);

	DDX_Control(pDX, IDC_BTN__ROUTE_SAVE,   mBtn__Route_Save);
	DDX_Control(pDX, IDC_BTN__ROUTE_SAVEAS, mBtn__Route_SaveAs);
	DDX_Control(pDX, IDC_BTN__ROUTE_FILE__DELETE, mBtn__Route_Delete);

	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT__DELETE,   mBtn__Rcp_Item_Delete);
	DDX_Control(pDX, IDC_BTN__ROUTE_EDIT__PROPERTY, mBtn__Rcp_Item_Property);
}


BEGIN_MESSAGE_MAP(CDlg__Route_EDIT, CDialog)
	ON_WM_TIMER()

	ON_NOTIFY(HDN_ITEMCLICK, 0, &CDlg__Route_EDIT::OnHdnItemclickList__File_List)

	ON_NOTIFY(NM_CLICK,  IDC_TREE__ROUTE_EDIT,  &CDlg__Route_EDIT::OnNMClickTree_RouteEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE__ROUTE_EDIT,  &CDlg__Route_EDIT::OnNMDblclkTree_RouteEdit)
	ON_NOTIFY(NM_RCLICK, IDC_TREE__ROUTE_EDIT,  &CDlg__Route_EDIT::OnNMRClickTree_RouteEdit)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE__ROUTE_EDIT, &CDlg__Route_EDIT::OnTvnSelchangedTree__RouteEdit)

	ON_BN_CLICKED(IDC_BTN__ROUTE_EDIT_MODE, &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Mode)
	ON_BN_CLICKED(IDC_BTN__RE_EXPAND,   &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Expand)
	ON_BN_CLICKED(IDC_BTN__RE_EXPAND_X, &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Expand_X)
	ON_BN_CLICKED(IDC_BTN__RE_CONTRACT, &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Contract)

	ON_BN_CLICKED(IDC_BTN__ROUTE_EDIT__DELETE,   &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Delete)
	ON_BN_CLICKED(IDC_BTN__ROUTE_EDIT__COPY,     &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Copy)
	ON_BN_CLICKED(IDC_BTN__ROUTE_EDIT__PROPERTY, &CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Property)

	ON_BN_CLICKED(IDC_BTN__ROUTE_FILE__DELETE, &CDlg__Route_EDIT::OnBnClickedBtn__File_Delete)
	ON_BN_CLICKED(IDC_BTN__ROUTE_FILE__REFRESH, &CDlg__Route_EDIT::OnBnClickedBtn_Refresh)
	ON_BN_CLICKED(IDC_BTN__ROUTE_FILE__LIST,    &CDlg__Route_EDIT::OnBnClickedBtn_RouteFile_Upload)

	ON_NOTIFY(NM_CLICK, IDC_LIST__ROUTE_FILE, &CDlg__Route_EDIT::OnNMClickList_RouteFile)

	ON_BN_CLICKED(IDC_BTN__ROUTE_NEW,  &CDlg__Route_EDIT::OnBnClickedBtn_New)
	ON_BN_CLICKED(IDC_BTN__ROUTE_UNDO, &CDlg__Route_EDIT::OnBnClickedBtn_Undo)

	ON_BN_CLICKED(IDC_BTN__ROUTE_SAVE, &CDlg__Route_EDIT::OnBnClickedBtn_Save)
	ON_BN_CLICKED(IDC_BTN__ROUTE_SAVEAS, &CDlg__Route_EDIT::OnBnClickedBtn_SaveAs)

END_MESSAGE_MAP()


// CDlg__Route_EDIT message handlers

BOOL CDlg__Route_EDIT::OnInitDialog()
{
	CDialog::OnInitDialog();

	Fnc_OnInitDialog();

	// ...
	{
		mBtn__Route_New.Init_Resource(this, NULL);
		mBtn__Route_Undo.Init_Resource(this, NULL);

		mBtn__Route_Save.Init_Resource(this, NULL);
		mBtn__Route_SaveAs.Init_Resource(this, NULL);
		mBtn__Route_Delete.Init_Resource(this, NULL);

		bActive__Recipe_Changed = FALSE;
	}

	mCheck__Default_Route.SetCheck(1);
	m_bResultDirect = TRUE;

	SetTimer(1, 500, NULL);
	return TRUE; 
}
BOOL CDlg__Route_EDIT::Fnc_OnInitDialog()
{
	int i_limit;
	int i;

	// Route_File List ...
	{
		CBitmap cBit;
		cBit.LoadBitmap(IDB_DIGITAL_LIST_IMG);

		CListCtrl *p_table = &mCtrl__RouteFile_List;
		CImageList *p_img  = &mImg__RouteFile_List;

		p_img->Create(1,20, ILC_COLOR4,1,1);
		p_img->Add(&cBit, RGB(0,0,0));	

		p_table->SetImageList(p_img, LVSIL_SMALL);

		// ...
		int list_view_stype;

		list_view_stype  = LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
		list_view_stype += LVS_EX_ONECLICKACTIVATE|LVS_EX_UNDERLINEHOT;
		list_view_stype += LVS_EX_INFOTIP;

		mCtrl__RouteFile_List.SetExtendedStyle(list_view_stype);

		Make__RouteFile_List();
	}

	// Moudle_List ...
	{
		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		CDragDropTreeCtrl *p_tree = &mTree__Module_List;
		CImageList *p_img = &mImg__Module_List;

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 
		
		p_tree->SetImageList(p_img, TVSIL_NORMAL);
		p_tree->Set_LinkDragDrop(this);

		//
		HTREEITEM h_module;
		CString str_module;

		h_module = p_tree->InsertItem("MODULE", _LIST__MODULE,_LIST__MODULE, TVI_ROOT, TVI_LAST);

		Add__ALx_To_Tree_Route(p_tree, h_module,NULL);
		Add__LLx_IN_To_Tree_Route(p_tree, h_module,NULL);
		Add__PMx_To_Tree_Route(p_tree, h_module,NULL, -1, true);
		
		if(bActive__LLx_PROC)			Add__LLx_PROC_To_Tree_Route(p_tree, h_module,NULL);
		if(bActive__LOOPx_PROC)			Add__LOOPx_PROC_To_Tree_Route(p_tree, h_module,NULL);
		
		Add__LLx_OUT_To_Tree_Route(p_tree, h_module,NULL);
		Add__STx_To_Tree_Route(p_tree, h_module,NULL);

		MACRO__Expand_Tree(p_tree, h_module, 2);
	}

	// Route_Edit ...
	{
		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		CDragDropTreeCtrl* p_tree = &mTree__Route_Edit;
		CImageList* p_img = &mImg__Route_Edit;

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 
	
		p_tree->SetImageList(p_img, TVSIL_NORMAL);
		p_tree->Set_LinkDragDrop(this);

		// ...
		Init__Route_Edit_Table();
		Change__Route_Edit_Mode(FALSE);
	}

	Update__RouteFile_List();
	return TRUE; 
}

void CDlg__Route_EDIT::OnTimer(UINT nIDEvent)
{
	static int pre_state = 0;

	if(bActive__Recipe_Changed)
	{
		if(pre_state <= 0)
		{
			pre_state = 1;

			mBtn__Route_New.Draw__Disable_State();
			mBtn__Route_Undo.Draw__Up_State();

			mBtn__Route_Save.Draw__Active_State();
			mBtn__Route_SaveAs.Draw__Active_State();
			mBtn__Route_Delete.Draw__Disable_State();
		}
	}
	else
	{
		if(pre_state >= 0)
		{
			pre_state = -1;

			mBtn__Route_New.Draw__Up_State();
			mBtn__Route_Undo.Draw__Up_State();

			mBtn__Route_Save.Draw__Disable_State();
			mBtn__Route_SaveAs.Draw__Up_State();
			mBtn__Route_Delete.Draw__Up_State();
		}
	}
}

BOOL CDlg__Route_EDIT::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if((wParam == IDC_BTN__ROUTE_NEW)
	|| (wParam == IDC_BTN__ROUTE_UNDO)
	|| (wParam == IDC_BTN__ROUTE_SAVE)
	|| (wParam == IDC_BTN__ROUTE_SAVEAS)
	|| (wParam == IDC_BTN__ROUTE_FILE__DELETE))
	{
		CPart__Rcp_Common *p_rcp = NULL;

			 if(wParam == IDC_BTN__ROUTE_NEW)				p_rcp = &mBtn__Route_New;
		else if(wParam == IDC_BTN__ROUTE_UNDO)				p_rcp = &mBtn__Route_Undo;
		else if(wParam == IDC_BTN__ROUTE_SAVE)				p_rcp = &mBtn__Route_Save;
		else if(wParam == IDC_BTN__ROUTE_SAVEAS)			p_rcp = &mBtn__Route_SaveAs;
		else if(wParam == IDC_BTN__ROUTE_FILE__DELETE)		p_rcp = &mBtn__Route_Delete;

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

// ...
#define _ROUTE_FILE_COL__NUMBER					0
#define _ROUTE_FILE_COL__FILE					1
#define _ROUTE_FILE_COL__DATE					2

void CDlg__Route_EDIT
::Make__RouteFile_List()
{
	CListCtrl *p_table = &mCtrl__RouteFile_List;

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
				l__col_width.Add(260);
			}
			else if(i == _ROUTE_FILE_COL__DATE)
			{
				l__col_name.Add("Date");
				l__col_width.Add(145);
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


// Route Edit ...
void CDlg__Route_EDIT::OnNMClickTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("CDlg__Route_EDIT::OnNMClickTree_RouteEdit() \n");

	*pResult = 0;
}
void CDlg__Route_EDIT::OnNMDblclkTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("CDlg__Route_EDIT::OnNMDblclkTree_RouteEdit() \n");

	*pResult = 0;
}

void CDlg__Route_EDIT::OnNMRClickTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("CDlg__Route_EDIT::OnNMRClickTree_RouteEdit() \n");

	CTreeCtrl *p_table = &mTree__Route_Edit;

	HTREEITEM h_cur = p_table->GetSelectedItem();				
	if(h_cur != NULL)
	{
		CString str_item = p_table->GetItemText(h_cur);
		
		printf(" ** str_item : %s \n", str_item);
	}	

	*pResult = 0;
}

void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Mode()
{
	if(bActive__RouteEdit_Mode)
	{
		bActive__RouteEdit_Mode = FALSE;
		Change__Route_Edit_Mode(FALSE);
	}
	else
	{
		bActive__RouteEdit_Mode = TRUE;
		Change__Route_Edit_Mode(TRUE);
	}
}
void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Expand()
{
	CTreeCtrl *p_tree = &mTree__Route_Edit;

	MACRO__Expand_All_Tree(p_tree);
}
void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Expand_X()
{
	CTreeCtrl *p_tree = &mTree__Route_Edit;
	HTREEITEM h_route = p_tree->GetRootItem();

	MACRO__Contract_All_Tree(p_tree);
	MACRO__Expand_Tree(p_tree, h_route, 2);
}
void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Contract()
{
	CTreeCtrl *p_tree = &mTree__Route_Edit;
	HTREEITEM h_route = p_tree->GetRootItem();

	MACRO__Contract_All_Tree(p_tree);
	MACRO__Expand_Tree(p_tree, h_route, 1);
}

void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Delete()
{
	CTreeCtrl *p_tree = &mTree__Route_Edit;

	HTREEITEM h_cur = p_tree->GetSelectedItem();				
	HTREEITEM h_mod = Get__Tree_Module(p_tree, h_cur);
	
	if(h_mod != NULL)		
	{
		p_tree->DeleteItem(h_mod);

		bActive__Recipe_Changed = TRUE;
	}
	else if(h_cur != NULL)
	{
		p_tree->DeleteItem(h_cur);

		bActive__Recipe_Changed = TRUE;
	}
}
void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Copy()
{
	CTreeCtrl *p_table = &mTree__Route_Edit;

	HTREEITEM h_cur = p_table->GetSelectedItem();				

	if(h_cur != NULL)
	{
		CString str_item = p_table->GetItemText(h_cur);

		HTREEITEM h_top = mTree__Route_Edit.GetParentItem(h_cur);
		HTREEITEM h_add_sibling = mTree__Route_Edit.InsertItem(str_item, h_top, h_cur);

		mTree__Route_Edit.Expand(h_add_sibling, TVE_EXPAND);
		mTree__Route_Edit.SelectItem(h_add_sibling);					
	}
}
void CDlg__Route_EDIT::OnBnClickedBtn_RouteEdit_Property()
{
	CTreeCtrl *p_table = &mTree__Route_Edit;

	HTREEITEM h_cur = p_table->GetSelectedItem();				
	if(h_cur != NULL)
	{
		CString str_data;

		HTREEITEM h_root = p_table->GetRootItem();
		HTREEITEM h_node = h_cur;

		str_data = p_table->GetItemText(h_node);
		printf(" * Current_Node - Text  :  [%s] \n", str_data);

		int n_img = -1;
		int n_sel = -1;
		p_table->GetItemImage(h_node, n_img,n_sel);
		str_data.Format("%1d : %1d", n_img,n_sel);
		printf(" * Current_Node - Data  :  [%s] \n", str_data);

		HTREEITEM h_upper  = h_node;
		HTREEITEM h_module = NULL;

		while((h_node != NULL) && (h_node != h_root))
		{
			h_upper = h_node;
			h_node  = p_table->GetParentItem(h_upper);

			// ... 
			int c_img;
			int c_sel;
			
			if(p_table->GetItemImage(h_upper, c_img,c_sel) > 0)
			{
				// ...
				{
					str_data = p_table->GetItemText(h_upper);

					printf(" ** [%s] [%1d] [%1d] \n", str_data,c_img,c_sel);
				}

				// ...
				int c_dif = 0;

					 if(c_img == _EDIT__ALx)			c_dif = c_sel - _SEL_ID__ALx;
				else if(c_img == _EDIT__LLx_IN)			c_dif = c_sel - _SEL_ID__LLx;
				else if(c_img == _EDIT__LLx_OUT)		c_dif = c_sel - _SEL_ID__LLx;
				else if(c_img == _EDIT__PROCESS_XX)		c_dif = c_sel - _SEL_ID__PMx;
				else if(c_img == _EDIT__STx_XX)			c_dif = c_sel - _SEL_ID__STx;
				else if(c_img == _EDIT__LLx_PROC)		c_dif = c_sel - _SEL_ID__LLx_PROC;
				else if(c_img == _EDIT__LOOPx_PROC)		c_dif = c_sel - _SEL_ID__LOOPx_PROC;

				if(c_dif > 0)
				{
					h_module = h_upper;
				}
			}
		}

		if(h_upper != NULL)
		{
			str_data = p_table->GetItemText(h_upper);
			printf(" * Upper_Node    :  [%s] \n", str_data);
		}
		if(!h_module != NULL)
		{
			str_data = p_table->GetItemText(h_module);
			printf(" * Current_Node  :  [%s] \n", str_data);
		}

		if(n_img == _EDIT__ALx)
		{
			HTREEITEM h_item__angle = NULL;
			HTREEITEM h_item__slot  = NULL;

			CString str_module = "???";
			CString str_anlge;
			CString str_slot;

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				HTREEITEM h_child = p_table->GetChildItem(h_module);
				if(h_child != NULL)
				{
					h_item__angle = h_child;
					str_anlge = p_table->GetItemText(h_child);
					
					h_child = p_table->GetNextSiblingItem(h_child);
					if(h_child != NULL)
					{
						h_item__slot = h_child;
						str_slot = p_table->GetItemText(h_child);
					}
					else
					{
						str_slot = "???";
					}
				}
			}

			// ...
			{
				CDlg__Route_ALx dlg;

				dlg.bACTIVE__CTRL_CFG   = bACTIVE_DEFAULT__AL1_CTRL_CFG;
				dlg.bACTIVE__SLOT_FIXED = bACTIVE_DEFAULT__AL1_SLOT_FIXED;

				dlg.sPARA_ALx   = str_module;
				dlg.sPARA_ANGLE = MACRO__Get_ITEM_DATA(str_anlge, ':');
				dlg.sPARA_SLOT  = MACRO__Get_ITEM_DATA(str_slot,  ':');

				dlg.bACTIVE_SLOT01 = bACTIVE_DEFAULT__AL1_SLOT01;
				dlg.bACTIVE_SLOT02 = bACTIVE_DEFAULT__AL1_SLOT02;

				if(dlg.DoModal() == IDOK)
				{
					if((str_anlge.CompareNoCase(dlg.sPARA_ANGLE) != 0)
					|| (str_slot.CompareNoCase(dlg.sPARA_SLOT) != 0))
					{
						bActive__Recipe_Changed = TRUE;
					}

					str_anlge = dlg.sPARA_ANGLE;
					str_slot  = dlg.sPARA_SLOT;

					str_data.Format("ANGLE : %s", str_anlge);
					p_table->SetItemText(h_item__angle, str_data);

					str_data.Format("SLOT : %s", str_slot);
					p_table->SetItemText(h_item__slot, str_data);

					UpdateData(FALSE);
				}
			}
		}
		else if((n_img == _EDIT__LLx_IN) || (n_img == _EDIT__LLx_OUT))
		{
			HTREEITEM h_item__mode = NULL;
			HTREEITEM h_item__slot = NULL;
			HTREEITEM h_item__cooling_sec = NULL;

			CString str_module = "???";
			CString str_mode = "???";
			CString str_slot = "???";
			CString str_cooling_sec = "???";

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				HTREEITEM h_child = p_table->GetChildItem(h_module);
				if(h_child != NULL)
				{
					h_item__mode = h_child;
					str_mode = p_table->GetItemText(h_child);

					h_child= p_table->GetNextSiblingItem(h_child);
					if(h_child != NULL)
					{
						h_item__slot = h_child;
						str_slot = p_table->GetItemText(h_child);
					}

					h_child= p_table->GetNextSiblingItem(h_child);
					if(h_child != NULL)
					{
						h_item__cooling_sec = h_child;
						str_cooling_sec = p_table->GetItemText(h_child);
					}
				}
			}

			// ...
			{
				CDlg__Route_LLx dlg;

				dlg.bACTIVE__LLx_SLOT_FIXED = bACTIVE_DEFAULT__LLx_SLOT_FIXED;

				if(iLLx_MODE == _LLx_MODE__ALL)			dlg.bACTIVE__LLx_MODE_ALL = true;
				else									dlg.bACTIVE__LLx_MODE_ALL = false;

				if(n_img == _EDIT__LLx_IN)
				{
					dlg.iLLx_IN__ACTIVE =  1;
					dlg.bACTIVE__LLx_OUT_COOLING = false;
				}
				else
				{
					dlg.iLLx_IN__ACTIVE = -1;
					dlg.bACTIVE__LLx_OUT_COOLING = bACTIVE__LLx_OUT_COOLING;
				}

				dlg.sPARA_LLx  = str_module;
				dlg.sPARA_MODE = MACRO__Get_ITEM_DATA(str_mode, ':');
				dlg.sPARA_SLOT = MACRO__Get_ITEM_DATA(str_slot, ':');

				if(dlg.bACTIVE__LLx_OUT_COOLING)
				{
					dlg.sPARA__COOLING_SEC = MACRO__Get_ITEM_DATA(str_cooling_sec, ':');
				}

				if(dlg.DoModal() == IDOK)
				{
					if((str_mode.CompareNoCase(dlg.sPARA_MODE) != 0)
					|| (str_slot.CompareNoCase(dlg.sPARA_SLOT) != 0))
					{
						bActive__Recipe_Changed = TRUE;
					}

					str_mode = dlg.sPARA_MODE;
					str_slot = dlg.sPARA_SLOT;
					str_cooling_sec = dlg.sPARA__COOLING_SEC;

					str_data.Format("MODE : %s", str_mode);
					p_table->SetItemText(h_item__mode, str_data);

					str_data.Format("SLOT : %s", str_slot);
					p_table->SetItemText(h_item__slot, str_data);
					
					if(dlg.bACTIVE__LLx_OUT_COOLING)
					{
						str_data.Format("COOLING : %s", str_cooling_sec);
						p_table->SetItemText(h_item__cooling_sec, str_data);
					}

					UpdateData(FALSE);
				}
			}
		}
		else if(n_img == _EDIT__PROCESS_XX)
		{
			HTREEITEM h_item__rcp_pre  = NULL;
			HTREEITEM h_item__rcp_main = NULL;
			HTREEITEM h_item__rcp_post = NULL;

			CString str_module = "???";
			CString str__rcp_pre;
			CString str__rcp_main;
			CString str__rcp_post;

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				// ...
				HTREEITEM h_child;

				h_child = p_table->GetChildItem(h_module);
				h_item__rcp_pre = h_child;
				if(h_child != NULL)			str__rcp_pre = p_table->GetItemText(h_child);
				else						str__rcp_pre = "???";
	
				h_child= p_table->GetNextSiblingItem(h_child);
				h_item__rcp_main = h_child;
				if(h_child != NULL)			str__rcp_main = p_table->GetItemText(h_child);
				else						str__rcp_main = "???";

				h_child= p_table->GetNextSiblingItem(h_child);
				h_item__rcp_post = h_child;
				if(h_child != NULL)			str__rcp_post = p_table->GetItemText(h_child);
				else						str__rcp_post = "???";
			}

			// ...
			{
				CDlg__Process_Recipe_Select dlg;

				dlg.iREAL_MODE = iREAL_MODE;
				dlg.iPara__PMx_ID = MACRO__Get__PMC_ID(str_module);

				dlg.sPara__PMx_Info = str_module;

				dlg.sPara__PRE_RCP      = MACRO__Get_ITEM_DATA(str__rcp_pre,  ':');
				dlg.sPara__PRE_SUB_DIR  = sData__RCP_PRE;
				
				dlg.sPara__MAIN_RCP     = MACRO__Get_ITEM_DATA(str__rcp_main, ':');
				dlg.sPara__MAIN_SUB_DIR = sData__RCP_MAIN;
				
				dlg.sPara__POST_RCP     = MACRO__Get_ITEM_DATA(str__rcp_post, ':');
				dlg.sPara__POST_SUB_DIR = sData__RCP_POST;

				if(dlg.DoModal() == IDOK)
				{
					if((str__rcp_pre.CompareNoCase(dlg.sPara__PRE_RCP)   != 0)
					|| (str__rcp_main.CompareNoCase(dlg.sPara__MAIN_RCP) != 0)
					|| (str__rcp_post.CompareNoCase(dlg.sPara__POST_RCP) != 0))
					{
						bActive__Recipe_Changed = TRUE;
					}

					str__rcp_pre  = dlg.sPara__PRE_RCP;
					str__rcp_main = dlg.sPara__MAIN_RCP;
					str__rcp_post = dlg.sPara__POST_RCP;

					str_data.Format("PRE_.RCP : %s", str__rcp_pre);
					p_table->SetItemText(h_item__rcp_pre, str_data);

					str_data.Format("MAIN.RCP : %s", str__rcp_main);
					p_table->SetItemText(h_item__rcp_main, str_data);

					str_data.Format("POST.RCP : %s", str__rcp_post);
					p_table->SetItemText(h_item__rcp_post, str_data);

					UpdateData(FALSE);
				}
			}
		}
		else if(n_img == _EDIT__STx_XX)
		{
			HTREEITEM h_item__mode = NULL;
			HTREEITEM h_item__slot = NULL;
			HTREEITEM h_item__sec  = NULL;
			HTREEITEM h_item__n2_purge = NULL;

			CString str_module = "???";
			CString str_mode;
			CString str_slot;
			CString str_sec;
			CString str_n2_purge;

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				// ...
				HTREEITEM h_child;

				h_child = p_table->GetChildItem(h_module);
				h_item__mode = h_child;
				if(h_child != NULL)			str_mode = p_table->GetItemText(h_child);
				else						str_mode = "???";

				h_child = p_table->GetNextSiblingItem(h_child);
				h_item__slot = h_child;
				if(h_child != NULL)			str_slot = p_table->GetItemText(h_child);
				else						str_slot = "???";

				h_child = p_table->GetNextSiblingItem(h_child);
				h_item__sec = h_child;
				if(h_child != NULL)			str_sec = p_table->GetItemText(h_child);
				else						str_sec = "???";

				h_child = p_table->GetNextSiblingItem(h_child);
				h_item__n2_purge = h_child;
				if(h_child != NULL)			str_n2_purge = p_table->GetItemText(h_child);
				else						str_n2_purge = "???";
			}

			// ...
			{
				CDlg__Route_STx dlg;

				dlg.sPARA_STx  = str_module;
				dlg.sPARA_MODE = MACRO__Get_ITEM_DATA(str_mode, ':');
				dlg.sPARA_SLOT = MACRO__Get_ITEM_DATA(str_slot, ':');
				dlg.sPARA_SEC  = MACRO__Get_ITEM_DATA(str_sec,  ':');

				dlg.bACTIVE__STx_N2_PURGE = bACTIVE__STx_N2_PURGE;
				dlg.sPARA_N2_PURGE = MACRO__Get_ITEM_DATA(str_n2_purge,  ':');

				if(dlg.DoModal() == IDOK)
				{
					if((str_mode.CompareNoCase(dlg.sPARA_MODE) != 0)
					|| (str_slot.CompareNoCase(dlg.sPARA_SLOT) != 0)
					|| (str_sec.CompareNoCase(dlg.sPARA_SEC)   != 0)
					|| (str_n2_purge.CompareNoCase(dlg.sPARA_N2_PURGE) != 0))
					{
						bActive__Recipe_Changed = TRUE;
					}

					str_mode = dlg.sPARA_MODE;
					str_slot = dlg.sPARA_SLOT;
					str_sec  = dlg.sPARA_SEC;
					str_n2_purge = dlg.sPARA_N2_PURGE;

					str_data.Format("MODE : %s", str_mode);
					p_table->SetItemText(h_item__mode, str_data);

					str_data.Format("SLOT : %s", str_slot);
					p_table->SetItemText(h_item__slot, str_data);

					str_data.Format("SEC : %s", str_sec);
					p_table->SetItemText(h_item__sec, str_data);

					str_data.Format("N2_PURGE : %s", str_n2_purge);
					p_table->SetItemText(h_item__n2_purge, str_data);

					UpdateData(FALSE);
				}
			}
		}
		else if(n_img == _EDIT__LLx_PROC)
		{
			HTREEITEM h_item__rcp_pre  = NULL;
			HTREEITEM h_item__rcp_main = NULL;
			HTREEITEM h_item__rcp_post = NULL;

			CString str_module = "???";
			CString str__rcp_pre;
			CString str__rcp_main;
			CString str__rcp_post;

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				// ...
				HTREEITEM h_child;

				h_child = p_table->GetChildItem(h_module);
				h_item__rcp_pre = h_child;
				if(h_child != NULL)			str__rcp_pre = p_table->GetItemText(h_child);
				else						str__rcp_pre = "???";

				h_child= p_table->GetNextSiblingItem(h_child);
				h_item__rcp_main = h_child;
				if(h_child != NULL)			str__rcp_main = p_table->GetItemText(h_child);
				else						str__rcp_main = "???";

				h_child= p_table->GetNextSiblingItem(h_child);
				h_item__rcp_post = h_child;
				if(h_child != NULL)			str__rcp_post = p_table->GetItemText(h_child);
				else						str__rcp_post = "???";
			}

			// ...
			{
				CDlg__Process_Recipe_Select dlg;

				dlg.iREAL_MODE = iREAL_MODE;
				dlg.iPara__PMx_ID = 0;

				dlg.sPara__PMx_Info = str_module;

				dlg.sPara__PRE_RCP      = MACRO__Get_ITEM_DATA(str__rcp_pre,  ':');
				dlg.sPara__PRE_SUB_DIR  = sData__RCP_PRE;

				dlg.sPara__MAIN_RCP     = MACRO__Get_ITEM_DATA(str__rcp_main, ':');
				dlg.sPara__MAIN_SUB_DIR = sData__RCP_MAIN;

				dlg.sPara__POST_RCP     = MACRO__Get_ITEM_DATA(str__rcp_post, ':');
				dlg.sPara__POST_SUB_DIR = sData__RCP_POST;

				if(dlg.DoModal() == IDOK)
				{
					if((str__rcp_pre.CompareNoCase(dlg.sPara__PRE_RCP)   != 0)
					|| (str__rcp_main.CompareNoCase(dlg.sPara__MAIN_RCP) != 0)
					|| (str__rcp_post.CompareNoCase(dlg.sPara__POST_RCP) != 0))
					{
						bActive__Recipe_Changed = TRUE;
					}

					str__rcp_pre  = dlg.sPara__PRE_RCP;
					str__rcp_main = dlg.sPara__MAIN_RCP;
					str__rcp_post = dlg.sPara__POST_RCP;

					str_data.Format("PRE_.RCP : %s", str__rcp_pre);
					p_table->SetItemText(h_item__rcp_pre, str_data);

					str_data.Format("MAIN.RCP : %s", str__rcp_main);
					p_table->SetItemText(h_item__rcp_main, str_data);

					str_data.Format("POST.RCP : %s", str__rcp_post);
					p_table->SetItemText(h_item__rcp_post, str_data);

					UpdateData(FALSE);
				}
			}
		}
		else if(n_img == _EDIT__LOOPx_PROC)
		{
			HTREEITEM h_item__repeat = NULL;

			CString str_module = "???";
			CString str_repeat;

			if(h_module != NULL)
			{
				str_module = p_table->GetItemText(h_module);

				// ...
				HTREEITEM h_child;

				h_child = p_table->GetChildItem(h_module);
				h_item__repeat = h_child;
				if(h_child != NULL)			str_repeat = p_table->GetItemText(h_child);
				else						str_repeat = "???";
			}

			// ...
			{
				CDlg__Route_LOOPx dlg;

				dlg.sPARA_MODULE = str_module;
				dlg.sPARA_REPEAT = MACRO__Get_ITEM_DATA(str_repeat, ':');

				if(dlg.DoModal() == IDOK)
				{
					if(str_repeat.CompareNoCase(dlg.sPARA_REPEAT) != 0)
					{
						bActive__Recipe_Changed = TRUE;
					}

					str_repeat = dlg.sPARA_REPEAT;

					str_data.Format("REPEAT : %s", str_repeat);
					p_table->SetItemText(h_item__repeat, str_data);

					UpdateData(FALSE);
				}
			}
		}

		// ...
	}
}


// ...
int CDlg__Route_EDIT
::Call__DragDrop(CTreeCtrl* p_tree_xxx, 
				 const HTREEITEM h_item,
				 const POINT scr_pt)
{
	printf("CDlg__Route_EDIT::Call__DragDrop() ... \n");

	UpdateData(TRUE);

	if(p_tree_xxx != NULL)
	{
		printf(" * Call__DragDrop() : Check_1 ... \n");

		CTreeCtrl *p_module_list = &mTree__Module_List;

		if(p_tree_xxx == p_module_list)
		{
			printf(" * Call__DragDrop() : Check_2 ... \n");

			POINT win_pt = scr_pt;
			ScreenToClient(&win_pt);

			CRect rt_edit;
			mTree__Route_Edit.GetWindowRect(&rt_edit);
			ScreenToClient(&rt_edit);

			if(rt_edit.PtInRect(win_pt))
			{
				printf(" * Call__DragDrop() : Check_3 ... \n");

				CString str_item;
				int c_img;
				int c_sel;
				
				str_item = p_tree_xxx->GetItemText(h_item);
				p_tree_xxx->GetItemImage(h_item, c_img,c_sel);

				printf(" * str_item : %s \n", str_item);
				printf("  ** c_img  : [%1d] \n", c_img);
				printf("  ** c_sel  : [%1d] \n", c_sel);

				// ...
				CDragDropTreeCtrl *p_tree_edit = &mTree__Route_Edit;

				HTREEITEM h_category = Get__Tree_Category(p_tree_edit);
				if(h_category != NULL)
				{
					CString cur_category = p_tree_edit->GetItemText(h_category);
					printf(" ** Current_Category : [%s] \n", cur_category);

					HTREEITEM h_root = p_tree_edit->GetRootItem();
					HTREEITEM h_node = Add__XXX_To_Tree_Route(p_tree_xxx,h_item, p_tree_edit,h_root,h_category);

					p_tree_edit->SelectItem(h_node);
					MACRO__Expand_Tree(p_tree_edit, h_node, 4);
				}
				else
				{
					printf(" ** No Selection ... \n");

					HTREEITEM h_root = p_tree_edit->GetRootItem();

					if(c_img == _EDIT__ALx)				Add__ALx_To_Tree_Route(p_tree_edit, h_root, NULL);
					if(c_img == _EDIT__LLx_IN)			Add__LLx_IN_To_Tree_Route(p_tree_edit, h_root, NULL);
					if(c_img == _EDIT__PROCESS_XX)		Add__PMx_To_Tree_Route(p_tree_edit, h_root, NULL);
					if(c_img == _EDIT__LLx_PROC)		Add__LLx_PROC_To_Tree_Route(p_tree_edit, h_root, NULL);
					if(c_img == _EDIT__LLx_OUT)			Add__LLx_OUT_To_Tree_Route(p_tree_edit, h_root, NULL);
					if(c_img == _EDIT__STx_XX)			Add__STx_To_Tree_Route(p_tree_edit, h_root, NULL);

					MACRO__Expand_All_Tree(p_tree_edit);
				}
			}
			else
			{
				printf(" * Call__DragDrop() : Check_11 ... \n");
			}
		}
		else
		{
			CDragDropTreeCtrl *p_tree = &mTree__Route_Edit;

			HTREEITEM h_cur_category = Get__Tree_Category(p_tree, h_item);
			HTREEITEM h_pre_category = Get__Tree_Pre_Category_Of_Process_X(p_tree, h_cur_category);
			
			int cur_img, cur_sel;
			int pre_img, pre_sel;

			p_tree->GetItemImage(h_cur_category, cur_img,cur_sel);
			p_tree->GetItemImage(h_pre_category, pre_img,pre_sel);
						
			if((cur_img == _EDIT__PROCESS_XX)
			&& (pre_img == _EDIT__PROCESS_XX))
			{
				_Change__Tree_Category(p_tree, h_cur_category,h_pre_category);

				MACRO__Expand_Tree(p_tree, h_cur_category, 4);
				MACRO__Expand_Tree(p_tree, h_pre_category, 4);
			}
		}
	}

	return 1;
}

void CDlg__Route_EDIT::OnBnClickedBtn__File_Delete()
{
	UpdateData(TRUE);

	// ...
	{
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

		CString file_name;
		mCtrl__Current_Route_File.GetWindowText(file_name);

		CString file_path;
		file_path.Format("%s\\%s.%s", dir_proc,file_name,file_ext);

		MACRO__Delete_File(file_path);

		// ...
		mStr__Sys_Msg.Format("Delete \"%s\".", file_name);
		mCtrl__Current_Route_File.SetWindowText("");
	}

	Update__RouteFile_List();
}
void CDlg__Route_EDIT::OnBnClickedBtn_Refresh()
{
	Update__RouteFile_List();
}
void CDlg__Route_EDIT
::Update__RouteFile_List()
{
	CString s_date;
	
	Update__RouteFile_List("",s_date);
}
void CDlg__Route_EDIT
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

	// ...
	{
		sList__RouteFile_Name.Copy(l_file);
		sList__RouteFile_Date.Copy(l_date);
	}

	m_bResultDirect = FALSE;
	Sort__Route_File(2);
}
void CDlg__Route_EDIT::
Update__RouteFile_List(const CString& s_name,
					   CString& s_date, 
					   const CStringArray& l_file,
					   const CStringArray& l_date)
{
	CListCtrl *p_table = &mCtrl__RouteFile_List;
	p_table->DeleteAllItems();

	int s_check = -1;
	CString str_count;
	CString file_name;
	CString file_date;

	int i_limit = l_file.GetSize();
	int i;

	for(i=0;i<i_limit;i++)
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
	mCtrl__Route_File_Size.SetWindowText(str_count);

	UpdateData(FALSE);
}

void CDlg__Route_EDIT::OnBnClickedBtn_RouteFile_Upload()
{
	UpdateData(TRUE);

	// ...
	CString file_name;
	CString file_date;

	mCtrl__RouteEdit_FileName.GetWindowText(file_name);
	mCtrl__RouteEdit_FileDate.GetWindowText(file_date);

	Undo__Route_File(file_name, file_date);
}

void CDlg__Route_EDIT::OnNMClickList_RouteFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ...
	{
		CListCtrl *p_table = &mCtrl__RouteFile_List;

		int row = pNMItemActivate->iItem;
		int col = pNMItemActivate->iSubItem;

		p_table->SetHotItem(row);
		p_table->SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 

		if(row >= 0)
		{
			CString file_name = p_table->GetItemText(row, _ROUTE_FILE_COL__FILE);
			CString file_date = p_table->GetItemText(row, _ROUTE_FILE_COL__DATE);

			mCtrl__Current_Route_File.SetWindowText(file_name);

			mCtrl__RouteEdit_FileName.SetWindowText(file_name);
			mCtrl__RouteEdit_FileDate.SetWindowText(file_date);
			
			Undo__Route_File(file_name, file_date);
		}
	}

	*pResult = 0;
}

void CDlg__Route_EDIT::OnBnClickedBtn_New()
{
	if(mBtn__Route_New.Is__Disable_State() > 0)
	{
		printf(" * CDlg__Route_EDIT::OnBnClickedBtn_New() \n");
		printf(" ** Disable_State !!! \n");
		return;
	}

	// ...
	{
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
		if(id_msg != IDYES)			return;
	}

	// ...
	{
		bActive__Recipe_Changed = FALSE;

		bActive__RouteEdit_Mode = TRUE;
		Change__Route_Edit_Mode(TRUE);
	}

	// Route_Edit ...
	CTreeCtrl* p_tree = &mTree__Route_Edit;
	p_tree->DeleteAllItems();

	// ...
	HTREEITEM h_route = p_tree->InsertItem("ROUTE", _EDIT__ROUTE, _EDIT__ROUTE, TVI_ROOT, TVI_LAST);

	int check_mode = mCheck__Default_Route.GetCheck();	
	if(check_mode > 0)
	{
		Add__ALx_To_Tree_Route(p_tree, h_route, NULL);
		Add__LLx_IN_To_Tree_Route(p_tree, h_route, NULL);
		Add__PMx_To_Tree_Route(p_tree, h_route, NULL);
		Add__LLx_PROC_To_Tree_Route(p_tree, h_route, NULL);
		Add__LLx_OUT_To_Tree_Route(p_tree, h_route, NULL);
		Add__STx_To_Tree_Route(p_tree, h_route, NULL);
	}

	MACRO__Expand_All_Tree(p_tree);

	// ...
	{
		CString file_date = MACRO__Get_Date_Time();

		mCtrl__RouteEdit_FileName.SetWindowText("");
		mCtrl__RouteEdit_FileDate.SetWindowText(file_date);
	}

	UpdateData(FALSE);
}
void CDlg__Route_EDIT::OnBnClickedBtn_Undo()
{
	// ...
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
		if(id_msg != IDYES)		return;
	}

	// ...
	UpdateData(TRUE);

	CString file_name;
	CString file_date;

	mCtrl__RouteEdit_FileName.GetWindowText(file_name);
	mCtrl__RouteEdit_FileDate.GetWindowText(file_date);

	Undo__Route_File(file_name,file_date, TRUE);
}

void CDlg__Route_EDIT
::Add__Process_Path_To_RouteEdit(CTreeCtrl* p_tree,
								 HTREEITEM h_upper_node, 
								 const CString& path_name)
{
	int img_id = _EDIT__PROCESS_XX;

	HTREEITEM h_path = p_tree->InsertItem(path_name, img_id,img_id, h_upper_node, TVI_LAST);

	CString str_pmx__name;
	CString str_rcp__pre;
	CString str_rcp__main;
	CString str_rcp__post;

	int i_limit = iPMx_SIZE;
	int i;

	for(i=0; i<i_limit; i++)
	{
		int pm_id = i + 1;
		str_pmx__name.Format("PM%1d", pm_id);
		
		int lst_id = _SEL_ID__PMx;
		int sel_id = lst_id + pm_id;

		HTREEITEM h_pmx = p_tree->InsertItem(str_pmx__name, img_id,sel_id, h_path, TVI_LAST);

		str_rcp__pre  = STR__PRE__RCP;
		str_rcp__main = STR__MAIN_RCP;
		str_rcp__post = STR__POST_RCP;

		p_tree->InsertItem(str_rcp__pre,  img_id,lst_id, h_pmx, TVI_LAST);
		p_tree->InsertItem(str_rcp__main, img_id,lst_id, h_pmx, TVI_LAST);
		p_tree->InsertItem(str_rcp__post, img_id,lst_id, h_pmx, TVI_LAST);
	}
}

void CDlg__Route_EDIT::OnTvnSelchangedTree__RouteEdit(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("CDlg__Route_EDIT::OnTvnSelchangedTree__Route_Edit() \n");

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;
}

void CDlg__Route_EDIT::OnBnClickedBtn_Save()
{
	UpdateData(TRUE);

	CString file_name;
	mCtrl__RouteEdit_FileName.GetWindowText(file_name);

	Save__Route_Rcp(file_name);
}
void CDlg__Route_EDIT::OnBnClickedBtn_SaveAs()
{
	UpdateData(TRUE);

	CString file_name;
	mCtrl__RouteEdit_FileName.GetWindowText(file_name);

	// ...
	CGX__UTILITY_CTRL x_pad_ctrl;

	CString str_name = "Input File Name !"; 
	CString in_data  = file_name;

	if(x_pad_ctrl->Popup_Keyboard(str_name, in_data, file_name) < 0)
	{
		return;
	}

	mCtrl__RouteEdit_FileName.SetWindowText(file_name);
	Save__Route_Rcp(file_name);

	Update__RouteFile_List();
}

int  CDlg__Route_EDIT::Save__Route_Rcp(const CString& file_name)
{
	CDB__Route_Info db_route;

	CDragDropTreeCtrl *p_tree = &mTree__Route_Edit;

	HTREEITEM h_root;
	HTREEITEM h_category;
	HTREEITEM h_main;
	HTREEITEM h_item;

	h_root = p_tree->GetRootItem();
	
	h_category = p_tree->GetChildItem(h_root);
	while(h_category != NULL)
	{
		CString str_title;
		int i_img;
		int i_sel;
		
		str_title = p_tree->GetItemText(h_category);
		p_tree->GetItemImage(h_category, i_img,i_sel);

		db_route.Load__Category_Info(str_title, i_img,i_sel);

		h_main = p_tree->GetChildItem(h_category);
		while(h_main != NULL)
		{
			CDB__Module_Info db_md;

			str_title = p_tree->GetItemText(h_main);
			p_tree->GetItemImage(h_main, i_img,i_sel);

			db_md.sTitle  = str_title;
			db_md.iImg_ID = i_img;
			db_md.iSel_ID = i_sel;

			h_item = p_tree->GetChildItem(h_main);
			while(h_item != NULL)
			{
				str_title = p_tree->GetItemText(h_item);
				p_tree->GetItemImage(h_item, i_img,i_sel);

				db_md.sList_Item.Add(str_title);
				db_md.iList_ImgID.Add(i_img);
				db_md.iList_SelID.Add(i_sel);

				h_item = p_tree->GetNextSiblingItem(h_item);
			}			

			db_route.Load__Module_Info(db_md);

			h_main = p_tree->GetNextSiblingItem(h_main);
		}

		h_category = p_tree->GetNextSiblingItem(h_category);
	}

	// Check Route ...
	{
		int active__llx_in = -1;
		int count__llx_in_all = 0;
		int count__llx_only_input = 0;
		CStringArray l__only_input__ll_id;

		int active__llx_out = -1;
		int count__llx_only_output = 0;
		int count__llx_out_all = 0;
		CStringArray l__only_output__ll_id;

		int active__pmx_path = -1;

		// ...
		CDB__Category_Info *p_category;
		CDB__Module_Info   *p_module;

		int c_limit = db_route.Get__Category_Size();
		int c;

		for(c=0; c<c_limit; c++)
		{
			CString log_msg;
			CString log_bff;

			p_category = db_route.Get__Category_Info(c);

			int img_category = p_category->iImg_ID;

			if(img_category == _EDIT__LLx_IN)
			{
				int m_limit = p_category->Get__Module_Size();

				for(int m=0; m<m_limit; m++)
				{
					p_module = p_category->Get__Module_Info(m);

					int i_limit = p_module->sList_Item.GetSize();
					int i;

					for(i=0; i<i_limit; i++)
					{
						CString str_para = p_module->sList_Item[i];

						if(str_para.Find(STR__MODE) != 0)
						{
							continue;
						}

						str_para = MACRO__Get_ITEM_DATA(str_para, ':');
						if((str_para.CompareNoCase(STR__ALL) != 0)
						&& (str_para.CompareNoCase(STR__ONLY_INPUT) != 0))
						{
							continue;
						}

						active__llx_in = 1;

							 if(str_para.CompareNoCase(STR__ALL) == 0)					count__llx_in_all++;
						else if(str_para.CompareNoCase(STR__ONLY_INPUT) == 0)			count__llx_only_input++;

						// ...
						{
							CString str__ll_id = p_module->sTitle;
							l__only_input__ll_id.Add(str__ll_id);
						}
						break;
					}
				}				
			}
			else if(img_category == _EDIT__LLx_OUT)
			{
				int m_limit = p_category->Get__Module_Size();
				int m;

				for(m=0; m<m_limit; m++)
				{
					p_module = p_category->Get__Module_Info(m);

					int i_limit = p_module->sList_Item.GetSize();
					int i;

					for(i=0; i<i_limit; i++)
					{
						CString str_para = p_module->sList_Item[i];

						if(str_para.Find(STR__MODE) != 0)
						{
							continue;
						}

						str_para = MACRO__Get_ITEM_DATA(str_para, ':');
						if((str_para.CompareNoCase(STR__ALL) != 0)
						&& (str_para.CompareNoCase(STR__ONLY_OUTPUT) != 0))
						{
							continue;
						}

						active__llx_out = 1;

							 if(str_para.CompareNoCase(STR__ALL) == 0)					count__llx_out_all++;
						else if(str_para.CompareNoCase(STR__ONLY_OUTPUT) == 0)			count__llx_only_output++;

						// ...
						{
							CString str__ll_id = p_module->sTitle;
							l__only_output__ll_id.Add(str__ll_id);
						}
						break;
					}
				}				
			}
			else if(img_category == _EDIT__PROCESS_XX)
			{
				int m_limit = p_category->Get__Module_Size();
				int m;

				for(m=0; m<m_limit; m++)
				{
					p_module = p_category->Get__Module_Info(m);

					int i_limit = p_module->sList_Item.GetSize();
					int i;

					for(i=0; i<i_limit; i++)
					{
						CString str_para = p_module->sList_Item[i];

						if(str_para.Find(STR__MAIN_RCP) != 0)
						{
							continue;
						}

						CString file_name = MACRO__Get_ITEM_DATA(str_para, ':');
						if(file_name.GetLength() < 1)
						{
							continue;
						}

						active__pmx_path = 1;
						break;
					}
				}				
			}
		}

		// Error Check ...
		{
			if(active__llx_in > 0)
			{
				if((count__llx_in_all < 1)
				&& (count__llx_only_input < 1))
				{
					active__llx_in = -1;
				}

				if((count__llx_only_input < 1) && (count__llx_only_output > 0))
				{
					active__llx_in = -2;
				}
			}

			if(active__llx_out > 0)
			{
				if((count__llx_out_all < 1)
				&& (count__llx_only_output < 1))
				{
					active__llx_out = -1;
				}

				if((count__llx_only_input > 0) && (count__llx_only_output < 1))
				{
					active__llx_out = -2;
				}

				if((count__llx_only_input  > 0)
				&& (count__llx_only_output > 0))
				{
					bool active__err_check = false;

					int k_limit = l__only_input__ll_id.GetSize();
					for(int k=0; k < k_limit; k++)
					{
						CString str__ll_id = l__only_input__ll_id[k];

						int t_limit = l__only_output__ll_id.GetSize();
						for(int t=0; t < t_limit; t++)
						{
							if(l__only_output__ll_id[t].CompareNoCase(str__ll_id) != 0)
								continue;

							active__err_check = true;
							break;
						}
					}

					if(active__err_check)
					{
						active__llx_out = -3;
					}
				}
			}

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "Recipe Info ... \n";

				// LLx_IN ...
				{
					log_bff.Format("  * active__llx_in <- [%1d] \n", active__llx_in);
					log_msg += log_bff;
					log_bff.Format("    count__llx_in_all <- %1d \n", count__llx_in_all);
					log_msg += log_bff;
					log_bff.Format("    count__llx_only_input <- %1d \n", count__llx_only_input);
					log_msg += log_bff;

					// ...
					log_msg += "  * ll_id \n";

					int k_limit = l__only_input__ll_id.GetSize();
					for(int k=0; k<k_limit; k++)
					{
						log_bff.Format("    %s \n", l__only_input__ll_id[k]);
						log_msg += log_bff;
					}
				}

				// LLx_OUT ...
				{
					log_bff.Format("  * active__llx_out <- [%1d] \n", active__llx_out);
					log_msg += log_bff;
					log_bff.Format("    count__llx_out_all <- %1d \n", count__llx_out_all);
					log_msg += log_bff;
					log_bff.Format("    count__llx_only_output <- %1d \n", count__llx_only_output);
					log_msg += log_bff;

					// ...
					log_msg += "  * ll_id \n";

					int k_limit = l__only_output__ll_id.GetSize();
					for(int k=0; k<k_limit; k++)
					{
						log_bff.Format("    %s \n", l__only_output__ll_id[k]);
						log_msg += log_bff;
					}
				}

				printf(log_msg);
			}
		}

		if((active__llx_in   < 0)
		|| (active__pmx_path < 0)
		|| (active__llx_out  < 0))
		{
			CString err_msg;
			CString err_bff;

			err_msg = "Route Recipe의 Module 설정이 되어 있지 않습니다. \n";

			if(active__llx_in < 0)		
				err_msg += " * LLx_IN 내의 설정 정보를 확인 바랍니다. \n";
			if(active__pmx_path < 0)		
				err_msg += " * PROCESSs 내의 설정 정보를 확인 바랍니다. \n";
			if(active__llx_out < 0)		
				err_msg += " * LLx_OUT 내의 설정 정보를 확인 바랍니다. \n";

			MessageBox(err_msg, "Save Error !", MB_OK|MB_ICONERROR);
			return -1;
		}
	}

	// File Data ...
	{
		CString file_data = "";

		file_data += "#ROUTE_EDIT#";
		file_data += "\n";

		file_data += "#DESCRIPT#,;";
		file_data += "\n";

		file_data += db_route.Get__ALx_Of_Route_Info();
		file_data += db_route.Get__LLx_Of_Route_Info(_ROUTE_TYPE__LLx_IN);
		file_data += db_route.Get__PROCESSx_Of_Route_Info();
		file_data += db_route.Get__LLx_PROC_Of_Route_Info();
		file_data += db_route.Get__LOOPx_PROC_Of_Route_Info();
		file_data += db_route.Get__LLx_Of_Route_Info(_ROUTE_TYPE__LLx_OUT);
		file_data += db_route.Get__STx_Of_Route_Info();	

		// ...
		CString dir_root  = "";
		CString dir_sub   = "ROUTE";
		CString file_ext  = "rte";

		// ...
		{
			CGX__SYSTEM_CTRL x_sys_ctrl;
			int eqp_id = 0;

			x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_root);
		}

		// ...
		CString file_path;
		file_path.Format("%s\\%s\\%s.%s", dir_root,dir_sub,file_name,file_ext);

		if(MACRO__Save_File_Data(file_path, file_data) < 0)
		{
			return -1;
		}
	}

	bActive__Recipe_Changed = FALSE;
	return 1;
}

void CDlg__Route_EDIT::OnHdnItemclickList__File_List(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	// ...
	{
		int col = phdr->iItem;

		Sort__Route_File(col);
	}

	*pResult = 0;
}
int  CDlg__Route_EDIT::Sort__Route_File(const int col)
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

