#include "stdafx.h"
#include "JGLEE__LOG_ANALYSIS.h"

#include "Dlg__Job_History.h"

#include "Macro_Function.h"


// ...
void CDlg__Job_History::
_Update__Search_All(const CString& s_date, 
					const CString& e_date)
{
	// ...
	{
		mStr__Search_Start = s_date;
		mStr__Search_End   = e_date;
	}

	// ...
	CStringArray l__res_date;

	// ...
	{
		CStringArray l_dir;
		CStringArray l_date;

		MACRO__Get_Dir_Date_List(sDir_Root, l_dir,l_date);

		int i_limit = l_dir.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CString cur_date = l_dir[i];

			if(cur_date < s_date)		continue;
			if(cur_date > e_date)		continue;

			l__res_date.Add(cur_date);
		}

		MACRO__Change_Order(l__res_date, true);
	}

	mLog_Ctrl.Clear_ALL();

	// ...
	{
		CString str_date;

		int i_limit = l__res_date.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			str_date = l__res_date[i];

			mLog_Ctrl.Load__Log_Date(str_date);

			// ...
			{
				CString dir_sub;
				dir_sub.Format("%s\\%s", sDir_Root,str_date);

				CStringArray l_log;
				CStringArray l_time;

				MACRO__Get_Dir_Time_List(dir_sub, l_log,l_time);

				int k_limit = l_log.GetSize();
				int k;
			
				for(k=0; k<k_limit; k++)
				{
					CString str_log  = l_log[k];
					CString str_time = l_time[k];

					CStringArray l_para;					
					MACRO__Convert__LIST('+', str_log, l_para);

					// ...
					CString para_lpid;
					CString para_lotid;
					CString para_cstid;
					CString para_jobid;

					if(l_para.GetSize() > 1)		para_lpid  = l_para[1];
					if(l_para.GetSize() > 2)		para_lotid = l_para[2]; 
					if(l_para.GetSize() > 3)		para_jobid = l_para[3]; 
					if(l_para.GetSize() > 4)		para_cstid = l_para[4]; 

					mLog_Ctrl.Load__Log_Info_With_No_Slot(para_lpid,para_cstid,para_jobid,para_lotid,str_log,str_time);
				}
			}
		}
	}

	// ...
}

void CDlg__Job_History::
_Update__Search_Wafer(const int r_index)
{
	CString str_portid = _Get_PortID__Result_Table(r_index);
	mBtn__Result_Sel_PortID.SetWindowText(str_portid);

	CString dir_sub = _Get_Path__Result_Table(r_index);
	mBtn__Result_Sel_Path.SetWindowText(dir_sub);

	CString dir_inf;
	dir_inf.Format("%s\\%s", sDir_Root,dir_sub);

	// ...
	CStringArray l_file;
	CStringArray l_date;

	MACRO__Get_File_List(dir_inf, "wfr", l_file,l_date);
	_Update__Slot_Info(l_file);

	UpdateData(FALSE);
}
