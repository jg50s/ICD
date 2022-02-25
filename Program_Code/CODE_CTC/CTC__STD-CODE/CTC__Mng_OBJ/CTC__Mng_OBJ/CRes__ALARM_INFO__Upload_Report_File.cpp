#include "stdafx.h"
#include "CTC__Mng_OBJ.h"

#include "CRes__ALARM_INFO.h"

#include "Interface_Code.h"
#include "Macro_Function.h"


// ...
int CRes__ALARM_REPORT::
Upload__Report_File()
{
	EnterCriticalSection(&mCS_LOCK);

	CString path_report;

	// ...
	{
		CString dir_alarm;

		SCX__SEQ_INFO x_seq_info;
		x_seq_info->Get__DIR_ROOT(dir_alarm);

		dir_alarm += "\\EQP_INF";
		dir_alarm += "\\RES-ALARM";

		path_report.Format("%s\\alarm_Report.input", dir_alarm);
	}

	printf(" * CRes__ALARM_REPORT::Upload__Report_File() ... \n");
	printf(" ** path_report <- [%s] \n", path_report);

	// ...
	_Clear__ALL_Of_REPORT_NO();

	int r_flag = _Upload__Report_File(path_report);

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}


//...
#define _CFG_CMMD__REPORT_DISABLE			"#REPORT=DISABLE"
#define _CFG_CMMD__EQP_ID					"#EQP.ID="
#define _CFG_CMMD__OBJECT_NAME				"#OBJECT_NAME="
#define _CFG_CMMD__ALM_ID					"#ID="

#define _CMMD_ID__REPORT_DISABLE			0
#define _CMMD_ID__EQP_ID					1
#define _CMMD_ID__OBJECT_NAME				2
#define _CMMD_ID__ALM_ID					3


int CRes__ALARM_REPORT::
_Upload__Report_File(const CString& file_path)
{
	CString file_data;

	if(MACRO__Get_File_Data(file_path, file_data) < 0)
	{
		printf("Upload__Report_File() ... \n");
		printf(" * Error : File_Path [%s] \n", file_path);
		return -1;
	}

	// ...
	CStringArray l_line;
	MACRO__Get_Line_List_From_File_Data(file_data, l_line);

	// ...
	bool active__report_disable = false;

	int para__eqp_id;
	int para__ext_id;

	int i_limit = l_line.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_line = l_line[i];

		// ...
		CString key_name;

		int k_limit = 4;
		int k;

		for(k=0; k<k_limit; k++)
		{
				 if(k == _CMMD_ID__REPORT_DISABLE)			key_name = _CFG_CMMD__REPORT_DISABLE;
			else if(k == _CMMD_ID__EQP_ID)					key_name = _CFG_CMMD__EQP_ID;
			else if(k == _CMMD_ID__OBJECT_NAME)				key_name = _CFG_CMMD__OBJECT_NAME;
			else if(k == _CMMD_ID__ALM_ID)					key_name = _CFG_CMMD__ALM_ID;
			else											continue;

			int s_index = str_line.Find(key_name);
			if(s_index < 0)		continue;

			CString str_data = str_line;
			str_data.Delete(0, s_index+key_name.GetLength());
			
			CStringArray l_para;
			MACRO__Convert__LIST('	', str_data, l_para, -1);

			if(k == _CMMD_ID__REPORT_DISABLE)
			{
				active__report_disable = true;

				para__eqp_id = -1;
				para__ext_id = -1;
			}
			else if(active__report_disable)
			{
				if(k == _CMMD_ID__EQP_ID)
				{
					para__eqp_id = atoi(str_data);
				}
				else if(k == _CMMD_ID__OBJECT_NAME)
				{
				}
				else if(k == _CMMD_ID__ALM_ID)
				{
					if(l_para.GetSize() > 1)
					{
						para__ext_id = atoi(l_para[1]);

						_Load__EQP_ID_Of_REPORT_NO(para__eqp_id, para__ext_id);
					}
				}
			}

			break;
		}
	}

	return 1;
}
