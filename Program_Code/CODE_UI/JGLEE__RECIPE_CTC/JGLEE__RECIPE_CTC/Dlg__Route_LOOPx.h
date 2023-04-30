#pragma once


// CDlg__Route_LOOPx dialog

class CDlg__Route_LOOPx : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_LOOPx)

public:
	CDlg__Route_LOOPx(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_LOOPx();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_LOOPx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedBtn_Repeat();

public:
	CString sPARA_MODULE;
	CString sPARA_REPEAT;
	CString mData_Repeat;
	afx_msg void OnBnClickedOk();
};
