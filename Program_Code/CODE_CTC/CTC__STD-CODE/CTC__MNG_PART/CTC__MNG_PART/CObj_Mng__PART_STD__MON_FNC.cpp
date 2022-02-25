#include "StdAfx.h"
#include "CObj_Mng__PART_STD.h"


#include "CMacro_FA.h"
extern CMacro_FA mFA_Link;


// ...
void CObj_Mng__PART_STD
::Mon__PART_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	SCX__SEQ_INFO seq_info;

	CString var_data;
	double  ref_day;
	double  ref_count;
	double  cur_day;
	double  cur_count;
	double  per_day;
	double  per_count;
	double  per_data;

	CString pre_count[CFG__PMx_SIZE];
	int p;

	for(p=0; p<iPMx_SIZE; p++)
	{
		xEXT_CH__MODULE_MATERIAL_COUNT_X[p]->Get__DATA(pre_count[p]);
	}


	while(1)
	{
		Sleep(490);


		for(p=0; p<iPMx_SIZE; p++)
		{
			Fnc__PART_CTRL(p_variable,p_alarm, pre_count[p],p);
		}
	}
}

void CObj_Mng__PART_STD
::Fnc__PART_CTRL(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm,
				 CString& pre_count,
				 const int p)
{
	SCX__SEQ_INFO seq_info;

	CString var_data;
	double  ref_day;
	double  ref_count;
	double  cur_day;
	double  cur_count;
	double  per_day;
	double  per_count;
	double  per_data;

	// CHECK COUNT ...
	{
		xEXT_CH__MODULE_MATERIAL_COUNT_X[p]->Get__DATA(var_data);

		if(pre_count.CompareNoCase(var_data) != 0)
		{
			pre_count = var_data;

			int count;
			int k;

			for(k=0; k<CFG__PART_SIZE; k++)
			{
				xCH__PART_CUR_COUNT_X[p][k]->Get__DATA(var_data);

				count = atoi(var_data) + 1;
				var_data.Format("%1d",count);

				xCH__PART_CUR_COUNT_X[p][k]->Set__DATA(var_data);
			}
		}
	}

	// CHECK DAY ...
	{
		CString str_day;
		int s_year;
		int s_mon;
		int s_day;
		int t_year;
		int t_mon;
		int t_day;
		int day_count;
		int k;

		seq_info->Get__DAY(t_year,t_mon,t_day);

		for(k=0; k<CFG__PART_SIZE; k++)
		{
			xCH__PART_CHANGE_DAY_X[p][k]->Get__DATA(str_day);
			seq_info->Convert__STR_TO_DAY(str_day,s_year,s_mon,s_day);

			if(s_year > 0)
			{
				day_count = seq_info->Get__DAY_COUNT(s_year,s_mon,s_day,t_year,t_mon,t_day);				

				var_data.Format("%1d",day_count);
				xCH__PART_CUR_DAY_X[p][k]->Set__DATA(var_data);
			}
			else
			{
				xCH__PART_CUR_DAY_X[p][k]->Set__DATA("0");
			}
		}
	}

	// RESET ...
	{
		int k;

		if(xCH__PART_ALL_RESET_X[p]->Check__DATA("YES") > 0)
		{
			xCH__PART_ALL_RESET_X[p]->Set__DATA("NO");

			for(k=0; k<CFG__PART_SIZE; k++)
			{
				xCH__PART_RESET_X[p][k]->Set__DATA("NO");

				xCH__PART_CUR_DAY_X[p][k]->Set__DATA("0");
				xCH__PART_CUR_COUNT_X[p][k]->Set__DATA("0");
			}
			return;
		}

		for(k=0; k<CFG__PART_SIZE; k++)
		{
			if(xCH__PART_RESET_X[p][k]->Check__DATA("YES") < 0)		
			{
				continue;
			}
			xCH__PART_RESET_X[p][k]->Set__DATA("NO");

			xCH__PART_CUR_DAY_X[p][k]->Set__DATA("0");
			xCH__PART_CUR_COUNT_X[p][k]->Set__DATA("0");
		}
	}

	// MSG POPUP ...
	{
		CStringArray l__part_item;
		CStringArray l__part_ref_day;
		CStringArray l__part_ref_count;
		CStringArray l__part_cur_count;

		int k;

		for(k=0; k<CFG__PART_SIZE; k++)
		{
			// Ref - Data
			xCH__PART_REF_DAY_X[p][k]->Get__DATA(var_data);
			ref_day = atof(var_data);

			xCH__PART_REF_COUNT_X[p][k]->Get__DATA(var_data);
			ref_count = atof(var_data);

			// Cur - Data
			xCH__PART_CUR_DAY_X[p][k]->Get__DATA(var_data);
			cur_day = atof(var_data);

			xCH__PART_CUR_COUNT_X[p][k]->Get__DATA(var_data);
			cur_count = atof(var_data);

			// Percent - Bar
			if((ref_day > 0)&&(ref_count > 0))
			{
				per_day   = (cur_day / ref_day) * 100.0;
				per_count = (cur_count / ref_count) * 100.0;

				if(per_day > per_count)		per_data = per_day;
				else						per_data = per_count;
			}
			else if(ref_day > 0)
			{
				per_data = (cur_day / ref_day) * 100.0;
			}
			else if(ref_count > 0)
			{
				per_data = (cur_count / ref_count) * 100.0;
			}
			else
			{
				per_data = 0.0;
			}

			var_data.Format("%.1f",per_data);
			xCH__PART_PERCENT_X[p][k]->Set__DATA(var_data);

			if(per_data >= 100.0)
			{
				xCH__PART_ITEM_X[p][k]->Get__DATA(var_data);
				l__part_item.Add(var_data);

				//
				xCH__PART_REF_DAY_X[p][k]->Get__DATA(var_data);
				l__part_ref_day.Add(var_data);

				//
				xCH__PART_REF_COUNT_X[p][k]->Get__DATA(var_data);
				l__part_ref_count.Add(var_data);

				xCH__PART_CUR_COUNT_X[p][k]->Get__DATA(var_data);
				l__part_cur_count.Add(var_data);
			}			
		}

		if(xEXT_CH__CFG_MODULE_USE_X[p]->Check__DATA("ENABLE") > 0)
		{
			int tt_limit = l__part_item.GetSize();
			int tt;

			if(tt_limit > CFG__EXCHANGE_SIZE)		
				tt_limit = CFG__EXCHANGE_SIZE;

			for(tt=0; tt<CFG__EXCHANGE_SIZE; tt++)
			{
				xCH__PART_EXCHANGE_MSG_X[p][tt]->Set__DATA("");
			}

			for(tt=0; tt<tt_limit; tt++)
			{
				xCH__PART_EXCHANGE_MSG_X[p][tt]->Set__DATA(l__part_item[tt]);
			}

			// ...
			int ref_hour;
			int pre_day;
			int cur_day;
			int cur_hour;

			xCH__POPUP_PERIOD_X[p]->Get__DATA(var_data);
			ref_hour = atoi(var_data);

			CTime t = CTime::GetCurrentTime();
			cur_day  = t.GetDay();
			cur_hour = t.GetHour();

			xCH__POPUP_CUR_DAY_X[p]->Get__DATA(var_data);
			pre_day = atoi(var_data);

			// ...
			int popup_flag = -1;

			if(((pre_day < cur_day)&&(cur_hour >= ref_hour))
			|| (pre_day == 0))
			{
				popup_flag = 1;
			}

			if((popup_flag > 0)
			&& (l__part_item.GetSize() > 0))
			{
				SYSTEMTIME st;
				GetLocalTime(&st);

				CString alart_time;
				alart_time.Format("%00004d%002d%002d%002d%002d%002d%002d",
								  st.wYear,st.wMonth, st.wDay,
								  st.wHour,st.wMinute,st.wSecond,
								  st.wMilliseconds/10);

				xCH__ALERT_TIME_X[p]->Set__DATA(alart_time);

				// ...
				var_data.Format("%1d",cur_day);
				xCH__POPUP_CUR_DAY_X[p]->Set__DATA(var_data);

				// ...
				CString win_name = sSTR__POPUP_WIN_NAME_X[p];
				xCH__MSG_WIN_X[p]->Set__DATA(win_name);

				if(iCEID__PART_CHANGE_ALERT_X[p] > 0)
				{
					int k_limit = l__part_item.GetSize();
					int k;

					for(k=0; k<k_limit; k++)
					{
						xCH__ALERT_PART_NAME_X[p]->Set__DATA(l__part_item[k]);

						xCH__ALERT_PART_REF_DAY_X[p]->Set__DATA(l__part_ref_day[k]);
						xCH__ALERT_PART_REF_COUNT_X[p]->Set__DATA(l__part_ref_count[k]);
						xCH__ALERT_PART_CUR_COUNT_X[p]->Set__DATA(l__part_cur_count[k]);

						if(mFA_Link.Is__ONLINE() > 0)
						{
							mFA_Link.Report_CEID(iCEID__PART_CHANGE_ALERT_X[p]);

							Sleep(90);
						}
					}
				}
			}
		}
	}

	// SELECT PART ...
	{
		CString cur_item;
		CString str_item;
		int i;

		dCH__SEL_PART_ITEM_X[p]->Get__DATA(cur_item);

		for(i=0; i<CFG__PART_SIZE; i++)
		{
			str_item.Format("ITEM%1d",i+1);
			if(str_item.CompareNoCase(cur_item) != 0)		continue;

			// ...
			{
				CString var_data;

				xCH__PART_REF_DAY_X[p][i]->Get__DATA(var_data);
				sCH__SEL_PART_REF_DAY_X[p]->Set__DATA(var_data);

				xCH__PART_REF_COUNT_X[p][i]->Get__DATA(var_data);
				sCH__SEL_PART_REF_COUNT_X[p]->Set__DATA(var_data);
			}
			break;
		}
	}

	// ...
}
