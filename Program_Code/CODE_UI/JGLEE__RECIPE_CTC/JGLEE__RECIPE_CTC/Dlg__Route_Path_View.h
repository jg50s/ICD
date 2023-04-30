#pragma once
#include "afxcmn.h"


#define _PROCES_PATH__SIZE				10


// CDlg__Route_Path_View dialog

class CDlg__Route_Path_View : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_Path_View)

public:
	CDlg__Route_Path_View(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_Path_View();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_PATH_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	// ...
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
									 const CStringArray& l_bm_slot);

	HTREEITEM Add__PROCESSx_To_Tree_Route(CTreeCtrl* p_tree,
										  HTREEITEM h_root,
										  HTREEITEM h_after,
										  const CString& str_category,
										  const CStringArray& l_pmx_name,
										  const CStringArray& l_pre_rcp,
										  const CStringArray& l_main_rcp,
										  const CStringArray& l_post_rcp);

	HTREEITEM Add__LLx_PRC_To_Tree_Route(CTreeCtrl* p_tree,
										 HTREEITEM h_root,
										 HTREEITEM h_after,
										 const int active_in_mode,
										 const CStringArray& l_ll_prc_id,
										 const CStringArray& l_ll_prc_pre,
										 const CStringArray& l_ll_prc_main,
										 const CStringArray& l_ll_prc_post);

	HTREEITEM Add__LOOPx_PRC_To_Tree_Route(CTreeCtrl* p_tree,
										   HTREEITEM h_root,
										   HTREEITEM h_after,
										   const int active_in_mode,
										   const CStringArray& l_loop_prc_id,
										   const CStringArray& l_loop_prc_repeat);

	HTREEITEM Add__STx_To_Tree_Route(CTreeCtrl* p_tree,
									 HTREEITEM h_root,
									 HTREEITEM h_after,
									 const CStringArray& l_st_id,
									 const CStringArray& l_st_mode,
									 const CStringArray& l_st_slot,
									 const CStringArray& l_st_sec,
									 const CStringArray& l_st_n2_purge);
	//

private:
	CTreeCtrl mTree__Route_Path;
	CImageList mImageList__Module_List;


public:
	CString sALx__Title;
	CStringArray Para_ALx__List_ID;
	CStringArray Para_ALx__List_ANGLE;
	CStringArray Para_ALx__List_SLOT;

	CString sBMx_IN__Title;
	CStringArray Para_BMx_IN__List_ID;
	CStringArray Para_BMx_IN__List_MODE;
	CStringArray Para_BMx_IN__List_SLOT;

	CString sPROCESS__Title;
	int iPara_PATH__SIZE;
	CStringArray Para_PATHx__List_PMx_ID[_PROCES_PATH__SIZE];
	CStringArray Para_PATHx__List_RCP_PRE[_PROCES_PATH__SIZE];
	CStringArray Para_PATHx__List_RCP_MAIN[_PROCES_PATH__SIZE];
	CStringArray Para_PATHx__List_RCP_POST[_PROCES_PATH__SIZE];

	CString sLLx_PRC__Title;
	CStringArray Para_LLx_PRC__List_ID;
	CStringArray Para_LLx_PRC__List_PRE;
	CStringArray Para_LLx_PRC__List_MAIN;
	CStringArray Para_LLx_PRC__List_POST;

	CString sLOOPx_PRC__Title;
	CStringArray Para_LOOPx_PRC__List_ID;
	CStringArray Para_LOOPx_PRC__List_REPEAT;

	CString sBMx_OUT__Title;
	CStringArray Para_BMx_OUT__List_ID;
	CStringArray Para_BMx_OUT__List_MODE;
	CStringArray Para_BMx_OUT__List_SLOT;

	CString sSTx__Title;
	CStringArray Para_STx__List_ID;
	CStringArray Para_STx__List_MODE;
	CStringArray Para_STx__List_SLOT;
	CStringArray Para_STx__List_SEC;
	CStringArray Para_STx__List_N2_PURGE;
};
