#include "StdAfx.h"
#include "CObj__RTU_SERIAL.h"


//------------------------------------------------------------------------------------
int CObj__RTU_SERIAL
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__RTU_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__RTU_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString ch_data;

	unsigned char r_data[256];
	int r_len = 0;

	memset(r_data, 0, 256);

	//
	if((siCH__DRIVER_STS__AUTO->Check__VARIABLE_NAME(var_name)   > 0)
	|| (siCH__DRIVER_STS__MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		unsigned short reg_addr  = 0x007F;
		unsigned short reg_count = 1;

		int r_val = _Read__Command(reg_addr, reg_count, r_data,r_len);
		if(r_val < 0)
		{
			read_data = "ERROR.1";

			sCH__INFO_DRV_BYTE_0_HEXA->Set__DATA("??");
			sCH__INFO_DRV_BYTE_1_HEXA->Set__DATA("??");
			return 1;
		}

		unsigned char byte_len = r_data[2];
		if(byte_len != 2)
		{
			read_data = "ERROR.2";

			sCH__INFO_DRV_BYTE_0_HEXA->Set__DATA("**");
			sCH__INFO_DRV_BYTE_1_HEXA->Set__DATA("**");
			return 1;
		}

		// Bit : 08 ~ 15
		{
			unsigned char byte_sts = 0x0ff & r_data[3];

			ch_data.Format("%02X", byte_sts);
			sCH__INFO_DRV_BYTE_0_HEXA->Set__DATA(ch_data);

			//
			if(byte_sts & 0x01)			sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT08_BUSY->Set__DATA(STR__OFF);

			if(byte_sts & 0x02)			sCH__INFO_DRV_BIT09_AREA0->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT09_AREA0->Set__DATA(STR__OFF);

			if(byte_sts & 0x04)			sCH__INFO_DRV_BIT10_AREA1->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT10_AREA1->Set__DATA(STR__OFF);

			if(byte_sts & 0x08)			sCH__INFO_DRV_BIT11_AREA2->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT11_AREA2->Set__DATA(STR__OFF);

			//
			if(byte_sts & 0x10)			sCH__INFO_DRV_BIT12_TIM->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT12_TIM->Set__DATA(STR__OFF);

			if(byte_sts & 0x20)			sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT13_MOVE->Set__DATA(STR__OFF);

			if(byte_sts & 0x40)			sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT14_IN_POS->Set__DATA(STR__OFF);

			if(byte_sts & 0x80)			sCH__INFO_DRV_BIT15_TLC->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT15_TLC->Set__DATA(STR__OFF);
		}
		// Bit : 00 ~ 07
		{
			unsigned char byte_sts = 0x0ff & r_data[4];

			ch_data.Format("%02X", byte_sts);
			sCH__INFO_DRV_BYTE_1_HEXA->Set__DATA(ch_data);

			//
			if(byte_sts & 0x01)			sCH__INFO_DRV_BIT00_M0->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT00_M0->Set__DATA(STR__OFF);

			if(byte_sts & 0x02)			sCH__INFO_DRV_BIT01_M1->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT01_M1->Set__DATA(STR__OFF);

			if(byte_sts & 0x04)			sCH__INFO_DRV_BIT02_M2->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT02_M2->Set__DATA(STR__OFF);

			if(byte_sts & 0x08)			sCH__INFO_DRV_BIT03_START->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT03_START->Set__DATA(STR__OFF);

			//
			if(byte_sts & 0x10)			sCH__INFO_DRV_BIT04_HOME->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT04_HOME->Set__DATA(STR__OFF);

			if(byte_sts & 0x20)			sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT05_READY->Set__DATA(STR__OFF);

			if(byte_sts & 0x40)			sCH__INFO_DRV_BIT06_INFO->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT06_INFO->Set__DATA(STR__OFF);

			if(byte_sts & 0x80)			sCH__INFO_DRV_BIT07_ALARM->Set__DATA(STR__ON);
			else						sCH__INFO_DRV_BIT07_ALARM->Set__DATA(STR__OFF);
		}

		read_data = "OK";
		return 1;
	}

	if(siCH__MONITOR_ALL->Check__VARIABLE_NAME(var_name) > 0)
	{
		unsigned short reg_addr  = 0x00C4;
		unsigned short reg_count = 22;

		int r_val = _Read__Command(reg_addr, reg_count, r_data,r_len);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		unsigned char byte_len = r_data[2];
		if(byte_len != 44)
		{
			read_data = "ERROR.2";
			return 1;
		}

		// ...
		int addr_offset = 3;

		// 0 : Data.No ...
		{
			addr_offset += 0;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			ch_data.Format("%1d", cur_data);
			sCH__INFO_MON_DATA_NO->Set__DATA(ch_data);
		}
		// 1 : Pos.Set ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__pos_step = 0;

			cur__pos_step += (byte_03 << 24);
			cur__pos_step += (byte_02 << 16);
			cur__pos_step += (byte_01 << 8);
			cur__pos_step += (byte_00 << 0);

			if(cur__pos_step >= 0x80000000)
			{
				cur__pos_step = 0xffffffff - cur__pos_step;

				ch_data.Format("-%1d", cur__pos_step);
			}
			else
			{
				ch_data.Format("%1d", cur__pos_step);
			}
			sCH__INFO_MON_POS_STEP_SET->Set__DATA(ch_data);
		}
		// 2 : Vel.Set (RPM) ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__vel_set = 0;

			cur__vel_set += (byte_03 << 24);
			cur__vel_set += (byte_02 << 16);
			cur__vel_set += (byte_01 << 8);
			cur__vel_set += (byte_00 << 0);

			if(cur__vel_set >= 0x80000000)
			{
				cur__vel_set = 0xffffffff - cur__vel_set;

				ch_data.Format("-%1d", cur__vel_set);
			}
			else
			{
				ch_data.Format("%1d", cur__vel_set);
			}
			sCH__INFO_MON_VEL_RPM_SET->Set__DATA(ch_data);
		}
		// 3 : Vel.Set (HZ) ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__vel_set = 0;

			cur__vel_set += (byte_03 << 24);
			cur__vel_set += (byte_02 << 16);
			cur__vel_set += (byte_01 << 8);
			cur__vel_set += (byte_00 << 0);

			if(cur__vel_set >= 0x80000000)
			{
				cur__vel_set = 0xffffffff - cur__vel_set;

				ch_data.Format("-%1d", cur__vel_set);
			}
			else
			{
				ch_data.Format("%1d", cur__vel_set);
			}
			sCH__INFO_MON_VEL_HZ_SET->Set__DATA(ch_data);
		}		
		// 4 : Pos.Current ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__pos_step = 0;

			cur__pos_step += (byte_03 << 24);
			cur__pos_step += (byte_02 << 16);
			cur__pos_step += (byte_01 << 8);
			cur__pos_step += (byte_00 << 0);

			if(cur__pos_step >= 0x80000000)
			{
				cur__pos_step = 0xffffffff - cur__pos_step;

				ch_data.Format("-%1d", cur__pos_step);
			}
			else
			{
				ch_data.Format("%1d", cur__pos_step);
			}
			
			sCH__INFO_MON_POS_STEP_CUR->Set__DATA(ch_data);
			sCH__INFO_CUR_POS_STEP->Set__DATA(ch_data);

			// ...
			{
				double cfg_unit = aCH__CFG_CONVERSION_UNIT_PULSE_TO_MM->Get__VALUE();
				double cfg_offset = aCH__CFG_HOME_ZERO_BASE_OFFSET->Get__VALUE();

				ch_data = sCH__INFO_CUR_POS_STEP->Get__STRING();
				double cur_pulse = atof(ch_data);
				double cur_pos = (cur_pulse * cfg_unit) - cfg_offset;				
				
				ch_data.Format("%.1f", cur_pos);
				sCH__INFO_CUR_POS_MM->Set__DATA(ch_data);
			}
		}
		// 5 : Vel.Current (RPM) ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__vel_set = 0;

			cur__vel_set += (byte_03 << 24);
			cur__vel_set += (byte_02 << 16);
			cur__vel_set += (byte_01 << 8);
			cur__vel_set += (byte_00 << 0);

			if(cur__vel_set >= 0x80000000)
			{
				cur__vel_set = 0xffffffff - cur__vel_set;

				ch_data.Format("-%1d", cur__vel_set);
			}
			else
			{
				ch_data.Format("%1d", cur__vel_set);
			}

			sCH__INFO_MON_VEL_RPM_CUR->Set__DATA(ch_data);
			sCH__INFO_CUR_VEL->Set__DATA(ch_data);
		}
		// 6 : Vel.Current (HZ) ...
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur__vel_set = 0;

			cur__vel_set += (byte_03 << 24);
			cur__vel_set += (byte_02 << 16);
			cur__vel_set += (byte_01 << 8);
			cur__vel_set += (byte_00 << 0);

			if(cur__vel_set >= 0x80000000)
			{
				cur__vel_set = 0xffffffff - cur__vel_set;

				ch_data.Format("-%1d", cur__vel_set);
			}
			else
			{
				ch_data.Format("%1d", cur__vel_set);
			}
			sCH__INFO_MON_VEL_HZ_CUR->Set__DATA(ch_data);
		}		
		// 7 : Dwell 시간의 남은 시간 (msec)
		{
			addr_offset += 0;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			ch_data.Format("%1d", cur_data);
			sCH__INFO_MON_DWELL_MSEC_CUR->Set__DATA(ch_data);
		}
		// 7 : Dwell 시간의 남은 시간 (msec)
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			ch_data.Format("%1d", cur_data);
			sCH__INFO_MON_DWELL_MSEC_CUR->Set__DATA(ch_data);
		}
		// 8 : Direct I/O
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			ch_data.Format("%1d", cur_data);
			sCH__INFO_MON_DIRECT_IO_CUR->Set__DATA(ch_data);
		}
		// 9 : Torque (%)
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			double cur_torque = 0.0;
			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			if(cur_data >= 0x80000000)
			{
				cur_data = 0xffffffff - cur_data;

				cur_torque = cur_data;
				cur_torque = - cur_torque;
			}
			else
			{
				cur_torque = cur_data;
			}

			ch_data.Format("%.1f", (cur_torque / 10.0));
			sCH__INFO_MON_TORQUE_CUR->Set__DATA(ch_data);
		}
		// 10 : Motor_Load (%)
		{
			addr_offset += 4;
			unsigned int byte_03 = 0x0ff & r_data[addr_offset + 0];
			unsigned int byte_02 = 0x0ff & r_data[addr_offset + 1];
			unsigned int byte_01 = 0x0ff & r_data[addr_offset + 2];
			unsigned int byte_00 = 0x0ff & r_data[addr_offset + 3];

			unsigned int cur_data = 0;

			cur_data += (byte_03 << 24);
			cur_data += (byte_02 << 16);
			cur_data += (byte_01 << 8);
			cur_data += (byte_00 << 0);

			ch_data.Format("%.1f", (cur_data / 10.0));
			sCH__INFO_MON_MOTOR_LOAD_CUR->Set__DATA(ch_data);
		}

		read_data = "OK";
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__RTU_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return -1;
}

int CObj__RTU_SERIAL
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	unsigned short reg_addr;
	unsigned short reg_count;

	if(doCH__CTRL_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		reg_addr  = 0x007D;
		reg_count = 1;

		// ...
		unsigned char byte_high = 0;
		unsigned char byte_low  = 0;

		if(set_data.CompareNoCase(_IO_Cmd__HOME) == 0)
		{		
			byte_high = 0x00;
			byte_low  = 0x10;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__GOTO) == 0)
		{
			byte_high = 0x00;
			byte_low  = 0x08;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__JOG_UP) == 0)
		{
			byte_high = 0x10;
			byte_low  = 0x00;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__JOG_DOWN) == 0)
		{
			byte_high = 0x20;
			byte_low  = 0x00;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__STOP) == 0)
		{
			byte_high = 0x00;
			byte_low  = 0x20;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__ALARM_RESET) == 0)
		{
			byte_high = 0x00;
			byte_low  = 0x80;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__SERVO_OFF) == 0)
		{
			byte_high = 0x00;
			byte_low  = 0x40;
		}
		else if(set_data.CompareNoCase(_IO_Cmd__SERVO_ON) == 0)
		{
			byte_high = 0x00;
			byte_low  = 0x00;
		}
		else
		{
			byte_high = 0x00;
			byte_low  = 0x00;
		}

		_Set__Driver_Command_Of_Byte(byte_low, byte_high);

		// ...
		CUIntArray l__reg_data;	
		
		l__reg_data.Add(byte_high);
		l__reg_data.Add(byte_low);

		return _Send__Command(reg_addr, reg_count, l__reg_data);
	}

	if(doCH__PARA_GOTO_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		reg_addr  = 0x1800;
		reg_count = 10;

		// ...
		double para__goto_pulse = aCH__PARA_GOTO_POS_DATA_PULSE->Get__VALUE();
		double para__goto_speed = aCH__PARA_GOTO_POS_SPEED->Get__VALUE();
		double para__goto_accel = aCH__PARA_GOTO_POS_ACCEL->Get__VALUE();
		double para__goto_decel = aCH__PARA_GOTO_POS_DECEL->Get__VALUE();

		CUIntArray l__reg_data;	
		CString ch_data;

		// Moving Mode ...
		{
			unsigned char byte_3 = 0x00;
			unsigned char byte_2 = 0x00;
			unsigned char byte_1 = 0x00;
			unsigned char byte_0 = 0x01;		// Absolute Position

			l__reg_data.Add(byte_3);;
			l__reg_data.Add(byte_2);;
			l__reg_data.Add(byte_1);;
			l__reg_data.Add(byte_0);;
		}
		// Position ...
		{
			unsigned int set__goto_step = 0;

			if(para__goto_pulse < 0)
			{
				set__goto_step = (unsigned int) (-para__goto_pulse);
				set__goto_step = 0x0FFFFFFFF - set__goto_step;

				ch_data.Format("%1d", set__goto_step);
			}
			else
			{
				set__goto_step = (unsigned int) (para__goto_pulse);
				
				ch_data.Format("%1d", set__goto_step);
			}			
			sCH__INFO_SET_POS_STEP->Set__DATA(ch_data);

			// ...
			unsigned char byte_3 = 0x0ff & (set__goto_step >> 24);
			unsigned char byte_2 = 0x0ff & (set__goto_step >> 16);
			unsigned char byte_1 = 0x0ff & (set__goto_step >> 8);
			unsigned char byte_0 = 0x0ff & (set__goto_step >> 0);

			l__reg_data.Add(byte_3);;
			l__reg_data.Add(byte_2);;
			l__reg_data.Add(byte_1);;
			l__reg_data.Add(byte_0);;
		}
		// Velocity ...
		{
			unsigned int set__goto_value = (unsigned int) (para__goto_speed);

			ch_data.Format("%1d", set__goto_value);
			sCH__INFO_SET_VEL->Set__DATA(ch_data);

			// ...
			unsigned char byte_3 = 0x0ff & (set__goto_value >> 24);
			unsigned char byte_2 = 0x0ff & (set__goto_value >> 16);
			unsigned char byte_1 = 0x0ff & (set__goto_value >> 8);
			unsigned char byte_0 = 0x0ff & (set__goto_value >> 0);

			l__reg_data.Add(byte_3);;
			l__reg_data.Add(byte_2);;
			l__reg_data.Add(byte_1);;
			l__reg_data.Add(byte_0);;
		}
		// Acceleration ...
		{
			unsigned int set__goto_value = (unsigned int) (para__goto_accel);

			ch_data.Format("%1d", set__goto_value);
			sCH__INFO_SET_ACCEL->Set__DATA(ch_data);

			// ...
			unsigned char byte_3 = 0x0ff & (set__goto_value >> 24);
			unsigned char byte_2 = 0x0ff & (set__goto_value >> 16);
			unsigned char byte_1 = 0x0ff & (set__goto_value >> 8);
			unsigned char byte_0 = 0x0ff & (set__goto_value >> 0);

			l__reg_data.Add(byte_3);;
			l__reg_data.Add(byte_2);;
			l__reg_data.Add(byte_1);;
			l__reg_data.Add(byte_0);;
		}
		// Deceleration ...
		{
			unsigned int set__goto_value = (unsigned int) (para__goto_decel);

			ch_data.Format("%1d", set__goto_value);
			sCH__INFO_SET_DECEL->Set__DATA(ch_data);

			// ...
			unsigned char byte_3 = 0x0ff & (set__goto_value >> 24);
			unsigned char byte_2 = 0x0ff & (set__goto_value >> 16);
			unsigned char byte_1 = 0x0ff & (set__goto_value >> 8);
			unsigned char byte_0 = 0x0ff & (set__goto_value >> 0);

			l__reg_data.Add(byte_3);;
			l__reg_data.Add(byte_2);;
			l__reg_data.Add(byte_1);;
			l__reg_data.Add(byte_0);;
		}

		return _Send__Command(reg_addr, reg_count, l__reg_data);
	}

	return -1;
}

int CObj__RTU_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__RTU_SERIAL
::_Send__Command(const unsigned short reg_addr,
				 const unsigned short reg_count,
				 const CUIntArray& l_reg_data)
{
	int retry_count = 0;

LOOP_RETYR:

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString r_err;
		mX_Serial->CLEAR__BUFFER(&r_err);
	}

	// ...
	unsigned char s_cmd[100];
	int s_len = 0;

	unsigned char slave_id = iPARA__SLAVE_ID;

	if(reg_count > 1)
	{
		int i = 0;

		s_cmd[i++] = 0x0ff & slave_id;
		s_cmd[i++] = 0x10;

		s_cmd[i++] = 0x0ff & (reg_addr  >> 8);
		s_cmd[i++] = 0x0ff & (reg_addr  >> 0);

		s_cmd[i++] = 0x0ff & (reg_count >> 8);
		s_cmd[i++] = 0x0ff & (reg_count >> 0);

		s_cmd[i++] = 0x0ff & (reg_count * 2);

		int k_limit = l_reg_data.GetSize();
		for(int k=0; k<k_limit; k++)
		{
			s_cmd[i++] = 0x0ff & l_reg_data[k];
		}

		unsigned short crc = _Get__CRC16(s_cmd, i);
		s_cmd[i++] = 0x0ff & (crc >> 0);
		s_cmd[i++] = 0x0ff & (crc >> 8);

		s_len = i;
	}
	else
	{
		int i = 0;

		s_cmd[i++] = 0x0ff & slave_id;
		s_cmd[i++] = 0x06;

		s_cmd[i++] = 0x0ff & (reg_addr >> 8);
		s_cmd[i++] = 0x0ff & (reg_addr >> 0);

		int k_limit = l_reg_data.GetSize();
		for(int k=0; k<k_limit; k++)
		{
			s_cmd[i++] = 0x0ff & l_reg_data[k];
		}

		unsigned short crc = _Get__CRC16(s_cmd, i);
		s_cmd[i++] = 0x0ff & (crc >> 0);
		s_cmd[i++] = 0x0ff & (crc >> 8);

		s_len = i;
	}

	// Send.Log ...
	{
		log_msg = "Send >> \n";

		for(int i=0; i<s_len; i++)
		{
			log_bff.Format("%02X ", (0x0ff & s_cmd[i]));
			log_msg += log_bff;
		}

		Write__DRV_LOG(log_msg);		
	}

	mX_Serial->CHAR__SEND(s_cmd, s_len);

	// ...
	int cfg__to_msec = 200;

	unsigned char r_data[256];
	int r_len = s_len;

	memset(r_data, 0, 256);

	int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, &r_len, cfg__to_msec);
	if (r_flag < 0)
	{
		// ...
		{
			log_msg = "Recv << \n";

			log_bff.Format("  Error (%1d)\n", r_flag);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}

		bActive__COMM_ONLINE = false;
		return -1;
	}

	// Recv.Log ...
	{
		log_msg.Format("Recv (%1d) << \n", r_len);

		for(int i=0; i<r_len; i++)
		{
			log_bff.Format("%02X ", (0x0ff & r_data[i]));
			log_msg += log_bff;
		}

		Write__DRV_LOG(log_msg);		
	}

	// Check : s_cmd & r_cmd ...
	{
		bool active__err_check = false;

		for(int i=0; i<s_len; i++)
		{
			if(s_cmd[i] == r_data[i])		continue;

			active__err_check = true;
			break;
		}

		if(active__err_check)
		{
			log_msg = "Check Error ... \n";

			unsigned char fnc_code = r_data[1];

			if(fnc_code > 0x80)
			{
				unsigned char err_code = r_data[2];

				log_bff.Format("  * Error Code <- %02X \n", err_code);
				log_msg += log_bff;
			}
			else
			{
				log_msg += "  * Data Mismatch ! \n";
			}

			Write__DRV_LOG(log_msg);		

			retry_count++;
			if(retry_count <= 2)			goto LOOP_RETYR;

			return -101;
		}
	}

	bActive__COMM_ONLINE = true;
	return r_flag;
}

int CObj__RTU_SERIAL
::_Read__Command(const unsigned short reg_addr,
				 const unsigned short reg_count,
				 unsigned char* r_data,
				 int& r_len)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString r_err;
		mX_Serial->CLEAR__BUFFER(&r_err);
	}

	// ...
	unsigned char s_cmd[100];
	int s_len = 0;

	unsigned char slave_id = iPARA__SLAVE_ID;

	// ...
	{
		int i = 0;

		s_cmd[i++] = 0x0ff & slave_id;
		s_cmd[i++] = 0x03;

		s_cmd[i++] = 0x0ff & (reg_addr  >> 8);
		s_cmd[i++] = 0x0ff & (reg_addr  >> 0);
		s_cmd[i++] = 0x0ff & (reg_count >> 8);
		s_cmd[i++] = 0x0ff & (reg_count >> 0);

		unsigned short crc = _Get__CRC16(s_cmd, i);
		s_cmd[i++] = 0x0ff & (crc >> 0);
		s_cmd[i++] = 0x0ff & (crc >> 8);

		s_len = i;
	}

	// Send.Log ...
	{
		log_msg = "Send >> \n";

		for(int i=0; i<s_len; i++)
		{
			log_bff.Format("%02X ", (0x0ff & s_cmd[i]));
			log_msg += log_bff;
		}

		Write__DRV_LOG(log_msg);		
	}

	mX_Serial->CHAR__SEND(s_cmd, s_len);

	// ...
	int cfg__to_msec = 200;

	r_len = 5 + (reg_count * 2);

	int r_flag = mX_Serial->OnlyRecv__CHAR(r_data, &r_len, cfg__to_msec);
	if (r_flag < 0)
	{
		// ...
		{
			log_msg = "Recv << \n";

			log_bff.Format("  Error (%1d)\n", r_flag);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}

		bActive__COMM_ONLINE = false;
		return -1;
	}

	// Recv.Log ...
	{
		log_msg.Format("Recv (%1d) << \n", r_len);

		for(int i=0; i<r_len; i++)
		{
			log_bff.Format("%02X ", (0x0ff & r_data[i]));
			log_msg += log_bff;
		}

		Write__DRV_LOG(log_msg);		
	}

	bActive__COMM_ONLINE = true;
	return r_flag;
}

int CObj__RTU_SERIAL
::_Set__Driver_Command_Of_Byte(unsigned char byte_0, 
							   unsigned char byte_1)
{
	CString ch_data;

	// BYTE : 0
	{
		ch_data.Format("%02X", byte_0);
		sCH__SET_DRV_BYTE_0_HEXA->Set__DATA(ch_data);

		if(byte_0 & 0x01)			sCH__SET_DRV_BIT00_M0->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT00_M0->Set__DATA(STR__OFF);

		if(byte_0 & 0x02)			sCH__SET_DRV_BIT01_M1->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT01_M1->Set__DATA(STR__OFF);

		if(byte_0 & 0x04)			sCH__SET_DRV_BIT02_M2->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT02_M2->Set__DATA(STR__OFF);

		if(byte_0 & 0x08)			sCH__SET_DRV_BIT03_START->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT03_START->Set__DATA(STR__OFF);

		if(byte_0 & 0x10)			sCH__SET_DRV_BIT04_HOME->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT04_HOME->Set__DATA(STR__OFF);

		if(byte_0 & 0x20)			sCH__SET_DRV_BIT05_STOP->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT05_STOP->Set__DATA(STR__OFF);

		if(byte_0 & 0x40)			sCH__SET_DRV_BIT06_FREE->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT06_FREE->Set__DATA(STR__OFF);

		if(byte_0 & 0x80)			sCH__SET_DRV_BIT07_ALARM_RESET->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT07_ALARM_RESET->Set__DATA(STR__OFF);
	}

	// BYTE : 1
	{
		ch_data.Format("%02X", byte_1);
		sCH__SET_DRV_BYTE_1_HEXA->Set__DATA(ch_data);

		if(byte_1 & 0x01)			sCH__SET_DRV_BIT08_D_SEL0->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT08_D_SEL0->Set__DATA(STR__OFF);

		if(byte_1 & 0x02)			sCH__SET_DRV_BIT09_D_SEL1->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT09_D_SEL1->Set__DATA(STR__OFF);

		if(byte_1 & 0x04)			sCH__SET_DRV_BIT10_D_SEL2->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT10_D_SEL2->Set__DATA(STR__OFF);

		if(byte_1 & 0x08)			sCH__SET_DRV_BIT11_SSTART->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT11_SSTART->Set__DATA(STR__OFF);

		if(byte_1 & 0x10)			sCH__SET_DRV_BIT12_FW_JOG->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT12_FW_JOG->Set__DATA(STR__OFF);

		if(byte_1 & 0x20)			sCH__SET_DRV_BIT13_RV_JOG->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT13_RV_JOG->Set__DATA(STR__OFF);

		if(byte_1 & 0x40)			sCH__SET_DRV_BIT14_FW_POS->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT14_FW_POS->Set__DATA(STR__OFF);

		if(byte_1 & 0x80)			sCH__SET_DRV_BIT15_RV_POS->Set__DATA(STR__ON);
		else						sCH__SET_DRV_BIT15_RV_POS->Set__DATA(STR__OFF);
	}

	return 1;
}


// ...
#define POLYNORMIAL			0xA001

unsigned short  CObj__RTU_SERIAL
::_Get__CRC16(unsigned char* s_data, const int data_len)
{
	unsigned short crc, flag;
	int count = data_len;

	crc = 0xffff;

	while(count--)
	{
		crc ^= *s_data++;

		for (int i=0; i<8; i++)
		{
			flag = crc & 0x0001;
			crc >>= 1;
			if(flag) crc ^= POLYNORMIAL;
		}
	}
	return crc;
}
