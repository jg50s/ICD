#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Report_Table.h"

#include "CObj__Report_Table__KEY_DEF.h"


// ...
int CDlg__Report_Table
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;
	CString str_data;

	// ...
	{
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_TABLE_ROW_MAX, str_data);
		iData__Table_Row_Max = atoi(str_data);
		if(iData__Table_Row_Max > _CFG__MSG_SIZE)			iData__Table_Row_Max =  _CFG__MSG_SIZE;

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_COL_WIDTH_INDEX, str_data);
		if(str_data.GetLength() < 1)		str_data = "60";
		iData__Col_Width_Index = atoi(str_data);

		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_COL_WIDTH_MSG, str_data);
		if(str_data.GetLength() < 1)		str_data = "580";
		iData__Col_Width_Msg = atoi(str_data);
	}

	if(bActive__Init_Table)
	{
		CListCtrl *p_table = &mList__Report_Table;
		_Make__Report_Table(p_table);
	}
	return 1;
}

int CDlg__Report_Table
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	// ...
	{
		CListCtrl* p_table = &mList__Report_Table;

		int t_sx = 2;
		int t_sy = 2;

		int t_ex = wx - 2;
		int t_ey = wy - 2;

		p_table->MoveWindow(t_sx,t_sy, t_ex-t_sx,t_ey-t_sy, true);
	}

	MoveWindow(sx,sy,wx,wy,true);
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__Report_Table
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}
