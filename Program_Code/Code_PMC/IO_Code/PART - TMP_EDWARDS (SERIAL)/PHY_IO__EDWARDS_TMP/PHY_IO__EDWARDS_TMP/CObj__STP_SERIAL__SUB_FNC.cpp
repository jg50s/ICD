#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"

#include "math.h"



//------------------------------------------------------------------------------------
void CObj__STP_SERIAL::
Fnc__APP_LOG(const CString& log_msg)
{

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__STP_SERIAL::
Fnc__DRV_LOG(const CString& log_msg)
{

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

CString CObj__STP_SERIAL::
_Get__Error_Message(const int err_value)
{
	switch(err_value)
	{
		case 0:			return "Ram Error";
		case 1:			return "[System reservation]";
		case 2:			return "TMS Higher Temp";
		case 3:			return "[System reservation]";
		case 4:			return "[System reservation]";

		case 5:			return "Power Failure";
		case 6:			return "Power Supply Fail";
		case 7:			return "Overspeed 1l";
		case 8:			return "DRV Overvoltage";

		case 9:			return "[System reservation]";
		case 10:		return "CNT Overheat 1";
		case 11:		return "DRV Overcurrent";
		case 12:		return "DRV Overload";

		case 13:		return "Disturbance X_H";
		case 14:		return "Disturbance Y_H";
		case 15:		return "Disturbance X_B";
		case 16:		return "Disturbance Y_B";
		case 17:		return "Disturbance Z";

		case 18:		return "MOTOR Overheat";
		case 19:		return "[System reservation]";
		case 20:		return "CNT Overheat 2";
		case 21:		return "[System reservation]";
		case 22:		return "[System reservation]";
		case 23:		return "[System reservation]";

		case 24:		return "DRV Com. Failure";
		case 25:		return "WARNING 1st Damage Limit";
		case 26:		return "WARNING 2nd Damage Limit";
		case 27:		return "[System reservation]";
		case 28:		return "Speed Pulse Lost";
		case 29:		return "Overspeed 2";
		case 30:		return "Overspeed 3";
		case 31:		return "M_Temp Lost";
		case 32:		return "TMS Lower Temp";

		// ...
	}

	return "Unknown";
}
