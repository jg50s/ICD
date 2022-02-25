#pragma once


class CDB__ALARM_REPORT
{
public:
	int iEQP_ID;
	CUIntArray iList__EXT_ID;
};

class CRes__ALARM_REPORT
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__REPORT_NO;		// CDB__ALARM_REPORT

	void _Clear__ALL_Of_REPORT_NO();
	void _Load__EQP_ID_Of_REPORT_NO(const int eqp_id, const int ext_id);

public:
	CRes__ALARM_REPORT();
	~CRes__ALARM_REPORT();

	// ...
	int Upload__Report_File();
	int _Upload__Report_File(const CString& path_alarm);

	// ...
	bool Check__EXT_ID_Of_REPORT_NO(const int eqp_id, const int ext_id);

	void Report__ALL_Of_REPORT_NO();
};
