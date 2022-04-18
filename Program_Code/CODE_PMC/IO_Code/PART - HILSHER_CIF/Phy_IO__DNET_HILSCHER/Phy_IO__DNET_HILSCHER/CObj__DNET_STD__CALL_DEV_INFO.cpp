#include "StdAfx.h"
#include "CObj__DNET_STD.h"
#include "CObj__DNET_STD__DEF.h"

#include "cifuser.h"
#include "rcs_user.h"
#include "dnm_user.h"


//-------------------------------------------------------------------------	
int  CObj__DNET_STD
::Call__DEV_INFO(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	EnterCriticalSection(&mLOCK_DNET);

	int r_flag = _Fnc__DEV_INFO(p_variable, p_alarm);

	LeaveCriticalSection(&mLOCK_DNET);
	return r_flag;
}
int  CObj__DNET_STD
::_Fnc__DEV_INFO(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	unsigned char abResponseData[RCS_SEGMENT_LEN];
	unsigned char bLen;

	CString log_msg;
	CString log_add;

	CString ch_data;
	
	// ...
	unsigned short total__in_byte  = 0;
	unsigned short total__out_byte = 0;

	for(int i=0; i<iSLAVE_COUNT; i++)
	{
		int err_check__id = 0;

		ch_data = sCH__DNET_CFG__SLAVE_X__MACID[i]->Get__STRING();
		unsigned char mac_id = atoi(ch_data);

		// ...
		{
			log_msg.Format("%1d) Slave_Info ... \n", i);

			log_add.Format("  * MacID <- [%1d] \n", mac_id);
			log_msg += log_add;

			printf(log_msg);
		}

		// Get the name of the Device from the network
		{
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_IDENTITY_CLASS, 
										1 , 
										DNM_IDOBJ_NAME, 
										&abResponseData[0]);

			if(bLen != 0)
			{
				// terminate string with 0
				abResponseData[bLen] = 0;

				ch_data.Format("%s", &abResponseData[1]);
				sCH__DNET_INFO__SLAVE_X__NAME[i]->Set__DATA(ch_data);

				log_msg.Format("  * Device Name <- [%s] \n",sCH__DNET_INFO__SLAVE_X__NAME[i]->Get__STRING());
				printf(log_msg);
			}
			else
			{
				err_check__id = 1;

				sCH__DNET_INFO__SLAVE_X__NAME[i]->Set__DATA("???");
			}
		}

		// VendorID ...
		{
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_IDENTITY_CLASS, 
										1 , 
										DNM_IDOBJ_VENDOR_ID, 
										&abResponseData[0]);

			if(bLen != 0)
			{
				unsigned short usVendorID = *((unsigned short*)&abResponseData[0]);

				log_msg.Format("  * VendorID <- [%1d] \n", usVendorID);
				printf(log_msg);
			}
			else
			{
				err_check__id = 2;
			}
		}

		// DeviceType ...
		{
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_IDENTITY_CLASS, 
										1 , 
										DNM_IDOBJ_DEV_TYPE, 
										&abResponseData[0]);
			if(bLen != 0)
			{
				unsigned short usDeviceType = *((unsigned short*)&abResponseData[0]);

				log_msg.Format("  * DeviceType <- [%1d] \n", usDeviceType);
				printf(log_msg);
			}
			else
			{
				err_check__id = 3;
			}
		}
		
		// ProductCode ...
		{
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_IDENTITY_CLASS, 
										1 , 
										DNM_IDOBJ_PROD_CODE, 
										&abResponseData[0]);
			if(bLen != 0)
			{
				unsigned short usProductCode = *((unsigned short*)&abResponseData[0]);
	
				log_msg.Format("  * ProductCode <- [%1d] \n", usProductCode);
				printf(log_msg);
			}
			else
			{
				err_check__id = 4;
			}
		}

		// Revision ...
		{
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_IDENTITY_CLASS, 
										1 , 
										DNM_IDOBJ_REV, 
										&abResponseData[0]);
			if(bLen != 0)
			{
				unsigned char bMajorRevision = abResponseData[0];
				unsigned char bMinorRevision = abResponseData[1];

				log_msg.Format("  * Major.Revision <- [%1d] \n", bMajorRevision);
				log_add.Format("  * Minor.Revision <- [%1d] \n", bMinorRevision);
				log_msg += log_add;
				printf(log_msg);
			}
			else
			{
				err_check__id = 5;
			}
		}

		// get the produced and consumed connection size
		{
			unsigned short usInstance = 0;
			unsigned char bProducedSize = 0;
			unsigned char bConsumedSize = 0; 

			usInstance = DNM_POLLED_CNXN_INSTANCE;
			/*
			usInstance = DNM_COS_CYCLIC_CNXN_INSTANCE;
			usInstance = DNM_COS_CYCLIC_CNXN_INSTANCE;
			usInstance = DNM_BIT_STROBED_CNXN_INSTANCE;
			usInstance = DNM_EXPLICIT_CNXN_INSTANCE;
			*/
	
			// In.Byte ...
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_CNXN_CLASS, 
										usInstance, 
										DNM_CNXN_PSIZE_ATTR_ID, 
										&abResponseData[0]);
			if( bLen != 0 )
			{
				bProducedSize = abResponseData[0];
				total__in_byte += bProducedSize;

				log_msg.Format("  * ProducedSize(In) <- [%1d] \n", bProducedSize);
				printf(log_msg);

				ch_data.Format("%1d", bProducedSize);;
				sCH__DNET_INFO__SLAVE_X__IN_SIZE[i]->Set__DATA(ch_data);
			}
			else
			{
				err_check__id = 11;

				sCH__DNET_INFO__SLAVE_X__IN_SIZE[i]->Set__DATA("???");
			}

			// Out.Byte ...
			bLen = DNet__ReadDeviceData((unsigned char) mac_id,
										DNM_CNXN_CLASS, 
										usInstance, 
										DNM_CNXN_CSIZE_ATTR_ID, 
										&abResponseData[0]);
			if(bLen != 0)
			{
				bConsumedSize = abResponseData[0];
				total__out_byte += bConsumedSize;

				log_msg.Format("  * ConsumedSize(Out) <- [%1d] \n", bConsumedSize);
				printf(log_msg);

				ch_data.Format("%1d", bConsumedSize);;
				sCH__DNET_INFO__SLAVE_X__OUT_SIZE[i]->Set__DATA(ch_data);
			}
			else
			{
				err_check__id = 12;

				sCH__DNET_INFO__SLAVE_X__OUT_SIZE[i]->Set__DATA("???");
			}
		}

		ch_data.Format("%1d", err_check__id);
		sCH__DNET_INFO__SLAVE_X__ERROR_CHECK_ID[i]->Set__DATA(ch_data);
	}

	// ...
	{
		ch_data.Format("%1d", total__in_byte);
		sCH__DNET_INFO__TOTAL_IN_BYTE->Set__DATA(ch_data);

		ch_data.Format("%1d", total__out_byte);
		sCH__DNET_INFO__TOTAL_OUT_BYTE->Set__DATA(ch_data);

		//
		log_msg.Format("  * Total In_Byte  <- [%1d] \n", total__in_byte );
		log_add.Format("  * Total Out_Byte <- [%1d] \n", total__out_byte);
		log_msg += log_add;

		printf(log_msg);
	}
	return 1;
}
