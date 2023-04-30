#include "stdafx.h"
#include "Dlg__PROCESS_STD.h"


// ...
int CDlg__PROCESS_STD::
Interlock_Rcp__GET_PROC(const int i_row,
				         const int i_col,
				         CString& str_data)
{
	/*
	if(m_pRecipeGrid != NULL)
	{
		CString in_data = m_pRecipeGrid->Get_Data_GridFrom(i_col, i_row);
		str_data.Format("%s",in_data);
	}
	*/
	return 1;
}

int CDlg__PROCESS_STD::
Interlock_Rcp__GET_FNC(const int main_fnc,
				       const int sub_fnc,
				       const CString& in_para,
				       const CStringArray& l_in_para,
				       CString& out_para,
				       CStringArray& l_out_para)
{

	return 11;
}
