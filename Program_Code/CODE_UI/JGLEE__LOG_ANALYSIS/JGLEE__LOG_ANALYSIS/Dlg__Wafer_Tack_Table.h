#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "CLS__Wafer_Trace.h"


// CDlg__Wafer_Tack_Table dialog

class CDlg__Wafer_Tack_Table : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_Tack_Table)

public:
	CDlg__Wafer_Tack_Table(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_Tack_Table();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_TACK_TABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedCheck_Move();
	afx_msg void OnBnClickedCheck_Process();
	afx_msg void OnBnClickedBtn_Refresh();
	DECLARE_MESSAGE_MAP()

	// ...
	CListCtrl mCtrl__Tack_Time;
	CImageList mImg__Tack_Time;

	CButton mBtn_WfrID;

	CButton mCheck__Moving;
	CButton mCheck__Process;

	// ...
	CStringArray sList__MODULE;
	CStringArray sList__ACTION;
	CStringArray sList__RESULT;
	CStringArray sList__TIME;
	CStringArray sList__COMMENT;

	// ...
	void _Make__Tack_Time_List(CListCtrl *p_table, CImageList *p_img);
	void _Add__Tack_Time_List(CListCtrl *p_table);

	// ...
	CButton mCtrl__Refresh_Btn;

	void _Refresh__Tack_Time();
	//


public:
	bool bPara__Active_Move;
	bool bPara__Active_Proc;

	CLS__Wafer_Info* pWfr_Info;
};
