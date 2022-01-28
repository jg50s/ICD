#include "StdAfx.h"
#include "CObj__UPPER_VAC_ROBOT.h"


//-------------------------------------------------------------------------
CObj__UPPER_VAC_ROBOT::CObj__UPPER_VAC_ROBOT()
{

}
CObj__UPPER_VAC_ROBOT::~CObj__UPPER_VAC_ROBOT()
{

}

//-------------------------------------------------------------------------
int CObj__UPPER_VAC_ROBOT::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__SWAP_LBx, "SWAP_LBx");
	}
	return 1;
}
int CObj__UPPER_VAC_ROBOT::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__PARA_ARM							\
"A  B  AB"

#define  APP_DSP__PARA_MODULE						\
"LBA  LBB  LBC  LBD									\
 LLL  LLU											\
 PM1   PM2   PM3   PM4   PM5   PM6"

#define  APP_DSP__PARA_SLOT							\
" 1  2  3  4  5  6  7  8  9 10						\
 11 12 13 14 15 16 17 18 19 20						\
 21 22 23 24 25 26 27 28 29 30"


int CObj__UPPER_VAC_ROBOT::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;

	// ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsc_item_list);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name,dsc_item_list,"");
		LINK__VAR_DIGITAL_CTRL(xCH__OBJ_STATUS,str_name);

		//.....
		str_name = "PARA.MODULE";
		STD__ADD_DIGITAL(str_name,APP_DSP__PARA_MODULE);
		LINK__VAR_DIGITAL_CTRL(xCH__PARA_MODULE,str_name);

		//
		str_name = "PARA.PICK.ARM";
		STD__ADD_DIGITAL(str_name,APP_DSP__PARA_ARM);
		LINK__VAR_DIGITAL_CTRL(xCH__PARA_PICK_ARM,str_name);

		str_name = "PARA.PICK.SLOT";
		STD__ADD_DIGITAL(str_name,APP_DSP__PARA_SLOT);
		LINK__VAR_DIGITAL_CTRL(xCH__PARA_PICK_SLOT,str_name);

		//
		str_name = "PARA.PLACE.ARM";
		STD__ADD_DIGITAL(str_name,APP_DSP__PARA_ARM);
		LINK__VAR_DIGITAL_CTRL(xCH__PARA_PLACE_ARM,str_name);

		str_name = "PARA.PLACE.SLOT";
		STD__ADD_DIGITAL(str_name,APP_DSP__PARA_SLOT);
		LINK__VAR_DIGITAL_CTRL(xCH__PARA_PLACE_SLOT,str_name);
	}
	return 1;
}

int CObj__UPPER_VAC_ROBOT::__DEFINE__ALARM(p_alarm)
{

	return 1;
}

int CObj__UPPER_VAC_ROBOT::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__UPPER_VAC_ROBOT::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// VAC_ROBOT
	{
		def_name = "OBJ__ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		pVAC_ROBOT__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "OBJ.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_ROBOT__OBJ_STATUS, def_data,str_name);

		//
		str_name = "PARA.ARM";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_ROBOT__PARA_ARM, def_data,str_name);

		str_name = "PARA.MODULE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_ROBOT__PARA_MODULE, def_data,str_name);

		str_name = "PARA.SLOT";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__VAC_ROBOT__PARA_SLOT, def_data,str_name);
	}

	// LLx 
	{
		def_name = "DATA.LLx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iSIZE_LLx = atoi(def_data);
		if(iSIZE_LLx > CFG__LLx_SIZE)		iSIZE_LLx = CFG__LLx_SIZE;

		for(int i=0; i<iSIZE_LLx; i++)
		{
			def_name.Format("OBJ__LL%1d", i+1);
			p_variable->Get__DEF_CONST_DATA(def_name,def_data);

			pLLx__OBJ_CTRL[i] = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

			//
			str_name = "OBJ.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__LLx__OBJ_STATUS[i], def_data,str_name);

			str_name = "PARA.PREMATERIAL.SLOT";	
			LINK__EXT_VAR_DIGITAL_CTRL(xEXT_CH__LLx__PREMATERIAL_SLOT[i], def_data,str_name);
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

	xCH__OBJ_STATUS->Set__DATA("STANDBY");
	return 1;
}

//-------------------------------------------------------------------------
int CObj__UPPER_VAC_ROBOT::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString para_module;
	CString para_pick_arm;
	CString para_pick_slot;
	CString para_place_arm;
	CString para_place_slot;

	xCH__PARA_MODULE->Get__DATA(para_module);
	xCH__PARA_PICK_ARM->Get__DATA(para_pick_arm);
	xCH__PARA_PICK_SLOT->Get__DATA(para_pick_slot);
	xCH__PARA_PLACE_ARM->Get__DATA(para_place_arm);
	xCH__PARA_PLACE_SLOT->Get__DATA(para_place_slot);

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s] (%s) (%s,%s) (%s,%s)",
						mode,
						para_module,
						para_pick_arm,
						para_pick_slot,
						para_place_arm,
						para_place_slot);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__SWAP_LBx)		flag = Call__SWAP_LBx(p_variable);

		else									
		{

		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	xCH__OBJ_STATUS->Set__DATA("STANDBY");
	return flag;
}
int CObj__UPPER_VAC_ROBOT::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
