#include "StdAfx.h"
#include "CObj__VIRTUAL_TYPE.h"


//------------------------------------------------------------------------------------
int CObj__VIRTUAL_TYPE
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__VIRTUAL_TYPE
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__VIRTUAL_TYPE
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__VIRTUAL_TYPE
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return 1;
}

int CObj__VIRTUAL_TYPE
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{

	return 1;
}

int CObj__VIRTUAL_TYPE
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return 1;
}
