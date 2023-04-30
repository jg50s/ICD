#include "stdafx.h"
#include "JGLEE__LOG_TMC.h"

#include "CObj__DA_Log_STD.h"
#include "Macro_Function.h"


// ...
int  CDlg__DA_Log_STD
::_Upload__DA_File(const CString& file_path,
				   const CString& file_portid)
{
	CStringArray l_portid;
	CStringArray l_slotid;
	CStringArray l_module;
	
	CStringArray l_off_r;
	CStringArray l_off_t;
	CStringArray l_off_x;
	CStringArray l_off_y;
	
	CStringArray l_lotid;
	CStringArray l_ppid;
	CStringArray l_arm_type;
	CStringArray l_arm_act;
	CStringArray l_end_time;

	CStringArray l_line;
	CString file_data = "";
	
	MACRO__Get_File_Data(file_path, file_data);
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	int i_len = l_line.GetSize();
	int i;

	for(i=0; i<i_len; i++)
	{
		CString str_line = l_line[i];
		
		CString key_word = "#SLOT=";
		int s_index = str_line.Find(key_word);
		if(s_index < 0)		continue;
		str_line.Delete(s_index, key_word.GetLength());

		CStringArray l_para;
		MACRO__Convert__LIST('/', str_line, l_para);

		int k_limit = l_para.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CString str_para = l_para[k];

			if(k == 0)				// 01 : SlotID
			{
				l_portid.Add(file_portid);
				l_slotid.Add(str_para);
			}
			else if(k == 1)			// 02 : R_Offset
				l_off_r.Add(str_para);
			else if(k == 2)			// 03 : T_Offset
				l_off_t.Add(str_para);
			else if(k == 3)			// 04 : X_Offset
				l_off_x.Add(str_para);
			else if(k == 4)			// 05 : Y_Offset
				l_off_y.Add(str_para);
			else if(k == 5)			// 06 : LOTID
				l_lotid.Add(str_para);
			else if(k == 6)			// 07 : PPID
				l_ppid.Add(str_para);
			else if(k == 7)			// 08 : MaterialID
				;
			else if(k == 8)			// 09 : Wafer_State
				;
			else if(k == 9)			// 10 : Wafer_Title
				;
			else if(k == 10)		// 11 : Wafer_MDx
				l_module.Add(str_para);
			else if(k == 11)		// 12 : End_Time
				l_end_time.Add(str_para);
			else if(k == 12)		// 13 : Arm_Act
				l_arm_act.Add(str_para);
			else if(k == 13)		// 14 : Arm_Type
				l_arm_type.Add(str_para);
		}

		// ...
		{
			int i_size = l_portid.GetSize();

			l_slotid.SetSize(i_size);
			l_module.SetSize(i_size);
			
			l_off_r.SetSize(i_size);
			l_off_t.SetSize(i_size);
			l_off_x.SetSize(i_size);
			l_off_y.SetSize(i_size);

			l_lotid.SetSize(i_size);
			l_ppid.SetSize(i_size);

			l_arm_act.SetSize(i_size);
			l_arm_type.SetSize(i_size);
			l_end_time.SetSize(i_size);
		}
	}

	// ...
	{
		CListCtrl *p_table = &mCtrl__Log_Result;

		_Add__Result_List(p_table, 
						  l_portid,
						  l_slotid,
						  l_module,
					 	  l_off_r,
						  l_off_t,
						  l_off_x,
						  l_off_y,
						  l_lotid,
						  l_ppid,
						  l_arm_type,
						  l_arm_act,
						  l_end_time);
	}
	return 1;
}
