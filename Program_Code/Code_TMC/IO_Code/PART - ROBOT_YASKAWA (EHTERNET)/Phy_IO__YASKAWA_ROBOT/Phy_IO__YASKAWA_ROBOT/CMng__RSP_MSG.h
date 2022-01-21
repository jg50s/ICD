#pragma once


class CMng__RSP_MSG
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CStringArray sList_MSG;

public:
	CMng__RSP_MSG()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CMng__RSP_MSG()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Clear__ALL_RSP_MSG()
	{
		EnterCriticalSection(&mCS_LOCK);

		sList_MSG.RemoveAll();

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Load__RSP_MSG(const CString& rsp_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		sList_MSG.Add(rsp_msg);

		int db_size = sList_MSG.GetSize();
		if(db_size > 10)
		{
			sList_MSG.RemoveAt(10);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int Get__RSP_MSG(CString& rsp_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		int db_size = sList_MSG.GetSize();
		if(db_size > 0)
		{
			rsp_msg = sList_MSG.GetAt(0);
			sList_MSG.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return db_size;
	}
};

