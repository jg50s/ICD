#include "stdafx.h"
#include "Dlg__PROCESS_STD.h"

#include "Macro_Function.h"


// ...
int CDlg__PROCESS_STD::
StringPAD_PopUp(const int row, 
				const int col,
				CString& out_data,
				CString& out_data2,
				int& dual_flag)
{
	CString title   = m_Grid.GetItemText(row, 0);
	CString in_data = m_Grid.GetItemText(row, col);

	if(col == 0)
	{
		in_data = "";
	}

	/*
	if((m_InterlockDll.GetLength() > 0)
	&& (iPAGE_TYPE == PAGE_TYPE__MAIN))
	{
		CString out_type;
		CString result_data;

		int flag = pI_Rcp_Interlock_Ctrl->Set__PROC(iModulID,row,col,in_data,out_type,result_data);

		if(flag > 0)
		{
			if(out_type.CompareNoCase(CMMD_TYPE__SETTO_STRING) == 0)
			{
				out_data = result_data;

				if(in_data.Compare(out_data) != 0)
				{
					return 1;
				}
				return -1;
			}
			else if((out_type.CompareNoCase(CMMD_TYPE__SETTO_STRING_DUAL_UP)   == 0)
				 || (out_type.CompareNoCase(CMMD_TYPE__SETTO_STRING_DUAL_DOWN) == 0))
			{
				out_data  = result_data;
				out_data2 = result_data;

				if(out_type.CompareNoCase(CMMD_TYPE__SETTO_STRING_DUAL_UP) == 0)
				{
					dual_flag = 1;
				}
				else
				{
					dual_flag = 2;
				}

				int str_len  = result_data.GetLength();
				int db_index = out_data.Find('	',0);

				if(db_index >= 0)
				{
					out_data.Delete(db_index,str_len-db_index);
					out_data2.Delete(0,db_index+1);
				}

				return 1;
			}
		}
	}
	*/

	// ...
	UIX__STRING_PAD_CTRL pad;

	if(pad->Popup(title,in_data,out_data) > 0)
	{
		if(in_data.Compare(out_data) != 0)
		{
			return 1;
		}
	}
	return -1;
}

int CDlg__PROCESS_STD::
DigitalPAD_PopUp(const bool active_string,
				 const CString input_list,
				 const int row, 
				 const int col,
				 CString& out_data)
{
	CString title   = m_Grid.GetItemText(row,0);
	CString in_data = m_Grid.GetItemText(row,col);

	if(col == 0)
	{
		in_data = "";
	}

	// ...
	CStringArray data_List;
	CString temp = input_list;

	char distinction = '/';

	if(active_string)		// STRING_ITEM
	{

	} 

	MACRO__Convert__LIST(distinction,temp, data_List);

	// ...
	UIX__DIGITAL_PAD_CTRL pad_ctrl;

	if(pad_ctrl->Popup(title,in_data,data_List, out_data) > 0)
	{
		if(in_data.CompareNoCase(out_data) != 0)
		{
			return 1;
		}
	}
	return -1;
}

int CDlg__PROCESS_STD::
AnalogPAD_PopUp(const int row, 
				const int col, 
				const CString& a_min,
				const CString& a_max, 
				CString& out_data)
{
	CString title   = m_Grid.GetItemText(row,0);
	CString in_data = m_Grid.GetItemText(row,col);

	if(col == 0)		in_data = "";

	// ...
	UIX__ANALOG_PAD_CTRL pad;

	if(pad->Popup(title,a_min,a_max,in_data,"", out_data) > 0)
	{
		if(in_data.Compare(out_data) != 0)
		{
			return 1;
		}
	}
	return -1;
}
