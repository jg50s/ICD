#pragma once


//----------------------------------------------------------------------------
class CDS_Pad_Analog
{
public:
	CString sChannel;
	CString sMin;
	CString sMax;
	CString sValue;

	CString sUnit;
};

class CI_Pad_Analog_CTRL
{
public:
	virtual ~CI_Pad_Analog_CTRL() {};

	virtual int Set_Property(const CDS_Pad_Analog& i_ds) = 0;
	virtual int Popup(CString& result) = 0;

	//
	virtual int Popup_KeyboardType(const HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   const CString& min_data, 
								   const CString& max_data, 
								   const CString& unit_data, 
								   CString& out_data) = 0;
};

class CDS_Pad_Digital
{
public:
	CString sChannel;
	CString sData;
	CStringArray sData_List;
};

class CI_Pad_Digital_CTRL 
{
public:
	virtual ~CI_Pad_Digital_CTRL() {};
	
	virtual int Set_Property(const CDS_Pad_Digital& i_ds) = 0;
	virtual int Popup(CString& result) = 0;

	//
	virtual int Popup_KeyboardType(HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   const CStringArray& l_item,
								   CString& out_data) = 0;
}; 

class CDS_Pad_String
{
public:
	CString sChannel;
	CString sValue;
};

class CI_Pad_String_CTRL 
{
public:
	virtual ~CI_Pad_String_CTRL() {};
	
	virtual int Set_Property(const CDS_Pad_String& i_ds) = 0;
	virtual int Popup(CString& result) = 0;
	virtual int Popup_Password(CString& result) = 0;

	//
	virtual int Popup_KeyboardType(HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   CString& out_data) = 0;
};

class CI_Pad__Digital_Analog_CTRL
{
public:
	virtual ~CI_Pad__Digital_Analog_CTRL() {};

	virtual int Popup__DIGITAL_ANALOG_PAD(const CString& digital_title,
	                                      const CStringArray& l_digital_data,
	                                      const CString& digital_in_data,
	                                      const CString& analog_title,
	                                      const CString& analog_min,
	                                      const CString& analog_max,
	                                      const CString& analog_in_data,
	                                      CString& digital_out_data,
	                                      CString& analog_out_data) = 0;
};
//----------------------------------------------------------------------------
