#pragma once

#include "afxcmn.h"

#include "CLS__Wafer_Trace.h"
#include "CCls__REPORT_CTRL.h"

#include "CLS__Rcp_Info.h"


// CDlg__Wafer_Rcp_Sel dialog

class CDlg__Wafer_Rcp_Sel : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_Rcp_Sel)

public:
	CDlg__Wafer_Rcp_Sel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_Rcp_Sel();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_RCP_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	afx_msg void OnBnClickedBtn__Rcp_View();

	DECLARE_MESSAGE_MAP()

	// ...
	CReportCtrl mList__RCP_SEL;

	void _Make__RCP_List(CListCtrl *p_table);
	void _Add__RCP_List();

	CString _Get__MDx_Name_Of_RCP_List();
	CString _Get__Log_Path_Of_RCP_List();

	// ...
	CReportCtrl mList__RCP_INFO;
	int iRCP_INFO__Column_Size;

	void _Clear__INFO_List();
	void _Make__INFO_List();
	void _Add__INFO_List();

	// ...
	CPara_Info mPara_Info;
	CRcp_Info  mRcp_Info;

	int  Upload__Rcp_Info(const CString& file_path, CRcp_Info* p_rcp_info);
	int  Upload__Para_Info(const CString& file_path, CPara_Info* p_para_info);
	//

public:
	CString sDir_Root;
	CString sDir_Lot;

	CLS__Wafer_Info *pWfr_Info;

	CString sPara__Rcp_Inf_PM1;
	CString sPara__Rcp_Inf_PM2;
	CString sPara__Rcp_Inf_PM3;
	CString sPara__Rcp_Inf_PM4;
	CString sPara__Rcp_Inf_PM5;
	CString sPara__Rcp_Inf_PM6;

	CString sPara__Rcp_Inf_LL1;
	CString sPara__Rcp_Inf_LL2;
};

