#include "StdAfx.h"



int  Macro__Get_Error_Msg_Of_1K_Type(const int err_id,CString& err_msg)
{
	if(err_id == 1)
	{
		err_msg  = "E:000001<CR><LF>\n";
		err_msg += "   Parity error \n";
		return 1;
	}
	if(err_id == 2)
	{
		err_msg  = "E:000002<CR><LF>\n";
		err_msg += "   <CR> or <LF> is missing \n";
		return 1;
	}
	if(err_id == 3)
	{
		err_msg  = "E:000003<CR><LF>\n";
		err_msg += "   ¡ì:¡í is missing \n";
		return 1;
	}
	if(err_id == 4)
	{
		err_msg  = "E:000004<CR><LF>\n";
		err_msg += "   letter code \n";
		return 1;
	}
	if(err_id == 5)
	{
		err_msg  = "E:000005<CR><LF>\n";
		err_msg += "   Numerical value not given in 6 digits \n";
		return 1;
	}
	if(err_id == 6)
	{
		err_msg  = "E:000006<CR><LF>\n";
		err_msg += "   value larger 1000 \n";
		return 1;
	}
	if(err_id == 7)
	{
		err_msg  = "E:000007<CR><LF>\n";
		err_msg += "   MODE, ZERO or LEARN selected with no sensor connected (display format set for no sensor) \n";
		return 1;
	}
	if(err_id == 8)
	{
		err_msg  = "E:000008<CR><LF>\n";
		err_msg += "   given in operating mode LOCAL";
		return 1;
	}
	if(err_id == 9)
	{
		err_msg  = "E:000009<CR><LF>\n";
		err_msg += "   commands Z: and L:XXXXXX given while a logic input is activated \n";
		return 1;
	}
	if(err_id == 10)
	{
		err_msg  = "E:000010<CR><LF>\n";
		err_msg += "   Commands U:07, U:08 or U:09 given while valve2 is not connected \n";
		err_msg += "   Or both valves are not in closed position. \n";
		return 1;
	}
	if(err_id == 200)
	{
		err_msg  = "E:000200<CR><LF>\n";
		err_msg += "   Error with ZERO \n";
		err_msg += "   - PM controller is switched in control mode PRESSURE MODE \n";
		err_msg += "   - function ZERO locked (= DISABLED) \n";
		return 1;
	}

	err_msg = "Unknown Error !\n";
	return -1;
}

int  Macro__Get_Error_Msg_Of_1M_Type(const int err_id,CString& err_msg)
{
	if(err_id == 1)
	{
		err_msg  = "[E:][000001][CR][LF]\n";
		err_msg += "   Parity error \n";
		return 1;
	}
	if(err_id == 2)
	{
		err_msg  = "[E:][000002][CR][LF]\n";
		err_msg += "   buffer overflow (to many characters) \n";
		return 1;
	}
	if(err_id == 3)
	{
		err_msg  = "[E:][000003][CR][LF]\n";
		err_msg += "   error (data length, number of stop bits) \n";
		return 1;
	}

	if(err_id == 10)
	{
		err_msg  = "[E:][000010][CR][LF]\n";
		err_msg += "   <CR> or <LF> missing \n";
		return 1;
	}
	if(err_id == 11)
	{
		err_msg  = "[E:][000011][CR][LF]\n";
		err_msg += "   : missing \n";
		return 1;
	}
	if(err_id == 12)
	{
		err_msg  = "[E:][000012][CR][LF]\n";
		err_msg += "   Invalid number of characters (between : and [CR][LF]) \n";
		return 1;
	}

	if(err_id == 20)	
	{
		err_msg  = "[E:][000020][CR][LF]\n";
		err_msg += "   Unknown command \n";
		return 1;
	}
	if(err_id == 21)
	{
		err_msg  = "[E:][000021][CR][LF]\n";
		err_msg += "   Unknown command \n";
		return 1;
	}
	if(err_id == 22)
	{
		err_msg  = "[E:][000022][CR][LF]\n";
		err_msg += "   value \n";
		return 1;
	}
	if(err_id == 23)
	{
		err_msg  = "[E:][000023][CR][LF]\n";
		err_msg += "   Invalid value \n";
		return 1;
	}
	if(err_id == 24)
	{
		err_msg  = "[E:][000030][CR][LF]\n";
		err_msg += "   Value out of range \n";
		return 1;
	}

	if(err_id == 41)
	{
		err_msg  = "[E:][000041][CR][LF]\n";
		err_msg += "   Command not applicable for hardware configuration \n";
		return 1;
	}
	if(err_id == 42)
	{
		err_msg  = "[E:][000060][CR][LF]\n";
		err_msg += "   disabled";
		return 1;
	}

	if(err_id == 80)
	{
		err_msg  = "[E:][000080][CR][LF]\n";
		err_msg +="   not accepted due to local operation \n";
		return 1;
	}
	if(err_id == 82)
	{
		err_msg  = "[E:][000082][CR][LF]\n";
		err_msg += "   Command not accepted due to synchronization, CLOSED or OPEN by digital input, \n";
		err_msg += "   safety mode or fatal error \n";
		return 1;
	}

	err_msg = "Unknown Error !\n";
	return -1;
}
