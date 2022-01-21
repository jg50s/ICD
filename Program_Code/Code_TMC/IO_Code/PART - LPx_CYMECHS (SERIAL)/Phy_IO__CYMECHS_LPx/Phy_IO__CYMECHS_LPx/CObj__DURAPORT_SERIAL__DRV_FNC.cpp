#include "stdafx.h"

#include "CObj__DURAPORT_SERIAL.h"
#include "CObj__DURAPORT_SERIAL__DEF.h"


// ...
int CObj__DURAPORT_SERIAL
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__DURAPORT_SERIAL
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	CString log_msg;
	CString log_bff;

	CString s_data;

	if(siCH__FIRMWARE_VER->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data = "GETVER";
	}
	else if(siCH__ERROR_CODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data = "ECODE";
	}
	else
	{
		log_msg = "__Read__STRING() : Var_Name Error ! \n";

		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;		
		
		Fnc__DRV_LOG(log_msg);
		return -101;
	}

	// ...
	{
		CString r_data;
		
		int r_len = _Recv__CMMD(var_name, s_data, r_data);

		// Log ...
		{
			log_msg = "__Read__STRING() ... \n";

			log_bff.Format(" * r_len <- %1d \n", r_len);
			log_msg += log_bff;		

			log_bff.Format(" * r_data <- [%s] \n", r_data);
			log_msg += log_bff;		

			Fnc__DRV_LOG(log_msg);
		}

		if(r_len > 0)
		{
			if(siCH__FIRMWARE_VER->Check__VARIABLE_NAME(var_name) > 0)
			{
				read_data = r_data;
				return 1;
			}
			else if(siCH__ERROR_CODE->Check__VARIABLE_NAME(var_name) > 0)
			{
				read_data = r_data;
				return 1;
			}

			return -111;
		}

		log_msg.Format("[NG] - read_data(%s)\n", read_data);	
		Fnc__DRV_LOG(log_msg);
	}

	return -1;
}

int CObj__DURAPORT_SERIAL
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{

	return -1;
}


// ...
int CObj__DURAPORT_SERIAL
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{

	return -1;
}

int CObj__DURAPORT_SERIAL
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString log_msg;
	CString log_bff;

	CString s_data;

	if(doCH__ERROR_RESET->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data = "RESET";
	}
	else if(doCH__AMP_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ON") == 0)				s_data = "AMPON";
		else												s_data = "AMPOFF";
	}
	else if(doCH__LAMP_AUTO_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("ON") == 0)				s_data = "AUTO_MODE ON";
		else												s_data = "AUTO_MODE OFF";
	}
	else if(doCH__UPDATE_SYSTEM->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data = "STATUS";
	}
	else if(doCH__UPDATE_INDICATOR->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_data = "STATUS_INDICATOR";
	}
	else if(doCH__OPR_LOAD_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		     if(set_data.CompareNoCase("LOAD")   == 0)		s_data = "LOAD";
		else if(set_data.CompareNoCase("UNLOAD") == 0)	    s_data = "UNLOAD";
	}
	else if(doCH__OPR_MAIN_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		     if(set_data.CompareNoCase("HOME")  == 0)		s_data = "HOM";
		else if(set_data.CompareNoCase("OPEN")  == 0)	    s_data = "TOPEN";
		else if(set_data.CompareNoCase("CLOSE") == 0)	    s_data = "TCLOSE";
		else if(set_data.CompareNoCase("SCAN")  == 0)	    s_data = "SCAN UP";
	}
	else if(doCH__OPR_CLAMP_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		     if(set_data.CompareNoCase("CLAMP")   == 0)		s_data = "POD_LOCK ON";
		else if(set_data.CompareNoCase("UNCLAMP") == 0)	    s_data = "POD_LOCK OFF";
	}
	else if(doCH__OPR_DOCK_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		     if(set_data.CompareNoCase("DOCK") == 0)		s_data = "DOCK";
		else if(set_data.CompareNoCase("UNDOCK") == 0)	    s_data = "UNDOCK";
	}
	else
	{
		log_msg = "__Write__DIGITAL() : Var_Name Error ! \n";

		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
		return -1;
	}

	// ...
	{
		CString var_data;
		CString r_data;

		int r_len = _Recv__CMMD(var_name, s_data, r_data);

		// ...
		{
			log_msg = "__Write__DIGITAL()... \n";

			log_bff.Format(" * r_len <- %1d \n", r_len);
			log_msg += log_bff;
			
			log_bff.Format(" * r_data <- [%s] \n", r_data);
			log_msg += log_bff;

			Fnc__DRV_LOG(log_msg);
		}

		if(_Check__ERROR_CODE(r_data) > 0)
		{
			// Log ...
			{
				log_msg.Format(" ** ERROR !!! \n");

				Fnc__DRV_LOG(log_msg);
			}
			return -1;
		}

		if(r_len > 0)
		{
			if(doCH__UPDATE_SYSTEM->Check__VARIABLE_NAME(var_name) > 0)
			{
				_Update__SYSTEM_STATUS(r_data);
			}
			else if(doCH__UPDATE_INDICATOR->Check__VARIABLE_NAME(var_name) > 0)
			{
				_Update__INDICATOR_STATUS(r_data);				
			}
			else if(doCH__OPR_LOAD_SET->Check__VARIABLE_NAME(var_name) > 0)
			{
				if(set_data.CompareNoCase("LOAD") == 0)
				{
					_Update__LPx_MAP(r_data);
				}
			}
			else if(doCH__OPR_MAIN_SET->Check__VARIABLE_NAME(var_name) > 0)
			{
				if(set_data.CompareNoCase("SCAN") == 0)
				{
					_Update__LPx_MAP(r_data);
				}
			}

			return 1;
		}		
	}

	return -1;
}

int CObj__DURAPORT_SERIAL
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


// ...
int CObj__DURAPORT_SERIAL
::_Recv__CMMD(const CString& var_name, 
		      const CString& set_data, 
		      CString& recv_data)
{
	CString log_msg;
	CString log_bff;

	// Log ...
	{
		log_msg = "Recv_CMD() ... \n";

		log_bff.Format(" * %s <- %s \n", var_name,set_data);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	int ref_tick = GetTickCount();
	int act_timeout = 30 * 1000;
	
	int loop_count = 0;
	int r_count = 0;

	// Init ...
	{
		CString buf_check;
		mX_Serial->CLEAR__BUFFER(&buf_check);

		mMng__RSP_MSG.Clear__ALL_RSP_MSG();
	}

	// Send ...
	{
		CString s_cmmd;

		s_cmmd  = set_data;
		s_cmmd += sStr_End;

		mX_Serial->DATA__SEND(s_cmmd);
	}

	// ...
	int rsp_active = -1;

	while(1)
	{
		Sleep(1);

		// ...
		CString rsp_msg;
		
		if(mMng__RSP_MSG.Get__RSP_MSG(rsp_msg) > 0)
		{
			m_nCommSts = ONLINE;

			if(rsp_msg.GetLength() > 0)
			{
				char ch_rsp = rsp_msg.GetAt(0);

				if((ch_rsp == 'A') || (ch_rsp == 'N'))
				{
					rsp_active = 1;
				}
				else if(ch_rsp == 'E')
				{
					recv_data = rsp_msg;
					return 1;
				}
				else if(rsp_active > 0)
				{
					recv_data = rsp_msg;
					return 1;
				}
			}
		}

		// ...
		{
			int dif_tick = GetTickCount() - ref_tick;

			if(dif_tick >= act_timeout)
			{
				// Log ...
				{
					log_msg = "Timeout ! \n";

					log_bff.Format(" * ref_timeput <- %1d \n", dif_tick);
					log_msg += log_bff;

					Fnc__DRV_LOG(log_msg);
				}

				m_nCommSts = OFFLINE;
				return -1;
			}
			else if(dif_tick < 0)
			{
				ref_tick = GetTickCount();
			}
		}
	} 

	return -1;
}

int CObj__DURAPORT_SERIAL
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

		if(iSim_Mode > 0)
		{
			Sleep(100);
			continue;
		}

		// ...
		CString r_data = "";

		int r_len = mX_Serial->OnlyRecv__DATA(sStr_End, &r_data, m_nTimeout);
		if(r_len > 0)
		{
			log_msg = "Response_Msg ... \n";

			// ...
			CString str_bff;
			mX_Serial->CLEAR__BUFFER(&str_bff);

			if(str_bff.GetLength() > 0)
			{
				log_bff.Format(" * buffer <- [%s] \n", str_bff);
				log_msg += log_bff;

				r_data += sStr_End;
				r_data += str_bff;
			}

			log_bff.Format(" * r_data <- [%s] \n", r_data);
			log_msg += log_bff;

			// ...
			CStringArray l_rsp;
			_Get__STRING_ARRAY(r_data,sStr_End, l_rsp);

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
int CObj__DURAPORT_SERIAL::
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

		if(str_data.GetLength() < 1)
		{
			return 1;
		}
	}
	return -1;
}


//=====================================================================================
int CObj__DURAPORT_SERIAL::
_Update__SYSTEM_STATUS(const CString& r_data)
{
	int i_len = r_data.GetLength();
	if(i_len != 9)		return -1;

	char ch_s = r_data.GetAt(0);
	if(ch_s != 'S')		return -2;

	// ...
	CString ch_data;

	int i_limit = 8;
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch_ascii = r_data.GetAt(i+1);
		unsigned char ch_hexa = 0x0f & _Get__HEXA_FROM_ASCII(ch_ascii);

		if(i == 7)				// Bit : 0 ~ 3
		{
			// Bit 00 : DURAPORT Homing Completes yes/no (1=Complete, 0=Not complete)
			if(ch_hexa & 0x01)		sCH__BIT_STS__HOMING_COMPLETE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__HOMING_COMPLETE->Set__DATA(STR__OFF);

			// Bit 01 : Motor Driver ON yes/no (1=ON, 0=OFF)
			if(ch_hexa & 0x02)		sCH__BIT_STS__MOTOR_DRIVER_ON->Set__DATA(STR__ON);
			else					sCH__BIT_STS__MOTOR_DRIVER_ON->Set__DATA(STR__OFF);

			// Bit 02 : Open condition  (1=Opened, 0=Not Opened )
			if(ch_hexa & 0x04)		sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__DOOR_OPENED->Set__DATA(STR__OFF);

			// Bit 03 : Close condition (1=Closed, 0=Not Closed)		
			if(ch_hexa & 0x08)		sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__DOOR_CLOSED->Set__DATA(STR__OFF);
		}
		else if(i == 6)			// Bit : 4 ~ 7
		{
			// Bit 04 : Condition of acting (1=On acting, 0=On stop)
			if(ch_hexa & 0x01)		sCH__BIT_STS__ACTING_CONDITION->Set__DATA(STR__ON);
			else					sCH__BIT_STS__ACTING_CONDITION->Set__DATA(STR__OFF);

			// Bit 05 : Backup Data's Crash yes/no 
			// (1=Presence of not normal Data, 0=Data normal)
			if(ch_hexa & 0x02)		sCH__BIT_STS__BACKUP_DATA_CRASH->Set__DATA(STR__ON);
			else					sCH__BIT_STS__BACKUP_DATA_CRASH->Set__DATA(STR__OFF);

			// Bit 06 : Maintenance Mode condition (1=Enable, 0=Disable)
			if(ch_hexa & 0x04)		sCH__BIT_STS__MAINT_MODE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__MAINT_MODE->Set__DATA(STR__OFF);
			
			// Bit 07 : Reserve
			if(ch_hexa & 0x08)		;
		}
		else if(i == 5)			// Bit : 8 ~ 11
		{
			// Bit 08 : Reserve
			if(ch_hexa & 0x01)		;

			// Bit 09 : POD clamped (1=Clamped, 0=Not clamped)
			if(ch_hexa & 0x02)		sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__POD_CLAMPED->Set__DATA(STR__OFF);
			
			// Bit 10 : POD unclamped (1=Unclamped, 0=Not unclamped)
			if(ch_hexa & 0x04)		sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__POD_UNCLAMPED->Set__DATA(STR__OFF);
			
			// Bit 11 : POD docked  (1=Docked, 0=Not docked)
			if(ch_hexa & 0x08)		sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__POD_DOCKED->Set__DATA(STR__OFF);
		}
		else if(i == 4)			// Bit : 12 ~ 15
		{
			// Bit 12 : POD undocked  (1=Undocked, 0=Not undocked)
			if(ch_hexa & 0x01)		sCH__BIT_STS__PAD_UNDOCKED->Set__DATA(STR__ON);
			else					sCH__BIT_STS__PAD_UNDOCKED->Set__DATA(STR__OFF);
			
			// Bit 13 : Vacuum Condition (1=Vacuum, 0=Not vacuum)
			if(ch_hexa & 0x02)		sCH__BIT_STS__VACUUM_CONDITION->Set__DATA(STR__ON);
			else					sCH__BIT_STS__VACUUM_CONDITION->Set__DATA(STR__OFF);
			
			// Bit 14 : Latch Condition (1=Latch, 0=Not Latch)
			if(ch_hexa & 0x04)		sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__ON);
			else					sCH__BIT_STS__LATCH_CONDITION->Set__DATA(STR__OFF);
			
			// Bit 15 : Unlatch Condition (1=Unlatch, 0=Not Unlatch)
			if(ch_hexa & 0x08)		sCH__BIT_STS__UNLATCH_CONDITION->Set__DATA(STR__ON);
			else					sCH__BIT_STS__UNLATCH_CONDITION->Set__DATA(STR__OFF);
		}
		else if(i == 3)			// Bit : 16 ~ 19
		{
			// Bit 16 : Error occurrence condition (1=Error occurred, 0=No Error)
			if(ch_hexa & 0x01)		sCH__BIT_STS__ERROR_OCCURRENCE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__ERROR_OCCURRENCE->Set__DATA(STR__OFF);
			
			// Bit 17 ~ 19 : Reserved
		}
		else if(i == 2)			// Bit : 20 ~ 23
		{
			// Bit 20 : AMHS Mode (1=AMHS Used, 0=AMHS Not Used)
			if(ch_hexa & 0x01)		sCH__BIT_STS__AMHS_MODE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__AMHS_MODE->Set__DATA(STR__OFF);
			
			// Bit 21 : BCR usage yes/no (1=Enable, 0=Disable)
			if(ch_hexa & 0x02)		sCH__BIT_STS__BCR_USAGE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__BCR_USAGE->Set__DATA(STR__OFF);
			
			// Bit 22 : Mapping function usage yes/no (1=Enable, 0=Disable)
			if(ch_hexa & 0x04)		sCH__BIT_STS__MAPPING_USAGE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__MAPPING_USAGE->Set__DATA(STR__OFF);
			
			// Bit 23 : Auto Mode condition (1=Auto Handoff, 0=Manual Handoff)
			if(ch_hexa & 0x08)		sCH__BIT_STS__AUTO_MODE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__AUTO_MODE->Set__DATA(STR__OFF);
		}
		else if(i == 1)			// Bit : 24 ~ 27
		{
			// Bit 24 : Load/Unload ID Switch usage yes/no (1=Used, 0=Not Used)
			if(ch_hexa & 0x01)		sCH__BIT_STS__Load_Unload_SW_USAGE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__Load_Unload_SW_USAGE->Set__DATA(STR__OFF);
			
			// Bit 25 : Open Cassette usage yes/no (1=OC Used, 0=POD Used)
			if(ch_hexa & 0x02)		sCH__BIT_STS__OPEN_CASSETTE_USAGE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__OPEN_CASSETTE_USAGE->Set__DATA(STR__OFF);

			// Bit 26 : Reserve condition of Load port (1=Reserved, 0=Not Reserved)
			if(ch_hexa & 0x04)		sCH__BIT_STS__LOADPORT_RESERVE->Set__DATA(STR__ON);
			else					sCH__BIT_STS__LOADPORT_RESERVE->Set__DATA(STR__OFF);
			
			// Bit 27 : Reserved
			if(ch_hexa & 0x08)		;
		}
		else if(i == 0)			// Bit : 28 ~ 31
		{
			// Bit 28 : Placement Sensor condition (1=ON, 0=OFF)
			if(ch_hexa & 0x01)		sCH__BIT_STS__PLACEMENT_SENSOR->Set__DATA(STR__ON);
			else					sCH__BIT_STS__PLACEMENT_SENSOR->Set__DATA(STR__OFF);
			
			// Bit 29 : Presence Sensor condition (1=ON, 0=OFF)
			if(ch_hexa & 0x02)		sCH__BIT_STS__PRESENCE_SENSOR->Set__DATA(STR__ON);
			else					sCH__BIT_STS__PRESENCE_SENSOR->Set__DATA(STR__OFF);
			
			// Bit 30 : Wafer Slide Out, Protrusion Condition (1=ON, 0=OFF)
			if(ch_hexa & 0x04)		sCH__BIT_STS__WAFER_SLIDE_SENSOR->Set__DATA(STR__ON);
			else					sCH__BIT_STS__WAFER_SLIDE_SENSOR->Set__DATA(STR__OFF);
			
			// Bit 31 : Fan IO Condition (1=ON, 0=OFF), CFG_FAN_BIT OFF½Ã Ç×½Ã OFF
			if(ch_hexa & 0x08)		sCH__BIT_STS__FAN_IO_CONDITION->Set__DATA(STR__ON);
			else					sCH__BIT_STS__FAN_IO_CONDITION->Set__DATA(STR__OFF);
		}
	}

	// DOOR STATUS ...
	{
		ch_data = STR__UNKNOWN;
		
		if(sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__OPEN;
		}
		else
		{
			if(sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__ON) > 0)
				ch_data = STR__CLOSE;
		}

		sCH__MON_DOOR_STATUS->Set__DATA(ch_data);
	}
	// FOUP POS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__POD_DOCKED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__PAD_UNDOCKED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__LOAD;
		}
		else
		{
			if(sCH__BIT_STS__PAD_UNDOCKED->Check__DATA(STR__ON) > 0)
				ch_data = STR__UNLOAD;
		}

		sCH__MON_FOUP_POS_STATUS->Set__DATA(ch_data);
	}
	// FOUP STATUS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__PLACEMENT_SENSOR->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__PRESENCE_SENSOR->Check__DATA(STR__ON) > 0)
				ch_data = STR__EXIST;
		}
		else
		{
			if(sCH__BIT_STS__PRESENCE_SENSOR->Check__DATA(STR__OFF) > 0)
				ch_data = STR__NONE;
		}

		sCH__MON_FOUP_STATUS->Set__DATA(ch_data);
	}
	// CLAMP STATUS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__POD_CLAMPED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__POD_UNCLAMPED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__CLAMP;
		}
		else
		{
			if(sCH__BIT_STS__POD_UNCLAMPED->Check__DATA(STR__ON) > 0)
				ch_data = STR__UNCLAMP;
		}

		sCH__MON_CLAMP_STATUS->Set__DATA(ch_data);
	}

	return 1;
}
int CObj__DURAPORT_SERIAL::
_Update__SYSTEM_STATUS()
{
	CString ch_data;

	// DOOR STATUS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__DOOR_OPENED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__OPEN;
		}
		else
		{
			if(sCH__BIT_STS__DOOR_CLOSED->Check__DATA(STR__ON) > 0)
				ch_data = STR__CLOSE;
		}

		sCH__MON_DOOR_STATUS->Set__DATA(ch_data);
	}
	// FOUP POS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__POD_DOCKED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__PAD_UNDOCKED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__LOAD;
		}
		else
		{
			if(sCH__BIT_STS__PAD_UNDOCKED->Check__DATA(STR__ON) > 0)
				ch_data = STR__UNLOAD;
		}

		sCH__MON_FOUP_POS_STATUS->Set__DATA(ch_data);
	}
	// FOUP STATUS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__PLACEMENT_SENSOR->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__PRESENCE_SENSOR->Check__DATA(STR__ON) > 0)
				ch_data = STR__EXIST;
		}
		else
		{
			if(sCH__BIT_STS__PRESENCE_SENSOR->Check__DATA(STR__OFF) > 0)
				ch_data = STR__NONE;
		}

		sCH__MON_FOUP_STATUS->Set__DATA(ch_data);
	}
	// CLAMP STATUS ...
	{
		ch_data = STR__UNKNOWN;

		if(sCH__BIT_STS__POD_CLAMPED->Check__DATA(STR__ON) > 0)
		{
			if(sCH__BIT_STS__POD_UNCLAMPED->Check__DATA(STR__OFF) > 0)
				ch_data = STR__CLAMP;
		}
		else
		{
			if(sCH__BIT_STS__POD_UNCLAMPED->Check__DATA(STR__ON) > 0)
				ch_data = STR__UNCLAMP;
		}

		sCH__MON_CLAMP_STATUS->Set__DATA(ch_data);
	}

	return 1;
}

int CObj__DURAPORT_SERIAL::
_Update__INDICATOR_STATUS(const CString& r_data)
{
	int i_len = r_data.GetLength();
	if(i_len != 9)		return -1;

	char ch_s = r_data.GetAt(0);
	if(ch_s != 'I')		return -2;

	// ...
	CString ch_data;

	int i_limit = 8;
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch_ascii = r_data.GetAt(i+1);
		unsigned char ch_hexa = 0x0f & _Get__HEXA_FROM_ASCII(ch_ascii);

			 if(ch_hexa & 0x01)		ch_data = STR__ON;
		else if(ch_hexa & 0x02)		ch_data = STR__BLINK;
		else						ch_data = STR__OFF;

		if(i == 7)				// Bit[0 ~ 3] : LOAD
		{
			sCH__INDICATOR_STS__LOAD->Set__DATA(ch_data);
		}
		else if(i == 6)			// Bit[4 ~ 7] : UNLOAD
		{
			sCH__INDICATOR_STS__UNLOAD->Set__DATA(ch_data);
		}
		else if(i == 5)			// Bit[8 ~ 11] : AUTO
		{
			sCH__INDICATOR_STS__AUTO->Set__DATA(ch_data);
		}
		else if(i == 4)			// Bit[12 ~ 15] : MANUAL
		{
			sCH__INDICATOR_STS__MANUAL->Set__DATA(ch_data);
		}
		else if(i == 3)			// Bit[16 ~ 19] : RESERVE
		{
			sCH__INDICATOR_STS__RESERVE->Set__DATA(ch_data);
		}
		else if(i == 2)			// Bit[20 ~ 23] : BUTTON
		{
			sCH__INDICATOR_STS__BUTTON->Set__DATA(ch_data);
		}
		else if(i == 1)			// Bit[24 ~ 27] : NOT USE
		{

		}
		else if(i == 0)			// Bit[28 ~ 31] : NOT USE
		{

		}
	}

	return 1;
}
int CObj__DURAPORT_SERIAL::
_Update__LPx_MAP(const CString& r_data)
{
	int i_len = r_data.GetLength();
	if(i_len != 27)		return -1;

	char ch_s = r_data.GetAt(0);
	if(ch_s != 'M')		return -2;

	// ...
	CString ch_slot1;
	CString ch_slot2;
	CString ch_slot3;
	CString ch_slot4;

	int i_limit;
	int i;

	/*
	STR__ABSENT
	STR__PRESENT
	STR__DOUBLE
	STR__CROSSED
	STR__INVALID
	*/

	// Normal Slot : 1 ~ 8 ...
	{
		i_limit = 8;

		for(i=0; i<i_limit; i++)
		{
			char ch_ascii = r_data.GetAt(i+1);
			unsigned char ch_hexa = 0x0f & _Get__HEXA_FROM_ASCII(ch_ascii);

			if(ch_hexa & 0x01)		ch_slot1 = STR__PRESENT;
			else					ch_slot1 = STR__ABSENT;

			if(ch_hexa & 0x02)		ch_slot2 = STR__PRESENT;
			else					ch_slot2 = STR__ABSENT;

			if(ch_hexa & 0x04)		ch_slot3 = STR__PRESENT;
			else					ch_slot3 = STR__ABSENT;

			if(ch_hexa & 0x08)		ch_slot4 = STR__PRESENT;
			else					ch_slot4 = STR__ABSENT;

			int s_offset = (7-i) * 4;

			sCH__RES_MAP_SLOT[s_offset + 0]->Set__DATA(ch_slot1);
			sCH__RES_MAP_SLOT[s_offset + 1]->Set__DATA(ch_slot2);
			sCH__RES_MAP_SLOT[s_offset + 2]->Set__DATA(ch_slot3);
			sCH__RES_MAP_SLOT[s_offset + 3]->Set__DATA(ch_slot4);
		}
	}
	// Cross Slot : 10 ~ 17 ...
	{
		i_limit = 8;

		for(i=0; i<i_limit; i++)
		{
			char ch_ascii = r_data.GetAt(i+10);
			unsigned char ch_hexa = 0x0f & _Get__HEXA_FROM_ASCII(ch_ascii);

			if(ch_hexa & 0x01)		ch_slot1 = STR__EXIST;
			else					ch_slot1 = STR__NONE;

			if(ch_hexa & 0x02)		ch_slot2 = STR__EXIST;
			else					ch_slot2 = STR__NONE;

			if(ch_hexa & 0x04)		ch_slot3 = STR__EXIST;
			else					ch_slot3 = STR__NONE;

			if(ch_hexa & 0x08)		ch_slot4 = STR__EXIST;
			else					ch_slot4 = STR__NONE;

			int s_offset = (7-i) * 4;

			sCH__RES_MAP_CROSS_SLOT[s_offset + 0]->Set__DATA(ch_slot1);
			sCH__RES_MAP_CROSS_SLOT[s_offset + 1]->Set__DATA(ch_slot2);
			sCH__RES_MAP_CROSS_SLOT[s_offset + 2]->Set__DATA(ch_slot3);
			sCH__RES_MAP_CROSS_SLOT[s_offset + 3]->Set__DATA(ch_slot4);
		}
	}
	// Double Slot : 19 ~ 26 ...
	{
		i_limit = 8;

		for(i=0; i<i_limit; i++)
		{
			char ch_ascii = r_data.GetAt(i+19);
			unsigned char ch_hexa = 0x0f & _Get__HEXA_FROM_ASCII(ch_ascii);

			if(ch_hexa & 0x01)		ch_slot1 = STR__EXIST;
			else					ch_slot1 = STR__NONE;

			if(ch_hexa & 0x02)		ch_slot2 = STR__EXIST;
			else					ch_slot2 = STR__NONE;

			if(ch_hexa & 0x04)		ch_slot3 = STR__EXIST;
			else					ch_slot3 = STR__NONE;

			if(ch_hexa & 0x08)		ch_slot4 = STR__EXIST;
			else					ch_slot4 = STR__NONE;

			int s_offset = (7-i) * 4;

			sCH__RES_MAP_DOUBLE_SLOT[s_offset + 0]->Set__DATA(ch_slot1);
			sCH__RES_MAP_DOUBLE_SLOT[s_offset + 1]->Set__DATA(ch_slot2);
			sCH__RES_MAP_DOUBLE_SLOT[s_offset + 2]->Set__DATA(ch_slot3);
			sCH__RES_MAP_DOUBLE_SLOT[s_offset + 3]->Set__DATA(ch_slot4);
		}
	}

	return 1;
}
int CObj__DURAPORT_SERIAL::
_Update__LPx_INIT()
{
	CString ch_data;

	int i_limit = LPx_SLOT_MAX;
	int i;

	for(i=0; i<i_limit; i++)
	{
		ch_data = STR__UNKNOWN;

		sCH__RES_MAP_SLOT[i]->Set__DATA(ch_data);
		sCH__RES_MAP_CROSS_SLOT[i]->Set__DATA(ch_data);
		sCH__RES_MAP_DOUBLE_SLOT[i]->Set__DATA(ch_data);
	}
	return 1;
}

int CObj__DURAPORT_SERIAL::
_Get__HEXA_FROM_ASCII(const unsigned char ch_ascii)
{
	switch(ch_ascii)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return (ch_ascii - '0');

		case 'a':
		case 'A':
			return 10;

		case 'b':
		case 'B':
			return 11;

		case 'c':
		case 'C':
			return 12;

		case 'd':
		case 'D':
			return 13;

		case 'e':
		case 'E':
			return 14;

		case 'f':
		case 'F':
			return 15;
	}

	return 0;
}
