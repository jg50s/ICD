#include "StdAfx.h"
#include "CObj__TMC_EX.h"
#include "CObj__TMC_EX__DEF.h"
#include "CObj__TMC_EX__ALID.h"


//-------------------------------------------------------------------------
CObj__TMC_EX::CObj__TMC_EX()
{

}
CObj__TMC_EX::~CObj__TMC_EX()
{

}

//-------------------------------------------------------------------------
int CObj__TMC_EX::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// LBA -----
	{
		ADD__CTRL_VAR(sMODE__LBA_SV_CLOSE, "LBA_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBA_SV_OPEN,  "LBA_SV_OPEN");

		ADD__CTRL_VAR(sMODE__LBA_DV_CLOSE, "LBA_DV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBA_DV_OPEN,  "LBA_DV_OPEN");
	}
	// LBB -----
	{
		ADD__CTRL_VAR(sMODE__LBB_SV_CLOSE, "LBB_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBB_SV_OPEN,  "LBB_SV_OPEN");

		ADD__CTRL_VAR(sMODE__LBB_DV_CLOSE, "LBB_DV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBB_DV_OPEN,  "LBB_DV_OPEN");
	}
	// LBC -----
	{
		ADD__CTRL_VAR(sMODE__LBC_SV_CLOSE, "LBC_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBC_SV_OPEN,  "LBC_SV_OPEN");

		ADD__CTRL_VAR(sMODE__LBC_DV_CLOSE, "LBC_DV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBC_DV_OPEN,  "LBC_DV_OPEN");
	}
	// LBD -----
	{
		ADD__CTRL_VAR(sMODE__LBD_SV_CLOSE, "LBD_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBD_SV_OPEN,  "LBD_SV_OPEN");

		ADD__CTRL_VAR(sMODE__LBD_DV_CLOSE, "LBD_DV_CLOSE");
		ADD__CTRL_VAR(sMODE__LBD_DV_OPEN,  "LBD_DV_OPEN");
	}

	// PMC -----
	{
		ADD__CTRL_VAR(sMODE__CHECK_PMC_SV_ALL_CLOSE, "CHECK_PMC_SV_ALL_CLOSE");

		ADD__CTRL_VAR(sMODE__PMC_SV_CLOSE,      "PMC_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__PMC_INIT_SV_CLOSE, "PMC_INIT_SV_CLOSE");
		ADD__CTRL_VAR(sMODE__PMC_ALL_SV_CLOSE,  "PMC_ALL_SV_CLOSE");

		ADD__CTRL_VAR(sMODE__PMC_SV_OPEN,           "PMC_SV_OPEN");
		ADD__CTRL_VAR(sMODE__PMC_SV_TRANSFER_OPEN,  "PMC_SV_TRANSFER_OPEN");
		ADD__CTRL_VAR(sMODE__PMC_SV_TRANSFER_CLOSE, "PMC_SV_TRANSFER_CLOSE");
	}
	return 1;
}
int CObj__TMC_EX::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define APP_DSP__CLOSE_OPEN						\
	"UNKNOWN  CLOSE  OPEN"


int CObj__TMC_EX::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OTR.OUT.MON.OBJ.STATUS";
		STD__ADD_STRING_WITH_COMMENT(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS,str_name);

		str_name = "OTR.IN.PARA.aPMC.ID";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"id",0,1,CFG_PMx__SIZE,"");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PMC_ID, str_name);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
	l_act.RemoveAll();								\
	l_act.Add("RETRY");								\
	l_act.Add("ABORT");


int CObj__TMC_EX::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__TMC__TRANSFER_PRESSURE_ERROR;

		alarm_title  = title;
		alarm_title += "TMC_CHM & PMC's Transfer Pressure Error.";

		alarm_msg = "Please, Check TMC_CHM & PMC's Pressure !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TMC__NOT_ATM_ERROR;

		alarm_title  = title;
		alarm_title += "Pressure is not ATM.";

		alarm_msg = "Please, Check module pressure !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PMC_SHUTTER__NOT_OPEN;

		alarm_title  = title;
		alarm_title += "PMC Shutter is not open !";

		alarm_msg = "Please, Check PMC's shutter status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PMC_LIFT_PIN_STATUS__NOT_DOWN;

		alarm_title  = title;
		alarm_title += "PMC lift-pin status is not down !";

		alarm_msg = "Please, Check PMC's lift-pin status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMC_EX::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString obj_name;
	CString str_name;
	int i;

	// PM SIZE ...
	{
		def_name = "PM_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		m_nPM_LIMIT = atoi(def_data);
		if(m_nPM_LIMIT <= 0)
		{
			m_nPM_LIMIT = CFG_PMx__SIZE;
		}
	}

	// DB OBJ ...
	{
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		str_name = "CFG.TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_TRANSFER_MODE, def_data,str_name);

		str_name = "CFG.REF.ATM.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_ATM_PRESSURE, def_data,str_name);

		str_name = "CFG.REF.VAC.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_VAC_PRESSURE, def_data,str_name);
	}

	// TMC CHM ...
	{
		def_name = "OBJ__TMC_CHM";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pTMC_CHM__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		str_name = "OTR.OUT.MON.OBJ.STATUS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__TMC_CHM__OBJ_STATUS, def_data,str_name);

		str_name = "OTR.OUT.MON.aPRESSURE.TORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__TMC_CHM__PRESSURE_TORR, def_data,str_name);
	}

	// LLx OBJ ...
	{
		def_name = "LLx.MULTI_DOOR_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_DOOR_VALVE = true;
		else											bActive__LLx_MULTI_DOOR_VALVE = false;

		def_name = "LLx.MULTI_SLOT_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_SLOT_VALVE = true;
		else											bActive__LLx_MULTI_SLOT_VALVE = false;

		if((bActive__LLx_MULTI_DOOR_VALVE) || (bActive__LLx_MULTI_SLOT_VALVE))
		{
			def_name = "LLx.SLOT_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			iLLx_SLOT_SIZE = atoi(def_data);
			if(iLLx_SLOT_SIZE > _LLx_SLOT__SIZE)		iLLx_SLOT_SIZE = _LLx_SLOT__SIZE;
		}
		else
		{
			iLLx_SLOT_SIZE = 1;
		}

		//
		def_name = "LL_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		iCFG__LLx_SIZE = atoi(def_data);
		if(iCFG__LLx_SIZE > CFG_LLx__SIZE)		iCFG__LLx_SIZE = CFG_LLx__SIZE;

		for(i=0; i<iCFG__LLx_SIZE; i++)
		{
			def_name.Format("OBJ__LLx.%1d", i+1);
			p_variable->Get__DEF_CONST_DATA(def_name, obj_name);

			pLLx__OBJ_CTRL[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			str_name = "OTR.OUT.MON.OBJ.STATUS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx__OBJ_STATUS[i], obj_name,str_name);

			str_name = "OTR.OUT.MON.aPRESSURE.TORR";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__LLx__PRESSURE_TORR[i], obj_name,str_name);

			//
			if(bActive__LLx_MULTI_SLOT_VALVE)
			{
				for(int k=0; k<iLLx_SLOT_SIZE; k++)
				{
					str_name.Format("OTR.OUT.MON.dSLIT.VALVE.STATUS.%1d", k+1);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx__SLIT_VLV_STATUS_XX[i][k], obj_name,str_name);
				}
			}
			else
			{
				str_name = "OTR.OUT.MON.dSLIT.VALVE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx__SLIT_VLV_STATUS_A[i], obj_name,str_name);
			}
		}
	}

	// PMx OBJ ...
	{
		def_name = "OBJ__PMx";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		pPMx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		str_name = "OTR.IN.PARA.aPMC.ID";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PMx__PARA_PMC_ID, def_data,str_name);

		for(i=0;i<m_nPM_LIMIT;i++)
		{
			str_name.Format("OTR.OUT.MON.aPM%1d.PRESSURE.TORR",i+1);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PMx__PRESSURE_TORR[i], def_data,str_name);

			str_name.Format("MODULE.LINK.sPM%1d.SHUTTER.STS",i+1);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMx__SHUTTER_STATUS[i], def_data,str_name);

			str_name.Format("MODULE.LINK.sPM%1d.LIFT.PIN.STS",i+1);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMx__LIFT_PIN_STATUS[i], def_data,str_name);
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMC_EX::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		int limit = l_para.GetSize();

		for(int i=0; i<limit; i++)
		{
			CString para_data = l_para[i];

			switch(i)
			{
				case 0:		
					aCH__PARA_PMC_ID->Set__DATA(para_data);
					break;
			}	
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg.Format("Start  [%s] ... Called By %s \n", 
						mode,
						p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		log_bff.Format(" * %s <- %.0f \n", 
			           aCH__PARA_PMC_ID->Get__VARIABLE_NAME(),
					   aCH__PARA_PMC_ID->Get__VALUE());
		log_msg += log_bff;

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		// LLx -----
			 IF__CTRL_MODE(sMODE__LBA_SV_CLOSE)			flag = Call__LLx_SV_CLOSE(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__LBB_SV_CLOSE)			flag = Call__LLx_SV_CLOSE(p_variable,p_alarm, 2);
		ELSE_IF__CTRL_MODE(sMODE__LBC_SV_CLOSE)			flag = Call__LLx_SV_CLOSE(p_variable,p_alarm, 3);
		ELSE_IF__CTRL_MODE(sMODE__LBD_SV_CLOSE)			flag = Call__LLx_SV_CLOSE(p_variable,p_alarm, 4);

		ELSE_IF__CTRL_MODE(sMODE__LBA_SV_OPEN)			flag = Call__LLx_SV_OPEN(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__LBB_SV_OPEN)			flag = Call__LLx_SV_OPEN(p_variable,p_alarm, 2);
		ELSE_IF__CTRL_MODE(sMODE__LBC_SV_OPEN)			flag = Call__LLx_SV_OPEN(p_variable,p_alarm, 3);
		ELSE_IF__CTRL_MODE(sMODE__LBD_SV_OPEN)			flag = Call__LLx_SV_OPEN(p_variable,p_alarm, 4);

		ELSE_IF__CTRL_MODE(sMODE__LBA_DV_CLOSE)			flag = Call__LLx_DV_CLOSE(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__LBB_DV_CLOSE)			flag = Call__LLx_DV_CLOSE(p_variable,p_alarm, 2);
		ELSE_IF__CTRL_MODE(sMODE__LBC_DV_CLOSE)			flag = Call__LLx_DV_CLOSE(p_variable,p_alarm, 3);
		ELSE_IF__CTRL_MODE(sMODE__LBD_DV_CLOSE)			flag = Call__LLx_DV_CLOSE(p_variable,p_alarm, 4);

		ELSE_IF__CTRL_MODE(sMODE__LBA_DV_OPEN)			flag = Call__LLx_DV_OPEN(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__LBB_DV_OPEN)			flag = Call__LLx_DV_OPEN(p_variable,p_alarm, 2);
		ELSE_IF__CTRL_MODE(sMODE__LBC_DV_OPEN)			flag = Call__LLx_DV_OPEN(p_variable,p_alarm, 3);
		ELSE_IF__CTRL_MODE(sMODE__LBD_DV_OPEN)			flag = Call__LLx_DV_OPEN(p_variable,p_alarm, 4);

		// PMC -----
		ELSE_IF__CTRL_MODE(sMODE__CHECK_PMC_SV_ALL_CLOSE)	
		{
			flag = Call__CHECK_PMC_SV_ALL_CLOSE(p_variable,p_alarm);
		}

		ELSE_IF__CTRL_MODE(sMODE__PMC_SV_CLOSE)				flag = Call__PMC_SV_CLOSE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PMC_INIT_SV_CLOSE)		flag = Call__PMC_INIT_SV_CLOSE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PMC_ALL_SV_CLOSE)			flag = Call__PMC_ALL_SV_CLOSE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PMC_SV_OPEN)				flag = Call__PMC_SV_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PMC_SV_TRANSFER_OPEN)		flag = Call__PMC_SV_TRANSFER_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PMC_SV_TRANSFER_CLOSE)	flag = Call__PMC_SV_TRANSFER_CLOSE(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s] [Flag : %1d]",mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}
int CObj__TMC_EX::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
