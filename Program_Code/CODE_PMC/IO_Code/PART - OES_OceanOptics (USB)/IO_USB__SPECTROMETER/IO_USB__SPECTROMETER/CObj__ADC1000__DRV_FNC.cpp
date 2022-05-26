#include "StdAfx.h"
#include "CObj__ADC1000.h"



//-------------------------------------------------------------------------	
int CObj__ADC1000
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	CString log_msg;
	CString log_bff;

	int log_flag = -1;
	int i, j;

	if(dCH__JGLEE_LOG->Check__DATA("START") > 0)
	{
		log_flag = 1;
	}

	if(Check_OES_Open() < 0)
	{
		log_msg = "OES Not Open ret:-1";
		xLOG_CTRL->WRITE__LOG(log_msg);

		return -1;
	}

	// ...
	CString str_data;
	int arr_waveLength[MAX_SPECTRUM_COUNT];
	int arr_spectrumIndex[MAX_SPECTRUM_COUNT];

	for(i=0; i<MAX_SPECTRUM_COUNT; i++)
	{
		aCH__CFG_IB_WAVELENGTH[i]->Get__DATA(str_data);
		arr_waveLength[i] = atoi(str_data);
		arr_spectrumIndex[i] = 0;
	}
	
	// ...
	m_WaveLength = wrapper.getWavelengths(SPECTRUM_INDEX);
	double* pWaveLengths = m_WaveLength.getDoubleValues();

	for(j=0; j<MAX_SPECTRUM_COUNT; j++)
	{
		for(i=0; i<m_WaveLength.getLength(); i++)
		{
			if( pWaveLengths[i] >= arr_waveLength[j])
			{
				arr_spectrumIndex[j] = i;
				break;
			}
		}
	}

	// Retreives the spectrum from the first spectrometer
	m_SpectrumArrary = wrapper.getSpectrum(SPECTRUM_INDEX);

	// Sets numberOfPixels to the length of the spectrumArray 
	int numberOfPixels = m_SpectrumArrary.getLength();

	// ...
	{
		log_msg = "";

		for(j=0; j<MAX_SPECTRUM_COUNT; j++)
		{
			if(numberOfPixels < arr_spectrumIndex[j])
			{
				// ...
				{
					log_bff.Format("IB%d Read Wave Length Failed. (%d) \n", j+1, numberOfPixels);
					log_msg += log_bff;
				}
			
				m_nCommSts = OFFLINE;
				return -1;
			}
		}
		m_nCommSts = ONLINE;

		if(log_msg.GetLength() > 0)
		{
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	
	// Sets a pointer to the values of the Spectrum array 
	double *pSpectrums = m_SpectrumArrary.getDoubleValues();

	// Broad Band - Check ...
	{
		int count = 0;
		double sampling_data = 0;
		double normal_value = 0;

		for(i=0; i<m_SpectrumArrary.getLength(); i++)
		{
			sampling_data = pSpectrums[i];
			count++;
		
			if(count == 1)
			{
				normal_value = sampling_data;
			}
			else
			{
				double pre_n = (double) (count - 1.0);
				double cur_n = (double) (count);

				double pre_y = normal_value;
				double pre_x = sampling_data / pre_n;

				normal_value = (pre_n / cur_n) * (pre_y + pre_x);
			}
		}
	
		CString cur_data;
		cur_data.Format("%.1f", normal_value);
		aCH__OES_BROADBAND_SIGNAL_AVG->Set__DATA(cur_data);
	}
	
	if(log_flag > 0)
	{
		log_msg = "";
		log_msg += "All Data : [Index/Wave_Length/Spectrum] ... \n";

		for(i=0; i<m_WaveLength.getLength(); i++)
		{
			log_bff.Format("[%1d/%.1f/%.1f] ", 
						   i, pWaveLengths[i], pSpectrums[i]);
			log_msg += log_bff;
		}

		log_msg += "\n\n";

		// ...
		CString cur_data;
		aCH__OES_BROADBAND_SIGNAL_AVG->Get__DATA(cur_data);

		log_bff.Format("OES Broadband Signal AVG. : [%s] ... \n", cur_data);
		log_msg += log_bff;

		log_msg += "\n\n";

		log_msg += "Spectrum Info. : [CH.ID/Wave_Length/Spectrum_Index] ... \n";

		for(i=0; i<MAX_SPECTRUM_COUNT; i++)
		{
			log_bff.Format("[%1d/%1d/%1d] ", 
						   i+1, arr_waveLength[i], arr_spectrumIndex[i]);
			log_msg += log_bff;
		}

		log_msg += "\n\n";
	}

	// ...
	double spec_data = .0;
	int count = 0;
	int sum_count;
	int start_pixel;
	double dblTemp = 0.0;
	double dblMin, dblMax;
	
	if(aiCH__Spectrum_Total->Check__VARIABLE_NAME(var_name) > 0)
	{
		for(j=0; j<MAX_SPECTRUM_COUNT; j++)
		{
			read_data = 0;

			// ...
			{
				dblMin =  1000000;
				dblMax = -1000000;
			}

			aCH__CFG_WIDTH_IB[0]->Get__DATA(str_data);

			if(log_flag > 0)
			{
				log_bff.Format("CH.ID : %1d \n", j+1);
				log_msg += log_bff;
			}

			if( (dCH__OES_SUM_MODE->Check__DATA("ON") > 0) 
			&& 	(atoi(str_data) > 0) )
			{
				aCH__CFG_WIDTH_IB[0]->Get__DATA(str_data);
				sum_count = (atoi(str_data)*3);

				start_pixel = arr_spectrumIndex[j] - (sum_count/2);
				for (i=0; i<sum_count;i++)
				{
					if(((start_pixel+i) > 0) 
					&& ((start_pixel+sum_count) < numberOfPixels))
					{
						dblTemp = pSpectrums[start_pixel+i];
					}
					else
					{
						dblTemp = 0;		// WaveLength Limit Over
					}
					
					if(dblMin > dblTemp)	dblMin = dblTemp;
					if(dblMax < dblTemp)	dblMax = dblTemp;

					read_data = read_data + dblTemp;					
				}

				if(dblMin ==  1000000)		dblMin = 0;
				if(dblMax == -1000000)		dblMax = 0;

				if(dCH__OES_MIN_MAX_DELETE->Check__DATA("ON") > 0)
				{
					read_data = read_data - dblMin - dblMax;
				}

				aiCH__Spectrum[j]->Set__VALUE(read_data);

				if(log_flag > 0)
				{
					log_bff.Format("   Sum_Count : %1d \n", sum_count);
					log_msg += log_bff;

					log_bff.Format("   Range (%1d, %1d) : NumberOfPixels (%1d) \n", 
								   start_pixel, (start_pixel+sum_count), numberOfPixels);
					log_msg += log_bff;
					
					for(i=0; i<sum_count;i++)
					{
						if(((start_pixel+i) > 0) 
						&& ((start_pixel+sum_count) < numberOfPixels))
						{
							log_bff.Format("   [%1d] <- %.1f \n", i,pSpectrums[start_pixel+i]);
							log_msg += log_bff;
						}
						else
						{
							log_bff.Format("   Over : [%1d] <- %.1f \n", i,0.0);
							log_msg += log_bff;
						}
					}

					log_bff.Format("   Read_Data (%.1f), dblMin (%.1f), dblMax (%.1f) \n",
								   read_data,
								   dblMin,
								   dblMax);
					log_msg += log_bff;
				}
			}
			else
			{
				read_data = pSpectrums[arr_spectrumIndex[j]];
				aiCH__Spectrum[j]->Set__VALUE(read_data);

				if(log_flag > 0)
				{
					log_bff.Format("   Read_Data (%.1f)  !!! \n", read_data);
					log_msg += log_bff;
				}
			}
		}

		if(log_flag > 0)
		{
			log_msg += "\n";

			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		return 1;
	}

	return -11;
}

int CObj__ADC1000
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	int spectrometerIndex = 0;
	int channelIndex = 0;

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommSts == OFFLINE)		read_data.Format("Offline");
		else							read_data.Format("Online");

		return 1;
	}
	if(diCH__Get_Dark->Check__VARIABLE_NAME(var_name) > 0)
	{
		boolean nRet = wrapper.getCorrectForElectricalDark(spectrometerIndex, channelIndex);

		if (nRet == TRUE)					read_data = "Enable";
		else								read_data = "Disable";

		return 1;
	}

	return -1;
}

int CObj__ADC1000
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str_log;
	Coefficients coef;

	if(Check_OES_Open() < 0)
	{
		// ...
		{
			CString log_msg;

			log_msg = "OES Not Open ret:-1";
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
		
		return -1;
	}

	// Information ...
	WRAPPER_T wrapperHandle;

	int buildNumber;
	int numberOfSpectrometersAttached;

	wrapperHandle = Wrapper_Create();
	JSTRING apiVersion = JString_Create();
	
	// 1. Build Number..
	{
		buildNumber = Wrapper_getBuildNumber(wrapperHandle);
		
		str_log.Format("build number = %d\n",buildNumber);
		xLOG_CTRL->WRITE__LOG(str_log);
	}

	// 2. API Version
	{
		Wrapper_getApiVersion(wrapperHandle,apiVersion);
	}

	// 3. 장착된 스페트로미터 갯수..
	{
		numberOfSpectrometersAttached = Wrapper_openAllSpectrometers(wrapperHandle);
	}

	// 4. We will arbitrarily use the first attached spectrometer
	int spectrometerIndex = 0;

	// 5. Display some information about this spectrometer
	JSTRING firmwareVersion = JString_Create();
	JSTRING serialNumber = JString_Create();
	JSTRING spectrometerName = JString_Create();
	
	Wrapper_getSerialNumber(wrapperHandle,spectrometerIndex,serialNumber);
	Wrapper_getName(wrapperHandle,spectrometerIndex,spectrometerName);
	Wrapper_getFirmwareVersion(wrapperHandle,spectrometerIndex,firmwareVersion);
	
	JString_Destroy(apiVersion);
	JString_Destroy(firmwareVersion);
	JString_Destroy(serialNumber);
	JString_Destroy(spectrometerName);

	double wavelengthIntercept = Wrapper_getWavelengthIntercept(wrapperHandle,0);
	double wavelengthCoefficient1 = Wrapper_getWavelengthFirst(wrapperHandle,0);
	double wavelengthCoefficient2 = Wrapper_getWavelengthSecond(wrapperHandle,0);
	double wavelengthCoefficient3 = Wrapper_getWavelengthThird(wrapperHandle,0);
	
	double intercept = 0;
	double first_coef = 0;
	double second_coef = 0;


	if(siCH__GET_INTERCEPT->Check__VARIABLE_NAME(var_name) > 0)
	{
		intercept = wavelengthIntercept;
		read_data.Format("%f", intercept);
	}
	else if(siCH__GET_FIRST_COEFF->Check__VARIABLE_NAME(var_name) > 0)
	{
		first_coef = wavelengthCoefficient1;
		read_data.Format("%.10f", first_coef);
	}
	else if(siCH__GET_SECOND_COEFF->Check__VARIABLE_NAME(var_name) > 0)
	{
		second_coef = wavelengthCoefficient2;
		read_data.Format("%.10f", second_coef);
	}
	else
	{
		return -1;
	}

	return 1;
}


//-------------------------------------------------------------------------	
int CObj__ADC1000
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString log_msg;

	if(Check_OES_Open() < 0)
	{
		log_msg = "OES Not Open ret:-1";
		xLOG_CTRL->WRITE__LOG(log_msg);

		return -1;
	}

	// ...
	int nIndex = atoi(io_info.sCOMMAND1);

	// ...
	CString str_data;

	aCH__CFG_IB_WAVELENGTH[nIndex]->Get__DATA(str_data);
	int waveLength = atoi(str_data);
	int spectrumIndex = 0;
	
	DoubleArray m_WaveLength = wrapper.getWavelengths(SPECTRUM_INDEX);
	
	double * pWaveLengths = m_WaveLength.getDoubleValues();
	for(int i=0; i<m_WaveLength.getLength(); i++)
	{
		if( pWaveLengths[i] >= waveLength)
		{
			spectrumIndex = i;
			break;
		}
	}
	
	if(aoCH__BoxCar_Width->Check__VARIABLE_NAME(var_name) > 0)
	{
		int witdh = static_cast<int>(set_data);
		wrapper.setBoxcarWidth(SPECTRUM_INDEX, witdh);

		// ...
		{
			log_msg.Format("Set Boxcar Index: %d, Width: %d", waveLength, witdh);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	else if(aoCH__Scan_Average->Check__VARIABLE_NAME(var_name) > 0)
	{
		int sample_count = static_cast<int>(set_data);
		wrapper.setScansToAverage(SPECTRUM_INDEX, sample_count);

		// ...
		{
			log_msg.Format("Set Multi-Sampling Index: %d, Count: %d", waveLength, sample_count);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	else
	{
		return -1;
	}

	return 1;
}

int CObj__ADC1000
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString log_msg;

	if(Check_OES_Open() < 0)
	{
		log_msg = "OES Not Open ret:-1";
		xLOG_CTRL->WRITE__LOG(log_msg);

		return -1;
	}

	if(doCH__CCD_GAIN->Check__VARIABLE_NAME(var_name) > 0)
	{
		double integ_time;
		if(set_data.CompareNoCase("0") == 0)
			integ_time = 5.6;	
		else if(set_data.CompareNoCase("1") == 0)
			integ_time = 8.0;   
		else if(set_data.CompareNoCase("2") == 0)
			integ_time = 11.2;   
		else if(set_data.CompareNoCase("3") == 0)
			integ_time = 16.0;
		else if(set_data.CompareNoCase("4") == 0)
			integ_time = 22.4;
		else if(set_data.CompareNoCase("5") == 0)
			integ_time = 32.0;
		else if(set_data.CompareNoCase("6") == 0)
			integ_time = 44.8;
		else if(set_data.CompareNoCase("7") == 0)
			integ_time = 64.0;

		int usec = static_cast<int>(integ_time * 1000);
		wrapper.setIntegrationTime(0, usec);

		// ...
		{
			log_msg.Format("Set Integration Time: %.3f msec", integ_time);
			xLOG_CTRL->WRITE__LOG(log_msg);
		}
	}
	else if(doCH__SET_COEFFICIENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("Set") == 0)
		{
			CString str_data;
			double intercept = 0;
			double first_coef = 0;
			double second_coef = 0;

			sCH__CFG_OES_MASTER_CCD_INTERCEPT->Get__DATA(str_data);
			intercept = atof(str_data);

			sCH__CFG_OES_MASTER_CCD_FIRST_COEFFICENT->Get__DATA(str_data);
			first_coef = atof(str_data);

			sCH__CFG_OES_MASTER_CCD_SECOND_COEFFICENT->Get__DATA(str_data);
			second_coef = atof(str_data);

			Coefficients coef;
			coef.setWlIntercept(intercept);
			coef.setWlFirst(first_coef);
			coef.setWlSecond(second_coef);
			coef.setStrayLight(3.0);	// 

			JString str;
			str.setASCII("Mat429sky");
			wrapper.insertKey(str);
			wrapper.setCalibrationCoefficientsIntoEEProm(0, coef,true, true, true);
		}
		else
		{
			return -1;
		}
	}
	else if(doCH__SET_Dark->Check__VARIABLE_NAME(var_name) > 0)
	{
		if (set_data.CompareNoCase("Enable") == 0)
		{
			int nSpectrometerIndex = 0;
			int enable = 1;

			wrapper.setCorrectForElectricalDark(nSpectrometerIndex, enable);
		}
		else 
		{
			int nSpectrometerIndex = 0;
			int enable = 0;

			wrapper.setCorrectForElectricalDark(nSpectrometerIndex, enable);
		}
	}
	else
	{
		return -1;
	}

	return 1;
}

int CObj__ADC1000
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	CString log_msg;

	if(Check_OES_Open() < 0)
	{
		log_msg = "OES Not Open ret:-1";
		xLOG_CTRL->WRITE__LOG(log_msg);

		return -1;
	}

	return 1;
}
