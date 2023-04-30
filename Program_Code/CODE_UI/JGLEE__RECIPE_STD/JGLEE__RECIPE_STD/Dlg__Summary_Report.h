#pragma once

#include "afxcmn.h"

#include "CInfo__Rcp_Item.h"
#include "CInfo__Rcp_File.h"


// CDlg__Summary_Report dialog

class CDlg__Summary_Report : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Summary_Report)

public:
	CDlg__Summary_Report(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Summary_Report();

// Dialog Data
	enum { IDD = IDD_DLG__SUMMARY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	DECLARE_MESSAGE_MAP()

	// ...
	CListCtrl mCtrl__Report_List;

	void _Make__INFO_List();
	void _Add__INFO_List();
	//

public:
	CInfo__Rcp_Item* pAddr__Rcp_Item;
	CInfo__Rcp_File* pAddr__Rcp_File;

	int iMODULE_ID;
	UII__RCP_INTERLOCK_CTRL* pI_Rcp_Interlock_Ctrl;

	CUIntArray iList__Item_ID;
};
