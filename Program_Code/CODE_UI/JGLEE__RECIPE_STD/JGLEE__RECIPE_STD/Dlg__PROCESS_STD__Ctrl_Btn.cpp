#include "stdafx.h"
#include "Dlg__PROCESS_STD.h"

#include "CObj__PROCESS_STD__KEY_DEF.h"

#include "Dlg__SaveAs.h"
#include "Dlg__GoTo_Step.h"
#include "Dlg__Summary_Report.h"


// ...
void CDlg__PROCESS_STD::OnBnClickedBtn__File_New()
{
	int rcp_folder = _RCP_FOLDER__MAIN;
	_Change__Rcp_Folder(rcp_folder);
	
	CString dir_sub = _Get__Rcp_Folder(rcp_folder);
	mData__Sel_Folder_Name.SetWindowText(dir_sub);

	CString cur_file = "";
	mData__Sel_File_Name.SetWindowText(cur_file);

	_Add__Nes_Step();

	// ...
	int rcp_type = _RCP_TYPE__STEP;
	_Change__Rcp_Type(rcp_type);

	CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;
	_Draw__Grid_Table(p_rcp_item);
}
void CDlg__PROCESS_STD::OnBnClickedBtn__File_Save()
{
	if(mCtrl__Summary_Save_Check.GetCheck() > 0)
	{
		if(_Fnc__Summary_Check() < 0)		return;
	}

	// ...
	CString dir_sub;
	CString cur_file;

	mData__Sel_Folder_Name.GetWindowText(dir_sub);
	mData__Sel_File_Name.GetWindowText(cur_file);

	_Save__File_Data(dir_sub, cur_file);
	OnBnClickedBtn__File_Refresh();
}
void CDlg__PROCESS_STD::OnBnClickedBtn__File_SaveAs()
{
	if(mCtrl__Summary_Save_Check.GetCheck() > 0)
	{
		if(_Fnc__Summary_Check() < 0)		return;
	}

	// ...
	_Fnc__File_Save();
	OnBnClickedBtn__File_Refresh();
}
void CDlg__PROCESS_STD::OnBnClickedBtn__Send_File()
{
	_Fnc__File_Send();
}

void CDlg__PROCESS_STD::_Fnc__File_Save()
{
	CString dir_sub;
	CString cur_file;

	mData__Sel_Folder_Name.GetWindowText(dir_sub);
	mData__Sel_File_Name.GetWindowText(cur_file);

	printf("_Fnc__File_Save() \n");
	printf("  * bActive__Rcp_Pre  <- %1d \n", bActive__Rcp_Pre);
	printf("  * bActive__Rcp_Main <- %1d \n", bActive__Rcp_Main);
	printf("  * bActive__Rcp_Post <- %1d \n", bActive__Rcp_Post);

	printf("  * Before ... \n");
	printf("    dir_sub  <- [%s] \n", dir_sub);
	printf("    cur_file <- [%s] \n", cur_file);

	int rcp_folder = _Get__Rcp_Folder();

	// ...
	CDlg__SaveAs dlg;

	dlg.iMODULE_ID   = iMODULE_ID;
	dlg.bActive_SEND = false;

	dlg.bActive__Rcp_Pre  = bActive__Rcp_Pre;
	dlg.bActive__Rcp_Main = bActive__Rcp_Main;
	dlg.bActive__Rcp_Post = bActive__Rcp_Post;

	dlg.iPara__Dir_Sub = rcp_folder;
	dlg.sPara__In_Data = cur_file;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	rcp_folder = dlg.iPara__Dir_Sub;

	dir_sub  = _Get__Rcp_Folder(rcp_folder);
	cur_file = dlg.sPara__Out_Data;

	printf("  * After ... \n");
	printf("    dir_sub  <- [%s] \n", dir_sub);
	printf("    cur_file <- [%s] \n", cur_file);

	mData__Sel_Folder_Name.SetWindowText(dir_sub);
	mData__Sel_File_Name.SetWindowText(cur_file);

	_Save__File_Data(dir_sub, cur_file);
}
void CDlg__PROCESS_STD::_Fnc__File_Send()
{
	CString src_path;
	CString trg_path;

	// ...
	{
		CString dir_sub;
		CString cur_file;

		mData__Sel_Folder_Name.GetWindowText(dir_sub);
		mData__Sel_File_Name.GetWindowText(cur_file);

		int rcp_folder = _Get__Rcp_Folder();

		src_path.Format("%s\\%s\\%s.rcp", sDir__ROOT_EQP,dir_sub,cur_file);

		// ...
		CDlg__SaveAs dlg;

		dlg.iMODULE_ID   = iMODULE_ID;
		dlg.bActive_SEND = true;

		int i_limit = _CFG_PMx__SIZE;
		int i;

		for(i=0; i<i_limit; i++)
			dlg.bActive__PMx[i] = bActive__PMx_LINK_USE[i];

		dlg.bActive__Rcp_Pre  = bActive__Rcp_Pre;
		dlg.bActive__Rcp_Main = bActive__Rcp_Main;
		dlg.bActive__Rcp_Post = bActive__Rcp_Post;

		dlg.iPara__Dir_Sub = rcp_folder;
		dlg.sPara__In_Data = cur_file;

		if(dlg.DoModal() != IDOK)
		{
			return;
		}

		int eqp_id = dlg.iMODULE_ID;
		if(eqp_id == iMODULE_ID)			return;

		// ...
		CGX__SYSTEM_CTRL x_sys_ctrl;

		CString dir_eqp;
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(eqp_id, dir_eqp);

		cur_file = dlg.sPara__Out_Data;

		trg_path.Format("%s\\%s\\%s.rcp", dir_eqp,dir_sub,cur_file);
	}

	//...
	{
		printf(" * src_path <- [%s] \n", src_path);
		printf(" * trg_path <- [%s] \n", trg_path);

		BOOL b_success = CopyFile(src_path,trg_path, TRUE);
		if(!b_success)
		{
			CString str_title;
			CString str_msg;

			str_title = "Check the file path.";

			str_msg  = "The same file name exists. \n";
			str_msg += "Should I overwrite it?";

			int id_yes = MessageBox(str_msg,str_title, MB_YESNO | MB_ICONQUESTION);

			printf(" ** msg : [%1d] [%1d] \n", id_yes,IDYES);
			if(id_yes != IDYES)			return;
		}

		CopyFile(src_path,trg_path, FALSE);
		printf(" * Copy OK !!! \n");
	}
}

void CDlg__PROCESS_STD::OnBnClickedBtn__File_Delete()
{
	CString dir_sub;
	CString file_name;

	mData__Sel_File_Name.GetWindowText(file_name);
	mData__Sel_Folder_Name.GetWindowText(dir_sub);

	CString file_info;
	file_info.Format("%s\\%s.rcp", dir_sub,file_name);

	// ...
	CString str_title;
	CString str_msg;
	CString str_bff;

	str_title = "Do you want to delete this file ?";

	str_msg  = "Delete the file ? \n";
	str_bff.Format("File : \"%s\" \n", file_info);
	str_msg += str_bff;

	int r_flag = MessageBox(str_msg, str_title, MB_YESNO | MB_ICONINFORMATION);
	if(r_flag != IDYES)			return;

	// ...
	CString file_path;

	file_path.Format("%s\\%s", sDir__ROOT_EQP,file_info);
	remove(file_path);

	OnBnClickedBtn__File_New();
	OnBnClickedBtn__File_Refresh();
}
void CDlg__PROCESS_STD::OnBnClickedBtn__File_CSV()
{
	CString csv_path;

	// ...
	{
		CString file_name;
		mData__Sel_File_Name.GetWindowText(file_name);

		// ...
		CString str_drv = "C";
		CString str_dir = "PM_RCP_CSV";

		char lpstrfile[MAX_PATH];
		char str_initdir[MAX_PATH];

		strcpy(lpstrfile, file_name);		
		sprintf(str_initdir, "%s:\\%s\\",str_drv,str_dir);

		CreateDirectory(str_initdir,NULL);

		//
		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = this->m_hWnd;
		ofn.lpstrFilter = "csv File (*.csv)\0";
		ofn.lpstrFile = lpstrfile;
		ofn.nMaxFile = 256;
		ofn.lpstrDefExt = "csv";
		ofn.lpstrTitle = "Input file name.";
		ofn.lpstrInitialDir = str_initdir;

		if(GetSaveFileName(&ofn) == 0)
		{
			return;
		}

		csv_path = ofn.lpstrFile;
	}

	_Save__CSV_Data(csv_path);
}
void CDlg__PROCESS_STD::OnBnClickedBtn__File_Undo()
{
	if(bActive__Rcp_item_Change)
	{
		CString str_title;
		CString str_msg;

		str_title = "Do you want to execute \"Undo\" command ?";

		str_msg  = "There are changes.";
		str_msg += "\n";
		str_msg += "Do you want to continue with the undo command ?";
		str_msg += "\n";

		int r_flag = MessageBox(str_msg, str_title, MB_YESNO | MB_ICONINFORMATION);
		if(r_flag != IDYES)			return;
	}

	// ...
	CString dir_sub;
	CString file_name;

	mData__Sel_File_Name.GetWindowText(file_name);
	mData__Sel_Folder_Name.GetWindowText(dir_sub);

	CString file_info;
	file_info.Format("%s\\%s.rcp", dir_sub,file_name);

	CString file_path;
	file_path.Format("%s\\%s", sDir__ROOT_EQP,file_info);

	m_Rcp_File.Upload__RCP_FILE(this->m_hWnd, file_path);

	_Draw__Grid_Table(pCur_Rcp_Item);
	_Init__Step_Ctrl_Btn();
}

void CDlg__PROCESS_STD::OnBnClickedBtn__Summary_View()
{
	_Fnc__Summary_Check();
}
void CDlg__PROCESS_STD::OnBnClickedCheck__Summary_Save()
{

}
int  CDlg__PROCESS_STD::_Fnc__Summary_Check()
{
	CDlg__Summary_Report dlg;

	for(int i=0; i<_CFG__SUMMARY_ITEM_MAX; i++)
	{
		int id = iList__Summary_ID[i];
		if(id < 1)		continue;

		dlg.iList__Item_ID.Add(id);
	}

	dlg.pAddr__Rcp_Item = &m_Rcp_Step;
	dlg.pAddr__Rcp_File = &m_Rcp_File;

	dlg.iMODULE_ID = iMODULE_ID;
	dlg.pI_Rcp_Interlock_Ctrl = xI_Rcp_Interlock_Ctrl.Get_PTR();

	if(dlg.DoModal() == IDOK)		return 1;
	return -1;
}

void CDlg__PROCESS_STD::OnBnClickedBtn__Step_Append()
{
	CString str_data;

	mCtrl__Sel_Step_ID.GetWindowText(str_data);
	int st_id = atoi(str_data);
	if(st_id < 1)		return;

	m_Rcp_File.Append__STEP_ID(st_id, -1);
	_Append__Grid_Table(pCur_Rcp_Item, -1);

	// ...
	st_id = m_Rcp_File.Get__Step_Size();
	printf(" * Step_Append <- [%1d] \n", st_id);

	_GoTo__Step_ID(st_id);
}
void CDlg__PROCESS_STD::OnBnClickedBtn__Step_Copy()
{
	CString str_data;

	mCtrl__Sel_Step_ID.GetWindowText(str_data);
	int st_id = atoi(str_data);
	if(st_id < 1)		return;

	int st_next = st_id + 1;
	m_Rcp_File.Append__STEP_ID(st_id, st_next);
	_Append__Grid_Table(pCur_Rcp_Item, st_next);

	// ...
	st_id = st_next;
	printf(" * Step_Copy <- [%1d] \n", st_id);

	_GoTo__Step_ID(st_id);
}
void CDlg__PROCESS_STD::OnBnClickedBtn__Step_Move()
{
	CString str_data;

	mData__Sel_Step_Count.GetWindowText(str_data);
	int st_max = atoi(str_data);

	mCtrl__Sel_Step_ID.GetWindowText(str_data);
	int st_id = atoi(str_data);
	if(st_id < 1)		return;

	// ...
	CDlg__GoTo_Step dlg;

	dlg.iPara__STEP_MAX = st_max;
	dlg.iPara__SEL_ID   = st_id;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	// ...
	int next_id = dlg.iPara__SEL_ID;
	m_Rcp_File.Move__STEP_ID(st_id, next_id);

	// ...
	int first_id = st_id;
	int end_id = next_id;

	if(st_id > next_id)		
	{
		first_id = next_id;
		end_id = st_id;
	}

	printf(" * Step_Move : [%1d] -> [%1d] \n", first_id,end_id);

	_Append__Grid_Table(pCur_Rcp_Item, first_id);
	_GoTo__Step_ID(next_id);
}
void CDlg__PROCESS_STD::OnBnClickedBtn__Step_Delete()
{
	CString str_data;

	mCtrl__Sel_Step_ID.GetWindowText(str_data);
	int st_id = atoi(str_data);
	if(st_id < 1)		return;

	printf(" * Step_Delete : [%1d] \n", st_id);

	m_Rcp_File.Delete__STEP_ID(st_id);
	_Append__Grid_Table(pCur_Rcp_Item, st_id);

	_GoTo__Step_ID(st_id);
}


// ...
CString CDlg__PROCESS_STD::
_Get__Rcp_Type()
{
	if(mCheck__Rcp_Pre.GetCheck()  > 0)		return "PRE";
	if(mCheck__Rcp_Post.GetCheck() > 0)		return "POST";

	return "MAIN";
}

CString CDlg__PROCESS_STD::
_Get__Channel_Type(const int ch_type)
{
	if(ch_type == _CH_TYPE__ANALOG)			return "A";
	if(ch_type == _CH_TYPE__DIGITAL)		return "D";

	return "S";
}

int CDlg__PROCESS_STD::
_Add__Nes_Step()
{
	m_Rcp_File.Clear__RCP_INFO();

	// ...
	CStringArray l_ch_name;
	CUIntArray   l_ch_type;
	CStringArray l_io_list;

	// Header Recipe .....
	if(bActive__Item_Header)
	{
		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Header;
		
		int i_imit = p_rcp_item->Get__ITEM_SIZE();
		int i;

		for(i=1; i<i_imit; i++)
		{
			CDS__Rcp_Item m_item;

			if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
			if(m_item.bPara__CATEGORY_ACTIVE)						continue;

			l_ch_name.Add(m_item.sPara__CH_NAME);
			l_ch_type.Add(m_item.iPara__CH_TYPE);
			l_io_list.Add(m_item.sPara__D_LIST);
		}
	}

	// Step & Tolerance Recipe ...
	{
		// Step Item ...
		{
			CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;

			int i_imit = p_rcp_item->Get__ITEM_SIZE();
			int i;

			for(i=1; i<i_imit; i++)
			{
				CDS__Rcp_Item m_item;

				if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
				if(m_item.bPara__CATEGORY_ACTIVE)						continue;

				l_ch_name.Add(m_item.sPara__CH_NAME);
				l_ch_type.Add(m_item.iPara__CH_TYPE);
				l_io_list.Add(m_item.sPara__D_LIST);
			}
		}
		
		// Tolerance Item ...
		if(bActive__Item_Tolerance)
		{
			CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Tolerance;

			int i_imit = p_rcp_item->Get__ITEM_SIZE();
			int i;

			for(i=1; i<i_imit; i++)
			{
				CDS__Rcp_Item m_item;

				if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
				if(m_item.bPara__CATEGORY_ACTIVE)						continue;;

				l_ch_name.Add(m_item.sPara__CH_NAME);
				l_ch_type.Add(m_item.iPara__CH_TYPE);
				l_io_list.Add(m_item.sPara__D_LIST);
			}
		}
	}

	m_Rcp_File.Add__NEW_STEP_OF_RCP_INFO(l_ch_name,l_ch_type,l_io_list);
	return 1;
}
int CDlg__PROCESS_STD::
_Save__File_Data(const CString& dir_sub, const CString& cur_file)
{
	if(_Get__Save_InterLock() < 0)			return -1;

	// ...
	CString file_data;
	CString str_data;

	// ...
	int step_id = 1;

	// ...
	{
		str_data.Format("@,%1d;\n", step_id);
		file_data += str_data;
	}

	// Header Recipe .....
	if(bActive__Item_Header)
	{
		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Header;
		
		int i_imit = p_rcp_item->Get__ITEM_SIZE();
		int i;

		for(i=1; i<i_imit; i++)
		{
			CDS__Rcp_Item m_item;

			if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
			if(m_item.bPara__CATEGORY_ACTIVE)						continue;

			// ...
			int i_type = m_item.iPara__CH_TYPE;

			CString ch_name = m_item.sPara__CH_NAME;
			CString ch_type = _Get__Channel_Type(i_type);
			CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);

			if(((i_type == _CH_TYPE__DIGITAL) || (i_type == _CH_TYPE__ANALOG == 0))
			&& (ch_name.GetLength() > 0) && (ch_data == ""))
			{
				CString str_title;
				CString str_msg;
				CString str_bff;

				str_title = "Header Recipe : Save Error !";

				str_msg  = "You can't save the recipe file !";
				str_msg += "\n";
				str_msg += "You have to input data without blank at Digital or Analog Items !!";
				str_msg += "\n";
				str_bff.Format("Item Position : %1d  (%s)", i,m_item.sPara__RCP_TITLE);					
				str_msg += str_bff;	
				str_msg += "\r\n";

				MessageBox(str_msg,str_title, MB_OK|MB_ICONERROR);
				return -1;
			}

			// ...
			{
				str_data.Format("&,%s,%s,%s;\n", ch_type,ch_name,ch_data);
				file_data += str_data;
			}
		}
	}

	// Step & Tolerance Recipe ...
	{
		int st_limit = m_Rcp_File.Get__Step_Size();
		int st_i;

		for(st_i=0; st_i<st_limit; st_i++)
		{
			step_id  = st_i + 1;

			if(step_id > 1)
			{
				str_data.Format("@,%1d;\n", step_id);
				file_data += str_data;
			}

			// Step Item ...
			{
				CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;

				int i_imit = p_rcp_item->Get__ITEM_SIZE();
				int i;

				for(i=1; i<i_imit; i++)
				{
					CDS__Rcp_Item m_item;

					if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
					if(m_item.bPara__CATEGORY_ACTIVE)						continue;

					// ...
					int i_type = m_item.iPara__CH_TYPE;

					CString ch_name = m_item.sPara__CH_NAME;
					CString ch_type = _Get__Channel_Type(i_type);
					CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);

					if(iDef__Rcp_Type__Line_ID == i)
					{
						bool active__save_check = false;

						if(sDef__Rcp_Type__Check_Data.CompareNoCase(ch_data) == 0)
						{
							active__save_check = true;
						}
						if(bActive__Interlock_Save)
						{
							active__save_check = true;
						}

						if(active__save_check)
						{
							if(bActive__Interlock_Dll)
							{
								CString err_msg;

								int save_flag = xI_Rcp_Interlock_Ctrl->Call__STEP_SAVE(iMODULE_ID, step_id, err_msg);
								if(save_flag < 0)
								{
									CString str_title;
									CString str_msg;

									str_title = "Step Recipe : Save Error !";

									str_msg.Format("Step(%1d) - Parameter Error ! \n", step_id);
									str_msg += "\n";
									str_msg += err_msg;

									MessageBox(str_msg,str_title, MB_OK|MB_ICONERROR);
									return -1;
								}
							}
						}
					}

					if(i_type == _CH_TYPE__SUB_PARA)
					{
						if(bActive__Interlock_Dll)
						{
							CStringArray l_ch_name;
							CStringArray l_ch_type;
							CStringArray l_ch_data;

							if(xI_Rcp_Interlock_Ctrl->Get__ALL_CHANNEL_OF_SUB_PAGE(iMODULE_ID,step_id, l_ch_name,l_ch_type,l_ch_data) > 0)
							{
								int k_limit = l_ch_name.GetSize();
								int k;

								for(k=0;k<k_limit;k++)
								{
									str_data.Format("&,%s,%s,%s;\n", l_ch_type[k],l_ch_name[k],l_ch_data[k]);
									file_data += str_data;
								}
								continue;
							}

							// ...
							{
								CString str_title;
								CString str_msg;
								CString str_bff;	

								str_title = "Step Recipe : Sub-Parameter Error !";

								str_msg  = "You can't save the recipe file !";
								str_msg += "\n";

								str_bff.Format("Please, check the sub-parameter of step(%1d) item(%1d).", step_id,i);
								str_msg += str_bff;
								str_msg += "\n";

								MessageBox(str_msg,str_title, MB_OK|MB_ICONERROR);
								return -1;
							}
						}
					}
					else
					{
						if(((i_type == _CH_TYPE__DIGITAL) || (i_type == _CH_TYPE__ANALOG == 0))
						&& (ch_name.GetLength() > 0) && (ch_data == ""))
						{
							CString str_title;
							CString str_msg;
							CString str_bff;

							str_title = "Header Recipe : Save Error !";

							str_msg  = "You can't save the recipe file !";
							str_msg += "\n";
							str_msg += "You have to input data without blank at Digital or Analog Items !!";
							str_msg += "\n";
							str_bff.Format("Item Position (%s) : Step(%1d) Item(%1d)", m_item.sPara__RCP_TITLE,step_id,i);
							str_msg += str_bff;	
							str_msg += "\r\n";

							MessageBox(str_msg,str_title, MB_OK|MB_ICONERROR);
							return -1;
						}

						// ...
						{
							str_data.Format("&,%s,%s,%s;\n", ch_type,ch_name,ch_data);
							file_data += str_data;
						}
					}
				}
			}

			// Tolerance Item ...
			if(bActive__Item_Tolerance)
			{
				CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Tolerance;

				int i_imit = p_rcp_item->Get__ITEM_SIZE();
				int i;

				for(i=1; i<i_imit; i++)
				{
					CDS__Rcp_Item m_item;

					if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;
					if(m_item.bPara__CATEGORY_ACTIVE)						continue;;

					// ...
					int i_type = m_item.iPara__CH_TYPE;

					CString ch_name = m_item.sPara__CH_NAME;
					CString ch_type = _Get__Channel_Type(i_type);
					CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);

					if(((i_type == _CH_TYPE__DIGITAL) || (i_type == _CH_TYPE__ANALOG == 0))
					&& (ch_name.GetLength() > 0) && (ch_data == ""))
					{
						CString str_title;
						CString str_msg;
						CString str_bff;

						str_title = "Tolerance Recipe : Save Error !";

						str_msg  = "You can't save the recipe file !";
						str_msg += "\n";
						str_msg += "You have to input data without blank at Digital or Analog Items !!";
						str_msg += "\n";
						str_bff.Format("Item Position (%s) : Step(%1d) Item(%1d)", m_item.sPara__RCP_TITLE,step_id,i);
						str_msg += str_bff;	
						str_msg += "\r\n";

						MessageBox(str_msg,str_title, MB_OK|MB_ICONERROR);
						return -1;
					}

					// ...
					{
						str_data.Format("&,%s,%s,%s;\n", ch_type,ch_name,ch_data);
						file_data += str_data;
					}
				}
			}

			// ...
		}
	}

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;

		CString dir_proc;
		x_sys_ctrl->Get__SEQ_DIR_PROCESS(iMODULE_ID, dir_proc);

		CString file_path;
		file_path.Format("%s\\%s\\%s.%s", dir_proc,dir_sub,cur_file,"rcp");

		// ...
		GObj__Parameter_Ctrl *p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;

		CString ch_data;
		p_para_ctrl->Get_Channel_Data(pKEY__CH_FILE_LOCK_FLAG, ch_data);
		
		if(ch_data.CompareNoCase(STR__YES) == 0)
		{
			MessageBox(file_path, 
					   "_Save__File_Data() : Now, EQP-program is uploading recipe file - Error !",
				       MB_OK|MB_TOPMOST);
			           return -1;
		}

		p_para_ctrl->Set_Suffix_Feedback(pKEY__CH_FILE_LOCK_FLAG, STR__YES);

		// ...
		{
			FILE *fp = fopen(file_path, "w");
			if(fp == NULL)
			{
				MessageBox(file_path, "_Save__File_Data() : File Path - Error !", MB_OK | MB_ICONERROR);

				p_para_ctrl->Set_Suffix_Feedback(pKEY__CH_FILE_LOCK_FLAG, "");
				return -1;
			}
			else
			{
				fputs(file_data,fp);
				fclose(fp);

				p_para_ctrl->Set_Suffix_Feedback(pKEY__CH_FILE_LOCK_FLAG, "");
			}
		}

		// ...
		{
			CString csv_log;
			CString csv_data = _Get__CSV_Data();

			csv_log.Format("path : %s \n", file_path);
			csv_log += csv_data;
			csv_log += "\n";
		
			xI_Log_Ctrl->Write__LOG(csv_log);
		}
	}

	bActive__Rcp_item_Change = false;

	/*
	// ...
	{		
		CString log_msg;
		log_msg.Format("File Save : Recipe Path <- \"%s\" \n", log_file_path);

		CString step_info;
		_Get_PM_Step_Info(step_info);
		log_msg += step_info;

		xFile_Log_Ctrl->Write__LOG(log_msg);							
	}
	*/
	return 1;
}
int CDlg__PROCESS_STD::
_Save__CSV_Data(const CString& csv_path)
{
	CString file_data = _Get__CSV_Data();

	// ...
	{
		FILE *fp = fopen(csv_path, "w");

		if(fp == NULL)
		{
			MessageBox(csv_path, "_Save__CSV_Data() : File Path - Error !", MB_OK | MB_ICONERROR);
			return -1;
		}
		else
		{
			fputs(file_data, fp);
			fclose(fp);
		}
	}
	return 1;
}
CString CDlg__PROCESS_STD::
_Get__CSV_Data()
{
	CString file_data;
	CString str_data;

	// ...
	int step_id;

	// Header Recipe .....
	if(bActive__Item_Header)
	{
		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Header;
		
		int i_imit = p_rcp_item->Get__ITEM_SIZE();
		int i;

		// ...
		{
			file_data += "Header Recipe,\n";

			str_data.Format("StepID,1,\n");
			file_data += str_data;
		}

		for(i=1; i<i_imit; i++)
		{
			CDS__Rcp_Item m_item;
			if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;

			CString ch_title = m_item.sPara__RCP_TITLE;

			if(m_item.bPara__CATEGORY_ACTIVE)
			{
				str_data.Format("%s,\n", ch_title);
				file_data += str_data;
				continue;
			}

			CString str_tap = "";
			if(m_item.bPara__CHILD_ACTIVE)		str_tap = "  ";

			// ...
			{
				CString ch_name = m_item.sPara__CH_NAME;
				CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);

				str_data.Format("%s%s,%s,\n", str_tap,ch_title,ch_data);
				file_data += str_data;
			}
		}
	}

	// Step & Tolerance Recipe ...
	{
		// Step Item ...
		{
			CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;

			int i_imit = p_rcp_item->Get__ITEM_SIZE();
			int i;

			int st_limit = m_Rcp_File.Get__Step_Size();
			int st_i;

			// ...
			file_data += "Step Recipe,\n";

			for(st_i=0; st_i<st_limit; st_i++)
			{
				step_id  = st_i + 1;

				if(step_id == 1)
				{
					str_data.Format("StepID,");
					file_data += str_data;
				}

				// ...
				{
					str_data.Format("%1d,", step_id);
					file_data += str_data;
				}
			}
			file_data += "\n";

			for(i=1; i<i_imit; i++)
			{
				CDS__Rcp_Item m_item;
				if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;

				CString ch_title = m_item.sPara__RCP_TITLE;
				int     ch_type = m_item.iPara__CH_TYPE;
				CString ch_name = m_item.sPara__CH_NAME;

				for(st_i=0; st_i<st_limit; st_i++)
				{
					step_id = st_i + 1;

					if(m_item.bPara__CATEGORY_ACTIVE)
					{
						str_data.Format("%s,", ch_title);
						file_data += str_data;
						break;
					}

					CString str_tap = "";
					if(m_item.bPara__CHILD_ACTIVE)		str_tap = "  ";

					if(ch_type == _CH_TYPE__SUB_PARA)
					{
						str_data.Format("%s,\n", ch_title);
						file_data += str_data;

						if(bActive__Interlock_Dll)
						{
							int db_index = 0;
							CString db_name;
							CStringArray l_data;

							while(xI_Rcp_Interlock_Ctrl->Get__ALL_STEP_INFO_OF_ITEM(iMODULE_ID,db_index, db_name,l_data) > 0)
							{
								db_index++;

								int k_limit = l_data.GetSize();
								int k;

								for(k=0; k<k_limit; k++)
								{
									if(k == 0)
									{
										str_data.Format("  %02d - %s,", db_index,db_name);
										file_data += str_data;
									}

									if(k < st_limit)
									{
										str_data.Format("%s,", l_data[k]);
										file_data += str_data;
									}
								}
								file_data += "\n";
							}
						}
						break;
					}
					else
					{
						if(step_id == 1)
						{
							str_data.Format("%s%s,", str_tap,ch_title);
							file_data += str_data;
						}

						// ...
						{
							CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);

							str_data.Format("%s,", ch_data);
							file_data += str_data;							
						}
					}
				}
				file_data += "\n";
			}
		}

		// Tolerance Item ...
		if(bActive__Item_Tolerance)
		{
			CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Tolerance;

			int i_imit = p_rcp_item->Get__ITEM_SIZE();
			int i;

			int st_limit = m_Rcp_File.Get__Step_Size();
			int st_i;

			// ...
			file_data += "Tolerance Recipe,\n";

			for(st_i=0; st_i<st_limit; st_i++)
			{
				step_id  = st_i + 1;

				if(step_id == 1)
				{
					str_data.Format("StepID,");
					file_data += str_data;
				}

				// ...
				{
					str_data.Format("%1d,", step_id);
					file_data += str_data;
				}
			}
			file_data += "\n";

			for(i=1; i<i_imit; i++)
			{
				CDS__Rcp_Item m_item;

				if(p_rcp_item->Get__ITEM_INFO(i, &m_item) < 0)			continue;

				// ...
				CString ch_title = m_item.sPara__RCP_TITLE;
				CString ch_name  = m_item.sPara__CH_NAME;

				for(st_i=0; st_i<st_limit; st_i++)
				{
					step_id  = st_i + 1;

					if(m_item.bPara__CATEGORY_ACTIVE)
					{
						str_data.Format("%s,", ch_title);
						file_data += str_data;
						break;
					}

					CString str_tap = "";
					if(m_item.bPara__CHILD_ACTIVE)		str_tap = "  ";

					if(step_id == 1)
					{
						str_data.Format("%s%s,", str_tap,ch_title);
						file_data += str_data;
					}

					// ...
					{
						CString ch_data = m_Rcp_File.Get__Step_Data(step_id,ch_name);
						
						str_data.Format("%s,", ch_data);
						file_data += str_data;
					}
				}
				file_data += "\n";
			}
		}

		// ...
	}

	return file_data;
}


// ...
#define  SAVE_CHECK__STEP					1
#define  SAVE_CHECK__HEADER					2
#define  SAVE_CHECK__TOLERANCE				3
#define  SAVE_CHECK__RECOVERY				4
#define  SAVE_CHECK__END					5

int  CDlg__PROCESS_STD::
_Get__Save_InterLock()
{
	if(bActive__Interlock_Dll)
	{
		CInfo__Rcp_Item* p_rcp_item = &m_Rcp_Step;

		int step_size = m_Rcp_File.Get__Step_Size();
		int para_size = p_rcp_item->Get__ITEM_SIZE();

		for(int st_i=1; st_i<step_size; st_i++)
		{
			CStringArray l_data;

			for(int para_j=1; para_j<para_size; para_j++)
			{
				CDS__Rcp_Item m_item;
				p_rcp_item->Get__ITEM_INFO(para_j, &m_item);

				CString ch_data = m_Rcp_File.Get__Step_Data(st_i, m_item.sPara__CH_NAME); 
				l_data.Add(ch_data);
			}

			int flag = xI_Rcp_Interlock_Ctrl->Set__FNC(iMODULE_ID, SAVE_CHECK__STEP,st_i, "",l_data);
			if(flag < 0)
			{
				return -1;
			}
		}
	}

	return 1;
}
