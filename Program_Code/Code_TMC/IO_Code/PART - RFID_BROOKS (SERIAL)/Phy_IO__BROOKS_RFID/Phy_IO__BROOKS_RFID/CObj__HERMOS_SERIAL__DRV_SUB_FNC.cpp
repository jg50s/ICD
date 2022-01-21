#include "StdAfx.h"
#include "CObj__HERMOS_SERIAL.h"
#include "CObj__HERMOS_SERIAL__DEF.h"

#include "math.h"


//------------------------------------------------------------------------------------
int  CObj__HERMOS_SERIAL::
Make_CheckSum(const int index,
			  char *data,
			  int *i_cs1_high,
			  int *i_cs1_low,
			  int *i_cs2_high,
			  int *i_cs2_low)
{
	unsigned char ch__check_sum1 = 0x00;
	unsigned char ch__check_sum2 = 0x00;

	int i_checksum1_high;
	int i_checksum1_low;
	int i_checksum2_high;
	int i_checksum2_low;
	int i;

	for(i=0;i<=index;i++)
	{
		ch__check_sum1 = ch__check_sum1 ^ data[i];		
	}

	i_checksum1_high = ch__check_sum1;
	i_checksum1_low  = i_checksum1_high;
	i_checksum1_high = i_checksum1_high >> 4;
	i_checksum1_low  = i_checksum1_low & 0x0f;      

	for(i=0;i<=index;i++)
	{
		ch__check_sum2 = ch__check_sum2 + data[i];
	}

	i_checksum2_high = ch__check_sum2;
	i_checksum2_low  = i_checksum2_high;
	i_checksum2_high = i_checksum2_high >> 4;
	i_checksum2_low  = i_checksum2_low & 0x0f;

	// ...
	{
		*i_cs1_high = i_checksum1_high;
		*i_cs1_low  = i_checksum1_low;
		*i_cs2_high = i_checksum2_high;
		*i_cs2_low  = i_checksum2_low;
	}
	return 1;
}

int  CObj__HERMOS_SERIAL::
Error_Report(const CString& err_code)
{
		 if(err_code.CompareNoCase("0") == 0)		sSTR__ERROR_VALUE = "NONE";
	else if(err_code.CompareNoCase("1") == 0)		sSTR__ERROR_VALUE = "AUTOFAIL";
	else if(err_code.CompareNoCase("2") == 0)		sSTR__ERROR_VALUE = "EXFAIL";
	else if(err_code.CompareNoCase("3") == 0)		sSTR__ERROR_VALUE = "WRITEFAIL";
	else if(err_code.CompareNoCase("4") == 0)		sSTR__ERROR_VALUE = "NOTAG";
	else if(err_code.CompareNoCase("5") == 0)		sSTR__ERROR_VALUE = "INVALID1";
	else if(err_code.CompareNoCase("6") == 0)		sSTR__ERROR_VALUE = "UNKNOWN";
	else if(err_code.CompareNoCase("7") == 0)		sSTR__ERROR_VALUE = "UNCONFIG";
	else if(err_code.CompareNoCase("8") == 0)		sSTR__ERROR_VALUE = "CHECK";
	else if(err_code.CompareNoCase("9") == 0)		sSTR__ERROR_VALUE = "VOIDACKN";
	else if(err_code.CompareNoCase("A") == 0)		sSTR__ERROR_VALUE = "LOCKED";
	else if(err_code.CompareNoCase(":") == 0)		sSTR__ERROR_VALUE = "MSGLEN";
	else if(err_code.CompareNoCase(";") == 0)		sSTR__ERROR_VALUE = "INVALID2";
	else											sSTR__ERROR_VALUE = "NOACKN";

	diCH__FAILURE_CODE->Set__DATA(sSTR__ERROR_VALUE);
	return 1;
}
