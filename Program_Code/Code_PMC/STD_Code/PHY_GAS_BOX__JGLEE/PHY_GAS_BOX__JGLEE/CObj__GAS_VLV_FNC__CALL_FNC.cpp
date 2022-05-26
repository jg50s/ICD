#include "StdAfx.h"
#include "CObj__GAS_VLV_FNC.h"


#define MFC_CMMD__CLOSE						"CLOSE"
#define MFC_CMMD__CONTROL					"CONTROL"
#define MFC_CMMD__PURGE_LINE_OPEN			"GAS_LINE_PURGE"
#define MFC_CMMD__PURGE_MFC_OPEN			"CHM_LINE_PURGE"
#define MFC_CMMD__PURGE_MFC_FLOW			"PURGE"

#define GAS_CMMD__ALL_CLOSE					"ALL_CLOSE"
#define GAS_CMMD__GAS_LINE_PURGE			"GAS_LINE_PURGE"
#define GAS_CMMD__CHM_LINE_PURGE			"CHM_LINE_PURGE"
#define GAS_CMMD__LINE_PURGE_WITH_N2		"LINE_PURGE_WITH_N2"
#define GAS_CMMD__PROC_OPEN					"PROC_OPEN"
#define GAS_CMMD__CLOSE_N2_PURGE			"CLOSE_N2_PURGE"

#define FRC_CMMD__ALL_CLOSE					"ALL_CLOSE"
#define FRC_CMMD__CONTROL_CFG				"CONTROL.CFG"
#define FRC_CMMD__GASLINE_PUMP				"GASLINE_PUMP"

#define DGF_CMMD__ALL_CLOSE					"ALL_CLOSE"
#define DGF_CMMD__CONTROL					"CONTROL"


// ...
int CObj__GAS_VLV_FNC::Call__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	int i;

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Dislink__UPPER_OBJECT();
	}
	pOBJ_CTRL__GAS->Dislink__UPPER_OBJECT();

	// ...
	int flag = Fnc__ALL_CLOSE(p_variable);

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Link__UPPER_OBJECT();
	}
	pOBJ_CTRL__GAS->Link__UPPER_OBJECT();

	return flag;
}
int CObj__GAS_VLV_FNC::Fnc__ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	int i;

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
	}

	// OBJ.FRC ...
	{
		for(i=0; i<iFRC_SIZE; i++)
		{
			pOBJ_CTRL__FRC_X[i]->Run__OBJECT(FRC_CMMD__ALL_CLOSE);
		}
		for(i=0; i<iFRC_SIZE; i++)
		{
			pOBJ_CTRL__FRC_X[i]->When__OBJECT();
		}
	}
	// OBJ.DGF ...
	if(bActive__DGF_VLV)
	{
		pOBJ_CTRL__DGF_VLV->Call__OBJECT(DGF_CMMD__ALL_CLOSE);
	}

	return pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE);
}

int CObj__GAS_VLV_FNC::Call__MFC_ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	int i;

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Dislink__UPPER_OBJECT();
	}
	pOBJ_CTRL__GAS->Dislink__UPPER_OBJECT();

	int flag = Fnc__MFC_ALL_CLOSE(p_variable);

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Link__UPPER_OBJECT();
	}
	pOBJ_CTRL__GAS->Link__UPPER_OBJECT();

	return flag;
}
int CObj__GAS_VLV_FNC::Fnc__MFC_ALL_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	int i;

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
	}

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->When__OBJECT();
	}
	return 1;
}

int CObj__GAS_VLV_FNC::Call__PROC_READY(CII_OBJECT__VARIABLE *p_variable)
{
	if(dCH__OBJ_CTRL->Check__DATA("ABORT") > 0)
	{
		dCH__OBJ_CTRL->Set__DATA("ABORTED");
	}

	//
	pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE);

	// ...
	int i;

	// OBJ.MFC ...
	{
		for(i=0; i<iMFC_SIZE; i++)
		{
			pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
		}
	}

	// OBJ.FRC ...
	{
		for(i=0; i<iFRC_SIZE; i++)
		{
			pOBJ_CTRL__FRC_X[i]->Run__OBJECT(FRC_CMMD__CONTROL_CFG);
		}
		
		for(i=0; i<iFRC_SIZE; i++)
		{
			pOBJ_CTRL__FRC_X[i]->When__OBJECT();
		}
	}
	// OBJ.DGF ...
	if(bActive__DGF_VLV)
	{
		pOBJ_CTRL__DGF_VLV->Call__OBJECT(DGF_CMMD__CONTROL);
	}

	pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__PROC_OPEN);
	return 1;
}

//
int CObj__GAS_VLV_FNC::Call__SV_OPEN(CII_OBJECT__VARIABLE *p_variable)
{
	return pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__SV_OPEN);
}
int CObj__GAS_VLV_FNC::Call__SV_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	return pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__SV_CLOSE);
}

//
int CObj__GAS_VLV_FNC::Call__FV_OPEN(CII_OBJECT__VARIABLE *p_variable)
{
	return pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__FV_OPEN);
}
int CObj__GAS_VLV_FNC::Call__FV_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	return pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__FV_CLOSE);
}

//
int CObj__GAS_VLV_FNC::Call__MFC_CONTROL(CII_OBJECT__VARIABLE *p_variable)
{
	CString var_data;
	int db_index;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Call__MFC_CONTROL() ... \n";

		log_bff.Format(" %s <- %s \n", 
						dCH__PARA_MFC_TYPE->Get__CHANNEL_NAME(),
						dCH__PARA_MFC_TYPE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" %s <- %s \n", 
						aCH__PARA_MFC_FLOW->Get__CHANNEL_NAME(),
						aCH__PARA_MFC_FLOW->Get__STRING());
		log_msg += log_bff;

		printf(log_msg);
	}

	// 1. MFC Number READ
	{
		dCH__PARA_MFC_TYPE->Get__DATA(var_data);
		db_index = Get__MFC_INDEX(var_data);	

		if(db_index < 0)	return OBJ_ABORT;
	}

	// 2. Shutoff OPEN, FRC Control
	{
		pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__PROC_OPEN);

		// FRC ...
		for(int i=0; i<iFRC_SIZE; i++)
		{
			pOBJ_CTRL__FRC_X[i]->Call__OBJECT(FRC_CMMD__CONTROL_CFG);
		}

		// DGF ...
		if(bActive__DGF_VLV)
		{
			pOBJ_CTRL__DGF_VLV->Call__OBJECT(DGF_CMMD__CONTROL);
		}
	}

	// 3. MFC Setting ...
	{
		aCH__PARA_MFC_FLOW->Get__DATA(var_data);
		aEXT_CH__PARA_SET_FLOW[db_index]->Set__DATA(var_data);
	}

	return pOBJ_CTRL__MFC[db_index]->Call__OBJECT(MFC_CMMD__CONTROL);
}

int CObj__GAS_VLV_FNC::Call__MFC_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	CString var_data;
	int db_index;

	// 1. MFC Number READ
	{
		dCH__PARA_MFC_TYPE->Get__DATA(var_data);
	
		db_index = Get__MFC_INDEX(var_data);	
		if(db_index < 0)		return OBJ_ABORT;
	}

	return pOBJ_CTRL__MFC[db_index]->Call__OBJECT(MFC_CMMD__CLOSE);
}

// 
int CObj__GAS_VLV_FNC::Call__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	Fnc__ALL_CLOSE(p_variable);

	int r_flag = Fnc__GAS_LINE_PURGE(p_variable);

	Call__PROC_READY(p_variable);
	return r_flag;
}
int CObj__GAS_VLV_FNC::Fnc__GAS_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	// 1. Gas Line Purge ...
	{
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__GAS_LINE_PURGE) < 0)
		{
			return -11;
		}
	}

	// 2. Only MFC N2 Purge Valve OPEN, MFC CLOSE
	if(dCH__PARA_PURGE_TEST_MODE->Check__DATA(STR__ALL) > 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		CString var_data;

		aCH__PARA_PURGE_DELAY_SEC->Get__DATA(var_data);
		double cfg_sec = atof(var_data);

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(aCH__CUR_PURGE_DELAY_SEC->Get__CHANNEL_NAME());

		//
		for(int i=0; i<iMFC_SIZE; i++)
		{
			if(dEXT_CH__CFG_MFC_USE[i]->Check__DATA(STR__YES) < 0)
			{
				continue;
			}

			pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__PURGE_LINE_OPEN);
		}

		// ...
		x_timer_ctrl->INIT__COUNT_UP();

		if(x_timer_ctrl->WAIT(cfg_sec) < 0)
		{
			return -1;
		}
	}
	else
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		CString var_data;

		aCH__PARA_PURGE_DELAY_SEC->Get__DATA(var_data);
		double cfg_sec = atof(var_data);

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(aCH__CUR_PURGE_DELAY_SEC->Get__CHANNEL_NAME());

		//
		for(int i=0; i<iMFC_SIZE; i++)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if(dEXT_CH__CFG_MFC_USE[i]->Check__DATA(STR__YES) < 0)
			{
				continue;
			}

			int exit_flag = -1;

			dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__DATA(var_data);

			if(var_data.CompareNoCase(STR__ALL) != 0)
			{
				int gas_index = Get__MFC_INDEX(var_data);
				if(i != gas_index)		continue;

				exit_flag = 1;
			}

			pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__PURGE_LINE_OPEN);

			// ...
			x_timer_ctrl->INIT__COUNT_UP();

			if(x_timer_ctrl->WAIT(cfg_sec) < 0)
			{
				return -1;
			}

			pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__CLOSE);

			if(exit_flag > 0)
			{
				break;
			}
		}
	}

	return 1;
}

int CObj__GAS_VLV_FNC::Call__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	Fnc__ALL_CLOSE(p_variable);

	int r_flag = Fnc__CHM_LINE_PURGE(p_variable);

	Call__PROC_READY(p_variable);
	return r_flag;
}
int CObj__GAS_VLV_FNC::Fnc__CHM_LINE_PURGE(CII_OBJECT__VARIABLE *p_variable)
{
	// 1. Chamber Line Purge ...
	{
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__CHM_LINE_PURGE) < 0)
		{
			return -11;
		}
	}

	// 2. Only MFC Secondary Valve OPEN, MFC CLOSE ...
	if(dCH__PARA_PURGE_TEST_MODE->Check__DATA(STR__ALL) > 0)
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		CString var_data;

		aCH__PARA_PURGE_DELAY_SEC->Get__DATA(var_data);
		double cfg_sec = atof(var_data);

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(aCH__CUR_PURGE_DELAY_SEC->Get__CHANNEL_NAME());

		//
		for(int i=0; i<iMFC_SIZE; i++)
		{
			if(dEXT_CH__CFG_MFC_USE[i]->Check__DATA(STR__YES) < 0)
			{
				continue;
			}

			pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__PURGE_MFC_OPEN);
		}

		// ...
		x_timer_ctrl->INIT__COUNT_UP();

		if(x_timer_ctrl->WAIT(cfg_sec) < 0)
		{
			return -1;
		}
	}
	else
	{
		SCX__TIMER_CTRL x_timer_ctrl;
		CString var_data;

		aCH__PARA_PURGE_DELAY_SEC->Get__DATA(var_data);
		double cfg_sec = atof(var_data);

		x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);
		x_timer_ctrl->REGISTER__COUNT_CHANNEL(aCH__CUR_PURGE_DELAY_SEC->Get__CHANNEL_NAME());

		//
		for(int i=0; i<iMFC_SIZE; i++)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return -11;
			}

			if(dEXT_CH__CFG_MFC_USE[i]->Check__DATA(STR__YES) < 0)
			{
				continue;
			}

			// ...
			int exit_flag = -1;

			dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__DATA(var_data);

			if(var_data.CompareNoCase(STR__ALL) != 0)
			{
				int gas_index = Get__MFC_INDEX(var_data);
				if(i != gas_index)		continue;

				exit_flag = 1;
			}

			pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__PURGE_MFC_OPEN);

			// ...
			x_timer_ctrl->INIT__COUNT_UP();

			if(x_timer_ctrl->WAIT(cfg_sec) < 0)
			{
				return -1;
			}

			pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__CLOSE);

			if(exit_flag > 0)
			{
				break;
			}
		}
	}

	return 1;
}

//
int CObj__GAS_VLV_FNC::Call__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable)
{
	Fnc__ALL_CLOSE(p_variable);

	int r_flag = Fnc__LINE_PURGE_WITH_N2(p_variable);

	Call__PROC_READY(p_variable);
	return r_flag;
}
int CObj__GAS_VLV_FNC::Fnc__LINE_PURGE_WITH_N2(CII_OBJECT__VARIABLE *p_variable)
{
	SCX__TIMER_CTRL x_timer_flow;
	CString var_data;
	int i;

	// FLOW
	x_timer_flow->INIT__COUNT_DOWN();
	x_timer_flow->REGISTER__ABORT_OBJECT(sObject_Name);
	x_timer_flow->REGISTER__COUNT_CHANNEL(aCH__CUR_N2_FLOW_TIME->Get__CHANNEL_NAME());

	// 3. Purge Cycle Count READ
	aCH__PARA_PURGE_CYCLE_COUNT->Get__DATA(var_data);
	aCH__CUR_PURGE_CYCLE_COUNT->Set__DATA(var_data);

	// 4. MFC Flushing
	int cycle_count;

	do
	{
		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		// N2-Purge Line Pumping
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__LINE_PURGE_WITH_N2) < 0)
		{
			return -2;
		}

		// 5. MFC Open, During Parameter Config
		if(dCH__PARA_PURGE_TEST_MODE->Check__DATA(STR__ALL) > 0)
		{
			for(i=0; i<iMFC_SIZE; i++)
			{
				if(dEXT_CH__CFG_MFC_USE[i]->Check__DATA(STR__YES) < 0)
				{
					continue;
				}

				pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__PURGE_MFC_FLOW);
			}

			aCH__PARA_N2_FLOW_TIME->Get__DATA(var_data);
			
			if(x_timer_flow->WAIT(atoi(var_data)) < 0)
			{
				return -3;
			}
		}
		else
		{
			for(i=0; i<iMFC_SIZE; i++)
			{
				pOBJ_CTRL__MFC[i]->Call__OBJECT(MFC_CMMD__CLOSE);

				// ...
				int exit_flag = -1;
				int gas_index = -1;

				dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__DATA(var_data);

				if(var_data.CompareNoCase(STR__ALL) != 0)
				{
					gas_index = Get__MFC_INDEX(var_data);
					if(i != gas_index)		continue;

					exit_flag = 1;
				}
				else
				{
					gas_index = i;
				}

				// ...
				{
					CString log_msg;
					CString log_bff;

					log_msg = "\n";
					log_bff.Format("%s <- %s \n",
									dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__CHANNEL_NAME(),
									dCH__PARA_SINGLE_TEST_GAS_TYPE->Get__STRING());
					log_msg += log_bff;
					log_bff.Format("gas_index <- %1d \n", gas_index);

					log_msg += log_bff;
					xLOG_CTRL->WRITE__LOG(log_msg);
				}
	
				if(gas_index >= 0)
				{
					if(pOBJ_CTRL__MFC[gas_index]->Call__OBJECT(MFC_CMMD__PURGE_MFC_FLOW) < 0)
					{
						return -101;
					}

					// ...
					double cfg_sec = aCH__PARA_N2_FLOW_TIME->Get__VALUE();

					x_timer_flow->INIT__COUNT_UP();

					if(x_timer_flow->WAIT(cfg_sec) < 0)
					{
						return -1;
					}

					pOBJ_CTRL__MFC[gas_index]->Call__OBJECT(MFC_CMMD__CLOSE);
				}

				if(exit_flag > 0)
				{
					break;
				}
			}
		}

		// 6. Close N2 & Purge Valve ...
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__CLOSE_N2_PURGE) < 0)
		{
			return -11;
		}

		// 7. MFC Close
		{
			for(i=0; i<iMFC_SIZE; i++)
			{
				pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
			}

			if(x_timer_flow->WAIT(2.0) < 0)
			{
				return -12;
			}
		}

		// 8. Purge Cycle Count decrease -1
		{
			aCH__CUR_PURGE_CYCLE_COUNT->Get__DATA(var_data);
			cycle_count = atoi(var_data) - 1;
			var_data.Format("%1d",cycle_count);
			aCH__CUR_PURGE_CYCLE_COUNT->Set__DATA(var_data);
		}
	}
	while(cycle_count > 0);

	return 1;
}


// Chamber Ballast Flow Control ...
int CObj__GAS_VLV_FNC::Call__CHM_BALLAST_FLOW(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;

	int db_index;
	int i;

	// ...
	{
		log_msg  = "\n";
		log_msg += " * Ballast.Chamber Parameter ... \n";

		log_bff.Format(" * %s <- %s \n",
						dCH__CFG_CHAMBER_BALLAST_GAS_ID->Get__CHANNEL_NAME(),
						dCH__CFG_CHAMBER_BALLAST_GAS_ID->Get__STRING());
		log_msg += log_bff;
		
		Fnc__WRITE_LOG(log_msg);
	}

	// Ballast Gas Select ...
	if(dCH__CFG_CHAMBER_BALLAST_GAS_ID->Check__DATA("N2.Ballast") > 0)
	{
		// A. N2(V8) Transfer Valve Select
		// A-1. Gas Line Valve All Close
		// A-2. FRC Close
		// A-3. Transfer Valve Open

		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE) < 0)			return -11;
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__SV_OPEN)   < 0)			return -12;
	}
	else
	{
		// B. MFC Select ...
		// B-1. MFC All Close
		// B-2. Gas Line Valve All Close
		// B-3. Shut-off Valve Open
		// B-4. DGF Control
		// B-5. MFC Gas Flow

		for(i=0; i<iMFC_SIZE; i++)
		{
			pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
		}

		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE) < 0)			return -21;
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__PROC_OPEN) < 0)			return -22;

		for(i=0; i<iFRC_SIZE; i++)
		{
			if(pOBJ_CTRL__FRC_X[i]->Call__OBJECT(FRC_CMMD__CONTROL_CFG) < 0)
			{
				return -231;
			}
		}

		// ...
		{
			ch_data = dCH__CFG_CHAMBER_BALLAST_GAS_ID->Get__STRING();
			db_index = Get__MFC_INDEX(ch_data);	
			if(db_index < 0)												return -24;

			aCH__CFG_CHAMBER_BALLAST_GAS_FLOW->Get__DATA(ch_data);
			aEXT_CH__PARA_SET_FLOW[db_index]->Set__DATA(ch_data);
		}

		if(pOBJ_CTRL__MFC[db_index]->Call__OBJECT(MFC_CMMD__CONTROL) < 0)	return -25;
	}

	return 1;
}

// ... Transfer Ballast Flow Control ...
int CObj__GAS_VLV_FNC::Call__TRANS_BALLAST_FLOW(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;

	int db_index;
	int i;

	// ...
	{
		log_msg = "\n";
		log_msg = " * Ballast.Transfer Parameter ... \n";

		log_bff.Format(" * %s <- %s ", 
						dCH__CFG_TRANSFER_BALLAST_GAS_ID->Get__CHANNEL_NAME(),
						dCH__CFG_TRANSFER_BALLAST_GAS_ID->Get__STRING());
		log_msg += log_bff;
	
		Fnc__WRITE_LOG(log_msg);
	}

	// Ballast Gas Select ...
	if(dCH__CFG_TRANSFER_BALLAST_GAS_ID->Check__DATA(STR__N2_Ballast) > 0)
	{
		// A. N2(V8) Transfer Valve Select
		// A-1. MFC All Close
		// A-2. Gas Line Valve All Close
		// A-3. DGF Close
		// A-4. Transfer Valve Open

		for(i=0; i<iMFC_SIZE; i++)
		{
			pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
		}

		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE) < 0)			return -11;
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__SV_OPEN) < 0)				return -12;

		for(i=0; i<iFRC_SIZE; i++)
		{
			if(pOBJ_CTRL__FRC_X[i]->Call__OBJECT(FRC_CMMD__GASLINE_PUMP) < 0)
			{
				return -13;
			}
		}
	}
	else
	{
		// B. MFC Select ...
		// B-1. MFC All Close
		// B-2. Gas Line Valve All Close
		// B-3. Shut-off Valve Open
		// B-4. DGF Control
		// B-5. MFC Gas Flow

		for(i=0; i<iMFC_SIZE; i++)
		{
			pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
		}

		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE) < 0)			return -21;
		if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__PROC_OPEN) < 0)			return -22;
		
		for(i=0; i<iFRC_SIZE; i++)
		{
			if(pOBJ_CTRL__FRC_X[i]->Call__OBJECT(FRC_CMMD__CONTROL_CFG) < 0)
			{
				return -231;
			}
		}

		ch_data = dCH__CFG_TRANSFER_BALLAST_GAS_ID->Get__STRING();
		db_index = Get__MFC_INDEX(ch_data);	
		if(db_index < 0)													return -24;

		aCH__CFG_TRANSFER_BALLAST_GAS_FLOW->Get__DATA(ch_data);
		aEXT_CH__PARA_SET_FLOW[db_index]->Set__DATA(ch_data);

		if(pOBJ_CTRL__MFC[db_index]->Call__OBJECT(MFC_CMMD__CONTROL) < 0)	return -25;
	}

	return 1;
}

// ...
int CObj__GAS_VLV_FNC::Call__BALLAST_CLOSE(CII_OBJECT__VARIABLE *p_variable)
{
	int i;

	// 1. MFC All Close
	// 2. Gas Line Valve All Close
	// 3. Shut-off Valve Open
	// 4. DGF Control

	for(i=0; i<iMFC_SIZE; i++)
	{
		pOBJ_CTRL__MFC[i]->Run__OBJECT(MFC_CMMD__CLOSE);
	}

	if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__ALL_CLOSE) < 0)				return -21;
	if(pOBJ_CTRL__GAS->Call__OBJECT(GAS_CMMD__PROC_OPEN) < 0)				return -22;
	
	for(i=0; i<iFRC_SIZE; i++)
	{
		if(pOBJ_CTRL__FRC_X[i]->Call__OBJECT(FRC_CMMD__CONTROL_CFG) < 0)
		{
			return -23;
		}
	}

	return OBJ_AVAILABLE;
}
