#include "StdAfx.h"
#include "CObj__VAT650_TYPE.h"



//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	CString cmmd1 = io_info.sCOMMAND1;
	CString cmmd2 = io_info.sCOMMAND2;
	CString cmmd3 = io_info.sCOMMAND3;

	double min_value = io_info.dMIN_VALUE;
	double max_value = io_info.dMAX_VALUE;

	// ...
	int flag = -1;

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		flag = _Read__ANALOG_OF_1M_TYPE(var_name, read_data, 
										min_value, max_value, 
										cmmd1,cmmd2,cmmd3);
	}
	else
	{
		flag = _Read__ANALOG_OF_1K_TYPE(var_name, read_data, 
										min_value, max_value, 
										cmmd1,cmmd2,cmmd3);
	}

	return flag;
}

int CObj__VAT650_TYPE
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString cmmd1 = io_info.sCOMMAND1;
	CString cmmd2 = io_info.sCOMMAND2;
	CString cmmd3 = io_info.sCOMMAND3;

	// ...
	int flag = -1;

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		flag = _Read__DIGITAL_OF_1M_TYPE(var_name, read_data);
	}
	else
	{
		flag = _Read__DIGITAL_OF_1K_TYPE(var_name, read_data);
	}

	return flag;
}

int CObj__VAT650_TYPE
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VAT650_TYPE
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	int flag;

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		flag = _Write__ANALOG_OF_1M_TYPE(var_name, set_data);
	}
	else
	{
		flag = _Write__ANALOG_OF_1K_TYPE(var_name, set_data);
	}

	return flag;
}

int CObj__VAT650_TYPE
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	int flag;

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		flag = _Write__DIGITAL_OF_1M_TYPE(var_name, set_data);
	}
	else
	{
		flag = _Write__DIGITAL_OF_1K_TYPE(var_name, set_data);
	}

	return flag;
}

int CObj__VAT650_TYPE
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	int flag;

	if(dCH__CFG_POS_COUNT_TYPE->Check__DATA(STR__1M_TYPE) > 0)
	{
		flag = _Write__STRING_OF_1M_TYPE(var_name, set_data);
	}
	else
	{
		flag = _Write__STRING_OF_1K_TYPE(var_name, set_data);
	}

	return flag;
}
