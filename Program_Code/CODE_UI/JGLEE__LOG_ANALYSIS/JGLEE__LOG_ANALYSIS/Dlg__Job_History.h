#pragma once

#include "resource.h"
#include "Interface_Header.h"
#include "afxcmn.h"
#include "afxdtctl.h"

#include "CCls__REPORT_CTRL.h"

#include "CLS__Job_History.h"
#include "CLS__Wafer_Trace.h"
#include "afxwin.h"


// CDlg__Job_History dialog

class CDlg__Job_History : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Job_History)

public:
	CDlg__Job_History(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Job_History();

// Dialog Data
	enum { IDD = IDD_DLG__JOB_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Search_All();
	afx_msg void OnBnClickedBtn__Search_Option();
	afx_msg void OnBnClickedBtn__Option_PortID();
	afx_msg void OnBnClickedBtn__Option_JobID();
	afx_msg void OnBnClickedBtn__Option_LotID();
	afx_msg void OnBnClickedBtn__Option_CSTID();

	afx_msg void OnBnClickedBtn__Before_1Day();
	afx_msg void OnBnClickedBtn__Before_2Day();
	afx_msg void OnBnClickedBtn__Before_3Day();
	afx_msg void OnBnClickedBtn__Before_4Day();
	afx_msg void OnBnClickedBtn__Before_5Day();

	afx_msg void OnNMClickList__Search_Table(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTree__Slot_Sel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTree__Slot_Sel(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Expand_Node_History();
	afx_msg void OnBnClickedBtn__Expand_Node_All_Open();
	afx_msg void OnBnClickedBtn__Expand_Node_All_Close();

	afx_msg void OnBnClickedCheck__Log_Wafer_Compare();
	afx_msg void OnBnClickedCheck__Ref_Wafer_Compare();

	afx_msg void OnBnClickedCheck__Check_Move_Of_Wafer_Table();
	afx_msg void OnBnClickedCheck__Check_Proc_Of_Wafer_Table();

	afx_msg void OnBnClickedBtn__DA_Chart_Wafer();
	afx_msg void OnBnClickedBtn__DA_Chart_Lot();

	afx_msg void OnBnClickedBtn__Tack_Time_Wafer();
	afx_msg void OnBnClickedBtn__Tack_Time_Lot();

	afx_msg void OnBnClickedBtn__Proc_Log_Wafer();
	afx_msg void OnBnClickedBtn__Proc_Log_Lot();

	afx_msg void OnBnClickedBtn__Rcp_Log_Wafer();
	afx_msg void OnBnClickedBtn__Rcp_Log_Lot();

	afx_msg void OnBnClickedBtn__Ref_Wafer_Sel();
	afx_msg void OnBnClickedBtn__Ref_Wafer_Mng();

	DECLARE_MESSAGE_MAP()

	// ...
	COleDateTime mData__Start_Date;
	COleDateTime mData__End_Date;

	CString mStr__Search_Start;
	CString mStr__Search_End;

	void _Update__Before_X_Day(const int i_day);

	// ...
	CLS__Job_Log_Ctrl mLog_Ctrl;
	CLS__Wafer_Info mWfr_Info;

	//
	CButton mBtn_Option__PortID;
	CButton mCheck_Option__PortID_All;
	bool bActive_Option__PortID_All;

	CString mStr_Option__JobID;
	CButton mCheck_Option__JobID_All;
	CButton mCheck_Option__JobID_Part;
	bool bActive_Option__JobID_All;
	bool bActive_Option__JobID_Part;

	CString mStr_Option__LotID;
	CButton mCheck_Option__LotID_All;
	CButton mCheck_Option__LotID_Part;
	bool bActive_Option__LotID_All;
	bool bActive_Option__LotID_Part;

	CString mStr_Option__CSTID;
	CButton mCheck_Option__CSTID_All;
	CButton mCheck_Option__CSTID_Part;
	bool bActive_Option__CSTID_All;
	bool bActive_Option__CSTID_Part;

	//
	void _Update__Search_All(const CString& s_date, const CString& e_date);
	void _Update__Search_Wafer(const int r_index);

	void _Update__Wafer_Info(const CString& file_path);
	void _Clear__Wafer_Tree();
	void _Update__Wafer_Tree();
	
	void _Expand__Node_History();

	// ...
	CButton mCheck__Log_Wfr_Compare;
	CButton mCheck__Ref_Wfr_Compare;

	// ...
	CImageList mImg__Tree;

	// ...
	bool bActive_Init;

	int iResult_Table__Click_Pre_ID;
	CReportCtrl mList__Result_Table;
	CButton mBtn__Result_Sel_Path;
	CButton mBtn__Result_Sel_PortID;
	CString sBtn__Result_Sel_SlotID;

	void _Make__Result_Table(CReportCtrl *p_table);
	void _Add__Result_Table(CReportCtrl *p_table, CLS__Job_Log_Ctrl* p_log_ctrl);
	void _Change_Color__Result_Table(CReportCtrl *p_table, const int r_index);
	void _Change_Color__Result_Table(CReportCtrl *p_table, const int r_index, const COLORREF t_color,const COLORREF b_color);
	
	int  _Get_Index__Number_Of_Result_Table(CReportCtrl *p_table, const int no_id);
	int  _Get_Number__Index_Of_Result_Table(CReportCtrl *p_table, const int r_index);

	CString _Get_JobID__Result_Table();
	CString _Get_CSTID__Result_Table();
	CString _Get_StartDate__Result_Table();
	CString _Get_LotID__Result_Table();
	CString _Get_LotID__Result_Table(const int r_index);
	CString _Get_PortID__Result_Table();
	CString _Get_PortID__Result_Table(const int r_index);
	CString _Get_Path__Result_Table();
	CString _Get_Path__Result_Table(const int r_index);

	// ...
	CStringArray sList__Tree_Slot_Info;
	CTreeCtrl mTree__Slot_Info;
	HTREEITEM hTree__Slot_Node__COMPLETED;
	HTREEITEM hTree__Slot_Node__NOT_COMPLETE;
	HTREEITEM hTree__Slot_Node__ERROR;

	void _Clear__Slot_Info();
	void _Update__Slot_Info(const CStringArray& l_wfr);

	// ...
	CTreeCtrl mTree__Wafer_Info;
	
	CButton mCheck__Node_History;
	CButton mCheck__Node_Open;
	CButton mCheck__Node_Close;
	
	CButton mCheck__Search_Move;
	CButton mCheck__Search_Proc;

	CButton mBtn__DA_Chart_Wafer;
	CButton mBtn__Tack_Time_Wafer;
	CButton mBtn__Proc_Log_Wafer;
	CButton mBtn__Rcp_Log_Wafer;

	// ...
	CString sDir_Root;
	CString sDir_Ref_Wfr;
	CString sDir_Ref_Lot;

	// ...
	double dRes__Axis_Range;
	double dData__Error_Range;

	int iLPx_SIZE;

	// ...
	bool bActive__Wafer_Tree;

	// ...
	CString sPara__Template_Name_PM1;
	CString sPara__Template_Name_PM2;
	CString sPara__Template_Name_PM3;
	CString sPara__Template_Name_PM4;
	CString sPara__Template_Name_PM5;
	CString sPara__Template_Name_PM6;

	CString sPara__Template_Name_LL1;
	CString sPara__Template_Name_LL2;

	// ...
	CString sPara__Rcp_Inf_PM1;
	CString sPara__Rcp_Inf_PM2;
	CString sPara__Rcp_Inf_PM3;
	CString sPara__Rcp_Inf_PM4;
	CString sPara__Rcp_Inf_PM5;
	CString sPara__Rcp_Inf_PM6;

	CString sPara__Rcp_Inf_LL1;
	CString sPara__Rcp_Inf_LL2;
	//

	void _Init_Parameter();

	CButton mBtn__Ref_Wafer_Info;
	CButton mBtn__Ref_Wafer_Slot;
	CButton mBtn__Ref_Wfr_Mng;

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
