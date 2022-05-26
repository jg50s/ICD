#include "StdAfx.h"
#include "CObj__MFC_IO.h"
#include "CObj__MFC_IO__DEF.h"
#include "CObj__MFC_IO__ALID.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
// 1. MFCx Purge Valve -> Open
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC1_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC2_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC3_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC4_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC5_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC6_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC7_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC8_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC9_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC10_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC11_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC12_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC13_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC14_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC15_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC16_Purge_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC17_Purge_Valve_Open);

// 2. MFCx Primary Valve -> Open
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC1_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC2_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC3_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC4_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC5_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC6_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC7_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC8_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC9_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC10_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC11_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC12_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC13_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC14_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC15_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC16_Primary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC17_Primary_Valve_Open);

// 3. MFCx Secondary Valve -> Open
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC1_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC2_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC3_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC4_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC5_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC6_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC7_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC8_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC9_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC10_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC11_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC12_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC13_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC14_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC15_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC16_Secondary_Valve_Open);
INTERLOCK_REGISTER(CObj__MFC_IO, Fnc_SetPoint__MFC17_Secondary_Valve_Open);


//-------------------------------------------------------------------------
int  CObj__MFC_IO
::__DEFINE__IO_INTERLOCK(p_interlock)
{
	CString ch_name;
	CString obj_name;
	CString var_name;
	CString var_data;
	int i;

	// 1. MFCx Valve.Purge -> Open
	{
		var_data = STR__OPEN;	

		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			ch_name = sList_Channel__MFC_DO_VLV_PURGE[i];
			if(ch_name.GetLength() < 1)		continue;

			_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

			if(i == 0)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC1_Purge_Valve_Open);
			if(i == 1)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC2_Purge_Valve_Open);
			if(i == 2)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC3_Purge_Valve_Open);
			if(i == 3)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC4_Purge_Valve_Open);
			if(i == 4)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC5_Purge_Valve_Open);
			if(i == 5)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC6_Purge_Valve_Open);
			if(i == 6)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC7_Purge_Valve_Open);
			if(i == 7)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC8_Purge_Valve_Open);
			if(i == 8)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC9_Purge_Valve_Open);
			if(i == 9)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC10_Purge_Valve_Open);
			if(i == 10)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC11_Purge_Valve_Open);
			if(i == 11)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC12_Purge_Valve_Open);
			if(i == 12)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC13_Purge_Valve_Open);
			if(i == 13)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC14_Purge_Valve_Open);
			if(i == 14)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC15_Purge_Valve_Open);
			if(i == 15)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC16_Purge_Valve_Open);
			if(i == 16)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC17_Purge_Valve_Open);
		}
	}

	// 2. MFCx Valve.In -> Open
	{
		var_data = STR__OPEN;	

		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			ch_name = sList_Channel__MFC_DO_VLV_IN[i];
			if(ch_name.GetLength() < 1)		continue;

			_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

			if(i == 0)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC1_Primary_Valve_Open);
			if(i == 1)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC2_Primary_Valve_Open);
			if(i == 2)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC3_Primary_Valve_Open);
			if(i == 3)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC4_Primary_Valve_Open);
			if(i == 4)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC5_Primary_Valve_Open);
			if(i == 5)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC6_Primary_Valve_Open);
			if(i == 6)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC7_Primary_Valve_Open);
			if(i == 7)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC8_Primary_Valve_Open);
			if(i == 8)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC9_Primary_Valve_Open);
			if(i == 9)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC10_Primary_Valve_Open);
			if(i == 10)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC11_Primary_Valve_Open);
			if(i == 11)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC12_Primary_Valve_Open);
			if(i == 12)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC13_Primary_Valve_Open);
			if(i == 13)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC14_Primary_Valve_Open);
			if(i == 14)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC15_Primary_Valve_Open);
			if(i == 15)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC16_Primary_Valve_Open);
			if(i == 16)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC17_Primary_Valve_Open);
		}
	}

	// 3. MFCx Valve.Out -> Open
	{
		var_data = STR__OPEN;	

		for(i=0; i<iSIZE__MFC_OBJ; i++)
		{
			ch_name = sList_Channel__MFC_DO_VLV_OUT[i];
			if(ch_name.GetLength() < 1)		continue;

			_Macro__Get_Channel_To_Obj_Variable(ch_name, obj_name,var_name);

			if(i == 0)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC1_Secondary_Valve_Open);
			if(i == 1)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC2_Secondary_Valve_Open);
			if(i == 2)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC3_Secondary_Valve_Open);
			if(i == 3)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC4_Secondary_Valve_Open);
			if(i == 4)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC5_Secondary_Valve_Open);
			if(i == 5)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC6_Secondary_Valve_Open);
			if(i == 6)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC7_Secondary_Valve_Open);
			if(i == 7)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC8_Secondary_Valve_Open);
			if(i == 8)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC9_Secondary_Valve_Open);
			if(i == 9)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC10_Secondary_Valve_Open);
			if(i == 10)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC11_Secondary_Valve_Open);
			if(i == 11)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC12_Secondary_Valve_Open);
			if(i == 12)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC13_Secondary_Valve_Open);
			if(i == 13)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC14_Secondary_Valve_Open);
			if(i == 14)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC15_Secondary_Valve_Open);
			if(i == 15)		p_interlock->REGISTER__VARIABLE_NAME(obj_name,var_name,var_data, Fnc_SetPoint__MFC16_Secondary_Valve_Open);
		}
	}

	return 1;
}


//--------------------------------------------------------
//	Interlock Function Add

// 1. MFCx Purge Valve -> Open ...
int CObj__MFC_IO::IFnc_SetPoint__MFC1_Purge_Valve_Open()
{
	int mfc_id = 1;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC2_Purge_Valve_Open()
{
	int mfc_id = 2;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC3_Purge_Valve_Open()
{
	int mfc_id = 3;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC4_Purge_Valve_Open()
{
	int mfc_id = 4;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC5_Purge_Valve_Open()
{
	int mfc_id = 5;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC6_Purge_Valve_Open()
{
	int mfc_id = 6;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC7_Purge_Valve_Open()
{
	int mfc_id = 7;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC8_Purge_Valve_Open()
{
	int mfc_id = 8;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC9_Purge_Valve_Open()
{
	int mfc_id = 9;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC10_Purge_Valve_Open()
{
	int mfc_id = 10;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC11_Purge_Valve_Open()
{
	int mfc_id = 11;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC12_Purge_Valve_Open()
{
	int mfc_id = 12;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC13_Purge_Valve_Open()
{
	int mfc_id = 13;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC14_Purge_Valve_Open()
{
	int mfc_id = 14;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC15_Purge_Valve_Open()
{
	int mfc_id = 15;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC16_Purge_Valve_Open()
{
	int mfc_id = 16;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC17_Purge_Valve_Open()
{
	int mfc_id = 17;
	return SetPoint__MFCx_Purge_Valve_Open(mfc_id);
}

int CObj__MFC_IO::SetPoint__MFCx_Purge_Valve_Open(const int mfc_id)
{
	int err_check = -1;
	CString err_msg;
	CString err_bff;

	if(diEXT_CH__GAS_BOX_CONVER->Check__DATA(sGAS_BOX_COVER__NORMAL_STATE) < 0)
	{
		int alarm_id = ALID__GAS_BOX_NOT_CLOSED_INTERLOCK + (mfc_id - 1);

		if(mfc_id < 1)
		{
			alarm_id = ALID__GAS_BOX_NOT_CLOSED_INTERLOCK;
		}

		err_msg.Format("MFC%1d's Purge Valve Open Interlock !", mfc_id);

		Post_Alarm(alarm_id,err_msg);
		return -1;
	}

	if(err_check < 0)
	{
		if(Check__MFC_Interlock(mfc_id,err_msg) < 0)
		{
			err_check = 1;
		}
	}
	if(err_check < 0)
	{
		if((mfc_id > 0) && (mfc_id < iSIZE__MFC_OBJ))
		{
			int db_index = mfc_id - 1;

			if(bActive__MFC_DO_VLV_IN_X[db_index])
			{
				if(doEXT_CH__MFC_DO_VLV_IN_X[db_index]->Check__DATA(STR__OPEN) > 0)
				{
					err_check = 1;

					err_msg.Format("MFC%1d의 Primary Valve가 Open 된 상태입니다. \n", mfc_id);
					err_bff.Format("MFC%1d의 Primary Valve를 Close한 이후에 진행하시기 바랍니다. \n", mfc_id);
					err_msg += err_bff;
				}
			}
		}
	}

	if(err_check > 0)
	{
		int alarm_id = ALID__MFCx_PURGE_VLV_OPEN_INTERLOCK + (mfc_id - 1);

		if(mfc_id < 1)
		{
			alarm_id = ALID__MFCx_PURGE_VLV_OPEN_INTERLOCK;
		}

		Post_Alarm(alarm_id,err_msg);
		return -1;
	}

	return 1;
}

// 2. MFCx Primary Valve -> Open ...
int CObj__MFC_IO::IFnc_SetPoint__MFC1_Primary_Valve_Open()
{
	int mfc_id = 1;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC2_Primary_Valve_Open()
{
	int mfc_id = 2;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC3_Primary_Valve_Open()
{
	int mfc_id = 3;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC4_Primary_Valve_Open()
{
	int mfc_id = 4;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC5_Primary_Valve_Open()
{
	int mfc_id = 5;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC6_Primary_Valve_Open()
{
	int mfc_id = 6;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC7_Primary_Valve_Open()
{
	int mfc_id = 7;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC8_Primary_Valve_Open()
{
	int mfc_id = 8;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC9_Primary_Valve_Open()
{
	int mfc_id = 9;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC10_Primary_Valve_Open()
{
	int mfc_id = 10;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC11_Primary_Valve_Open()
{
	int mfc_id = 11;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC12_Primary_Valve_Open()
{
	int mfc_id = 12;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC13_Primary_Valve_Open()
{
	int mfc_id = 13;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC14_Primary_Valve_Open()
{
	int mfc_id = 14;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC15_Primary_Valve_Open()
{
	int mfc_id = 15;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC16_Primary_Valve_Open()
{
	int mfc_id = 16;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC17_Primary_Valve_Open()
{
	int mfc_id = 17;
	return SetPoint__MFCx_Primary_Valve_Open(mfc_id);
}

int CObj__MFC_IO::SetPoint__MFCx_Primary_Valve_Open(const int mfc_id)
{
	int err_check = -1;
	CString err_msg;
	CString err_bff;

	if(err_check < 0)
	{
		if(Check__MFC_Interlock(mfc_id,err_msg) < 0)
		{
			err_check = 1;
		}
	}
	if(err_check < 0)
	{
		if((mfc_id > 0) && (mfc_id < iSIZE__MFC_OBJ))
		{
			int db_index = mfc_id - 1;

			if(bActive__MFC_DO_VLV_PURGE_X[db_index])
			{
				if(doEXT_CH__MFC_DO_VLV_PURGE_X[db_index]->Check__DATA(STR__OPEN) > 0)
				{
					err_check = 1;

					err_msg.Format("MFC%1d의 Purge Valve가 Open 된 상태입니다. \n", mfc_id);
					err_bff.Format("MFC%1d의 Purge Valve를 Close한 이후에 진행하시기 바랍니다. \n", mfc_id);
					err_msg += err_bff;
				}
			}
		}
	}

	if(err_check > 0)
	{
		int alarm_id = ALID__MFCx_PRIMARY_VLV_OPEN_INTERLOCK + (mfc_id - 1);

		if(mfc_id < 1)
		{
			alarm_id = ALID__MFCx_PRIMARY_VLV_OPEN_INTERLOCK;
		}

		Post_Alarm(alarm_id,err_msg);	
		return -1;
	}

	return 1;
}

// 3. MFCx Secondary Valve -> Open ...
int CObj__MFC_IO::IFnc_SetPoint__MFC1_Secondary_Valve_Open()
{
	int mfc_id = 1;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC2_Secondary_Valve_Open()
{
	int mfc_id = 2;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC3_Secondary_Valve_Open()
{
	int mfc_id = 3;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC4_Secondary_Valve_Open()
{
	int mfc_id = 4;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC5_Secondary_Valve_Open()
{
	int mfc_id = 5;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC6_Secondary_Valve_Open()
{
	int mfc_id = 6;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC7_Secondary_Valve_Open()
{
	int mfc_id = 7;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC8_Secondary_Valve_Open()
{
	int mfc_id = 8;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC9_Secondary_Valve_Open()
{
	int mfc_id = 9;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC10_Secondary_Valve_Open()
{
	int mfc_id = 10;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC11_Secondary_Valve_Open()
{
	int mfc_id = 11;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC12_Secondary_Valve_Open()
{
	int mfc_id = 12;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC13_Secondary_Valve_Open()
{
	int mfc_id = 13;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC14_Secondary_Valve_Open()
{
	int mfc_id = 14;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC15_Secondary_Valve_Open()
{
	int mfc_id = 15;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC16_Secondary_Valve_Open()
{
	int mfc_id = 16;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}
int CObj__MFC_IO::IFnc_SetPoint__MFC17_Secondary_Valve_Open()
{
	int mfc_id = 17;
	return SetPoint__MFCx_Secondary_Valve_Open(mfc_id);
}

int CObj__MFC_IO::SetPoint__MFCx_Secondary_Valve_Open(const int mfc_id)
{
	CString err_msg;

	if(diEXT_CH__GAS_BOX_CONVER->Check__DATA(sGAS_BOX_COVER__NORMAL_STATE) < 0)
	{
		int alarm_id = ALID__GAS_BOX_NOT_CLOSED_INTERLOCK + (mfc_id - 1);

		if(mfc_id < 1)
		{
			alarm_id = ALID__GAS_BOX_NOT_CLOSED_INTERLOCK;
		}

		err_msg.Format("MFC%1d's Secondary Valve Open Interlock ! \n", mfc_id);

		Post_Alarm(alarm_id,err_msg);
		return -1;
	}

	if(Check__MFC_Interlock(mfc_id,err_msg) < 0)
	{
		int alarm_id = ALID__MFCx_SECONDARY_VLV_OPEN_INTERLOCK + (mfc_id - 1);

		if(mfc_id < 1)
		{
			alarm_id = ALID__MFCx_SECONDARY_VLV_OPEN_INTERLOCK;
		}

		Post_Alarm(alarm_id,err_msg);
		return -1;
	}
	return 1;
}

