#pragma once

#ifdef _DEBUG
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__PAD_CTRL_D.lib")
#else
	#pragma comment(lib, "C:\\Module_Linker\\SUI_Link_Res\\SUI_LIB\\SUI__PAD_CTRL_R.lib")
#endif


//----------------------------------------------------------------------------
//-------------------------------------------
class CDS_Pad_Analog
{
public:
	CString sChannel;
	CString sMin;
	CString sMax;
	CString sValue;

	CString sUnit;
	int iDec;
};

class CI_Pad_Analog_CTRL
{
public:
	virtual ~CI_Pad_Analog_CTRL() {};

	virtual int Set_Property(const CDS_Pad_Analog& i_ds) = 0;

	virtual int Popup(CString& result) = 0;

	virtual int Popup(CString strChannel, 
		              CString strMinValue, 
					  CString strMaxValue, 
					  CString strDefaultValue, 
					  CString strUnit, 
					  CString& result) = 0;

	//
	virtual int Popup_KeyboardType(const HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   const CString& min_data, 
								   const CString& max_data, 
								   const CString& unit_data, 
								   CString& out_data) = 0;
};

//-----------------------------------------------
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

	virtual int Popup(CString strChannel, 
					  CString strDefaultValue, 
					  CStringArray& arrDataList, 
					  CString& result) = 0;

	//
	virtual int Popup_KeyboardType(const HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   const CStringArray& data_list,
								   CString& out_data) = 0;
}; 

//-----------------------------------------------
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

	//
	virtual int Set_Property(const CDS_Pad_String& i_ds) = 0;

	//
	virtual int Popup(CString& result) = 0;
	virtual int Popup_Password(CString& result) = 0;

	virtual int Popup(CString strChannel, 
					  CString strDefaultValue, 
					  CString& result) = 0;
	virtual int Popup_Password(CString strChannel, 
							   CString strDefaultValue, 
							   CString& result) = 0;

	// 
	virtual int Popup_KeyboardType(HWND p_hwnd,
								   const POINT& cur_pt,
								   const CString& in_data,
								   CString& out_data) = 0;
};

//-----------------------------------------------
class CI_Pad__AnalogDigital_CTRL
{
public:
	virtual ~CI_Pad__AnalogDigital_CTRL() {};

	virtual int Popup__ANALOG_DIGITAL_PAD(const CString& analog_title,
			                              const CString& analog_min,
				                          const CString& analog_max,
						                  const CString& analog_in_data,
								          const CString& digital_title,
					                      const CStringArray& digital_data_list,
							              const CString& digital_in_data,
									      CString& analog_out_data,
							              CString& digital_out_data) = 0;
};

class CI_Pad__DigitalAnalog_CTRL
{
public:
	virtual ~CI_Pad__DigitalAnalog_CTRL() {};

	virtual int Popup__DIGITAL_ANALOG_PAD(const CString& digital_title,
					                      const CStringArray& digital_data_list,
							              const CString& digital_in_data,
					                      const CString& analog_title,
				                          const CString& analog_min,	
				                          const CString& analog_max,	
				                          const CString& analog_in_data,
					                      CString& digital_out_data,
						                  CString& analog_out_data) = 0;
};
//----------------------------------------------------------------------------
