#include "stdafx.h"
#include "CLS__Wafer_Trace.h"

#include "Macro_Function.h"


// ...
CLS__Wafer_Info::CLS__Wafer_Info()
{
	InitializeCriticalSection(&mCS_LOCK);

	// ...
	{
		bActive__WAFER_INFO = false;

		iPara__PORTID = 0;
		iPara__SLOTID = 0;
	}
}
CLS__Wafer_Info::~CLS__Wafer_Info()
{
	// ...
	{
		int i_limit = pList__MD_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];
			delete p_info;
		}

		pList__MD_INFO.RemoveAll();
	}

	DeleteCriticalSection(&mCS_LOCK);
}

void CLS__Wafer_Info::
Clear__ALL()
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		bActive__WAFER_INFO = false;

		iPara__PORTID = 0;
		iPara__SLOTID = 0;

		sPara__LOTID = "";
		sPara__PPID  = "";
		sPara__MATERIALID = "";

		sList__STEP_RCP.RemoveAll();
		
		sPara__LOOP_ID    = "";
		sPara__LOOP_COUNT = "";
	}

	// ...
	{
		int i_limit = pList__MD_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];
			delete p_info;
		}
		pList__MD_INFO.RemoveAll();
	}

	LeaveCriticalSection(&mCS_LOCK);
}

void CLS__Wafer_Info::
Load__WFR_INFO(const DS__Wafer_Info& ds_info)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		bActive__WAFER_INFO = true;

		iPara__PORTID = ds_info.iPORTID;
		iPara__SLOTID = ds_info.iSLOTID;

		sPara__LOTID = ds_info.sLOTID;
		sPara__PPID  = ds_info.sPPID;
		sPara__MATERIALID = ds_info.sMATERIALID;

		sList__STEP_RCP.RemoveAll();
		sList__STEP_RCP.Copy(ds_info.sList__STEP_RCP);
		
		sPara__LOOP_ID    = ds_info.sLOOP_ID;
		sPara__LOOP_COUNT = ds_info.sLOOP_COUNT;
	}

	LeaveCriticalSection(&mCS_LOCK);
}
void CLS__Wafer_Info::
Load__MD_INFO(CLS__MD_Info md_info)
{
	EnterCriticalSection(&mCS_LOCK);

	CLS__MD_Info *p_info = new CLS__MD_Info;
	pList__MD_INFO.Add(p_info);

	// ...
	{
		CString act_name = md_info.sPara__ACT;
	
		if(act_name.Find("PROCESS") >= 0)		md_info.bActive__PROCESS = true;
		if(act_name.Find("PICK")    >= 0)		md_info.bActive__PICK    = true;
		if(act_name.Find("PLACE")   >= 0)		md_info.bActive__PLACE   = true;
	}

	p_info->Copy_From(md_info);

	LeaveCriticalSection(&mCS_LOCK);
}

bool CLS__Wafer_Info::Is_Active__WFR_INFO()
{
	return bActive__WAFER_INFO;
}

int  CLS__Wafer_Info::
Get__WFR_INFO(DS__Wafer_Info& ds_info)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		ds_info.iPORTID = iPara__PORTID;
		ds_info.iSLOTID = iPara__SLOTID;

		ds_info.sLOTID = sPara__LOTID;
		ds_info.sPPID  = sPara__PPID;
		ds_info.sMATERIALID = sPara__MATERIALID;

		ds_info.sList__STEP_RCP.RemoveAll();
		ds_info.sList__STEP_RCP.Copy(sList__STEP_RCP);

		ds_info.sLOOP_ID    = sPara__LOOP_ID;
		ds_info.sLOOP_COUNT = sPara__LOOP_COUNT;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int  CLS__Wafer_Info::
Get__MD_SIZE()
{
	EnterCriticalSection(&mCS_LOCK);

	int db_size = _Get__MD_SIZE();

	LeaveCriticalSection(&mCS_LOCK);
	return db_size;
}
int  CLS__Wafer_Info::
_Get__MD_SIZE()
{
	return pList__MD_INFO.GetSize();
}
int  CLS__Wafer_Info::
Get__MD_INFO(const int db_index, 
			 CLS__MD_Info& md_info)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_flag = _Get__MD_INFO(db_index, md_info);

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CLS__Wafer_Info::
_Get__MD_INFO(const int db_index, 
			 CLS__MD_Info& md_info)
{
	int check_flag = -1;

	if(pList__MD_INFO.GetSize() > db_index)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[db_index];

		md_info.Copy_From(*p_info);
		check_flag = 1;
	}
	return check_flag;
}

int  CLS__Wafer_Info::
Get__CURRENT_PROCESS_SIZE()
{
	EnterCriticalSection(&mCS_LOCK);

	int prc_cnt = 0;

	int i_limit = pList__MD_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];
		if(!p_info->bActive__PROCESS)		continue;

		prc_cnt++;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return prc_cnt;
}

int  CLS__Wafer_Info::
Get__WAFER_DA_INFO(CStringArray& l_module, 
				   CStringArray& l_r_offset,
				   CStringArray& l_t_offset)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_module.RemoveAll();
		l_r_offset.RemoveAll();
		l_t_offset.RemoveAll();
	}

	int i_limit = pList__MD_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];

		if(!p_info->bActive__PROCESS)		
			continue;

		// ...
		CString str_module = p_info->sPara__MODULE;
		CString str_r_off = "???";
		CString str_t_off = "???";

		// ...
		{
			CString str_rt_off = p_info->sPara__RT_OFFSET;
			CStringArray l_data;
			MACRO__Convert__LIST('_', str_rt_off,l_data);

			if(l_data.GetSize() > 0)		str_r_off = l_data[0];
			if(l_data.GetSize() > 1)		str_t_off = l_data[1];
		}

		l_module.Add(str_module);
		l_r_offset.Add(str_r_off);
		l_t_offset.Add(str_t_off);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int CLS__Wafer_Info::
Get__WAFER_TACK_INFO(const bool active__search_move,
					 const bool active__search_proc,
					 CStringArray& l_module,
					 CStringArray& l_action,
					 CStringArray& l_result,
					 CStringArray& l_time,
					 CStringArray& l_comment)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_module.RemoveAll();
		l_action.RemoveAll();
		l_result.RemoveAll();
		l_time.RemoveAll();
		l_comment.RemoveAll();
	}

	int i_limit = pList__MD_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];

		// ...
		bool active_check = false;

		CString str_module = p_info->sPara__MODULE;
		CString str_action = p_info->sPara__ACT;
		CString str_result = p_info->sPara__RESULT;
		CString str_time   = p_info->sPara__TIME_ACT;
		CString str_comment;

		if(active__search_move)
		{
			active_check = true;

			if(p_info->bActive__PLACE)
			{
				str_comment.Format("[%s][%s] -> [%s]", 
									p_info->sPara__ROBOT,
									p_info->sPara__ARM,
									p_info->sPara__MODULE);
			}
			else if(p_info->bActive__PICK)
			{
				str_comment.Format("[%s][%s] <- [%s]", 
									p_info->sPara__ROBOT,
									p_info->sPara__ARM,
									p_info->sPara__MODULE);
			}
			else if(!p_info->bActive__PROCESS)
			{
				str_comment.Format("[%s][%s] & [%s]", 
								   p_info->sPara__ROBOT,
								   p_info->sPara__ARM,
								   p_info->sPara__MODULE);
			}
			else
			{
				active_check = false;
			}
		}
		if(active__search_proc)
		{
			if(p_info->bActive__PROCESS)
			{
				active_check = true;

				str_comment.Format("Recipe [%s]", 
								    p_info->sPara__RECIPE);
			}
		}

		if(!active_check)		continue;

		l_module.Add(str_module);
		l_action.Add(str_action);
		l_result.Add(str_result);
		l_time.Add(str_time);
		l_comment.Add(str_comment);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

int  CLS__Wafer_Info::
Get__PROCESS_LOG(CStringArray& l_md_info,
				 CStringArray& l_tack,
				 CStringArray& l_rcp,
				 CStringArray& l_log_info)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_md_info.RemoveAll();
		l_log_info.RemoveAll();
	}

	int i_limit = pList__MD_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];

		if(!p_info->bActive__PROCESS)
		{
			continue;
		}

		CString str_md  = p_info->sPara__MODULE;
		CString str_tack = p_info->sPara__TIME_ACT;
		CString str_rcp = p_info->sPara__RECIPE;
		CString str_log = p_info->sPara__LOG;

		l_md_info.Add(str_md);
		l_tack.Add(str_tack);
		l_rcp.Add(str_rcp);
		l_log_info.Add(str_log);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int  CLS__Wafer_Info::
Get__PROCESS_LOG(CStringArray& l_md_info,
				 CStringArray& l_log_info,
				 CStringArray& l_result)
{
	EnterCriticalSection(&mCS_LOCK);

	// ...
	{
		l_md_info.RemoveAll();
		l_log_info.RemoveAll();
		l_result.RemoveAll();
	}

	int i_limit = pList__MD_INFO.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CLS__MD_Info *p_info = (CLS__MD_Info*) pList__MD_INFO[i];

		if(!p_info->bActive__PROCESS)
		{
			continue;
		}

		CString str_md     = p_info->sPara__MODULE;
		CString str_log    = p_info->sPara__LOG;
		CString str_result = p_info->sPara__RESULT;

		l_md_info.Add(str_md);
		l_log_info.Add(str_log);
		l_result.Add(str_result);
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}

void CLS__Wafer_Info::
Display__WFR_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	printf(" * Wafer Info ... \n");

	printf(" ** para__portid <- [%1d] \n", iPara__PORTID);
	printf(" ** para__slotid <- [%1d] \n", iPara__SLOTID);

	printf(" ** para__lotid <- [%s] \n", sPara__LOTID);
	printf(" ** para__ppid  <- [%s] \n", sPara__PPID);
	printf(" ** para__materialid <- [%s] \n", sPara__MATERIALID);

	int i_limit = sList__STEP_RCP.GetSize();

	printf(" ** step_size <- [%1d] \n", i_limit);

	for(int i=0; i<i_limit; i++)
	{
		printf("  ** %1d) [%s] \n", i+1,sList__STEP_RCP[i]);
	}

	printf(" ** para__loop_id <- [%s] \n", sPara__LOOP_ID);
	printf(" ** para__loop_count <- [%s] \n", sPara__LOOP_COUNT);

	LeaveCriticalSection(&mCS_LOCK);
}
void CLS__Wafer_Info::
Display__MD_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	printf(" * Module Info ... \n");

	int db_size = _Get__MD_SIZE();
	int db_i;

	for(db_i=0; db_i<db_size; db_i++)
	{
		CLS__MD_Info md_info;
		_Get__MD_INFO(db_i, md_info);

		printf(" * db_index <- [%1d] \n", db_i);

		// ...
		CString para_act = md_info.sPara__ACT;
		
		printf("  ** ACT    <- [%s] \n", para_act);
		printf("  ** MODULE <- [%s] \n", md_info.sPara__MODULE);

		if(para_act.Find("PROCESS") >= 0)
		{
			printf("   ** RT_OFFSET <- [%s] \n", md_info.sPara__RT_OFFSET);
			printf("   ** RECIPE    <- [%s] \n", md_info.sPara__RECIPE);
			printf("   ** RESULT    <- [%s] \n", md_info.sPara__RESULT);
		}
		else
		{
			printf("   ** ROBOT <- [%s] \n", md_info.sPara__ROBOT);
			printf("   ** ARM   <- [%s] \n", md_info.sPara__ARM);
		}

		printf("   ** TIME.ACT   <- [%s] \n", md_info.sPara__TIME_ACT);
		printf("   ** TIME.START <- [%s] \n", md_info.sPara__TIME_START);
		printf("   ** TIME.END   <- [%s] \n", md_info.sPara__TIME_END);
	}

	LeaveCriticalSection(&mCS_LOCK);
}
