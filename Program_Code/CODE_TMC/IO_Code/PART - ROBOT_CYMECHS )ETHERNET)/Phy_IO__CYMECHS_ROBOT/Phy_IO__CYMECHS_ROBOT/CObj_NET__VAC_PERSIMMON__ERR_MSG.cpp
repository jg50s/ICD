#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"


//------------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON
::_Check__ERROR_CODE(const CString& err_code)
{
	int i_err = atoi(err_code);
	if(i_err > 0)
	{
		CString err_msg = _Get__Error_Msg_Of_Error_Code(i_err, err_code);

		mMNG__ERR_CODE.Load__Error_Code(err_code, err_msg);
		return 1;
	}
	return -1;
}
CString CObj_NET__VAC_PERSIMMON
::_Get__Error_Msg_Of_Error_Code(const int err_code,
							    const CString& err_xxxx)
{
	CString err_msg;
	CString err_name;
	CString err_ment;
	CString err_act_;

	err_msg.Format("Error_Code : %1d (0x%02X)", err_code,err_code);
	err_msg += "\n";

	if(_Get__Error_Msg_Info(err_code, err_name,err_ment,err_act_) > 0)
	{
		err_msg += err_name;
		err_msg += "\n";
		err_msg += err_ment;
		err_msg += "\n";
		err_msg += err_act_;
		err_msg += "\n";
	}
	return err_msg;
}
int CObj_NET__VAC_PERSIMMON
::_Get__Error_Msg_Info(const int err_code,
					   CString& err_name,
					   CString& err_ment,
					   CString& err_act_)
{
	// ...
	{
		err_name = "Name    : ";
		err_ment = "Comment : ";
		err_act_ = "Action  : ";
	}

	switch(err_code)
	{
		case 210:
			err_name  = "ERR_NOTSTATION";
			
			err_ment  = "\"Not at station\"";
			err_ment += "\n";
			err_ment += "Robot is not at station.";

			err_act_  = "Check if the command is correct or not";
			break;

		case 220:
			err_name  = "ERR_NOTRETRACTED";
			err_ment  = "\"Not retracted\" Arm is not retracted";
			err_act_  = "Check if robot is retracted or not";
			break;

		case 221:
			err_name  = "ERR_NOACTIVEARM";
			err_ment  = "\"No active arm\" Wrong arm seleted for excution";
			err_act_  = "Check if arm is selected correctly or not";
			break;
			
		case 233:
			err_name  = "ERR_HANDSHAKE";			

			err_ment  = "\"Handshake\" Check extend interlock.";
			err_ment += "\n";
			err_ment += "Check if slit valve is functioning properly.";
			
			err_act_  = "1. Check extend_enable interlock";
			err_act_  = "\n";
			err_act_ += "2. Check Slit valve";
			break;

		case 305:
			err_name  = "ERR_SYNTAXERROR";
			err_ment  = "\"Syntax error\" Command not typed correctly";
			err_act_  = "Check command is typed correctly";
			break;

		case 309:
			err_name  = "ERR_NOTIMPLEMENTED";
			err_ment  = "\"Not implemented\" Error that was not implemented or created";
			err_act_  = "Check command exists or not";
			break;

		case 352:
			err_name  = "ERR_NOMEMORY";
			err_ment  = "\"No memory\" Memory is not enough";
			err_act_  = "Check memory(occuping too much memory space)";
			break;

		case 443:
			err_name  = "ERR_STNINVALID";
			err_ment  = "\"Invalid station\" Station is not defined or created.";
			err_act_  = "Check if the station has been set or not";
			break;
				
		case 450:
			err_name  = "ERR_STNOUTOFRANGE";
			err_ment  = "Station Coordinate change larger than the defined limit";
			err_act_  = "Check moving range is out of station coordinate";
			break;
				
		case 451:
			err_name  = "ERR_APSCORROVERLIMIT";
			
			err_ment  = "\"APS correction over limit\"";
			err_ment += "\n";
			err_ment += "Wafer is out of maximun correct (5mm).";
			err_ment += "\n";
			err_ment += "Check if wafer is broken or slided on EE.";
			err_ment += "\n";
			err_ment += "Try to recalibrate APS if wafer is centered on EE.";

			err_act_  = "1. Check if wafer is borken or slided on EE";
			err_act_  = "\n";
			err_act_ += "2. Recheck APS data for the following wafers";
			break;
			
		case 509:
			err_name  = "ERR_ZLESS";

			err_ment  = "\"Z-Less Robot\"";
			err_ment += "\n";
			err_ment += "Please contact to Persimmon.";

			err_act_  = "Please, backup log & contact Persimmon";
			break;
				
		case 527:
			err_name  = "ERR_COMMINTERNALERROR";
			err_ment  = "\"Internal error in communication\"";
			err_act_  = "Please, backup log & contact Persimmon";
			break;
				
		case 528:
			err_name  = "ERR_BUFFFULL";
			
			err_ment  = "\"Buff full\"";
			err_ment += "\n";
			err_ment  = "Bull is full so need memory refresh";
			
			err_act_  = "Please, backup log & contact Persimmon";
			break;
			
		case 558:
			err_name  = "ERR_UNKNOWN";
			
			err_ment  = "\"Unknown\"";
			err_ment += "\n";
			err_ment += "Error that was not defined";
			
			err_act_  = "Check if it keeps happening, if so please contact Persimmon";
			break;
				
		case 602:
			err_name  = "ERR_RESOURCEBUSY";

			err_ment  = "\"Resource busy\"";
			err_ment += "\n";
			err_ment += "Commnad is under implementation.";
			err_ment += "\n";
			err_ment += "Please wait until previous command is completed.";
			
			err_act_  = "Please wait until previous command is completed.";
			break;
				
		case 607:
			err_name  = "ERR_COMMTIMEOUT";
			err_ment  = "\"Communication timeout\"";	
			
			err_act_  = "Reset controller first,";
			err_act_  = "\n";
			err_act_ += "if it keeps happening, please contact Persimmon";
			break;
				
		case 608:
			err_name  = "ERR_TRJABORTED";
			err_ment  = "\"Trajectory aborted by user command\"";
			err_act_  = "Check if abort command has been issued from Host";
			break;
				
		case 658:
			err_name  = "ERR_HWOFFLINE";

			err_ment  = "\"HW is offline\"";
			err_ment += "\n";
			err_ment += "Command configuration is wrong.";
			err_ment += "\n";
			err_ment += "Please contact to Persimmon.";
			
			err_act_  = "Please contact to Persimmon.";
			break;
				
		case 705:
			err_name  = "ERR_PAYLOADMISSING";
			
			err_ment += "\"Payload missing\"";
			err_ment += "\n";
			err_ment += "Wafer is not detected.";
			err_ment += "\n";
			err_ment += "Check if wafer is on EE";
			
			err_act_  = "Check if wafer is on EE";
			break;
				
		case 706:
			err_name  = "ERR_PAYLOADPRESENT";

			err_ment  = "\"Payload present\"";
			err_ment += "\n";
			err_ment += "Wafer is on End effector.";
			
			err_act_  = "Check if wafer is on EE";
			break;
				
		case 770:
			err_name  = "ERR_APSUNKNOWNSENSOR";

			err_ment  = "\"APS unknown sensor\"";
			err_ment += "\n";
			err_ment += "Check if APS sensor is working.";
			err_ment += "\n";
			err_ment += "Check if APS sensor was calibrated properly per procedure.";
			
			err_act_  = "1. Check if APS sensor is working";
			err_act_  = "\n";
			err_act_ += "2. Check if correct sensor is used";
			err_act_  = "\n";
			err_act_ += "3. Check if sensor is calibrated correctly";
			break;
				
		case 771:
			err_name  = "ERR_APSINVALIDCAPPOS";

			err_ment  = "\"APS invalid captured position\"";
			err_ment += "\n";
			err_ment += "Check is APS was calibrated properly.";
			
			err_act_  = "1. Check is APS was calibrated properly";
			err_act_  = "\n";
			err_act_ += "2. Check there is any loose ends on Sensors";
			break;
				
		case 772:
			err_name  = "ERR_APSWAFERBREAKAGE";

			err_ment  = "\"APS wafer breakage\"";
			err_ment += "\n";
			err_ment += "Out of APS breakage threshold(10 mm).";
			err_ment += "\n";
			err_ment += "Check if wafer is broken or slided on EE.";
			err_ment += "\n";
			err_ment += "Try to recalibrate APS if wafer is centered on EE.";
			
			err_act_  = "1. Check if wafer is broken or slided on EE.";
			err_act_  = "\n";
			err_act_ += "2. Check if sensor is calibrated correctly";
			break;

		case 773:
			err_name  = "ERR_APSTOOLARGEBURST";

			err_ment  = "\"Exceeded maximum length of the burst\"";
			err_ment += "\n";
			err_ment += "Please contact to Persimmon";
			
			err_act_  = "Please contact to Persimmon";
			break;
				
		case 774:
			err_name  = "ERR_APSINVALIDBURSTVALUE";

			err_ment  = "\"Invalid value of the burst - should be different to previous one\"";
			err_ment += "\n";
			err_ment += "Received two sequential IO transitions of the same state.";
			err_ment += "\n";
			err_ment += "Please check APS sensor hardware and configuration.";
			err_ment += "\n";
			err_ment += "Please try recalibrate APS sensor.";
			
			err_act_  = "1. Check if APS was calibrated correctly";
			err_act_  = "\n";
			err_act_ += "2. Check if sensors are correctly installed";
			err_act_  = "\n";
			err_act_ += "3. Check Sensor configuration";
			break;
			
		case 775:
			err_name  = "ERR_APSDISABLED";
			err_ment  = "\"Cannot use the disabled APS\"";	 
			err_act_  = "check if APS is disabled";
			break;
				
		case 776:
			err_name  = "ERR_APSCPTRPOSMISSING";

			err_ment  = "\"APS captured position is missing\"";
			err_ment += "\n";
			err_ment += "Check is one of APS sensor is blocked by any object.";
			err_ment += "\n";
			err_ment += "Check if wafer is broken or slided on EE.";
			err_ment += "\n";
			err_ment += "Try to recalibrate APS if wafer is centered on EE.";
			
			err_act_  = "1. Check is one of APS sensor is blocked by any object";
			err_act_  = "\n";
			err_act_ += "2. Check if wafer is broken or slided on EE";
			err_act_  = "\n";
			err_act_ += "3. Check Sensor hardware & configuration";
			break;
				
		case 777:
			err_name  = "ERR_APSCORRITERSFAIL";

			err_ment  = "\"APS calculation failed\"";
			err_ment += "\n";
			err_ment += "Check if wafer is aligned on EE.";
			err_ment += "\n";
			err_ment += "Check if APS sensor is working.";

			err_act_  = "1. Check if wafer is aligned on EE";
			err_act_  = "\n";
			err_act_ += "2. Check Sensor hardware";
			break;
				
		case 778:
			err_name  = "ERR_APSSENSORNOTFOUND";

			err_ment  = "\"APS sensor not found\"";
			err_ment += "\n";
			err_ment += "Check if APS sensor is woking.";
			
			err_act_  = "1. Check if APS sensor is woking";
			err_act_  = "\n";
			err_act_ += "2. Check if sensor is installed correctly";
			break;
			
		case 821:
			err_name  = "ERR_COREOBJNOTEXISTS";

			err_ment  = "\"Requested core object not found\"";
			err_ment += "\n";
			err_ment += "Need log verification.";
			err_ment += "\n";
			err_ment += "Please contact to Persimmon";
			
			err_act_  = "Please contact to Persimmon";
			break;
				
		case 822:
			err_name  = "ERR_CONFIGINVALID";
			err_ment  = "\"Configuration not vaild\"";
			err_act_  = "Please check if configuration is set correctly";
			break;
			
		case 823:
			err_name  = "ERR_COREOBJDIFFTYPE";
			
			err_ment  = "\"Core object has a different type\"";
			err_ment += "\n";
			err_ment += "Need log verification.";
			err_ment += "\n";
			err_ment += "Please contact to Persimmon";
			
			err_act_  = "Please contact to Persimmon";
			break;
				
		case 830:
			err_name  = "ERR_NOTCONFIGURED";

			err_ment  = "\"Not configured\"";
			err_ment += "\n";
			err_ment += "Check if APS is calibrated.";
			
			err_act_  = "Check if APS is calibrated.";
			break;
				
		case 832:
			err_name  = "ERR_READONLY";
			err_ment  = "Read only, writing not supported";
			err_act_  = "Check if writing is allowed or not";
			break;
				
		case 838:
			err_name  = "ERR_PAR_IS_NOT_DEF";
			err_ment  = "\"Parameter is not defined\"";
			err_act_  = "Check if parameter is right";
			break;
				
		case 840:
			err_name  = "ERR_PAR_DIFFTYPE";
			err_ment  = "\"Parameter has a different type\"";
			err_act_  = "Check if parameter is a correct type or not";
			break;
			
		case 844:
			err_name  = "ERR_PARAMINVALID";
			err_ment  = "\"Parameter value not valid\"";
			err_act_  = "Check if parameter value is valid";
			break;
				
		case 951:
			err_name  = "ERR_EVENT_NOTFOUND";
			err_ment  = "\"Event object is not found\"";
			err_act_  = "Check if event is a correct type";
			break;
				
		case 952:
			err_name  = "ERR_EVENT_NOTSUPPORTED";
			err_ment  = "\"Event is not supported\"";
			err_act_  = "Check if event is supported or not";
			break;
				
		case 1101:
			err_name  = "ERR_TRJOUTOFSAFE";
			err_ment  = "\"Out of configured move range\"";
			err_act_  = "Check if the move range is out of range";
			break;
				
		case 1805:
			err_name  = "ERR_CTRLLOCKED";

			err_ment  = "\"Control locked\"";
			err_ment += "\n";
			err_ment += "Check if Teach Pendant is power On.";
			
			err_act_  = "Check if Teach Pendant is released or not";
			break;

		default:
			return -1;
	}

	return 1;
}
