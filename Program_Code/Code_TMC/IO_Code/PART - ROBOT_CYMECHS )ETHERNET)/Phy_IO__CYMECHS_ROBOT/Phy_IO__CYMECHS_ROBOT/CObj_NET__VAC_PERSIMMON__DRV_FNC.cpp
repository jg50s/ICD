#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"

#include "Macro_Function.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj_NET__VAC_PERSIMMON
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString str_cmmd;
	CStringArray l_rsp;
	CStringArray l_err;

	if(diCH__RB_STS_READ->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "RQ BG";

		read_data = "Unknown";

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, _TO__QUERY, TRUE, l_rsp,l_err) ;		
		if(r_flag > 0)
		{
			if(l_rsp.GetSize() > 1)
			{
				CString r_data = l_rsp[0];
				CString e_data = l_rsp[1];

					 if(r_data.CompareNoCase("Y") == 0)			read_data = "Busy";
				else if(r_data.CompareNoCase("N") == 0)			read_data = "Idle";

				sCH__DRV_RB_STS->Set__DATA(e_data);
				_Check__ERROR_CODE(e_data);
			}
		}
		return 1;
	}
	else if((diCH__ARM_A_READ->Check__VARIABLE_NAME(var_name) > 0)
	     || (diCH__ARM_B_READ->Check__VARIABLE_NAME(var_name) > 0))
	{
		if(diCH__ARM_A_READ->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = "RQ POS STN A R";
		}
		else
		{
			str_cmmd = "RQ POS STN B R";
		}

		read_data = "Unknown";

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, _TO__QUERY, TRUE, l_rsp,l_err) ;
		if(r_flag > 0)
		{
			if(l_rsp.GetSize() > 3)
			{
				CString r_data = l_rsp[3];

					 if(r_data.CompareNoCase("EX") == 0)		read_data = "Extended";
				else if(r_data.CompareNoCase("RE") == 0)		read_data = "Retracted";
			}
		}
		return 1;
	}
	else if((diCH__ARM_A_MAT_READ->Check__VARIABLE_NAME(var_name) > 0)
		 || (diCH__ARM_B_MAT_READ->Check__VARIABLE_NAME(var_name) > 0))
	{
		if(diCH__ARM_A_MAT_READ->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = "RQ LOAD A";
		}
		else
		{
			str_cmmd = "RQ LOAD B";
		}

		read_data = "Unknown";

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, _TO__QUERY, TRUE, l_rsp,l_err) ;
		if(r_flag > 0)
		{
			if(l_rsp.GetSize() > 2)
			{
				CString r_data = l_rsp[2];

				if((r_data.CompareNoCase("Y")  == 0)
				|| (r_data.CompareNoCase("ON") == 0))
				{
					read_data = "Present";
				}
				else if((r_data.CompareNoCase("N")   == 0)
					 || (r_data.CompareNoCase("OFF") == 0))
				{
					read_data = "Absent";
				}
				else
				{
					read_data = "Absent";
				}
			}
		}
		return 1;
	}

	return -1;
}

int CObj_NET__VAC_PERSIMMON
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str_cmmd;
	CStringArray l_rsp;
	CStringArray l_err;

	if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = "RQ VERSION";

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, _TO__QUERY, FALSE, l_rsp,l_err) ;
		if(r_flag < 0)		return -1;

		if(l_rsp.GetSize() > 0)
		{
			read_data = "";

			int i_limit = l_rsp.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				if(i > 0)		read_data += " ";

				read_data += l_rsp[i];
			}
		}
		else
		{
			read_data = "Unknown";
		}
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	if(aoCH_RO_OFFSET->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sRO_OFFSET.Format("%.f", set_data);
		return 1;
	}
	if(aoCH_TO_OFFSET->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sTO_OFFSET.Format("%.f", set_data);
		return 1;
	}

	if(aoCH_STN_R_VAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sSTN_R_SET_VAL.Format("%.f", set_data);
		return 1;
	}
	if(aoCH_STN_T_VAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sSTN_T_SET_VAL.Format("%.f", set_data);
		return -1;
	}

	return -1;
}

int CObj_NET__VAC_PERSIMMON
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString str_cmmd;
	CStringArray l_rsp;
	CStringArray l_err;

	if(doCH__COMMAND->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString str_action;
		CString para__stn_name;
		double  to_sec = 30;	// sec

		sCH__ACTION_STS->Get__DATA(str_action);
		dCH__OTR_IN_PARA__STN_NAME->Get__DATA(para__stn_name);

		// Command Check...
		if(set_data.CompareNoCase(_Cmmd__AGoto) == 0)
		{
			str_cmmd.Format("GOTO Robot1 N %s R %s Z %s SLOT %s ARM A", m_sStationA, m_sRPos, m_sZPos, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__AGoto_Offset) == 0)
		{
			str_cmmd.Format("GOTO Robot1 N %s R %s RO %s TO %s Z %s SLOT %s ARM A", m_sStationA, m_sRPos, m_sRO_OFFSET, m_sTO_OFFSET, m_sZPos, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BGoto) == 0)
		{
			str_cmmd.Format("GOTO Robot1 N %s R %s Z %s SLOT %s ARM B", m_sStationB, m_sRPos, m_sZPos, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BGoto_Offset) == 0)
		{
			str_cmmd.Format("GOTO Robot1 N %s R %s RO %s TO %s Z %s SLOT %s ARM B", m_sStationB, m_sRPos, m_sRO_OFFSET, m_sTO_OFFSET, m_sZPos, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APick_Act) == 0)
		{
			str_cmmd.Format("PICK Robot1  %s SLOT %s ARM A", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APick_Extend) == 0)
		{
			str_cmmd.Format("PICK Robot1  %s SLOT %s ARM A  ENRT NR", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APick_Retract) == 0)
		{
			str_cmmd.Format("PICK Robot1  %s SLOT %s ARM A  STRT NR", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPick_Act) == 0)
		{
			str_cmmd.Format("PICK Robot1 %s SLOT %s ARM B", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPick_Extend) == 0)
		{
			str_cmmd.Format("PICK Robot1 %s SLOT %s ARM B  ENRT NR", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPick_Retract) == 0)
		{
			str_cmmd.Format("PICK Robot1 %s SLOT %s ARM B  STRT NR", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APlace_Act) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM A", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APlace_Extend) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM A  ENRT NR", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APlace_Retract) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM A  STRT NR", m_sStationA, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPlace_Act) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM B", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPlace_Extend) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM B  ENRT NR", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPlace_Retract) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM B  STRT NR", m_sStationB, m_sSlot);
		}
		else if(set_data.CompareNoCase(_Cmmd__APlace_Offset) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM A RO %s TO %s", m_sStationA, m_sSlot, m_sRO_OFFSET, m_sTO_OFFSET);
		}
		else if(set_data.CompareNoCase(_Cmmd__BPlace_Offset) == 0)
		{
			str_cmmd.Format("PLACE Robot1 %s SLOT %s ARM B RO %s TO %s", m_sStationB, m_sSlot, m_sRO_OFFSET, m_sTO_OFFSET);
		}

		else if(set_data.CompareNoCase(_Cmmd__HomeAll) == 0)
		{
			str_cmmd = "HOME ALL";
		}
		else if(set_data.CompareNoCase(_Cmmd__HomeR) == 0)
		{
			str_cmmd = "HOME R";
		}
		else if(set_data.CompareNoCase(_Cmmd__Reset) == 0)
		{
			str_cmmd = "RESET";
		}
		else if(set_data.CompareNoCase(_Cmmd__LoadA) == 0)
		{
			str_cmmd = "SET LOAD robot1 ARM A ON";
		}
		else if(set_data.CompareNoCase(_Cmmd__LoadB) == 0)
		{
			str_cmmd = "SET LOAD robot1 ARM B ON";
		}
		else if(set_data.CompareNoCase(_Cmmd__UnloadA) == 0)
		{
			str_cmmd = "SET LOAD robot1 ARM A OFF";
		}
		else if(set_data.CompareNoCase(_Cmmd__UnloadB) == 0)
		{
			str_cmmd = "SET LOAD robot1 ARM B OFF";
		}
		else if(set_data.CompareNoCase(_Cmmd__ChkLoad) == 0)
		{
			str_cmmd.Format("CHECK LOAD INTLCK ALL DIS");
		}
		else if(set_data.CompareNoCase(_Cmmd__ChkLoadA) == 0)
		{
			str_cmmd.Format("CHECK LOAD A INTLCK ALL DIS");
		}
		else if(set_data.CompareNoCase(_Cmmd__ChkLoadB) == 0)
		{
			str_cmmd.Format("CHECK LOAD B INTLCK ALL DIS");
		}

		// DA ...
		else if(set_data.CompareNoCase(_Cmmd__ASet_Cptr_On) == 0)
		{
			str_cmmd.Format("SET CPTR robot1 %s ON", m_sCptr_StationA);
		}
		else if(set_data.CompareNoCase(_Cmmd__ASet_Cptr_Off) == 0)
		{
			str_cmmd.Format("SET CPTR robot1 %s OFF", m_sCptr_StationA);
		}
		else if(set_data.CompareNoCase(_Cmmd__BSet_Cptr_On) == 0)
		{
			str_cmmd.Format("SET CPTR robot1 %s ON", m_sCptr_StationB);
		}
		else if(set_data.CompareNoCase(_Cmmd__BSet_Cptr_Off) == 0)
		{
			str_cmmd.Format("SET CPTR robot1 %s OFF", m_sCptr_StationB);
		}
		else if(set_data.CompareNoCase(_Cmmd__AGet_Cptr) == 0)
		{
			str_cmmd.Format("RQ CPTR robot1 %s", m_sCptr_StationA);
		}
		else if(set_data.CompareNoCase(_Cmmd__BGet_Cptr) == 0)
		{
			str_cmmd.Format("RQ CPTR robot1 %s", m_sCptr_StationB);
		}
		else if(set_data.CompareNoCase(_Cmmd__Wfr_Cen_Data) == 0)
		{
			str_cmmd.Format("RQ WAF_CEN DATA robot1");
		}
		else if(set_data.CompareNoCase(_Cmmd__AGet_Current_Stn) == 0)
		{
			str_cmmd.Format("RQ STN %s A ALL", m_sStationA);
		}	
		else if(set_data.CompareNoCase(_Cmmd__BGet_Current_Stn) == 0)
		{
			str_cmmd.Format("RQ STN %s B ALL", m_sStationB);
		}
		else if(set_data.CompareNoCase(_Cmmd__ASet_Stn) == 0)
		{
			str_cmmd.Format("SET STN %s ARM A R %s T %s", m_sStationA, m_sSTN_R_SET_VAL, m_sSTN_T_SET_VAL);
		}
		else if(set_data.CompareNoCase(_Cmmd__BSet_Stn) == 0)
		{
			str_cmmd.Format("SET STN %s ARM B R %s T %s", m_sStationB, m_sSTN_R_SET_VAL, m_sSTN_T_SET_VAL);
		}
		else
		{
			CString log_msg;

			log_msg.Format("[%s] Unknown DATA Error \n", var_name);
			Fnc__DRV_LOG(log_msg);
			return -1;
		}

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, to_sec, TRUE, l_rsp,l_err) ;
		if(r_flag < 0)		return -1;

		if(l_rsp.GetSize() > 0)
		{
			CString rsp_data = Get__STRING_OF_LIST(l_rsp);

			if((set_data.CompareNoCase(_Cmmd__AGet_Cptr) == 0) 
			|| (set_data.CompareNoCase(_Cmmd__BGet_Cptr) == 0))
			{
				sCH__CPTR_SNS_FULL_VAL->Set__DATA(rsp_data);
			}
			else if((set_data.CompareNoCase(_Cmmd__AGet_Current_Stn) == 0) 
				 || (set_data.CompareNoCase(_Cmmd__BGet_Current_Stn) == 0))
			{
				sCH__RQ_STN_FULL_VAL->Set__DATA(rsp_data);
			}
			else if(set_data.CompareNoCase(_Cmmd__Wfr_Cen_Data) == 0)
			{
				sCH__WFR_CEN_DATA__FULL_VAL->Set__DATA(rsp_data);
			}
		}

		if(l_err.GetSize() > 0)
		{

		}
		return 1;
	}

	// edo.RB1.StnA 
	if(doCH__STN_A->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sStationA = set_data;
		return 1;
	}
	// edo.RB1.StnB 
	if(doCH__STN_B->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sStationB = set_data;
		return 1;
	}

	// edo.RB1.CPTR.StnA
	if(doCH__CPTR_STN_A->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sCptr_StationA = set_data;
		return 1;
	}
	// edo.RB1.CPTR.StnB
	if(doCH__CPTR_STN_B->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sCptr_StationB = set_data;
		return 1;
	}

	// edo.RB1.RPos
	if(doCH__RPOS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("Retract") == 0)		m_sRPos = "RE";
		else											m_sRPos = "EX";

		return 1;
	}

	// edo.RB1.ArmAMat
	if((doCH__ARM_A_MAT->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__ARM_B_MAT->Check__VARIABLE_NAME(var_name) > 0))
	{
		if(set_data.CompareNoCase("Absent") == 0)
		{
			str_cmmd.Format("SET LOAD A OFF");
		}
		else if(set_data.CompareNoCase("Present") == 0)
		{
			str_cmmd.Format("SET LOAD A ON");
		}
		else
		{
			str_cmmd.Format("SET LOAD A ?");
		}

		int r_flag = Proc__CMMD_RSP(var_name, str_cmmd, _TO__ACT, TRUE, l_rsp,l_err) ;
		if(r_flag < 0)		return -1;

		if(l_rsp.GetSize() > 0)
		{
			CString rsp_data = Get__STRING_OF_LIST(l_rsp);

			// ...
			{

			}
		}

		if(l_err.GetSize() > 0)
		{

		}
		return 1;
	}

	// edo.RB1.ZPos
	if(doCH__ZPOS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("Down") == 0)		m_sZPos = "DN";
		else										m_sZPos = "UP";

		return 1;
	}
	// edo.RB1.Slot
	if(doCH__SLOT->Check__VARIABLE_NAME(var_name) > 0)
	{
		m_sSlot = set_data;

		return 1;
	}
	// edo.RB1.WfrSns
	if(doCH__ARM_WFR_SNS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("Yes") == 0)		m_sWfrSnsIntlk = "Y";
		else										m_sWfrSnsIntlk = "N";

		return 1;
	}

	return -1;
}

int CObj_NET__VAC_PERSIMMON
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
