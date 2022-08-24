#include "StdAfx.h"
#include "CObj__DGF_FLEX.h"



//------------------------------------------------------------------------------------------
int CObj__DGF_FLEX
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	aCH__CFG_DGF_INITIAL_CENTER_WEIGHT->Get__DATA(ch_data);
	aCH__CENTER_Wt_SET_POINT->Set__DATA(ch_data);

	return Call__CONTROL(p_variable, p_alarm);
}

int CObj__DGF_FLEX
::Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int i;

	// 1. ORIFICE Valve All Close
	for(i=0; i<_CFG__MAX_ORIFICE; i++)
	{
		if(dEXT_CH__ORIFICE_VALVE[i]->Set__DATA(STR__CLOSE) < 0)
		{
			CString log_msg;
			log_msg.Format("Orifice valve Close Error [%s]", dEXT_CH__ORIFICE_VALVE[i]->Get__VARIABLE_NAME());

			Fnc__WRITE_LOG(log_msg);
		}
	}

	// 2. BRANCH Valve All Close ...
	{
		dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(STR__CLOSE);

		dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(STR__CLOSE);
	}

	// ...
	{
		sCH__CUR_CENTER_SETPOINT->Set__DATA("__");
		dCH__MON_ALL_CLOSE_ACTIVE->Set__DATA(STR__ON);
	}
	return 1;
}

int CObj__DGF_FLEX
::Call__CONTROL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;
	double set_point, cfg_value;
	int level = -1;

	// 1. DGF Current Set Point Reading
	{
		aCH__CENTER_Wt_SET_POINT->Get__DATA(str_data);
		set_point = atof(str_data);

		sCH__CUR_CENTER_SETPOINT->Set__DATA(str_data);
		dCH__MON_ALL_CLOSE_ACTIVE->Set__DATA(STR__OFF);
	}

	// 2. DGF Function Table Reading
	for(int i=0; i<_CFG__MAX_DGF_LEVEL; i++)
	{
		aCH__MAX_LEVELx[i]->Get__DATA(str_data);	// Max Setpoint
		cfg_value = atof(str_data);

		// 3. Current Set <= Max Config Set (Search Level)
		if(set_point <= cfg_value)
		{
			level = i+1;
			aCH__MIN_LEVELx[i]->Get__DATA(str_data);
			double cfg_min = atof(str_data);

			// ...
			{
				CString log_msg;

				log_msg.Format("Orifice Level Set Point[%.3f] [%d](%.3f - %.3f)", set_point, level, cfg_min, cfg_value);
				Fnc__WRITE_LOG(log_msg);
			}
			break;
		}
	}

	// 4. Current Set Value < DGF Function Table Max Set Value ... Level
	if(level < 0)
	{
		// ...
		{
			CString log_msg;

			log_msg.Format("Orifice Level Mismatch SetPoint: [%.3f]", set_point);
			Fnc__WRITE_LOG(log_msg);
		}
		return -11;
	}
	else
	{
		if(Fnc__CONTROL(level) < 0)
		{
			// ...
			{
				CString log_msg;

				log_msg.Format("Call__CONTROL : Fnc__CONTROL (Level-%d) Failed ... ", level);
				Fnc__WRITE_LOG(log_msg);
			}
			return -21;
		}
	}

	return 1;
}


// ...
#define BRANCH2_EDGE_NUM				6
#define BRANCH2_CENTER_NUM				7
#define BRANCH1_EDGE_NUM				8
#define BRANCH1_CENTER_NUM				9
#define CHAMBER_CENTER_NUM				10
#define CHAMBER_EDGE_NUM				11


int CObj__DGF_FLEX
::Fnc__CONTROL(const int level)
{
	CString str_data;
	int i;

	for(i = 0; i < _CFG__MAX_VALVE; i++)
	{
		// 1. Level-Valve Array Data Get
		dCFG_CH__VALVE_STATUS[level-1][i]->Get__DATA(str_data);

		// 2. Level-Valve Set
		if(i < _CFG__MAX_ORIFICE)
			dEXT_CH__ORIFICE_VALVE[i]->Set__DATA(str_data);
		else if(i == BRANCH2_EDGE_NUM)
			dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(str_data);
		else if(i == BRANCH2_CENTER_NUM)
			dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(str_data);
		else if(i == BRANCH1_EDGE_NUM)
			dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(str_data);
		else if(i == BRANCH1_CENTER_NUM)
			dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(str_data);
		else if(i == CHAMBER_CENTER_NUM)
			dEXT_CH__CHAMBER_CENTER_VALVE->Set__DATA(str_data);
		else if(i == CHAMBER_EDGE_NUM)
			dEXT_CH__CHAMBER_EDGE_VALVE->Set__DATA(str_data);
	}
	return 1;
}

int CObj__DGF_FLEX
::Call__ORIFICE_CTRL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString vlv_type;
	int vlv_index = -1;

	dCH_PARA__ORIFICE_TYPE->Get__DATA(vlv_type);

		 if(vlv_type.CompareNoCase("VLV1") == 0)			vlv_index = 0;
	else if(vlv_type.CompareNoCase("VLV2") == 0)			vlv_index = 1;
	else if(vlv_type.CompareNoCase("VLV3") == 0)			vlv_index = 2;
	else if(vlv_type.CompareNoCase("VLV4") == 0)			vlv_index = 3;
	else if(vlv_type.CompareNoCase("VLV5") == 0)			vlv_index = 4;
	else if(vlv_type.CompareNoCase("VLV6") == 0)			vlv_index = 5;
	else													return -1;

	// ...
	int i;

	for(i=0; i<_CFG__MAX_ORIFICE; i++)
	{
		dEXT_CH__ORIFICE_VALVE[i]->Set__DATA(STR__CLOSE);
	}

	dEXT_CH__ORIFICE_VALVE[vlv_index]->Set__DATA(STR__OPEN);		

	if(vlv_index == 5)
	{
		dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(STR__CLOSE);

		dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(STR__OPEN);
		dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(STR__OPEN);
	}
	else
	{
		dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(STR__CLOSE);

		dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(STR__OPEN);
		dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(STR__OPEN);
	}

	dEXT_CH__CHAMBER_CENTER_VALVE->Set__DATA(STR__OPEN);
	dEXT_CH__CHAMBER_EDGE_VALVE->Set__DATA(STR__OPEN);

	return 1;
}

int CObj__DGF_FLEX
::Call__ALL_OPEN(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int i;

	for(i=0; i<_CFG__MAX_ORIFICE; i++)
	{
		dEXT_CH__ORIFICE_VALVE[i]->Set__DATA(STR__OPEN);		
	}

	// ...
	{
		dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(STR__OPEN);
		dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(STR__OPEN);

		dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(STR__OPEN);
		dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(STR__OPEN);

		dEXT_CH__CHAMBER_CENTER_VALVE->Set__DATA(STR__OPEN);
		dEXT_CH__CHAMBER_EDGE_VALVE->Set__DATA(STR__OPEN);
	}
	return 1;
}

// Gas Line Pump DGF Mode ...	
int CObj__DGF_FLEX
::Call__GASLINE_PUMP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int i;

	// 1. Branch Valve Close ...
	{
		dEXT_CH__BRANCH2_EDGE_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH2_CENTER_VALVE->Set__DATA(STR__CLOSE);

		dEXT_CH__BRANCH1_EDGE_VALVE->Set__DATA(STR__CLOSE);
		dEXT_CH__BRANCH1_CENTER_VALVE->Set__DATA(STR__CLOSE);

		//
		if(dEXT_CH__IO_VAC_SNS->Check__DATA(STR__ON) > 0)
		{
			dEXT_CH__CHAMBER_CENTER_VALVE->Set__DATA(STR__OPEN);
			dEXT_CH__CHAMBER_EDGE_VALVE->Set__DATA(STR__OPEN);
		}
	}

	// 2. Orifice Valve Open ...
	for(i=0; i<_CFG__MAX_ORIFICE; i++)
	{
		dEXT_CH__ORIFICE_VALVE[i]->Set__DATA(STR__OPEN);
	}

	// 3. V2, V4 Open
	{
		dEXT_CH__VLV_2->Set__DATA(STR__OPEN);
		dEXT_CH__VLV_4->Set__DATA(STR__OPEN);
	}

	return 1;
}

int CObj__DGF_FLEX
::Call__SAVE_LEVEL_VLV(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	log_msg = "\n";

	int i_limmit = _CFG__MAX_DGF_LEVEL;
	for(int i=0; i<i_limmit; i++)
	{
		log_bff.Format("%02d   ", i+1);
		log_msg += log_bff;

		int k_limit = _CFG__MAX_VALVE;
		int k;

		for(k=0; k<k_limit; k++)
		{
			log_bff.Format("%5s  ", dCFG_CH__VALVE_STATUS[i][k]->Get__STRING());
			log_msg += log_bff;
		}

		log_msg += "\n";
	}

	xLOG_CTRL->WRITE__LOG(log_msg);
	return 1;
}

void CObj__DGF_FLEX
::Fnc__WRITE_LOG(const CString& log_msg)
{
	xLOG_CTRL->WRITE__LOG(log_msg);
}
