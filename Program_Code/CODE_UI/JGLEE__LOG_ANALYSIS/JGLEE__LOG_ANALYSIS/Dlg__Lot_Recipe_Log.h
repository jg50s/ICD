#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "CCls__REPORT_CTRL.h"
#include "CLS__Route_Info.h"


// ...
class CLS__Slot_Process_Info
{
public:
	CString sRef__SlotID;

	CStringArray sList__Module;
	CStringArray sList__Log_Info;
	CStringArray sList__Result;

public:
	CLS__Slot_Process_Info()
	{

	}
	~CLS__Slot_Process_Info()
	{

	}

	void Load__Slot_Process_Info(const CStringArray& l_module,
								 const CStringArray& l_log_info,
								 const CStringArray& l_result)
	{
		sList__Module.Copy(l_module);
		sList__Log_Info.Copy(l_log_info);
		sList__Result.Copy(l_result);
	}
};
class CLS__Slot_Process_Ctrl
{
private:
	CPtrArray pList_DB;

	CLS__Slot_Process_Info* _Get_Addr__Slot_Process_Into(const CString& str_slotid)
	{
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Process_Info *p_info = (CLS__Slot_Process_Info*) pList_DB[i];

			if(p_info->sRef__SlotID.CompareNoCase(str_slotid) != 0)
				continue;

			return p_info;
		}
		return NULL;
	}

public:
	CLS__Slot_Process_Ctrl()
	{

	}
	~CLS__Slot_Process_Ctrl()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Process_Info *p_info = (CLS__Slot_Process_Info*) pList_DB[i];
			delete p_info;
		}
		pList_DB.RemoveAll();
	}
	void Load__Slot_Process_Info(const CString& str_slotid,
							     const CStringArray& l_module,
								 const CStringArray& l_log_info,
								 const CStringArray& l_result)
	{
		CLS__Slot_Process_Info* p_info = _Get_Addr__Slot_Process_Into(str_slotid);

		if(p_info == NULL)
		{
			p_info = new CLS__Slot_Process_Info;
			pList_DB.Add(p_info);

			p_info->sRef__SlotID = str_slotid;
		}

		p_info->Load__Slot_Process_Info(l_module,l_log_info,l_result);
	}

	CLS__Slot_Process_Info*  Get_Addr__Slot_Process_Info(const CString& str_slotid)
	{
		return _Get_Addr__Slot_Process_Into(str_slotid);
	}

	int Get_Addr__Log_Info_Of_MDx(const CString& md_name,
								  CStringArray& l__slot_id,
								  CStringArray& l__log_info)
	{
		l__slot_id.RemoveAll();
		l__log_info.RemoveAll();

		// ...
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Process_Info *p_info = (CLS__Slot_Process_Info*) pList_DB[i];

			int k_limit = p_info->sList__Module.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				if(p_info->sList__Module[k].Find(md_name) < 0)
					continue;

				l__slot_id.Add(p_info->sRef__SlotID);
				l__log_info.Add(p_info->sList__Log_Info[k]);
			}
		}
		return 1;
	}
};


// CDlg__Lot_Recipe_Log dialog

class CDlg__Lot_Recipe_Log : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Lot_Recipe_Log)

public:
	CDlg__Lot_Recipe_Log(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Lot_Recipe_Log();

// Dialog Data
	enum { IDD = IDD_DLG__LOT_RECIPE_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	afx_msg void OnBnClickedBtn__Save_All_CSV();

	afx_msg void OnBnClickedBtn__Template_Ctrl_PM1();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM2();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM3();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM4();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM5();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM6();

	afx_msg void OnBnClickedBtn__Template_Ctrl_LL1();
	afx_msg void OnBnClickedBtn__Template_Ctrl_LL2();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__LOTID_DATA;
	CButton mBtn__PORTID_DATA;

	// ..
	CButton mBtn__Template_Name_PM1;
	CButton mBtn__Template_Name_PM2;
	CButton mBtn__Template_Name_PM3;
	CButton mBtn__Template_Name_PM4;
	CButton mBtn__Template_Name_PM5;
	CButton mBtn__Template_Name_PM6;

	CButton mBtn__Template_Name_LL1;
	CButton mBtn__Template_Name_LL2;

	//
	CButton mCheck_PM1;
	CButton mCheck_PM2;
	CButton mCheck_PM3;
	CButton mCheck_PM4;
	CButton mCheck_PM5;
	CButton mCheck_PM6;

	CButton mCheck_LL1;
	CButton mCheck_LL2;

	//
	CButton mBtn__SAVE_ALL_CSV;

	void _Fnc__Template_Sel_MDx(const int pm_id, const int ll_id);

	CString _Get__Template_Name_Of_PMx(const int pm_id);
	CString _Get__Template_Name_Of_LLx(const int ll_id);

	// ...
	CButton mBtn__Lot_Recipe;

	int _Upload__Route_File(const CString& file_path);
	int _Get__Route_Cmmd(const CString& cmmd);

	// ...
	CTreeCtrl  mTree__Lot_Recipe;
	CImageList mImg_Tree;

	HTREEITEM _Add__PROCESSx_To_Tree_Route(CTreeCtrl* p_tree,
											HTREEITEM h_root,
											HTREEITEM h_after,
											const CStringArray& l_pmx_name,
											const CStringArray& l_pre_rcp,
											const CStringArray& l_main_rcp,
											const CStringArray& l_post_rcp);
	HTREEITEM _Add__LLx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
											HTREEITEM h_root,
											HTREEITEM h_after,
											const CStringArray& l_llx_id,
											const CStringArray& l_pre_rcp,
											const CStringArray& l_main_rcp,
											const CStringArray& l_post_rcp);
	HTREEITEM _Add__LOOPx_PROC_To_Tree_Route(CTreeCtrl* p_tree,
										 	 HTREEITEM h_root,
											 HTREEITEM h_after,
											 const CStringArray& l_loop_id,
											 const CStringArray& l_loop_repeat);

	HTREEITEM _Add__ALx_To_Tree_Route(CTreeCtrl* p_tree,
										HTREEITEM h_root,
										HTREEITEM h_after,
										const CStringArray& l_al_id,
										const CStringArray& l_al_angle,
										const CStringArray& l_al_slot);
	HTREEITEM _Add__LLx_To_Tree_Route(CTreeCtrl* p_tree,
										HTREEITEM h_root,
										HTREEITEM h_after,
										const int active_in_mode,
										const CStringArray& l_bm_id,
										const CStringArray& l_bm_mode,
										const CStringArray& l_bm_slot);
	HTREEITEM _Add__STx_To_Tree_Route(CTreeCtrl* p_tree,
										HTREEITEM h_root,
										HTREEITEM h_after,
										const CStringArray& l_st_id,
										const CStringArray& l_st_mode,
										const CStringArray& l_st_slot,
										const CStringArray& l_st_sec);

	// ...
	CReportCtrl mList__Slot_Info;

	void _Make__Slot_List();
	void _Add__Slot_List(const CStringArray& l_slot);

	void _Update__MDx_Of_Slot_List();
	int  _Get__MDx_ID_Of_Slot_List(const CString& md_name);

	CString _Get__ID_Of_Slot_List(const int r_index);

	// ...
	CLS__Slot_Process_Ctrl mSlot_Proc;

	void _Update__Slot_Info();
	//

public:
	CString sDir_Root;
	CString sDir_Lot;

	CString sPara__LotID;
	CString sPara__PortOD;

	CStringArray sList__Slot_ID;

	CString sPara__Template_Name_PM1;
	CString sPara__Template_Name_PM2;
	CString sPara__Template_Name_PM3;
	CString sPara__Template_Name_PM4;
	CString sPara__Template_Name_PM5;
	CString sPara__Template_Name_PM6;

	CString sPara__Template_Name_LL1;
	CString sPara__Template_Name_LL2;
	afx_msg void OnDestroy();
};
