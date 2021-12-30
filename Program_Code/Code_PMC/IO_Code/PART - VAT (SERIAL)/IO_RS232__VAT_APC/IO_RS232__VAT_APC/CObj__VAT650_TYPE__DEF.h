#pragma once


// ...
#define  STR__ENABLE					"ENABLE"

#define  STR__ONLINE					"ONLINE"
#define  STR__OFFLINE					"OFFLINE"

#define  STR__LOCAL						"LOCAL"
#define  STR__REMOTE					"REMOTE"

#define  STR__ON						"ON"
#define  STR__OFF						"OFF"

#define  STR__STANDBY					"STANDBY"
#define  STR__MAINTMODE					"MAINTMODE"

#define  STR__1K_TYPE					"_1000"
#define  STR__1M_TYPE					"10000"


// ...
#define	 MAX_GUI_RANGE_PRESSURE			1000			// mTorr
#define	 MAX_GUI_RANGE_POSITION			1000			// UI에서 사용자가 설정한 Range

#define	 MAX_CFG_RANGE_PRESSURE			1000			// Controller에 설정한 Range
#define	 MAX_CFG_RANGE_POSITION			1000		


// ...
#define  VALVE_OPEN_TIMEOUT				20.0
#define  VALVE_CLOSE_TIMEOUT			20.0
#define  VALVE_PRESS_STS_TIMEOUT		20.0
#define  VALVE_POSITION_STS_TIMEOUT		20.0
#define  VALVE_HOLD_TIMEOUT				20.0


// ...
#define  DRV__CMD_FAIL					-11					// 


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
#define  ESC							0x1B
//
