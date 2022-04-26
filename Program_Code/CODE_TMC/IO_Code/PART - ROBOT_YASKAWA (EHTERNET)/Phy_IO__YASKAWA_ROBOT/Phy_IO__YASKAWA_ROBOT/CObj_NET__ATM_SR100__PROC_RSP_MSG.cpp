#include "StdAfx.h"
#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ATM_SR100__DEF.h"
#include "CObj_NET__ATM_SR100__ALID.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj_NET__ATM_SR100
::Mon__PROC_RSP_MSG(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	_Proc__RSP_MSG();
}

int CObj_NET__ATM_SR100
::_Proc__RSP_MSG()
{
	CString log_msg;
	CString log_bff;

	// Log ...
	{
		log_msg = "_Proc__RSP_MSG() : Start ... \n";
		Fnc__DRV_LOG(log_msg);
	}

	while(1)
	{
		Sleep(1);

		if(iSim_Flag > 0)
		{
			Sleep(100);
			continue;
		}

		// ...
		CString rsp_data = "";
		CString err_msg  = "";

		int r_len = mX_Net->DATA__RECV_QUEUE(&rsp_data, 1, &err_msg);
		if(r_len > 0)
		{
			log_msg = "Response_Msg ... \n";

			// ...
			{
				CString str_bff;
				mX_Net->CLEAR__BUFFER(&str_bff);

				if(str_bff.GetLength() > 0)
				{
					log_bff.Format(" * buffer <- [%s] \n", str_bff);
					log_msg += log_bff;

					rsp_data += sEnd_InStr;
					rsp_data += str_bff;
				}

				log_bff.Format(" * r_data <- [%s] \n", rsp_data);
				log_msg += log_bff;
			}

			// ...
			CStringArray l_rsp;
			_Get__STRING_ARRAY(rsp_data,sEnd_InStr, l_rsp);

			int i_limit = l_rsp.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				CString str_rsp = l_rsp[i];
				mMng__RSP_MSG.Load__RSP_MSG(str_rsp);

				log_bff.Format(" <<- %1d) %s \n", i+1,str_rsp);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG(log_msg);
		}
	}

	return 1;
}

CString CObj_NET__ATM_SR100::
_Get__CHECK_SUM(const CString& s_cmmd)
{
	int s_sum = 0;

	int i_len = s_cmmd.GetLength();
	int i;

	for(i=0; i<i_len; i++)
	{
		s_sum += 0x0ff & s_cmmd.GetAt(i);
	}

	CString str_hexa;
	str_hexa.Format("%02X", 0x0ff & s_sum);
	return str_hexa;
}
int CObj_NET__ATM_SR100::
_Get__STRING_ARRAY(const CString& xxx_data,
				   const CString& str_delimiter,
				   CStringArray& l_data)
{
	l_data.RemoveAll();

	CString str_data = xxx_data;
	int del_size = str_delimiter.GetLength();

	while(1)
	{
		int s_index = str_data.Find(str_delimiter);
		if(s_index < 0)
		{
			l_data.Add(str_data);
			return 1;
		}

		// ...
		CString str_rsp = str_data;

		str_rsp.Delete(s_index, str_data.GetLength()-s_index);
		str_data.Delete(0, s_index+del_size);

		l_data.Add(str_rsp);
	}
	return -1;
}
