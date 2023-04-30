#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxcmn.h"

#include "Part_Recipe.h"
#include "DragDropTreeCtrl.h"
#include "afxwin.h"


// ...
class CDB__Module_Info
{
public:
	CDB__Module_Info()
	{

	}

	// ...
	CString sTitle;
	int iImg_ID;
	int iSel_ID;

	CStringArray sList_Item;
	CUIntArray iList_ImgID;
	CUIntArray iList_SelID;
};
class CDB__Category_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_Module;		// CDB__Module_Info

public:
	CString sTitle;
	int iImg_ID;
	int iSel_ID;

	// ...
	CDB__Category_Info();
	~CDB__Category_Info();

	int Load__Module_Info(const CDB__Module_Info& db_info);

	int Get__Module_Size();
	CDB__Module_Info* Get__Module_Info(const int db_index);
};


// ...
class CDB__PMx_TREE_INFO
{
public:
	HTREEITEM hTREE_NODE;

	int iPMx_ID;
	CString sPMx_NAME;
};

class CDB__PMx_TREE_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__PMx_TREE;

public:
	CDB__PMx_TREE_CTRL()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CDB__PMx_TREE_CTRL()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear_INFO()
	{
		EnterCriticalSection(&mCS_LOCK);
		
		int i_limit = pList__PMx_TREE.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CDB__PMx_TREE_INFO* p_db = (CDB__PMx_TREE_INFO*) pList__PMx_TREE[i];
			delete p_db;
		}
		pList__PMx_TREE.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Add_INFO(const HTREEITEM h_item, const int pm_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CDB__PMx_TREE_INFO* p_db = new CDB__PMx_TREE_INFO;
		pList__PMx_TREE.Add(p_db);

		p_db->hTREE_NODE = h_item;
		p_db->iPMx_ID    = pm_id;
		p_db->sPMx_NAME  = "";

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Change_NAME(const int pm_id, const CString& pm_name)
	{
		EnterCriticalSection(&mCS_LOCK);

		int i_limit = pList__PMx_TREE.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CDB__PMx_TREE_INFO* p_db = (CDB__PMx_TREE_INFO*) pList__PMx_TREE[i];
			if(pm_id != p_db->iPMx_ID)		continue;

			p_db->sPMx_NAME = pm_name;
			break;
		}
	
		LeaveCriticalSection(&mCS_LOCK);
	}
	void Update_INFO(CTreeCtrl* p_tree)
	{
		EnterCriticalSection(&mCS_LOCK);

		int i_limit = pList__PMx_TREE.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CDB__PMx_TREE_INFO* p_db = (CDB__PMx_TREE_INFO*) pList__PMx_TREE[i];
			
			CString str_name;
			if(p_db->sPMx_NAME.GetLength() > 0)		str_name.Format("PM%1d  (%s)", p_db->iPMx_ID,p_db->sPMx_NAME);
			else									str_name.Format("PM%1d", p_db->iPMx_ID);

			p_tree->SetItemText(p_db->hTREE_NODE, str_name);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
};


// ...
#define _LLx__MAX							4

#define _ROUTE_TYPE__LLx_IN					1
#define _ROUTE_TYPE__LLx_OUT				2


class CDB__Route_Info
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_Category;			// CDB__Category_Info

public:
	CDB__Route_Info();
	~CDB__Route_Info();

	int Load__Category_Info(const CString& category_name, 
							const int category_imgid,
							const int category_selid);
	int Load__Module_Info(const CDB__Module_Info& db_info);

	int Get__Category_Size();
	CDB__Category_Info* Get__Category_Info(const int c_index);

	// ...
	CString Get__ALx_Of_Route_Info();
	CString Get__LLx_Of_Route_Info(const int ll_type);
	CString Get__STx_Of_Route_Info();	
	
	CString Get__PROCESSx_Of_Route_Info();
	CString Get__LLx_PROC_Of_Route_Info();	
	CString Get__LOOPx_PROC_Of_Route_Info();	
};


// CDlg__Route_EDIT dialog

class CDlg__Route_EDIT : public CDialog, public CLink__DragDrop
{
	DECLARE_DYNAMIC(CDlg__Route_EDIT)

public:
	CDlg__Route_EDIT(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_EDIT();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHdnItemclickList__File_List(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTree_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree__RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn_RouteEdit_Mode();
	afx_msg void OnBnClickedBtn_RouteEdit_Expand();
	afx_msg void OnBnClickedBtn_RouteEdit_Expand_X();
	afx_msg void OnBnClickedBtn_RouteEdit_Contract();

	afx_msg void OnBnClickedBtn_RouteEdit_Delete();
	afx_msg void OnBnClickedBtn_RouteEdit_Copy();
	afx_msg void OnBnClickedBtn_RouteEdit_Property();

	afx_msg void OnBnClickedBtn__File_Delete();
	afx_msg void OnBnClickedBtn_Refresh();
	afx_msg void OnBnClickedBtn_RouteFile_Upload();
	afx_msg void OnNMClickList_RouteFile(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn_New();
	afx_msg void OnBnClickedBtn_Undo();

	afx_msg void OnBnClickedBtn_Save();
	afx_msg void OnBnClickedBtn_SaveAs();

	DECLARE_MESSAGE_MAP()

	// ...
	int  Sort__Route_File(const int col);
	bool m_bResultDirect;
	//

private:
	// ...
	int iShow_Count;

	CString sPMx_NAME[10];
	CDB__PMx_TREE_CTRL mDB__PMx_TREE_CTRL;

	// ...
	CDragDropTreeCtrl mTree__Module_List;
	CImageList mImg__Module_List;

	CDragDropTreeCtrl mTree__Route_Edit;
	CImageList mImg__Route_Edit;

	/// ...
	CListCtrl mCtrl__RouteFile_List;
	CImageList mImg__RouteFile_List;

	CStringArray sList__RouteFile_Name;
	CStringArray sList__RouteFile_Date;

	// ...
	CPart__Rcp_New  mBtn__Route_New;
	CPart__Rcp_Undo mBtn__Route_Undo;

	CPart__Rcp_Save   mBtn__Route_Save;
	CPart__Rcp_SaveAs mBtn__Route_SaveAs;
	CPart__Rcp_Delete mBtn__Route_Delete;

	CButton mBtn__Rcp_Item_Delete;
	CButton mBtn__Rcp_Item_Property;

	// ...
	CButton mCtrl__Current_Route_File;
	CButton mCtrl__Route_File_Size;

	CButton mCtrl__RouteEdit_FileName;
	CButton mCtrl__RouteEdit_FileDate;

	CButton mCheck__Default_Route;
	CString mStr__Sys_Msg;

	CString mStr_Edit__Error_Msg;
	CButton mCtrl__RouteEdit_Mode;

	// ...
	CString sData__RCP_PRE;
	CString sData__RCP_MAIN;
	CString sData__RCP_POST;

	bool bActive__LLx_PROC;
	bool bActive__LOOPx_PROC;

	int  iLLx_MODE;
	int  iSIZE__LLx_IN;
	bool bACTIVE__LLx_IN[_LLx__MAX];
	int  iSIZE__LLx_OUT;
	bool bACTIVE__LLx_OUT[_LLx__MAX];

	int  iSIZE__ACTIVE_LLx_PROC;
	bool bACTIVE__ACTIVE_LLx_PROC[_LLx__MAX];

	// ...
	bool bACTIVE_DEFAULT__AL1_CTRL_CFG;
	bool bACTIVE_DEFAULT__AL1_SLOT_FIXED;

	bool bACTIVE_DEFAULT__AL1_SLOT01;
	bool bACTIVE_DEFAULT__AL1_SLOT02;

	// ...
	bool bACTIVE_DEFAULT__LLx_SLOT_FIXED;

	bool bACTIVE_DEFAULT__LLx_SLOT01[_LLx__MAX];
	bool bACTIVE_DEFAULT__LLx_SLOT02[_LLx__MAX];

	// ...
	bool bACTIVE__LLx_OUT_COOLING;

	// ...
	bool bACTIVE__STx_N2_PURGE;

	// ...
	BOOL Fnc_OnInitDialog();
	int  Check__RouteEdit_Mode();

	//
	void Make__RouteFile_List();

	void Update__RouteFile_List();
	void Update__RouteFile_List(const CString& s_name,
								CString& s_date);
	void Update__RouteFile_List(const CString& s_name,
								CString& s_date, 
								const CStringArray& l_file,
								const CStringArray& l_date);

	// ...
	void Add__Process_Path_To_RouteEdit(CTreeCtrl* p_tree,HTREEITEM h_upper_node, const CString& path_name);

	// ...
	HTREEITEM Add__XXX_To_Tree_Route(CTreeCtrl* p_tree_src,
									 HTREEITEM h_src, 
								     CTreeCtrl* p_tree_trg,
									 HTREEITEM h_root,
									 HTREEITEM h_after);
	HTREEITEM _Add__XXX_To_Tree_Route(CTreeCtrl* p_tree_src,
									  HTREEITEM h_src, 
									  CTreeCtrl* p_tree_trg,
									  HTREEITEM h_root,
									  HTREEITEM h_after,
									  const int src_img,
									  const int src_sel,
									  const int trg_img,
									  const int trg_sel);
	int _Change__Tree_Category(CTreeCtrl* p_tree, 
							   HTREEITEM h_src_category, 
							   HTREEITEM h_trg_category);

	HTREEITEM Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);
	HTREEITEM Add__LLx_IN_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);
	HTREEITEM Add__PMx_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after, const int pm_id = -1, const bool active_init = false);
	HTREEITEM Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);
	HTREEITEM Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);
	HTREEITEM Add__LLx_OUT_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);
	HTREEITEM Add__STx_To_Tree_Route(CTreeCtrl* p_tree,HTREEITEM h_root,HTREEITEM h_after);

	HTREEITEM Add__MODULEx_To_Tree_Route(CTreeCtrl* p_tree,
										 HTREEITEM h_root,
										 HTREEITEM h_after,
										 const CString& str_title,
										 const CString& str_module,
										 const int img_id,
										 const int lst_id,
										 const int lst_size);
	HTREEITEM Add__MODULEx_To_Tree_Route(CTreeCtrl* p_tree,
										 HTREEITEM h_root,
										 HTREEITEM h_after,
										 const CString& str_title,
										 const CString& str_module,
										 const int img_id,
										 const int lst_id,
										 const int lst_size,
										 const CStringArray& l_ll_name);

	HTREEITEM Add__PROCESSx_To_Tree_Route(const bool active_init,
										  CTreeCtrl* p_tree,
										  HTREEITEM h_root,
										  HTREEITEM h_after,
										  const CStringArray& l_pmx_name,
										  const CStringArray& l_pre_rcp,
										  const CStringArray& l_main_rcp,
										  const CStringArray& l_post_rcp);
	HTREEITEM Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
										  HTREEITEM h_root,
										  HTREEITEM h_after,
										  const CStringArray& l_llx_id,
										  const CStringArray& l_pre_rcp,
										  const CStringArray& l_main_rcp,
										  const CStringArray& l_post_rcp);
	HTREEITEM Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
										    HTREEITEM h_root,
										    HTREEITEM h_after,
										    const CStringArray& l_loop_id,
										    const CStringArray& l_loop_repeat);

	HTREEITEM Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,
									 HTREEITEM h_root,
									 HTREEITEM h_after,
									 const CStringArray& l_al_id,
									 const CStringArray& l_al_angle,
									 const CStringArray& l_al_slot);
	HTREEITEM Add__LLx_To_Tree_Route(CTreeCtrl* p_tree,
									 HTREEITEM h_root,
									 HTREEITEM h_after,
									 const int active_in_mode,
									 const CStringArray& l_bm_id,
									 const CStringArray& l_bm_mode,
									 const CStringArray& l_bm_slot,
									 const CStringArray& l_bm_cooling_sec);
	HTREEITEM Add__STx_To_Tree_Route(CTreeCtrl* p_tree,
									 HTREEITEM h_root,
									 HTREEITEM h_after,
									 const CStringArray& l_st_id,
									 const CStringArray& l_st_mode,
									 const CStringArray& l_st_slot,
									 const CStringArray& l_st_sec,
									 const CStringArray& l_st_n2_purge);

	int Check__Tree_Category(const int i_img);
	int Get__Tree_ModuleID(const int i_img,const int i_sel);

	HTREEITEM Get__Tree_Category(CTreeCtrl* p_tree);
	HTREEITEM Get__Tree_Category(CTreeCtrl* p_tree, HTREEITEM h_node);
	HTREEITEM Get__Tree_Pre_Category_Of_Process_X(CTreeCtrl* p_tree, HTREEITEM h_category);

	HTREEITEM Get__Tree_Module(CTreeCtrl* p_tree);
	HTREEITEM Get__Tree_Module(CTreeCtrl* p_tree, HTREEITEM h_node);
	
	int Check__Tree_Main_Module(CTreeCtrl* p_tree, const int img_id);
	int Check__Tree_Sub_Module(CTreeCtrl* p_tree, HTREEITEM h_main, const int img_id, const int md_id);
	int Get__Tree_Sub_Module(CTreeCtrl* p_tree, HTREEITEM h_main, CStringArray& l_md);

	HTREEITEM Get__Tree_Pos_Of_ALx(CTreeCtrl* p_tree);
	HTREEITEM Get__Tree_Pos_Of_PROCESSx(CTreeCtrl* p_tree, const int last_index = -1);
	HTREEITEM Get__Tree_Pos_Of_LLx_PROC(CTreeCtrl* p_tree);
	HTREEITEM Get__Tree_Pos_Of_LLx_IN(CTreeCtrl* p_tree);

	// ...
	BOOL bActive__RouteEdit_Mode;
	BOOL bActive__Recipe_Changed;

	void Change__Route_Edit_Mode(BOOL edit_mode);

	void Init__Route_Edit_Table();

	int  Undo__Route_File(const CString& file_name,
						  const CString& file_date,
						  const BOOL edit_mode = TRUE);
	int  Get__Route_Cmmd(const CString& cmmd);

	// ...
	int  Save__Route_Rcp(const CString& file_name);

	// ...
	int  Get__LLx_ID(const CString& llx_name)
	{
		CString cmp_name;
		int i;

		for(i=0; i<_LLx__MAX; i++)
		{
			int  id = i + 1;
			cmp_name.Format("LL%1d", id);
			
			if(cmp_name.CompareNoCase(llx_name) != 0)
			{
				continue;
			}
			return id;
		}
		return -1;
	}

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	int iPMx_SIZE;
	int iSTx_SIZE;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();

	// ...
	int Call__DragDrop(CTreeCtrl* p_tree, const HTREEITEM h_item, const POINT scr_pt);
};
