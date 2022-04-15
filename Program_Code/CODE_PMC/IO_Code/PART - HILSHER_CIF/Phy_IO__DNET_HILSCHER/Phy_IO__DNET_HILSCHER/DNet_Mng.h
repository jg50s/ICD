#pragma once


class CDNet_Mng
{
private:
	int iBD_ID;

public:	
	CDNet_Mng()
	{
		iBD_ID = 0;
	}

	// ...
	int Set__BOARD_ID(const int bd_id);
	int Get__BOARD_ID();

	// ...
	int Call__BOARD_OPEN();
	int Call__BOARD_CLOSE();

	int Call__SCAN_START();
	int Call__SCAN_STOP();

	int Call__DEV_INFO();	
};
