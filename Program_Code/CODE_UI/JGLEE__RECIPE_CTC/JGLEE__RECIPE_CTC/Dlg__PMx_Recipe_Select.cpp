// Dlg__PMx_Recipe_Select.cpp : implementation file
//

#include "stdafx.h"
#include "JGLEE__RECIPE_CTC.h"
#include "Dlg__PMx_Recipe_Select.h"
#include "Dlg__Process_Recipe_Select.h"

#include "CObj__PMx_Recipe_Select__KEY_DEF.h"
#include "Macro_Function.h"


// CDlg__PMx_Recipe_Select dialog

IMPLEMENT_DYNAMIC(CDlg__PMx_Recipe_Select, CDialog)

CDlg__PMx_Recipe_Select::CDlg__PMx_Recipe_Select(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__PMx_Recipe_Select::IDD, pParent)
{

}

CDlg__PMx_Recipe_Select::~CDlg__PMx_Recipe_Select()
{
}

void CDlg__PMx_Recipe_Select::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TREE__PMx_RECIPE, mTree__PMx_Recipe);
	DDX_Control(pDX, IDC_BTN__CUR_PMx_ID,  mCtrl__SEL_PMx_ID);
}


BEGIN_MESSAGE_MAP(CDlg__PMx_Recipe_Select, CDialog)
	ON_BN_CLICKED(IDC_BTN__CUR_PMx_ID, &CDlg__PMx_Recipe_Select::OnBnClickedBtn__PMx_Recipe)
	ON_NOTIFY(NM_CLICK,  IDC_TREE__PMx_RECIPE, &CDlg__PMx_Recipe_Select::OnNMClickTree__PMx_Recipe)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE__PMx_RECIPE, &CDlg__PMx_Recipe_Select::OnNMDblclkTree__PMx_Recipe)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE__PMx_RECIPE, &CDlg__PMx_Recipe_Select::OnTvnSelchangedTree__PMx_Recipe)
END_MESSAGE_MAP()


// CDlg__PMx_Recipe_Select message handlers

BOOL CDlg__PMx_Recipe_Select::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Result ReportMoudle_List ...
	{
		Init__Tree_Table_Of_PMx_Recipe();
	}

	return TRUE;  
}

void CDlg__PMx_Recipe_Select
::Init__Tree_Table_Of_PMx_Recipe()
{
	CTreeCtrl *p_tree = &mTree__PMx_Recipe;
	
	// ...
	{
		CImageList *p_img  = &mImageList__PMx_Recipe;

		CBitmap bmp;
		bmp.LoadBitmap(IDB_IMAGE_LIST);

		p_img->Create(16, 16, ILC_COLORDDB|ILC_MASK, 9, 9);
		p_img->Add(&bmp, RGB(0, 0, 0)); 

		p_tree->SetImageList(p_img, TVSIL_NORMAL);
	}
	p_tree->DeleteAllItems();

	//
	CString pmx_id;
	HTREEITEM h_pm1 = NULL;

	CString str_data;

	//
	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_PRE_USE, str_data);
	if(str_data.CompareNoCase("YES") == 0)			bActive__PRE_ISE = true;
	else											bActive__PRE_ISE = false;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_POST_USE, str_data);
	if(str_data.CompareNoCase("YES") == 0)			bActive__POST_ISE = true;
	else											bActive__POST_ISE = false;

	//
	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_PM_SIZE, str_data);
	iPM_SIZE = atoi(str_data);
	if(iPM_SIZE > _DEF_PMx__MAX)		iPM_SIZE = _DEF_PMx__MAX;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_LL_SIZE, str_data);
	iLL_SIZE = atoi(str_data);
	if(iLL_SIZE > _DEF_LLx__MAX)		iLL_SIZE = _DEF_LLx__MAX;

	// ...
	int i_limit;
	int i;

	// PMx ...
	{
		i_limit = iPM_SIZE;

		for(i=0; i<i_limit; i++)
		{
			pmx_id.Format("PM%1d", i+1);

			HTREEITEM h_pmx;
			HTREEITEM h_rcp;

			h_pmx = p_tree->InsertItem(pmx_id, i,i, TVI_ROOT, TVI_LAST);
			if(h_pm1 == NULL)		h_pm1 = h_pmx;

			if(bActive__PRE_ISE)
			{
				h_rcp = p_tree->InsertItem("Pre_Recipe",  i,i, h_pmx, TVI_LAST);
				p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);
			}

			h_rcp = p_tree->InsertItem("Main_Recipe", i,i, h_pmx, TVI_LAST);
			p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);

			if(bActive__POST_ISE)
			{
				h_rcp = p_tree->InsertItem("Post_Recipe", i,i, h_pmx, TVI_LAST);
				p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);
			}
		}
	}
	// LLx ...
	{
		i_limit = iLL_SIZE;

		for(i=0; i<i_limit; i++)
		{
			pmx_id.Format("LL%1d", i+1);

			HTREEITEM h_pmx;
			HTREEITEM h_rcp;

			h_pmx = p_tree->InsertItem(pmx_id, i,i, TVI_ROOT, TVI_LAST);
			if(h_pm1 == NULL)		h_pm1 = h_pmx;

			if(bActive__PRE_ISE)
			{
				h_rcp = p_tree->InsertItem("Pre_Recipe",  i,i, h_pmx, TVI_LAST);
				p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);
			}

			h_rcp = p_tree->InsertItem("Main_Recipe", i,i, h_pmx, TVI_LAST);
			p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);

			if(bActive__POST_ISE)
			{
				h_rcp = p_tree->InsertItem("Post_Recipe", i,i, h_pmx, TVI_LAST);
				p_tree->InsertItem("",  i,i, h_rcp, TVI_LAST);
			}
		}
	}

	if(h_pm1 != NULL)			
	{
		p_tree->Expand(h_pm1, TVE_EXPAND);
	}
}


// ...
int CDlg__PMx_Recipe_Select
::Set_Parameter(const int module_id)
{
	Init__Tree_Table_Of_PMx_Recipe();
	return 1;
}

int CDlg__PMx_Recipe_Select
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	Update__PMx_Recipe_Channel();

	// ...
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	mCtrl__SEL_PMx_ID.SetWindowPos(&wndTop, 2, 2,  (wx-6), 26, SWP_SHOWWINDOW);
	mTree__PMx_Recipe.SetWindowPos(&wndTop, 2, 30, (wx-6), (wy-36), SWP_SHOWWINDOW);
	MoveWindow(sx,sy,wx,wy,true);
	
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__PMx_Recipe_Select
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}

int  CDlg__PMx_Recipe_Select::Update__PMx_Recipe_Channel()
{
	CString pmx_name;
	CString rcp_pre;
	CString rcp_main;
	CString rcp_post;

	CString key_name;
	CString ch_data;

	int i_limit;
	int i;

	// PMx ...
	{
		i_limit = iPM_SIZE;
	
		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			pmx_name.Format("PM%1d", id);

			// 1. PRE
			{
				key_name.Format(pKEY__CH_RECIPE_PRE_PM_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_pre = ch_data;
			}
			// 2. MAIN
			{
				key_name.Format(pKEY__CH_RECIPE_MAIN_PM_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_main = ch_data;
			}
			// 3. POST
			{
				key_name.Format(pKEY__CH_RECIPE_POST_PM_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_post = ch_data;
			}

			Set__Recipe_Of_MDx(pmx_name, rcp_pre,rcp_main,rcp_post, true,false);
		}
	}
	// LLx ...
	{
		i_limit = iLL_SIZE;

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			pmx_name.Format("LL%1d", id);

			// 1. PRE
			{
				key_name.Format(pKEY__CH_RECIPE_PRE_LL_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_pre = ch_data;
			}
			// 2. MAIN
			{
				key_name.Format(pKEY__CH_RECIPE_MAIN_LL_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_main = ch_data;
			}
			// 3. POST
			{
				key_name.Format(pKEY__CH_RECIPE_POST_LL_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				rcp_post = ch_data;
			}

			Set__Recipe_Of_MDx(pmx_name, rcp_pre,rcp_main,rcp_post, false,true);
		}
	}
	return 1;
}

// ...
void CDlg__PMx_Recipe_Select::OnBnClickedBtn__PMx_Recipe()
{
	printf("CDlg__PMx_Recipe_Select::OnBnClickedBtn__PMx_Recipe() \n");

	Change__PMx_Recipe();
}

void CDlg__PMx_Recipe_Select::OnNMClickTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult)
{

	*pResult = 0;
}
void CDlg__PMx_Recipe_Select::OnNMDblclkTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult)
{
	printf("CDlg__PMx_Recipe_Select::OnNMDblclkTree__PMx_Recipe() \n");

	Change__PMx_Recipe();

	*pResult = 0;
}
void CDlg__PMx_Recipe_Select::OnTvnSelchangedTree__PMx_Recipe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// ...
	{
		CTreeCtrl *p_table = &mTree__PMx_Recipe;

		HTREEITEM h_node = pNMTreeView->itemNew.hItem;
		HTREEITEM h_pmx  = h_node;

		while(h_node != NULL)
		{
			h_pmx  = h_node;
			h_node = p_table->GetParentItem(h_pmx);
		}

		if(h_pmx == NULL)
		{
			printf("CDlg__PMx_Recipe_Select::OnTvnSelchangedTree__PMx_Recipe() \n");
			printf(" ** Node : No Selection ! \n");
		}
		else
		{
			CString str_item = p_table->GetItemText(h_pmx);
			mCtrl__SEL_PMx_ID.SetWindowText(str_item);

			pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(pKEY__CH_CURRENT_PM_ID, str_item);
		}	
	}

	*pResult = 0;
}

HTREEITEM CDlg__PMx_Recipe_Select
::Get__Node_Of_MDx(const CString& md_name)
{
	HTREEITEM h_root = mTree__PMx_Recipe.GetRootItem();

	if(h_root == NULL)
	{
		printf(" ** Error (No Node) : %s \n", md_name);				
		return NULL;
	}

	// ...
	CString str_item;
	int i_count = 0;

	do
	{
		str_item = mTree__PMx_Recipe.GetItemText(h_root);

		if(str_item.CompareNoCase(md_name) == 0)
		{
			return h_root;
		}

		h_root = mTree__PMx_Recipe.GetNextSiblingItem(h_root);
	}
	while(h_root);

	printf(" ** Error (No Search) : %s \n", md_name);				
	return NULL;
}
int CDlg__PMx_Recipe_Select
::Get__Recipe_Of_MDx(const CString& md_name, 
					 CString& rcp_pre, 
					 CString& rcp_main, 
					 CString& rcp_post)
{
	// ...
	{
		rcp_pre  = "";
		rcp_main = "";
		rcp_post = "";
	}

	// ...
	HTREEITEM h_node = Get__Node_Of_MDx(md_name);
	if(h_node == NULL)			return -1;

	HTREEITEM h_child = NULL;

	// 1. Pre-Recipe
	if(bActive__PRE_ISE)
	{
		h_child = mTree__PMx_Recipe.GetChildItem(h_node);
		if(h_child)
		{
			HTREEITEM h_sub = mTree__PMx_Recipe.GetChildItem(h_child);
			rcp_pre = mTree__PMx_Recipe.GetItemText(h_sub);
		}
	}
	// 2. Main-Recipe
	{
		if(h_child == NULL)			h_child = mTree__PMx_Recipe.GetChildItem(h_node);
		else						h_child = mTree__PMx_Recipe.GetNextSiblingItem(h_child);

		if(h_child)
		{
			HTREEITEM h_sub = mTree__PMx_Recipe.GetChildItem(h_child);
			rcp_main = mTree__PMx_Recipe.GetItemText(h_sub);
		}
	}
	// 3. Post-Recipe
	if(bActive__POST_ISE)
	{
		if(h_child == NULL)			h_child = mTree__PMx_Recipe.GetChildItem(h_node);
		else						h_child = mTree__PMx_Recipe.GetNextSiblingItem(h_child);
		
		if(h_child)
		{
			HTREEITEM h_sub = mTree__PMx_Recipe.GetChildItem(h_child);
			rcp_post = mTree__PMx_Recipe.GetItemText(h_sub);
		}
	}

	return 1;
}
int CDlg__PMx_Recipe_Select
::Set__Recipe_Of_MDx(const CString& md_name, 
					 const CString& rcp_pre, 
					 const CString& rcp_main, 
					 const CString& rcp_post,
					 const bool active_pm,
					 const bool active_ll)
{
	printf(" * CDlg__PMx_Recipe_Select::Set__Recipe_Of_MDx() <- [%s] \n", md_name);

	HTREEITEM h_node = Get__Node_Of_MDx(md_name);
	if(h_node == NULL)			return -1;

	printf(" ** rcp_pre  <- [%s] \n", rcp_pre );
	printf(" ** rcp_main <- [%s] \n", rcp_main);
	printf(" ** rcp_post <- [%s] \n", rcp_post);

	// ...
	HTREEITEM h_child = NULL;

	// 1. Pre-Recipe
	if(bActive__PRE_ISE)
	{
		h_child = mTree__PMx_Recipe.GetChildItem(h_node);
		if(h_child)
		{
			HTREEITEM h_rcp  = mTree__PMx_Recipe.GetChildItem(h_child);
			CString str_data = mTree__PMx_Recipe.GetItemText(h_rcp);

			if(str_data != rcp_pre)		
				mTree__PMx_Recipe.SetItemText(h_rcp, rcp_pre);
		}
	}
	// 2. Main-Recipe
	{
		if(h_child == NULL)			h_child = mTree__PMx_Recipe.GetChildItem(h_node);
		else						h_child = mTree__PMx_Recipe.GetNextSiblingItem(h_child);

		if(h_child)
		{
			HTREEITEM h_rcp  = mTree__PMx_Recipe.GetChildItem(h_child);
			CString str_data = mTree__PMx_Recipe.GetItemText(h_rcp);

			if(str_data != rcp_main)		
				mTree__PMx_Recipe.SetItemText(h_rcp, rcp_main);
		}
	}
	// 3. Post-Recipe
	if(bActive__POST_ISE)
	{
		h_child = mTree__PMx_Recipe.GetNextSiblingItem(h_child);
		if(h_child)
		{
			HTREEITEM h_rcp  = mTree__PMx_Recipe.GetChildItem(h_child);
			CString str_data = mTree__PMx_Recipe.GetItemText(h_rcp);

			if(str_data != rcp_post)		
				mTree__PMx_Recipe.SetItemText(h_rcp, rcp_post);
		}
	}

	if(active_pm)
	{
		int pm_id = MACRO__Get__PMC_ID(md_name);
		CString key_name;

		key_name.Format(pKEY__CH_RECIPE_PRE_PM_X, pm_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_pre);

		key_name.Format(pKEY__CH_RECIPE_MAIN_PM_X, pm_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_main);

		key_name.Format(pKEY__CH_RECIPE_POST_PM_X, pm_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_post);
	}
	else if(active_ll)
	{
		int ll_id = MACRO__Get__LLx_ID(md_name);
		CString key_name;

		key_name.Format(pKEY__CH_RECIPE_PRE_LL_X, ll_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_pre);

		key_name.Format(pKEY__CH_RECIPE_MAIN_LL_X, ll_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_main);

		key_name.Format(pKEY__CH_RECIPE_POST_LL_X, ll_id);
		pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(key_name, rcp_post);
	}
	return 1;
}

int CDlg__PMx_Recipe_Select
::Change__PMx_Recipe()
{
	UpdateData(TRUE);

	CString str_pmx;
	mCtrl__SEL_PMx_ID.GetWindowText(str_pmx);

	// ...
	CString str__pre_rcp  = "";
	CString str__main_rcp = "";
	CString str__post_rcp = "";

	Get__Recipe_Of_MDx(str_pmx, str__pre_rcp,str__main_rcp,str__post_rcp);

	// ...
	CString str__pre_sub_dir;
	CString str__main_sub_dir;
	CString str__post_sub_dir;
	CString str_data;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_PRE_SUB_DIR, str_data);
	if(str_data.GetLength() < 1)			str__pre_sub_dir = "PRE";
	else									str__pre_sub_dir = str_data;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_MAIN_SUB_DIR, str_data);
	if(str_data.GetLength() < 1)			str__main_sub_dir = "MAIN";
	else									str__main_sub_dir = str_data;

	pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_POST_SUB_DIR, str_data);
	if(str_data.GetLength() < 1)			str__post_sub_dir = "POST";
	else									str__post_sub_dir = str_data;

	// ...
	CDlg__Process_Recipe_Select dlg;

	bool active_pm = false;
	bool active_ll = false;

	dlg.iREAL_MODE = iREAL_MODE;

	int ll_id = MACRO__Get__LLx_ID(str_pmx);
	if(ll_id > 0)	
	{
		active_ll = true;

		dlg.bActive__LLx  = active_ll;
		dlg.iPara__PMx_ID = 1;
	}
	else
	{
		active_pm = true;

		dlg.iPara__PMx_ID = MACRO__Get__PMC_ID(str_pmx);
	}
	
	dlg.bActive__PRE_ISE  = bActive__PRE_ISE;
	dlg.bActive__POST_ISE = bActive__POST_ISE;

	dlg.sPara__PMx_Info = str_pmx;
	
	dlg.sPara__PRE_RCP      = str__pre_rcp;
	dlg.sPara__PRE_SUB_DIR  = str__pre_sub_dir;
	
	dlg.sPara__MAIN_RCP     = str__main_rcp;
	dlg.sPara__MAIN_SUB_DIR = str__main_sub_dir;
	
	dlg.sPara__POST_RCP     = str__post_rcp;
	dlg.sPara__POST_SUB_DIR = str__post_sub_dir;

	if(dlg.DoModal() == IDOK)
	{
		printf("CDlg__PMx_Recipe_Select::Change__PMx_Recipe() - OK ! \n");

		// PRE ...
		{
			CString dir_sub   = dlg.sPara__PRE_SUB_DIR;
			CString file_name = dlg.sPara__PRE_RCP;

			if(file_name.GetLength() > 0)
			{
				dir_sub += "\\";

				if(file_name.Find(dir_sub) == 0)		str__pre_rcp = file_name;
				else									str__pre_rcp.Format("%s%s", dir_sub,file_name);
			}
			else
			{
				str__pre_rcp = "";
			}

			printf(" ** pre_rcp : [%s] \n", str__pre_rcp);
			printf("   ** [%s] : [%s] \n",  dir_sub, file_name);
		}
		// MAIN ...
		{
			CString dir_sub   = dlg.sPara__MAIN_SUB_DIR;
			CString file_name = dlg.sPara__MAIN_RCP;

			if(file_name.GetLength() > 0)
			{
				dir_sub += "\\";

				if(file_name.Find(dir_sub) == 0)		str__main_rcp = file_name;
				else									str__main_rcp.Format("%s%s", dir_sub,file_name);
			}
			else
			{
				str__main_rcp = "";
			}

			printf(" ** main_rcp : [%s] \n", str__main_rcp);
			printf("   ** [%s] : [%s] \n",   dir_sub, file_name);
		}
		// POST ...
		{
			CString dir_sub   = dlg.sPara__POST_SUB_DIR;
			CString file_name = dlg.sPara__POST_RCP;

			if(file_name.GetLength() > 0)
			{
				dir_sub += "\\";

				if(file_name.Find(dir_sub) == 0)		str__post_rcp = file_name;
				else									str__post_rcp.Format("%s%s", dir_sub,file_name);
			}
			else
			{
				str__post_rcp = "";
			}

			printf(" ** post_rcp : [%s] \n", str__post_rcp);
			printf("   ** [%s] : [%s] \n",   dir_sub, file_name);
		}

		Set__Recipe_Of_MDx(str_pmx, str__pre_rcp,str__main_rcp,str__post_rcp, active_pm,active_ll);
	}
	else
	{
		printf("CDlg__PMx_Recipe_Select::Change__PMx_Recipe() - CANCEL ! \n");
	}

	return 1;
}
