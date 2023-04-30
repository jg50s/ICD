#pragma once
#include "afxwin.h"


// CDlg__Route_Mode_Select dialog

class CDlg__Route_Mode_Select : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Route_Mode_Select)

public:
	CDlg__Route_Mode_Select(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Route_Mode_Select();

// Dialog Data
	enum { IDD = IDD_DLG__ROUTE_MODE_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CString mData_Info;
	CButton mCtrl__Sel_Item;
	CListBox mCtrl__Item_List;

public:
	CString sPARA__INFO;
	CString sPARA__SEL_DATA;
	CStringArray sList__ITEM_DATA;
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnBnClickedOk();
};
