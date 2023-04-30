#pragma once
#include "afxwin.h"


// CDlg__Route_ALx dialog

class CDlg__Route_ALx : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_ALx)

public:
	CDlg__Route_ALx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_ALx();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_ALx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__PARA_ANGLE();
	afx_msg void OnBnClickedBtn__PARA_SLOT02();
	afx_msg void OnBnClickedBtn__PARA_SLOT01();
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	CString mData_Angle;
	CString mData_Slot02;
	CString mData_Slot01;

	CButton mCtrl_Slot02;
	CButton mCtrl_Slot01;

	CButton mCtrl_Angle;

public:
	bool bACTIVE__CTRL_CFG;
	bool bACTIVE__SLOT_FIXED;

	CString sPARA_ALx;
	CString sPARA_ANGLE;
	CString sPARA_SLOT;

	bool bACTIVE_SLOT01;
	bool bACTIVE_SLOT02;
};
