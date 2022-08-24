#include "stdafx.h"
#include "CCommon_Utility.h"


// ...
float Macro__Get_FLOAT_FROM_HEXA(const CString& str_hexa)
{
	UNION_4_BYTE__FLOAT m_value;
	CCommon_Utility m_fnc;

	// ...
	{
		byte uch_data[21];
		memset(uch_data, 0, 21);

		// String_Hexa -> Int_Hexa
		{
			CStringArray l_data;
			m_fnc.Get__StringArrray_From_String(str_hexa, " ", l_data);

			int i_limit = l_data.GetSize();
			if(i_limit > 20)		i_limit = 20;

			for(int i=0; i<i_limit; i++)
			{
				uch_data[i] = 0x0ff & m_fnc.Get__Hexa_From_String(l_data[i]);
			}
		}

		m_value.cBYTE[0] = 0x0ff & uch_data[0];
		m_value.cBYTE[1] = 0x0ff & uch_data[1];
		m_value.cBYTE[2] = 0x0ff & uch_data[2];
		m_value.cBYTE[3] = 0x0ff & uch_data[3];
	}

	return m_value.fDATA;
}

unsigned short int Macro__Get_2_UINT_FROM_HEXA(const CString& str_hexa)
{
	UNION_2_BYTE__UINT m_value;
	CCommon_Utility m_fnc;

	// ...
	{
		byte uch_data[21];
		memset(uch_data, 0, 21);

		// String_Hexa -> Int_Hexa
		{
			CStringArray l_data;
			m_fnc.Get__StringArrray_From_String(str_hexa, " ", l_data);

			int i_limit = l_data.GetSize();
			if(i_limit > 20)		i_limit = 20;

			for(int i=0; i<i_limit; i++)
			{
				uch_data[i] = 0x0ff & m_fnc.Get__Hexa_From_String(l_data[i]);
			}
		}

		m_value.cBYTE[0] = 0x0ff & uch_data[0];
		m_value.cBYTE[1] = 0x0ff & uch_data[1];
	}

	return m_value.uiDATA;
}
unsigned char Macro__Get_1_BYTE_FROM_HEXA(const CString& str_hexa)
{
	CCommon_Utility m_fnc;
	
	unsigned char m_byte = 0x0ff & m_fnc.Get__Hexa_From_String(str_hexa);
	return m_byte;
}
