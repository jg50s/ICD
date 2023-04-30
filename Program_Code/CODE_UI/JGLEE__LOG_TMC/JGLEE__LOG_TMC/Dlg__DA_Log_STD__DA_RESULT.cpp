#include "stdafx.h"
#include "JGLEE__LOG_TMC.h"

#include "CObj__DA_Log_STD.h"
#include "Macro_Function.h"


// ...
#define _RST_COL__NUMBER						0
#define _RST_COL__WFRID							1
#define _RST_COL__MDx							2
#define _RST_COL__OFF_01						3
#define _RST_COL__OFF_02						4
#define _RST_COL__LOTID							5
#define _RST_COL__PPID							6
#define _RST_COL__ARM_TYPE						7
#define _RST_COL__ARM_ACT						8
#define _RST_COL__END_TIME						9


void CDlg__DA_Log_STD
::_Make__Result_List(CListCtrl *p_table)
{
	CStringArray l__col_name;
	CUIntArray   l__col_width;

	CString str_info;

	// ...
	{
		l__col_name.RemoveAll();
		l__col_width.RemoveAll();

		int i_limit = 12;
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(i == _RST_COL__NUMBER)
			{
				l__col_name.Add("No.");
				l__col_width.Add(50);
			}
			else if(i == _RST_COL__WFRID)
			{
				l__col_name.Add("Wafer");
				l__col_width.Add(60);
			}
			else if(i == _RST_COL__MDx)
			{
				l__col_name.Add("Module");
				l__col_width.Add(60);
			}
			else if(i == _RST_COL__OFF_01)
			{
				if(bActive__R_T_OFFSET)			str_info = "Offset_R (mm)";
				else							str_info = "Offset_X (mm)";

				l__col_name.Add(str_info);
				l__col_width.Add(90);
			}
			else if(i == _RST_COL__OFF_02)
			{
				if(bActive__R_T_OFFSET)			str_info = "Offset_T (deg)";
				else							str_info = "Offset_Y (mm)";

				l__col_name.Add(str_info);
				l__col_width.Add(90);
			}
			else if(i == _RST_COL__LOTID)
			{
				l__col_name.Add("LotID");
				l__col_width.Add(120);
			}
			else if(i == _RST_COL__PPID)
			{
				l__col_name.Add("PPID");
				l__col_width.Add(120);
			}
			else if(i == _RST_COL__ARM_TYPE)
			{
				l__col_name.Add("Arm");
				l__col_width.Add(50);
			}
			else if(i == _RST_COL__ARM_ACT)
			{
				l__col_name.Add("Action");
				l__col_width.Add(60);
			}
			else if(i == _RST_COL__END_TIME)
			{
				l__col_name.Add("End Time");
				l__col_width.Add(120);
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

		for(int i=0; i<10; i++)
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

			if(col_cx < 1)
			{
				col_cx = 10 + (col_name.GetLength() * 10);
			}

			p_table->InsertColumn(i, col_name, LVCFMT_CENTER, col_cx);
		}		
	}
}
void CDlg__DA_Log_STD
::_Add__Result_List(CListCtrl *p_table, 
				    const CStringArray& l_portid,
				    const CStringArray& l_slotid,
				    const CStringArray& l_module,
				    const CStringArray& l_off_r,
				    const CStringArray& l_off_t,
					const CStringArray& l_off_x,
					const CStringArray& l_off_y,
				    const CStringArray& l_lotid,
					const CStringArray& l_ppid,
					const CStringArray& l_arm_type,
				    const CStringArray& l_arm_act,
					const CStringArray& l_end_time)
{
	mDB__OFFSET_PT.Clear__INFO();
	p_table->DeleteAllItems();

	// ...
	int active__only_alarm = mCheck__Only_Alarm.GetCheck();
	double ref__err_range = 0.0;

	if(mCheck__Error_Range.GetCheck() > 0)
	{
		ref__err_range = atof(mStr__Error_Range);
	}
	else
	{
		active__only_alarm = -1;
	}

	// ...
	CString str_item;
	
	int tbl_r = 0;

	int i_limit = l_portid.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(sSearch__LotID.GetLength() > 0)
		{
			str_item = l_lotid[i];

			if(str_item.Find(sSearch__LotID) < 0)
				continue;
		}
		if(sSearch__PPID.GetLength() > 0)
		{
			str_item = l_ppid[i];

			if(str_item.Find(sSearch__PPID) < 0)
				continue;
		}
		
		if(iSearch__PortID > 0)
		{
			int port_id = atoi(l_portid[i]);

			if(port_id != iSearch__PortID)
				continue;
		}
		if(iSearch__SlotID > 0)
		{
			int slot_id = atoi(l_slotid[i]);

			if(slot_id != iSearch__SlotID)
				continue;
		}

		// Module Check ...
		{
			CString str_mdx = l_module[i];

			// ...
			bool check_mdx = false;
			
			if(!check_mdx)
			{
				int ll_i = MACRO__Get__LLx_ID(str_mdx) - 1;
				if(ll_i >= 0)
				{
					if(!bCheck__LLx[ll_i])		continue;
					check_mdx = true;
				}
			}
			if(!check_mdx)
			{
				int pm_i = MACRO__Get__PMC_ID(str_mdx) - 1;
				if(pm_i >= 0)
				{
					if(!bCheck__PMx[pm_i])		continue;
					check_mdx = true;
				}
			}
			
			if(!check_mdx)		continue;
		}

		if(active__only_alarm > 0)
		{
			double cur__err_range = atof(l_off_r[i]);

			/*
			if(!bActive__R_T_OFFSET)
			{
				double x_mm = atof(l_off_x[i]);
				double y_mm = atof(l_off_y[i]);

				cur__err_range = sqrt(pow(x_mm, 2) + pow(y_mm, 2)); 
			}
			*/
			
			if(cur__err_range < 0)			cur__err_range = -cur__err_range;
			if(cur__err_range < ref__err_range)			continue;
		}

		// ...
		int active__end_check = -1;

		CString item__wfrid;
		CString item__mdx;
		
		CString item__off_01;
		CString item__off_02;
		
		CString item__lotid;
		CString item__ppid;
		CString item__arm_type;
		CString item__arm_act;
		CString item__end_time;

		int k_limit = 15;
		int k;

		for(k=0; k<k_limit; k++)
		{
			if(k == _RST_COL__NUMBER)
			{

			}
			else if(k == _RST_COL__WFRID)
			{
				item__wfrid.Format("P%s:%s", l_portid[i],l_slotid[i]);
			}
			else if(k == _RST_COL__MDx)
			{
				item__mdx = l_module[i];
			}
			else if(k == _RST_COL__OFF_01)
			{
				if(bActive__R_T_OFFSET)			item__off_01 = l_off_r[i];
				else							item__off_01 = l_off_x[i];
			}
			else if(k == _RST_COL__OFF_02)
			{
				if(bActive__R_T_OFFSET)			item__off_02 = l_off_t[i];
				else							item__off_02 = l_off_y[i];
			}
			else if(k == _RST_COL__LOTID)
			{
				item__lotid = l_lotid[i];
			}
			else if(k == _RST_COL__PPID)
			{
				item__ppid = l_ppid[i];
			}
			else if(k == _RST_COL__ARM_TYPE)
			{
				item__arm_type = l_arm_type[i];
			}
			else if(k == _RST_COL__ARM_ACT)
			{
				item__arm_act = l_arm_act[i];
			}
			else if(k == _RST_COL__END_TIME)
			{
				item__end_time = l_end_time[i];
			}
			else
			{
				active__end_check = 1;
				break;
			}
		}

		if(active__end_check < 0)
		{
			continue;
		}

		for(k=0; k<k_limit; k++)
		{
				 if(k == _RST_COL__NUMBER)			str_item.Format("%02d", i+1);
			else if(k == _RST_COL__WFRID)			str_item = item__wfrid;
			else if(k == _RST_COL__MDx)				str_item = item__mdx;
			else if(k == _RST_COL__OFF_01)			str_item = item__off_01;
			else if(k == _RST_COL__OFF_02)			str_item = item__off_02;
			else if(k == _RST_COL__LOTID)			str_item = item__lotid;
			else if(k == _RST_COL__PPID)			str_item = item__ppid;	
			else if(k == _RST_COL__ARM_TYPE)		str_item = item__arm_type;
			else if(k == _RST_COL__ARM_ACT)			str_item = item__arm_act;
			else if(k == _RST_COL__END_TIME)		str_item = item__end_time;
			else									break;

			if(k == 0)		p_table->InsertItem(tbl_r, str_item, 0);
			else			p_table->SetItem(tbl_r,k, LVIF_TEXT,str_item,0,0,0,0);
		}

		tbl_r++;
		mDB__OFFSET_PT.Load__INFO(item__off_01, item__off_02);
		mDB__OFFSET_PT.Load__INFO_ARM(item__arm_type, item__arm_act); // KMS
	}
}
