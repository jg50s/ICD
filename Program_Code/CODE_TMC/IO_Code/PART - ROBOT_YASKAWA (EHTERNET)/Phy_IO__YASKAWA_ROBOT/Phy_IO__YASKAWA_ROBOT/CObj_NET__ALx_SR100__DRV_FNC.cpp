#include "StdAfx.h"
#include "CObj_NET__ALx_SR100.h"
#include "CObj_NET__ALx_SR100__DEF.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CObj_NET__ALx_SR100
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj_NET__ALx_SR100
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString str__recv_data;
	CString str__cmmd;
	int flag;

	if(diCH__PA_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd.Format("%s,RSTS", sDRV_UnitID);

		flag = _Recv__CMMD(var_name, false, str__cmmd,str__recv_data);	
		if(flag != _DRV_RSP__ACK)		return -1;

		CStringArray l_rsp;
		_Get__STRING_ARRAY(str__recv_data,",", l_rsp);

		// PRE-ALIGNER ...
		if(l_rsp.GetSize() > 6)
		{
			CString str_err = l_rsp[5];
			CString str_sts = l_rsp[6];

			_Update__ERROR_CODE(str_err);
			_Update__ALIGNER_STATUS(str_sts);
		}
		return 1;
	}

	return -1;
}

int CObj_NET__ALx_SR100
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj_NET__ALx_SR100
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	
	return -1;
}

int CObj_NET__ALx_SR100
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "__Write__DIGITAL() ... \n";

		log_bff.Format(" *** var_name : %s \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" *** set_data : %s \n", set_data);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	CString str__recv_data;
	CString str__cmmd;
    int flag;

	if(doCH__AL_CMMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString str_unitid = sDRV_UnitID;

		if(set_data.CompareNoCase(_CMMD__Align) == 0) 
		{
			str__cmmd.Format("%s,MALN,0,%08.0f", 
				             str_unitid,
							 dPARA__TRG_ANGLE * 1000.0);
		}
		else if(set_data.CompareNoCase(_CMMD__VacOn) == 0) 
		{
			str__cmmd.Format("%s,CSOL,1,1,0", str_unitid);
		}
		else if(set_data.CompareNoCase(_CMMD__VacOff) == 0) 
		{
			str__cmmd.Format("%s,CSOL,1,0,0", str_unitid);
		}
		else if(set_data.CompareNoCase(_CMMD__ALErrClr) == 0) 
		{
			str__cmmd.Format("%s,CCLR,E", str_unitid);
		}
		
		flag = _Recv__CMMD(var_name, true, str__cmmd,str__recv_data);

		if(flag < 0)
		{
			return -1;
		}
		if(flag == _DRV_RSP__ERROR)
		{
			return -1;
		}
		if(flag == _DRV_RSP__COMPLETE)
		{
			CStringArray l_rsp;
			_Get__STRING_ARRAY(str__recv_data,",", l_rsp);

			if(l_rsp.GetSize() > 4)
			{
				CString rsp_sts = l_rsp[2];
				CString rsp_err = l_rsp[3];

				_Update__SYSTEM_STATUS(rsp_sts);
				_Update__ERROR_CODE(rsp_err);

				_Check__ERROR_CODE(rsp_err);
			}
		}
		return 1;   
	}
	
	return -1;
}

int CObj_NET__ALx_SR100
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
