#pragma once


#define _CFG__CHART_INTENSITY			5

#define STR__ON					"ON"
#define STR__OFF				"OFF"


class CClass__EPD_CHART
{
private:
	int iSAMPLING_LIMIT;
	int iSAMPLING_COUNT;

	bool bACTIVE__EPD_CHECK;

	CII__VAR_STRING_CTRL*  pCH__CHART_EPD;
	CII__VAR_DIGITAL_CTRL* pCH__EPD_CHECK_ACTIVE;

	CII__VAR_STRING_CTRL* pCH__CHART_INTENSITY_X[_CFG__CHART_INTENSITY];
	CII__VAR_ANALOG_CTRL* pCH__DATA_INTENSITY_X[_CFG__CHART_INTENSITY];

	CII__VAR_STRING_CTRL* pCH__REPORT_EPD_RESULT;
	CII__VAR_STRING_CTRL* pCH__REPORT_EPD_SEC;

public:
	CClass__EPD_CHART()
	{
		iSAMPLING_LIMIT = 60 * 10;		// time : 60 sec, interval : 0.1 sec
		iSAMPLING_COUNT = 0;

		bACTIVE__EPD_CHECK = false;

		// CHART ...
		{
			pCH__CHART_EPD = NULL;
			pCH__EPD_CHECK_ACTIVE = NULL;

			for(int i=0; i<_CFG__CHART_INTENSITY; i++)
			{
				pCH__CHART_INTENSITY_X[i] = NULL;
			}
		}

		// MON ...
		{
			for(int i=0; i<_CFG__CHART_INTENSITY; i++)
			{
				pCH__DATA_INTENSITY_X[i] = NULL;
			}
		}

		// REPORT ...
		{
			pCH__REPORT_EPD_RESULT = NULL;
			pCH__REPORT_EPD_SEC = NULL;
		}
	}
	~CClass__EPD_CHART()
	{

	}

	// ...
	void Link__EPD_CHANNEL(CX__VAR_STRING_CTRL& ch_chart, CX__VAR_DIGITAL_CTRL& ch_state)
	{
		pCH__CHART_EPD = ch_chart.Get__PTR();
		pCH__EPD_CHECK_ACTIVE = ch_state.Get__PTR();
	}
	int Link__INTENSITY_CHANNEL(const int ch_index, CX__VAR_STRING_CTRL& ch_chart, CX__VAR_ANALOG_CTRL& ch_data)
	{
		if(ch_index <  0)							return -11;
		if(ch_index >= _CFG__CHART_INTENSITY)		return -12;

		pCH__CHART_INTENSITY_X[ch_index] = ch_chart.Get__PTR();
		pCH__DATA_INTENSITY_X[ch_index]  = ch_data.Get__PTR();
		return 1;
	}
	void Link__REPORT_CHANNEL(CX__VAR_STRING_CTRL& ch_result, CX__VAR_STRING_CTRL& ch_sec)
	{
		pCH__REPORT_EPD_RESULT = ch_result.Get__PTR();
		pCH__REPORT_EPD_SEC    = ch_sec.Get__PTR();
	}

	// ...
	void Clear__ALL_CHART()
	{
		iSAMPLING_COUNT = 0;
		
		bACTIVE__EPD_CHECK = false;

		if(pCH__CHART_EPD != NULL)
		{
			pCH__CHART_EPD->Set__DATA("");
		}

		for(int i=0; i<_CFG__CHART_INTENSITY; i++)
		{
			if(pCH__CHART_INTENSITY_X[i] != NULL)
				pCH__CHART_INTENSITY_X[i]->Set__DATA("");
		}

		if(pCH__REPORT_EPD_SEC != NULL)			
		{
			pCH__REPORT_EPD_SEC->Set__DATA("___");
		}
		if(pCH__REPORT_EPD_RESULT != NULL)
		{
			pCH__REPORT_EPD_RESULT->Set__DATA(STR__OFF);
		}
	}

	void Update__CHART_DATA(const double cur_sec)
	{
		CString chart_info;
		CString ch_data;

		bool active__count_over = false;

		if(iSAMPLING_COUNT > iSAMPLING_LIMIT)
		{
			active__count_over = true;
		}
		iSAMPLING_COUNT++;

		if(pCH__CHART_EPD != NULL)
		{
			chart_info = pCH__CHART_EPD->Get__STRING();

			if(active__count_over)
			{
				int s_index = chart_info.Find(',');
				if(s_index >= 0)		chart_info.Delete(0, s_index+1);
			}

			// ...
			bool active__end_check = false;

			if(pCH__EPD_CHECK_ACTIVE != NULL)
			{
				if(pCH__EPD_CHECK_ACTIVE->Check__DATA(STR__ON) > 0)			active__end_check = true;
			}

			if(active__end_check)
			{
				if(!bACTIVE__EPD_CHECK)
				{
					bACTIVE__EPD_CHECK = true;

					if(pCH__REPORT_EPD_SEC != NULL)			
					{
						ch_data.Format("%.2f", cur_sec);
						pCH__REPORT_EPD_SEC->Set__DATA(ch_data);
					}
					if(pCH__REPORT_EPD_RESULT != NULL)
					{
						pCH__REPORT_EPD_RESULT->Set__DATA(STR__ON);
					}
				}
			}

			ch_data.Format("%.2f/%1d,", cur_sec, active__end_check);
			chart_info += ch_data;
			pCH__CHART_EPD->Set__DATA(chart_info);;
		}

		for(int i=0; i<_CFG__CHART_INTENSITY; i++)
		{
			if((pCH__CHART_INTENSITY_X[i] != NULL)
				&& (pCH__DATA_INTENSITY_X[i]  != NULL))
			{
				chart_info = pCH__CHART_INTENSITY_X[i]->Get__STRING();

				if(active__count_over)
				{
					int s_index = chart_info.Find(',');
					if(s_index >= 0)		chart_info.Delete(0, s_index+1);
				}

				double cur_value = pCH__DATA_INTENSITY_X[i]->Get__VALUE();				
				ch_data.Format("%.2f/%.0f,", cur_sec, cur_value);

				chart_info += ch_data;
				pCH__CHART_INTENSITY_X[i]->Set__DATA(chart_info);
			}
		}		
	}
};
