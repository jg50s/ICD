#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlg__Wafer_Trace_Sel dialog

class CDlg__Wafer_Trace_Sel : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_Trace_Sel)

public:
	CDlg__Wafer_Trace_Sel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_Trace_Sel();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_TRACE_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
	afx_msg void OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList__Wafer_Info(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Wafer_Refresh();
	afx_msg void OnLbnSelchangeList();
	
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

	// ...
	CImageList mImg_List;

	CListCtrl mCtrl__Wafer_Info;
	CListBox  mList__Slot_Info;
	CStringArray sList__Slot_Path;

	CButton mCheck__1_Day_Before;
	CButton mCheck__LotID;

	CButton mCheck_LP1;
	CButton mCheck_LP2;
	CButton mCheck_LP3;
	CButton mCheck_LP4;
	CButton mCheck_LP5;

	// ...
	int iIndex__Lot_Table;

	void _Make__Wafer_List(CListCtrl *p_table);
	void _Add__Wafer_List(CListCtrl *p_table);
	void _Add__Slot_Info(CListCtrl *p_table, const int r_index, const bool active_focus = false);

	void _Get__SEL_INFO();
	//

public:
	// In ...
	int iREAL_MODE;

	CString sPara__DIR_ROOT;
	int iPara__LPx_SIZE;
	CStringArray sPara__LOTID;

	// Out ...
	int iSel__PortID;
	int iSel__SlotID;
	CString sSel__LotID;
	CString sSel__Path;
	CButton mBtn_OK;
};
