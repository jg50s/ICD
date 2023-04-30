#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "CLS__Wafer_Trace.h"
#include "CCls__REPORT_CTRL.h"


// CDlg__Wafer_MDx_Sel dialog

class CDlg__Wafer_MDx_Sel : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_MDx_Sel)

public:
	CDlg__Wafer_MDx_Sel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_MDx_Sel();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_MDx_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__Template_Ctrl_PM1();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM2();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM3();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM4();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM5();
	afx_msg void OnBnClickedBtn__Template_Ctrl_PM6();
	afx_msg void OnBnClickedBtn__Template_Ctrl_LL1();
	afx_msg void OnBnClickedBtn__Template_Ctrl_LL2();

	afx_msg void OnBnClickedBtn__Template_Name_PM1();
	afx_msg void OnBnClickedBtn__Template_Name_PM2();
	afx_msg void OnBnClickedBtn__Template_Name_PM3();
	afx_msg void OnBnClickedBtn__Template_Name_PM4();
	afx_msg void OnBnClickedBtn__Template_Name_PM5();
	afx_msg void OnBnClickedBtn__Template_Name_PM6();
	afx_msg void OnBnClickedBtn__Template_Name_LL1();
	afx_msg void OnBnClickedBtn__Template_Name_LL2();

	afx_msg void OnBnClickedBtn__Log_Graph();
	afx_msg void OnBnClickedBtn__Log_Text();
	afx_msg void OnBnClickedBtn__SAVE_CSV();

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__Template_Ctrl_PM1;
	CButton mBtn__Template_Ctrl_PM2;
	CButton mBtn__Template_Ctrl_PM3;
	CButton mBtn__Template_Ctrl_PM4;
	CButton mBtn__Template_Ctrl_PM5;
	CButton mBtn__Template_Ctrl_PM6;
	CButton mBtn__Template_Ctrl_LL1;
	CButton mBtn__Template_Ctrl_LL2;

	CButton mBtn__Template_Name_PM1;
	CButton mBtn__Template_Name_PM2;
	CButton mBtn__Template_Name_PM3;
	CButton mBtn__Template_Name_PM4;
	CButton mBtn__Template_Name_PM5;
	CButton mBtn__Template_Name_PM6;
	CButton mBtn__Template_Name_LL1;
	CButton mBtn__Template_Name_LL2;

	CButton mCheck__Template_PM1;
	CButton mCheck__Template_PM2;
	CButton mCheck__Template_PM3;
	CButton mCheck__Template_PM4;
	CButton mCheck__Template_PM5;
	CButton mCheck__Template_PM6;
	CButton mCheck__Template_LL1;
	CButton mCheck__Template_LL2;

	CButton mBtn__Template_Sel_MDx;
	CButton mBtn__Template_Sel_Name;
	CReportCtrl mList__MDx_Template;

	void _Fnc__Template_Sel_MDx(const int pm_id, const int ll_id);
	void _Change__Template_Table(const CString& str_mdx, const CString& str_template);

	void _Make__Template_List(CListCtrl *p_table);
	void _Add__Template_List(const CString& str_mdx, const CString& str_template);

	// ...
	CImageList mImg_List;
	CListCtrl mList__MDx_Sel;

	// ...
	void _Make__MDx_List(CListCtrl *p_table);
	void _Add__MDx_List(CListCtrl *p_table);

	CString _Get__MDx_Name_Of_MDx_List();
	CString _Get__Log_Path_Of_MDx_List();

	// ...
	void _Upload__Log_Graph(const CString& md_name, const CString& log_path);
	void _Upload__Log_Text(const CString& md_name, const CString& log_path);
	void _Upload__Log_CSV(const CString& md_name, const CString& log_path);

	CString _Get__Template_Name_Of_PMx(const int pm_id);
	CString _Get__Template_Name_Of_LLx(const int ll_id);
	//

public:
	CString sDir_Root;
	CString sDir_Lot;

	CLS__Wafer_Info *pWfr_Info;

	CString sPara__Template_Name_PM1;
	CString sPara__Template_Name_PM2;
	CString sPara__Template_Name_PM3;
	CString sPara__Template_Name_PM4;
	CString sPara__Template_Name_PM5;
	CString sPara__Template_Name_PM6;
	CString sPara__Template_Name_LL1;
	CString sPara__Template_Name_LL2;
	CButton mCheck__STEP_MIN;
	CButton mCheck__STEP_MAX;
	CButton mCheck__STEP_AVG;
};
