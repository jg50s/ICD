#pragma once

#include "Interface_Code.h"


class CLink__Error_Common
{
public:
	CII__VAR_DIGITAL_CTRL* pCH__CFG_USE;
	CII__VAR_DIGITAL_CTRL* pCH__ACTIVE_CHECK;

	CII__VAR_ANALOG_CTRL*  pCH__CFG_TOLERANCE_ZERO_PERCENT;

	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_DELAY_SEC;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_CHECK_SEC;

	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_MIN;
	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_MAX;

	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_MIN;
	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_MAX;

	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_DELAY_SEC;
	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_CHECK_SEC;

public:
	CLink__Error_Common()
	{
		pCH__CFG_USE = NULL;
		pCH__ACTIVE_CHECK = NULL;

		pCH__CFG_TOLERANCE_ZERO_PERCENT = NULL;

		pCH__CFG_STABLE_DELAY_SEC = NULL;
		pCH__CFG_STABLE_CHECK_SEC = NULL;

		pCH__CUR_STABLE_MIN = NULL;
		pCH__CUR_STABLE_MAX = NULL;

		pCH__CUR_ERROR_MIN = NULL;
		pCH__CUR_ERROR_MAX = NULL;

		pCH__CUR_STABLE_DELAY_SEC = NULL;
		pCH__CUR_STABLE_CHECK_SEC = NULL;
	}
};

class CLink__Error_Para
{
public:
	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_DATA_PERCENT;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_TOLERANCE_DATA_PERCENT;

	CII__VAR_ANALOG_CTRL*  pCH__CFG_ERROR_CHECK_SEC;
	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_CHECK_SEC;

public:
	CLink__Error_Para()
	{
		pCH__CFG_STABLE_DATA_PERCENT    = NULL;
		pCH__CFG_TOLERANCE_DATA_PERCENT = NULL;

		pCH__CFG_ERROR_CHECK_SEC  = NULL;
		pCH__CUR_ERROR_CHECK_SEC  = NULL;
	}
};

class CClass__Error_Report
{
public:
	double dSet_VALUE;
	double dCurrent_VALUE;

	double dError_PERCENT;
	double dError_THRESHOLD;
	double dError_SEC;
	double dError_MIN;
	double dError_MAX;

	double dRange_MIN;
	double dRange_MAX;
	int iRange_DEC;
};


class CClass__Error_Timer
{
private:
	double _Set_VALUE;
	double _Current_VALUE;

	double _Error_PERCENT;
	double _Error_THRESHOLD;
	double _Error_SEC;
	double _Error_MIN;
	double _Error_MAX;

	double _Range_MIN;
	double _Range_MAX;
	int _Range_DEC;

private:
	// ...
	bool bActive__MAX_RANGE;
	bool bActive__ERROR_THRESHOLD;

	// ...
	double dPre__Set_Value;

	bool bActive__Delay_Check;
	bool bActive__Stable_State;
	bool bActive__Checking_State;
	bool bActive__Error_State;

	SCX__ASYNC_TIMER_CTRL mCtrl__Delay_Timer;
	SCX__ASYNC_TIMER_CTRL mCtrl__Checking_Timer;
	SCX__ASYNC_TIMER_CTRL mCtrl__Error_Timer;

	// ...
	CII__VAR_ANALOG_CTRL*  pCH__REF_CHANNEL_SET__ANALOG;
	CII__VAR_STRING_CTRL*  pCH__REF_CHANNEL_SET__STRING;
	CII__VAR_ANALOG_CTRL*  pCH__REF_CHANNEL_GET__ANALOG;
	CII__VAR_STRING_CTRL*  pCH__REF_CHANNEL_GET__STRING;

	CII__VAR_ANALOG_CTRL*  pCH__REF_CHANNEL_RANGE;

	// ...
	CII__VAR_DIGITAL_CTRL* pCH__CFG_USE;
	CII__VAR_DIGITAL_CTRL* pCH__ACTIVE_CHECK;

	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_DATA_PERCENT;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_TOLERANCE_DATA_PERCENT;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_TOLERANCE_ZERO_PERCENT;

	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_DELAY_SEC;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_STABLE_CHECK_SEC;
	CII__VAR_ANALOG_CTRL*  pCH__CFG_ERROR_CHECK_SEC;

	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_MIN;
	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_MAX;

	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_MIN;
	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_MAX;

	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_DELAY_SEC;
	CII__VAR_STRING_CTRL*  pCH__CUR_STABLE_CHECK_SEC;
	CII__VAR_STRING_CTRL*  pCH__CUR_ERROR_CHECK_SEC;
	//

public:
	CClass__Error_Timer()
	{
		bActive__MAX_RANGE = false;
		bActive__ERROR_THRESHOLD = false;

		// ...
		{
			_Set_VALUE = 0.0;
			_Current_VALUE = 0.0;

			_Error_PERCENT = 0.0;
			_Error_THRESHOLD = 0.0;
			_Error_SEC = 0.0;
			_Error_MIN = 0.0;
			_Error_MAX = 0.0;

			_Range_MIN = 0.0;
			_Range_MAX = 0.0;
			_Range_DEC = 0;
		}

		// ...
		{
			pCH__REF_CHANNEL_SET__ANALOG = NULL;
			pCH__REF_CHANNEL_SET__STRING = NULL;
			pCH__REF_CHANNEL_GET__ANALOG = NULL;
			pCH__REF_CHANNEL_GET__STRING = NULL;

			pCH__REF_CHANNEL_RANGE = NULL;

			//
			pCH__CFG_USE = NULL;
			pCH__ACTIVE_CHECK = NULL;

			//
			pCH__CFG_STABLE_DATA_PERCENT    = NULL;
			pCH__CFG_TOLERANCE_DATA_PERCENT = NULL;
			pCH__CFG_TOLERANCE_ZERO_PERCENT = NULL;

			pCH__CFG_STABLE_DELAY_SEC = NULL;
			pCH__CFG_STABLE_CHECK_SEC = NULL;
			pCH__CFG_ERROR_CHECK_SEC  = NULL;

			pCH__CUR_STABLE_MIN = NULL;
			pCH__CUR_STABLE_MAX = NULL;

			pCH__CUR_ERROR_MIN = NULL;
			pCH__CUR_ERROR_MAX = NULL;

			pCH__CUR_STABLE_DELAY_SEC = NULL;
			pCH__CUR_STABLE_CHECK_SEC = NULL;
			pCH__CUR_ERROR_CHECK_SEC  = NULL;
		}

		_Init__Error_State();
	}
	~CClass__Error_Timer()
	{

	}

	//============================================================================
	void Init()
	{
		_Init__Timer();
		_Init__Error_State();
	}
	void Reset()
	{
		_Init__Error_State();
	}

	bool IsStable()
	{
		return bActive__Stable_State;
	}

	void Enable__MAX_RANGE()
	{
		bActive__MAX_RANGE = true;
	}
	void Disable__MAX_RANGE()
	{
		bActive__MAX_RANGE = false;
	}

	void Enable__ERROR_THRESHOLD()
	{
		bActive__ERROR_THRESHOLD = true;
	}
	void Disable__ERROR_THRESHOLD()
	{
		bActive__ERROR_THRESHOLD = false;
	}

	// ...
	void Link__REF_OUT_CHANNEL(CX__VAR_ANALOG_CTRL& x_ch)
	{
		pCH__REF_CHANNEL_SET__ANALOG = x_ch.Get__PTR();
	}
	void Link__REF_OUT_CHANNEL(CX__VAR_STRING_CTRL& x_ch)
	{
		pCH__REF_CHANNEL_SET__STRING = x_ch.Get__PTR();
	}

	void Link__REF_IN_CHANNEL(CX__VAR_ANALOG_CTRL& x_ch)
	{
		pCH__REF_CHANNEL_GET__ANALOG = x_ch.Get__PTR();
	}
	void Link__REF_IN_CHANNEL(CX__VAR_STRING_CTRL& x_ch)
	{
		pCH__REF_CHANNEL_GET__STRING = x_ch.Get__PTR();
	}

	void Link__REF_RANGE_CHANNEL(CX__VAR_ANALOG_CTRL& x_ch)
	{
		pCH__REF_CHANNEL_RANGE = x_ch.Get__PTR();
	}

	void Link__ERROR_COMMON(CLink__Error_Common* p_link)
	{
		pCH__CFG_USE      = p_link->pCH__CFG_USE;
		pCH__ACTIVE_CHECK = p_link->pCH__ACTIVE_CHECK;

		pCH__CFG_TOLERANCE_ZERO_PERCENT = p_link->pCH__CFG_TOLERANCE_ZERO_PERCENT;

		pCH__CFG_STABLE_DELAY_SEC = p_link->pCH__CFG_STABLE_DELAY_SEC;
		pCH__CFG_STABLE_CHECK_SEC = p_link->pCH__CFG_STABLE_CHECK_SEC;

		pCH__CUR_STABLE_MIN = p_link->pCH__CUR_STABLE_MIN;
		pCH__CUR_STABLE_MAX = p_link->pCH__CUR_STABLE_MAX;

		pCH__CUR_ERROR_MIN = p_link->pCH__CUR_ERROR_MIN;
		pCH__CUR_ERROR_MAX = p_link->pCH__CUR_ERROR_MAX;

		pCH__CUR_STABLE_DELAY_SEC = p_link->pCH__CUR_STABLE_DELAY_SEC;
		pCH__CUR_STABLE_CHECK_SEC = p_link->pCH__CUR_STABLE_CHECK_SEC;
	}
	void Link__ERROR_PARA(CLink__Error_Para* p_link)
	{
		pCH__CFG_STABLE_DATA_PERCENT    = p_link->pCH__CFG_STABLE_DATA_PERCENT;
		pCH__CFG_TOLERANCE_DATA_PERCENT = p_link->pCH__CFG_TOLERANCE_DATA_PERCENT;

		pCH__CFG_ERROR_CHECK_SEC = p_link->pCH__CFG_ERROR_CHECK_SEC;
		pCH__CUR_ERROR_CHECK_SEC = p_link->pCH__CUR_ERROR_CHECK_SEC;
	}

	bool Check__Error_State()
	{
		_Check__Error_State();

		return _Check__Error_Time();
	}	

	void Get__ERROR_REPORT(CClass__Error_Report* p_report)
	{
		p_report->dSet_VALUE = _Set_VALUE;
		p_report->dCurrent_VALUE = _Current_VALUE;

		p_report->dError_PERCENT = _Error_PERCENT;
		p_report->dError_THRESHOLD = _Error_THRESHOLD;
		p_report->dError_SEC = _Error_SEC;
		p_report->dError_MIN = _Error_MIN;
		p_report->dError_MAX = _Error_MAX;

		p_report->dRange_MIN = _Range_MIN;
		p_report->dRange_MAX = _Range_MAX;
		p_report->iRange_DEC = _Range_DEC;
	};
	//============================================================================


private:
	void _Init__Timer()
	{
		if(pCH__CUR_STABLE_DELAY_SEC != NULL)
		{
			mCtrl__Delay_Timer->REGISTER__COUNT_CHANNEL_NAME(pCH__CUR_STABLE_DELAY_SEC->Get__CHANNEL_NAME());
		}

		if(pCH__CUR_STABLE_CHECK_SEC != NULL)
		{
			mCtrl__Checking_Timer->REGISTER__COUNT_CHANNEL_NAME(pCH__CUR_STABLE_CHECK_SEC->Get__CHANNEL_NAME());
		}

		if(pCH__CUR_ERROR_CHECK_SEC != NULL)
		{
			mCtrl__Error_Timer->REGISTER__COUNT_CHANNEL_NAME(pCH__CUR_ERROR_CHECK_SEC->Get__CHANNEL_NAME());
		}
	}

	void _Init__Error_State(const bool active__pre_set = true)
	{
		bActive__Delay_Check    = true;
		bActive__Stable_State   = false;
		bActive__Checking_State = false;
		bActive__Error_State    = false;

		mCtrl__Delay_Timer->STOP_ZERO();
		mCtrl__Checking_Timer->STOP_ZERO();
		mCtrl__Error_Timer->STOP_ZERO();

		if(active__pre_set)		dPre__Set_Value = 0.0;
	}

	void _Check__Error_State()
	{
		if(pCH__CFG_USE == NULL)			return;
		if(pCH__ACTIVE_CHECK == NULL)		return;

		if(pCH__CFG_USE->Check__DATA("YES") < 0)
		{
			_Init__Error_State();
			return;
		}
		if(pCH__ACTIVE_CHECK->Check__DATA("ON") < 0)
		{
			_Init__Error_State();
			return;
		}

		// ...
		double cfg__delay_sec = 0.0;
		double cfg__check_sec = 0.0;

		if(pCH__CFG_STABLE_DELAY_SEC != NULL)		cfg__delay_sec = pCH__CFG_STABLE_DELAY_SEC->Get__VALUE();
		if(pCH__CFG_STABLE_CHECK_SEC != NULL)		cfg__check_sec = pCH__CFG_STABLE_CHECK_SEC->Get__VALUE();

		// ...
		double set_value = 0.0;
		double cur_value = 0.0;

		if(pCH__REF_CHANNEL_SET__ANALOG != NULL)
		{
			set_value = pCH__REF_CHANNEL_SET__ANALOG->Get__VALUE();
		}
		else if(pCH__REF_CHANNEL_SET__STRING != NULL)
		{
			CString ch_data = pCH__REF_CHANNEL_SET__STRING->Get__STRING();
			set_value = atof(ch_data);
		}

		if(pCH__REF_CHANNEL_GET__ANALOG != NULL)
		{
			cur_value = pCH__REF_CHANNEL_GET__ANALOG->Get__VALUE();
		}
		else if(pCH__REF_CHANNEL_GET__STRING != NULL)
		{
			CString ch_data = pCH__REF_CHANNEL_GET__STRING->Get__STRING();
			cur_value = atof(ch_data);
		}

		// ...
		bool active__set_change = false;

		if(dPre__Set_Value != set_value)
		{
			dPre__Set_Value = set_value;

			active__set_change = true;
		}

		if(active__set_change)
		{
			_Init__Error_State(false);

			mCtrl__Delay_Timer->START__COUNT_UP(9999);
			return;
		}

		if(bActive__Delay_Check)
		{
			if(mCtrl__Delay_Timer->Get__CURRENT_TIME() >= cfg__delay_sec)
			{
				bActive__Delay_Check = false;				
				mCtrl__Delay_Timer->STOP_ZERO();
			}
		}

		// ...
		double cfg__stable_per   = 0.0;
		double cfg__tol_data_per = 0.0;
		double cfg__tol_zero_per = 0.0;

		if(pCH__CFG_TOLERANCE_DATA_PERCENT != NULL)	
		{
			cfg__tol_data_per = pCH__CFG_TOLERANCE_DATA_PERCENT->Get__VALUE();
			cfg__stable_per = cfg__tol_data_per;
		}
		if(pCH__CFG_STABLE_DATA_PERCENT != NULL)
		{
			cfg__stable_per = pCH__CFG_STABLE_DATA_PERCENT->Get__VALUE();
		}

		if(pCH__CFG_TOLERANCE_ZERO_PERCENT != NULL)
		{
			cfg__tol_zero_per = pCH__CFG_TOLERANCE_ZERO_PERCENT->Get__VALUE();
		}

		// ...
		bool active__nax_check = false;

		double ref__set_max = 0.0;
		double ref__set_min = 0.0;
		int ref__set_dec = 3;

		double err_stable = 0.0;
		double err_value  = 0.0;

		if(pCH__REF_CHANNEL_RANGE != NULL)
		{
			active__nax_check = true;

			pCH__REF_CHANNEL_RANGE->Get__MIN_MAX_DEC(ref__set_min, ref__set_max, ref__set_dec);
		}

		if((bActive__MAX_RANGE) && (active__nax_check))
		{
			if(bActive__ERROR_THRESHOLD)
			{
				err_stable = cfg__stable_per;
				err_value  = cfg__tol_data_per;
			}
			else
			{
				err_stable = ref__set_max * cfg__stable_per * 0.01;
				err_value  = ref__set_max * cfg__tol_data_per * 0.01;
			}
		}
		else
		{
			if(bActive__ERROR_THRESHOLD)
			{
				err_stable = cfg__stable_per;
				err_value  = cfg__tol_data_per;
			}
			else
			{
				err_stable = set_value * cfg__stable_per * 0.01;
				err_value  = set_value * cfg__tol_data_per * 0.01;
			}
		}

		double stable_min = set_value - err_stable;
		double stable_max = set_value + err_stable;

		double err_min = set_value - err_value;
		double err_max = set_value + err_value;

		// ...
		CString ch_data;

		if(pCH__CUR_STABLE_MIN != NULL)
		{
			ch_data.Format("%.3f", stable_min);
			pCH__CUR_STABLE_MIN->Set__DATA(ch_data);
		}
		if(pCH__CUR_STABLE_MAX != NULL)
		{
			ch_data.Format("%.3f", stable_max);
			pCH__CUR_STABLE_MAX->Set__DATA(ch_data);
		}

		if(pCH__CUR_ERROR_MIN != NULL)
		{
			ch_data.Format("%.3f", err_min);
			pCH__CUR_ERROR_MIN->Set__DATA(ch_data);
		}
		if(pCH__CUR_ERROR_MAX != NULL)
		{
			ch_data.Format("%.3f", err_max);
			pCH__CUR_ERROR_MAX->Set__DATA(ch_data);
		}

		// Report ...
		{
			_Set_VALUE = set_value;
			_Current_VALUE = cur_value;

			_Error_PERCENT = cfg__tol_data_per;
			_Error_THRESHOLD = fabs(err_max - err_min) * 0.5;
			_Error_MIN = err_min;
			_Error_MAX = err_max;

			_Range_MIN = ref__set_min;
			_Range_MAX = ref__set_max;
			_Range_DEC = ref__set_dec;
		}

		if(cfg__tol_zero_per > 0.001)
		{
			double cfg__zero_err = ref__set_max * cfg__tol_zero_per * 0.01;

			if(set_value < cfg__zero_err)
			{
				bActive__Stable_State = true;

				bActive__Error_State = false;
				mCtrl__Error_Timer->STOP_ZERO();
				return;
			}
		}

		if((cur_value < err_min) || (cur_value > err_max))
		{
			bActive__Stable_State = false;

			bActive__Checking_State = false;
			mCtrl__Checking_Timer->STOP_ZERO();

			if(!bActive__Delay_Check)
			{
				if(!bActive__Error_State)
				{
					bActive__Error_State = true;
					mCtrl__Error_Timer->START__COUNT_UP(9999);
				}
			}
			return;
		}
		else if((cur_value >= stable_min) && (cur_value <= stable_max))
		{
			if(!bActive__Stable_State)
			{
				if(!bActive__Checking_State)
				{
					bActive__Checking_State = true;
					mCtrl__Checking_Timer->START__COUNT_UP(9999);
				}

				if(bActive__Checking_State)
				{
					if(mCtrl__Checking_Timer->Get__CURRENT_TIME() >= cfg__check_sec)
					{
						bActive__Stable_State = true;
						mCtrl__Checking_Timer->STOP_ZERO();

						bActive__Delay_Check = false;	
						mCtrl__Delay_Timer->STOP_ZERO();
					}
				}
			}

			bActive__Error_State = false;
			mCtrl__Error_Timer->STOP_ZERO();
		}
		return;
	}

	bool _Check__Error_Time()
	{
		if(bActive__Error_State)
		{
			double cfg__error_sec = 0.0;

			if(pCH__CFG_ERROR_CHECK_SEC != NULL)
			{
				cfg__error_sec = pCH__CFG_ERROR_CHECK_SEC->Get__VALUE();
			}

			_Error_SEC = cfg__error_sec;

			if(mCtrl__Error_Timer->Get__CURRENT_TIME() > cfg__error_sec)
			{
				bActive__Error_State = false;
				mCtrl__Error_Timer->STOP_ZERO();

				return true;
			}
		}
		return false;
	}
};

