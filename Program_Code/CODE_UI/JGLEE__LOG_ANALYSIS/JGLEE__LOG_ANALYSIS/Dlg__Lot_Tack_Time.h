#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "CCls__REPORT_CTRL.h"
#include "ChartViewer.h"

#include "CLS__Slot_Tack.h"


#define _CFG__SLOT_MAX						25


// CDlg__Lot_Tack_Time dialog

class CDlg__Lot_Tack_Time : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Lot_Tack_Time)

public:
	CDlg__Lot_Tack_Time(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Lot_Tack_Time();

// Dialog Data
	enum { IDD = IDD_DLG__LOT_TACK_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMouseMovePlotArea();

	afx_msg void OnBnClickedBtn__Chart_Refresh();

	afx_msg void OnBnClickedBtn__Single_Slot();
	afx_msg void OnBnClickedBtn__Multi_Slot();
	afx_msg void OnBnClickedBtn__Slot_All();
	afx_msg void OnBnClickedBtn__Slot_Clear();

	afx_msg void OnNMClickList__Slot_Info(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__LotID_Data;
	CButton mBtn__PortID_Data;

	CButton mCheck__Move;
	CButton mCheck__Process;

	// ...
	CReportCtrl mList__Slot_Info;

	CButton mBtn__Single_Slot;
	CButton mBtn__Sel_Slot;
	CButton mBtn__Multi_Slot;
	CButton mBtn__Slot_All;
	CButton mBtn__Slot_Clear;

	void _Make__Slot_List();
	void _Add__Slot_List(const CStringArray& l_slot);
	void _Update__Slot_Act_Cnt();
	
	CString _Get__ID_Of_Slot_List(const int r_index);
	int  _Get__Selected_Index_Of_Slot_List();
	int  _Get__Checked_Count_Of_Slot_List();

	void _Btn_Click__Single_Slot();
	void _Btn_Click__Multi_Slot();
	void _Btn_Click__Slot_All();
	void _Btn_Click__Slot_Clear();

	// ...
	CChartViewer mChart_Viwer;
	RECT mArea__Chart_View;
	RECT mArea__Chart_XY;

	CString sPara__X_Axis_Title;
	CString sPara__Y_Axis_Title;

	COLORREF cPara__Single_Color;
	COLORREF cPara__Slot_Color_RGB[_CFG__SLOT_MAX];
	COLORREF cPara__Slot_Color_ARGB[_CFG__SLOT_MAX];
	bool bActive__Chart_Single;

	void _Init__Proc_Chart();
	void _Make__Proc_Chart();

	int  _getDefaultBgColor();
	void _trackLineLegend(XYChart *c, int mouseX);

	// ...
	CLS__Slot_Tack_Ctrl mSlot_Tack;

	void _Update__Slot_Info();
	//

public:
	CStringArray sList__Slot_ID;

	CString sDir_Root;
	CString sDir_Sub;

	CString sPara__LotID;
	CString sPara__PortOD;

	bool bPara__Active_Move;
	bool bPara__Active_Proc;
};

