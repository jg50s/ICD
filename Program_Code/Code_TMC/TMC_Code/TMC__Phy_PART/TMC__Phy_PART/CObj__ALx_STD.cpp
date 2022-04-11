#include "StdAfx.h"
#include "CObj__ALx_STD.h"
#include "CObj__ALx_STD__DEF.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------
CObj__ALx_STD::CObj__ALx_STD()
{

}
CObj__ALx_STD::~CObj__ALx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__ALIGN, "ALIGN");
	}
	return 1;
}
int CObj__ALx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__ALx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString dsc_item_list;
	int i;

	// ...
	{
		str_name = "PARA.SLOT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slot", 0, 1, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SLOT, str_name);
	}

	// ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

		for(i=0;i<CFG_ALx__SLOT_MAX;i++)
		{
			// Slot Status 
			str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",i+1);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsc_item_list,"");
			LINK__VAR_DIGITAL_CTRL(dCH__SLOT_STATUS[i], str_name);

			// Slot Title
			str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name, "");
			LINK__VAR_STRING_CTRL(sCH__SLOT_TITLE[i], str_name);
		}

		// Slot Title
		str_name.Format("INR.sMSG");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MSG, str_name);
	}

	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");


int CObj__ALx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__ALx_STD::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	int al_id = -1;

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

	// LLx ...
	{
		def_name = "LLx.MULTI_DOOR_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_DOOR_VALVE = true;
		else											bActive__LLx_MULTI_DOOR_VALVE = false;

		if(bActive__LLx_MULTI_DOOR_VALVE)
		{
			def_name = "LLx.SLOT_SIZE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

			iLLx_SLOT_SIZE = atoi(def_data);
			if(iLLx_SLOT_SIZE > CFG_LLx__SLOT_SIZE)		iLLx_SLOT_SIZE = CFG_LLx__SLOT_SIZE;
		}
		else
		{
			iLLx_SLOT_SIZE = 1;
		}
	}

	// DB_CFG ...
	{
		def_name = "OBJ__DB";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		// ...
		{
			var_name = "MAINT.TARGET.LLx.NAME";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAINT_TARGT_LLx_NAME, def_data,var_name);

			var_name = "MAINT.TARGET.LLx.SLOT";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAINT_TARGT_LLx_SLOT, def_data,var_name);

			//
			var_name = "MODULE.LINK.sTARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MODULE_LINK_TARGT_LLx_NAME, def_data,var_name);

			var_name = "MODULE.LINK.sTARGET.LLx.SLOT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MODULE_LINK_TARGT_LLx_SLOT, def_data,var_name);

			//
			var_name = "CUR.AL1.TARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_TARGET_LLx_NAME, def_data,var_name);

			var_name = "CUR.AL1.TARGET.LLx.SLOT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_TARGET_LLx_SLOT, def_data,var_name);

			var_name = "CUR.AL1.CCD.POS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_CCD_POS, def_data,var_name);
		}

		if(bActive__LLx_MULTI_DOOR_VALVE)
		{
			for(int i=0; i<CFG_LLx__SIZE; i++)
			{
				int id = i + 1;

				for(int k=0; k<CFG_LLx__SLOT_SIZE; k++)
				{
					int slot = k + 1;

					var_name.Format("CFG.LL%1d.%1d.ALIGN.POS", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_ALIGN_ANGLE[i][k], def_data,var_name);

					var_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT[i][k], def_data,var_name);

					var_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.RANGE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_RANGE[i][k], def_data,var_name);

					var_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.START.ANGLE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_START_ANGLE[i][k], def_data,var_name);

					var_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.APPLY", id,slot);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_APPLY[i][k], def_data,var_name);

					var_name.Format("CUR.LL%1d.%1d.POST.POSITION.INCREMENT.ANGLE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[i][k], def_data,var_name);
				}
			}
		}
		else
		{
			for(int i=0; i<CFG_LLx__SIZE; i++)
			{
				int id = i + 1;

				var_name.Format("CFG.LL%1d.ALIGN.POS", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_ALIGN_ANGLE[i], def_data,var_name);

				var_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT[i], def_data,var_name);

				var_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT.RANGE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_RANGE[i], def_data,var_name);

				var_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT.START.ANGLE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_START_ANGLE[i], def_data,var_name);

				var_name.Format("CFG.LL%1d.POST.POSITION.INCREMENT.APPLY", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_APPLY[i], def_data,var_name);

				var_name.Format("CUR.aLL%1d.POST.POSITION.INCREMENT.ANGLE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[i], def_data,var_name);
			}
		}
	}

	// LINK : CHANNEL ...
	{
		//
		def_name = "CH.AL_OBJ_STATUS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__OBJ_STATUS, obj_name,var_name);

		//
		def_name = "CH.CFG_SLOT_MAX";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SLOT_MAX, obj_name,var_name);
	}

	// ALx OBJECT ...
	{
		def_name = "OBJ__AL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		if((obj_name.CompareNoCase("NO")   == 0)
		|| (obj_name.CompareNoCase("NULL") == 0))
		{
			bActive__AL1_USE = false;
		}
		else
		{
			bActive__AL1_USE = true;
		}

		if(bActive__AL1_USE)
		{
			pALx__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			// LINK.MODE ...
			{
				def_name = "AL_MODE.INIT";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sDATA__AL_MODE__INIT = def_data;

				def_name = "AL_MODE.ALIGN";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
				sDATA__AL_MODE__ALIGN = def_data;
			}

			// LINK.CHANNEL ...
			{
				def_name = "CH_AL.PARA_SLOT_ID";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ALx_PARA_SLOT, obj_name,var_name);

				def_name = "CH_AL.PARA_CCD_POS";
				p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__ALx_PARA_CCD_POS, obj_name,var_name);
			}
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	CString log_msg;
	CString log_bff;

	// ...
	{	
		log_msg.Format("Start ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}

	int flag = -1;

	if(mode.CompareNoCase(sMODE__ALIGN) == 0)
	{
		CString llx_name;
		CString llx_slot;
		CString al_angle;

		CString var_data;

		if(sEXT_CH__OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
		{
			dEXT_CH__MAINT_TARGT_LLx_NAME->Get__DATA(llx_name);
			dEXT_CH__MAINT_TARGT_LLx_SLOT->Get__DATA(llx_slot);
		}
		else
		{
			sEXT_CH__MODULE_LINK_TARGT_LLx_NAME->Get__DATA(llx_name);	
			sEXT_CH__MODULE_LINK_TARGT_LLx_SLOT->Get__DATA(llx_slot);	

			if(llx_name == "")		llx_name = "LBA";
			if(llx_slot == "")		llx_slot = "1";
		}

		// ...
		{
			log_msg = "\n";

			log_bff.Format("%s(%s) Align Info ... \n", llx_name,llx_slot);
			log_msg += log_bff;
		}

		// ...
		bool active_ll = false;

		int ll_index   = Macro__CHECK_LLx_INDEX(llx_name);
		int slot_index = -1;

		if(ll_index >= 0)
		{
			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				slot_index = atoi(llx_slot) - 1;
			
				if((slot_index >= 0) && (slot_index < CFG_LLx__SLOT_SIZE))
					active_ll = true;
			}
			else
			{
				active_ll = true;
			}
		}

		if(active_ll)
		{
			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				if(dEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_APPLY[ll_index][slot_index]->Check__DATA(STR__ENABLE) > 0)
				{
					aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[ll_index][slot_index]->Get__DATA(var_data);
					double cur_angle = atof(var_data);

					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT[ll_index][slot_index]->Get__DATA(var_data);
					double cfg_inc = atof(var_data);

					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_RANGE[ll_index][slot_index]->Get__DATA(var_data);
					double max_angle = atof(var_data);

					if(cur_angle > max_angle)		cur_angle = 0;

					// ...
					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_START_ANGLE[ll_index][slot_index]->Get__DATA(var_data);
					double start_angle = atof(var_data);

					al_angle.Format("%.0f", (start_angle+cur_angle));

					// ...
					{
						double next_angle = cur_angle + cfg_inc;
						if(next_angle > max_angle)		next_angle = 0;

						var_data.Format("%.0f", next_angle);
						aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[ll_index][slot_index]->Set__DATA(var_data);
					}

					// ...
					{
						log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
						log_msg += log_bff;

						log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
						log_msg += log_bff;

						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}	
				else
				{
					aEXT_CH__CFG_LLx_X_ALIGN_ANGLE[ll_index][slot_index]->Get__DATA(al_angle);

					// ...
					{
						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}
			}
			else
			{
				if(dEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_APPLY[ll_index]->Check__DATA(STR__ENABLE) > 0)
				{
					aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[ll_index]->Get__DATA(var_data);
					double cur_angle = atof(var_data);

					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT[ll_index]->Get__DATA(var_data);
					double cfg_inc = atof(var_data);

					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_RANGE[ll_index]->Get__DATA(var_data);
					double max_angle = atof(var_data);

					if(cur_angle > max_angle)		cur_angle = 0;

					// ...
					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_START_ANGLE[ll_index]->Get__DATA(var_data);
					double start_angle = atof(var_data);

					al_angle.Format("%.0f", (start_angle+cur_angle));

					// ...
					{
						double next_angle = cur_angle + cfg_inc;
						if(next_angle > max_angle)		next_angle = 0;

						var_data.Format("%.0f", next_angle);
						aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[ll_index]->Set__DATA(var_data);
					}

					// ...
					{
						log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
						log_msg += log_bff;

						log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
						log_msg += log_bff;

						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}	
				else
				{
					aEXT_CH__CFG_LLx_ALIGN_ANGLE[ll_index]->Get__DATA(al_angle);

					// ...
					{
						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}
			}
		}

		sEXT_CH__CUR_AL1_TARGET_LLx_NAME->Set__DATA(llx_name);
		sEXT_CH__CUR_AL1_TARGET_LLx_SLOT->Set__DATA(llx_slot);
		sEXT_CH__CUR_AL1_CCD_POS->Set__DATA(al_angle);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)		flag = Call__ALIGN(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__MSG->Set__DATA(log_msg);
	}

	return flag;
}
int CObj__ALx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
