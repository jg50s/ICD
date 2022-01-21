#include "StdAfx.h"
#include "CObj_NET__ATM_SR100.h"
#include "CObj_NET__ATM_SR100__DEF.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CObj_NET__ATM_SR100
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj_NET__ATM_SR100
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString str__recv_data;
	CString str__cmmd;
	int flag;


	if(diCH__RB_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd.Format("%s,RSTS", sDRV_UnitID);

		flag = _Recv__CMMD(var_name, false, str__cmmd,str__recv_data);	
		if(flag != _DRV_RSP__ACK)		return -1;

		CStringArray l_rsp;
		_Get__STRING_ARRAY(str__recv_data,",", l_rsp);

		// ROBOT_STATUS ...
		if(l_rsp.GetSize() > 6)
		{
			CString str_err = l_rsp[5];
			CString str_rsp = l_rsp[6];

			_Update__ERROR_CODE(str_err);
			_Update__ROBOT_STATUS(str_rsp);
		}
		return 1;
	}

	return -1;
}

int CObj_NET__ATM_SR100
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str__recv_data;
	CString str__cmmd;
	int flag;

	if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd.Format("%s,RVER", sDRV_UnitID);

		flag = _Recv__CMMD(var_name, false, str__cmmd,str__recv_data);	
		if(flag != _DRV_RSP__ACK)		return -1;

		CStringArray l_rsp;
		_Get__STRING_ARRAY(str__recv_data,",", l_rsp);

		// ROBOT_STATUS ...
		if(l_rsp.GetSize() > 6)
		{
			CString sys_ver = l_rsp[5];
			CString srv_ver = l_rsp[6];

			sCH__INFO_VER_SYSTEM->Set__DATA(sys_ver);
			sCH__INFO_VER_SERVO->Set__DATA(srv_ver);
		}
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj_NET__ATM_SR100
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	
	return -1;
}

int CObj_NET__ATM_SR100
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
	CString str_data;
	CString str__cmmd;
    int flag;

	if(doCH__COMMAND->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString str_unitid = sDRV_UnitID;

		if(set_data.CompareNoCase(_CMMD__Goto) == 0) 
		{
			CString motion_mode = "G";
			CString trg_stn  = _Get__TRG_STN();
			CString trg_slot = _Get__TRG_SLOT();
			CString arm_pos  = _Get__ARM_MODE();
			CString arm_hand = _Get__ARM_ID();
			CString pos_mode = "G1";
			CString off_x = "00000000";
			CString off_y = "00000000";
			CString off_z = "00000000";
			CString pos_angle = "00000000";

			if(_Check__ARM_WAFER() > 0)
			{
				motion_mode = "P";
				pos_mode = "P1";
			}

			/*
			//                        1  2  3  4  5  6  7  8  9  10
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
				             str_unitid,
				             motion_mode,			// 01. 
							 trg_stn,				// 02.
							 trg_slot,				// 03.
							 arm_pos,				// 04.
							 arm_hand,				// 05.
							 pos_mode,				// 06.
							 off_x,					// 07.
							 off_y,					// 08.
							 off_z,					// 09.
							 pos_angle);			// 10.
			*/

			//                        1  2  3  4  5  6 
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s",
				             str_unitid,
				             motion_mode,			// 01. 
							 trg_stn,				// 02.
							 trg_slot,				// 03.
							 arm_pos,				// 04.
							 arm_hand,				// 05.
							 pos_mode);				// 06.

		}
		else if(set_data.CompareNoCase(_CMMD__Pick) == 0) 
		{
			CString motion_mode = "G";
			CString trg_stn  = _Get__TRG_STN();
			CString trg_slot = _Get__TRG_SLOT();
			CString arm_pos  = _Get__ARM_MODE();
			CString arm_hand = _Get__ARM_ID();
			CString pos_mode = "G4";
			CString off_x = "00000000";
			CString off_y = "00000000";
			CString off_z = "00000000";
			CString pos_angle = "00000000";

			/*
			//                        1  2  3  4  5  6  7  8  9  10
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
				             str_unitid,
							 motion_mode,			// 01. 
							 trg_stn,				// 02.
							 trg_slot,				// 03.
							 arm_pos,				// 04.
							 arm_hand,				// 05.
							 pos_mode,				// 06.
							 off_x,					// 07.
							 off_y,					// 08.
							 off_z,					// 09.
							 pos_angle);			// 10.
			 */
			//                        1  2  3  4  5  6 
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s",
							str_unitid,
							motion_mode,			// 01. 
							trg_stn,				// 02.
							trg_slot,				// 03.
							arm_pos,				// 04.
							arm_hand,				// 05.
							pos_mode);				// 06.

		}
		else if(set_data.CompareNoCase(_CMMD__Place) == 0) 
		{
			CString motion_mode = "P";
			CString trg_stn  = _Get__TRG_STN();
			CString trg_slot = _Get__TRG_SLOT();
			CString arm_pos  = _Get__ARM_MODE();
			CString arm_hand = _Get__ARM_ID();
			CString pos_mode = "P4";
			CString off_x = "00000000";
			CString off_y = "00000000";
			CString off_z = "00000000";
			CString pos_angle = "00000000";

			/*
			//                        1  2  3  4  5  6  7  8  9  10
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
				             str_unitid,
							 motion_mode,			// 01. 
							 trg_stn,				// 02.
							 trg_slot,				// 03.
							 arm_pos,				// 04.
							 arm_hand,				// 05.
							 pos_mode,				// 06.
							 off_x,					// 07.
							 off_y,					// 08.
							 off_z,					// 09.
							 pos_angle);			// 10.
			*/
			//                        1  2  3  4  5  6 
			str__cmmd.Format("%s,MTRS,%s,%s,%s,%s,%s,%s",
							str_unitid,
							motion_mode,			// 01. 
							trg_stn,				// 02.
							trg_slot,				// 03.
							arm_pos,				// 04.
							arm_hand,				// 05.
							pos_mode);				// 06.
		}
		else if(set_data.CompareNoCase(_CMMD__RBSrvOn) == 0) 
		{
			str__cmmd.Format("%s,CSRV,1", str_unitid);
		}
		else if(set_data.CompareNoCase(_CMMD__RBSrvOff) == 0) 
		{
			str__cmmd.Format("%s,CSRV,0", str_unitid);
		}
		else if(set_data.CompareNoCase(_CMMD__RBInit) == 0)  
		{
			// Error Clear
			// Servo ON
			// All axes mode to home
			
			str__cmmd.Format("%s,INIT,1,1,G", str_unitid);
		}
		else if(set_data.CompareNoCase(_CMMD__RBErrClr) == 0)
		{
			str__cmmd.Format("%s,CCLR,E", str_unitid);
		}

		flag = _Recv__CMMD(var_name, true, str__cmmd,str__recv_data);

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

int CObj_NET__ATM_SR100
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
