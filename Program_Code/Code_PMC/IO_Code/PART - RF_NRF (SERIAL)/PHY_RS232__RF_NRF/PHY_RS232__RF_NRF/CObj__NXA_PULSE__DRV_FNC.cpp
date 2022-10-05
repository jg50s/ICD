#include "StdAfx.h"
#include "CObj__NXA_PULSE.h"
#include "CObj__NXA_PULSE__DEF.h"


//------------------------------------------------------------------------------------
int CObj__NXA_PULSE
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__NXA_PULSE
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__NXA_PULSE
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	// ...
	bool actove__param_a1 = false;
	bool actove__param_a2 = false;
	bool actove__param_b  = false;
	bool actove__param_c  = false;
	bool actove__get_exec = false;

		 if(siCH__PARAM_A1->Check__VARIABLE_NAME(var_name) > 0)			actove__param_a1 = true;
	else if(siCH__PARAM_A2->Check__VARIABLE_NAME(var_name) > 0)			actove__param_a2 = true;
	else if(siCH__PARAM_B->Check__VARIABLE_NAME(var_name)  > 0)			actove__param_b  = true;
	else if(siCH__PARAM_C->Check__VARIABLE_NAME(var_name)  > 0)			actove__param_c  = true;
	else if(siCH__GET_EXEC->Check__VARIABLE_NAME(var_name) > 0)			actove__get_exec = true;

	if((actove__param_a1)
	|| (actove__param_a2)
	|| (actove__param_b)
	|| (actove__param_c)
	|| (actove__get_exec))
	{
		unsigned char cmmd_id;

			 if(actove__param_a1)			cmmd_id = _NXA_CMD__GET_PARAM_A1;
		else if(actove__param_a2)			cmmd_id = _NXA_CMD__GET_PARAM_A2;
		else if(actove__param_b)			cmmd_id = _NXA_CMD__GET_PARAM_B;
		else if(actove__param_c)			cmmd_id = _NXA_CMD__GET_PARAM_C;
		else if(actove__get_exec)			cmmd_id = _NXA_CMD__GET_EXEC;
		else								return -1;

		int r_len = _Recv__Command(cmmd_id, r_data);		
		if(r_len > 8)
		{
			int r_offset = 3;

			if(actove__param_a1)
			{
				_DATA__4BYTE_UINT data_freq;
				
				// ...
				{
					byte data_2 = r_data[0 + r_offset];
					byte data_1 = r_data[1 + r_offset];
					byte data_0 = r_data[2 + r_offset];

					data_freq._byte[3] = 0;
					data_freq._byte[2] = data_2;
					data_freq._byte[1] = data_1;
					data_freq._byte[0] = data_0;
				}
			
				_DATA__4BYTE_UINT data_duty;

				// ...
				{
					byte data_1 = r_data[3 + r_offset];
					byte data_0 = r_data[4 + r_offset];

					data_duty._byte[3] = 0;
					data_duty._byte[2] = 0;
					data_duty._byte[1] = data_1;
					data_duty._byte[0] = data_0;
				}
						
				ch_data.Format("%.2f", dUNIT__FREQ*data_freq._hexa);
				sCH__INFO_PARAM_A_FREQ->Set__DATA(ch_data);
	
				ch_data.Format("%.2f", dUNIT__DUTY*data_duty._hexa);
				sCH__INFO_PARAM_A_DUTY->Set__DATA(ch_data);
			}
			else if(actove__param_a2)
			{
				_DATA__4BYTE_UINT data__on_time;

				// ...
				{
					byte data_2 = r_data[0 + r_offset];
					byte data_1 = r_data[1 + r_offset];
					byte data_0 = r_data[2 + r_offset];

					data__on_time._byte[3] = 0;
					data__on_time._byte[2] = data_2;
					data__on_time._byte[1] = data_1;
					data__on_time._byte[0] = data_0;
				}

				_DATA__4BYTE_UINT data__off_time;

				// ...
				{
					byte data_2 = r_data[3 + r_offset];
					byte data_1 = r_data[4 + r_offset];
					byte data_0 = r_data[5 + r_offset];

					data__off_time._byte[3] = 0;
					data__off_time._byte[2] = data_2;
					data__off_time._byte[1] = data_1;
					data__off_time._byte[0] = data_0;
				}

				ch_data.Format("%.0f", dUNIT__uSEQ*data__on_time._hexa);
				sCH__INFO_PARAM_A_ON_TIME->Set__DATA(ch_data);

				ch_data.Format("%.0f", dUNIT__uSEQ*data__off_time._hexa);
				sCH__INFO_PARAM_A_OFF_TIME->Set__DATA(ch_data);
			}
			else if(actove__param_b)
			{
				_DATA__4BYTE_INT data__on_time;

				// ...
				{
					byte data_2 = r_data[0 + r_offset];
					byte data_1 = r_data[1 + r_offset];
					byte data_0 = r_data[2 + r_offset];

					data__on_time._byte[3] = 0;
					data__on_time._byte[2] = data_2;
					data__on_time._byte[1] = data_1;
					data__on_time._byte[0] = data_0;
				}

				_DATA__4BYTE_INT data__off_time;

				// ...
				{
					byte data_2 = r_data[3 + r_offset];
					byte data_1 = r_data[4 + r_offset];
					byte data_0 = r_data[5 + r_offset];

					data__off_time._byte[3] = 0;
					data__off_time._byte[2] = data_2;
					data__off_time._byte[1] = data_1;
					data__off_time._byte[0] = data_0;
				}

				ch_data.Format("%.0f", dUNIT__uSEQ*data__on_time._hexa);
				sCH__INFO_PARAM_B_ON_SHIFT_TIME->Set__DATA(ch_data);

				//
				int value__off_time = data__off_time._hexa;
				int ref__minus_value = 0x800000;
				
				if(value__off_time >= ref__minus_value)
				{
					value__off_time = 0xffffff - value__off_time;
					value__off_time = -value__off_time;
				}

				ch_data.Format("%.0f", dUNIT__uSEQ*value__off_time);
				sCH__INFO_PARAM_B_OFF_SHIFT_TIME->Set__DATA(ch_data);
			}
			else if(actove__param_c)
			{
				_DATA__4BYTE_INT data__on_time;

				// ...
				{
					byte data_2 = r_data[0 + r_offset];
					byte data_1 = r_data[1 + r_offset];
					byte data_0 = r_data[2 + r_offset];

					data__on_time._byte[3] = 0;
					data__on_time._byte[2] = data_2;
					data__on_time._byte[1] = data_1;
					data__on_time._byte[0] = data_0;
				}

				_DATA__4BYTE_INT data__off_time;

				// ...
				{
					byte data_2 = r_data[3 + r_offset];
					byte data_1 = r_data[4 + r_offset];
					byte data_0 = r_data[5 + r_offset];

					data__off_time._byte[3] = 0;
					data__off_time._byte[2] = data_2;
					data__off_time._byte[1] = data_1;
					data__off_time._byte[0] = data_0;
				}

				ch_data.Format("%.0f", dUNIT__uSEQ*data__on_time._hexa);
				sCH__INFO_PARAM_C_ON_SHIFT_TIME->Set__DATA(ch_data);

				ch_data.Format("%.0f", dUNIT__uSEQ*data__off_time._hexa);
				sCH__INFO_PARAM_C_OFF_SHIFT_TIME->Set__DATA(ch_data);
			}
			else if(actove__get_exec)
			{
				unsigned char para__clk_a = r_data[0 + r_offset];
				unsigned char para__clk_b = r_data[1 + r_offset];
				unsigned char para__clk_c = r_data[2 + r_offset];

				// CLK.A 
				ch_data = _Get__CLK_STATE(para__clk_a);
				sCH__INFO_CLK_A_CTRL->Set__DATA(ch_data);

				// CLK.B
				ch_data = _Get__CLK_STATE(para__clk_b);
				sCH__INFO_CLK_B_CTRL->Set__DATA(ch_data);

				// CLK.C
				ch_data = _Get__CLK_STATE(para__clk_c);
				sCH__INFO_CLK_C_CTRL->Set__DATA(ch_data);
			}

			read_data = STR__OK;
			return 1;
		}

		read_data = STR__ERROR;
		return -1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__NXA_PULSE
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return -1;
}

int CObj__NXA_PULSE
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	// Log ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "_Write__DIGITAL() \n";

		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" * set_data (%1d) <- %s \n", item_index, set_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);
	}

	// ...
	unsigned char cmmd_id;
	unsigned char param_data[10];
	int param_size = 0;


	if(doCH__PARAM_A1->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_id = _NXA_CMD__SET_PARAM_A1;

		double para_freq = aCH__PARA_A_DRV_FREQ->Get__VALUE();
		double para_duty = aCH__PARA_A_DRV_DUTY->Get__VALUE();

		_DATA__4BYTE_UINT data_freq;
		_DATA__2BYTE_UINT data_duty;
		int db_i = 0;

		data_freq._hexa = (int) (para_freq / dUNIT__FREQ);
		param_data[db_i++] = data_freq._byte[2];
		param_data[db_i++] = data_freq._byte[1];
		param_data[db_i++] = data_freq._byte[0];

		data_duty._hexa = (int) (para_duty / dUNIT__DUTY);
		param_data[db_i++] = data_duty._byte[1];
		param_data[db_i++] = data_duty._byte[0];

		param_size = db_i;

		return _Recv__Command(cmmd_id, param_data,param_size);		
	}
	if(doCH__PARAM_A2->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_id = _NXA_CMD__SET_PARAM_A2;

		double para__on_time  = aCH__PARA_A_DRV_ON_TIME->Get__VALUE();
		double para__off_time = aCH__PARA_A_DRV_OFF_TIME->Get__VALUE();

		_DATA__4BYTE_UINT data__on_time;
		_DATA__4BYTE_UINT data__off_time;
		int db_i = 0;

		data__on_time._hexa = (int) (para__on_time / dUNIT__uSEQ);
		param_data[db_i++] = data__on_time._byte[2];
		param_data[db_i++] = data__on_time._byte[1];
		param_data[db_i++] = data__on_time._byte[0];

		data__off_time._hexa = (int) (para__off_time / dUNIT__uSEQ);
		param_data[db_i++] = data__off_time._byte[2];
		param_data[db_i++] = data__off_time._byte[1];
		param_data[db_i++] = data__off_time._byte[0];

		param_size = db_i;

		return _Recv__Command(cmmd_id, param_data,param_size);		
	}

	if((doCH__PARAM_B->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__PARAM_C->Check__VARIABLE_NAME(var_name) > 0))
	{
		double para__on_time  = 0;
		double para__off_time = 0;

		if(doCH__PARAM_B->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _NXA_CMD__SET_PARAM_B;

			para__on_time  = aCH__PARA_B_DRV_ON_SHIFT_TIME->Get__VALUE();
			para__off_time = aCH__PARA_B_DRV_OFF_SHIFT_TIME->Get__VALUE();
		}
		else if(doCH__PARAM_C->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _NXA_CMD__SET_PARAM_C;

			para__on_time  = aCH__PARA_C_DRV_ON_SHIFT_TIME->Get__VALUE();
			para__off_time = aCH__PARA_C_DRV_OFF_SHIFT_TIME->Get__VALUE();
		}

		_DATA__4BYTE_INT data__on_time;
		_DATA__4BYTE_INT data__off_time;
		int db_i = 0;

		data__on_time._hexa = (int) (para__on_time / dUNIT__uSEQ);
		param_data[db_i++] = data__on_time._byte[2];
		param_data[db_i++] = data__on_time._byte[1];
		param_data[db_i++] = data__on_time._byte[0];

		data__off_time._hexa = (int) (para__off_time / dUNIT__uSEQ);
		param_data[db_i++] = data__off_time._byte[2];
		param_data[db_i++] = data__off_time._byte[1];
		param_data[db_i++] = data__off_time._byte[0];

		param_size = db_i;

		return _Recv__Command(cmmd_id, param_data,param_size);		
	}

	if(doCH__SET_EXEC->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_id = _NXA_CMD__SET_EXEC;

		CString para__clk_a = dCH__PARA_A_DRV_CLK_CTRL->Get__STRING();
		CString para__clk_b = dCH__PARA_B_DRV_CLK_CTRL->Get__STRING();
		CString para__clk_c = dCH__PARA_C_DRV_CLK_CTRL->Get__STRING();

		int db_i = 0;

		if(set_data.CompareNoCase(STR__ON) == 0)
		{
				 if(para__clk_a.CompareNoCase(STR__NORMAL)  == 0)		param_data[db_i++] = 0;		// Normal
			else if(para__clk_a.CompareNoCase(STR__INVERSE) == 0)		param_data[db_i++] = 1;		// Inverse
			else if(para__clk_a.CompareNoCase(STR__HIGH)    == 0)		param_data[db_i++] = 2;		// High
			else														param_data[db_i++] = 3;		// Low.Fixed

				 if(para__clk_b.CompareNoCase(STR__NORMAL)  == 0)		param_data[db_i++] = 0;		// Normal
			else if(para__clk_b.CompareNoCase(STR__INVERSE) == 0)		param_data[db_i++] = 1;		// Inverse
			else if(para__clk_b.CompareNoCase(STR__HIGH)    == 0)		param_data[db_i++] = 2;		// High
			else														param_data[db_i++] = 3;		// Low.Fixed

				 if(para__clk_c.CompareNoCase(STR__NORMAL)  == 0)		param_data[db_i++] = 0;		// Normal
			else if(para__clk_c.CompareNoCase(STR__INVERSE) == 0)		param_data[db_i++] = 1;		// Inverse
			else if(para__clk_c.CompareNoCase(STR__HIGH)    == 0)		param_data[db_i++] = 2;		// High
			else														param_data[db_i++] = 3;		// Low.Fixed
		}
		else
		{
			param_data[db_i++] = 3;		// CLK.A : Low.Fixed
			param_data[db_i++] = 3;		// CLK.B : Low.Fixed
			param_data[db_i++] = 3;		// CLK.C : Low.Fixed
		}

		param_size = db_i;

		return _Recv__Command(cmmd_id, param_data,param_size);		
	}
	if(doCH__FLASH_CTRL->Check__VARIABLE_NAME(var_name) > 0)
	{
			 if(set_data.CompareNoCase(STR__WRITE) == 0)		cmmd_id = _NXA_CMD__FRASH_WRITE;
		else if(set_data.CompareNoCase(STR__ERASE) == 0)		cmmd_id = _NXA_CMD__FRASH_ERASE;
		else													return -1;

		param_size = 0;

		return _Recv__Command(cmmd_id, param_data,param_size);		
	}

	return -1;
}

int CObj__NXA_PULSE
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

