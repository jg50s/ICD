#pragma once

#include "Interface_Header.h"
#include "resource.h"

#include "Part_Recipe.h"
#include "Dlg__Route_STD__DB_Info.h"
#include "afxwin.h"


#define _DB_INFO__PRCx_SIZE				10


// CDlg__Route_STD dialog

class CDlg__Route_STD : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_STD)

public:
	CDlg__Route_STD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_STD();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_STD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnHdnItemclickList__File_List(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn_RouteFile_Update();
	afx_msg void OnBnClickedBtn_RouteFile_New();
	afx_msg void OnBnClickedBtn_RouteFile_Undo();
	afx_msg void OnBnClickedBtn_RouteFile_Save();
	afx_msg void OnBnClickedBtn_RouteFile_SaveAs();
	afx_msg void OnBnClickedBtn_RouteFile_Delete();

	afx_msg void OnBnClickedBtn_CurRoute_Update();
	afx_msg void OnLvnColumnclickList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList_RouteTable(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn_RouteEdit_Mode();
	afx_msg void OnLvnColumnclickList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList_RouteEdit(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn_RouteEdit_STx_Use();
	afx_msg void OnBnClickedBtn_PathView();

	afx_msg void OnBnClickedBtn_PM1_RCP_Update();
	afx_msg void OnBnClickedBtn_PM2_RCP_Update();
	afx_msg void OnBnClickedBtn_PM3_RCP_Update();
	afx_msg void OnBnClickedBtn_PM4_RCP_Update();
	afx_msg void OnBnClickedBtn_PM5_RCP_Update();
	afx_msg void OnBnClickedBtn_PM6_RCP_Update();
	afx_msg void OnBnClickedBtn_PMx_PRE_Update();
	afx_msg void OnBnClickedBtn_PMx_MAIN_Update();
	afx_msg void OnBnClickedBtn_PMx_POST_Update();

	afx_msg void OnLbnSelchangeList_PreRCP();
	afx_msg void OnLbnSelchangeList_MainRCP();
	afx_msg void OnLbnSelchangeList_PostRCP();

	DECLARE_MESSAGE_MAP()

	// ...
	int  Sort__Route_File(const int col);
	bool m_bResultDirect;
	//

private:
	BOOL bActive__Recipe_Changed;

	CString mStr_Edit__Main_Msg;
	CString mStr_Edit__Error_Msg;

	BOOL bRouteEdit__Edit_Mode;

	CButton mCtrl_RouteFile_Update;
	
	CPart__Rcp_New    mCtrl_RouteFile_New;
	CPart__Rcp_Undo   mCtrl_RouteFile_Undo;
	CPart__Rcp_Save   mCtrl_RouteFile_Save;
	CPart__Rcp_SaveAs mCtrl_RouteFile_SaveAs;
	CPart__Rcp_Delete mCtrl_RouteFile_Delete;
	
	// ...
	CListCtrl  mCtrl__Route_List_Table;
	CImageList mImg__Route_List_Table;

	CStringArray sList__RouteFile_Name;
	CStringArray sList__RouteFile_Date;

	// ...
	CButton mCtrl__Current_Route_File_Name;
	CString mStr__Current_Route_File_Date;
	CButton mCtrl_RouteFile_Size;
	
	CButton mCtrl_RouteEdit_Mode;
	CButton mCtrl_RouteEdit_PathID;
	CButton mCtrl_RouteEdit_FileName;
	CButton mCtrl_RouteEdit_FileDate;

	CListCtrl  mCtrl__Route_Edit_Table;
	CImageList mImg__Route_Edit_Table;
	
	CButton mCtrl_RouteEdit_STx_Use;
	CButton mCtrl__Rcp_Type;

	CButton mCtrl_SEL_PMx;
	int iPMx_SEL;
	CButton mCtrl_PM1_RCP;
	CButton mCtrl_PM2_RCP;
	CButton mCtrl_PM3_RCP;
	CButton mCtrl_PM4_RCP;
	CButton mCtrl_PM5_RCP;
	CButton mCtrl_PM6_RCP;
	
	CButton mCtrl_PMx_PRE_RCP;
	CListBox mList_PMx_PRE_RCP;
	CButton mCtrl_PMx_MAIN_RCP;
	CListBox mList_PMx_MAIN_RCP;
	CButton mCtrl_PMx_POST_RCP;
	CListBox mList_PMx_POST_RCP;

	int iPMx_SIZE;
	CString sRCP__DIR_PRE;
	CString sRCP__DIR_MAIN;
	CString sRCP__DIR_POST;

	// ...
	int iShow_Count;
	CString sPMx_NAME[10];
	//

	// ...
	BOOL Msg_OnInitDialog();
	BOOL Fnc_OnInitDialog();

	//
	void Make__Route_List_Table();
	void Update__RouteFile_List();
	void Update__RouteFile_List(const CString& file_name,
								CString& file_date);
	void Update__RouteFile_List(const CString& file_name,
								CString& file_date, 
								const CStringArray& l_file,
								const CStringArray& l_date);

	void Make__Route_Edit_Table();
	void Init__Route_Edit_Table();
	void Update__Route_Edit_Table(CListCtrl *p_table,
								  CStringArray* p_module_list[], 
								  CStringArray* p_recipe_list[],
								  const int step_count,
								  const int col_id);
	void Change__Route_Edit_Table(CListCtrl *p_table,
								  const CString& pmx_name,
								  const CString& rcp_name,
								  const int path_index,
								  const int col_id);

	//
	int  Undo__Route_File(const CString& file_name,
						  const CString& file_date,
						  const BOOL edit_mode = TRUE);

	int  Upload__Route_File_Of_New_Type(const CString& file_data);
	int  Get__Route_Cmmd_Of_New_Type(const CString& cmmd);

	int  Upload__Route_File_Of_Old_Type(const CString& file_data);
	int  Get__Route_Cmmd_Of_Old_Type(const CString& cmmd);

	//
	void Click__PMx_RCP(const int pmx_id);
	
	void Set__Route_Edit_Mode(BOOL edit_mode);
	void Select__RouteEdit_PathID(const int path_id);

	void Change__PMx_RCP_Of_Route_Edit(CListBox  *p_rcp_list, 
									   const int col_id,
									   const CString& dir_sub);

	void Init_RouteFile(const CString& file_name);
	int  Save_RouteFile(const CString& file_name);

	CString Get__RouteEdit_FileData();
	int Check__RouteEdit_FileData();
	int Check__Module_Name(const CString& check_module, const CStringArray& l_module);

	int Get__RouteEdit__Process_Path(CStringArray *pl__pmx_name,
									 CStringArray *pl__rcp_pre,
									 CStringArray *pl__rcp_main,
									 CStringArray *pl__rcp_post);
	int Update__RouteEdit__STx_To_DB();
	//

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();

	// ...
	BOOL bRCP_TYPE__NEW;
	BOOL bSCH_TYPE__CONFIG;

	_DB_Info__Category mDB__ALx;
	_DB_Info__Category mDB__LLx_IN;
	int iSIZE__PRC_PATH;
	_DB_Info__Category mDB__PRCx[_DB_INFO__PRCx_SIZE];
	_DB_Info__Category mDB__LLx_PRC;
	_DB_Info__Category mDB__LOOPx_PRC;
	_DB_Info__Category mDB__LLx_OUT;
	_DB_Info__Category mDB__STx;
};
