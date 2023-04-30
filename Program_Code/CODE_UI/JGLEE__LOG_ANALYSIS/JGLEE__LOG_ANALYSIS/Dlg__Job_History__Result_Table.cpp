#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Job_History.h"


// ...
#define _CFG__JRT_COL_SIZE						8
#define _JRT_COL__NUMBER						0
#define _JRT_COL__JOBID	    					1
#define _JRT_COL__LOTID   						2
#define _JRT_COL__PORTID						3
#define _JRT_COL__CSTID							4
#define _JRT_COL__DATE							5
#define _JRT_COL__TIME							6
#define _JRT_COL__PATH							7


void CDlg__Job_History
::_Make__Result_Table(CReportCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = _CFG__JRT_COL_SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _JRT_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(35);
			}
			else if(i == _JRT_COL__JOBID)
			{
				l__col_name.Add("JOB ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__LOTID)
			{
				l__col_name.Add("LOT ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__PORTID)
			{
				l__col_name.Add("PTN");
				l__col_width.Add(40);
			}
			else if(i == _JRT_COL__CSTID)
			{
				l__col_name.Add("CST ID");
				l__col_width.Add(120);
			}
			else if(i == _JRT_COL__DATE)
			{
				l__col_name.Add("Date");
				l__col_width.Add(80);
			}
			else if(i == _JRT_COL__TIME)
			{
				l__col_name.Add("Time");
				l__col_width.Add(80);
			}
			else if(i == _JRT_COL__PATH)
			{
				l__col_name.Add("Path");
				l__col_width.Add(0);
			}
			else
			{
				continue;
			}
		}
	}

	// ...
	{
		p_table->DeleteAllItems();

		for(int i=0; i<_CFG__JRT_COL_SIZE; i++)
		{
			p_table->DeleteColumn(0);
		}
	}

	// ...
	{
		CString col_name;
		int col_cx;

		int limit = l__col_name.GetSize();
		int i;

		for(i=0; i<limit; i++)
		{
			col_name = l__col_name[i];
			col_cx   = (int) l__col_width[i];

			/*
			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}
			*/

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}

void CDlg__Job_History::
_Add__Result_Table(CReportCtrl *p_table, CLS__Job_Log_Ctrl* p_log_ctrl)
{
	COLORREF t_color = RGB(0,0,255);
	COLORREF b_color = RGB(255,255,255);

	// ...
	{
		p_table->DeleteAllItems();
		p_table->SetRedraw(FALSE);

		iResult_Table__Click_Pre_ID = -1;
	}

	// ...
	CString str__portid_check;
	mBtn_Option__PortID.GetWindowText(str__portid_check);

	CString str__jobid_check = mStr_Option__JobID;
	CString str__lotid_check = mStr_Option__LotID;
	CString str__cstid_check = mStr_Option__CSTID;

	// ...
	int r_index = 0;

	int i_limit = p_log_ctrl->Get__Log_Size();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__Job_Log_Info* p_info = p_log_ctrl->Get__Log_Info(i);

		CString str_data;
		int col;

		CString str_no;
		CString str_lpid;
		CString str_cstid;
		CString str_jobid;
		CString str_lotid;
		CString str_date = p_info->sLog_Date;
		CString str_time;
		CString str_path;

		int k_limit = p_info->sList_PortID.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			str_no.Format("%1d", r_index+1);
			str_lpid  = p_info->sList_PortID[k];
			str_jobid = p_info->sList_JobID[k];
			str_lotid = p_info->sList_LotID[k];
			str_cstid = p_info->sList_CstID[k];
			str_time  = p_info->sList_Time[k];
			str_path.Format("%s\\%s", p_info->sLog_Date,p_info->sList_Dir[k]);

			// PortID Option ...
			if(bActive_Option__PortID_All)
			{
				if(str_lpid.CompareNoCase(str__portid_check) != 0)
					continue;
			}
			// JobID Option ...
			{
				if(bActive_Option__JobID_Part)
				{
					if(str_jobid.Find(str__jobid_check) < 0)
						continue;
				}
				else if(bActive_Option__JobID_All)		
				{
					if(str_jobid.CompareNoCase(str__jobid_check) != 0)
						continue;
				}
			}
			// LotID Option ...
			{
				if(bActive_Option__LotID_Part)
				{
					if(str_lotid.Find(str__lotid_check) < 0)
						continue;
				}
				else if(bActive_Option__LotID_All)		
				{
					if(str_lotid.CompareNoCase(str__lotid_check) != 0)
						continue;
				}
			}
			// CSTID Option ...
			{
				if(bActive_Option__CSTID_Part)
				{
					if(str_lotid.Find(str__cstid_check) < 0)
						continue;
				}
				else if(bActive_Option__CSTID_All)		
				{
					if(str_lotid.CompareNoCase(str__cstid_check) != 0)
						continue;
				}
			}

			// ...
			{
				p_table->InsertItem(r_index, str_no, t_color,b_color);

				//
				col = _JRT_COL__JOBID;
				str_data = str_jobid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__LOTID;
				str_data = str_lotid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__PORTID;
				str_data = str_lpid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__CSTID;
				str_data = str_cstid;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__DATE;
				str_data = str_date;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__TIME;
				str_data = str_time;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);

				col = _JRT_COL__PATH;
				str_data = str_path;
				p_table->SetItem(r_index,col, LVIF_TEXT,str_data,0,0,0,0);
			}

			r_index++;
		}
	}

	p_table->SetRedraw(TRUE);

	_Clear__Slot_Info();
}

void CDlg__Job_History::
_Change_Color__Result_Table(CReportCtrl *p_table, const int r_index)
{
	CString str_data;
	int col;

	int p_index = _Get_Index__Number_Of_Result_Table(p_table, iResult_Table__Click_Pre_ID);
	if(p_index != r_index)
	{
		COLORREF t_color = RGB(0,0,0);
		COLORREF b_color = RGB(255,255,255);
		
		_Change_Color__Result_Table(p_table, p_index, t_color,b_color);
	}
	
	// ...
	{
		COLORREF t_color = RGB(255,255,255);
		COLORREF b_color = RGB(0,0,255);

		_Change_Color__Result_Table(p_table, r_index, t_color,b_color);
	}
}
void CDlg__Job_History::
_Change_Color__Result_Table(CReportCtrl *p_table, const int r_index, const COLORREF t_color,const COLORREF b_color)
{
	CString str_data;
	int col;

	// ...
	{
		col = _JRT_COL__NUMBER;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__JOBID;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__LOTID;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__PORTID;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__CSTID;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__DATE;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);

		col = _JRT_COL__TIME;
		str_data = p_table->GetItemText(r_index,col);
		p_table->SetItemText(r_index,col, str_data, t_color,b_color);
	}
}

int CDlg__Job_History::
_Get_Index__Number_Of_Result_Table(CReportCtrl *p_table, const int no_id)
{
	CString str_data;

	int i_limit = p_table->GetItemCount();
	int i;

	for(i=0; i<i_limit; i++)
	{
		str_data = p_table->GetItemText(i, _JRT_COL__NUMBER);
		if(no_id == atoi(str_data))		return i;
	}
	return -1;
}
int CDlg__Job_History::
_Get_Number__Index_Of_Result_Table(CReportCtrl *p_table, const int r_index)
{
	CString str_data = p_table->GetItemText(r_index, _JRT_COL__NUMBER);

	return atoi(str_data);
}

CString CDlg__Job_History::
_Get_JobID__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)		return "";

	return p_table->GetItemText(r_index, _JRT_COL__JOBID);
}
CString CDlg__Job_History::
_Get_CSTID__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)		return "";

	return p_table->GetItemText(r_index, _JRT_COL__CSTID);
}
CString CDlg__Job_History::
_Get_StartDate__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	if(r_index < 0)		return "";

	return p_table->GetItemText(r_index, _JRT_COL__DATE);
}

CString CDlg__Job_History::
_Get_LotID__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	return _Get_LotID__Result_Table(r_index);
}
CString CDlg__Job_History::
_Get_LotID__Result_Table(const int r_index)
{
	CListCtrl* p_table = &mList__Result_Table;

	return p_table->GetItemText(r_index, _JRT_COL__LOTID);
}

CString CDlg__Job_History::
_Get_PortID__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	return _Get_PortID__Result_Table(r_index);
}
CString CDlg__Job_History::
_Get_PortID__Result_Table(const int r_index)
{
	CListCtrl* p_table = &mList__Result_Table;

	return p_table->GetItemText(r_index, _JRT_COL__PORTID);
}

CString CDlg__Job_History::
_Get_Path__Result_Table()
{
	CListCtrl* p_table = &mList__Result_Table;

	int r_index = p_table->GetSelectionMark();
	return _Get_Path__Result_Table(r_index);
}
CString CDlg__Job_History::
_Get_Path__Result_Table(const int r_index)
{
	CListCtrl* p_table = &mList__Result_Table;

	return p_table->GetItemText(r_index, _JRT_COL__PATH);
}
