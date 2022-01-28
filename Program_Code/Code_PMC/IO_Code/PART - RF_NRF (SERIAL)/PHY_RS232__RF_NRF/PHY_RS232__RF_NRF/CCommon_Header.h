#pragma once


// ...
union _DATA__2BYTE_INT
{
	unsigned char _byte[2];
	unsigned int  _hexa;
};
union _DATA__3BYTE_INT
{
	unsigned char _byte[3];
	unsigned int  _hexa;
};


// ...
#define MAX_CHAR					256


// ...
#define ACT__RETRY					"RETRY"
#define ACT__ABORT					"ABORT"
#define ACT__IGNORE					"IGNORE"


// ...
#define  STR__ONLINE				"ONLINE"
#define  STR__OFFLINE				"OFFLINE"

#define  STR__ON					"ON"
#define  STR__OFF					"OFF"

#define  STR__OK					"OK"
#define  STR__ERROR					"ERROR"

#define  STR__CW					"CW"
#define  STR__PULSE					"PULSE"

#define  STR__WRITE					"WRITE"
#define  STR__ERASE					"ERASE"

#define  STR__Normal				"Normal"
#define  STR__Abnormal				"Abnormal"
	
#define  STR__Disable				"Disable"
#define  STR__Enable				"Enable"
