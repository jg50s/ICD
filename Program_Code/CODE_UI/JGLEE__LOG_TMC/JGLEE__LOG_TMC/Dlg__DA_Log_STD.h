#pragma once

#include "Interface_Header.h"
#include "resource.h"
#include "afxcmn.h"

#include "Dlg__DA_Wafer_Search.h"
#include "afxwin.h"


class CDB__LOTID
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CStringArray sList__LotID;
	CStringArray sList__PortID;
	CStringArray sList__LOG_HEADER;

public:
	CDB__LOTID()
	{
		InitializeCriticalSection(&mCS_LOCK);

	}
	~CDB__LOTID()
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	int Load__LOTID(const CString& str_lotid, const CString& str_portid, const CString& str_log_header)
	{
		EnterCriticalSection(&mCS_LOCK);

		int check_flag = -1;

		int i_limit = sList__LotID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(sList__LotID[i].CompareNoCase(str_lotid) != 0)
				continue;

			if(sList__PortID[i].CompareNoCase(str_portid) != 0)
				continue;

			if(sList__LOG_HEADER[i].CompareNoCase(str_log_header) != 0)
				continue;

			check_flag = 1;
			break;
		}

		if(check_flag < 0)
		{
			sList__LotID.Add(str_lotid);
			sList__PortID.Add(str_portid);
			sList__LOG_HEADER.Add(str_log_header);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return check_flag;
	}
	int Get__LOTID(CStringArray& l_lotid, CStringArray& l_portid, CStringArray& l_log_header)
	{
		EnterCriticalSection(&mCS_LOCK);

		l_lotid.RemoveAll();
		l_portid.RemoveAll();
		l_log_header.RemoveAll();

		l_lotid.Copy(sList__LotID);
		l_portid.Copy(sList__PortID);
		l_log_header.Copy(sList__LOG_HEADER);

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	void Clear__LOTID()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__LotID.RemoveAll();
		sList__PortID.RemoveAll();
		sList__LOG_HEADER.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
};
class CDB__OFFSET_POINT
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CStringArray sList__P1;
	CStringArray sList__P2;
	CStringArray sList__ARM_Type;
	CStringArray sList__ARM_Action;

public:
	CDB__OFFSET_POINT()
	{
		InitializeCriticalSection(&mCS_LOCK);

	}
	~CDB__OFFSET_POINT()
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	void Load__INFO(const CString& str_p1, const CString& str_p2)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			sList__P1.Add(str_p1);
			sList__P2.Add(str_p2);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}

	void Load__INFO_ARM(const CString& str_ARM_TYPE, const CString& str_ARM_ACTION)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			sList__ARM_Type.Add(str_ARM_TYPE);
			sList__ARM_Action.Add(str_ARM_ACTION);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}

	int Get__INFO(CStringArray& l_p1, CStringArray& l_p2)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_p1.RemoveAll();
			l_p2.RemoveAll();

			l_p1.Copy(sList__P1);
			l_p2.Copy(sList__P2);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	int Get__INFO_ARM(CStringArray& l_ARM_TYPE, CStringArray& l_ARM_ACTION)
	{
		EnterCriticalSection(&mCS_LOCK);

		// ...
		{
			l_ARM_TYPE.RemoveAll();
			l_ARM_ACTION.RemoveAll();

			l_ARM_TYPE.Copy(sList__ARM_Type);
			l_ARM_ACTION.Copy(sList__ARM_Action);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return 1;
	}

	void Clear__INFO()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList__P1.RemoveAll();
		sList__P2.RemoveAll();
		sList__ARM_Type.RemoveAll();
		sList__ARM_Action.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
};


// CDlg__DA_Log_STD dialog

class CDlg__DA_Log_STD : public CDialog
{
	DECLARE_DYNAMIC(CDlg__DA_Log_STD)

public:
	CDlg__DA_Log_STD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__DA_Log_STD();

// Dialog Data
	enum { IDD = IDD_DLG__DA_LOG_STD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtn__Upload_Log();
	afx_msg void OnBnClickedBtn__Wafer_Search();
	afx_msg void OnBnClickedBtn__DA_Refresh();
	afx_msg void OnBnClickedBtn__Result_Refresh();

	afx_msg void OnNMClickList__Log_Date(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList__Log_File(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList__DA_Item(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposSpin__Err_Range(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLvnColumnclickList__Log_Date(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickList__Log_File(NMHDR *pNMHDR, LRESULT *pResult);

	// ...
	int  Sort__Log_Table(CListCtrl* p_table,
						 const int col_id, 
						 bool& sort_order,
						 CStringArray& l_file,
						 CStringArray& l_date);

	int  Sort__Log_Table(CListCtrl* p_table,
						 const int col_size, 
						 const int col_id, 
						 bool& sort_order,
						 CStringArray& l_file,
						 CStringArray& l_date,
						 CStringArray& l_header);

	bool bSortDirect_LogDate;
	bool bSortDirect_LogFile;

	// ...
	CString sDir_Root;
	
	CImageList mImg_Log;
	CListCtrl mCtrl__Log_Date;
	CListCtrl mCtrl__Log_File;
	CListCtrl mCtrl__Log_Result;

	// ...
	CStringArray sList__Log_Date__Name;
	CStringArray sList__Log_Date__Date;

	CStringArray sList__Log_File__PortID;
	CStringArray sList__Log_File__LotID;
	CStringArray sList__Log_File__Header;

	// ...
	CString mStr__Search_LotID;
	CString mStr__Search_PPID;
	CString mStr__Search_PortID;
	CString mStr__Search_SlotID;

	CButton mCheck__Search_PM1;
	CButton mCheck__Search_PM2;
	CButton mCheck__Search_PM3;
	CButton mCheck__Search_PM4;
	CButton mCheck__Search_PM5;
	CButton mCheck__Search_PM6;

	CButton mCheck__Search_LL1;
	CButton mCheck__Search_LL2;
	CButton mCheck__Search_LL3;
	CButton mCheck__Search_LL4;

	CButton* pCheck__Search_PMx[_CFG__PMx_SIZE];
	CButton* pCheck__Search_LLx[_CFG__LLx_SIZE];

	CButton mCheck__Error_Range;
	CSpinButtonCtrl mCtrl__Err_Ramge;
	CString mStr__Error_Range;
	double dData__Error_Range;

	CButton mCheck__Only_Alarm;

	// ...
	CString sSearch__LotID;
	CString sSearch__PPID;

	int iSearch__PortID;
	int iSearch__SlotID;

	bool bCheck__PMx[_CFG__PMx_SIZE];
	bool bCheck__LLx[_CFG__LLx_SIZE];

	CDB__LOTID mDB_LOTID;
	CDB__OFFSET_POINT mDB__OFFSET_PT;
	
	CStatic mDA_Chart;

	// ...
	void _Make__Table_Dir_List(CListCtrl *p_table);
	void _Make__Table_LotID_List(CListCtrl *p_table);

	void _Make__Table_List(CListCtrl *p_table,
						   const int tbl_type);
	void _Add__Table_List(CListCtrl *p_table,
						  const int col_size,
						  const CStringArray& l_data1,
						  const CStringArray& l_data2,
						  const CStringArray& l_data3);

	void _Make__Result_List(CListCtrl *p_table);
	void _Add__Result_List(CListCtrl *p_table, 
							const CStringArray& l_portid,
							const CStringArray& l_slotid,
							const CStringArray& l_module,
							const CStringArray& l_off_r,
							const CStringArray& l_off_t,
							const CStringArray& l_off_x,
							const CStringArray& l_off_y,
							const CStringArray& l_lotid,
							const CStringArray& l_ppid,
							const CStringArray& l_arm_type,
							const CStringArray& l_arm_act,
							const CStringArray& l_end_time);

	void _Fnc__Log_View(const int db_index = -1);
	int  _Upload__DA_File(const CString& file_path,
						  const CString& file_portid);

	void _Draw__DA_Chart(const int sel_index = -1);
	int  _Get__XY_Of_RT(const double para_radius, 
						const double para_degree,
						int& p_x1,int& p_y1,
						int& p_x2,int& p_y2);
	int  _Get__XY_Of_XY(const double x_offset, 
						const double y_offset,
						int& p_x1,int& p_y1,
						int& p_x2,int& p_y2);

	void _Update__Log_Date(const CString& dir_log,
						   const CString& file_ext);

	// ...
	double dRes__Axis_Range;

	int iRes__Center_X;
	int iRes__Center_Y;
	double dRes__Center_R;
	int iRes__Point_R_Size;

	bool bActive__LOG_PROC;
	bool bActive__R_T_OFFSET;
	//

public:
	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	int Set_Parameter(const int module_id);

	int Set_MoveWindow(const POINT& p_st, const POINT& p_et);
	int Redraw_Page();
};
