#include "StdAfx.h"
#include "CObj__LF80_SERIAL.h"
#include "CObj__LF80_SERIAL__DEF.h"

#include "math.h"


//------------------------------------------------------------------------------------
void CObj__LF80_SERIAL::
Fnc__LOG(const char *fmt, ...)
{
	if(iFlag_Log < 1)		return;

	CString str_msg;
	va_list args;

	va_start(args, fmt);
	str_msg.FormatV(fmt, args);
	va_end(args);

	xLOG_CTRL->WRITE__LOG(str_msg);
}

void CObj__LF80_SERIAL::
Fnc__MSG(const CString& log_msg)
{
	sCH__MSG->Set__DATA(log_msg);
}


CString CObj__LF80_SERIAL::
Fnc__ASCII_Conver(CString data)
{
	CString select;
	CString stemp;
	CString result;

	char temp[2];

	int count = data.GetLength();
	int i;
	int j;

	for(i=0;i<count;i=i+2)
	{		
		select = " ";

		for(j=0;j<2;j++)
		{
			if(i+j<count)	temp[j] = data.GetAt(i+j);
			else			temp[j] = 0;
		}

		select.Format("%c%c",temp[0],temp[1]);
		result += Fnc__ASCII_Table(select);
	}

	return result;
}

CString CObj__LF80_SERIAL::
Fnc__ASCII_Table(CString data)
{
	data.MakeUpper();

	// ...
	CString result;

		 if(data == "30")		result = "0";
	else if(data == "31")		result = "1";
	else if(data == "32")		result = "2";
	else if(data == "33")		result = "3";
	else if(data == "34")		result = "4";
	else if(data == "35")		result = "5";
	else if(data == "36")		result = "6";
	else if(data == "37")		result = "7";
	else if(data == "38")		result = "8";
	else if(data == "39")		result = "9";
	else if(data == "41")		result = "A";
	else if(data == "42")		result = "B";
	else if(data == "43")		result = "C";
	else if(data == "44")		result = "D";
	else if(data == "45")		result = "E";
	else if(data == "46")		result = "F";
	else if(data == "47")		result = "G";
	else if(data == "48")		result = "H";
	else if(data == "49")		result = "I";
	else if(data == "4A")		result = "J";
	else if(data == "4B")		result = "K";
	else if(data == "4C")		result = "L";
	else if(data == "4D")		result = "M";
	else if(data == "4E")		result = "N";
	else if(data == "4F")		result = "O";
	else if(data == "50")		result = "P";
	else if(data == "51")		result = "Q";
	else if(data == "52")		result = "R";
	else if(data == "53")		result = "S";
	else if(data == "54")		result = "T";
	else if(data == "55")		result = "U";
	else if(data == "56")		result = "V";
	else if(data == "57")		result = "W";
	else if(data == "58")		result = "X";
	else if(data == "59")		result = "Y";
	else if(data == "5A")		result = "Z";
	else if(data == "5B")		result = "[";
	else if(data == "5C")		result = "\\";
	else if(data == "5D")		result = "]";
	else if(data == "5E")		result = "^";
	else if(data == "5F")		result = "_";
	else if(data == "61")		result = "a";
	else if(data == "62")		result = "b";
	else if(data == "63")		result = "c";
	else if(data == "64")		result = "d";
	else if(data == "65")		result = "e";
	else if(data == "66")		result = "f";
	else if(data == "67")		result = "g";
	else if(data == "68")		result = "h";
	else if(data == "69")		result = "i";
	else if(data == "6A")		result = "j";
	else if(data == "6B")		result = "k";
	else if(data == "6C")		result = "l";
	else if(data == "6D")		result = "m";
	else if(data == "6E")		result = "n";
	else if(data == "6F")		result = "o";
	else if(data == "70")		result = "p";
	else if(data == "71")		result = "q";
	else if(data == "72")		result = "r";
	else if(data == "73")		result = "s";
	else if(data == "74")		result = "t";
	else if(data == "75")		result = "u";
	else if(data == "76")		result = "v";
	else if(data == "77")		result = "w";
	else if(data == "78")		result = "x";
	else if(data == "79")		result = "y";
	else if(data == "7A")		result = "z";
	else if(data == "21")		result = "!";
	else if(data == "23")		result = "#";
	else if(data == "24")		result = "$";	
	else if(data == "25")		result = "%";
	else if(data == "26")		result = "&";	
	else if(data == "27")		result = "'";
	else if(data == "28")		result = "(";
	else if(data == "29")		result = ")";
	else if(data == "2A")		result = "*";
	else if(data == "2B")		result = "+";
	else if(data == "2C")		result = ",";
	else if(data == "2D")		result = "-";
	else if(data == "2E")		result = ".";
	else if(data == "2F")		result = "/";
	else						result = " " ;

	return result;
}

CString CObj__LF80_SERIAL::
Fnc__HEX_Conver(CString data)
{
	CString select;
	CString result;

	int count = data.GetLength();
	int i;

	for(i=0; i<count; i++)
	{		
		select = data.GetAt(i);
		result += Fnc__HEX_Table(select);
	}

	return result;
}

CString CObj__LF80_SERIAL::
Fnc__HEX_Table(CString data)
{
	CString result;

	 	 if(data == "0")		result = "30";
	else if(data == "1")		result = "31";
	else if(data == "2")		result = "32";
	else if(data == "3")		result = "33";
	else if(data == "4")		result = "34";
	else if(data == "5")		result = "35";
	else if(data == "6")		result = "36";
	else if(data == "7")		result = "37";
	else if(data == "8")		result = "38";
	else if(data == "9")		result = "39";
	else if(data == "A")		result = "41";
	else if(data == "B")		result = "42";
	else if(data == "C")		result = "43";
	else if(data == "D")		result = "44";
	else if(data == "E")		result = "45";
	else if(data == "F")		result = "46";
	else if(data == "G")		result = "47";
	else if(data == "H")		result = "48";
	else if(data == "I")		result = "49";
	else if(data == "J")		result = "4A";
	else if(data == "K")		result = "4B";
	else if(data == "L")		result = "4C";
	else if(data == "M")		result = "4D";
	else if(data == "N")		result = "4E";
	else if(data == "O")		result = "4F";
	else if(data == "P")		result = "50";
	else if(data == "Q")		result = "51";
	else if(data == "R")		result = "52";
	else if(data == "S")		result = "53";
	else if(data == "T")		result = "54";
	else if(data == "U")		result = "55";
	else if(data == "V")		result = "56";
	else if(data == "W")		result = "57";
	else if(data == "X")		result = "58";
	else if(data == "Y")		result = "59";
	else if(data == "Z")		result = "5A";
	else if(data == "a")		result = "61";
	else if(data == "b")		result = "62";
	else if(data == "c")		result = "63";
	else if(data == "d")		result = "64";
	else if(data == "e")		result = "65";
	else if(data == "f")		result = "66";
	else if(data == "g")		result = "67";
	else if(data == "h")		result = "68";
	else if(data == "i")		result = "69";
	else if(data == "j")		result = "6A";
	else if(data == "k")		result = "6B";
	else if(data == "l")		result = "6C";
	else if(data == "m")		result = "6D";
	else if(data == "n")		result = "6E";
	else if(data == "o")		result = "6F";
	else if(data == "p")		result = "70";
	else if(data == "q")		result = "71";
	else if(data == "r")		result = "72";
	else if(data == "s")		result = "73";
	else if(data == "t")		result = "74";
	else if(data == "u")		result = "75";
	else if(data == "v")		result = "76";
	else if(data == "w")		result = "77";
	else if(data == "x")		result = "78";
	else if(data == "y")		result = "79";
	else if(data == "z")		result = "7A";
	else if(data == "!")		result = "21";
	else if(data == "#")		result = "23";
	else if(data == "$")		result = "24";	
	else if(data == "%")		result = "25";
	else if(data == "&")		result = "26";	
	else if(data == "'")		result = "27";
	else if(data == "(")		result = "28";
	else if(data == ")")		result = "29";
	else if(data == "*")		result = "2A";
	else if(data == "+")		result = "2B";
	else if(data == ",")		result = "2C";
	else if(data == "-")		result = "2D";
	else if(data == ".")		result = "2E";
	else if(data == "/")		result = "2F";
	else if(data == " ")		result = "20";
	else						result = " " ;

	return result;
}
