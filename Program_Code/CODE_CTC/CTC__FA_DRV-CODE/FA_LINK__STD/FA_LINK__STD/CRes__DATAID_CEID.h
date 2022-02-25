#pragma once


class CRes__DATAID_CEID
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CUIntArray iList__CEID;
	CUIntArray iList__DATAID;

public:
	CRes__DATAID_CEID();
	~CRes__DATAID_CEID();

	void Load__INFO(const int ceid,const int dataid);
	int  Get__DATAID(const int ceid,int& dataid);
};
