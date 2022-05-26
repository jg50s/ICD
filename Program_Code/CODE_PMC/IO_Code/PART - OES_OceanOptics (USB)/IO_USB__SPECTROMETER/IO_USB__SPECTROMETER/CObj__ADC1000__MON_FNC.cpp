#include "StdAfx.h"
#include "CObj__ADC1000.h"



//-------------------------------------------------------------------------	
int CObj__ADC1000
::MON__MAKE_EPD_SIGNAL_THREAD(CII_OBJECT__VARIABLE *p_variable,
							  CII_OBJECT__ALARM *p_alarm)
{
	// ... Program Loading Wait ...
	Sleep(5000);

	if(iACTIVE_SIM > 0)
	{
		diCH__COMM_STS->Set__DATA("Online");
	}

	// ...
	CString str_data;

	double opr1_data = 0;
	double opr2_data = 0;
	double epd_data  = 0;

	int opr1_idx = 0;
	int opr2_idx = 0;


	while(1)
	{
		bool active__err_check = true;
		if(dCH__CFG_PART_USE->Check__DATA(STR__YES) < 0)		active__err_check = false;

		//
		if(dCH__CFG_BASIC_FUNCTION->Check__DATA("USE") > 0)
		{
			dCH__CFG_BASIC_OPERAND1->Get__DATA(str_data);
			opr1_idx = GetSpecSignalIndex(str_data);

			dCH__CFG_BASIC_OPERAND2->Get__DATA(str_data);
			opr2_idx = GetSpecSignalIndex(str_data);

			aCH__SPEC_FILTERED_DATA[opr1_idx]->Get__DATA(str_data);
			opr1_data = atof(str_data);

			aCH__SPEC_FILTERED_DATA[opr2_idx]->Get__DATA(str_data);
			opr2_data = atof(str_data);

			dCH__CFG_BASIC_OPERATOR->Get__DATA(str_data);
			if(str_data.CompareNoCase("+") == 0)
			{
				epd_data = opr1_data + opr2_data;
				aCH__EPD_SIGNAL->Set__VALUE(epd_data);
			}
			else if(str_data.CompareNoCase("-") == 0)
			{
				epd_data = opr1_data - opr2_data;
				aCH__EPD_SIGNAL->Set__VALUE(epd_data);
			}
			else if(str_data.CompareNoCase("*") == 0)
			{
				epd_data = opr1_data * opr2_data;
				aCH__EPD_SIGNAL->Set__VALUE(epd_data);
			}
			else 
			{
				if(opr2_data < 0.01)
				{
					opr2_data = 0.01;
				}

				epd_data = opr1_data / opr2_data;
				aCH__EPD_SIGNAL->Set__VALUE(epd_data);
			}
		}
		
		aCH__EPD_SIGNAL->Set__DATA("0.0");

		if(active__err_check)
		{
			if(diCH__COMM_STS->Check__DATA("Online") < 0)
			{
				Alarm__CHECK__POST(p_alarm, ALID__OFFLINE_ALARM);
			}
		}

		Sleep(10);
	}

	return 1;
}

int CObj__ADC1000
::GetSpecSignalIndex(CString str_name)
{
	int idx = atoi(str_name.Mid(2, 1)) - 1;

	if(idx < 0 || idx > 7)
	{
		idx = 0;
	}
	return idx;
}

int CObj__ADC1000
::MON__FILTER_THREAD(CII_OBJECT__VARIABLE *p_variable,
					 CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;
	double nor_time = 0;

	int fir_count = 0;
	double f_data = 0;

	double iir_coef = 0;
	double dbCfg_Width_Ib = 0;
	double dbBoxCar_Width = 0;
	int multi_sample = 0;

	CString filter[MAX_SPECTRUM_COUNT];
	double raw_data_t[MAX_SPECTRUM_COUNT][32] = { 0, };
	double PreIIRData[MAX_SPECTRUM_COUNT] = { 0, };
	double PreNorData[MAX_SPECTRUM_COUNT] = { 0, };
	double PreFirNorData[MAX_SPECTRUM_COUNT] = { 0, };
	double PreIIRNorData[MAX_SPECTRUM_COUNT] = { 0, };
	int	   nor_count[MAX_SPECTRUM_COUNT] = { 0, };
	int	   nor_Fircount[MAX_SPECTRUM_COUNT] = { 0, };
	int	   nor_IIRcount[MAX_SPECTRUM_COUNT] = { 0, };

	CString str_ccd_gain;

	if(iACTIVE_SIM > 0)
	{
		for(int i=0; i<MAX_SPECTRUM_COUNT; i++)
		{
			aiCH__Spectrum[i]->Set__DATA("10000");
		}
	}

	//
	bool active__snap_shot = false;

	SCX__ASYNC_TIMER_CTRL x_timer__snap_shot;
	x_timer__snap_shot->REGISTER__COUNT_CHANNEL_NAME(sCH__CUR_SNAP_SHOT_TIME_COUNT->Get__CHANNEL_NAME());


	while(1)
	{
		// ...
		{
			double cfg_msec = aCFG_OES_SNAP_SHOP_GET_DATA_DELAY->Get__VALUE();
			double sample_sec = cfg_msec / 1000.0;

			p_variable->Wait__SINGLE_OBJECT(sample_sec);
		}


		// CCD Gain Config SET ...
		dCH__CFG_CCD_GAIN->Get__DATA(str_data);
		doCH__CCD_GAIN->Get__DATA(str_ccd_gain);
		if(str_data.CompareNoCase(str_ccd_gain) != 0)
		{
			doCH__CCD_GAIN->Set__DATA(str_data);
		}

		if(dCH__OES_SUM_MODE->Check__DATA("OFF") > 0)
		{
			// Set width
			aCH__CFG_WIDTH_IB[0]->Get__DATA(str_data);

			if(aoCH__BoxCar_Width->Check__DATA(str_data) < 0)
			{
				aoCH__BoxCar_Width->Set__DATA(str_data);		// 0
			}
		}
		else
		{
			aoCH__BoxCar_Width->Set__DATA("0");		// 0
		}

		// Set multi sampling
		aCH__CFG_MULTI_SAMPLE->Get__DATA(str_data);
		if(aoCH__Scan_Average->Check__DATA(str_data) < 0)
		{	
			aoCH__Scan_Average->Set__DATA(str_data);		// 1
		}

		if(sCH__REQ_SNAP_SHOT_CHECK->Check__DATA(STR__YES_START) > 0)
		{
			if(!active__snap_shot)
			{
				active__snap_shot = true;

				str_data = dCH__PARA_SNAP_SHOT_MODE->Get__STRING();
				sCH__CUR_SNAP_SHOT_MODE->Set__DATA(str_data);

				aCH__CFG_SNAP_SHOT_TIME_COUNT->Get__DATA(str_data);
				sCH__CUR_SNAP_SHOT_TIME_COUNT->Set__DATA(str_data);
				double cfg_sec = atof(str_data);

				if(sCH__CUR_SNAP_SHOT_MODE->Check__DATA("AUTO") > 0)
					x_timer__snap_shot->START__COUNT_DOWN(cfg_sec);
				else
					x_timer__snap_shot->STOP_ZERO();

				sCH__ACTIVE_SNAP_SHOT_CHECK->Set__DATA("YES");
			}
	
			Fnc__SNAP_SHOT(p_variable, p_alarm);

			if(x_timer__snap_shot->Get__CURRENT_TIME() < 1.0)
			{
				x_timer__snap_shot->STOP_ZERO();

				sCH__REQ_SNAP_SHOT_CHECK->Set__DATA("");
				sCH__ACTIVE_SNAP_SHOT_CHECK->Set__DATA("");

				active__snap_shot = false;
			}
		}
		else if(sCH__REQ_SNAP_SHOT_CHECK->Check__DATA(STR__YES_ABORT) > 0)
		{
			x_timer__snap_shot->STOP_ZERO();

			sCH__REQ_SNAP_SHOT_CHECK->Set__DATA("");
			sCH__ACTIVE_SNAP_SHOT_CHECK->Set__DATA("");

			active__snap_shot = false;
		}

		// ...
		aiCH__Spectrum_Total->Get__DATA(str_data);

		for(int i=0; i<MAX_SPECTRUM_COUNT; i++)
		{
			// ... Filtered Data Holding Problem Block by wjkim
			if(aCH__CFG_IB_USE[i]->Check__DATA("Yes") < 0)
			{
				if(i != 0)		// ... IB 1 is Always Use ...
				{
					Sleep(9);
					continue;
				}
			}

			// Get Filter
			dCH__SPEC_FILTER[i]->Get__DATA(filter[i]);

			// Maintain raw-data (fir-count)
			aCH__CFG_FIR_COUNT[i]->Get__DATA(str_data);
			fir_count = atoi(str_data)+1;
			aiCH__Spectrum[i]->Get__DATA(str_data);
			raw_data_t[i][fir_count-1] = atoi(str_data);

			// Maintain iir-data
			aCH__CFG_IIR_COEFFICIENT[i]->Get__DATA(str_data);
			iir_coef = atof(str_data);
			PreIIRData[i] = ((1-iir_coef) * PreIIRData[i]) + (iir_coef*raw_data_t[i][fir_count-1]);

			// Check filter	- NONE FIR IIR Normalize FIRNormalize IIRNormalize
			if(filter[i].CompareNoCase("FIR") == 0)
			{
				// sum all data				
				f_data = .0;
				for(int j=fir_count-1; j>=0; j--)
				{
					f_data += raw_data_t[i][j];
				}

				f_data = f_data/fir_count;
				aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(f_data);
			}
			else if(filter[i].CompareNoCase("IIR") == 0)
			{				
				aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(PreIIRData[i]);
			}
			else if(filter[i].CompareNoCase("Normalize") == 0)
			{
				// Maintain nor-data
				aCH__CFG_NORMAL_TIME[i]->Get__DATA(str_data);
				nor_time = atof(str_data);
				nor_count[i]++;
				aiCH__Spectrum[i]->Get__DATA(str_data);
				PreNorData[i] +=  atof(str_data);

				if((nor_time*5) <= (nor_count[i])*2)
				{
					aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(PreNorData[i]/(nor_count[i]));

					nor_count[i] = 0;
					PreNorData[i] = 0;
				}
			}
			else if(filter[i].CompareNoCase("FIRNormalize") == 0)
			{
				// sum all data
				for(int j=fir_count-1; j>=0; j--)
				{
					f_data += raw_data_t[i][j];
				}

				f_data = f_data/fir_count;
				PreFirNorData[i] +=  f_data;

				aCH__CFG_NORMAL_TIME[i]->Get__DATA(str_data);
				nor_time = atof(str_data);				
				nor_Fircount[i]++;

				if((nor_time*5) <= (nor_Fircount[i]*2))
				{
					aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(PreFirNorData[i]/(nor_Fircount[i]));

					nor_Fircount[i] = 0;
					PreFirNorData[i] = 0;
				}
			}
			else if(filter[i].CompareNoCase("IIRNormalize") == 0)
			{				
				PreIIRNorData[i] +=  f_data;

				aCH__CFG_NORMAL_TIME[i]->Get__DATA(str_data);
				nor_time = atof(str_data);
				nor_IIRcount[i]++;

				if((nor_time*5) <= (nor_IIRcount[i]*2))
				{
					aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(PreIIRNorData[i]/(nor_IIRcount[i]));

					nor_IIRcount[i] = 0;
					PreIIRNorData[i] = 0;
				}
			}
			else // filter none
			{
				aCH__SPEC_FILTERED_DATA[i]->Set__VALUE(raw_data_t[i][fir_count-1]);
			}

			// delete first data
			for(int k=0; k<fir_count; k++)
			{
				raw_data_t[i][k] = raw_data_t[i][k+1];
			}

			if(filter[i].Find("Normalize") < 0)
			{
				nor_count[i]	= 0;
				PreNorData[i]	= 0;
				nor_Fircount[i] = 0;
				PreFirNorData[i]= 0;
				nor_IIRcount[i] = 0;
				PreIIRNorData[i]= 0;
			}
		}
	}

	return 1;
}

int CObj__ADC1000
::Fnc__SNAP_SHOT(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	CString str_display = "";
	CString str_data;

	double* pSpectrums   = m_SpectrumArrary.getDoubleValues();
	double* pWaveLengths = m_WaveLength.getDoubleValues();

	// x1/y1,x2/y2,...xn/yn (x=wavelength, y=spectrum, n=2048)
	if(iACTIVE_SIM > 0)
	{
		for(int i=0; i<2048; i++)
		{
			double y_value = (rand() % 100) + 1000.0;

			str_data.Format("%1d/%.3f,", i+1,y_value);
			str_display += str_data;
		}
	}
	else
	{
		for(int i=0; i<m_SpectrumArrary.getLength(); i++)
		{
			str_data.Format("%.3f/%.3f,", pWaveLengths[i],pSpectrums[i]);
			str_display += str_data;
		}
	}

	str_display.TrimRight(",");
	sCH__OES_SNAP_SHOP_GRAPH_DISPLAY->Set__DATA(str_display);
	return 1;
}

int CObj__ADC1000
::MON__DARK_CTRL(CII_OBJECT__VARIABLE *p_variable,
				 CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	int use_flag = -1;

	while(1)
	{
		Sleep(500);

		if(dCH__CFG_ZERO_CAL_USE->Check__DATA(STR__NO) > 0)
		{
			if(use_flag > 0)
			{
				use_flag = 1;

				sCH__Gui_Cal_Value->Set__DATA("0");
				doCH__SET_Dark->Set__DATA(STR__Disable);
			}
		}
		else
		{
			use_flag = 1;
		}

		if(sCH__EPD_BIAS_VOLT_CAL_REQ->Check__DATA(STR__YES) > 0)
		{
			if(dCH__CFG_ZERO_CAL_USE->Check__DATA(STR__YES) > 0)
			{
				doCH__SET_Dark->Set__DATA(STR__Disable);
				Sleep(2000);

				aiCH__Spectrum[1]->Get__DATA(var_data);
				sCH__Gui_Cal_Value->Set__DATA(var_data);

				doCH__SET_Dark->Set__DATA(STR__Enable);
			}

			sCH__EPD_BIAS_VOLT_CAL_REQ->Set__DATA("");
		}
		else if(sCH__EPD_BIAS_VOLT_CAL_REQ->Check__DATA(STR__NO) > 0)
		{
			sCH__Gui_Cal_Value->Set__DATA("0");

			if(dCH__CFG_ZERO_CAL_USE->Check__DATA(STR__YES) > 0)
			{
				doCH__SET_Dark->Set__DATA(STR__Disable);
			}

			sCH__EPD_BIAS_VOLT_CAL_REQ->Set__DATA("");
		}
	}

	return 1;	
}
