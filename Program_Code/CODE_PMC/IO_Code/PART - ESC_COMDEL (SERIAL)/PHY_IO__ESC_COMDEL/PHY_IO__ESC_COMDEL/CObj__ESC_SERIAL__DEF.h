#pragma once


// ...
#define CMD__LOCAL					"EX"
#define CMD__REMOTE					"!"

#define CMD__ENABLE_ECHO			"EE"
#define CMD__DISABLE_ECHO			"DE"

#define CMD__ON						"EV"
#define CMD__OFF					"DV"

#define CMD__VOLTAGE_SET			"SV"
#define CMD__VOLTAGE_READ			"RV"

#define CMD__CURRENT_LIMIT_SET		"SI"
#define CMD__CURRENT_READ			"RI"

#define CMD__POSITIVE				"V-"
#define CMD__NEGATIVE				"V+"

#define CMD__RAMP_UP				"P+"
#define CMD__RAMP_DN				"P-"


// ...
#define  SP							0x20
#define  CR							0x0D
#define  LF							0x0A
#define  SOH						0x01
#define  STX						0x02
#define  ETX						0x03
#define  ACK						0x06
#define  NAK						0x15
#define  EOT						0x04
#define  ENQ						0x05
#define	 SAC						0x23
#define	 ECH						0x3E
#define  PACKET_ADR_DEF				0x30


// ...
#define STR__REMOTE					"REMOTE"
#define STR__LOCAL					"LOCAL"

#define STR__ONLINE					"ONLINE"
#define STR__OFFLINE				"OFFLINE"

#define STR__ON						"ON"
#define STR__OFF					"OFF"

#define STR__POSITIVE				"POSITIVE"
#define STR__NEGATIVE				"NEGATIVE"

