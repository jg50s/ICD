#pragma once

#include "afxcmn.h"

#include "CCls__REPORT_CTRL.h"
#include "CLS__Job_History.h"
#include "afxwin.h"


// CDlg__Ref_Wafer_Sel dialog

class CDlg__Ref_Wafer_Sel : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Ref_Wafer_Sel)

public:
	CDlg__Ref_Wafer_Sel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Ref_Wafer_Sel();

// Dialog Data
	enum { IDD = IDD_DLG__REF_WAFER_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnNMClickList__Ref_Result_Table(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtn__Ref_Wfr_Del();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__Ref_Delete;

	// ...
	CLS__Job_Log_Ctrl mLog_Ctrl;
	CReportCtrl mList__Result_Table;

	int iSel_Table_Index;
	CButton mBtn__Ref_Wfr_Sel;

	void _Make__Result_Table(CReportCtrl *p_table);
	void _Add__Result_Table(CReportCtrl *p_table, CLS__Job_Log_Ctrl* p_log_ctrl);

	void _Update__Search_All();

	// ...
	void _Refresh__Result_Table();
	//

public:
	CString sDir_Root;

	CString sPara__Dir_Log;
	CString sPara__Wfr_Port;
	CString sPara__Wfr_Slot;
};
