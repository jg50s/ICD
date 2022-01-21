#include "StdAfx.h"
#include "CObj__TYPE_BROOKS.h"
#include "CObj__TYPE_BROOKS__DEF.h"

#include "cifuser.h"
#include "rcs_user.h"
#include "dnm_user.h"


//--------------------------------------------------------------------------------
CObj__TYPE_BROOKS::CObj__TYPE_BROOKS()
{
	InitializeCriticalSection(&mLOCK_DNET);

	iDNet_BoardNumber = -1;
}
CObj__TYPE_BROOKS::~CObj__TYPE_BROOKS()
{

	DeleteCriticalSection(&mLOCK_DNET);
}

//--------------------------------------------------------------------------------
int CObj__TYPE_BROOKS::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	// ...
	{
		sObject_Name = obj;
	}

	// ...
	{
		ADD__CTRL_VAR(sMODE__LINK_IO_SET_OFF, "LINK_IO.SET_OFF");
		ADD__CTRL_VAR(sMODE__LINK_IO_SET_ON,  "LINK_IO.SET_ON" );

		// 
		ADD__CTRL_VAR(sMODE__FLOAT_TO_HEXA, "FLOAT_TO_HEXA");
		ADD__CTRL_VAR(sMODE__HEXA_TO_FLOAT, "HEXA_TO_FLOAT");

		ADD__CTRL_VAR(sMODE__NODE_OUT_BYTE_UPLOAD, "NODE.OUT.BYTE.UPLOAD");
		ADD__CTRL_VAR(sMODE__NODE_IN_BYTE_UPLOAD,  "NODE.IN.BYTE.UPLOAD" );
	}
	return 1;
}
int CObj__TYPE_BROOKS::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__OFF_ON				"OFF  ON"


int CObj__TYPE_BROOKS::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CString str_name;

	// ...
	{
		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "APP.DO.DNET_HEARTBEAT";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);
		LINK__VAR_DIGITAL_CTRL(dCH__DO_DNET_HEARTBEAT, str_name);
	}

	// Config ...
	{
		str_name = "CFG.DNET.HEARTBEAT.PERIOD";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DNET_HEARTBEAT_PERIOD, str_name);

		str_name = "DNET.HEARTBEAT.TIME.COUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_HEARTBEAT_TIME_COUNT, str_name);
	}

	// ...
	{
		str_name = "DNET.INFO.MASTER_BOARD_NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_INFO__MASTER_BOARD_NAME, str_name);

		str_name = "DNET.INFO.MASTER_BOARD_ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_INFO__MASTER_BOARD_ID, str_name);

		str_name = "DNET.INFO.BAUD_RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_INFO__BAUD_RATE, str_name);

		//
		{
			iSLAVE_COUNT = 0;

			str_name = "DNET.INFO.SLAVE_COUNT";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__DNET_INFO__SLAVE_COUNT, str_name);

			str_name = "DNET.CFG.SLAVE_COUNT";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_COUNT, str_name);
		}

		// ...
		{
			str_name = "di.Comm.Sts";
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(diCH__COMM_STS, str_name);

			str_name = "APP.DRV.LOG.ENABLE";
			STD__ADD_DIGITAL(str_name, "NO YES");
			LINK__VAR_DIGITAL_CTRL(dCH__APP_DRV_LOG_ENABLE, str_name);
		}

		for(int i=0; i<CFG__SLAVE_SIZE; i++)
		{
			int id = i + 1;

			// INFO ...
			{
				str_name.Format("DNET.INFO.SLAVE.%1d.MACID", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_INFO__SLAVE_X__MACID[i], str_name);

				str_name.Format("DNET.INFO.SLAVE.%1d.NAME", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_INFO__SLAVE_X__NAME[i], str_name);

				str_name.Format("DNET.INFO.SLAVE.%1d.IN_SIZE", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_INFO__SLAVE_X__IN_SIZE[i], str_name);

				str_name.Format("DNET.INFO.SLAVE.%1d.OUT_SIZE", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_INFO__SLAVE_X__OUT_SIZE[i], str_name);
			}

			// CFG ...
			{
				str_name.Format("DNET.CFG.SLAVE.%1d.MACID", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__MACID[i], str_name);

				str_name.Format("DNET.CFG.SLAVE.%1d.NAME", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__NAME[i], str_name);

				//
				str_name.Format("DNET.CFG.SLAVE.%1d.IN_OFFSET", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__IN_OFFSET[i], str_name);

				str_name.Format("DNET.CFG.SLAVE.%1d.IN_SIZE", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__IN_SIZE[i], str_name);

				//
				str_name.Format("DNET.CFG.SLAVE.%1d.OUT_OFFSET", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__OUT_OFFSET[i], str_name);

				str_name.Format("DNET.CFG.SLAVE.%1d.OUT_SIZE", id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__DNET_CFG__SLAVE_X__OUT_SIZE[i], str_name);
			}
		}
	}

	// ...
	{
		int i;

		str_name = "DNET.INFO.OUT.BYTE.SIZE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_INFO__OUT_BYTE_SIZE, str_name);

		str_name = "DNET.INFO.OUT.BYTE.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__DNET_INFO__OUT_BYTE_CHECK_ACTIVE, str_name);

		for(i=0; i<CFG__DNET_OUT_BYTE_LIMIT; i++)
		{
			str_name.Format("DNET.INFO.OUT.BYTE.DATA.%1d", i);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__DNET_INFO__OUT_BYTE_DATA_X[i], str_name);
		}

		//
		str_name = "DNET.INFO.IN.BYTE.SIZE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DNET_INFO__IN_BYTE_SIZE, str_name);

		str_name = "DNET.INFO.IN.BYTE.CHECK.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__DNET_INFO__IN_BYTE_CHECK_ACTIVE, str_name);

		for(i=0; i<CFG__DNET_IN_BYTE_LIMIT; i++)
		{
			str_name.Format("DNET.INFO.IN.BYTE.DATA.%1d", i);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__DNET_INFO__IN_BYTE_DATA_X[i], str_name);
		}
	}

	// ...
	{
		str_name = "FLOAT_TO_HEXA.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__FLOAT_TO_HEXA__VALUE, str_name);

		str_name = "FLOAT_TO_HEXA.RESULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__FLOAT_TO_HEXA__RESULT, str_name);

		//
		str_name = "HEXA_TO_FLOAT.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HEXA_TO_FLOAT__VALUE, str_name);

		str_name = "HEXA_TO_FLOAT.RESULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HEXA_TO_FLOAT__RESULT, str_name);
	}

	// ...
	{
		str_name = "TEST.GAUGE.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_GAUGE_HEXA, str_name);

		str_name = "TEST.GAUGE.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_GAUGE_VALUE, str_name);
	}
	// ...
	{
		str_name = "TEST.FFFF.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_FFFF_HEXA, str_name);

		str_name = "TEST.FFFF.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TEST_FFFF_VALUE, str_name);
	}

	// ...
	{
		str_name = "CFG.LINK_IO.WAITING.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LINK_IO_WAITING_SEC, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__MONITOR);
	}
	return 1;
}
int CObj__TYPE_BROOKS::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString obj_title;
	obj_title.Format("%s - ",sObject_Name);

	int alm_id;
	CString alm_title;
	CString alm_msg;
	CStringArray l_act;

	// ...
	{
		alm_id = ALID__OFFLINE;

		alm_title  = obj_title;
		alm_title += "Offline !";

		alm_msg = "Check the line & parameter.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alm_id, alm_title, alm_msg, l_act);
	}

	return 1;
}

int CObj__TYPE_BROOKS::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;

	// ...
	{

	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__TYPE_BROOKS::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// SIM.MODE ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// LINK : IO ...
	{
		CString def_name;
		CString def_data;

		CString ch_name;
		CString obj_name;
		CString var_name;

		int i_limit;
		int i;

		def_name = "LINK.IO_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		i_limit = atoi(def_data);
		if(i_limit > CFG__LINK_IO_SIZE)		i_limit = CFG__LINK_IO_SIZE;

		iSIZE__LINK_IO = i_limit;

		for(i=0; i<i_limit; i++)
		{
			def_name.Format("LINK.IO_CHANNEL.%1d", i+1);

			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DNET_LINK_IO[i], obj_name,var_name);
		}
	}
	return 1;
}
int CObj__TYPE_BROOKS::__INITIALIZE__IO(p_io_para)
{
	// ...
	{
		CString para_name;
		CString para_data;

		int i_limit;
		int i;

		para_name = "BOARD.ID";
		p_io_para->Get__PARAMETER_DATA(para_name, para_data);
		int bd_ud = atoi(para_data);
		mDNet_Mng.Set__BOARD_ID(bd_ud);

		para_name = "NODE.SIZE";
		p_io_para->Get__PARAMETER_DATA(para_name, para_data);
		i_limit = atoi(para_data);
		if(i_limit > CFG__SLAVE_SIZE)		i_limit = CFG__SLAVE_SIZE;

		para_data.Format("%1d", i_limit);
		sCH__DNET_CFG__SLAVE_COUNT->Set__DATA(para_data);

		for(i=0; i<i_limit; i++)
		{
			int id = i + 1;

			para_name.Format("NODE.%1d.MACID", id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__MACID[i]->Set__DATA(para_data);

			para_name.Format("NODE.%1d.NAME",  id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__NAME[i]->Set__DATA(para_data);

			//
			para_name.Format("NODE.%1d.IN_OFFSET", id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__IN_OFFSET[i]->Set__DATA(para_data);

			para_name.Format("NODE.%1d.IN_BYTE",  id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__IN_SIZE[i]->Set__DATA(para_data);

			//
			para_name.Format("NODE.%1d.OUT_OFFSET", id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__OUT_OFFSET[i]->Set__DATA(para_data);

			para_name.Format("NODE.%1d.OUT_BYTE", id);
			p_io_para->Get__PARAMETER_DATA(para_name, para_data);
			sCH__DNET_CFG__SLAVE_X__OUT_SIZE[i]->Set__DATA(para_data);
		}
	}

	// ...
	{
		CString ch_data;
		sCH__DNET_CFG__SLAVE_COUNT->Get__DATA(ch_data);

		int i_limit = atoi(ch_data);
		int i;

		for(i=0; i<i_limit; i++)
		{
			CInfo__DNet_Node node_info;

			sCH__DNET_CFG__SLAVE_X__MACID[i]->Get__DATA(ch_data);
			node_info.iMAC_ID = atoi(ch_data);

			sCH__DNET_CFG__SLAVE_X__NAME[i]->Get__DATA(ch_data);
			node_info.sNAME = ch_data;

			sCH__DNET_CFG__SLAVE_X__IN_OFFSET[i]->Get__DATA(ch_data);
			node_info.iIN_OFFSET = atoi(ch_data);

			sCH__DNET_CFG__SLAVE_X__IN_SIZE[i]->Get__DATA(ch_data);
			node_info.iIN_SIZE = atoi(ch_data);

			sCH__DNET_CFG__SLAVE_X__OUT_OFFSET[i]->Get__DATA(ch_data);
			node_info.iOUT_OFFSET = atoi(ch_data);

			sCH__DNET_CFG__SLAVE_X__OUT_SIZE[i]->Get__DATA(ch_data);
			node_info.iOUT_SIZE = atoi(ch_data);

			mCtrl__DNet_Node.Load__Node_Info(&node_info);
		}

		mCtrl__DNet_Node.Load__Complete();

		// ...
		{
			CString str_node_info = mCtrl__DNet_Node.Get__All_Node_Info();

			xI__APP_LOG_CTRL->WRITE__LOG(str_node_info);
			xI__DRV_LOG_CTRL->WRITE__LOG(str_node_info);
		}
	}

	// ...
	SCX__SEQ_INFO x_seq_info;
	int sim_mode = x_seq_info->Is__SIMULATION_MODE();

	// ...
	printf("%s : Initial Starting ... \n", sObject_Name);

	int r_ret;

	if(sim_mode < 0)		r_ret = _Init__DNET_MASTER_BY_USER_CFG();
	else					r_ret = -1;

	if(r_ret > 0)
	{
		usInputOffset  = mCtrl__DNet_Node.Get__TOTAL_IN_BYTE();
		usOutputOffset = mCtrl__DNet_Node.Get__TOTAL_OUT_BYTE();

		diCH__COMM_STS->Set__DATA("ONLINE");

		printf("%s : Initial Completed ... \n", sObject_Name);
	}
	else
	{
		usInputOffset  = 0;
		usOutputOffset = 0;

		diCH__COMM_STS->Set__DATA("OFFLINE");

		printf("%s : Initial Aborted ... \n", sObject_Name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__TYPE_BROOKS
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;
	int flag = -1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		Write__APP_LOG(msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__LINK_IO_SET_OFF)				flag = Call__LINK_IO_SET_OFF(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LINK_IO_SET_ON)				flag = Call__LINK_IO_SET_ON(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__FLOAT_TO_HEXA)				flag = Call__FLOAT_TO_HEXA(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HEXA_TO_FLOAT)				flag = Call__HEXA_TO_FLOAT(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__NODE_OUT_BYTE_UPLOAD)			flag = Call__NODE_OUT_BYTE_UPLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__NODE_IN_BYTE_UPLOAD)			flag = Call__NODE_IN_BYTE_UPLOAD(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		Write__APP_LOG(msg);
	}
	return flag;
}

int CObj__TYPE_BROOKS::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__MONITOR:
			Mon__MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__TYPE_BROOKS
::__CLOSE__OBJECT()
{
	EnterCriticalSection(&mLOCK_DNET);

	if(iDNet_BoardNumber >= 0)
	{
		DevExitBoard(iDNet_BoardNumber);
		DevCloseDriver(0);

		iDNet_BoardNumber = -1;
	}

	LeaveCriticalSection(&mLOCK_DNET);
	return 1;
}
