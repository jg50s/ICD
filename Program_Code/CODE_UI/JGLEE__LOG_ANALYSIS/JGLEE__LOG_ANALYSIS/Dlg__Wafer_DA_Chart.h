#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "CLS__Wafer_Trace.h"

#include "resource.h"


// CDlg__Wafer_DA_Chart dialog

class CDlg__Wafer_DA_Chart : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Wafer_DA_Chart)

public:
	CDlg__Wafer_DA_Chart(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Wafer_DA_Chart();

// Dialog Data
	enum { IDD = IDD_DLG__WAFER_DA_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnBnClickedBtn__Slot_All();
	afx_msg void OnBnClickedBtn__Slot_Clear();

	afx_msg void OnDeltaposSpin__Error_Range(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheck__Error_Range();
	afx_msg void OnNMClickList__Wafer_Select(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBtn__Check_All();
	afx_msg void OnBnClickedBtn__Check_Clear();
	afx_msg void OnBnClickedBtn__Check_PMx();
	afx_msg void OnBnClickedBtn__Check_LLx();

	afx_msg void OnNMClickList__Slot_Info(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtn__Result_Refresh();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__LotID_Data;
	CButton mBtn__PortID_Data;
	CButton mBtn__SlotID_Data;

	CButton mCheck_PM1;
	CButton mCheck_PM2;
	CButton mCheck_PM3;
	CButton mCheck_PM4;
	CButton mCheck_PM5;
	CButton mCheck_PM6;

	CButton mCheck_LL1;
	CButton mCheck_LL2;
	CButton mCheck_LL3;
	CButton mCheck_LL4;

	CButton mCheck__Only_Alarm;

	// ...
	CListCtrl mList__Slot_Info;
	CButton mBtn__Slot_All;
	CButton mBtn__Slot_Clear;

	CListCtrl  mCtrl__Wafer_Info;
	CImageList mImg__Wafer_Info;

	CStatic mDA_Chart;

	// ...
	double dRes__Axis_Max;
	double dRes__Axis_Range;

	int iRes__Center_X;
	int iRes__Center_Y;
	double dRes__Center_R;
	int iRes__Point_R_Size;

	// ...
	double dData__Error_Range;

	CButton mCheck__Error_Range;
	CString mStr__Error_Range;
	CSpinButtonCtrl mCtrl__Error_Range;
	//

	// ...
	void _Make__Slot_List();

	void _Add__Slot_List(const CStringArray& l_slot);
	CString _Get__ID_Of_Slot_List(const int r_index);

	// ...
	void _Make__Wafer_List(CListCtrl *p_table,
						   CImageList *p_img);

	void _Clear__Wafer_List();
	void _Add__Wafer_List(const CString& str_slotid,
						  const CStringArray& l_module,
						  const CStringArray& l_r_offset,
						  const CStringArray& l_t_offset);

	void _Get__RT_Offset_Of_Wafer_List(CStringArray& l_r_offset,
								       CStringArray& l_t_offset);

	// ...
	void _Draw__DA_Chart(const int db_index);

	int  _Get__XY_Of_RT(const double para_r_deg, 
						const double t_mm,
						int& p_x1,int& p_y1,
						int& p_x2,int& p_y2);
	//

public:
	bool bActive__Multi_Slot;
	CStringArray sList__Slot_ID;

	CString sDir_Root;
	CString sDir_Sub;

	//
	CString sPara__LotID;
	CString sPara__PortOD;
	CString sPara__SlotID;

	CStringArray sList__MODULE;
	CStringArray sList__R_OFFSET;
	CStringArray sList__T_OFFSET;
};
