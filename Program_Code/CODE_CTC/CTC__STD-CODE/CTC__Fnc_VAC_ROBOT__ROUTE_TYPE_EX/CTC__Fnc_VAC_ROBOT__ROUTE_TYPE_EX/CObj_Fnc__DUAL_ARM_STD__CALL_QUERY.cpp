#include "StdAfx.h"
#include "CObj_Fnc__DUAL_ARM_STD.h"


#define _QRY__GET_EMPTY_ARM                 "GET.EMPTY_ARM"


// ...
int CObj_Fnc__DUAL_ARM_STD
::__Define__QUERY(CStringArray& l_query)
{
	l_query.Add(_QRY__GET_EMPTY_ARM);

	return 1;
}


int CObj_Fnc__DUAL_ARM_STD
::__Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data)
{
	int log_enable = -1;

	if(dCH__QUERY_LOG_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		log_enable = 1;
	}

	if(log_enable > 0)
	{
		CString log_msg = "";
		CString log_bff;

		log_msg = " * CObj_Fnc__DUAL_ARM_STD::__Call__QUERY_LIST() ... \n";
		
		int i_limit = l_sub_query.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			log_bff.Format("  ** %1d) %s \n", i+1,l_sub_query[i]);
			log_msg += log_bff;
		}
		printf(log_msg);
	}

	if(query_name.CompareNoCase(_QRY__GET_EMPTY_ARM) == 0)
	{
		l_data.RemoveAll();

		if(xCH__VAC_RB__CFG_A_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__VAC_RB__SLOT01_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
			{
				l_data.Add("A");
			}
		}
		if(xCH__VAC_RB__CFG_B_ARM_USE_MODE->Check__DATA(STR__ENABLE) > 0)
		{
			if(xCH__VAC_RB__SLOT02_STATUS->Check__DATA(SLOT_STS__NONE) > 0)
			{
				l_data.Add("B");
			}
		}

		if(log_enable > 0)
		{
			CString log_msg = "";
			CString log_bff;

			int i_limit = l_data.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				log_bff.Format("  ** Empty_Arm : %s \n", l_data[i]);
				log_msg += log_bff;
			}

			printf(log_msg);
		}
		return 1;
	}

	return -1;
}
