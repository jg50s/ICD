#include "stdafx.h"


// ...
int Macro__HexToDec(const CString& str_hexa)
{
	CString str_data = str_hexa;
	str_data.MakeUpper();

	int dec_value = 0;
	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		if(i > 0)		dec_value *= 16;

		char ch = str_data.GetAt(i);

		     if(((ch >= '0')&&(ch <= '9')))		dec_value += (ch - '0');
		else if(ch == 'A')						dec_value += 10;
		else if(ch == 'B')						dec_value += 11;
		else if(ch == 'C')						dec_value += 12;
		else if(ch == 'D')						dec_value += 13;
		else if(ch == 'E')						dec_value += 14;
		else if(ch == 'F')						dec_value += 15;		
	}

	return dec_value;
}

CString Macro__HEX_ASCII_TO_ASCII(const CString& str__hexa_ascii)
{
	CString str_data = "";

	int i_limit = str__hexa_ascii.GetLength();
	int i;

	for(i=0; i<i_limit; i += 2)
	{
		CString str_hexa = str__hexa_ascii.Mid(i, 2);

		str_data += (char) Macro__HexToDec(str_hexa);
	}
	return str_data;
}
