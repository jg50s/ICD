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

#define ACT__CHECK					"CHECK"
#define ACT__CLEAR					"CLEAR"


// ...
#define  STR__ONLINE				"ONLINE"
#define  STR__OFFLINE				"OFFLINE"

#define  STR__ON					"ON"
#define  STR__OFF					"OFF"

#define  STR__OK					"OK"
#define  STR__ERROR					"ERROR"

#define STR__STAND_BY				"STANDBY"
#define STR__AUTO_ON				"AUTOON"

#define STR__MANUAL					"MANUAL"
#define STR__AUTO					"AUTO"

#define STR__NORMAL					"NORMAL"
#define STR__ABNORMAL				"ABNORMAL"

#define STR__NOT_MATCHED			"NOTMATCHED"
#define STR__MATCHED				"MATCDED"