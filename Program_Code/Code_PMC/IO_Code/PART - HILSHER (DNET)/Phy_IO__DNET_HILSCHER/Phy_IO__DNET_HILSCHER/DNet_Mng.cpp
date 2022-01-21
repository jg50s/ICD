#include "StdAfx.h"
#include "DNet_Mng.h"

#include "cifuser.h"
#include "rcs_user.h"
#include "dnm_user.h"


//--------------------------------------------------------------------------------
int CDNet_Mng::Set__BOARD_ID(const int bd_id)
{
	iBD_ID = bd_id;
	return 1;
}
int CDNet_Mng::Get__BOARD_ID()
{
	return iBD_ID;
}

int CDNet_Mng::Call__BOARD_OPEN()
{
	int dev_id = iBD_ID;

	// ...
	BOARD_INFO      tBoardInfo;
	FIRMWAREINFO    tFirmwareInfo;
	DRIVERINFO	    tDriverInfo;
	RCS_MESSAGE     tMsg;
	RCS_MESSAGE     tMsgDownload;

	// ...
	CString log_add;
	CString log_msg;

	CString ch_data;
	short s_ret;

	// open driver first
	if((s_ret = DevOpenDriver(dev_id)) != DRV_NO_ERROR) 
	{
		printf("DevOpenDriver(%1d): %d\n", dev_id,s_ret);
		return -1;
	} 
	printf("DevOpenDriver(%1d): OK\n", dev_id);

	s_ret = DevInitBoard(dev_id, NULL);
	if(s_ret != DRV_NO_ERROR)
	{
		printf("DevInitBoard(%1d): %d\n", dev_id,s_ret);

		DevCloseDriver(dev_id);
		return -1;
	} 
	printf("DevInitBoard(%1d): OK\n", dev_id);

	if((s_ret = DevGetBoardInfo(dev_id, sizeof(tBoardInfo), &tBoardInfo)) != DRV_NO_ERROR) 
	{
		log_msg.Format("DevGetBoardInfo(%1d, sizeof(BOARD_INFO), %p): %d\n", dev_id,tBoardInfo, s_ret);
		log_add += log_msg;

		printf(log_msg);

		DevCloseDriver(dev_id);
		return -1;
	} 
	printf("DevGetBoardInfo(%s): OK\n", tBoardInfo.abDriverVersion);

	s_ret = DevReset(dev_id, WARMSTART, 5000);
	if(s_ret != DRV_NO_ERROR)
	{
		printf("DevReset(%1d): %d\n", dev_id,s_ret);
		return -1;
	}

	return 1;
}
int CDNet_Mng::Call__BOARD_CLOSE()
{
	int dev_id = iBD_ID;
	short s_ret;

	// ...
	{
		s_ret = DevExitBoard(dev_id);
		printf("DevExitBoard RetWert = %5d \n", s_ret);

		s_ret = DevCloseDriver(dev_id);
		printf("DevCloseDriver RetWert = %5d \n", s_ret);
		return -1;
	}
	return 1;
}

int CDNet_Mng::Call__SCAN_START()
{
	int dev_id = iBD_ID;
	short s_ret;

	// Signal board, application is running
	s_ret = DevSetHostState(dev_id, HOST_READY, 0L);
	printf("DevSetHostState (HOST_READY) RetWert = %5d \n", s_ret);

	if(s_ret != DRV_NO_ERROR)		return -1;

	// ...
	IOINFO io_info;

	s_ret = DevGetInfo(dev_id, GET_IO_INFO, sizeof(IOINFO), &io_info);
	printf("DevGetInfo(%1d, GET_IO_INFO) RetWert = %5d \n", dev_id,s_ret);

	// ...
	{
		CString log_msg;

		log_msg.Format("io_info.bComBit <- %1d \n",         io_info.bComBit);				// Actual state of the COM bit (0,1)
		printf(log_msg);

		log_msg.Format("io_info.bIOExchangeMode <- %1d \n", io_info.bIOExchangeMode);		// Actual data exchange mode (0..5)
		printf(log_msg);

		log_msg.Format("io_info.ulIOExchangeCnt <- %1d \n", io_info.ulIOExchangeCnt);		// Exchange IO counter
		printf(log_msg);
	}
	return 1;
}
int CDNet_Mng::Call__SCAN_STOP()
{
	int dev_id = iBD_ID;
	short s_ret;

	// Signal board, application is not running
	s_ret = DevSetHostState(dev_id, HOST_NOT_READY, 0L);
	printf("DevSetHostState (HOST_NOT_READY) RetWert = %5d \n", s_ret);

	return 1;
}

int CDNet_Mng::Call__DEV_INFO()
{
	int dev_id = iBD_ID;
	short s_ret;

	// ...
	int usReadOffset = 0;
	int usReadSize = 100;
	unsigned char abIOReadData[101];

	memset(abIOReadData, 0, 100);

	COMSTATE  tComState;
	TASKSTATE tTaskState;

	if((s_ret = DevExchangeIOErr(dev_id,
		0,0,NULL,
		usReadOffset,usReadSize,&abIOReadData[0],
		&tComState,
		100L)) == DRV_NO_ERROR) 
	{
		// Check state field transfer mode
		switch(tComState.usMode) 
		{
		case STATE_MODE_3:
			// Check state field usStateFlag signals entrys
			if(tComState.usStateFlag != 0) 
			{
				// Show COM errors
				printf("STATE_3 : Show COM errors \n");
			}
			break;
		case STATE_MODE_4:
			// Check state field usStateFlag signals new entrys
			if(tComState.usStateFlag != 0) 
			{
				// Show COM errors
				printf("STATE_4 : Show COM errors \n");
			}
			break;

		default:
			// State mode unknown or not implemented
			// Read the task state field by yourself
			if(s_ret = DevGetTaskState(dev_id,0,16, &tTaskState) != DRV_NO_ERROR) 
			{
				// Error by reading the task state
				printf("Error by reading the task state \n");
			}
			break;
		} 
		/* end switch */

		// ...
		{
			CString str_data;
			CString str_hexa;
			int i_count = 0;
			int i;

			printf("=========================================================\n");

			for(i=0; i<usReadSize; i++)
			{
				i_count++;
				str_hexa.Format("%02X ", 0x0ff & abIOReadData[i]);
				str_data += str_hexa;

				if(i_count >= 10)
				{
					i_count = 0;
					printf(str_data);
					printf("\n");

					str_data = "";
				}
			}

			if(i_count >= 10)
			{
				printf(str_data);
				printf("\n");
			}
		}
	}
	return 1;
}
