#include "stdafx.h"
#include "JGLEE__RECIPE_STD.h"

#include "Dlg__PROCESS_STD.h"
#include "CObj__PROCESS_STD__KEY_DEF.h"


RCP_INTERLOCK__GET_PROC(Interlock_Rcp__GET_PROC, CDlg__PROCESS_STD); 
RCP_INTERLOCK__GET_FNC(Interlock_Rcp__GET_FNC, CDlg__PROCESS_STD);



// ...
int CDlg__PROCESS_STD
::Set_Parameter(const int module_id)
{
	iMODULE_ID = module_id;

	// ...
	GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

	CString key_name;
	CString def_data;

	// Header ...
	{
		key_name = pKEY__ITEM_HEADER_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		
		if(def_data.CompareNoCase(STR__YES) == 0)
		{
			bActive__Item_Header = true;
			bShow__Item_Header   = true;
		}
		else if(def_data.CompareNoCase(STR__NO_SHOW) == 0)
		{
			bActive__Item_Header = false;
			bShow__Item_Header   = false;
		}
		else
		{
			bActive__Item_Header = false;
			bShow__Item_Header   = true;
		}

		//
		key_name = pKEY__ITEM_HEADER_FILE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Item_Header_File = def_data;

		key_name = pKEY__ITEM_HEADER_WIDTH;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		int width = atoi(def_data);
		if(width < 120)		width = 120;
		iDef__Item_Header_Width = width;
	}
	// Step ...
	{
		key_name = pKEY__ITEM_STEP_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);

		if(def_data.CompareNoCase(STR__YES) == 0)
		{
			bActive__Item_Step = true;
			bShow__Item_Step   = true;
		}
		else if(def_data.CompareNoCase(STR__NO_SHOW) == 0)
		{
			bActive__Item_Step = false;
			bShow__Item_Step   = false;
		}
		else
		{
			bActive__Item_Step = false;
			bShow__Item_Step   = true;
		}

		//
		key_name = pKEY__ITEM_STEP_FILE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Item_Step_File = def_data;

		key_name = pKEY__ITEM_STEP_WIDTH;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		int width = atoi(def_data);
		if(width < 120)		width = 120;
		iDef__Item_Step_Width = width;
	}
	// Tolerance ...
	{
		key_name = pKEY__ITEM_TOLERANCE_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		
		if(def_data.CompareNoCase(STR__YES) == 0)
		{
			bActive__Item_Tolerance = true;
			bShow__Item_Tolerance   = true;
		}
		else if(def_data.CompareNoCase(STR__NO_SHOW) == 0)
		{
			bActive__Item_Tolerance = false;
			bShow__Item_Tolerance   = false;
		}
		else
		{
			bActive__Item_Tolerance = false;
			bShow__Item_Tolerance   = true;
		}

		//
		key_name = pKEY__ITEM_TOLERANCE_FILE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Item_Tolerance_File = def_data;

		key_name = pKEY__ITEM_TOLERANCE_WIDTH;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		int width = atoi(def_data);
		if(width < 120)		width = 120;
		iDef__Item_Tolerance_Width = width;
	}

	// Pre ...
	{
		key_name = pKEY__RCP_PRE_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		if(def_data.CompareNoCase("YES") == 0)			bActive__Rcp_Pre = true;
		else											bActive__Rcp_Pre = false;

		key_name = pKEY__RCP_PRE_FOLDER;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Rcp_Pre_Folder = def_data;
	}
	// Main ...
	{
		key_name = pKEY__RCP_MAIN_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		if(def_data.CompareNoCase("YES") == 0)			bActive__Rcp_Main = true;
		else											bActive__Rcp_Main = false;

		key_name = pKEY__RCP_MAIN_FOLDER;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Rcp_Main_Folder = def_data;
	}
	// Post ..
	{
		key_name = pKEY__RCP_POST_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		if(def_data.CompareNoCase("YES") == 0)			bActive__Rcp_Post = true;
		else											bActive__Rcp_Post = false;

		key_name = pKEY__RCP_POST_FOLDER;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Rcp_Post_Folder = def_data;
	}

	// PMx LINK_USE ...
	{
		int i_limit = _CFG_PMx__SIZE;
		int i;

		for(i=0; i<i_limit; i++)
		{
			key_name.Format("PM%1d.LINK_USE", i+1);
			p_para_ctrl->Get_Constant_Data(key_name, def_data);

			if(def_data.CompareNoCase(STR__YES) == 0)			bActive__PMx_LINK_USE[i] = true;
			else												bActive__PMx_LINK_USE[i] = false;
		}
	}

	// SUMMARY MODE ...
	{
		bActive__Summary_Mode = false;
		bActive__Summary_User = false;

		key_name = pKEY__SUMMARY_MODE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);

		if(def_data.CompareNoCase(STR__ENABLE) == 0)
		{
			bActive__Summary_Mode = true;
		}
		if(def_data.CompareNoCase(STR__USER)   == 0)
		{
			bActive__Summary_Mode = true;
			bActive__Summary_User = true;
		}

		// ...
		int i_limit = _CFG__SUMMARY_ITEM_MAX;
		int i;

		for(i=0; i<i_limit; i++)
		{
			key_name.Format(pKEY__SUMMARY_ITEM_ID_X, i+1);
			p_para_ctrl->Get_Constant_Data(key_name, def_data);	

			iList__Summary_ID[i] = atoi(def_data);
		}
	}

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString dir_root;

		// UI ...
		{
			x_sys_ctrl->Get__GUI_DIR_EXE(dir_root);

			sDir__ROOT_UI = dir_root;

			dir_root += "\\INCLUDE_FILE";
			sDir__ROOT_INF = dir_root;
		}

		// EQP ...
		{
			if(iREAL_MODE < 0)
			{
				key_name = pKEY__TEST_MODULE_ID;
				p_para_ctrl->Get_Constant_Data(key_name, def_data);
				iMODULE_ID = atoi(def_data);
			}

			x_sys_ctrl->Get__SEQ_DIR_PROCESS(iMODULE_ID, dir_root);
			sDir__ROOT_EQP = dir_root;
		}

		m_Rcp_File.iMODULE_ID = iMODULE_ID;
	}

	// Interlock Dll ...
	if(!bActive__Interlock_Dll)
	{
		key_name = pKEY__RCP_INTERLOCK_DLL_NAME;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);

		sDef__Rcp_Interlock_Name = def_data;
		if(sDef__Rcp_Interlock_Name.GetLength() > 0)		
		{
			CString dll_path;
			dll_path.Format("%s\\%s", sDir__ROOT_INF,def_data);

			printf("=========================================================== \n");
			printf(" * interlock_dll <- [%s] \n", dll_path);

			if(xI_Rcp_Interlock_Ctrl->Link__DLL_NAME(dll_path, IInterlock_Rcp__GET_PROC,IInterlock_Rcp__GET_FNC, this) > 0)
			{
				bActive__Interlock_Dll = true;
				m_Rcp_File.pI_Rcp_Interlock_Ctrl = xI_Rcp_Interlock_Ctrl.Get_PTR();

				printf(" * interlock_dll <- OK !!! \n");
			}
			else
			{
				printf(" * interlock_dll <- ERROR !!! \n");
			}

			printf("=========================================================== \n\n");

			if(bActive__Interlock_Dll)
			{
				xI_Rcp_Interlock_Ctrl->Set__DIR_ROOT(sDir__ROOT_INF);
			}
		}
	}

	// RCP_TYPE - LINE_ID ...
	{
		key_name = pKEY__RCP_TYPE_LINE_ID;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		iDef__Rcp_Type__Line_ID = atoi(def_data);

		key_name = pKEY__RCP_TYPE_CHECK_DATA;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		sDef__Rcp_Type__Check_Data = def_data;
	}

	// RCP_INTERLOCK.SAVE_CHECK ...
	{
		key_name = pKEY__RCP_INTERLOCK_SAVE_CHECK;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		if(def_data.CompareNoCase(STR__YES) == 0)			bActive__Interlock_Save = true;
		else												bActive__Interlock_Save = false;
	}

	return 1;
}

int CDlg__PROCESS_STD::
Get_Link_Channel_List(CStringArray& l__link_ch)
{
	l__link_ch.RemoveAll();

	// ...
	CStringArray l__ch_name;

	if(bActive__Rcp_Pre)
	{
		m_Rcp_Header.Get__LINK_CHANNEL_LIST(l__ch_name);
		l__link_ch.Append(l__ch_name);
	}

	// ...
	{
		m_Rcp_Step.Get__LINK_CHANNEL_LIST(l__ch_name);
		l__link_ch.Append(l__ch_name);
	}

	if(bActive__Rcp_Post)
	{
		m_Rcp_Tolerance.Get__LINK_CHANNEL_LIST(l__ch_name);
		l__link_ch.Append(l__ch_name);
	}

	return 1;
}

int CDlg__PROCESS_STD
::Set_MoveWindow(const POINT& p_st, const POINT& p_et)
{
	// ...
	{
		int sx = p_st.x;
		int sy = p_st.y;
		int wx = p_et.x - p_st.x;
		int wy = p_et.y - p_st.y;

		MoveWindow(sx,sy,wx,wy,true);
		ShowWindow(SW_SHOW);
	}

	bActive__Show_Page = true;
	return 1;
}
int CDlg__PROCESS_STD
::Redraw_Page()
{
	Invalidate(TRUE);
	return 1;
}
