#include "StdAfx.h"

#include "CObj_Phy__LPx_STD.h"
#include "CObj_Phy__LPx_STD__DEF.h"
#include "CObj_Phy__LPx_STD__ALID.h"

#include "Macro_Function.h"

#include "CMacro_FA.h"
extern CMacro_FA  mFA_Link;


// ...
#define SUB_MODE__INIT				"INIT"
#define SUB_MODE__MAP				"MAP"

#define SUB_MODE__PREPLOAD			"PREPLOAD"
#define SUB_MODE__CID_READ			"CID_READ"
#define SUB_MODE__LOAD				"LOAD"

#define SUB_MODE__RLSUNLOAD			"RLSUNLOAD"
#define SUB_MODE__UNLOAD_REQ		"UNLOAD.REQ"
#define SUB_MODE__UNLOAD			"UNLOAD"

#define SUB_MODE__RELOAD			"RELOAD"

#define SUB_MODE__RF_CID_READ		"RF_CID_READ"
#define SUB_MODE__RF_PAGE_READ		"RF_PAGE_READ"
#define SUB_MODE__RF_CID_WRITE		"RF_CID_WRITE"
#define SUB_MODE__RF_PAGE_WRITE		"RF_PAGE_WRITE"


//------------------------------------------------------------------------------------------
MODULE__IS_AVAILABLE(CObj_Phy__LPx_STD,LP, xCH__OBJ_STATUS,xCH__OBJ_CTRL);

#define DEF__CHECK_OUT_OF_SERVICE											\
if(xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__OUT_OF_SERVICE) > 0)			\
{																			\
	return 1;																\
}


//------------------------------------------------------------------------------------------
int CObj_Phy__LPx_STD
::Fnc__WAIT_SEC(CII_OBJECT__VARIABLE* p_variable,
				CII__VAR_ANALOG_CTRL* pch_analog_cfg)
{
	double cfg_sec = pch_analog_cfg->Get__VALUE();

	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->START__COUNT_UP(cfg_sec + 1.0);

	while(1)
	{
		Sleep(1);

		if(x_timer_ctrl->Get__CURRENT_TIME() >= cfg_sec)
		{
			return 1;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			break;
		}
	}

	return -1;
}

int CObj_Phy__LPx_STD
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("INIT : START");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__INIT);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("INIT : END");
	else			xLOG_CTRL->WRITE__LOG("INIT : ABORTED");
	
	return flag;
}
int CObj_Phy__LPx_STD::Fnc__MAP(CII_OBJECT__VARIABLE* p_variable,
								CII_OBJECT__ALARM* p_alarm)
{
	DEF__CHECK_OUT_OF_SERVICE;

	// ...
	CString log_string;

	log_string = "MAP_START : START";
	xLOG_CTRL->WRITE__LOG(log_string);
	
	sCH__PORT_STATUS->Set__DATA("MAP_START");
	FA_Seq__MAP_START();

	if(Fnc__LOAD(p_variable, p_alarm) < 0)
	{
		xLOG_CTRL->WRITE__LOG("MAP_START : ABORTED");
		return -1;
	}

	sCH__PORT_STATUS->Set__DATA("MAP_END");
	FA_Seq__MAP_END();

	log_string = "MAP_START : END";
	xLOG_CTRL->WRITE__LOG(log_string);

	if((xCH__FA_LP_HOST_VERIFY_FLAG->Check__DATA(STR__ENABLE) < 0)
	&& (xCH__FA_LP_ACCESS_REQ->Check__DATA(STR__MANUAL) > 0))
	{
		sCH__PORT_STATUS->Set__DATA("MAP_CONFIRM");
		return 1;
	}

	return Verify__MAP(p_alarm);
}
int CObj_Phy__LPx_STD::Fnc__PREPLOAD(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	if(iCALL_FLAG__FNC_UNLOAD > 0)
	{
		return 0;
	}
	
	if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
	{
		sCH__PORT_STATUS->Set__DATA("ABORTED");

		Sleep(90);
		return 1;
	}

	// ...
	{
		CString str_unknown = "UNKNOWN";
		
		int limit = CFG_LP__SLOT_MAX;
		int i;
		
		for(i=0;i<limit;i++)
		{
			xCH__SLOT_STATUS[i]->Set__DATA(str_unknown);
		}
	}

	// ...
	CString log_string;
	int flag;
	int cst_sts = -1;

	log_string = "PREPLOAD : START";
	xLOG_CTRL->WRITE__LOG(log_string);

	sCH__PORT_STATUS->Set__DATA("LOAD.REQ");
	xI_SCH_MATERIAL_CTRL->Clear__JOB(iPTN);

	FA_Seq__LOAD_REQ();

	// ...
	xI_SCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__LOAD_REQ(sObject_Name);
	sCH__PORT_UNLOAD_REQ_FROM_TMC->Set__DATA("");

	flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__PREPLOAD);

	xI_SCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__LOAD_REQ(sObject_Name);

	// ...
	FA_Seq__TRANSFER_BLOCKED();

	if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
	{
		if(cst_sts < 0)
		{
			xI_SCH_MATERIAL_CTRL->LPx__MOVE_IN(iPTN);
		}

		log_string = "PREPLOAD : END";

		if(flag > 0)
		{
			if(sCH__PORT_UNLOAD_REQ_FROM_TMC->Check__DATA("YES") > 0)
			{
				log_string = "PREPLOAD -> UNLOAD.REQ From TMC";

				sCH__PORT_STATUS->Set__DATA("CANCELED");
			}
			else
			{
				sCH__PORT_STATUS->Set__DATA("LOAD");
			}
		}
		else
		{
			sCH__PORT_STATUS->Set__DATA("ABORTED");
		}
	}
	else
	{
		sCH__PORT_STATUS->Set__DATA("ABORTED");

		log_string = "LOAD : ERROR (NO CASSETTE)";
	}
	
	xLOG_CTRL->WRITE__LOG(log_string);
	return flag;
}

int CObj_Phy__LPx_STD
::Check__CST_ERROR(CII_OBJECT__ALARM* p_alarm,const int load_seq_flag)
{
	if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
	{
		return 1;
	}

	// ...
	int flag;
	int check_loop;

	do
	{
		check_loop = -1;

		if(dCH__CST_STATUS->Check__DATA("NONE") > 0)
		{
			flag = -1;
		}
		else
		{
			flag = 1;
		}

		if(flag < 0)
		{
			int alarm_id = ALID__CST_DISAPPEAR__UNEXPECTEDLY;
			CString alarm_msg;
			CString r_act;

			if(load_seq_flag > 0)
			{
				alarm_msg.Format("Unexpectedly, LP%1d's cassette disappeared\n",iPTN);
				alarm_msg += "   During LOAD Sequence is running !\n";
			}
			else
			{
				alarm_msg.Format("Unexpectedly, LP%1d's cassette disappeared\n",iPTN);
				alarm_msg += "   During CID_READ Sequence is running !\n";
			}
			alarm_msg += "\n";
			alarm_msg += "  [RETRY_CHECK] :  Check if cassette on the load port exist or not.\n";
			alarm_msg += "  [ABORT]       :  Convert the status of load port to \"ABORTED\".\n";

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

			if(r_act.CompareNoCase("RETRY_CHECK") == 0)
			{
				check_loop = 1;
			}
			else
			{
				check_loop = -1;
			}
		}
	}
	while(check_loop > 0);

	return flag;
}

int CObj_Phy__LPx_STD
::Fnc__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const int seq_flag)
{
	DEF__CHECK_OUT_OF_SERVICE;
	
	iSEQ__LOCK_FLAG = 1;
	
	int flag = _Fnc__CID_READ(p_variable,p_alarm,seq_flag);

	iSEQ__LOCK_FLAG = -1;
	return flag;
}
int CObj_Phy__LPx_STD
::_Fnc__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm,
				 const int seq_flag)
{
	CString log_string;

	if(seq_flag > 0)
	{
		log_string = "CID_READ : START";
		xLOG_CTRL->WRITE__LOG(log_string);

		sCH__PORT_STATUS->Set__DATA("CID_READING");
		FA_Seq__CID_READ_START();

		// ...
		int flag = 1;

		if(mFA_Link.Is_LP__BYPASS_ID(iPTN) < 0)
		{
			flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__CID_READ);

			if(sCH__CID_STRING->Check__DATA("") > 0)
			{
				// R/F : Fail (Ignore) ?
				if(xCH__RF_YES_NO_FLAG->Check__DATA(STR__YES) > 0)
				{
					SCX__TIMER_CTRL x_timer_ctrl;
					x_timer_ctrl->WAIT(1.5);
				}

				// ...
				CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();

				if(p_e87_ctrl != NULL)
				{
					p_e87_ctrl->Event__CARRIERID_READ_FAIL(iPTN);
					p_e87_ctrl->Event__UNKNOWN_CARRIERID(iPTN);		
				}
			}
		}
		else
		{
			sCH__CID_STRING->Set__DATA("");
		}
		
		if(flag < 0)
		{
			sCH__PORT_STATUS->Set__DATA("ABORTED");
			return -1;
		}
		else
		{
			if(sCH__CID_STRING->Check__DATA("") > 0)
			{
				if(mFA_Link.Is__REMOTE() < 0)
				{
					int cfg_flag = -1;

					if(xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__FULL_AUTO) > 0)
					{
						cfg_flag = 1;
					}
					else
					{
						// R/F : Fail (Ignore) ? -> (Config Option)
						if(xCH__RF_YES_NO_FLAG->Check__DATA(STR__YES) > 0)
						{
							cfg_flag = 1;
						}
					}

					if(cfg_flag > 0)
					{
						if(xEXT_CH__CFG_LPx_CID_FORMAT->Check__DATA(STR__CID_FORMAT__USER) > 0)
						{
							if(Popup__WIN_CSTID() < 0)
							{
								Cancel__PORT();
								return 1;
							}
						}
						else
						{
							CString str_cid;
							CString str_date;
							CString str_time;

							Macro__GET_DATE_TIME(str_date,str_time);

							if(xEXT_CH__CFG_LPx_CID_FORMAT->Check__DATA(STR__CID_FORMAT__ONLY_TIME) > 0)
							{
								str_cid.Format("LP%1d-%s_%s",iPTN,str_date,str_time);
							}
							else
							{
								str_cid.Format("LP%1d_Bypass-%s_%s",iPTN,str_date,str_time);
							}
								
							sCH__CID_STRING->Set__DATA(str_cid);
						}
					}
					else
					{
						if(Popup__WIN_CSTID() < 0)
						{
							Cancel__PORT();
							return 1;
						}
					}

					// ...
				}
				else
				{
					if((xCH__FA_LP_CURRENT_STATUS->Check__DATA(STR__FULL_AUTO) < 0)
					&& (mFA_Link.Is_LP__BYPASS_ID(iPTN) < 0))
					{
						// R/F : Fail (Ignore) ? -> (NULL)
						if(xCH__RF_YES_NO_FLAG->Check__DATA(STR__YES) > 0)
						{

						}
						else
						{
							if(Popup__WIN_CSTID() < 0)
							{
								Cancel__PORT();
								return 1;
							}
						}
					}

					// ...
				}
			}
		}

		// ...
	}

	// ...
	{
		sCH__PORT_STATUS->Set__DATA("CID_READ");
		FA_Seq__CID_READ_END();

		log_string = "CID_READ : END";
		xLOG_CTRL->WRITE__LOG(log_string);
	}

	// ...
	{
		if(Check__CST_ERROR(p_alarm,-1) < 0)
		{
			return -1;
		}

		if((xCH__FA_LP_HOST_VERIFY_FLAG->Check__DATA(STR__ENABLE) < 0)
		&& (xCH__FA_LP_ACCESS_REQ->Check__DATA(STR__MANUAL) > 0))
		{
			sCH__PORT_STATUS->Set__DATA("CID_CONFIRM");	
			return 1;
		}

		if(Verify__CID(p_alarm) < 0)
		{
			return -1;
		}
	}
	return 1;
}
int CObj_Phy__LPx_STD::Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable,
								 CII_OBJECT__ALARM *p_alarm)
{
	DEF__CHECK_OUT_OF_SERVICE;

	iSEQ__LOCK_FLAG = 1;

	_Fnc__LOAD(p_variable, p_alarm);
	
	int flag = Check__CST_ERROR(p_alarm,1);
	if(flag > 0)
	{
		flag = _Fnc__DEVICE_MAP(p_alarm);
	}
	
	iSEQ__LOCK_FLAG = -1;
	return flag;
}
int CObj_Phy__LPx_STD::_Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable,
								  CII_OBJECT__ALARM* p_alarm)
{
	xLOG_CTRL->WRITE__LOG("LOAD : START");

	xCH__LPx_JOB_STATUS_FLAG->Set__DATA("");
	xEXT_CH__CFG_LPx_JOB_START_FLAG->Set__DATA("");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__LOAD);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("LOAD : END");
	else			xLOG_CTRL->WRITE__LOG("LOAD : ABORTED");

	return flag;
}

int CObj_Phy__LPx_STD::_Fnc__DEVICE_MAP(CII_OBJECT__ALARM* p_alarm)
{
	if(dEXT_CH__SCH_MAP_DEVICE->Check__DATA(STR__ATM_RB) < 0)
	{
		if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
		{
			for(int i=0; i<CFG_LP__SLOT_MAX; i++)
			{
				xCH__SLOT_STATUS[i]->Set__DATA(STR__EXIST);
			}
		}
		return 1;
	}

	xLOG_CTRL->WRITE__LOG("DEVICE_MAP : START");

	// ...
	CString str__map_req;

	sEXT_CH__LPx_MAP_REQ->Set__DATA(STR__YES);

	while(1)
	{
		Sleep(10);

		sEXT_CH__LPx_MAP_REQ->Get__DATA(str__map_req);

		if(str__map_req.CompareNoCase(STR__ERROR) == 0)
		{
			xLOG_CTRL->WRITE__LOG("DEVICE_MAP : ABORTED");
		
			if(mFA_Link.Is__REMOTE() > 0)
			{
				return -1;
			}
			return 1;
		}
		if(str__map_req.CompareNoCase(STR__YES) != 0)
		{
			xLOG_CTRL->WRITE__LOG("DEVICE_MAP : END");
			return 1;
		}
	}
	return -1;
}

int CObj_Phy__LPx_STD::Fnc__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("RLSUNLOAD : START");

	xEXT_CH__CFG_LPx_JOB_START_FLAG->Set__DATA("");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__RLSUNLOAD);

	if(flag > 0)
	{
		sCH__PORT_STATUS->Set__DATA(SUB_MODE__UNLOAD);
		xLOG_CTRL->WRITE__LOG("RLSUNLOAD : END");
	}
	else
	{
		sCH__PORT_STATUS->Set__DATA("ABORTED");
		xLOG_CTRL->WRITE__LOG("RLSUNLOAD : ABORTED");
	}
	return flag;
}

int CObj_Phy__LPx_STD::Fnc__RF_CID_READ(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("RF CID_READ : START");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__RF_CID_READ);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("RF CID_READ : END");
	else			xLOG_CTRL->WRITE__LOG("RF CID_READ : ABORTED");

	return flag;
}
int CObj_Phy__LPx_STD::Fnc__RF_PAGE_READ(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("RF PAGE_READ : START");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__RF_PAGE_READ);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("RF PAGE_READ : END");
	else			xLOG_CTRL->WRITE__LOG("RF PAGE_READ : ABORTED");

	return flag;
}
int CObj_Phy__LPx_STD::Fnc__RF_CID_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("RF CID_WRITE : START");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__RF_CID_WRITE);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("RF CID_WRITE : END");
	else			xLOG_CTRL->WRITE__LOG("RF CID_WRITE : ABORTED");

	return flag;
}
int CObj_Phy__LPx_STD::Fnc__RF_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable)
{
	DEF__CHECK_OUT_OF_SERVICE;

	xLOG_CTRL->WRITE__LOG("RF PAGE_WRITE : START");

	int flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__RF_PAGE_WRITE);

	if(flag > 0)	xLOG_CTRL->WRITE__LOG("RF PAGE_WRITE : END");
	else			xLOG_CTRL->WRITE__LOG("RF PAGE_WRITE : ABORTED");

	return flag;
}


int CObj_Phy__LPx_STD
::Fnc__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	xI_Sync_Ctrl.Thread__LOCK();
	iFLAG__MODULE_OBJ = 1;

	// ...
	{
		CString obj_msg;
		obj_msg.Format("%s started ...",obj_mode);

		xCH__SEQ_INFO_MSG->Set__DATA(obj_msg);
	}

	int flag = -1;

	if(dEXT_CH__SCH_TEST_CFG_TMC_DUMMY_BY_CTC->Check__DATA(STR__YES) > 0)
	{
		flag = Sim__MODULE_OBJ(p_variable, obj_mode);
	}
	else
	{
		flag = xI_Module_Obj->Connect__Module_Obj(obj_mode);
	}

	// ...
	{
		CString obj_msg;

		if(flag > 0)		obj_msg.Format("%s completed ...",obj_mode);
		else				obj_msg.Format("%s aborted ...",obj_mode);

		xCH__SEQ_INFO_MSG->Set__DATA(obj_msg);
	}

	iFLAG__MODULE_OBJ = -1;
	xI_Sync_Ctrl.Thread__UNLOCK();

	return flag;
}
int CObj_Phy__LPx_STD
::Sim__MODULE_OBJ(CII_OBJECT__VARIABLE* p_variable,
				  const CString obj_mode)
{
	CII__VAR_ANALOG_CTRL* pch_analog_cfg = NULL;

	if(obj_mode.CompareNoCase(SUB_MODE__INIT) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_INIT_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__MAP) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_MAP_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__PREPLOAD) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_PREPLOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__CID_READ) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_CID_READ_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__LOAD) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_LOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RLSUNLOAD) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RLSUNLOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__UNLOAD_REQ) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_UNLOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__UNLOAD) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_UNLOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RELOAD) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RELOAD_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RF_CID_READ) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RF_CID_READ_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RF_PAGE_READ) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RF_PAGE_READ_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RF_CID_WRITE) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RF_CID_WRITE_SEC.Get__PTR();
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RF_PAGE_WRITE) == 0)
	{
		pch_analog_cfg = aCH__SCH_TEST_CFG_RF_PAGE_WRITE_SEC.Get__PTR();
	}

	// ...
	CString log_msg;
	CString log_bff;

	log_msg.Format("Sim__MODULE_OBJ() : Started ... \n");
	log_bff.Format(" * Obj_Mode <- %s \n", obj_mode);
	log_msg += log_bff;

	if(pch_analog_cfg == NULL)
	{
		log_msg += " * pch_analog_cfg - Error ! \n";

		xLOG_CTRL->WRITE__LOG(log_msg);
		return -1;
	}
	else
	{
		log_bff.Format(" * %s <- %.1f sec \n", 
						pch_analog_cfg->Get__CHANNEL_NAME(),
						pch_analog_cfg->Get__VALUE());
		log_msg += log_bff;

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	if(Fnc__WAIT_SEC(p_variable, pch_analog_cfg) < 0)
	{
		return -2;
	}

	if(obj_mode.CompareNoCase(SUB_MODE__INIT) == 0)
	{
		xCH__OBJ_STATUS->Set__DATA(STR__STANDBY);
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__RLSUNLOAD) == 0)
	{
		if(dCH__CST_STATUS->Check__DATA(STR__NONE) < 0)
		{
			dCH__CST_STATUS->Set__DATA(STR__EXIST);
		}
		dCH__DOOR_STS->Set__DATA(STR__CLOSE);
		dCH__SHUTL_STS->Set__DATA(STR__UNLOAD);
		dCH__CLAMP_STS->Set__DATA(STR__UNCLAMP);
	}
	else if((obj_mode.CompareNoCase(SUB_MODE__UNLOAD_REQ) == 0)
		 || (obj_mode.CompareNoCase(SUB_MODE__UNLOAD) == 0))
	{
		// MessageBox(NULL, "Unload.Req Completed ?", sObject_Name, MB_OK);
		Sleep(3000);

		dCH__CST_STATUS->Set__DATA(STR__NONE);
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__PREPLOAD) == 0)
	{
		// MessageBox(NULL, "Preload Completed ?", sObject_Name, MB_OK);
		Sleep(3000);

		dCH__CST_STATUS->Set__DATA(STR__EXIST);
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__LOAD) == 0)
	{
		dCH__CLAMP_STS->Set__DATA(STR__CLAMP);
		dCH__SHUTL_STS->Set__DATA(STR__LOAD);
		dCH__DOOR_STS->Set__DATA(STR__OPEN);
	}
	else if(obj_mode.CompareNoCase(SUB_MODE__MAP) == 0)
	{
		for(int i=0; i<CFG_LP__SLOT_MAX; i++)
		{
			xCH__SLOT_STATUS[i]->Set__DATA(STR__EXIST);
		}
	}

	// ...
	{
		log_msg.Format("Sim__MODULE_OBJ() : Completetd ... \n");
		
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int CObj_Phy__LPx_STD
::Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const int complete_flag)
{
	// ...
	{
		xCH__LPx_END_REQ_FLAG->Set__DATA("");
		xCH__LPx_RETURN_REQ_FLAG->Set__DATA("");
	}

	if(xCH__APP_LOCK_FLAG->Check__DATA(STR__YES) > 0)
	{
		int alarm_id = ALID__LPx_IN_USE__NOT_UNLOAD;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}

	// ...
	DEF__CHECK_OUT_OF_SERVICE;

	iCALL_FLAG__FNC_UNLOAD = 1;

	// ...
	{
		CString str_lotid;
		sCH__PORT_LOTID->Get__DATA(str_lotid);

		if(complete_flag > 0)		xLOT_LOG_CTRL->Register__LOT_COMPLETED(str_lotid);
		else						xLOT_LOG_CTRL->Register__LOT_ABORTED(str_lotid);

		xLOT_LOG_CTRL->Clear__LOG_NAME(str_lotid);
	}

	int flag = _Fnc__UNLOAD(p_variable, complete_flag);

	Sleep(490);
	iCALL_FLAG__FNC_UNLOAD = -1;

	return flag;
}
int CObj_Phy__LPx_STD::_Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable,
									const int complete_flag)
{
	if(LP__Is_Available() < 0)
	{
		sCH__PORT_STATUS->Set__DATA("ABORTED");

		CString log_string;
		log_string.Format("UNLOAD : ABORTED - LP Status ??");
		xLOG_CTRL->WRITE__LOG(log_string);
		return -1;
	}
	
	// ...
	{
		sCH__PORT_CJOBID->Set__DATA("");
		sCH__PORT_JOB_POPUP_TYPE->Set__DATA("");
		sCH__LPx_PICK_COUNT->Set__DATA("");
		sCH__LPx_LAMP_STATUS->Set__DATA("FINISH");
	}

	if(Is__DUMMY_PORT() > 0)
	{
		Set__DUMMY_PORT();
		return 1;
	}

	// ...
	CString log_string;
	int flag;

	log_string.Format("UNLOAD : START");
	xLOG_CTRL->WRITE__LOG(log_string);

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		CString dir_prc;
		CString path;		

		x_seq_info->Get__DIR_PROCESS(dir_prc);
		path.Format("%s\\LP%1d\\LP%1d_LocalJOB.css", dir_prc,iPTN,iPTN);

		DeleteFile(path);
	}

	flag = Fnc__RLSUNLOAD(p_variable);

	// ...
	int cst_sts = 1;

	if(flag > 0)
	{
		sCH__PORT_STATUS->Set__DATA(SUB_MODE__UNLOAD_REQ);
		
		if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
		{
			FA_Seq__UNLOAD_REQ();

			xI_SCH_MATERIAL_CTRL->Set__SYSTEM_STATUS__UNLOAD_REQ(sObject_Name);

			flag = Fnc__MODULE_OBJ(p_variable, SUB_MODE__UNLOAD);
	
			xI_SCH_MATERIAL_CTRL->Clear__SYSTEM_STATUS__UNLOAD_REQ(sObject_Name);
		}
		else 
		{
			cst_sts = -1;
		}
	}

	FA_Seq__TRANSFER_BLOCKED();

	if(flag > 0)
	{
		if(dCH__CST_STATUS->Check__DATA("NONE") < 0)
		{
			sCH__PORT_STATUS->Set__DATA(SUB_MODE__UNLOAD);

			log_string.Format("UNLOAD : END   (CST EXIST)");
		}
		else
		{
			if(cst_sts > 0)
			{
				xI_SCH_MATERIAL_CTRL->LPx__MOVE_OUT(iPTN);
			}

			if(sCH__PORT_STATUS->Check__DATA("EMPTY") < 0)
			{
				sCH__PORT_STATUS->Set__DATA(SUB_MODE__UNLOAD);
			}

			log_string.Format("UNLOAD : END   (CST NONE)");
		}
	}
	else
	{
		sCH__PORT_STATUS->Set__DATA("ABORTED");

		log_string.Format("UNLOAD : ABORTED");
	}

	xLOG_CTRL->WRITE__LOG(log_string);

	if(complete_flag > 0)
	{
		if(xEXT_CH__MELODY_CTRL->Check__DATA("FOUP_ON") > 0)
		{
			if(dCH__CST_STATUS->Check__DATA("NONE") > 0)
			{
				xEXT_CH__MELODY_BUZZER->Set__DATA("OFF");
			}
		}
	}
	return flag;
}
  
// ...
int CObj_Phy__LPx_STD
::Fnc__RELOAD(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__RELOAD(p_variable, p_alarm, 1);
}
int CObj_Phy__LPx_STD
::Fnc__RELOAD(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm,
			  const int seq_flag)
{
	DEF__CHECK_OUT_OF_SERVICE;

	// ...
	int flag = Fnc__CID_READ(p_variable,p_alarm,seq_flag);

	if(flag < 0)
	{
		xCH__RELOAD_FLAG->Set__DATA("NO");
		return -1;
	}

	if((sCH__PORT_STATUS->Check__DATA("CANCELED")   > 0)
	|| (sCH__PORT_STATUS->Check__DATA("ABORTED")    > 0)
	|| (sCH__PORT_STATUS->Check__DATA(STR__UNLOAD_REQ) > 0))
	{
		xCH__RELOAD_FLAG->Set__DATA("NO");
		return -1;
	}

	// ...
	CString log_string;

	// ...
	{
		log_string = "RELOAD : START";
		xLOG_CTRL->WRITE__LOG(log_string);

		flag = Fnc__MAP(p_variable,p_alarm);

		xCH__RELOAD_FLAG->Set__DATA("NO");
	}
	return flag;
}


//------------------------------------------------------------------------------------------
int CObj_Phy__LPx_STD::Cancel__PORT()
{
	FA_Seq__CAMCEL();

	sCH__PORT_STATUS->Set__DATA("CANCELED");
	return 1;
}
int CObj_Phy__LPx_STD::Pause__PORT(CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		xI_SCH_MATERIAL_CTRL->Pause__PORT_ID(iPTN);

		FA_Seq__PAUSE();
		sCH__PORT_STATUS->Set__DATA("PAUSED");
	}

	// ...
	{
		int alarm_id = ALID__LPx__JOB_PAUSED;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
	}
	return 1;
}
int CObj_Phy__LPx_STD::Resume__PORT(CII_OBJECT__ALARM* p_alarm)
{
	xI_SCH_MATERIAL_CTRL->Resume__PORT_ID(iPTN);

	FA_Seq__RESUME();
	sCH__PORT_STATUS->Set__DATA(STR__BUSY);

	// ...
	{
		int alarm_id = ALID__LPx__JOB_RESUMED;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
	}
	return 1;
}
int CObj_Phy__LPx_STD::Abort__PORT(CII_OBJECT__ALARM* p_alarm)
{
	if(xCH__CFG_END_BUTTON_MODE->Check__DATA(STR__ENABLE) > 0)
	{
		if(xCH__END_BUTTON_FLAG->Check__DATA("ON") < 0)
		{
			CString title;
			CString msg;
			CString msg_bff;
			CStringArray l_act;
			CString r_act;

			msg_bff.Format("The status of LP%1d's job-end button is not \"ON\"",iPTN);
			title += msg_bff;

			msg  = "Can not execute the \"JOB END\" command.\n";
			msg_bff.Format("To run the command, the status of LP%1d job-end button must be \"ON\".\n",iPTN);
			msg += msg_bff;
			msg_bff.Format("Please, check the status of LP%1d job-end button !",iPTN);
			msg += msg_bff;

			l_act.RemoveAll();
			l_act.Add("CHECK");

			p_alarm->Popup__MESSAGE_BOX(title,msg,l_act,r_act);
			return -1;
		}
	}

	if(sCH__LPx_LAMP_STATUS->Check__DATA("PROCESS") > 0)
	{
		sCH__LPx_LAMP_STATUS->Set__DATA("END");
	}

	// ...
	{
		CString var_data;
		int slot_id;

		aCH__PORT_CFG_JOB_END_SLOT->Get__DATA(var_data);
		slot_id = atoi(var_data);

		//xI_SCH_MATERIAL_CTRL->End__PORT_ID(iPTN);
		xI_SCH_MATERIAL_CTRL->End__PTN_And_SLOTID(iPTN,slot_id);

		// ...
		{
			int alarm_id = ALID__LPx__JOB_END;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}
	}

	FA_Seq__ABORT();
	return 1;
}
int CObj_Phy__LPx_STD::Return__PORT(CII_OBJECT__ALARM* p_alarm)
{
	xI_SCH_MATERIAL_CTRL->Return__PORT_ID(iPTN);

	// ...
	{
		int alarm_id = ALID__LPx__JOB_ABORT;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);
	}

	FA_Seq__ABORT();
	return 1;
}
int CObj_Phy__LPx_STD::Reload__PORT(CII_OBJECT__ALARM* p_alarm, const int call_flag)
{	
	if(sCH__PIO_TRANSFER->Check__DATA(STR__YES) > 0)
	{
		return -11;
	}

	xLOG_CTRL->WRITE__LOG("Reload__PORT : START");

	// Process Wafer Check ...
	{
		bool active__err_check = false;

		CString err_msg;
		CString err_bff;

		CString ch_data = dCH__CFG_SLOT_MAX->Get__STRING();
		int cfg_max = atoi(ch_data);		
		if(cfg_max > CFG_LP__SLOT_MAX)		cfg_max = CFG_LP__SLOT_MAX;

		for(int i=0; i<cfg_max; i++)
		{
			int id = i + 1;
			ch_data = xCH__SLOT_STATUS[i]->Get__STRING();

			if((ch_data.CompareNoCase(STR__PROCESSING) == 0)
			|| (ch_data.CompareNoCase(STR__PROCESSED)  == 0)
			|| (ch_data.CompareNoCase(STR__COMPLETED)  == 0)
			|| (ch_data.CompareNoCase(STR__ABORTED)    == 0))
			{
				active__err_check = true;

				err_bff.Format(" Slot(%02d) - %s \n", id,ch_data);
				err_msg += err_bff;
			}
		}

		if(active__err_check)
		{
			CString box_title;
			CString box_msg;
			CStringArray l_option;
			CString r_act;

			box_title.Format("LP%1d - Reload Error !", iPTN);

			box_msg  = "There is a processing or processed wafer in load port. \n";
			box_msg += "Do you want to reload foup ? \n";
			box_msg += "\n";
			box_msg += err_msg;

			l_option.RemoveAll();
			l_option.Add(ACT__YES);
			l_option.Add(ACT__NO);

			// ...
			{
				CString log_msg;

				log_msg = "\n";
				log_msg += box_msg;

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			p_alarm->Popup__MESSAGE_BOX(box_title, box_msg, l_option, r_act);

			// ...
			{
				CString log_msg;

				log_msg.Format("\n User.Selection <- [%s] \n", r_act);

				xLOG_CTRL->WRITE__LOG(log_msg);
			}

			if(r_act.CompareNoCase(ACT__YES) != 0)			
			{
				return -1;
			}
		}
	}

	if(sCH__PIO_TRANSFER->Check__DATA(STR__YES) > 0)
	{
		return -21;
	}

	// ...
	{
		xCH__RELOAD_FLAG->Set__DATA("YES");
		Sleep(90);
	
		xI_Module_Obj->Abort__Module_Obj();
		Sleep(90);
	}

	if(xCH__OBJ_CTRL->Check__DATA("ABORTED") > 0)
	{
		xCH__RELOAD_FLAG->Set__DATA("NO");
		sCH__PORT_STATUS->Set__DATA("ABORTED");		

		xLOG_CTRL->WRITE__LOG("Reload__PORT : ABORTED");
		return -1;
	}

	if(call_flag < 0)
	{
		sCH__PORT_STATUS->Set__DATA("RELOAD");
	}

	xLOG_CTRL->WRITE__LOG("Reload__PORT : END");
	return 1;
}

int CObj_Phy__LPx_STD::Verify__CID(CII_OBJECT__ALARM* p_alarm)
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();

	if((p_e30_ctrl == NULL)
	|| (p_e87_ctrl == NULL))
	{
		sCH__PORT_STATUS->Set__DATA("CID_CONFIRM");
		return 1;
	}

	// ...
	int lp_auto = -1;

	if((p_e30_ctrl->Is_LP__IN_SERVICE(iPTN) > 0)
	&& (p_e30_ctrl->Is_REMOTE() > 0))
	{
		lp_auto = 1;

		sCH__PORT_STATUS->Set__DATA("CID_VERIFY");	
	}

	// ...
	int location_report = -1;
	int carrier_reader_available = 1;

	if(location_report < 0)
	{
		CString lp_cstid;
		sCH__CID_STRING->Get__DATA(lp_cstid);

		if(lp_cstid.GetLength() > 0)
		{
			CString cst_pos;
			cst_pos.Format("LP%1d",iPTN);

			p_e87_ctrl->Event__CARRIER_LOCATION_CHANGE(iPTN,cst_pos);

			location_report = 1;
		}
		else if(p_e87_ctrl->Is__EQUIPMENT_BASED_VERIFICATION(iPTN) > 0)
		{
			CString e87_cstid;
			p_e87_ctrl->Get_VID__CarrierID(iPTN,e87_cstid);
			sCH__CID_STRING->Set__DATA(e87_cstid);

			CString cst_pos;
			cst_pos.Format("LP%1d",iPTN);

			p_e87_ctrl->Event__CARRIER_LOCATION_CHANGE(iPTN,cst_pos);

			location_report = 1;
			carrier_reader_available = -1;
		}
	}

	// ...
	int flag = 1;

	if(lp_auto > 0)
	{
		flag = Fnc__Verify_CarrierID(p_alarm,iPTN,carrier_reader_available);

		if(flag > 0)
		{
			sCH__PORT_STATUS->Set__DATA("CID_CONFIRM");	
		}
		else if(flag == -11)
		{
			
		}
		else
		{
			if(sCH__PORT_STATUS->Check__DATA(STR__UNLOAD_REQ) < 0)
			{
				sCH__PORT_STATUS->Set__DATA("CANCELED");
			}
		}
	}
	else
	{
		CString lp_cstid;
		sCH__CID_STRING->Get__DATA(lp_cstid);

		p_e87_ctrl->Create__CARRIER_With_CID_VERIFICATION_OK(iPTN,lp_cstid);

		sCH__PORT_STATUS->Set__DATA("CID_CONFIRM");
	}

	if(location_report < 0)
	{
		CString lp_cstid;
		sCH__CID_STRING->Get__DATA(lp_cstid);

		if(lp_cstid.GetLength() > 0)
		{
			CString cst_pos;
			cst_pos.Format("LP%1d",iPTN);

			p_e87_ctrl->Event__CARRIER_LOCATION_CHANGE(iPTN,cst_pos);
		}
	}

	return flag;
}
int CObj_Phy__LPx_STD::Verify__MAP(CII_OBJECT__ALARM* p_alarm)
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E90_CTRL *p_e90_ctrl = mFA_Link.Get__E90_CTRL();

	if((p_e30_ctrl == NULL)
	|| (p_e90_ctrl == NULL))
	{
		sCH__PORT_STATUS->Set__DATA("MAP_CONFIRM");
		return 1;
	}

	// ...
	int lp_auto = -1;

	if((p_e30_ctrl->Is_LP__IN_SERVICE(iPTN) > 0)
	&& (p_e30_ctrl->Is_REMOTE() > 0))
	{
		lp_auto = 1;
		
		sCH__PORT_STATUS->Set__DATA("MAP_VERIFY");
	}

	// ...
	int flag = 1;

	if(lp_auto > 0)
	{
		flag = Fnc__Verify_SlotMap(p_alarm,iPTN);
			
		if(flag > 0)
		{
			sCH__PORT_STATUS->Set__DATA("MAP_CONFIRM");

			p_e90_ctrl->Create__OBJECT(iPTN);
		}
		else
		{
			if(sCH__PORT_STATUS->Check__DATA(STR__UNLOAD_REQ) < 0)
			{
				sCH__PORT_STATUS->Set__DATA("CANCELED");
			}
		}
	}
	else
	{
		sCH__PORT_STATUS->Set__DATA("MAP_CONFIRM");

		p_e90_ctrl->Create__OBJECT(iPTN);
	}
	return flag;
}


int CObj_Phy__LPx_STD
::Fnc__Verify_CarrierID(CII_OBJECT__ALARM* p_alarm,const int ptn,const int carrier_reader_available)
{
	CI_FA_300mm__E30_CTRL *p_e30_ctrl = mFA_Link.Get__E30_CTRL();
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();

	if(p_e30_ctrl == NULL)			return -1;
	if(p_e87_ctrl == NULL)			return -2;

	//
	if(p_e87_ctrl->Is__EQUIPMENT_BASED_VERIFICATION(ptn) > 0)
	{
		// Equipment Verification

		CString e87_cstid;
		CString lp_cstid;
		int bypass_flag = -1;

		p_e87_ctrl->Get_VID__CarrierID(ptn,e87_cstid);

		if(p_e30_ctrl->Is_LP__BYPASS_READ_ID(ptn) < 0)
		{
			sCH__CID_STRING->Get__DATA(lp_cstid);
		}
		else
		{
			bypass_flag = 1;

			lp_cstid = e87_cstid;
			sCH__CID_STRING->Set__DATA(lp_cstid);
		}

		if((e87_cstid != lp_cstid)
		|| (e87_cstid.GetLength()    < 1)
		|| (carrier_reader_available < 0))
		{
			if(e87_cstid != lp_cstid)
			{
				int db_index = ptn - 1;

				if((db_index >= 0)&&(db_index < CFG_LP_LIMIT))
				{
					CString r_act;

					p_alarm->Check__ALARM(ALID__CARRIER_VERIFY_FAIL,r_act);
					p_alarm->Post__ALARM(ALID__CARRIER_VERIFY_FAIL);
				}

				// ...
				{
					p_e87_ctrl->Report_CarrierObject__CARRIER_To_NoState(ptn);

					p_e87_ctrl->Set__CarrierID(ptn,lp_cstid);
					p_e87_ctrl->Event__LP__ASSOCIATED(ptn);
					p_e87_ctrl->Report_CarrierIDStatus__NoState_To_ID_WAITING_FOR_HOST(ptn);
				}
			}
			else
			{
				if(bypass_flag < 0)
				{
					p_e87_ctrl->Event__LP__ID_WAITING_FOR_HOST__BypassReadID_False(ptn);
				}
				else
				{
					p_e87_ctrl->Event__LP__ID_VERIFICATION_OK__BypassReadID_True(ptn);

					return 1;
				}
			}
		}
		else
		{
			if(bypass_flag < 0)
			{
				p_e87_ctrl->Event__LP__ID_VERIFICATION_OK(ptn);
			}
			else
			{
				p_e87_ctrl->Event__LP__ID_VERIFICATION_OK__BypassReadID_True(ptn);
			}
			
			return 1;
		}
	}
	else
	{
		// Host Verification

		CString lp_cstid;
		sCH__CID_STRING->Get__DATA(lp_cstid);

		if(p_e30_ctrl->Is_LP__BYPASS_READ_ID(ptn) < 0)
		{
			p_e87_ctrl->Create__CARRIER_With_CID_WAITING_FOR_HOST(ptn,lp_cstid);
			p_e87_ctrl->Set__CarrierID(ptn,lp_cstid);
		}
		else
		{
			p_e87_ctrl->Create__CARRIER_With_CID_WAITING_FOR_HOST(ptn,lp_cstid);
			p_e87_ctrl->Set__CarrierID(ptn,lp_cstid);
		}
	}

	// ...
	CString host_cstid;
	int result;
	int cst_flag = 0;
	
	while(1)
	{
		Sleep(100);

		if(p_e87_ctrl->Receive__VERIFICATION_RESULT_From_HOST(ptn,result) > 0)
		{
			CString e87_cstid;

			p_e87_ctrl->Get_VID__CarrierID(ptn,e87_cstid);
			sCH__CID_STRING->Set__DATA(e87_cstid);

			if(result < 0)
			{
				p_e87_ctrl->Event__LP__ID_VERIFICATION_FAIL(ptn);
				return -1;
			}

			p_e87_ctrl->Event__LP__ID_VERIFICATION_OK(ptn);
			return 1;
		}

		if(dCH__CST_STATUS->Check__DATA("NONE") > 0)
		{
			cst_flag++;
			
			if(cst_flag > 4)
			{
				return -11;
			}
		}
		else
		{
			cst_flag = 0;
		}
		
		if(sCH__PORT_STATUS->Check__DATA("CID_VERIFY") < 0)
		{
			return -1;
		}
	}

	return 1;
}
int CObj_Phy__LPx_STD
::Fnc__Verify_SlotMap(CII_OBJECT__ALARM* p_alarm,const int ptn)
{
	CI_FA_300mm__E87_CTRL *p_e87_ctrl = mFA_Link.Get__E87_CTRL();
	if(p_e87_ctrl == NULL)			return -1;

	// ...
	int flag = -1;

	// ...
	{
		CStringArray lp_slot_list;
		CStringArray e87_slot_list;
		int e87_flag;

		Get__PORT_SLOT_STS(lp_slot_list);
		e87_flag = p_e87_ctrl->Get_LP__SLOT_MAP_INFO(ptn,e87_slot_list);

		int lp_limit  = lp_slot_list.GetSize();
		int e87_limit = e87_slot_list.GetSize();

		if((lp_limit == e87_limit)
		&& (e87_flag > 0))
		{
			flag = 1;
			
			for(int i=0;i<lp_limit;i++)
			{
				if(atoi(e87_slot_list[i]) > 0)
				{
					if(lp_slot_list[i] != "EXIST")
					{
						flag = -1;
						break;
					}
				}
				else 
				{
					if(lp_slot_list[i] != "NONE")
					{
						flag = -2;
						break;
					}
				}
			}

			if(flag > 0)
			{
				p_e87_ctrl->Event__LP__SLOT_MAP_VERIFICATION_OK(ptn);
				return 1;
			}
		}

		if(p_e87_ctrl->Is__EQUIPMENT_BASED_VERIFICATION(ptn) > 0)
		{
			p_e87_ctrl->Set_Reason__VERIFICATION_BY_EQUIPMENT_UNSUCCESSFUL(ptn);
		}
		else
		{
			p_e87_ctrl->Set_Reason__VERIFICATION_NEEDED(ptn);
		}

		p_e87_ctrl->Event__LP__SLOT_MAP_WAITING_FOR_HOST(ptn);
	}

	// ...
	CString host_cstid;
	int result;
	
	while(1)
	{
		Sleep(100);

		if(p_e87_ctrl->Receive__VERIFICATION_RESULT_From_HOST(ptn,result) > 0)
		{
			if(result < 0)
			{
				if((dCH__CST_STATUS->Check__DATA("NONE") < 0)
				&& (sCH__PORT_STATUS->Check__DATA("MAP_VERIFY") > 0))
				{
					int db_index = ptn - 1;

					if((db_index >= 0)&&(db_index < CFG_LP_LIMIT))
					{
						CString r_act;

						p_alarm->Check__ALARM(ALID__MAP_VERIFY_FAIL,r_act);
						p_alarm->Post__ALARM(ALID__MAP_VERIFY_FAIL);
					}
				}

				p_e87_ctrl->Event__LP__SLOT_MAP_VERIFICATION_FAIL(ptn);
				return -1;
			}

			p_e87_ctrl->Event__LP__SLOT_MAP_VERIFICATION_OK(ptn);
			return 1;
		}

		if(dCH__CST_STATUS->Check__DATA("NONE") > 0)
		{
			return -1;
		}
		
		if(sCH__PORT_STATUS->Check__DATA("MAP_VERIFY") < 0)
		{
			return -1;
		}
	}

	return 1;
}

	
//------------------------------------------------------------------------------------------
int CObj_Phy__LPx_STD::Is__DUMMY_PORT()
{
	if(dCH_CFG__LPx_USE->Check__DATA("DUMMY") > 0)
	{
		return 1;
	}
	return -1;
}
int CObj_Phy__LPx_STD::Set__DUMMY_PORT()
{
	if(dCH_CFG__LPx_USE->Check__DATA("DUMMY") > 0)
	{
		xI_SCH_MATERIAL_CTRL->Clear__JOB(iPTN);

		Clear__PORT_DATA();
		Set__PORT_SLOT_STS_TO_NEW_STS("EXIST");

		sCH__PORT_STATUS->Set__DATA("WAITING");
		return 1;
	}
	return -1;
}

int CObj_Phy__LPx_STD::Clear__PORT_DATA()
{
	sCH__PORT_LOTID->Set__DATA("");
	sCH__PORT_PPID->Set__DATA("");

	sCH__PORT_JOB_POPUP_FILE->Set__DATA("");
	sCH__PORT_JOB_POPUP_FILE->Set__DATA("");
	sCH__PORT_JOB_NAME->Set__DATA("");
	return 1;
}

int CObj_Phy__LPx_STD::Is__MANUAL_MODE()
{
	if((xCH__FA_LP_ACCESS_REQ->Check__DATA("MANUAL") > 0)
	&& (xCH__FA_LP_MANUAL_LOADING_FLAG->Check__DATA("ENABLE") > 0))
	{
		return 1;
	}

	return -1;
}

void CObj_Phy__LPx_STD::Get__PORT_SLOT_STS(CUIntArray& l_slot_Sts)
{
	l_slot_Sts.RemoveAll();

	for(int i=0; i<CFG_LP__SLOT_MAX; i++)
	{
		if(xCH__SLOT_STATUS[i]->Check__DATA("NONE") > 0)
		{
			l_slot_Sts.Add(-1);
		}
		else
		{
			l_slot_Sts.Add(1);
		}
	}
}
void CObj_Phy__LPx_STD::Get__PORT_SLOT_STS(CStringArray& l_slot_Sts)
{
	l_slot_Sts.RemoveAll();

	for(int i=0; i<CFG_LP__SLOT_MAX; i++)
	{
		if(xCH__SLOT_STATUS[i]->Check__DATA("NONE") > 0)
		{
			l_slot_Sts.Add("0");
		}
		else
		{
			l_slot_Sts.Add("1");
		}
	}
}
void CObj_Phy__LPx_STD::Set__PORT_SLOT_STS_TO_NEW_STS(const CString& new_sts)
{
	for(int i=0; i<CFG_LP__SLOT_MAX; i++)
	{
		if(xCH__SLOT_STATUS[i]->Check__DATA("NONE") > 0)
		{
			continue;
		}

		xCH__SLOT_STATUS[i]->Set__DATA(new_sts);
	}
}

int  CObj_Phy__LPx_STD::Check__PORT_STS__Standby_Or_CtcInUse()
{
	CString obj_sts;
	xCH__OBJ_STATUS->Get__DATA(obj_sts);

	if((obj_sts.CompareNoCase("STANDBY")  == 0)
    || (obj_sts.CompareNoCase("CTCINUSE") == 0))
	{
		return 1;
	}
	return -1;
}

int  CObj_Phy__LPx_STD::Check__PORT_STATUS__JOB_READY()
{
	CString lp_sts;
	sCH__PORT_STATUS->Get__DATA(lp_sts);

	if(lp_sts.CompareNoCase("RESERVE") == 0)		return 1;
	if(lp_sts.CompareNoCase("START")   == 0)		return 1;
	if(lp_sts.CompareNoCase(STR__BUSY) == 0)		return 1;
	if(lp_sts.CompareNoCase("PAUSED")  == 0)		return 1;

	return -1;
}
