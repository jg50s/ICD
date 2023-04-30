#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "CCls__REPORT_CTRL.h"

#include "ChartViewer.h"
#include "CDB__Chart_Data.h"
#include "CLS__Proc_Log.h"


// CDlg__Wafer_Proc_Chart dialog

#define _DEF__Y_SIZE				10


class CDlg__Wafer_Proc_Chart : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_Proc_Chart)

public:
	CDlg__Wafer_Proc_Chart(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_Proc_Chart();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_PROC_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMouseMovePlotArea();

	afx_msg void OnNMClickList__Channel_Table(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList__Channel_Sel(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Chart_Single();
	afx_msg void OnBnClickedBtn__Chart_Multi();
	afx_msg void OnBnClickedBtn__Multi_All();
	afx_msg void OnBnClickedBtn__Multi_Clear();

	DECLARE_MESSAGE_MAP()

	// ...
	CReportCtrl mList__Channel_Table;

	void _Make__Channel_List(CListCtrl* p_table);
	void _Add__Channel_List();

	int _Get__Selected_Index_Of_Channel_List();
	CString _Get__Channel_Of_Channel_List(const int r_index);
	CString _Get__Name_Of_Channel_List(const int r_index);
	CString _Get__ID_Of_Channel_List(const int r_index);

	// ...
	CButton mBtn__Chart_Single;

	CButton mBtn__Chart_Multi;
	CButton mBtn__Multi_All;
	CButton mBtn__Multi_Clear;

	//
	CReportCtrl mList__Channel_Sel;
	COLORREF cList__Channel_Color_RGB[_DEF__Y_SIZE];

	void _Make__Channel_Sel(CListCtrl* p_table);
	void _Add__Channel_Sel();
	void _Fnc__Multi_All();

	// ...
	CChartViewer m_ChartViewer;
	RECT mArea__Chart_View;
	RECT mArea__Chart_XY;

	CString sPara__X_Axis_Title;
	CString sPara__Y_Axis_Title;

	COLORREF cPara__Single_Color;
	COLORREF cPara__Y_Color[_DEF__Y_SIZE];
	bool bActive__Chart_Single;

	void _Init__Proc_Chart();
	void _Make__Proc_Chart();
	
	int  _getDefaultBgColor();
	void _trackLineLegend(XYChart *c, int mouseX);
	//

public:
	CLS__Proc_Log* pLog_Proc;

};
