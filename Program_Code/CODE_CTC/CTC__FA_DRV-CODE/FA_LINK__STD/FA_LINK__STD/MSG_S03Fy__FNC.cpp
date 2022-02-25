#include "stdafx.h"
#include "MSG_S03Fy.h"

#include "Macro_FNC.h"

#include "CRes__CHANNEL.h"
extern CRes__CHANNEL mRes__CHANNEL;


// ...
void CMsg_S03Fy::_Make__CMS_LOG(const CDS_CASSETTE_INFO& cst_info)
{
	SCX__SEQ_INFO  x_seq_info;

	CString dir_root;
	CString dir_log;

	x_seq_info->Get__DIR_ROOT(dir_root);
	
	dir_log  = dir_root;
	dir_log += "\\EQP_INF";
	dir_log += "\\OBJ-FA";
	x_seq_info->Create__DIR(dir_log);
	
	dir_log += "\\_E87_FILE";
	x_seq_info->Create__DIR(dir_log);

	CString log_path;
	log_path.Format("%s\\_CMS_LP%1d.txt", dir_log,cst_info.iPTN);

	// ...
	CString log_msg;
	CString log_bff;

	int k_limit;
	int k;

	//
	log_bff = "#CMS_INFO.START#\n";
	log_msg += log_bff;
	log_msg += "\n";

	// ...
	{
		log_bff.Format("#TIME.LOG=\"%s\"\n", Macro__Get_Date_Time());
		log_msg += log_bff;
		log_msg += "\n";

		log_bff.Format("#CARRIERACTION=\"%s\"\n", cst_info.sCARRIER_ACTION);
		log_msg += log_bff;

		log_bff.Format("#CARRIERID=\"%s\"\n", cst_info.sCARRIER_ID);
		log_msg += log_bff;
	
		log_bff.Format("#CAPACITY=\"%1d\"\n", cst_info.iCAPACITY);
		log_msg += log_bff;
	
		log_bff.Format("#SUBSTRATECOUNT=\"%1d\"\n", cst_info.iSUBSTRATE_COUNT);
		log_msg += log_bff;

		log_bff.Format("#USAGE=\"%s\"\n", cst_info.sUSAGE);
		log_msg += log_bff;

		log_msg += "\n";
	}

	//
	{
		k_limit = cst_info.sSLOTMAP_LIST.GetSize();

		for(k=0; k<k_limit; k++)
		{
			CString str_map;
			int i_map = atoi(cst_info.sSLOTMAP_LIST[k]);

			     if(i_map == 1)			str_map = "EMPTY"; 
			else if(i_map == 2)			str_map = "NOT EMPTY";
			else if(i_map == 3)			str_map = "CORRECTLY OCCUPIED";
			else if(i_map == 4)			str_map = "DOUBLE SLOTTED";
			else if(i_map == 5)			str_map = "CROSS SLOTTED";
			else						str_map = "UNDEFINED";

			log_bff.Format("#SLOT.%02d=\"%s\"\n", k+1,str_map);
			log_msg += log_bff;
		}

		if(k_limit > 0)			log_msg += "\n";
	}

	//
	{
		k_limit = cst_info.sLOTID_LIST.GetSize();

		for(k=0; k<k_limit; k++)
		{
			log_bff.Format("#LOTID.%02d=\"%s\"\n", k+1,cst_info.sLOTID_LIST[k]);
			log_msg += log_bff;
		}

		if(k_limit > 0)			log_msg += "\n";
	}

	//
	{
		k_limit = cst_info.sWAFERID_LIST.GetSize();

		for(k=0; k<k_limit; k++)
		{
			log_bff.Format("#WFRID.%02d=\"%s\"\n", k+1,cst_info.sWAFERID_LIST[k]);
			log_msg += log_bff;
		}

		if(k_limit > 0)			log_msg += "\n";
	}

	//
	{
		k_limit = cst_info.sWID_ANGLE_LIST.GetSize();

		for(k=0; k<k_limit; k++)
		{
			log_bff.Format("#ANGLE.%02d=\"%s\"\n", k+1,cst_info.sWID_ANGLE_LIST[k]);
			log_msg += log_bff;
		}

		if(k_limit > 0)			log_msg += "\n";
	}

	log_bff = "#CMS_INFO.END#\n";
	log_msg += log_bff;

	 Macro__Make_File_Data(log_path, log_msg, false);

	//
	mRes__CHANNEL.Set__CMS_Update_Flag_Of_LPx(cst_info.iPTN);
}
