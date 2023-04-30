#pragma once

#include "Interface_Code.h"
#include "resource.h"

#include "CObj__PROCESS_STD__KEY_DEF.h"
#include "CCls__REPORT_CTRL.h"

#include "User_GridCtrl.h"
#include "CInfo__Rcp_Item.h"
#include "CInfo__Rcp_File.h"

#include "afxwin.h"
#include "afxcmn.h"


// CDlg__PROCESS_STD dialog

class CDlg__PROCESS_STD : public CDialog
{
	DECLARE_DYNAMIC(CDlg__PROCESS_STD)

public:
	CDlg__PROCESS_STD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__PROCESS_STD();

// Dialog Data
	enum { IDD = IDD_DLG__PROCESS_STD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnGridSelChanged(NMHDR* pNMHDR, LRESULT* pResult); 

	afx_msg void OnBnClickedCheck__Rcp_Type_Header();
	afx_msg void OnBnClickedCheck__Rcp_Type_Step();
	afx_msg void OnBnClickedCheck__Rcp_Type_Tolerance();

	afx_msg void OnBnClickedBtn__Node_Expand();
	afx_msg void OnBnClickedBtn__Node_Contract();

	afx_msg void OnBnClickedCheck__Rcp_Folder_Pre();
	afx_msg void OnBnClickedCheck__Rcp_Folder_Main();
	afx_msg void OnBnClickedCheck__Rcp_Folder_Post();

	afx_msg void OnNMClickList__File_Table(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtn__File_Refresh();
	afx_msg void OnBnClickedBtn__Send_File();

	afx_msg void OnBnClickedBtn__File_New();
	afx_msg void OnBnClickedBtn__File_Save();
	afx_msg void OnBnClickedBtn__File_SaveAs();
	afx_msg void OnBnClickedBtn__File_Delete();
	afx_msg void OnBnClickedBtn__File_CSV();
	afx_msg void OnBnClickedBtn__File_Undo();

	afx_msg void OnBnClickedBtn__Summary_View();
	afx_msg void OnBnClickedCheck__Summary_Save();

	afx_msg void OnBnClickedBtn__Step_Append();
	afx_msg void OnBnClickedBtn__Step_Copy();
	afx_msg void OnBnClickedBtn__Step_Move();
	afx_msg void OnBnClickedBtn__Step_Delete();

	DECLARE_MESSAGE_MAP()

	// ...
	UIX__FILE_LOG_CTRL xI_Log_Ctrl;

	//
	bool bActive__Show_Page;
	bool bActive__Rcp_item_Change;

	int  iItem_Height;
	bool bActive__PMx_LINK_USE[_CFG_PMx__SIZE];

	//
	bool bActive__Summary_Mode;
	bool bActive__Summary_User;

	int  iList__Summary_ID[_CFG__SUMMARY_ITEM_MAX];

	//
	int iDef__Rcp_Type__Line_ID;
	CString sDef__Rcp_Type__Check_Data;

	bool bActive__Interlock_Save;

	bool bActive__Interlock_Dll;
	CString sDef__Rcp_Interlock_Name;
	UIX__RCP_INTERLOCK_CTRL xI_Rcp_Interlock_Ctrl;

	//
	CString sDir__ROOT_UI;
	CString sDir__ROOT_INF;

	bool bActive__Item_Header;
	bool bShow__Item_Header;
	CString sDef__Item_Header_File;
	int  iDef__Item_Header_Width;

	bool bActive__Item_Step;
	bool bShow__Item_Step;
	CString sDef__Item_Step_File;
	int  iDef__Item_Step_Width;

	bool bActive__Item_Tolerance;
	bool bShow__Item_Tolerance;
	CString sDef__Item_Tolerance_File;
	int  iDef__Item_Tolerance_Width;

	//
	CString sDir__ROOT_EQP;

	bool bActive__Rcp_Pre;
	CString sDef__Rcp_Pre_Folder;

	bool bActive__Rcp_Main;
	CString sDef__Rcp_Main_Folder;

	bool bActive__Rcp_Post;
	CString sDef__Rcp_Post_Folder;

	CString sCur__Rcp__Folder;

	// ...
	CButton mCheck__Header_Type_Ctrl;
	CButton mCheck__Step_Type_Ctrl;
	CButton mCheck__Tolerance_Type_Ctrl;

	CButton mData__Sel_Step_Count;
	CButton mData__Sel_Para_Count;
	CButton mData__Sel_File_Name;
	CButton mData__Sel_Folder_Name;

	// ...
	CButton mCtrl__File_New;
	CButton mCtrl__File_Save;
	CButton mCtrl__File_SaveAs;
	CButton mCtrl__File_Delete;
	CButton mCtrl__File_CSV;
	CButton mCtrl__File_Undo;

	CButton mCtrl__Summary_View;
	CButton mCtrl__Summary_Save_Check;

	CButton mCtrl__Step_Append;
	CButton mCtrl__Step_Copy;
	CButton mCtrl__Step_Move;
	CButton mCtrl__Step_Delete;

	CButton mCtrl__Sel_Step_ID;
	CButton mCtrl__Sel_Item_ID;

	// ...
	CImageList m_Img_List;
	CUser_GridCtrl m_Grid;

	CInfo__Rcp_Item* pCur_Rcp_Item;
	CInfo__Rcp_Item m_Rcp_Header;
	CInfo__Rcp_Item m_Rcp_Step;
	CInfo__Rcp_Item m_Rcp_Tolerance;

	CInfo__Rcp_File m_Rcp_File;

	void _GoTo__Step_ID(const int st_id);
	void _Change__Grid_Info(const int step_id,const int item_id);
	void _Draw__Grid_Table(CInfo__Rcp_Item* p_rcp_item);
	void _Append__Grid_Table(CInfo__Rcp_Item* p_rcp_item, const int next_id, const int first_id = -1);

	void _Fnc__Grid_SelChanged(const int row,const int col);
	void _Fnc__Grid_Contract(const int row,const int col, CInfo__Rcp_Item* p_rcp_item);
	void _Fnc__Grid_Expand(const int row,const int col, CInfo__Rcp_Item* p_rcp_item);
	void _Fnc__Grid_Catergory(const int row,const int col, CInfo__Rcp_Item* p_rcp_item,const int node_state);

	void _Change__Rcp_Type(const int rcp_type);

	void _Fnc__File_Save();
	void _Fnc__File_Send();

	// ...
	CReportCtrl mCtrl__File_Table;
	CButton mCtrl__Send_File;

	CButton mCheck__Rcp_Pre;
	CButton mCheck__Rcp_Main;
	CButton mCheck__Rcp_Post;

	CButton mData__Rcp_Main_Count;
	CButton mData__Rcp_Pre_Count;
	CButton mData__Rcp_Post_Count;

	void _Make__File_Table(CReportCtrl *p_table);
	void _Add__File_Table(CReportCtrl *p_table, const CStringArray& l_name,const CStringArray& l_date);

	CString _Get__Name_Of_File_Talbe(const int r_index);

	void _Upload__Rcp_Folder(const int rcp_folder);
	int  _Upload__File_List(const CString& dir_sub);
	void _Change__Rcp_Folder(const int rcp_folder);
	
	int  _Get__Rcp_Folder();
	CString _Get__Rcp_Folder(const int rcp_folder);
	CString _Get__Rcp_Folder(const CString& rcp_folder);

	int  _Fnc__Summary_Check();

	// ...
	int StringPAD_PopUp(const int row,const int col, CString& out_data,CString& out_data2,int& dual_flag);
	int DigitalPAD_PopUp(const bool active_string, const CString input_list,const int row,const int col, CString& out_data);
	int AnalogPAD_PopUp(const int row,const int col, const CString& a_min,const CString& a_max, CString& out_data);

	// ...
	int _Init__Step_Ctrl_Btn();

	int _Add__Nes_Step();
	int _Save__File_Data(const CString& dir_sub, const CString& cur_file);
	CString _Get__Channel_Type(const int ch_type);

	int _Save__CSV_Data(const CString& csv_path);
	CString _Get__CSV_Data();

	CString _Get__Rcp_Type();

	int _Get__Save_InterLock();
	//

public:
	int Interlock_Rcp__GET_PROC(const int i_row,
		                        const int i_col, 
		                        CString& str_data);
	int Interlock_Rcp__GET_FNC(const int main_fnc,
								const int sub_fnc,
								const CString& in_para,
								const CStringArray& l_in_para,
								CString& out_para,
								CStringArray& l_out_para);

public:
	int iMODULE_ID;
	int iREAL_MODE;

	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);
	int Get_Link_Channel_List(CStringArray& l__link_ch);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
