#include "stdafx.h"
#include "Dlg__Compare_CFG.h"

#include "CObj__Compare_CFG__KEY_DEF.h"


// ...
int CDlg__Compare_CFG
::Set_Parameter(const int module_id)
{
	GObj__Parameter_Ctrl *p_para = pGObj_Res->pGOBJ_PARA_CTRL;
	CString str_data;

	// 
	{
		CString dir_root;

		CGX__SYSTEM_CTRL x_sys_ctrl;
		x_sys_ctrl->Get__GUI_DIR_EXE(dir_root);

		dir_root += "\\INCLUDE_FILE";

		CString inf_file;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_INF_FILE, inf_file);

		CString inf_path;
		inf_path.Format("%s\\%s", dir_root,inf_file);

		if(iREAL_MODE < 0)
		{
			printf(" * CDlg__Compare_CFG::Set_Parameter() ... \n");
			printf(" ** inf_path <- [%s] \n", inf_path);
		}

		_Upload__Inf_File(inf_path);
	}

	// 
	{
		p_para->Get_Constant_Data(pKEY__DATA_PMx_SIZE, str_data);
		iPM_SIZE = atoi(str_data);
		if(iPM_SIZE > DEF_PMx__SIZE)		iPM_SIZE = DEF_PMx__SIZE;
	}

	return 1;
}

// ...
int CDlg__Compare_CFG
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	int sx = p_st.x;
	int sy = p_st.y;
	int wx = p_et.x - p_st.x;
	int wy = p_et.y - p_st.y;

	MoveWindow(sx,sy,wx,wy,true);
	ShowWindow(SW_SHOW);
	return 1;
}
int CDlg__Compare_CFG
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}

