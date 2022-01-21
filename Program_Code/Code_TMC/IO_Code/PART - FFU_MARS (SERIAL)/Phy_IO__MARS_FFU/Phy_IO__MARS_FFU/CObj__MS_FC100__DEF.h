#pragma once


// ...
#define  CFG__FAN_SIZE					4
#define  CFG__MAX_DATA					100

// ...
#define  STR__ONLINE					"ONLINE"
#define  STR__OFFLINE					"OFFLINE"

#define  STR__LOCAL						"LOCAL"
#define  STR__REMOTE					"REMOTE"

#define  STR__OK						"OK"
#define  STR__ON						"ON"
#define  STR__OFF						"OFF"


// ...
#define  OFFLINE						-1
#define  ONLINE							1

#define  SP								0x20
#define  CR								0x0D
#define  LF								0x0A
#define  SOH							0x01
#define  STX							0x02
#define  ETX							0x03
#define  ACK							0x06
#define  NAK							0x15
#define  EOT							0x04
#define  ENQ							0x05
#define	 SAC							0x23
#define	 ECH							0x3E
#define  PACKET_ADR_DEF					0x30


// ...
#define _CMMD_MODE__STATUS_GET			0xce
#define _CMMD_MODE__GROUP_GET           0x8e
#define _CMMD_MODE__BLOCK_GET           0x8a

#define _CMMD_MODE__GROUP_SET           0x8d
#define _CMMD_MODE__BLOCK_SET           0x89

