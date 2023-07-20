#pragma once


// ...
union _DATA__4BYTE_INT
{
	unsigned char _byte[4];
	int  _hexa;
};
union _DATA__4BYTE_UINT
{
	unsigned char _byte[4];
	unsigned int  _hexa;
};

union _DATA__2BYTE_UINT
{
	unsigned char _byte[2];
	unsigned int  _hexa;
};


// ...
#define MAX_CHAR					256


// ...
#define ACT__RETRY					"RETRY"
#define ACT__ABORT					"ABORT"
#define ACT__IGNORE					"IGNORE"

#define ACT__CHECK					"CHECK"
#define ACT__CLEAR					"CLEAR"


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

#define  STR__NULL					"NULL"
#define  STR__NONE					"NONE"
#define  STR__NO					"NO"

