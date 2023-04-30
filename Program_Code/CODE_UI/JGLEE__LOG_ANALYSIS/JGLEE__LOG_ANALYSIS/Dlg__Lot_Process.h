#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "CCls__REPORT_CTRL.h"
#include "ChartViewer.h"

#include "CLS__Wafer_Trace.h"


class CLS__MDx_Step_Info
{
public:
	CLS__MDx_Step_Info()
	{

	}

	CString sMDx_Name;
	CStringArray sList__Step_Time;
};
class CLS__Slot_Step_Info
{
public:
	CString sRef_SlotID;
	CPtrArray pList_DB;

public:
	CLS__Slot_Step_Info()
	{

	}
	~CLS__Slot_Step_Info()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList_DB.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__MDx_Step_Info *p_md = (CLS__MDx_Step_Info*) pList_DB[i];
			delete p_md;
		}
		pList_DB.RemoveAll();
	}
	void Load__MDx_Step_Time(const CLS__MDx_Step_Info* p_md_info)
	{
		CLS__MDx_Step_Info* p_md = new CLS__MDx_Step_Info;
		pList_DB.Add(p_md);

		p_md->sMDx_Name = p_md_info->sMDx_Name;
		p_md->sList__Step_Time.Copy(p_md_info->sList__Step_Time);
	}

	int Get__MDx_Size()
	{
		return pList_DB.GetSize();
	}
	CLS__MDx_Step_Info* Get_Addr__MDx_Step_Info(const int md_index)
	{
		if(md_index < 0)						return NULL;
		if(md_index >= pList_DB.GetSize())		return NULL;

		return (CLS__MDx_Step_Info*) pList_DB[md_index];
	}
	CLS__MDx_Step_Info* Get_Addr__MDx_Step_Info(const CString& md_name)
	{
		int i_limit = pList_DB.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__MDx_Step_Info* p_md_db = (CLS__MDx_Step_Info*) pList_DB[i];

			if(p_md_db->sMDx_Name.Find(md_name) < 0)		
				continue;

			return p_md_db;
		}
		return NULL;
	}
};
class CLS__Slot_Step_Ctrl
{
private:
	CPtrArray pList_Slot;

	CLS__Slot_Step_Info* _Get__Slot_Step_Info(const CString& slot_id)
	{
		int i_limit = pList_Slot.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Step_Info *p_slot = (CLS__Slot_Step_Info*) pList_Slot[i];
			if(p_slot->sRef_SlotID.CompareNoCase(slot_id) != 0)		continue;

			return p_slot;
		}
		return NULL;
	}

public:
	CLS__Slot_Step_Ctrl()
	{

	}
	~CLS__Slot_Step_Ctrl()
	{
		Clear();
	}

	void Clear()
	{
		int i_limit = pList_Slot.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Step_Info *p_slot = (CLS__Slot_Step_Info*) pList_Slot[i];
			delete p_slot;
		}
		pList_Slot.RemoveAll();
	}
	void Load__Slot_Info(const CString& slot_id,const CLS__MDx_Step_Info* p_slot_xxx)
	{
		CLS__Slot_Step_Info* p_slot_db = _Get__Slot_Step_Info(slot_id);

		if(p_slot_db == NULL)
		{
			p_slot_db = new CLS__Slot_Step_Info;
			pList_Slot.Add(p_slot_db);

			p_slot_db->sRef_SlotID = slot_id;
		}

		p_slot_db->Load__MDx_Step_Time(p_slot_xxx);
	}

	int Get__Slot_Size()
	{
		return pList_Slot.GetSize();
	}
	CLS__Slot_Step_Info* Get__Slot_Step_Info(const CString& slot_id)
	{
		return _Get__Slot_Step_Info(slot_id);
	}
	CLS__Slot_Step_Info* Get__Slot_Step_Info(const int slot_i)
	{
		if(slot_i <  0)							return NULL;
		if(slot_i >= pList_Slot.GetSize())		return NULL;

		return (CLS__Slot_Step_Info*) pList_Slot[slot_i];
	}

	int Get__Max_Step_Size_Of_MDx(const CString& md_name)
	{
		int i_max = 0;
		int i_limit = pList_Slot.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Step_Info* p_slot_db = (CLS__Slot_Step_Info*) pList_Slot[i];
			if(p_slot_db == NULL)				continue;

			CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(md_name);
			if(p_md_db == NULL)					continue;

			int cur_size = p_md_db->sList__Step_Time.GetSize();
			if(cur_size > i_max)				i_max = cur_size;
		}
		return i_max;
	}
	int Get__Max_Step_Size_Of_MDx(const int md_i)
	{
		int i_max = 0;
		int i_limit = pList_Slot.GetSize();
		
		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Step_Info* p_slot_db = (CLS__Slot_Step_Info*) pList_Slot[i];
			if(p_slot_db == NULL)				continue;
			
			CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(md_i);
			if(p_md_db == NULL)					continue;
			
			int cur_size = p_md_db->sList__Step_Time.GetSize();
			if(cur_size > i_max)				i_max = cur_size;
		}
		return i_max;
	}

	int Get__Step_Size_Of_MDx(const CString& slot_id, const CString& md_name)
	{
		CLS__Slot_Step_Info* p_slot_db = _Get__Slot_Step_Info(slot_id);
		if(p_slot_db == NULL)					return 0;

		CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(md_name);
		if(p_md_db == NULL)						return 0;

		return p_md_db->sList__Step_Time.GetSize();
	}
	CLS__MDx_Step_Info* Get_Addr__Step_Size_Of_MDx(const CString& slot_id, const int md_i)
	{
		CLS__Slot_Step_Info* p_slot_db = _Get__Slot_Step_Info(slot_id);
		if(p_slot_db == NULL)					return NULL;

		CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(md_i);
		if(p_md_db == NULL)						return NULL;

		return p_md_db;
	}
	CLS__MDx_Step_Info* Get_Addr__Step_Size_Of_MDx(const CString& slot_id, const CString& md_name)
	{
		CLS__Slot_Step_Info* p_slot_db = _Get__Slot_Step_Info(slot_id);
		if(p_slot_db == NULL)					return NULL;

		CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(md_name);
		if(p_md_db == NULL)						return NULL;

		return p_md_db;
	}

	int Get__All_MDx_List(CStringArray& l__md_name)
	{
		l__md_name.RemoveAll();

		int i_limit = pList_Slot.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			CLS__Slot_Step_Info* p_slot_db = (CLS__Slot_Step_Info*) pList_Slot[i];
			if(p_slot_db == NULL)				continue;

			int m_size = p_slot_db->Get__MDx_Size();
			for(int m=0; m<m_size; m++)
			{
				CLS__MDx_Step_Info* p_md_db = p_slot_db->Get_Addr__MDx_Step_Info(m);

				//
				bool active_check = false;

				int k_limit = l__md_name.GetSize();
				for(int k=0; k<k_limit; k++)
				{
					if(p_md_db->sMDx_Name.CompareNoCase(l__md_name[k]) != 0)
						continue;

					active_check = true;
					break;
				}

				if(!active_check)
				{
					l__md_name.Add(p_md_db->sMDx_Name);
				}
			}
		}
		return 1;
	}
};


// ...
#define _CFG__SLOT_MAX						25


// CDlg__Lot_Process dialog

class CDlg__Lot_Process : public CDialog
{
	DECLARE_DYNAMIC(CDlg__Lot_Process)

public:
	CDlg__Lot_Process(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg__Lot_Process();

// Dialog Data
	enum { IDD = IDD_DLG__LOT_PROCESS };

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

	afx_msg void OnBnClickedCheck__PM1();
	afx_msg void OnBnClickedCheck__PM2();
	afx_msg void OnBnClickedCheck__PM3();
	afx_msg void OnBnClickedCheck__PM4();
	afx_msg void OnBnClickedCheck__PM5();
	afx_msg void OnBnClickedCheck__PM6();

	afx_msg void OnBnClickedCheck__LL1();
	afx_msg void OnBnClickedCheck__LL2();

	DECLARE_MESSAGE_MAP()

	// ...
	CButton mBtn__LotID_Data;
	CButton mBtn__PortID_Data;

	CButton mCheck_PM1;
	CButton mCheck_PM2;
	CButton mCheck_PM3;
	CButton mCheck_PM4;
	CButton mCheck_PM5;
	CButton mCheck_PM6;

	CButton mCheck_LL1;
	CButton mCheck_LL2;

	void _Btn_Click__PMx(const int ll_id);
	void _Btn_Click__LLx(const int ll_id);

	CString _Get__MDx_Name();
	
	// ...
	CReportCtrl mList__Slot_Info;

	CButton mBtn__Single_Slot;
	CButton mBtn__Sel_Slot;
	CButton mBtn__Multi_Slot;
	CButton mBtn__Slot_All;
	CButton mBtn__Slot_Clear;

	void _Make__Slot_List();
	void _Add__Slot_List(const CStringArray& l_slot);
	void _Update__Slot_Step_Cnt();

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
	CLS__Slot_Step_Ctrl mSlot_Step;

	void _Update__Slot_Info();

	bool _Is__PMx_Check(const int pm_id);
	bool _Is__LLx_Check(const int ll_id);
	//

public:
	CStringArray sList__Slot_ID;

	CString sDir_Root;
	CString sDir_Sub;

	CString sPara__LotID;
	CString sPara__PortOD;
};
