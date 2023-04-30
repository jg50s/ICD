#pragma once

#include "resource.h"
#include "Interface_Header.h"
#include "afxcmn.h"

#include "CLS__Wafer_Trace.h"
#include "afxwin.h"

#include "CCls__Utility.h"


// CDlg__Wafer_Trace dialog

class CDlg__Wafer_Trace : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_Trace)

public:
	CDlg__Wafer_Trace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_Trace();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_TRACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__Wafer_Sel();
	afx_msg void OnBnClickedBtn__Wafer_Refresh();
	afx_msg void OnBnClickedBtn__DA_Chart();
	afx_msg void OnBnClickedBtn__Tack_Time();

	afx_msg void OnBnClickedBtn__Expand_Node_History();
	afx_msg void OnBnClickedBtn__Expand_All_Open();
	afx_msg void OnBnClickedBtn__Expand_All_Close();

	DECLARE_MESSAGE_MAP()

	// ...
	bool bActive_Init;

	CCls__ReSize mReSize;

	RECT mRC_DLG__WIN;
	RECT mRC_BTN__NODE_HISTORY;
	RECT mRC_BTN__NODE_ALL_OPEN;
	RECT mRC_BTN__NODE_ALL_CLOSE;
	RECT mRC_CHK__NODE_HISTORY;
	RECT mRC_CHK__NODE_ALL_OPEN;
	RECT mRC_CHK__NODE_ALL_CLOSE;

	RECT mRC_BTN__WFR_REFREASH;
	RECT mRC_BTN__DA_CHART;
	RECT mRC_BTN__TACK_TIME;
	RECT mRC_BTN__WFR_SEL;
	RECT mRC_CHK__SEARCH_MOVE;
	RECT mRC_CHK__SEARCH_PROC;

	RECT mRC_GROUP__ITEM;
	RECT mRC_TEXT__WFRID;
	RECT mRC_TEXT__LOTID;

	RECT mRC_EDIT__WFR_PATH;
	RECT mRC_EDIT__WFRID;
	RECT mRC_EDIT__LOTID;

	RECT mRC_TREE__WAFER;

	// ...
	CButton mBtn__Node_History;
	CButton mBtn__Node_All_Open;
	CButton mBtn__Node_All_Close;

	CButton mCheck__Node_History;
	CButton mCheck__Node_Open;
	CButton mCheck__Node_Close;

	//
	CButton mBtn__Wfr_Refresh;
	CButton mBtn__DA_Chart;
	CButton mBtn__Tack_Time;
	CButton mBtn__Wfr_Sel;

	CButton mCheck__Search_Move;
	CButton mCheck__Search_Proc;

	CStatic mGroup__Item;
	CStatic mText__WfrID;
	CStatic mText__LotID;

	CEdit mEdit__Wfr_Path;
	CEdit mEdit__WfrID;
	CEdit mEdit__LotID;

	// ...
	CTreeCtrl mTree_Wafer;
	CImageList mTree_Image;

	// ...
	CLS__Wafer_Info mWfr_Info;
	CString sDir_Root;

	CString mStr__Sel_WaferID;
	CString mStr__Sel_LotID;
	CString mStr__Wafer_Path;

	// ...
	double dRes__Axis_Range;
	double dData__Error_Range;

	int iLPx_SIZE;

	// ...
	bool bActive__Wafer_Tree;
	void _Update__Wafer_Tree();

	// ...
	void _Refresh__Wafer_Info(const CString& wfr_path);
	
	void _Update__Wafer_Info(const CString& file_path);
	void _Expand__Node_History();
	//


public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
