#include "StdAfx.h"
#include "CObj__LF80_SERIAL.h"
#include "CObj__LF80_SERIAL__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__LF80_SERIAL::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	str__log = "RF Reader : Init Starting ...";
	Fnc__LOG(str__log);

	// ... 초기화..
	sCH__READ_MID_PAGE_DATA->Set__DATA("");
	sCH__READ_PAGE_DATA->Set__DATA("");

	// ... 초기화..
	for (int i=0; i<CFG__PAGE_SIZE; i++)
	{
		siCH__READ_PAGE_DATA[i]->Set__DATA("");
	}

	// ...
	state = doCH__HEART_BEAT->Set__DATA("ON");
	if(state > 0)
	{
		str__log = "RF Reader : Init Complete ...";
	}
	else
	{
		str__log = "RF Reader : Init Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}

int  CObj__LF80_SERIAL::
Call__MULTI_PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;
	int min_page;
	int max_page;

	CString var_data;

	// ...
	str__log = "RF Reader : MultPageRead Starting ...";
	Fnc__LOG(str__log);

	aCH__PAGE1_NUM->Get__DATA(var_data);
	min_page = atoi(var_data)-1;

	aCH__PAGE2_NUM->Get__DATA(var_data);
	max_page = atoi(var_data)-1;

	if(dCH__OTR_IN_READ_PAGE1_AND_2_ONLY->Check__DATA("TRUE") > 0)
	{
		min_page = 0;
		max_page = 1;		
	}

	// ...
	state = Fnc__MultPage_Read(p_alarm,min_page,max_page,&page_data, "");
	if(state > 0)
	{
		sCH__READ_PAGE_DATA->Set__DATA(page_data);

		str__log = "RF Reader : MultPageRead Complete ...";
	}
	else
	{
		str__log = "RF Reader : MultPageRead Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}
int  CObj__LF80_SERIAL::
Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;
	int page_index;

	CString var_data;

	str__log = "RF Reader : PageRead Starting ...";
	Fnc__LOG(str__log);

	aCH__PAGE1_NUM->Get__DATA(var_data);
	page_index = atoi(var_data) - 1;

	// ...
	state = Fnc__Page_Read(p_alarm,page_index,&page_data);
	if(state > 0)
	{
		page_data.TrimRight();
		sCH__READ_PAGE_DATA->Set__DATA(page_data);    

		str__log = "RF Reader : PageRead Complete ...";
	}
	else
	{
		str__log = "RF Reader : PageRead Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}

int  CObj__LF80_SERIAL::
Call__MULTI_PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;
	int min_page_index;
	int max_page_index;

	CString var_data;

	// ...
	str__log = "RF Reader : MultPageWrite Starting ...";
	Fnc__LOG(str__log);

	aCH__PAGE1_NUM->Get__DATA(var_data);
	min_page_index = atoi(var_data) - 1;

	aCH__PAGE2_NUM->Get__DATA(var_data);
	max_page_index = atoi(var_data) - 1;

	// ...
	sCH__WRITE_PAGE_DATA->Get__DATA(page_data);

	state = Fnc__MultPage_Write(p_alarm,min_page_index,max_page_index,page_data);
	if(state > 0)
	{
		str__log = "RF Reader : MultPageWrite Complete ...";
	}
	else
	{
		str__log = "RF Reader : MultPageWrite Abort ....";
	} 

	Fnc__LOG(str__log);
	return state;
}
int  CObj__LF80_SERIAL::
Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;
	int page_index;

	CString var_data;

	// ...
	str__log = "RF Reader : PageWrite Starting ...";

	aCH__PAGE1_NUM->Get__DATA(var_data);
	page_index = atoi(var_data) - 1;

	// ...
	sCH__WRITE_PAGE_DATA->Get__DATA(page_data);

	state = Fnc__Page_Write(p_alarm,page_index,page_data);
	if(state > 0)
	{
		str__log = "RF Reader : PageWrite Complete ...";
	}
	else
	{
		str__log = "RF Reader : PageWrite Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}


int  CObj__LF80_SERIAL::
Call__MID_WRITE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;

	str__log = "RF Reader :  CID_Write Starting ....";
	Fnc__LOG(str__log);

	// ...
	sCH__WRITE_MID_PAGE_DATA->Get__DATA(page_data);

	state = Fnc__MultPage_Write(p_alarm,0,1,page_data);
	if(state > 0)
	{
		str__log = "RF Reader : CIDWrite Complete ...";
	}
	else
	{
		str__log = "RF Reader : CIDWrite Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}
int  CObj__LF80_SERIAL::
Call__MID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString str__log;
	int state;

	CString page_data;
	CString var_data;

	str__log = "RF Reader : CIDRead Starting ...";
	Fnc__LOG(str__log);

	// ...
	state = Fnc__MultPage_Read(p_alarm,0,1,&page_data, "CID_READ");

	page_data.TrimRight();
	sCH__READ_MID_PAGE_DATA->Set__DATA(page_data);				

	str__log.Format("CID_DATA:[%s]", page_data);
	Fnc__LOG(str__log);

	if(state > 0)
	{
		str__log = "RF Reader : CIDRead Complete ...";
	}
	else
	{
		str__log = "RF Reader : CIDRead Abort ...";
	}

	Fnc__LOG(str__log);
	return state;
}
