#include "StdAfx.h"
#include "CObj__STD_TYPE.h"
#include "CObj__STD_TYPE__DEF.h"
#include "CObj__STD_TYPE__ALID.h"


//----------------------------------------------------------------------------------------------------
// LIGHT RED -----
int CObj__STD_TYPE::
Call__RED_ON()
{
	doEXT_CH__LIGHT_RED__ON_OFF->Set__DATA(STR__ON);
	doEXT_CH__LIGHT_RED__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__RED_OFF()
{
	doEXT_CH__LIGHT_RED__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_RED__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__RED_BLINK()
{
	doEXT_CH__LIGHT_RED__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_RED__BLINK->Set__DATA(STR__ON);

	return 1;
}


// LIGHT YELLOW -----
int CObj__STD_TYPE::
Call__YELLOW_ON()
{
	doEXT_CH__LIGHT_YELLOW__ON_OFF->Set__DATA(STR__ON);
	doEXT_CH__LIGHT_YELLOW__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__YELLOW_OFF()
{
	doEXT_CH__LIGHT_YELLOW__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_YELLOW__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__YELLOW_BLINK()
{
	doEXT_CH__LIGHT_YELLOW__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_YELLOW__BLINK->Set__DATA(STR__ON);

	return 1;
}


// LIGHT GREEN -----
int CObj__STD_TYPE::
Call__GREEN_ON()
{
	doEXT_CH__LIGHT_GREEN__ON_OFF->Set__DATA(STR__ON);
	doEXT_CH__LIGHT_GREEN__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__GREEN_OFF()
{
	doEXT_CH__LIGHT_GREEN__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_GREEN__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__GREEN_BLINK()
{
	doEXT_CH__LIGHT_GREEN__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_GREEN__BLINK->Set__DATA(STR__ON);

	return 1;
}


// LIGHT BLUE -----
int CObj__STD_TYPE::
Call__BLUE_ON()
{
	doEXT_CH__LIGHT_BLUE__ON_OFF->Set__DATA(STR__ON);
	doEXT_CH__LIGHT_BLUE__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__BLUE_OFF()
{
	doEXT_CH__LIGHT_BLUE__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_BLUE__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__BLUE_BLINK()
{
	doEXT_CH__LIGHT_BLUE__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_BLUE__BLINK->Set__DATA(STR__ON);

	return 1;
}

// LIGHT WHITE -----
int CObj__STD_TYPE::
Call__WHITE_ON()
{
	doEXT_CH__LIGHT_WHITE__ON_OFF->Set__DATA(STR__ON);
	doEXT_CH__LIGHT_WHITE__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__WHITE_OFF()
{
	doEXT_CH__LIGHT_WHITE__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_WHITE__BLINK->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__WHITE_BLINK()
{
	doEXT_CH__LIGHT_WHITE__ON_OFF->Set__DATA(STR__OFF);
	doEXT_CH__LIGHT_WHITE__BLINK->Set__DATA(STR__ON);

	return 1;
}


// ALARM BUZZER -----
int CObj__STD_TYPE::
Call__ALARM_BUZZER_ON()
{
	doEXT_CH__ALARM_BUZZER->Set__DATA(STR__ON);

	return 1;
}
int CObj__STD_TYPE::
Is__ALARM_BUZZER_ON()
{
	if(doEXT_CH__ALARM_BUZZER->Check__DATA(STR__ON) > 0)	return 1;

	return -1;
}

int CObj__STD_TYPE::
Call__ALARM_BUZZER_OFF()
{
	doEXT_CH__ALARM_BUZZER->Set__DATA(STR__OFF);

	return 1;
}
int CObj__STD_TYPE::
Call__ALARM_BUZZER_RESET_ON()
{
	doEXT_CH__ALARM_BUZZER_RESET->Set__DATA(STR__ON);

	return 1;
}
int CObj__STD_TYPE::
Is__ALARM_BUZZER_RESET_ON()
{
	if(doEXT_CH__ALARM_BUZZER_RESET->Check__DATA(STR__ON) > 0)	return 1;

	return -1;
}
int CObj__STD_TYPE::
Call__ALARM_BUZZER_RESET_OFF()
{
	doEXT_CH__ALARM_BUZZER_RESET->Set__DATA(STR__OFF);

	return 1;
}

int CObj__STD_TYPE::
Seq__SET_BUZZER_ON()
{
	if(Is__ALARM_BUZZER_ON() < 0)
	{
		Call__ALARM_BUZZER_ON();
	}

	if(Is__ALARM_BUZZER_RESET_ON() < 0)
	{
		Call__ALARM_BUZZER_RESET_ON();
	}

	return 1;
}
int CObj__STD_TYPE::
Seq__SET_BUZZER_OFF()
{
	if(Is__ALARM_BUZZER_ON() > 0)
	{
		Call__ALARM_BUZZER_OFF();
	}

	if(Is__ALARM_BUZZER_RESET_ON() > 0)
	{
		Call__ALARM_BUZZER_RESET_OFF();
	}

	return 1;
}

// MELODY -----
int CObj__STD_TYPE::
Call__MELODY_ON()
{
	Call__MELODY_OFF();

	// ...
	{
		CString str_data = dCH__CFG_MELODY_NUM->Get__STRING();
		int i = atoi(str_data) - 1;

		doEXT_CH__MELODY[i]->Set__DATA(STR__ON);
	}
	return 1;
}

int CObj__STD_TYPE::
Call__MELODY_OFF()
{
	CString str_data;

	// ...
	for (int i=0; i<CFG_MELODY_MAX; i++)
	{
		doEXT_CH__MELODY[i]->Set__DATA(STR__OFF);
	}

	return 1;
}
