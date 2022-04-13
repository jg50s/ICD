#pragma once


// ...
#define _SM									0x05
#define _END								0x0A

#define  _MAT_CMD__DO_SET_STATUS			0X00
#define  _MAT_CMD__DO_MOTOR_RESET			0X08

#define  _MAT_CMD__AO_SET_LOAD_PRESET		0X01
#define  _MAT_CMD__AO_SET_TUNE_PRESET		0X02
#define  _MAT_CMD__AO_SET_LOAD_MANUAL		0X0F
#define  _MAT_CMD__AO_SET_TUNE_MANUAL		0X10

// ...
#define  _MAT_CMD__SI_MAT_STATE				0x40
#define  _MAT_CMD__SI_LOAD_PRESET			0x41
#define  _MAT_CMD__SI_TUNE_PRESET			0x42
#define  _MAT_CMD__SI_CUR_LOAD_POSITION		0x43
#define  _MAT_CMD__SI_CUR_TUNE_POSITION		0x44
#define  _MAT_CMD__SI_VPP_VALUE				0x45

#define  _MAT_CMD__SI_VRMS_IRMS				0x05
#define  _MAT_CMD__SI_IMPEDANCE				0x06
#define  _MAT_CMD__SI_FORWARD_PWR			0x03
#define  _MAT_CMD__SI_REF_PWR				0x04
#define  _MAT_CMD__SI_START_STOP_SWR		0x14
#define  _MAT_CMD__SI_SWR					0x07
#define  _MAT_CMD__SI_PHASE_SHIFT			0xCE

