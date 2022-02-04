#pragma once


#define GASCAL_CONSTANT 2.156381e-2
/*
	flow rate (cc/min) = V * P * 22414 (cc/mole) /
						[ (0.08206 liter atm/K mole) * (273.16 + T) * t ]

	V : the chamber volume when gap distance = 5.5 cm, liter
    P : the pressure change, atm
	t : the elapse time, minutes
	T : the temperature, Celcius

    flow rate (cc/min) = V * P / (273.16 + T) / t * C
		where C = 22414 / 0.08206

    in order to use V (cc), P (mt) and t (sec), we calculated the C
		as:
			C = 22414 * (60 min -> sec)
				/ 0.08206 / (1000 liter -> cc) / (1000 * 760 atm -> mt)

			C = 2.156381 E-02
*/


// ...
#define CFG__MFC_SIZE								17
#define CFG__GAS_FLOW_LIST							10
#define CFG__GAS_FLOW_EVEN_LIST						5


// ...
#define CHECK_MODE__PARTIAL_PRESSURE				1
#define CHECK_MODE__MFC_CAL							2
#define CHECK_MODE__ALL_CHECK						3


// ...
#define CMMD_MODE__CHM_HIGH_VAC_PUMP				"HIGH_VAC_PUMP"
#define CMMD_MODE__CHM_CLOSE_VAC_LINE  				"CLOSE.VAC_LINE"

#define CMMD_MODE__VAT_OPEN							"OPEN"
#define CMMD_MODE__VAT_CLOSE						"CLOSE"

#define CMMD_MODE__MFC_CONTROL						"CONTROL"
#define CMMD_MODE__MFC_CLOSE						"CLOSE"

#define CMMD_MODE__FNC_MFC__MFC_CONTROL				"MFC_CONTROL"
#define CMMD_MODE__FNC_MFC__ALL_CLOSE				"ALL_CLOSE"
//
