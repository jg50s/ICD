#include "StdAfx.h"
#include "CObj_Phy__ROBOT_ATM.h"
#include "CObj_Phy__ROBOT_ATM__DEF.h"


// ...
int CObj_Phy__ROBOT_ATM::__Define__QUERY(CStringArray& l_query)
{
	l_query.RemoveAll();
	l_query.Add(_QRY__GET_EMPTY_ARM);

	return 1;
}

int CObj_Phy__ROBOT_ATM::
__Call__QUERY_LIST(const CString& query_name,CStringArray& l_data)
{
	l_data.RemoveAll();

	if(query_name.CompareNoCase(_QRY__GET_EMPTY_ARM) == 0)
	{
		return _Query__GET_EMPTY_ARM(query_name, l_data);
	}
	return -1;
}
int CObj_Phy__ROBOT_ATM::
__Call__QUERY_LIST(const CString& query_name,const CStringArray& l_sub_query, CStringArray& l_data)
{
	l_data.RemoveAll();

	if(query_name.CompareNoCase(_QRY__GET_EMPTY_ARM) == 0)
	{
		return _Query__GET_EMPTY_ARM(query_name, l_data);
	}
	return -1;
}

int CObj_Phy__ROBOT_ATM::
_Query__GET_EMPTY_ARM(const CString& query_name, CStringArray& l_data)
{
	int i;

	for(i=0; i<CFG_ROBOT__ARM_SIZE; i++)
	{
		if(xCH__SLOT_STATUS[i]->Check__DATA(STR__NONE) < 0)					continue;
		if(dCH__CFG_ARM_USE_FLAG_X[i]->Check__DATA(STR__ENABLE) < 0)		continue;

		// ...
		CString arm_name;

			 if(i == 0)			arm_name = _ARM__A;
		else if(i == 1)			arm_name = _ARM__B;	
		else					continue;

		l_data.Add(arm_name);
	}

	if(iACTIVE__SIM_MODE > 0)
	{
		printf(" [%s] : __Call__QUERY_LIST() ... \n", sObject_Name);
		printf(" * Query.Name <- [%s] \n", query_name);

		int i_limit = l_data.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			printf("   * %1d) [%s] \n", i,l_data[i]);
		}
		printf("\n");
	}
	return 1;
}
