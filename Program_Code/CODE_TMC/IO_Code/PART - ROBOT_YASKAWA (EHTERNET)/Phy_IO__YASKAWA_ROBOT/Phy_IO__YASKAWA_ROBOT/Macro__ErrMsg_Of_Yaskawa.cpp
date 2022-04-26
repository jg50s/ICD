#include "StdAfx.h"
#include "CCommon_SYSTEM.h"


// ...
CString YASKAWA__Get_Error_Msg_Of_Error_Code(const int err_cxxx, 
											 const CString& err_mxx)
{
	CString err_level = "Level : ";
	CString err_name  = "Error Name  : ";
	CString err_commt = "Description : ";
	CString err_msg;

	int err_check = 1;
	int err_code = 0x0fff & err_cxxx;

	err_msg.Format("Error_Code : %1d (0x%02X)", err_code,err_code);
	err_msg += "\n";

	switch(err_code)
	{
		// Success Codes
		case 0x0:
			err_msg += "Command succeeded.";
			break;

		//=========================================================================
		case 0x020:
			err_level += "W2";
			err_name  += "Secondary power off";
			err_commt += "Motion command failed due to servo power off.";
			break;

		case 0x021:
			err_level += "W2";
			err_name  += "Secondary power on";
			err_commt += "Setting command failed due to servo power on.";
			break;

		case 0x040:
			err_level += "W2";
			err_name  += "In TEACH Mode";
			err_commt += "Command was rejected because host command was sent when the controller was in TEACH mode.";
			break;

		case 0x050:
			err_level += "W2";
			err_name  += "Unit is in motion";
			err_commt += "Command was rejected because a unit is executing a motion command when host sent another motion command to the same unit.";
			break;

		case 0x051:
			err_level += "W2";
			err_name  += "Unable to set pitch between slots";
			err_commt += "Host attempted to set pitch between slot when pitch generation method was set to \"automatic calculation mode\"";
			break;

		case 0x052:
			err_level += "W2";
			err_name  += "Unable to restart motion";
			err_commt += "RESTART command was rejected because immediately after power on	or the error occur.";
			break;

		case 0x053:
			err_level += "W2";
			err_name  += "Ready position move incomplete";
			err_commt += "Get/Put (or exchange) command was rejected because \"move to ready position\¡± command had not been executed before that.";
			break;
		
		case 0x055:
			err_level += "W2";
			err_name  += "Improper station type";
			err_commt += "Inaccessible station type is specified.";
			break;

		case 0x058:
			err_level += "W2";
			err_name  += "Command not supported 1-1";
			err_commt += "Command was rejected because the command sent is not supported by specified unit.";
			break;

		case 0x059:
			err_level += "W2";
			err_name  += "Invalid transfer point";
			err_commt += "\"Motion between Transfer Points\¡± command was rejected because an invalid point was specified.";
			break;

		case 0x05A:
			err_level += "W2";
			err_name  += "Linear motion failed";
			err_commt += "Cannot move since manipulator arm is in the range (or the posture) where linear motion cannot be executed.";
			break;

		case 0x05C:
			err_level += "W2";
			err_name  += "Unable to reference wafer alignment result";
			err_commt += "Wafer alignment had not been executed.";
			break;

		case 0x05d:
			err_level += "W2";
			err_name  += "Unable to perform arm calibration";
			err_commt += "Arm calibration was rejected because the pre-aligner stage has not been recorded.";
			break;

		case 0x05E:
			err_level += "W2";
			err_name  += "Unable to read mapping data";
			err_commt += "The mapping data reference command was rejected because the mapping has not been executed ever.";
			break;

		case 0x05F:
			err_level += "W2";
			err_name  += "Data Upload/Download in	progress";
			err_commt += "Command is rejected because data upload/download command was in	progress.";
			break;

		case 0x061:
			err_level += "W2";
			err_name  += "Unable to motion";
			err_commt += "Unable to home safely from current manipulator posture.";
			break;

		case 0x070:
			err_level += "W2";
			err_name  += "Bottom slot position record incomplete";
			err_commt += "Command was rejected because the bottom slot position had not been recorded.";
			break;

		case 0x071:
			err_level += "W2";
			err_name  += "Top slot position record incomplete";
			err_commt += "Command was rejected because the top slot position had not been recorded when pitch generation method was set to \¡°automatic calculation mode\¡±.";
			break;

		case 0x088:
			err_level += "W2";
			err_name  += "Position generating error 1";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x089:
			err_level += "W2";
			err_name  += "Position generating error 2";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x08A:
			err_level += "W2";
			err_name  += "Position generating error 3";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x08b:
			err_level += "W2";
			err_name  += "Position generating error 4";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x08C:
			err_level += "W2";
			err_name  += "Position generating error 5";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x08d:
			err_level += "W2";
			err_name  += "Position generating error 6";
			err_commt += "The transfer position (posture) calculated by the teaching position exceeded the motion limitation.";
			break;

		case 0x090:
			err_level += "W2";
			err_name  += "Host parameter out of range";
			err_commt += "The parameter setting of the communication command from host is out of range.";
			break;

		case 0x0A0:
			err_level += "W2";
			err_name  += "Alignment motion error";
			err_commt += "Alignment motion was not executed because ple-aligner is not ready to run in put motion command with alignment angle.";
			break;

		case 0x0E0:
			err_level += "W2";
			err_name  += "Teach position adjustment offset amount limit error";
			err_commt += "The adjustment offset amount exceeded the limitation.";
			break;

		case 0x0F0:
			err_level += "W1";
			err_name  += "Voltage drop warning";
			err_commt += "Input voltage became too low.";
			break;

		//=========================================================================
		case 0x701:
			err_level += "A2"; 
			err_name  += "ROM Error";
			err_commt += "Servo control board or ROM is defective.";
			break;

		case 0x703:
			err_level += "A2";
			err_name  += "Communication Error (internal controller) 2-1";
			err_commt += "Communication error between the main control board and the servo control board happened.";
			break;

		case 0x704:
			err_level += "A2";
			err_name  += "Communication Error (internal controller) 2-2";
			err_commt += "Communication error between the main control board and the servo control board happened.";
			break;

		case 0x705:
			err_level += "A2";
			err_name  += "Communication Error (internal controller) 2-3";
			err_commt += "Communication error between the main control board and the converter happened.";
			break;

		case 0x706:
			err_level += "A2";
			err_name  += "Servo system error 1";
			err_commt += "System error occurred in servo control board.";
			break;
			
		case 0x707:
			err_level += "A2";
			err_name  += "Servo system error 2";
			err_commt += "System error occurred in servo control board.";
			break;
			
		case 0x709:
			err_level += "A2";
			err_name  += "Current feedback error";
			err_commt += "The current is abnormal.";
			break;
			
		case 0x70A:
			err_level += "A2";
			err_name  += "Power Lost";
			err_commt += "Power lost is detected.";
			break;
			
		case 0x70b:
			err_level += "A2";
			err_name  += "Rush Current Prevention Relay Abnormal";
			err_commt += "The rush current prevention relay is abnormal.";
			break;
			
		case 0x70C:
			err_level += "A2";
			err_name  += "Converter mismatch";
			err_commt += "The converter type is mismatched.";
			break;

		case 0x70F:
			err_level += "A2";
			err_name  += "Servo control board response timeout 2.";
			err_commt += "No response from servo control board.";
			break;
			
		case 0x713:
			err_level += "A2";
			err_name  += "DB error";
			err_commt += "DB is abnormal.";
			break;
			
		case 0x714:
			err_level += "A2";
			err_name  += "Converter charge Error";
			err_commt += "Converter charge error occurs.";
			break;
			
		case 0x715:
			err_level += "A2";
			err_name  += "Servo OFF Status Error 1";
			err_commt += "Hard wire base block error occurs.";
			break;

		case 0x716:
			err_level += "A2";
			err_name  += "Servo ON Status Error 1";
			err_commt += "Hard wire base enable error occurs.";
			break;
			
		case 0x717:
			err_level += "A2";
			err_name  += "Servo OFF Status Error 2";
			err_commt += "Base block error occurs.";
			break;

		case 0x718:
			err_level += "A2";
			err_name  += "Servo ON Status Error 2";
			err_commt += "Base enable error occurs.";
			break;

		case 0x719:
			err_level += "A2";
			err_name  += "Servo On Abnormal";
			err_commt += "Request hard wire base block release, but does not release.";
			break;

		case 0x71A:
			err_level += "A2";
			err_name  += "Brake circuit error 2";
			err_commt += "Brake lock error occurs.";
			break;

		case 0x71b:
			err_level += "A2";
			err_name  += "Brake circuit error 3"; 
			err_commt += "Brake unlock error occurs.";
			break;

		case 0x71C:
			err_level += "A2";
			err_name  += "Power relay error"; 
			err_commt += "Power relay is abnormal.";
			break;

		case 0x721:
			err_level += "A2";
			err_name  += "Servo parameter error 2";
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x722:
			err_level += "A2";
			err_name  += "Servo parameter error 3";
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x725:
			err_level += "A2";
			err_name  += "Converter Overheat";
			err_commt += "Detected the converter overheat.";
			break;

		case 0x726:
			err_level += "A2";
			err_name  += "Communication Error (internal controller) 2-4";
			err_commt += "Detected the undefined command.";
			break;

		case 0x727:
			err_level += "A2";
			err_name  += "Command not supported 1-2";
			err_commt += "Detected the unsupported command.";
			break;

		case 0x728:
			err_level += "A2"; 
			err_name  += "Communication Error (internal controller) 2-5";
			err_commt += "Detected the data abnormal of the command.";
			break;

		case 0x729:
			err_level += "A2";
			err_name  += "Servo system error 3"; 
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x72A:
			err_level += "A2";
			err_name  += "Servo system error 4";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x72b:
			err_level += "A2";
			err_name  += "Servo parameter error 4";
			err_commt += "Servo parameter value is abnormal.";
			break;

		case 0x730:
			err_level += "A2";
			err_name  += "Amp module disconnected."; 
			err_commt += "Amp module is not installed.";
			break;
			
		case 0x732:
			err_level += "A2";
			err_name  += "Servo parameter error 5";
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x733:
			err_level += "A2";
			err_name  += "Servo parameter error 6";
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x734:
			err_level += "A2";
			err_name  += "Servo parameter error 7"; 
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x735:
			err_level += "A2";
			err_name  += "Servo parameter error 8";
			err_commt += "Servo parameter is abnormal.";
			break;

		case 0x73F:
			err_level += "A2"; 
			err_name  += "Undefined Error"; 
			err_commt += "Receive the undefined error from the servo control board.";
			break;
			
		case 0x740:
			err_level += "A2";
			err_name  += "Encoder Status Error";
			err_commt += "PG ON Error occurs.";
			break;

		case 0x741:
			err_level += "A2";
			err_name  += "Servo system error 5";
			err_commt += "Requested the multiple servo on.";
			break;

		case 0x742:
			err_level += "A2";
			err_name  += "Servo system error 6";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x743:
			err_level += "A2";
			err_name  += "Servo system error 7";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x744:
			err_level += "A2";
			err_name  += "Servo system error 8";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x745:
			err_level += "A2";
			err_name  += "Servo system error 9";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x746:
			err_level+= "A2";
			err_name  += "Servo system error 10";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x74A:
			err_level += "A2";
			err_name  += "Servo system error 11";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x74b:
			err_level += "A2";
			err_name  += "Servo system error 12";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x74C:
			err_level += "A2";
			err_name  += "Servo system error 13";
			err_commt += "System error occurred in servo control board.";
			break;

		case 0x74d:
			err_level += "A2";
			err_name  += "Servo system error 14";
			err_commt += "System error occurred in servo control board.";
			break;

		//=========================================================================
		case 0x7A0:
			err_level += "W2"; 
			err_name  += "Communication Error";
			err_commt += "PAIF board received an undefined command.";
			break;
		
		case 0x7A1:
			err_level += "W2";
			err_name  += "Communication Error (internal controller) 3-2";
			err_commt += "PAIF board detected that the command¡¯s parameter value is out of range.";
			break;

		case 0x7A2:
			err_level += "W2";
			err_name  += "Command not supported 3-1";
			err_commt += "Detected the unsupported command.";
			break;

		case 0x7A3:
			err_level += "W2";
			err_name  += "Data buffer full";
			err_commt += "The data buffer is full.";
			break;

		case 0x7A4:
			err_level += "W2";
			err_name  += "Command not supported 3-2";
			err_commt += "Detected the unsupported command.";
			break;

		case 0x7A5:
			err_level += "W2"; 
			err_name  += "Encoder data error 3-1";
			err_commt += "The encoder data is abnormal.";
			break;
			
		case 0x7A6:
			err_level += "W2";
			err_name  += "Command not supported 3-3";
			err_commt += "Detected the unsupported command.";
			break;

		case 0x7AE:
			err_level += "W2";
			err_name  += "Communication Error (internal controller) 3-3";
			err_commt += "The PA board has not become ready.";
			break;

		case 0x7AF:
			err_level += "W2";
			err_name  += "Communication Error (internal controller) 3-4";
			err_commt += "The PA board is not responding.";
			break;

		case 0x7b0:
			err_level += "W2";
			err_name  += "CCD sensor abnormal 1";
			err_commt += "The CCD sensor head power supply voltage is low.";
			break;

		case 0x7b4:
			err_level += "W2";
			err_name  += "CCD sensor abnormal 2"; 
			err_commt += "CCD light source LED is off.";
			break;

		case 0x7b5:
			err_level += "W2";
			err_name  += "CCD sensor abnormal 3";
			err_commt += "CCD light source LED light intensity dropped.";
			break;

		case 0x7C0:
			err_level += "A1";
			err_name  += "PAIF board Failure 1"; 
			err_commt += "Watch dog of PAIF board was detected.";
			break;
			
		case 0x7C1:
			err_level += "A1";
			err_name  += "PAIF board Failure 2"; 
			err_commt += "Low Voltage was detected.";
			break;

		case 0x7C2:
			err_level += "A1";
			err_name  += "PAIF board Failure 3";
			err_commt += "Exception interrupt occurs.";
			break;

		case 0x7C3:
			err_level += "A1";
			err_name  += "CCD sensor abnormal 4";
			err_commt += "LED turn on but the light intensity is zero.";
			break;

		case 0x7d0:
			err_level += "W2";
			err_name  += "PAIF board disconnected ";
			err_commt += "PAIF board is not installed.";
			break;

		case 0x7E0:
			err_level += "W2";
			err_name  += "PAIF board Failure 4 ";
			err_commt += "Over voltage was detected.";
			break;

		case 0x7E1:
			err_level += "W2";
			err_name  += "PAIF board Failure 5";
			err_commt += "The data acquisition failed.";
			break;

		//=========================================================================
		case 0x900:
			err_level += "W1";
			err_name  += "Character Interval Timeout";
			err_commt += "Host command message was interrupted.";
			break;

		case 0x910:
			err_level += "W1";
			err_name  += "Received Data Checksum Error";
			err_commt += "The sum value of data received from the host is invalid.";
			break;

		case 0x920:
			err_level += "W1";
			err_name  += "Unit Number Error"; 
			err_commt += "The command for an undefined unit was received from the host.";
			break;

		case 0x930:
			err_level += "W1";
			err_name  += "Undefined Command Received";
			err_commt += "Received command from the host is undefined.";
			break;

		case 0x940:
			err_level += "W1";
			err_name  += "Message Parameter Error";
			err_commt += "The parameter attached to the command received from the host is";
			break;

		case 0x950:
			err_level += "W1";
			err_name  += "Receiving Time-out Error for Confirmation of Execution Completion";
			err_commt += "The confirmation report of execution completion is not received from the host.";
			break;

		case 0x960:
			err_level += "W1";
			err_name  += "Incorrect sequence number";
			err_commt += "Incorrect sequence number in received command message from host.";
			break;
			
		case 0x961:
			err_level += "W1";
			err_name  += "Duplicated message"; 
			err_commt += "Sequence number was the same as the one on previous received command message from host.";
			break;

		case 0x970:
			err_level += "W1";
			err_name  += "Delimiter error";
			err_commt += "There is no delimiter.";
			break;

		case 0x9A1:
			err_level += "W2";
			err_name  += "Message buffer overflow";
			err_commt += "Message buffer was full when the controller received the command from host.";
			break;

		case 0x9C0:
			err_level += "W2";
			err_name  += "LAN device setting error";
			err_commt += "LAN device setting is invalid.";
			break;

		case 0x9C1:
			err_level += "W2";
			err_name  += "IP address error";
			err_commt += "Set IP address is invalid.";
			break;

		case 0x9C2:
			err_level += "W2";
			err_name  += "Subnet mask error";
			err_commt += "Set subnet mask is invalid.";
			break;

		case 0x9C3:
			err_level += "W2";
			err_name  += "Default gateway error";
			err_commt += "Set default gate way is invalid.";
			break;

		case 0x9d0:
			err_level += "W2";
			err_name  += "Ethernet receive error";
			err_commt += "Host message reception failure (Ethernet).";
			break;

		case 0x9E0:
			err_level += "W2";
			err_name  += "During operation the maintenance tool";
			err_commt += "The request from the host is not acceptable because during operate the maintenance tool.";
			break;

		case 0x9E1:
			err_level += "W2";
			err_name  += "The data abnormal";
			err_commt += "Because internal data was damaged when data is acquired with the maintenance tool, it could not be acquired.";
			break;

		//=========================================================================
		case 0xA01:
			err_level += "A2";
			err_name  += "Re-detection of a power Supply voltage fall";
			err_commt += "The fall of power supply voltage was re-detected.";
			break;

		case 0xA10:
			err_level += "A1";
			err_name  += "External emergency stop";
			err_commt += "External emergency stop (EXESP) enabled by I/O.";
			break;
			
		case 0xA20:
			err_level += "A1";
			err_name  += "T.P emergency stop"; 
			err_commt += "T.P emergency stop button was pressed.";
			break;
			
		case 0xA21:
			err_level += "A1"; 
			err_name  += "Interlock board failure 0";
			err_commt += "Detected the interlock board failure.";
			break;
			
		case 0xA30:
			err_level += "A1";
			err_name  += "Emergency stop"; 
			err_commt += "Emergency stop is commanded from the host.";
			break;
				
		case 0xA40:
			err_level += "W2";
			err_name  += "Controller Fan 1 Error";
			err_commt += "Error occurred in controller cooling fan 1.";
			break;

		case 0xA41:
			err_level += "W2";
			err_name  += "Controller Fan 2 Error";
			err_commt += "Error occurred in controller cooling fan 2.";
			break;

		case 0xA42:
			err_level += "W2";
			err_name  += "Controller Fan 3 Error";
			err_commt += "Error occurred in controller cooling fan 3.";
			break;

		case 0xA45:
			err_level += "W2";
			err_name  += "Unit fan 1 error";
			err_commt += "Unit fan 1 is defective.";
			break;

		case 0xA46:
			err_level += "W2";
			err_name  += "Unit fan 2 error";
			err_commt += "Unit fan 2 is defective.";
			break;

		case 0xA4F:
			err_level += "W2";
			err_name  += "Controller Battery Alarm";
			err_commt += "Controller's memory backup battery is low.";
			break;

		case 0xAC0:
			err_level += "A1";
			err_name  += "Safety fence signal detection";
			err_commt += "An safety fence (SAFF) signal is input from the I/O.";
			break;

		case 0xAC9:
			err_level += "A1";
			err_name  += "Protection stop signal"; 
			err_commt += "Protection stop (ONEN) signal is input from the I/O.";
			break;

		case 0xAE0:
			err_level += "W2";
			err_name  += "HOST Mode Switching error";
			err_commt += "The mode is switched to \¡°HOST\¡± while being controlled from the teaching pendant.";
			break;

		case 0xAE1:
			err_level += "W2";
			err_name  += "TEACH Mode Switching Error"; 
			err_commt += "The mode is switched to ¡°TEACH¡± while being controlled from the host.";
			break;

		case 0xAE8:
			err_level += "W2";
			err_name  += "Deadman switch error";
			err_commt += "Deadman switch was released during teach pendant operation.";
			break;

		case 0xAF0:
			err_level += "A2";
			err_name  += "Interlock board failure 1";
			err_commt += "Detected the interlock board failure.";
			break;
		
		case 0xAF1:
			err_level += "A2";
			err_name  += "Interlock board failure 2";
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF2:
			err_level += "A2";
			err_name  += "Interlock board failure 3"; 
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF3:
			err_level += "A2";
			err_name  += "Interlock board failure 4"; 
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF4:
			err_level += "A2";
			err_name  += "Interlock board failure 5";
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF5: 
			err_level += "A2";
			err_name  += "Interlock board failure 6";
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF6:
			err_level += "A2";
			err_name  += "Interlock board failure 7";
			err_commt += "Detected the interlock board failure.";
			break;

		case 0xAF8:
			err_level += "A2";
			err_name  += "Input compare error 1";
			err_commt += "Cross-check compare error for the teach pendant emergency stop";
			break;

		case 0xAF9:
			err_level += "A2";
			err_name  += "Input compare error 2";
			err_commt += "Cross-check compare error for the interlock input signal 1.";
			break;

		case 0xAFA:
			err_level += "A2";
			err_name  += "Input compare error 3";
			err_commt += "Cross-check compare error for the external emergency stop signal";
			break;

		case 0xAFb:
			err_level += "A2";
			err_name  += "Input compare error 4";
			err_commt += "Cross-check compare error for the deadman switch signal.";
			break;

		case 0xAFC:
			err_level += "A2";
			err_name  += "Input compare error 5";
			err_commt += "Cross-check compare error for the safety fence signal (SAFF).";
			break;

		case 0xAFd: 
			err_level += "A2";
			err_name  += "Input compare error 6";
			err_commt += "Cross-check compare error for the Protection stop signal (ONEN).";
			break;

		case 0xAFE:
			err_level += "A2";
			err_name  += "Input compare error 7";
			err_commt += "Cross-check compare error for the interlock input signal 2.";
			break;

		case 0xAFF:
			err_level += "A2";
			err_name  += "Input compare error 8";
			err_commt += "Cross-check compare error for the interlock input signal 3.";
			break;

		//=========================================================================
		case 0xb10:
			err_level += "A1";
			err_name  += "Axis-1 Speed Limit Detection";
			err_commt += "Axis 1 exceeds the allowable speed.";
			break;
		
		case 0xb11:
			err_level += "A1";
			err_name  += "Axis-2 Speed Limit Detection"; 
			err_commt += "Axis 2 exceeds the allowable speed.";
			break;

		case 0xb12:
			err_level += "A1";
			err_name  += "Axis-3 Speed Limit Detection";
			err_commt += "Axis 3 exceeds the allowable speed.";
			break;

		case 0xb13:
			err_level += "A1"; 
			err_name  += "Axis-4 Speed Limit Detection";
			err_commt += "Axis 4 exceeds the allowable speed.";
			break;

		case 0xb14:
			err_level += "A1";
			err_name  += "Axis-5 Speed Limit Detection";
			err_commt += "Axis 5 exceeds the allowable speed.";
			break;

		case 0xb20:
			err_level += "W2";
			err_name  += "Axis-1 Positive (+) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-1 motion range in the positive direction.";
			break;

		case 0xb21:
			err_level += "W2";
			err_name  += "Axis-2 Positive (+) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-2 motion range in the positive direction.";
			break;

		case 0xb22:
			err_level += "W2";
			err_name  += "Axis-3 Positive (+) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-3 motion range in the positive direction.";
			break;
			
		case 0xb23:
			err_level += "W2";
			err_name  += "Axis-4 Positive (+) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-4 motion range in the positive direction.";
			break;

		case 0xb24:
			err_level += "W2";
			err_name  += "Axis-5 Positive (+) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-5 motion range in the positive direction.";
			break;

		case 0xb28:
			err_level += "W2";
			err_name  += "Axis-1 Positive (+) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-1 motion range in the positive direction when the mapping motion start.";
			break;

		case 0xb29:
			err_level += "W2";
			err_name  += "Axis-2 Positive (+) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-2 motion range in the positive direction when the mapping motion start.";
			break;

		case 0xb2A:
			err_level += "W2";
			err_name  += "Axis-3 Positive (+) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-3 motion range in the positive direction when the mapping motion start.";
			break;

		case 0xb2b:
			err_level += "W2";
			err_name  += "Axis-4 Positive (+) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-4 motion range in the positive direction when the mapping motion start.";
			break;

		case 0xb2C:
			err_level += "W2";
			err_name  += "Axis-5 Positive (+) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-5 motion range in the positive direction when the mapping motion start.";
			break;

		case 0xb30:
			err_level += "W2";
			err_name  += "Axis-1 Negative (-) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-1 motion range in the negative direction.";
			break;

		case 0xb31:
			err_level += "W2";
			err_name  += "Axis-2 Negative (-) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-2 motion range in the negative direction.";
			break;
			
		case 0xb32:
			err_level += "W2";
			err_name  += "Axis-3 Negative (-) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-3 motion range in the negative direction.";
			break;
				
		case 0xb33:
			err_level += "W2";
			err_name  += "Axis-4 Negative (-) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-4 motion range in the negative direction.";
			break;
				
		case 0xb34:
			err_level += "W2";
			err_name  += "Axis-5 Negative (-) Direction Software-limit Detection 1";
			err_commt += "Exceeds Axis-5 motion range in the negative direction.";
			break;
			
		case 0xb38:
			err_level += "W2";
			err_name  += "Axis-1 Negative (-) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-1 motion range in the negative direction when the mapping motion start.";
			break;
	
		case 0xb39:
			err_level += "W2";
			err_name  += "Axis-2 Negative (-) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-2 motion range in the negative direction when the mapping motion start.";
			break;

		case 0xb3A:
			err_level += "W2";
			err_name  += "Axis-3 Negative (-) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-3 motion range in the negative direction when the mapping motion start.";
			break;

		case 0xb3b:
			err_level += "W2";
			err_name  += "Axis-4 Negative (-) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-4 motion range in the negative direction when the mapping motion start.";
			break;

		case 0xb3C:
			err_level += "W2";
			err_name  += "Axis-5 Negative (-) Direction Software-limit Detection 2";
			err_commt += "Exceeds Axis-5 motion range in the negative direction when the mapping motion start.";
			break;

		case 0xb40:
			err_level += "W2";
			err_name  += "Access Permission Signal 1 Time-out Error";
			err_commt += "Time-out of access permission signal 1 occurred.";
			break;

		case 0xb41:
			err_level += "W2";
			err_name  += "Access Permission Signal 2 Time-out Error";
			err_commt += "Time-out of access permission signal 2 occurred.";
			break;
				
		case 0xb42:
			err_level += "W2";
			err_name  += "Access Permission Signal 3 Time-out Error";
			err_commt += "Time-out of access permission signal 3 occurred.";
			break;
				
		case 0xb43:
			err_level += "W2";
			err_name  += "Access Permission Signal 4 Time-out Error";
			err_commt += "Time-out of access permission signal 4 occurred.";
			break;

		case 0xb44:
			err_level += "W2";
			err_name  += "Access Permission Signal 5 Time-out Error";
			err_commt += "Time-out of access permission signal 5 occurred.";
			break;

		case 0xb45:
			err_level += "W2";
			err_name  += "Access Permission Signal 6 Time-out Error";
			err_commt += "Time-out of access permission signal 6 occurred.";
			break;

		case 0xb46:
			err_level += "W2";
			err_name  += "Access Permission Signal 7 Time-out Error";
			err_commt += "Time-out of access permission signal 7 occurred.";
			break;

		//=========================================================================
		case 0xb47:
			err_level += "W2";
			err_name  += "Access Permission Signal 8 Time-out Error";
			err_commt += "Time-out of access permission signal 8 occurred.";
			break;
			
		case 0xb48:
			err_level += "W2";
			err_name  += "Access Permission Signal 9 Time-out Error";
			err_commt += "Time-out of access permission signal 9 occurred.";
			break;

		case 0xb49:
			err_level += "W2";
			err_name  += "Access Permission Signal 10 Time-out Error";
			err_commt += "Time-out of access permission signal 10 occurred.";
			break;

		case 0xb4A:
			err_level += "W2";
			err_name  += "Access Permission Signal 11 Time-out Error";
			err_commt += "Time-out of access permission signal 11 occurred.";
			break;

		case 0xb4b:
			err_level += "W2";
			err_name  += "Access Permission Signal 12 Time-out Error";
			err_commt += "Time-out of access permission signal 12 occurred.";
			break;

		case 0xb4C:
			err_level += "W2";
			err_name  += "Access Permission Signal 13 Time-out Error";
			err_commt += "Time-out of access permission signal 13 occurred.";
			break;

		case 0xb4d:
			err_level += "W2";
			err_name  += "Access Permission Signal 14 Time-out Error";
			err_commt += "Time-out of access permission signal 14 occurred.";
			break;

		case 0xb4E:
			err_level += "W2";
			err_name  += "Access Permission Signal 15 Time-out Error";
			err_commt += "Time-out of access permission signal 15 occurred.";
			break;

		case 0xb4F:
			err_level += "W2";
			err_name  += "Access Permission Signal 16 Time-out Error";
			err_commt += "Time-out of access permission signal 16 occurred.";
			break;
			
		case 0xb70:
			err_level += "W2";
			err_name  += "SS signal detection";
			err_commt += "SS (software stop) signal was detected during operation.";
			break;

		//=========================================================================
		case 0xb80:
			err_level += "W2";
			err_name  += "Fork 1/Pre-aligner: Wafer Presence Confirmation Timeout Error 1";
			err_commt += "The vacuum/grip sensor does not turn on within the specified time.";
			break;
			
		case 0xb81: 
			err_level += "W2";
			err_name  += "Fork 1/Pre-aligner: Wafer Absence Confirmation Timeout Error 1";
			err_commt += "The vacuum/grip sensor does not turn off within the specified time.";
			break;
			
		case 0xb82:
			err_level += "W2";
			err_name  += "Fork 1/Pre-aligner: Wafer Presence Confirmation Timeout Error 2";
			err_commt += "The wafer presence/absence sensor does not turn on within the specified time.";
			break;

		case 0xb83:
			err_level += "W2";
			err_name  += "Fork 1/Pre-aligner: Wafer Absence Confirmation Timeout Error 2";
			err_commt += "The wafer presence/absence sensor does not turn off within the specified time.";
			break;

		case 0xb8F:
			err_level += "W2";
			err_name  += "Fork 1: Plunger non-operation error";
			err_commt += "The plunger of Fork 1 did not move in the observed time.";
			break;
				
		case 0xb90:
			err_level += "W2";
			err_name  += "Fork 2: Wafer Presence Confirmation Time-out Error 1";
			err_commt += "The vacuum/grip sensor does not turn on within the specified time.";
			break;

		case 0xb91:
			err_level += "W2";
			err_name  += "Fork 2: Wafer Absence Confirmation Time-out Error 1";
			err_commt += "The vacuum/grip sensor does not turn off within the specified time.";
			break;

		case 0xb92:
			err_level += "W2";
			err_name  += "Fork 2: Wafer Presence Confirmation Time-out Error 2";
			err_commt += "The wafer presence/absence sensor does not turn on within the specified time.";
			break;

		case 0xb93:
			err_level += "W2";
			err_name  += "Fork 2: Wafer Absence Confirmation Time-out Error 2";
			err_commt += "The wafer presence/absence sensor does not turn off within the specified time.";
			break;

		case 0xb9F:
			err_level += "W2";
			err_name  += "Fork 2: Plunger non-operation error";
			err_commt += "The plunger of Fork 2 did not move in the observed time.";
			break;
			
		case 0xbA0:
			err_level += "W2";
			err_name  += "Fork 1/Pre-aligner: Wafer Absence Error";
			
			err_commt += "The vacuum/grip sensor or wafer presence/absence sensor turns off";
			err_commt += "\n";
			err_commt += "while the manipulator(Fork1)/Pre-aligner is transferring a wafer.";
			break;

		case 0xbA1:
			err_level += "W2";
			err_name  += "Fork 1: Sensor Status Mismatch";
			err_commt += "The vacuum/grip sensor of Fork 1 is on while the wafer presence/absence sensor is off.";
			break;

		case 0xbb0:
			err_level += "W2";
			err_name  += "Fork 2: Wafer Absence Error";
			
			err_commt += "The suction/grip sensor or wafer presence/absence sensor turns off";
			err_commt += "\n";
			err_commt += "while Fork 2 is holding and transferring a wafer.";
			break;
		
		case 0xbb1:
			err_level += "W2";
			err_name  += "Fork 2: Sensor Status Mismatch";
			err_commt += "The suction/grip sensor of Fork 2 is on while the wafer presence/absence sensor is off.";
			break;

		case 0xbF0:
			err_level += "W2";
			err_name  += "Stopped by HOLD signal ";
			err_commt += "Motion request is transmitted while the manipulator is being stopped by HOLD signal.";
			break;

		case 0xC80:
			err_level += "W2";
			err_name  += "The alignment data error";
			err_commt += "Insufficient effective data for wafer alignment.";
			break;
						
		case 0xC90:
			err_level += "W2";
			err_name  += "Notch/Orientation flat position analysis error 1";
			err_commt += "The notch/orientation flat position was not able to be distinguished.";
			break;
			
		case 0xCA0:
			err_level += "W2";
			err_name  += "Center position detection";
			err_commt += "An accurate wafer center position could not be detected.";
			break;

		case 0xCb0:
			err_level += "W2";
			err_name  += "Excessive wafer eccentric amount";
			err_commt += "The wafer eccentric amount is excessive.";
			break;
			
		case 0xCC0:
			err_level += "W2";
			err_name  += "Notch/Orientation flat position analysis error 2";
			err_commt += "An accurate notch/orientation flat position could not be detected.";
			break;
			
		case 0xCd0:
			err_level += "W2";
			err_name  += "Excessive arm correction amount";
			err_commt += "The amount corrected by alignment exceeds the allowable range.";
			break;
			
		case 0xCE0:
			err_level += "W2";
			err_name  += "Robot pre-aligner distance calculation error";
			err_commt += "Could not execute arm calibration correctly.";
			break;

		case 0xd00:
			err_level += "W2";
			err_name  += "Mapping sensor error";
			err_commt += "Mapping sensor beam was already blocked at the mapping start";
			break;

		case 0xd10:
			err_level += "W2";
			err_name  += "Mapping calibration error";
			err_commt += "Could not execute mapping calibration properly.";
			break;

		case 0xd20:
			err_level += "W2";
			err_name  += "Mapping calibration";
			err_commt += "Never executed mapping calibration.";
			break;
			
		case 0xd30:
			err_level += "W2";
			err_name  += "Mapping sampling data error";
			err_commt += "Sampling data for mapping or mapping calibration are abnormal.";
			break;

		case 0xd40:
			err_level += "W2";
			err_name  += "Protruded wafer detection";
			err_commt += "Detected wafer protrusion when mapping or mapping calibration.";
			break;

		case 0xd50:
			err_level += "W2";
			err_name  += "Mapping data chattering detected";
			err_commt += "Detected chattering when mapping or mapping calibration.";
			break;

		case 0xd60:
			err_level += "W2";
			err_name  += "Mapping motion failed";
			err_commt += "The mapping or the mapping calibration was not enforceable for \¡°Top side GET / PUT station\¡±.";
			break;

		//=========================================================================
		case 0xE90:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 1-0";
			break;
			err_commt += "System configuration error.";
				
		case 0xE91:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 1-1";
			err_commt += "Manipulator configuration error.";
			break;
				
		case 0xEA0:
			err_level += "W2";
			err_name  += "Parameter set value abnormal 2-0";
			err_commt += "Real-type common parameter setting warning.";
			break;
				
		case 0xEA1:
			err_level += "W2";
			err_name  += "Parameter set value abnormal 2-1";
			err_commt += "Integer-type common parameter setting warning.";
			break;
			
		case 0xEA4:
			err_level += "W2";
			err_name  += "Parameter set value abnormal 2-4";
			err_commt += "Real-type unit parameter setting warning.";
			break;
				
		case 0xEA5:
			err_level += "W2";
			err_name  += "Parameter set value abnormal 2-5";
			err_commt += "Integer-type unit parameter setting warning.";
			break;
				
		case 0xEb0:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 3-0";
			err_commt += "Real-type common parameter setting is invalid.";
			break;
			
		case 0xEb1:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 3-1";
			err_commt += "Integer-type common parameter setting is invalid.";
			break;
				
		case 0xEb4:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 3-04";
			err_commt += "Real-type unit parameter setting is invalid.";
			break;
				
		case 0xEb5:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 3-5";
			err_commt += "Integer-type unit parameter setting is invalid.";
			break;
				
		case 0xEC0:
			err_level += "A2";
			err_name  += "Parameter set value abnormal 4-0";
			err_commt += "Software and setting parameter do not match.";
			break;
				
		case 0xEd0:
			err_level += "A2";
			err_name  += "Memory operation error 0 ";
			err_commt += "Memory operation error occur.";
			break;
				
		case 0xEd1: 
			err_level += "A2";
			err_name  += "Memory operation error 1";
			err_commt += "Memory operation error occur.";
			break;
				
		case 0xEE0:
			err_level += "A2";
			err_name  += "File operation error 0";
			err_commt += "Failed to open file.";
			break;
				
		case 0xEE1:
			err_level += "A2";
			err_name  += "File operation error 1";
			err_commt += "Failed to close file.";
			break;
				
		case 0xEE2:
			err_level += "A2";
			err_name  += "File operation error 2";
			err_commt += "Failed to read file.";
			break;
				
		case 0xEE3:
			err_level += "A2";
			err_name  += "File operation error 3";
			err_commt += "Failed to write file.";
			break;

		case 0xEE4:
			err_level += "A2";
			err_name  += "File operation error 4";
			err_commt += "Failed to delete file.";
			break;
				
		case 0xEE5:
			err_level += "A2";
			err_name  += "File operation error 5";
			err_commt += "Size of parameter initialization file is invalid.";
			break;
				
		case 0xEE8:
			err_level += "A2";
			err_name  += "File operation error 8";
			err_commt += "Failed to create folder.";
			break;
				
		case 0xEF0:
			err_level += "W2";
			err_name  += "Invalid data in file 0";
			err_commt += "Invalid data in \¡°Format request file\¡±.";
			break;
				
		case 0xEF1:
			err_level += "W2";
			err_name  += "Invalid data in file 1";
			err_commt += "Invalid data in \¡°Auto update request file\¡±.";
			break;
				
		case 0xEF2:
			err_level += "W2";
			err_name  += "Invalid data in file 2";
			err_commt += "Invalid data in \¡°Servo parameter file\¡±.";
			break;

		case 0xEF3:
			err_level += "W2"; 
			err_name  += "Invalid data in file 3"; 
			err_commt += "Invalid data in \¡°Common parameter file\¡±.";
			break;
				
		case 0xEF4:
			err_level += "W2"; 
			err_name  += "Invalid data in file 4"; 
			err_commt += "Invalid data in \¡°Unit parameter file\¡±.";
			break;
				
		case 0xEF5:
			err_level += "W2";
			err_name  += "Invalid data in file 5"; 
			err_commt += "Invalid data in \¡°Position data file\¡±.";
			break;
				
		case 0xEF8:
			err_level += "W2"; 
			err_name  += "Invalid data in file 8"; 
			err_commt += "Invalid data in \¡°Servo parameter automatic update file\¡±.";
			break;
				
		case 0xEF9:
			err_level += "W2"; 
			err_name  += "Invalid data in file 9"; 
			err_commt += "Invalid data in \¡°Common parameter auto update file\¡±.";
			break;
				
		case 0xEFA:
			err_level += "W2"; 
			err_name  += "Invalid data in file 10"; 
			err_commt += "Invalid data in \¡°Unit parameter auto update file\¡±.";
			break;
				
		case 0xEFE:
			err_level += "W2"; 
			err_name  += "Invalid data in file 14"; 
			err_commt += "File data abnormality 1 in the controller.";
			break;
				
		case 0xEFF:
			err_level += "W2"; 
			err_name  += "Invalid data in file 15"; 
			err_commt += "File data abnormality 2 in the controller.";
			break;
		
		//=========================================================================

		default:
			err_msg.Format("Error_Code : %s", err_mxx);

			err_check = -1;
			break;
	}

	if(err_check > 0)
	{
		err_msg += err_level;
		err_msg += "\n";
		err_msg += err_name;
		err_msg += "\n";
		err_msg += err_commt;
	}

	err_msg += "\n";
	return err_msg;
}
