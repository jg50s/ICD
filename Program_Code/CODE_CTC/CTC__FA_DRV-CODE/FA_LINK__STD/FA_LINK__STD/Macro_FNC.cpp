#include "StdAfx.h"
#include "Macro_FNC.h"


void Macro__Get_ERRTEXT_From_ERRCODE(const int errcode,CString& errtext)
{
	switch(errcode)
	{
		case 0:
			errtext = "No error";
			break;

		case 1:
			errtext = "Unknown object in Object Specifier";
			break;

		case 2:
			errtext = "Unknown target object type";
			break;

		case 3:
			errtext = "Unknown object instance";
			break;

		case 4:
			errtext = "Unknown attribute name";
			break;

		case 5:
			errtext = "Ready-only attribute - access denied";
			break;

		case 6:
			errtext = "Unknown object type";
			break;

		case 7:
			errtext = "Invalid attribute value";
			break;

		case 8:
			errtext = "Syntax error";
			break;

		case 9:
			errtext = "Verification error";
			break;

		case 10:
			errtext = "Validation error";
			break;

		case 11:
			errtext = "Object identifier in use";
			break;

		case 12:
			errtext = "Parameters improperly specified";
			break;

		case 13:
			errtext = "Insufficient parameters specified";
			break;

		case 14:
			errtext = "Unsupported option requested";
			break;

		case 15:
			errtext = "Busy";
			break;

		case 16:
			errtext = "Not available for processing";
			break;

		case 17:
			errtext = "Command not valid for current state";
			break;

		case 18:
			errtext = "No material altered";
			break;

		case 19:
			errtext = "Material partially processed";
			break;

		case 20:
			errtext = "All material processed";
			break;

		case 21:
			errtext = "Recipe specification related error";
			break;

		case 22:
			errtext = "Failed during processing";
			break;

		case 23:
			errtext = "Failed while not processing";
			break;

		case 24:
			errtext = "Failed dut to lack of material";
			break;

		case 25:
			errtext = "Job aborted";
			break;

		case 26:
			errtext = "Job stopped";
			break;

		case 27:
			errtext = "Job cancelled";
			break;

		case 28:
			errtext = "Cannot change selected recipe";
			break;

		case 29:
			errtext = "Unknown event";
			break;

		case 30:
			errtext = "Duplicate report ID";
			break;

		case 31:
			errtext	= "Unknown data report";
			break;

		case 32:
			errtext = "Data report not linked";
			break;

		case 33:
			errtext = "Unknown trace report";
			break;

		case 34:
			errtext = "Duplicate trace ID";
			break;

		case 35:
			errtext = "Too many data reports";
			break;

		case 36:
			errtext = "Sample period out of range";
			break;

		case 37:
			errtext = "Group size to large";
			break;

		case 38:
			errtext = "Recovery action currently invalid";
			break;

		case 39:
			errtext = "Busy with another recovery currently unable to perform the recovery";
			break;

		case 40:
			errtext = "No active recovery action";
			break;

		case 41:
			errtext = "Exception recovery failed";
			break;

		case 42:
			errtext = "Exception recovery aborted";
			break;

		case 43:
			errtext = "Invalid table element";
			break;

		case 44:
			errtext = "Unknown table element";
			break;

		case 45:
			errtext = "Cannot delete predefined";
			break;

		case 46:
			errtext = "Invalid token";
			break;

		case 47:
			errtext = "Invalid parameter";
			break;

		case 48:
			errtext = "Load port does not exist";
			break;

		case 49:
			errtext = "Load port already in use";
			break;

		case 50:
			errtext = "Missing Carrier";
			break;

		default:
			errtext.Format("Unknown Error Code : %1d",errcode);
			break;
	}
}

extern CString Macro__Get_Date_Time()
{
	CTime   t = CTime::GetCurrentTime();
	CString date_time;

	date_time.Format("%00004d_%002d_%002d %002d:%002d:%002d",
					 t.GetYear(),t.GetMonth(),t.GetDay(),
					 t.GetHour(),t.GetMinute(),t.GetSecond());

	return date_time;
}

extern int Macro__Make_File_Data(const CString& file_path, 
								 const CString& file_data,
								 const bool open_mode)
{
	CFile file_ctrl;

	int file_mode = CFile::modeWrite | CFile::modeCreate;
	if(open_mode)	file_mode |= CFile::modeNoTruncate;

	if(file_ctrl.Open(file_path, file_mode)) 
	{	
		file_ctrl.SeekToEnd();
		file_ctrl.Write(file_data, file_data.GetLength());
		file_ctrl.Close();
		return 1;
	}
	return -1;
}
